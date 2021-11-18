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
#include <FMX.Edit.hpp>
#include <FMX.Layouts.hpp>
#include <FMX.Objects.hpp>
//---------------------------------------------------------------------------
class Tfm : public TForm
{
__published:	// IDE-managed Components
	TToolBar *ToolBar1;
	TLabel *Label1;
	TButton *buAbout;
	TTabControl *tc;
	TButton *buCalc;
	TTabItem *tiBegin;
	TTabItem *tiRes;
	TEdit *edVal;
	TTabItem *tiSettings;
	TTabItem *tiMenu;
	TImage *Image1;
	TGridPanelLayout *GridPanelLayout2;
	TGridPanelLayout *GridPanelLayout1;
	TButton *buStart;
	TButton *buSettings;
	TLabel *Label2;
	TLabel *Label3;
	TEdit *edDown;
	TEdit *edUp;
	TLabel *laFirst;
	TLabel *laSecond;
	TButton *buBack;
	TButton *Button1;
	TButton *Button2;
	TLabel *Label4;
	TCheckBox *ckSq;
	TCheckBox *ckTrap;
	TLabel *Label5;
	TEdit *edDelta;
	TStyleBook *StyleBook1;
	TStyleBook *StyleBook2;
	TButton *Button3;
	TButton *Button4;
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall buSettingsClick(TObject *Sender);
	void __fastcall buCalcClick(TObject *Sender);
	void __fastcall buBackClick(TObject *Sender);
	void __fastcall buAboutClick(TObject *Sender);
	void __fastcall buStartClick(TObject *Sender);
	void __fastcall ThemeClick(TObject *Sender);
private:	// User declarations
	String ValStr;
	long double up;
	long double down;
	long double delta;
    bool MetCheck();
public:		// User declarations
	__fastcall Tfm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE Tfm *fm;
//---------------------------------------------------------------------------
#endif
