//---------------------------------------------------------------------------

#include <fmx.h>
#pragma hdrstop

#include "fmu.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.fmx"
Tfm *fm;
//---------------------------------------------------------------------------
__fastcall Tfm::Tfm(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall Tfm::B30Click(TObject *Sender)
{
	im->RotationAngle += 30;
	trBar->Value = im->RotationAngle;
	la->Text = im->RotationAngle;
}
//---------------------------------------------------------------------------
void __fastcall Tfm::B60Click(TObject *Sender)
{
	im->RotationAngle += 60;
	trBar->Value = im->RotationAngle;
	la->Text = im->RotationAngle;
}
//---------------------------------------------------------------------------
void __fastcall Tfm::B90Click(TObject *Sender)
{
	im->RotationAngle += 90;
	trBar->Value = im->RotationAngle;
	la->Text = im->RotationAngle;
}
//---------------------------------------------------------------------------
void __fastcall Tfm::B180Click(TObject *Sender)
{
	im->RotationAngle += 180;
	trBar->Value = im->RotationAngle;
	la->Text = im->RotationAngle;
}
//---------------------------------------------------------------------------
void __fastcall Tfm::Bm10Click(TObject *Sender)
{
	im->RotationAngle -= 10;
	trBar->Value = im->RotationAngle;
	la->Text = im->RotationAngle;
}
//---------------------------------------------------------------------------
void __fastcall Tfm::Bp10Click(TObject *Sender)
{
	im->RotationAngle += 10;
	trBar->Value = im->RotationAngle;
	la->Text = im->RotationAngle;
}
//---------------------------------------------------------------------------
void __fastcall Tfm::trBarChange(TObject *Sender)
{
	im->RotationAngle = trBar->Value;
	la->Text = trBar->Value;

}
//---------------------------------------------------------------------------
void __fastcall Tfm::B0Click(TObject *Sender)
{

	trBar->Value = 0;

}
//---------------------------------------------------------------------------
void __fastcall Tfm::BHClick(TObject *Sender)
{
	im->Bitmap->FlipHorizontal();
}
//---------------------------------------------------------------------------
void __fastcall Tfm::BVClick(TObject *Sender)
{
	im->Bitmap->FlipVertical();
}
//---------------------------------------------------------------------------
void __fastcall Tfm::trbOpacityChange(TObject *Sender)
{
    im->Opacity = trbOpacity->Value;
}
//---------------------------------------------------------------------------
void __fastcall Tfm::trSizeChange(TObject *Sender)
{
	im->Scale->X = trSize->Value;
	im->Scale->Y = trSize->Value;
}
//---------------------------------------------------------------------------
