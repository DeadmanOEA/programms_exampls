//---------------------------------------------------------------------------

#ifndef fmuH
#define fmuH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <FMX.Controls.hpp>
#include <FMX.Forms.hpp>
#include <FMX.Controls.Presentation.hpp>
#include <FMX.ImgList.hpp>
#include <FMX.Layouts.hpp>
#include <FMX.StdCtrls.hpp>
#include <FMX.Types.hpp>
#include <System.ImageList.hpp>
#include <FMX.Objects.hpp>
#include <FMX.Colors.hpp>
//---------------------------------------------------------------------------
class Tfm : public TForm
{
__published:	// IDE-managed Components
	TToolBar *tb;
	TButton *buNewImage;
	TButton *buNewRect;
	TButton *buClear;
	TButton *buAbout;
	TToolBar *tbOptions;
	TButton *buBringToFront;
	TButton *buSendToBack;
	TButton *buDel;
	TTrackBar *trRotation;
	TToolBar *tbImage;
	TButton *buImagePrev;
	TButton *buImageNext;
	TButton *buImageSelect;
	TButton *buRND;
	TImageList *il;
	TLayout *ly;
	TGlyph *Glyph1;
	TGlyph *Glyph2;
	TSelection *Selection1;
	TSelection *Selection2;
	TRectangle *Rectangle1;
	TSelection *Selection3;
	TToolBar *tbRect;
	TComboColorBox *ComboColorBoxRect;
	TTrackBar *trRectRadius;
	TSelection *Selection4;
	TButton *buNewText;
	TText *Text1;
	TToolBar *tbText;
	TComboColorBox *ComboColorBoxText;
	TTrackBar *tbTextSize;
	void __fastcall SelectionAllMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
          float X, float Y);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall buBringToFrontClick(TObject *Sender);
	void __fastcall buSendToBackClick(TObject *Sender);
	void __fastcall trRotationChange(TObject *Sender);
	void __fastcall buDelClick(TObject *Sender);
	void __fastcall buImagePrevClick(TObject *Sender);
	void __fastcall buImageSelectClick(TObject *Sender);
	void __fastcall buRNDClick(TObject *Sender);
	void __fastcall buImageNextClick(TObject *Sender);
	void __fastcall buNewImageClick(TObject *Sender);
	void __fastcall buClearClick(TObject *Sender);
	void __fastcall ComboColorBoxRectChange(TObject *Sender);
	void __fastcall trRectRadiusChange(TObject *Sender);
	void __fastcall buNewRectClick(TObject *Sender);
	void __fastcall buNewTextClick(TObject *Sender);
	void __fastcall ComboColorBoxTextChange(TObject *Sender);
	void __fastcall tbTextSizeChange(TObject *Sender);
private:	// User declarations
	TSelection *FSel;
    void SelectionAll (TObject *Sender);
public:		// User declarations
	__fastcall Tfm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE Tfm *fm;
//---------------------------------------------------------------------------
#endif
