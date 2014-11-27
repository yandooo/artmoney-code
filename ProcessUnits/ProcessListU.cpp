//---------------------------------------------------------------------------


#pragma hdrstop

#include <vcl.h>
#include "ProcessListU.h"
#include "ProcessFormU.h"
#include "ProcessInfoU.h"
#include "Windows.h"
#include "Tlhelp32.h"
//******************************************************************
struct ProcessStruct {
        DWORD            ProcessHandle;
        AnsiString       NameModule;
        AnsiString       WindowTitle;
};
//******************************************************************
     ProcessStruct      MasProcessId[50];
//******************************************************************
char* ProcessWindowTitle (DWORD  ProcessId){

        DWORD          ID;
        HANDLE         NextWindow, ZWindow;
        char           local[MAX_PATH];

 ZWindow = GetTopWindow(NULL);
 NextWindow = GetWindow(ZWindow, GW_HWNDNEXT);
 while (NextWindow!=NULL){
       if (GetParent(NextWindow)==0){
          GetWindowThreadProcessId(NextWindow , &ID);
          if ( ProcessId == ID ){
              GetWindowText(NextWindow, local, MAX_PATH);break;}
          };
       NextWindow = GetWindow(NextWindow, GW_HWNDNEXT);
       };
if (local[0] == NULL) return "Unencountered window - a console version";
else  return local;
};
//******************************************************************
void ProcessStructCreate(void){
 DWORD          MainProcessId = GetCurrentProcessId();
 DWORD          i, ProcessId;
 long           NumberProcess = 2;
 ProcessStruct  PStruct;
 CHAR           local[MAX_PATH];
 PROCESSENTRY32 DataProcess = {0};
 HANDLE         SnapshotHandle;

 for (long i=1;i<ProcessForm->SGProcess->RowCount;InterlockedIncrement(&i))
    ProcessForm->SGProcess->Rows[i]->Clear();
//-------------------------------------------------------------
 SnapshotHandle = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS,0);
        DataProcess.dwSize = sizeof(DataProcess);
        if (Process32First(SnapshotHandle, &DataProcess))
          {
        DataProcess.dwSize = sizeof(DataProcess);
        while (Process32Next(SnapshotHandle,&DataProcess))
             if (DataProcess.th32ProcessID != MainProcessId){
                  MasProcessId[NumberProcess-1].NameModule.sprintf(DataProcess.szExeFile);
                  MasProcessId[NumberProcess-1].ProcessHandle = DataProcess.th32ProcessID;
                  MasProcessId[NumberProcess-1].WindowTitle = ProcessWindowTitle( DataProcess.th32ProcessID );
                  ProcessForm->SGProcess->RowCount = NumberProcess;
                  ProcessForm->SGProcess->Cells[0][NumberProcess-1] = ExtractFileName(MasProcessId[NumberProcess-1].NameModule);
                  ProcessForm->SGProcess->Cells[1][NumberProcess-1] = IntToStr(MasProcessId[NumberProcess-1].ProcessHandle);
                  ProcessForm->SGProcess->Cells[2][NumberProcess-1] = MasProcessId[NumberProcess-1].WindowTitle;
                  InterlockedIncrement(&NumberProcess);
                }
           }
CloseHandle(SnapshotHandle);
ProcessForm->ClientHeight = (NumberProcess+2)*12;
ProcessForm->Caption = "Process List -  founded :  " + IntToStr(NumberProcess-1);
ProcessForm->ShowModal();
};
//---------------------------------------------------------------------------
DWORD GetProcessHandle(void){
if ( CheckProcessPresenceInSystem(MasProcessId[ProcessForm->SGProcess->Row].ProcessHandle) &&
     CheckProcessForErrors(MasProcessId[ProcessForm->SGProcess->Row].ProcessHandle) )
     return MasProcessId[ProcessForm->SGProcess->Row].ProcessHandle;
else
     return 0;
}; 
//---------------------------------------------------------------------------

#pragma package(smart_init)
 