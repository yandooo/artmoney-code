//---------------------------------------------------------------------------
#pragma hdrstop

#include "NewZU.h"
#include "MainFormU.h"
#include "ProcessListU.h"
#include "ProcessInfoU.h"
#include "PoiskFormU.h"
#include "PoiskFractional.h"
//----------------------------------------------------------------------------
      signed  char           TypeChar;
      signed  short int      TypeSInt;
      signed  int            TypeInt;
union FractionalFloat {
      unsigned char     BArray[4];
               float    BFloat;
      }TypeFloat, StaticFloat;
union FractionalDouble {
      unsigned char     BArray[8];
               double   BDouble;
      }TypeDouble, StaticDouble;
union FractionalLDouble {
      unsigned char     BArray[10];
        long double     BLDouble;
      }TypeLDouble, StaticLDouble;
//____________________________________________________________________________
struct NewZ{
        LPVOID     Address;
        DWORD      ProcessHandle;
        int        Size;
        char       Type;
};
typedef   NewZ*  LPNewZ;
//--------------------------------
long            KolNewZ = 0;
LPNewZ          MemP;
LPDWORD         Component;
HANDLE          OpenHandle = NULL;
DWORD           MemWrite = 0;
NewZ            Write;
AnsiString      Value;
//--------------------------------
//******************************************************************************
void CreateStruct(long Row){
if (PrezentInTable(MainForm->AddressTable->Items->Strings[Row])==FALSE){
     if ( KolNewZ >=1 )MainForm->SGnew->RowCount = MainForm->SGnew->RowCount+1;
     if (KolNewZ == 0) CreateHeadline();
     Component     = reinterpret_cast<LPDWORD>((reinterpret_cast<DWORD>(GetLPVOID()) + 4*Row));
     Write.Address = reinterpret_cast<LPVOID>(Component[0]);
     Write.ProcessHandle = GetProcessHandle();
Write.Type = SearchForm->RadioGroup->ItemIndex;
MainForm->SGnew->Cells[0][MainForm->SGnew->RowCount-1] = MainForm->AddressTable->Items->Strings[Row];
MainForm->SGnew->Cells[1][MainForm->SGnew->RowCount-1] = IntToStr(Write.ProcessHandle);
MainForm->SGnew->Cells[3][MainForm->SGnew->RowCount-1] = SearchForm->EditIN->Text;
Value = SearchForm->EditIN->Text;
OpenHandle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, Write.ProcessHandle);
/////////////////////////////////////////////////////
switch ( Write.Type ){
     case 0:case 1:{
             ReadProcessMemory(OpenHandle , Write.Address, &TypeInt, 4, &MemWrite);
             ReadProcessMemory(OpenHandle , Write.Address, &TypeSInt,2, &MemWrite);
             ReadProcessMemory(OpenHandle ,Write.Address, &TypeChar, 1, &MemWrite);
             if (TypeInt == Value.ToInt())Write.Size = 4;
             else
                if (TypeSInt == Value.ToInt())Write.Size = 2;
                    else Write.Size = 1;
             MainForm->SGnew->Cells[2][MainForm->SGnew->RowCount-1] = "integer(" + IntToStr(Write.Size) + "b)";break;}
     case 2:{
             StaticFloat.BFloat     = Value.ToDouble();
             StaticDouble.BDouble   = Value.ToDouble();
             StaticLDouble.BLDouble = Value.ToDouble();
             ReadProcessMemory(OpenHandle , Write.Address, &TypeLDouble,10, &MemWrite);
             ReadProcessMemory(OpenHandle , Write.Address, &TypeDouble,8, &MemWrite);
             ReadProcessMemory(OpenHandle , Write.Address, &TypeFloat, 4, &MemWrite);
             if ( _STRCHK(TypeLDouble.BArray, StaticLDouble.BArray,10) ) Write.Size = 10;
             else
                 if ( _STRCHK(TypeDouble.BArray, StaticDouble.BArray,8) ) Write.Size = 8;
                     else Write.Size = 4;
             MainForm->SGnew->Cells[2][MainForm->SGnew->RowCount-1] = "frational(" + IntToStr(Write.Size) + "b)";break;}
      default :{
              Write.Size = Value.Length();
             MainForm->SGnew->Cells[2][MainForm->SGnew->RowCount-1] = "string(" + IntToStr(Write.Size) + "b)";break;}
     };
CloseHandle(OpenHandle);
/////////////////////////////////////////////////////
MemP[KolNewZ] = Write;
InterlockedIncrement(&KolNewZ);
MainForm->LInTable->Caption = "In table : " + IntToStr(KolNewZ);}}
//******************************************************************************
//******************************************************************************
void CreateHeadline(void){
     MainForm->SGnew->Cells[0][0] = "Address";
     MainForm->SGnew->Cells[1][0] = "PID";
     MainForm->SGnew->Cells[2][0] = "Type";
     MainForm->SGnew->Cells[3][0] = "Condition";
MemP = new NewZ[502];}
//******************************************************************************
void DestroyHeadline(void){
for (long i=0;i<MainForm->SGnew->RowCount;InterlockedIncrement(&i))
    MainForm->SGnew->Rows[i]->Clear();
MainForm->SGnew->RowCount = 2;
KolNewZ = 0;
delete [] MemP;
MainForm->LInTable->Caption = "";
}
//******************************************************************************
boolean PrezentInTable(AnsiString check){
for (long i=1;i<MainForm->SGnew->RowCount;InterlockedIncrement(&i))
     if (MainForm->SGnew->Cells[0][i] == check) return TRUE;
return FALSE;}
//******************************************************************************
void ADDALL(void){for (long i=0;i<MainForm->AddressTable->Items->Count;InterlockedIncrement(&i))CreateStruct(i);}
//******************************************************************************
void WriteToMemory(long Item, AnsiString Str){
OpenHandle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, MemP[Item].ProcessHandle);
     switch (MemP[Item].Type){
     case 0:case 1:{
             char       CharN    = Str.ToInt();
             short int  SIntN    = Str.ToInt();
             int        IntegerN = Str.ToInt();
             if (MemP[Item].Size ==  4)
                WriteProcessMemory(OpenHandle , MemP[Item].Address, &IntegerN, MemP[Item].Size, &MemWrite);
             else
             if (MemP[Item].Size == 2 )
                WriteProcessMemory(OpenHandle , MemP[Item].Address, &SIntN, MemP[Item].Size, &MemWrite);
             else
                WriteProcessMemory(OpenHandle , MemP[Item].Address, &CharN, MemP[Item].Size, &MemWrite);
             break;}
     case 2:{
             float        FloatN   = Str.ToDouble();
             double       DoubleN  = Str.ToDouble();
             long double  LDoubleN = Str.ToDouble();
             if (MemP[Item].Size == 10 )
                   WriteProcessMemory(OpenHandle , MemP[Item].Address, &LDoubleN, MemP[Item].Size, &MemWrite);
             else
             if (MemP[Item].Size == 8 )
                   WriteProcessMemory(OpenHandle , MemP[Item].Address, &DoubleN, MemP[Item].Size, &MemWrite);
             else
                   WriteProcessMemory(OpenHandle , MemP[Item].Address, &FloatN, MemP[Item].Size, &MemWrite);
             break;}
     case 3:{
             char*        CharN;
             CharN = new char[Str.Length()*2];
             strcpy(CharN, Str.c_str());
             WriteProcessMemory(OpenHandle , MemP[Item].Address, CharN, MemP[Item].Size, &MemWrite);
             delete  [] CharN;
             break;}
     };
CloseHandle(OpenHandle);
}
//******************************************************************************
#pragma package(smart_init)






