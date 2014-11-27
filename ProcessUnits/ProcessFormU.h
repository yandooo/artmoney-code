//---------------------------------------------------------------------------

#ifndef ProcessFormUH
#define ProcessFormUH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Grids.hpp>
//---------------------------------------------------------------------------
class TProcessForm : public TForm
{
__published:	// IDE-managed Components
        TStringGrid *SGProcess;
        void __fastcall FormCreate(TObject *Sender);
        void __fastcall SGProcessDblClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TProcessForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TProcessForm *ProcessForm;
//---------------------------------------------------------------------------
#endif
