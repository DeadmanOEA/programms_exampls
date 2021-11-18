//---------------------------------------------------------------------------

#ifndef fmuH
#define fmuH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <FMX.Controls.hpp>
#include <FMX.Forms.hpp>
#include <FMX.Controls.Presentation.hpp>
#include <FMX.StdCtrls.hpp>
#include <FMX.TabControl.hpp>
#include <FMX.Types.hpp>
#include <FMX.Layouts.hpp>
#include <FMX.Memo.hpp>
#include <FMX.ScrollBox.hpp>
#include <FMX.Edit.hpp>
//---------------------------------------------------------------------------
class Tfm : public TForm
{
__published:	// IDE-managed Components
	TTabControl *tc;
	TTabItem *tiMainMenu;
	TTabItem *tiChooseGame;
	TTabItem *tiGame;
	TTabItem *tiResult;
	TTabItem *tiSettings;
	TTabItem *tiTheme;
	TTabItem *tiAbout;
	TLabel *Label2;
	TButton *buStart;
	TButton *buSettings;
	TButton *Button2;
	TButton *buTheme;
	TLabel *Label1;
	TButton *buAbout;
	TLabel *Label3;
	TLabel *Label4;
	TLabel *Label5;
	TButton *Button1;
	TLabel *Label6;
	TButton *buSimple;
	TButton *buMedium;
	TButton *buHard;
	TButton *buBack1;
	TButton *Button3;
	TButton *Button4;
	TButton *Button5;
	TGridPanelLayout *GPLTable;
	TGridPanelLayout *GPLFunc;
	TGridPanelLayout *GridPanelLayout1;
	TGridPanelLayout *GridPanelLayout2;
	TButton *buRestart;
	TButton *buMenu;
	TButton *bu1S;
	TButton *bu2S;
	TButton *bu3S;
	TButton *bu4S;
	TButton *bu5S;
	TButton *bu6S;
	TButton *bu7S;
	TButton *bu8S;
	TButton *bu9S;
	TButton *bu1B;
	TButton *bu2B;
	TButton *bu3B;
	TButton *bu4B;
	TButton *bu5B;
	TButton *bu6B;
	TButton *bu7B;
	TButton *bu8B;
	TButton *bu9B;
	TGridPanelLayout *GridPanelLayout3;
	TGridPanelLayout *GridPanelLayout4;
	TGridPanelLayout *GridPanelLayout5;
	TGridPanelLayout *GridPanelLayout6;
	TGridPanelLayout *GridPanelLayout7;
	TGridPanelLayout *GridPanelLayout8;
	TGridPanelLayout *GridPanelLayout9;
	TGridPanelLayout *GridPanelLayout10;
	TGridPanelLayout *GridPanelLayout11;
	TMemo *me11;
	TMemo *me12;
	TMemo *me13;
	TMemo *me21;
	TMemo *me22;
	TMemo *me23;
	TMemo *me31;
	TMemo *me32;
	TMemo *me33;
	TMemo *me14;
	TMemo *me15;
	TMemo *me16;
	TMemo *me24;
	TMemo *me25;
	TMemo *me26;
	TMemo *me34;
	TMemo *me35;
	TMemo *me36;
	TMemo *me17;
	TMemo *me18;
	TMemo *me19;
	TMemo *me27;
	TMemo *me28;
	TMemo *me29;
	TMemo *me37;
	TMemo *me38;
	TMemo *me39;
	TMemo *me41;
	TMemo *me42;
	TMemo *me43;
	TMemo *me51;
	TMemo *me52;
	TMemo *me53;
	TMemo *me61;
	TMemo *me62;
	TMemo *me63;
	TMemo *me44;
	TMemo *me45;
	TMemo *me46;
	TMemo *me54;
	TMemo *me55;
	TMemo *me56;
	TMemo *me64;
	TMemo *me65;
	TMemo *me66;
	TMemo *me47;
	TMemo *me48;
	TMemo *me49;
	TMemo *me57;
	TMemo *me58;
	TMemo *me59;
	TMemo *me67;
	TMemo *me68;
	TMemo *me69;
	TMemo *me71;
	TMemo *me72;
	TMemo *me73;
	TMemo *me81;
	TMemo *me82;
	TMemo *me83;
	TMemo *me91;
	TMemo *me92;
	TMemo *me93;
	TMemo *me74;
	TMemo *me75;
	TMemo *me76;
	TMemo *me84;
	TMemo *me85;
	TMemo *me86;
	TMemo *me94;
	TMemo *me95;
	TMemo *me96;
	TMemo *me77;
	TMemo *me78;
	TMemo *me79;
	TMemo *me87;
	TMemo *me88;
	TMemo *me89;
	TMemo *me97;
	TMemo *me98;
	TMemo *me99;
	TLabel *Label8;
	TLabel *laResInf;
	TLabel *laTimeRes;
	TGridPanelLayout *GridPanelLayout12;
	TButton *buResRestart;
	TButton *buMenuMain;
	TLabel *Label7;
	TTimer *tm;
	TLabel *laTime;
	TButton *Button6;
	TStyleBook *StyleBook1;
	TStyleBook *StyleBook2;
	void __fastcall buAllStartClick(TObject *Sender);
	void __fastcall buSettingsClick(TObject *Sender);
	void __fastcall buComplexityClick(TObject *Sender);
	void __fastcall buThemeClick(TObject *Sender);
	void __fastcall buAboutClick(TObject *Sender);
	void __fastcall ThemeClick(TObject *Sender);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall buBackClick(TObject *Sender);
	void __fastcall buAllSClick(TObject *Sender);
	void __fastcall buAllBClick(TObject *Sender);
	void __fastcall buMenuClick(TObject *Sender);
	void __fastcall buRestartClick(TObject *Sender);
	void __fastcall meTableAllClick(TObject *Sender);
	void __fastcall buResRestartClick(TObject *Sender);
	void __fastcall tmTimer(TObject *Sender);
private:	// User declarations
	bool bTimerOn;
	int iComplexity;
	TDateTime FTimeStart;
	UnicodeString xTime;
//---------------------------------------------------------------------------
	int iStartNum[9][9]; //хранит видимое пользователю поле
	int iFullNum[9][9]; //хранит полностью заполненое поле
	int iResultNum[9][9];
	bool bEndGame;
	int iComplexityConst;

	int bigtxt;
	int smalltxt;

	int meXnow;
	int meYnow;
	bool choseitem;

	String i1Num[9][9];
	String i2Num[9][9];
	String i3Num[9][9];
	String i4Num[9][9];
	String i5Num[9][9];
	String i6Num[9][9];
	String i7Num[9][9];
	String i8Num[9][9];
	String i9Num[9][9];
//---------------------------------------------------------------------------
	void Start(int dif);
	void WorkWithTable(int i, int j, String str, bool onlyRead, int txtsize, int color);
	void FillTable(int txtsize);
public:		// User declarations
	__fastcall Tfm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE Tfm *fm;
//---------------------------------------------------------------------------
#endif
