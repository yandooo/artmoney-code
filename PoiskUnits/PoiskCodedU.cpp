//---------------------------------------------------------------------------


#pragma hdrstop

#include <vcl.h>

#include "PoiskCodedU.h"
#include "Windows.h"
#include "ProcessInfoU.h"
#include "MainFormU.h"
#include "GoFormU.h"
struct StructToFile{
       LPVOID        Address;
       unsigned char Zmey;
};

typedef StructToFile* LPStructToFile;
//---------------------------------------------------------------------------
void CreateSnapshotOfProcess(DWORD ProcessHandle, AnsiString File){
      SYSTEM_INFO              Sinfo;
      MEMORY_BASIC_INFORMATION MemInfo;
      long                     Start = 0, Fin = 0, FPage = 0, SPage = 0;
      unsigned char            MasPoisk[4096];
      HANDLE                   OpenHandle = NULL, FileMemA = NULL;
      LPVOID                   Point = NULL;
      DWORD                    MemRead, WriteK;
      TGo                      *Go = new TGo(0);

SPage         = PageKol(ProcessHandle);
OpenHandle    = OpenProcess(PROCESS_ALL_ACCESS, FALSE, ProcessHandle);
FileMemA      = CreateFile(File.c_str(), GENERIC_WRITE, FILE_SHARE_WRITE, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
GetSystemInfo(&Sinfo);
Go->GoProgress->MaxValue = SPage;
Go->Show();
Go->Update();
do{
   VirtualQueryEx(OpenHandle, Point, &MemInfo, sizeof(MemInfo));
     if ((MemInfo.Protect==PAGE_READWRITE) && (MemInfo.State!=MEM_FREE)){
        Start = reinterpret_cast<DWORD>(MemInfo.BaseAddress);
        Fin = Start + MemInfo.RegionSize;
     do {
         ReadProcessMemory(OpenHandle , reinterpret_cast<LPVOID>(Start), &MasPoisk, 4096, &MemRead);
         WriteFile(FileMemA, &MasPoisk, 4096, &WriteK, NULL);
         InterlockedExchangeAdd(&Start,4096);
         InterlockedIncrement(&FPage);
         Go->GoProgress->Progress = FPage;
         Application->ProcessMessages();
        }
     while (Start!=Fin);
  }
 Point = (LPVOID)(MemInfo.RegionSize + (DWORD) Point);
}while ( FPage != SPage );
CloseHandle(FileMemA);
CloseHandle(OpenHandle);
delete Go;
};
//*****************************************************************************
long  FirstCodedFALSE(DWORD ProcessHandle, AnsiString File, LPVOID VirtualMem){
   MEMORY_BASIC_INFORMATION MemInfo;
   SYSTEM_INFO              Sinfo;
   unsigned char            FileFirst[4096], FileSecond[4096];
   long                     FindKol = 0, WriteK = 0, Param, SPage = 0, Start = 0, Fin = 0, FPage = 0;
   DWORD                    MemRead = 0, ReadK;
   HANDLE                   OpenHandle = NULL, FileMemA = NULL;
   TVarRec                  Item;
   LPVOID                   Point = NULL;
   StructToFile             *FileWrite;
   TGo                      *Go = new TGo(0);

SPage         = PageKol(ProcessHandle);
OpenHandle    = OpenProcess(PROCESS_ALL_ACCESS, FALSE, ProcessHandle);
FileMemA      = CreateFile(File.c_str(), GENERIC_READ,FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
FileWrite     = reinterpret_cast<LPStructToFile> ( VirtualAlloc(VirtualMem, 4096, MEM_COMMIT, PAGE_READWRITE) );
GetSystemInfo(&Sinfo);
Go->GoProgress->MaxValue = SPage;
Go->Show();
Go->Update();
do{
  VirtualQueryEx(OpenHandle, Point, &MemInfo, sizeof(MemInfo));
     if ((MemInfo.Protect==PAGE_READWRITE) && (MemInfo.State!=MEM_FREE)){
        Start = reinterpret_cast<DWORD>(MemInfo.BaseAddress);
        Fin = Start + MemInfo.RegionSize;
     do {
         ReadProcessMemory(OpenHandle ,reinterpret_cast<LPVOID>(Start), &FileFirst, 4096, &MemRead);
         ReadFile(FileMemA, FileSecond, 4096, &ReadK, NULL);
         for (Param = 0;Param<=4095;InterlockedIncrement(&Param))
             if ( FileFirst[Param] != FileSecond[Param] ){
                 FileWrite[WriteK].Zmey    = FileFirst[Param];
                 FileWrite[WriteK].Address = reinterpret_cast<LPVOID>(Start+Param);
                 InterlockedIncrement(&FindKol);
                 InterlockedIncrement(&WriteK);
                 if (WriteK == 512){
                    FileWrite = reinterpret_cast<LPStructToFile> ( VirtualAlloc( reinterpret_cast<LPVOID>(reinterpret_cast<DWORD>(FileWrite)+ 4096),  4096, MEM_COMMIT, PAGE_READWRITE) );
                    WriteK = 0;}
                 if (MainForm->AddressTable->Count<=300){
                    Item = reinterpret_cast<LPVOID>(Start+Param);
                    MainForm->AddressTable->Items->Add(Format(": %p", &Item, 0));}
             }
         Application->ProcessMessages();
         InterlockedExchangeAdd(&Start,4096);
         InterlockedIncrement(&FPage);
         Go->GoProgress->Progress = FPage;
        }while (Start!=Fin);
  }Point = reinterpret_cast<LPVOID>(MemInfo.RegionSize + reinterpret_cast<DWORD>(Point));
}while (FPage!=SPage);
CloseHandle(OpenHandle);
CloseHandle(FileMemA);
delete Go;
return FindKol;
};
//******************************************************************************
long  FirstCodedTRUE(DWORD ProcessHandle, AnsiString File, LPVOID VirtualMem){
   MEMORY_BASIC_INFORMATION MemInfo;
   SYSTEM_INFO              Sinfo;
   unsigned char            FileFirst[4096], FileSecond[4096];
   long                     FindKol = 0, WriteK = 0, Param, SPage = 0, Start = 0, Fin = 0, FPage = 0;
   DWORD                    MemRead = 0, ReadK;
   HANDLE                   OpenHandle = NULL, FileMemA = NULL;
   TVarRec                  Item;
   LPVOID                   Point = NULL;
   StructToFile             *FileWrite;
   TGo                      *Go = new TGo(0);

SPage         = PageKol(ProcessHandle);
OpenHandle    = OpenProcess(PROCESS_ALL_ACCESS, FALSE, ProcessHandle);
FileMemA      = CreateFile(File.c_str(), GENERIC_READ,FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
FileWrite     = reinterpret_cast<LPStructToFile> ( VirtualAlloc(VirtualMem, 4096, MEM_COMMIT, PAGE_READWRITE) );
GetSystemInfo(&Sinfo);
Go->GoProgress->MaxValue = SPage;
Go->Show();
do{
  VirtualQueryEx(OpenHandle, Point, &MemInfo, sizeof(MemInfo));
     if ((MemInfo.Protect==PAGE_READWRITE) && (MemInfo.State!=MEM_FREE)){
        Start = reinterpret_cast<DWORD>(MemInfo.BaseAddress);
        Fin = Start + MemInfo.RegionSize;
     do {
         ReadProcessMemory(OpenHandle ,reinterpret_cast<LPVOID> (Start), &FileFirst, 4096, &MemRead);
         ReadFile(FileMemA, FileSecond, 4096, &ReadK, NULL);
         for (Param = 0;Param<=4095;InterlockedIncrement(&Param))
             if ( FileFirst[Param] == FileSecond[Param] ){
                 FileWrite[WriteK].Zmey    = FileFirst[Param];
                 FileWrite[WriteK].Address = reinterpret_cast<LPVOID>(Start+Param);
                 InterlockedIncrement(&FindKol);
                 InterlockedIncrement(&WriteK);
                 if (WriteK == 512){
                    FileWrite = reinterpret_cast<LPStructToFile> ( VirtualAlloc( reinterpret_cast<LPVOID>(reinterpret_cast<DWORD>(FileWrite)+ 4096),  4096, MEM_COMMIT, PAGE_READWRITE) );
                    WriteK = 0;}
                 if (MainForm->AddressTable->Count<=300){
                    Item = reinterpret_cast<LPVOID>(Start+Param);
                    MainForm->AddressTable->Items->Add(Format(": %p", &Item, 0));}
             }
         Application->ProcessMessages();
         InterlockedExchangeAdd(&Start,4096);
         InterlockedIncrement(&FPage);
         Go->GoProgress->Progress = FPage;
        }while (Start!=Fin);
  }Point = reinterpret_cast<LPVOID>(MemInfo.RegionSize + reinterpret_cast<DWORD>(Point));
}while (FPage!=SPage);
CloseHandle(OpenHandle);
CloseHandle(FileMemA);
delete Go;
return FindKol;
};
//******************************************************************************
long  PoiskFALSEAgain (DWORD ProcessHandle, LPVOID VirtualMem, long FindNumber){
      unsigned char            PoiskAll = 0;
      long                     FindKol = 0, WriteK = 0, ReadK = 0, Pages = 0;
      DWORD                    MemRead = 0;
      HANDLE                   OpenHandle = NULL;
      TVarRec                  Item;
      StructToFile             *FileWrite, *FileRead;
      TGo                      *Go = new TGo(0);

OpenHandle    = OpenProcess(PROCESS_ALL_ACCESS, FALSE, ProcessHandle);
FileWrite  = reinterpret_cast<LPStructToFile> (VirtualMem);
FileRead   = reinterpret_cast<LPStructToFile> (VirtualMem);
Go->GoProgress->MaxValue = FindNumber;
Go->Show();
for(FindKol=0;FindKol<FindNumber;InterlockedIncrement(&FindKol)){
       ReadProcessMemory(OpenHandle , FileRead[ReadK].Address, &PoiskAll, 1, &MemRead);
       if ( PoiskAll != FileRead[ReadK].Zmey ){
          FileWrite[WriteK].Zmey    = PoiskAll;
          FileWrite[WriteK].Address = FileRead[ReadK].Address;
          InterlockedIncrement(&WriteK);
                if (MainForm->AddressTable->Count<=500){
                   Item =FileWrite[ReadK].Address;
                   MainForm->AddressTable->Items->Add(Format(": %p", &Item, 0));}
                if (WriteK == 512){
                   FileWrite = reinterpret_cast<LPStructToFile> (reinterpret_cast<DWORD>(FileWrite)+ 4096);
                   InterlockedIncrement(&Pages);
                   WriteK = 0;}
          }
       InterlockedIncrement(&ReadK);
       if (ReadK  == 512){
                 FileRead = reinterpret_cast<LPStructToFile> ( reinterpret_cast<DWORD>(FileRead)+ 4096 );
                    ReadK = 0;}
      Application->ProcessMessages();
      Go->GoProgress->Progress = FindKol;
   }
//-----------------------------Close handles------------------------------
CloseHandle(OpenHandle);
delete Go;
return    Pages*512+WriteK;
};
//******************************************************************************
long  PoiskTRUEAgain (DWORD ProcessHandle, LPVOID VirtualMem, long FindNumber){
      unsigned char            PoiskAll = 0;
      long                     FindKol = 0, WriteK = 0, ReadK = 0, Pages = 0;
      DWORD                    MemRead = 0;
      HANDLE                   OpenHandle = NULL;
      TVarRec                  Item;
      StructToFile             *FileWrite, *FileRead;
      TGo                      *Go = new TGo(0);

OpenHandle    = OpenProcess(PROCESS_ALL_ACCESS, FALSE, ProcessHandle);
FileWrite  = reinterpret_cast<LPStructToFile> (VirtualMem);
FileRead   = reinterpret_cast<LPStructToFile> (VirtualMem);
Go->GoProgress->MaxValue = FindNumber;
Go->Show();
for(FindKol=0;FindKol<FindNumber;InterlockedIncrement(&FindKol)){
       ReadProcessMemory(OpenHandle , FileRead[ReadK].Address, &PoiskAll, 1, &MemRead);
       if ( PoiskAll == FileRead[ReadK].Zmey ){
          FileWrite[WriteK] = FileRead[ReadK];
          InterlockedIncrement(&WriteK);
                if (MainForm->AddressTable->Count<=500){
                   Item =FileWrite[ReadK].Address;
                   MainForm->AddressTable->Items->Add(Format(": %p", &Item, 0));}
                if (WriteK == 512){
                   FileWrite = reinterpret_cast<LPStructToFile> (reinterpret_cast<DWORD>(FileWrite)+ 4096);
                   InterlockedIncrement(&Pages);
                   WriteK = 0;}
          }
       InterlockedIncrement(&ReadK);
       if (ReadK  == 512){
                 FileRead = reinterpret_cast<LPStructToFile> (reinterpret_cast<DWORD>(FileRead)+ 4096);
                    ReadK = 0;}
      Application->ProcessMessages();
      Go->GoProgress->Progress = FindKol;
   }
//-----------------------------Close handles------------------------------
CloseHandle(OpenHandle);
delete Go;
return    Pages*512+WriteK;
};
//******************************************************************************

#pragma package(smart_init)
 