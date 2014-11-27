//---------------------------------------------------------------------------

#ifndef ProcessInfmUH
#define ProcessInfmUH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
//---------------------------------------------------------------------------
class TFormInfm : public TForm
{
__published:	// IDE-managed Components
        TMemo *Memo;
        TBitBtn *BitBtn1;
        void __fastcall BitBtn1Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TFormInfm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormInfm *FormInfm;
//---------------------------------------------------------------------------
#endif
