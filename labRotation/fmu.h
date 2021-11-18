//---------------------------------------------------------------------------

#ifndef fmuH
#define fmuH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <FMX.Controls.hpp>
#include <FMX.Forms.hpp>
#include <FMX.Controls.Presentation.hpp>
#include <FMX.Objects.hpp>
#include <FMX.StdCtrls.hpp>
#include <FMX.Types.hpp>
//---------------------------------------------------------------------------
class Tfm : public TForm
{
__published:	// IDE-managed Components
	TButton *B30;
	TButton *B60;
	TButton *B90;
	TButton *B180;
	TButton *Bm10;
	TButton *Bp10;
	TImage *im;
	TTrackBar *trBar;
	TLabel *la;
	TButton *B0;
	TButton *BH;
	TButton *BV;
	TTrackBar *trbOpacity;
	TTrackBar *trSize;
	void __fastcall B30Click(TObject *Sender);
	void __fastcall B60Click(TObject *Sender);
	void __fastcall B90Click(TObject *Sender);
	void __fastcall B180Click(TObject *Sender);
	void __fastcall Bm10Click(TObject *Sender);
	void __fastcall Bp10Click(TObject *Sender);
	void __fastcall trBarChange(TObject *Sender);
	void __fastcall B0Click(TObject *Sender);
	void __fastcall BHClick(TObject *Sender);
	void __fastcall BVClick(TObject *Sender);
	void __fastcall trbOpacityChange(TObject *Sender);
	void __fastcall trSizeChange(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall Tfm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE Tfm *fm;
//---------------------------------------------------------------------------
#endif
