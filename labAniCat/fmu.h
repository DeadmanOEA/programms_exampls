//---------------------------------------------------------------------------

#ifndef fmuH
#define fmuH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <FMX.Controls.hpp>
#include <FMX.Forms.hpp>
#include <FMX.Ani.hpp>
#include <FMX.Objects.hpp>
#include <FMX.Types.hpp>
#include <FMX.Controls.Presentation.hpp>
#include <FMX.StdCtrls.hpp>
//---------------------------------------------------------------------------
class Tfm : public TForm
{
__published:	// IDE-managed Components
	TImage *imF;
	TFloatAnimation *FAimF;
	TImage *inS;
	TFloatAnimation *FAimS;
	TLabel *la1;
	TLabel *la2;
	TFloatAnimation *FAla1;
	TFloatAnimation *FAla2;
	void __fastcall imFClick(TObject *Sender);
	void __fastcall inSClick(TObject *Sender);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall FormResize(TObject *Sender);
	void __fastcall FAimSProcess(TObject *Sender);
private:	// User declarations
	int FCountF;
	int FCountS;
public:		// User declarations
	__fastcall Tfm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE Tfm *fm;
//---------------------------------------------------------------------------
#endif
