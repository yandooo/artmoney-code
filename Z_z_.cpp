//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
//---------------------------------------------------------------------------
USEFORM("MainFormU.cpp", MainForm);
USEFORM("ProcessUnits\ProcessFormU.cpp", ProcessForm);
USEFORM("PoiskForm\PoiskFormU.cpp", SearchForm);
USEFORM("ProcessUnits\ProcessInfmU.cpp", FormInfm);
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
        try
        {
                 Application->Initialize();
                 Application->CreateForm(__classid(TMainForm), &MainForm);
                 Application->CreateForm(__classid(TProcessForm), &ProcessForm);
                 Application->CreateForm(__classid(TSearchForm), &SearchForm);
                 Application->CreateForm(__classid(TFormInfm), &FormInfm);
                 Application->Run();
        }
        catch (Exception &exception)
        {
                 Application->ShowException(&exception);
        }
        catch (...)
        {
                 try
                 {
                         throw Exception("");
                 }
                 catch (Exception &exception)
                 {
                         Application->ShowException(&exception);
                 }
        }
        return 0;
}
//---------------------------------------------------------------------------
