//---------------------------------------------------------------------------


#pragma hdrstop

#include "ProcessInfoU.h"
#include "ProcessInfmU.h"
//---------------------------------------------------------------------------

#pragma hdrstop
#include <vcl.h>

#include "Windows.h"
#include "Tlhelp32.h"
//******************************************************************************
     static  LPVOID  VirtualMem;
//******************************************************************************
boolean CheckProcessForErrors(DWORD ProcessHandle){
HANDLE OpenHandle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, ProcessHandle);
if (OpenHandle == NULL){
MessageBox(NULL, "This process system. To system of no access.", "Informaton", MB_OK);
    CloseHandle(OpenHandle);
    return FALSE;}
else {
    CloseHandle(OpenHandle);
    return TRUE;}
}
//******************************************************************************
boolean CheckProcessPresenceInSystem(DWORD ProcessHandle){
PROCESSENTRY32 DataProcess = {0};
HANDLE SnapshotHandle = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS,0);
        DataProcess.dwSize = sizeof(DataProcess);
        Process32First(SnapshotHandle, &DataProcess);
        DataProcess.dwSize = sizeof(DataProcess);
        while ( Process32Next(SnapshotHandle,&DataProcess) )
             if (DataProcess.th32ProcessID == ProcessHandle){CloseHandle(SnapshotHandle);return TRUE;}
CloseHandle(SnapshotHandle);             
MessageBox(NULL, "At present process in system is not found. The Action is cancelled.", "Informaton", MB_OK);
return FALSE;
}
//******************************************************************************
void AllPageKol(DWORD ProcessHandle, long* FulSize, long* PageRW, long* PageR, long* PageNA,
             long* PageWC, long* PageEX, long* MemFree, long* MemCom, long* MemRES)
{
  LPVOID                     Point = NULL;
 _MEMORY_BASIC_INFORMATION   MemInfo;
 _SYSTEM_INFO                Sinfo;
  HANDLE   OpenHandle;

  *FulSize = 0; *PageRW = 0; *PageR = 0; *PageNA = 0;
  *PageWC  = 0; *PageEX = 0; *MemFree = 0; *MemCom = 0;  *MemRES = 0;

 GetSystemInfo(&Sinfo);
 OpenHandle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, ProcessHandle);
 VirtualQueryEx(OpenHandle, Point, &MemInfo, sizeof(MemInfo));
 while ((DWORD) Point<(DWORD) Sinfo.lpMaximumApplicationAddress)
     {
        if (MemInfo.Protect == PAGE_READWRITE) InterlockedIncrement(PageRW);
        if (MemInfo.Protect == PAGE_NOACCESS)  InterlockedIncrement(PageR);
        if (MemInfo.Protect == PAGE_READONLY)  InterlockedIncrement(PageNA);
        if (MemInfo.Protect == PAGE_WRITECOPY) InterlockedIncrement(PageWC);
        if (MemInfo.Protect == PAGE_EXECUTE)   InterlockedIncrement(PageEX);
        if (MemInfo.State   == MEM_FREE)       InterlockedIncrement(MemFree);
        if (MemInfo.State   == MEM_COMMIT)     InterlockedIncrement(MemCom);
        if (MemInfo.State   == MEM_RESERVE)    InterlockedIncrement(MemRES);
                                               InterlockedIncrement(FulSize);
          Point = (LPVOID) (MemInfo.RegionSize + (DWORD) Point);
          VirtualQueryEx(OpenHandle, Point, &MemInfo, sizeof(MemInfo));
      };
