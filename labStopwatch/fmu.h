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
//---------------------------------------------------------------------------
class TFm : public TForm
{
__published:	// IDE-managed Components
	TButton *buStart;
	TButton *buStop;
	TLabel *laTime;
	TTimer *tm;
	TMemo *me;
	TButton *Circle;
	TButton *Clear;
	TButton *Pause;
	void __fastcall buStartClick(TObject *Sender);
	void __fastcall buStopClick(TObject *Sender);
	void __fastcall tmTimer(TObject *Sender);
	void __fastcall CircleClick(TObject *Sender);
	void __fastcall ClearClick(TObject *Sender);
	void __fastcall PauseClick(TObject *Sender);
private:	// User declarations
	TDateTime FTimeStart;
public:		// User declarations
	__fastcall TFm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFm *Fm;
//---------------------------------------------------------------------------
#endif
