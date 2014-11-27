//---------------------------------------------------------------------------

#ifndef MainFormUH
#define MainFormUH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include <Grids.hpp>
#include <Menus.hpp>
#include <ToolWin.hpp>
//---------------------------------------------------------------------------
class TMainForm : public TForm
{
__published:	// IDE-managed Components
        TBevel *Bevel1;
        TSpeedButton *AddBT;
        TSpeedButton *AddAllBT;
        TLabel *LFound;
        TLabel *LInTable;
        TStringGrid *SGnew;
        TCoolBar *CoolBar1;
        TSpeedButton *AboutBT;
        TSpeedButton *TerminateBT;
        TSpeedButton *SearchBT;
        TSpeedButton *SAgainBT;
        TSpeedButton *ProcessInfoBT;
        TSpeedButton *TFClearBT;
        TSpeedButton *TSClearBT;
        TSpeedButton *ProcessListBT;
        TListBox *AddressTable;
        TAnimate *Animate;
        TMainMenu *MainMenu1;
        TMenuItem *Progress1;
        TMenuItem *Search1;
        TMenuItem *Searchagain1;
        TMenuItem *N1;
        TMenuItem *Exit1;
        TMenuItem *Tables1;
        TMenuItem *Addtosecondtable1;
        TMenuItem *Addalltosecondtable1;
        TMenuItem *N2;
        TMenuItem *Deletefromtable1;
        TMenuItem *Firsttableclear1;
        TMenuItem *Secondtableclear1;
        TMenuItem *Process1;
        TMenuItem *ProcessList1;
        TMenuItem *Information1;
        TMenuItem *Terminate1;
        TMenuItem *About1;
        TBevel *Bevel2;
        TBevel *Bevel3;
        void __fastcall ProcessList1Click(TObject *Sender);
        void __fastcall FormCreate(TObject *Sender);
        void __fastcall Search1Click(TObject *Sender);
        void __fastcall Searchagain1Click(TObject *Sender);
        void __fastcall Exit1Click(TObject *Sender);
        void __fastcall Firsttableclear1Click(TObject *Sender);
        void __fastcall Addtosecondtable1Click(TObject *Sender);
        void __fastcall Addalltosecondtable1Click(TObject *Sender);
        void __fastcall Secondtableclear1Click(TObject *Sender);
        void __fastcall SGnewSetEditText(TObject *Sender, int ACol,
          int ARow, const AnsiString Value);
        void __fastcall Terminate1Click(TObject *Sender);
        void __fastcall Information1Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TMainForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TMainForm *MainForm;
//---------------------------------------------------------------------------
#endif
