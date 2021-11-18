//---------------------------------------------------------------------------

#ifndef fmuH
#define fmuH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <FMX.Controls.hpp>
#include <FMX.Forms.hpp>
#include <FMX.Controls.Presentation.hpp>
#include <FMX.StdCtrls.hpp>
#include <FMX.Types.hpp>
#include <FMX.Memo.hpp>
#include <FMX.ScrollBox.hpp>
#include <FMX.TabControl.hpp>
//---------------------------------------------------------------------------
class Tfm : public TForm
{
__published:	// IDE-managed Components
	TToolBar *ToolBar1;
	TButton *buMinus;
	TButton *buPlus;
	TButton *buAbout;
	TLabel *Label1;
	TTabControl *tc;
	TTabItem *tb1;
	TTabItem *TabItem2;
	TTabItem *TabItem3;
	TMemo *meFull;
	TMemo *me1;
	TMemo *me2;
	TTabItem *TabItem1;
	TTabItem *TabItem4;
	TMemo *me3;
	TMemo *me4;
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall buPlusClick(TObject *Sender);
	void __fastcall buMinusClick(TObject *Sender);
	void __fastcall buAboutClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall Tfm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE Tfm *fm;
//---------------------------------------------------------------------------
#endif
