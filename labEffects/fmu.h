//---------------------------------------------------------------------------

#ifndef fmuH
#define fmuH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <FMX.Controls.hpp>
#include <FMX.Forms.hpp>
#include <FMX.Ani.hpp>
#include <FMX.Controls.Presentation.hpp>
#include <FMX.Effects.hpp>
#include <FMX.Filter.Effects.hpp>
#include <FMX.Objects.hpp>
#include <FMX.StdCtrls.hpp>
#include <FMX.Types.hpp>
//---------------------------------------------------------------------------
class Tfm : public TForm
{
__published:	// IDE-managed Components
	TImage *Image1;
	TImage *Image2;
	TImage *Image3;
	TImage *Image4;
	TImage *Image5;
	TImage *Image6;
	TBlurEffect *BlurEffect1;
	TRippleEffect *RippleEffect1;
	TShadowEffect *ShadowEffect1;
	TGlowEffect *GlowEffect1;
	TBandsEffect *BandsEffect1;
	TWrapEffect *WrapEffect1;
	TButton *Button1;
	TFloatAnimation *FloatAnimation1;
	TEmbossEffect *EmbossEffect1;
	TButton *Button2;
	TButton *Button3;
	TGlowEffect *GlowEffect2;
	TPaperSketchEffect *PaperSketchEffect1;
private:	// User declarations
public:		// User declarations
	__fastcall Tfm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE Tfm *fm;
//---------------------------------------------------------------------------
#endif
