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
//---------------------------------------------------------------------------
class Tfm : public TForm
{
__published:	// IDE-managed Components
	TImage *Image1;
	TBitmapAnimation *BitmapAnimation1;
	TImage *im1;
	TBitmapListAnimation *BitmapListAnimation1;
	TFloatAnimation *fa1;
	void __fastcall FormResize(TObject *Sender);
	void __fastcall fa1Process(TObject *Sender);
private:	// User declarations
int StopValue;
public:		// User declarations
	__fastcall Tfm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE Tfm *fm;
//---------------------------------------------------------------------------
#endif
