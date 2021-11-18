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
//---------------------------------------------------------------------------
class Tfm : public TForm
{
__published:	// IDE-managed Components
	TToolBar *ToolBar;
	TButton *buRestart;
	TButton *buAbout;
	TGridPanelLayout *GPLTop;
	TGridPanelLayout *GPLBut;
	TButton *buYes;
	TButton *buNo;
	TRectangle *RecLeft;
	TLabel *laCorrect;
	TRectangle *RecRight;
	TLabel *laWrong;
	TLabel *Label1;
	TLabel *laCode;
	TButton *buEasy;
	TButton *buMedium;
	TButton *buHard;
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall buRestartClick(TObject *Sender);
	void __fastcall buYesClick(TObject *Sender);
	void __fastcall buNoClick(TObject *Sender);
	void __fastcall buAboutClick(TObject *Sender);
	void __fastcall buEasyClick(TObject *Sender);
	void __fastcall buMediumClick(TObject *Sender);
	void __fastcall buHardClick(TObject *Sender);
private:	// User declarations
	int FCountCorrect;
	int FCountWrong;
	int FLeverComplexity;
	bool FAnswerCorrect;
	void DoReset();
	void DoContinue();
	void DoAnswer (bool aValue);
	int FXir;
public:		// User declarations
	__fastcall Tfm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE Tfm *fm;
//---------------------------------------------------------------------------
#endif
