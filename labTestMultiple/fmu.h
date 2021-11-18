//---------------------------------------------------------------------------

#ifndef fmuH
#define fmuH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <FMX.Controls.hpp>
#include <FMX.Forms.hpp>
#include <FMX.Controls.Presentation.hpp>
#include <FMX.Layouts.hpp>
#include <FMX.Memo.hpp>
#include <FMX.Objects.hpp>
#include <FMX.ScrollBox.hpp>
#include <FMX.StdCtrls.hpp>
#include <FMX.TabControl.hpp>
#include <FMX.Types.hpp>
//---------------------------------------------------------------------------
class Tfm : public TForm
{
__published:	// IDE-managed Components
	TToolBar *ToolBar1;
	TLabel *Label1;
	TButton *Button1;
	TLabel *laNum;
	TTabControl *tc;
	TTabItem *tiMenu;
	TTabItem *tiFirst;
	TTabItem *tiThird;
	TTabItem *tiResult;
	TButton *buStart;
	TImage *Image1;
	TCheckBox *CheckBox1;
	TCheckBox *CheckBox2;
	TCheckBox *CheckBox3;
	TCheckBox *CheckBox4;
	TCheckBox *CheckBox5;
	TLabel *Label2;
	TButton *buNext1;
	TTabItem *tiSecond;
	TScrollBox *ScrollBox1;
	TScrollBox *ScrollBox2;
	TButton *Button2;
	TCheckBox *CheckBox6;
	TCheckBox *CheckBox7;
	TCheckBox *CheckBox8;
	TCheckBox *CheckBox9;
	TCheckBox *CheckBox10;
	TLabel *Label3;
	TScrollBox *ScrollBox3;
	TButton *Button3;
	TCheckBox *CheckBox11;
	TCheckBox *CheckBox12;
	TCheckBox *CheckBox13;
	TCheckBox *CheckBox14;
	TCheckBox *CheckBox15;
	TLabel *Label4;
	TLabel *laRight;
	TLabel *laNone;
	TMemo *me;
	TImage *imR;
	TImage *imN;
	TProgressBar *pb;
	TButton *buRes;
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall buNextAllClick(TObject *Sender);
	void __fastcall tcChange(TObject *Sender);
	void __fastcall buStartClick(TObject *Sender);
	void __fastcall buResClick(TObject *Sender);
	void __fastcall Button1Click(TObject *Sender);
private:	// User declarations
	int FCountCorrect;
	int FCountWrong;
public:		// User declarations
	__fastcall Tfm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE Tfm *fm;
//---------------------------------------------------------------------------
#endif
