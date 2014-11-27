//---------------------------------------------------------------------------

#ifndef PoiskFormUH
#define PoiskFormUH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TSearchForm : public TForm
{
__published:	// IDE-managed Components
        TLabel *Label1;
        TBevel *Bevel2;
        TRadioGroup *RadioGroup;
        TBitBtn *GoBt;
        TBitBtn *CancelBT;
        TEdit *EditIN;
        void __fastcall GoBtClick(TObject *Sender);
        void __fastcall CancelBTClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TSearchForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TSearchForm *SearchForm;
//---------------------------------------------------------------------------
#endif
