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
void Tfm::SelectionAll(TObject *Sender)
{
	if (FSel != NULL) {
		FSel->HideSelection = true;
	}
	FSel = dynamic_cast<TSelection*>(Sender);
	if (FSel != NULL) {
        FSel->HideSelection = false;
	}


	//tbImage->Visible = (FSel != NULL);
	tbOptions->Visible = (FSel != NULL);
	//tbRect->Visible = (FSel != NULL);
    if (tbOptions->Visible) {
		trRotation->Value = FSel->RotationAngle;
	}

	tbImage->Visible = (FSel != NULL) && (dynamic_cast<TGlyph*>(FSel->Controls->Items[0]));
	tbRect->Visible = (FSel != NULL) && (dynamic_cast<TRectangle*>(FSel->Controls->Items[0]));
	
	if (tbRect->Visible) {
		ComboColorBoxRect->Color = ((TRectangle*)FSel->Controls->Items[0])->Fill->Color;
		trRectRadius->Value = ((TRectangle*)FSel->Controls->Items[0])->XRadius;

	}
	tbText->Visible = (FSel != NULL) && (dynamic_cast<TText*>(FSel->Controls->Items[0]));
	if (tbText->Visible) {
		ComboColorBoxText->Color = ((TText*)FSel->Controls->Items[0])->TextSettings->FontColor;
		tbTextSize->Value = ((TText*)FSel->Controls->Items[0])->Font->Size;

	}

}
//---------------------------------------------------------------------------
void __fastcall Tfm::SelectionAllMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
          float X, float Y)
{
	SelectionAll(Sender);
}
//---------------------------------------------------------------------------

void __fastcall Tfm::FormCreate(TObject *Sender)
{
    Randomize();
	FSel = NULL;
	SelectionAll(ly);
}
//---------------------------------------------------------------------------

void __fastcall Tfm::buBringToFrontClick(TObject *Sender)
{
	FSel->BringToFront();
	FSel->Repaint();
}
//---------------------------------------------------------------------------

void __fastcall Tfm::buSendToBackClick(TObject *Sender)
{
	FSel->SendToBack();
	FSel->Repaint();
}
//---------------------------------------------------------------------------

void __fastcall Tfm::trRotationChange(TObject *Sender)
{
	FSel->RotationAngle = trRotation->Value;
}
//---------------------------------------------------------------------------

void __fastcall Tfm::buDelClick(TObject *Sender)
{
	FSel->DisposeOf();
	FSel = NULL;
    SelectionAll(ly);
}
//---------------------------------------------------------------------------

void __fastcall Tfm::buImagePrevClick(TObject *Sender)
{
	TGlyph *x = (TGlyph*)FSel->Controls->Items[0];
	x->ImageIndex = (x->ImageIndex <= 0) ? 0 : x->ImageIndex - 1;
}
//---------------------------------------------------------------------------


void __fastcall Tfm::buImageSelectClick(TObject *Sender)
{
	//
}
//---------------------------------------------------------------------------

void __fastcall Tfm::buRNDClick(TObject *Sender)
{
	//
}
//---------------------------------------------------------------------------

void __fastcall Tfm::buImageNextClick(TObject *Sender)
{
    TGlyph *x = (TGlyph*)FSel->Controls->Items[0];
	x->ImageIndex = (x->ImageIndex >= il->Count-1) ? 0 : x->ImageIndex + 1;
}
//---------------------------------------------------------------------------

void __fastcall Tfm::buNewImageClick(TObject *Sender)
{
	TSelection *x = new TSelection(ly);
	x->Parent = ly;
	x->GripSize = 8;
	x->Width = 50 + Random(100);
	x->Height = 50 + Random(100);
	x->Position->X = Random(ly->Width - x->Width);
	x->Position->Y = Random(ly->Height - x->Height);
	x->RotationAngle = Random(100)-50;
	x->OnMouseDown = SelectionAllMouseDown;
	TGlyph *xGlyph = new TGlyph(x);
	xGlyph->Parent = x;
	xGlyph->Align = TAlignLayout::Client;
	xGlyph->Images = il;
	xGlyph->ImageIndex = Random(il->Count);

	SelectionAll(x);
}
//---------------------------------------------------------------------------

void __fastcall Tfm::buClearClick(TObject *Sender)
{
	SelectionAll(ly);
	for (int i = ly->ControlsCount-1; i >= 0; i--) {
		if (dynamic_cast<TSelection*>(ly->Controls->Items[i])) {
        	ly->RemoveObject(i);    
		}	
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfm::ComboColorBoxRectChange(TObject *Sender)
{
	TRectangle *x = (TRectangle*)FSel->Controls->Items[0];
	x->Fill->Color = ComboColorBoxRect->Color;	
}
//---------------------------------------------------------------------------

void __fastcall Tfm::trRectRadiusChange(TObject *Sender)
{
	TRectangle *x = (TRectangle*)FSel->Controls->Items[0];
	x->XRadius = trRectRadius->Value;
	x->YRadius = x->XRadius;	
}
//---------------------------------------------------------------------------

void __fastcall Tfm::buNewRectClick(TObject *Sender)
{
	TSelection *x = new TSelection(ly);
	x->Parent = ly;
	x->GripSize = 8;
	x->Width = 50 + Random(100);
	x->Height = 50 + Random(100);
	x->Position->X = Random(ly->Width - x->Width);
	x->Position->Y = Random(ly->Height - x->Height);
	x->RotationAngle = Random(100)-50;
	x->OnMouseDown = SelectionAllMouseDown;
	TRectangle *xRectangle = new TRectangle(x);
	xRectangle->Parent = x;
	xRectangle->Align = TAlignLayout::Client;
	xRectangle->HitTest = false;
	xRectangle->XRadius = Random(50);
	xRectangle->YRadius = xRectangle->XRadius;
	xRectangle->Fill->Color = TAlphaColorF::Create(Random(256),Random(256),Random(256)).ToAlphaColor();

	SelectionAll(x);	
}
//---------------------------------------------------------------------------

void __fastcall Tfm::buNewTextClick(TObject *Sender)
{
	TSelection *x = new TSelection(ly);
	x->Parent = ly;
	x->GripSize = 8;
	x->Width = 50 + Random(100);
	x->Height = 50 + Random(100);
	x->Position->X = Random(ly->Width - x->Width);
	x->Position->Y = Random(ly->Height - x->Height);
	x->RotationAngle = Random(100)-50;
	x->OnMouseDown = SelectionAllMouseDown;
	TText *xText = new TText(x);
	xText->Parent = x;
	xText->Align = TAlignLayout::Client;
	
	xText->Text = Random(100);
	xText->Font->Size = 15 + Random(30);
	xText->TextSettings->FontColor = TAlphaColorF::Create(Random(256),Random(256),Random(256)).ToAlphaColor();
	xText->HitTest = false;

	SelectionAll(x);	
}
//---------------------------------------------------------------------------

void __fastcall Tfm::ComboColorBoxTextChange(TObject *Sender)
{
	TText *x = (TText*)FSel->Controls->Items[0];
   	x->TextSettings->FontColor = ComboColorBoxText->Color;
}
//---------------------------------------------------------------------------

void __fastcall Tfm::tbTextSizeChange(TObject *Sender)
{
	TText *x = (TText*)FSel->Controls->Items[0];
	x->Font->Size = tbTextSize->Value;
		
}
//---------------------------------------------------------------------------