CloseHandle(OpenHandle);
};
//*****************************************************************************
void ProcessInfoCreate(DWORD PID){
 CHAR           local[MAX_PATH];
 PROCESSENTRY32 DataProcess = {0};
 long           PageRW , PageR, PageNA, PageWC,
                PageEX, MemFree, MemCom,  MemRES, FulSize, i;
 HANDLE         SnapshotHandle;
//-------------------------------------------------------------
if ( PID != 0 ){
        FormInfm->Memo->Lines->Clear();
        SnapshotHandle = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS,0);
        DataProcess.dwSize = sizeof(DataProcess);
        if (Process32First(SnapshotHandle, &DataProcess))
          {
        DataProcess.dwSize = sizeof(DataProcess);
        while (Process32Next(SnapshotHandle,&DataProcess))
             if (DataProcess.th32ProcessID == PID){
        FormInfm->Memo->Lines->Add("TH32ProcessID       " + IntToStr(DataProcess.th32ProcessID));
        FormInfm->Memo->Lines->Add("TH32DefaultHeapID   " + IntToStr(DataProcess.th32DefaultHeapID));
        FormInfm->Memo->Lines->Add("TH32ModuleID        " + IntToStr(DataProcess.th32ModuleID));
        FormInfm->Memo->Lines->Add("CNTThreads          " + IntToStr(DataProcess.cntThreads));
        FormInfm->Memo->Lines->Add("TH32ParentProcessID " + IntToStr(DataProcess.th32ParentProcessID));
        FormInfm->Memo->Lines->Add("PCPriClassBase      " + IntToStr(DataProcess.pcPriClassBase));

        AllPageKol(PID, &FulSize, &PageRW, &PageR,&PageNA,&PageWC, &PageEX, &MemFree, &MemCom, &MemRES);

        FormInfm->Memo->Lines->Add("MEM_RESERVE         " + IntToStr(MemRES)  + " Pages");
        FormInfm->Memo->Lines->Add("MEM_FREE            " + IntToStr(MemFree) + " Pages");
        FormInfm->Memo->Lines->Add("MEM_COMMIT          " + IntToStr(MemCom)  + " Pages");
        FormInfm->Memo->Lines->Add("PAGE_EXECUTE        " + IntToStr(PageEX)  + " Pages");
        FormInfm->Memo->Lines->Add("PAGE_NOACCESS       " + IntToStr(PageNA)  + " Pages");
        FormInfm->Memo->Lines->Add("PAGE_READONLY       " + IntToStr(PageR)   + " Pages");
        FormInfm->Memo->Lines->Add("PAGE_READWRITE      " + IntToStr(PageRW)  + " Pages");
        FormInfm->Memo->Lines->Add("PAGE_WRITECOPY      " + IntToStr(PageWC)  + " Pages");
        FormInfm->Memo->Lines->Add("AllPagesOfProcess   " + IntToStr(FulSize) + " Pages");break;
                }
           }
        CloseHandle(SnapshotHandle);
        FormInfm->Show();
 }
};
//******************************************************************************
void Terminate(DWORD PID){
if ( CheckProcessForErrors(PID) ){
   HANDLE OpenHandle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, PID);
   TerminateProcess(OpenHandle,0);
   CloseHandle(OpenHandle);}
};
//******************************************************************************
long PageKol(DWORD ProcessHandle){
  LPVOID                     Point = NULL;
 _MEMORY_BASIC_INFORMATION   MemInfo;
 _SYSTEM_INFO                Sinfo;
  long                       PageNumber, SizeProcess = 0;
  HANDLE                     OpenHandle;
if ( CheckProcessForErrors(ProcessHandle) ){
 GetSystemInfo(&Sinfo);PageNumber = 0;
 OpenHandle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, ProcessHandle);
 VirtualQueryEx(OpenHandle, Point, &MemInfo, sizeof(MemInfo));
 while ((DWORD) Point<(DWORD) Sinfo.lpMaximumApplicationAddress){
        if ((MemInfo.Protect==PAGE_READWRITE) && (MemInfo.State!=MEM_FREE)){
                InterlockedIncrement(&PageNumber);
                InterlockedExchangeAdd(&SizeProcess, MemInfo.RegionSize / 4096);};
          Point = (LPVOID) (MemInfo.RegionSize + (DWORD) Point);
          VirtualQueryEx(OpenHandle, Point, &MemInfo, sizeof(MemInfo));
      };return PageNumber;
  }return 0;
};
//******************************************************************************
void VirtualMemCreate(void){
VirtualMem      =  VirtualAlloc(NULL, 200000000, MEM_RESERVE, PAGE_READWRITE);
                   VirtualAlloc(NULL, 200000000, MEM_RESERVE, PAGE_READWRITE);}
//******************************************************************************
LPVOID GetLPVOID(void){return VirtualMem;}
//******************************************************************************

#pragma package(smart_init)
 