//---------------------------------------------------------------------------

#ifndef fmuH
#define fmuH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <FMX.Controls.hpp>
#include <FMX.Forms.hpp>
#include <FMX.Controls.Presentation.hpp>
#include <FMX.Edit.hpp>
#include <FMX.EditBox.hpp>
#include <FMX.Layouts.hpp>
#include <FMX.NumberBox.hpp>
#include <FMX.StdCtrls.hpp>
#include <FMX.Types.hpp>
//---------------------------------------------------------------------------
class Tfm : public TForm
{
__published:	// IDE-managed Components
	TToolBar *ToolBar1;
	TLabel *Label1;
	TButton *buAbout;
	TLayout *ly;
	TEdit *edPassword;
	TButton *buPassword;
	TNumberBox *edLength;
	TLabel *Label2;
	TCheckBox *ckLower;
	TCheckBox *ckSpec;
	TCheckBox *ckNumber;
	TCheckBox *ckUpper;
	TCheckBox *ckRus;
	TCheckBox *ckEng;
	void __fastcall buPasswordClick(TObject *Sender);
	void __fastcall buAboutClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall Tfm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE Tfm *fm;
//---------------------------------------------------------------------------
#endif
