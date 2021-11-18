//---------------------------------------------------------------------------

#ifndef fmuH
#define fmuH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <FMX.Controls.hpp>
#include <FMX.Forms.hpp>
#include <FMX.Controls.Presentation.hpp>
#include <FMX.Layouts.hpp>
#include <FMX.StdCtrls.hpp>
#include <FMX.Types.hpp>
#include <FMX.Objects.hpp>
#include <FMX.TabControl.hpp>
#include <FMX.Memo.hpp>
#include <FMX.ScrollBox.hpp>
#include <FMX.Ani.hpp>
//---------------------------------------------------------------------------
class Tfm : public TForm
{
__published:	// IDE-managed Components
	TLayout *Layout1;
	TButton *bAbout;
	TLabel *laName;
	TTabControl *tc;
	TTabItem *tiMenu;
	TTabItem *tiFirst;
	TTabItem *tiSecond;
	TTabItem *TabItem4;
	TTabItem *tiResult;
	TButton *buStart;
	TImage *Image1;
	TScrollBox *ScrollBox1;
	TLabel *Label1;
	TButton *Button1;
	TButton *Button2;
	TButton *Button3;
	TButton *Button4;
	TButton *Button5;
	TScrollBox *ScrollBox2;
	TLabel *Label2;
	TButton *Button6;
	TButton *Button7;
	TButton *Button8;
	TButton *Button9;
	TButton *Button10;
	TScrollBox *ScrollBox3;
	TLabel *Label3;
	TButton *Button11;
	TButton *Button12;
	TButton *Button13;
	TButton *Button14;
	TButton *Button15;
	TButton *buRestart;
	TMemo *me;
	TLabel *laWrong;
	TLabel *laCorrect;
	TProgressBar *pb;
	TLabel *laNum;
	TImage *im1;
	TImage *im2;
	TStyleBook *StyleBook1;
	TTabItem *TabItem1;
	TScrollBox *ScrollBox4;
	TLabel *Label4;
	TButton *Button16;
	TButton *Button17;
	TButton *Button18;
	TButton *Button19;
	TButton *Button20;
	TFloatAnimation *fa1;
	TFloatAnimation *fa2;
	TStyleBook *StyleBook2;
	TButton *buCT;
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall buStartClick(TObject *Sender);
	void __fastcall ButtonAllClick(TObject *Sender);
	void __fastcall buRestartClick(TObject *Sender);
	void __fastcall bAboutClick(TObject *Sender);
	void __fastcall tcChange(TObject *Sender);
	void __fastcall buCTClick(TObject *Sender);
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
