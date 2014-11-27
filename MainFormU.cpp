//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "MainFormU.h"
#include "PoiskFormU.h"

#include "ProcessListU.h"
#include "ProcessInfoU.h"
#include "NewZU.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TMainForm *MainForm;
//---------------------------------------------------------------------------
__fastcall TMainForm::TMainForm(TComponent* Owner)
        : TForm(Owner){}
//---------------------------------------------------------------------------
void __fastcall TMainForm::ProcessList1Click(TObject *Sender){
Animate->Active = TRUE;
ProcessStructCreate();
Animate->Active = FALSE;}
//---------------------------------------------------------------------------
void __fastcall TMainForm::FormCreate(TObject *Sender){VirtualMemCreate();}
//---------------------------------------------------------------------------
void __fastcall TMainForm::Search1Click(TObject *Sender){
if ( GetProcessHandle() != 0 ){
     SearchForm->Caption = "Search options";
     SearchForm->RadioGroup->Enabled = TRUE;
     SearchForm->Show();}}
//---------------------------------------------------------------------------
void __fastcall TMainForm::Searchagain1Click(TObject *Sender){
if ( GetProcessHandle() != 0 ){
     SearchForm->Caption = "Search again options";
     SearchForm->RadioGroup->Enabled = FALSE;
     SearchForm->Show();}}
//---------------------------------------------------------------------------
void __fastcall TMainForm::Exit1Click(TObject *Sender){Close();}
//---------------------------------------------------------------------------
void __fastcall TMainForm::Firsttableclear1Click(TObject *Sender){AddressTable->Items->Clear();}
//---------------------------------------------------------------------------
void __fastcall TMainForm::Addtosecondtable1Click(TObject *Sender){
if (MainForm->AddressTable->ItemIndex>=0){
    CreateStruct(MainForm->AddressTable->ItemIndex);}}
//---------------------------------------------------------------------------
void __fastcall TMainForm::Addalltosecondtable1Click(TObject *Sender){ADDALL();}
//---------------------------------------------------------------------------
void __fastcall TMainForm::Secondtableclear1Click(TObject *Sender){
if ( MainForm->SGnew->Cells[0][0] != "" ){DestroyHeadline();}}
//---------------------------------------------------------------------------

void __fastcall TMainForm::SGnewSetEditText(TObject *Sender, int ACol,
      int ARow, const AnsiString Value){
if (ACol == 3 && Value.Length()>=1){WriteToMemory(ARow-1, Value);}
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::Terminate1Click(TObject *Sender){
if (MessageBox(NULL, "You really want to stop functioning(working) the process?", "Elaborate", MB_OKCANCEL) == IDOK)
    Terminate(GetProcessHandle());}
//---------------------------------------------------------------------------
void __fastcall TMainForm::Information1Click(TObject *Sender){ProcessInfoCreate(GetProcessHandle());}
//---------------------------------------------------------------------------

