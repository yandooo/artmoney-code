//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "ProcessFormU.h"
#include "MainFormU.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TProcessForm *ProcessForm;
//---------------------------------------------------------------------------
__fastcall TProcessForm::TProcessForm(TComponent* Owner)
        : TForm(Owner){}
//---------------------------------------------------------------------------
void __fastcall TProcessForm::FormCreate(TObject *Sender){
SGProcess->Cells[0][0] = "Module.exe";
SGProcess->Cells[1][0] = "Process ID";
SGProcess->Cells[2][0] = "Window title";}
//---------------------------------------------------------------------------
void __fastcall TProcessForm::SGProcessDblClick(TObject *Sender){
MainForm->Caption ="Z_z_ - " + ProcessForm->SGProcess->Cells[0][ProcessForm->SGProcess->Row];
ProcessForm->Close();}
//---------------------------------------------------------------------------
