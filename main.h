//---------------------------------------------------------------------------

#ifndef mainH
#define mainH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>

#include<tlhelp32.h>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:
private:
public:
	__fastcall TForm1(TComponent* Owner);


	// Console
	HANDLE handle;
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
