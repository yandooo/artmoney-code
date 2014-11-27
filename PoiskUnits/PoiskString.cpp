//---------------------------------------------------------------------------
#pragma hdrstop

#include <vcl.h>
#include "PoiskString.h"
#include "Windows.h"
#include "ProcessInfoU.h"
#include "MainFormU.h"
//---------------------------------------------------------------------------
long PoiskString(DWORD ProcessHandle,AnsiString BPoiskString, LPVOID VirtualMem){

      char                     MasPoisk[4095], *PoiskB, *PoiskStr;
      SYSTEM_INFO              Sinfo;
      MEMORY_BASIC_INFORMATION MemInfo;
      long                     Start = 0, Fin = 0, Param = 0, FPage = 0, FindKol = 0, SPage = 0, WriteK = 0, i, j;
      HANDLE                   OpenHandle = NULL;
      LPVOID                   Point = NULL;
      DWORD                    MemRead, *FileWrite;
      TVarRec                  Item;
//--------------------------
OpenHandle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, ProcessHandle);
FileWrite  = reinterpret_cast<LPDWORD> ( VirtualAlloc(VirtualMem, 4096, MEM_COMMIT, PAGE_READWRITE) );
GetSystemInfo(&Sinfo);
SPage    = PageKol(ProcessHandle);
PoiskB   = new char[BPoiskString.Length()*2+1];
PoiskStr = new char[BPoiskString.Length()*2+1];
strcpy(PoiskB, BPoiskString.c_str() );
StrUpper(PoiskB);
//--------------------------
do{
   VirtualQueryEx(OpenHandle, Point, &MemInfo, sizeof(MemInfo));
      if ((MemInfo.Protect==PAGE_READWRITE) && (MemInfo.State!=MEM_FREE)){
           InterlockedIncrement(&FPage);
           Start = reinterpret_cast<DWORD>(MemInfo.BaseAddress);Fin = Start + MemInfo.RegionSize;
         do{
           ReadProcessMemory(OpenHandle , reinterpret_cast<LPVOID>(Start), &MasPoisk, 4096, &MemRead);
           for (Param=0;Param<=4095;InterlockedIncrement(&Param))
            if (MasPoisk[Param]==PoiskB[0]){
                  ReadProcessMemory(OpenHandle , reinterpret_cast<LPVOID>(Start+Param), PoiskStr, BPoiskString.Length()*2, &MemRead);
                  //----------------------------------------------------------------
                  for (i = 0;i<BPoiskString.Length();InterlockedIncrement(&i)){
                      if (PoiskStr[i]=='\0')
                         for (j=i;j<BPoiskString.Length()*2;InterlockedIncrement(&j))PoiskStr[j]=PoiskStr[j+1];}
                  //-----------------------------
                      if (strcmp(PoiskB, StrUpper(PoiskStr))==0){
                         FileWrite[WriteK] = Start+Param;
                         InterlockedIncrement(&FindKol);
                         InterlockedIncrement(&WriteK);
                         if (WriteK == 1024){
                            FileWrite = reinterpret_cast<LPDWORD> ( VirtualAlloc( reinterpret_cast<LPVOID>(reinterpret_cast<DWORD>(FileWrite)+ 4096),  4096, MEM_COMMIT, PAGE_READWRITE) );
                            WriteK = 0;}
                         if (MainForm->AddressTable->Count<=500){
                             Item = reinterpret_cast<LPVOID>(Start+Param);
                             MainForm->AddressTable->Items->Add(Format(": %p", &Item, 0));}
                        }
               }
            Application->ProcessMessages();
            InterlockedExchangeAdd(&Start,4096);
         }while (Start!=Fin);
      }Point = reinterpret_cast<LPVOID>(MemInfo.RegionSize + reinterpret_cast<DWORD>(Point));
  }while (FPage!=SPage);
//-------------------------------------------------  
CloseHandle(OpenHandle);
return FindKol;
};
//******************************************************************************
//******************************************************************************
long  PoiskStringAgainQucly(DWORD ProcessHandle,AnsiString BPoiskString, LPVOID VirtualMem, long FindNumber){

      char                     *PoiskB, *PoiskStr;
      long                     FindKol = 0, WriteK = 0, ReadK = 0, Pages = 0, i, j;
      DWORD                    MemRead = 0, *FileWrite, *FileRead;
      HANDLE                   OpenHandle = NULL;
      TVarRec                  Item;
PoiskB   = new char[BPoiskString.Length()*2];
PoiskStr = new char[BPoiskString.Length()*2];
strcpy(PoiskB, BPoiskString.c_str());
StrUpper(PoiskB);
OpenHandle    = OpenProcess(PROCESS_ALL_ACCESS, FALSE, ProcessHandle);
//-----------------------------------------------------------------------------
FileWrite  = reinterpret_cast<LPDWORD> (VirtualMem);
FileRead   = reinterpret_cast<LPDWORD> (VirtualMem);
//-----------------------------------------------------------------------------
for(FindKol=0;FindKol<FindNumber;InterlockedIncrement(&FindKol)){
       ReadProcessMemory(OpenHandle , reinterpret_cast<LPVOID>(FileRead[ReadK]), PoiskStr, BPoiskString.Length(),  &MemRead);
       //----------------------------------------------------------------
                  for (i = 0;i<BPoiskString.Length();InterlockedIncrement(&i)){
                      if (PoiskStr[i]=='\0')
                         for (j=i;j<BPoiskString.Length()*2;InterlockedIncrement(&j))PoiskStr[j]=PoiskStr[j+1];}
                  //-----------------------------
       if (strcmp(PoiskB, StrUpper(PoiskStr))==0){
          FileWrite[WriteK] = FileRead[ReadK];
          InterlockedIncrement(&WriteK);
                if (MainForm->AddressTable->Count<=500){
                   Item =reinterpret_cast<LPVOID>(FileWrite[ReadK]);
                   MainForm->AddressTable->Items->Add(Format(": %p", &Item, 0));}
                if (WriteK == 1024){
                   FileWrite = reinterpret_cast<LPDWORD> (reinterpret_cast<DWORD>(FileWrite)+ 4096);
                   InterlockedIncrement(&Pages);
                   WriteK = 0;}
          }
       InterlockedIncrement(&ReadK);
       if (ReadK  == 1024){
                 FileRead = reinterpret_cast<LPDWORD> ( reinterpret_cast<DWORD>(FileRead)+ 4096 );
                    ReadK = 0;}
      Application->ProcessMessages();
   }
//-----------------------------------------------------------------------------
CloseHandle(OpenHandle);
return    Pages*1024+WriteK;
};
//**********************************************************************
#pragma package(smart_init)
 