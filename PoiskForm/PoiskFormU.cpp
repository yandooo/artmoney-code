//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "PoiskFormU.h"
#include "MainFormU.h"
#include "ProcessListU.h"
#include "ProcessInfoU.h"

#include "PoiskInteger.h"
#include "PoiskFractional.h"
#include "PoiskString.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TSearchForm *SearchForm;
//---------------------------------------------------------------------------
   long FindKol;
//---------------------------------------------------------------------------
__fastcall TSearchForm::TSearchForm(TComponent* Owner)
        : TForm(Owner){}
//---------------------------------------------------------------------------
void __fastcall TSearchForm::GoBtClick(TObject *Sender){
DWORD ProcessHandle;
SearchForm->Close();
MainForm->AddressTable->Items->Clear();
MainForm->Animate->Active = TRUE;
if ( (ProcessHandle = GetProcessHandle()) != 0 )
switch (RadioGroup->ItemIndex){
case 0:case 1:{
       if (SearchForm->Caption == "Search options")
            FindKol = PoiskInteger(ProcessHandle, EditIN->Text, GetLPVOID());
       else FindKol = PoiskIntegerAgainQucly (ProcessHandle, EditIN->Text, GetLPVOID(), FindKol);
             break;}
case 2:{
       if (SearchForm->Caption == "Search options")
            FindKol = PoiskFractional(ProcessHandle, EditIN->Text, GetLPVOID());
       else FindKol = PoiskFractionalAgainQucly (ProcessHandle, EditIN->Text, GetLPVOID(), FindKol);
             break;}
case 3:{
       if (SearchForm->Caption == "Search options")
            FindKol = PoiskString(ProcessHandle, EditIN->Text,  GetLPVOID());
       else FindKol = PoiskStringAgainQucly (ProcessHandle, EditIN->Text,  GetLPVOID(), FindKol);
             break;}
 }
MainForm->LFound->Caption ="In table : " + IntToStr(FindKol);
MainForm->Animate->Active = FALSE;
}
//---------------------------------------------------------------------------
void __fastcall TSearchForm::CancelBTClick(TObject *Sender){
SearchForm->Close();
}
//---------------------------------------------------------------------------
