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
void __fastcall Tfm::imFClick(TObject *Sender)
{
	FCountF++;
	la1->Text = "First = " + IntToStr(FCountF);
	FAla1->Start();
}
//---------------------------------------------------------------------------
void __fastcall Tfm::inSClick(TObject *Sender)
{
	FCountS++;
	la2->Text = "Second = " + IntToStr(FCountS);
    FAla2->Start();
}
//---------------------------------------------------------------------------
void __fastcall Tfm::FormCreate(TObject *Sender)
{
	FCountF = 0;
	FCountS = 0;
}
//---------------------------------------------------------------------------
void __fastcall Tfm::FormResize(TObject *Sender)
{
	 FAimF->StopValue = this->Width - imF->Width;
	 FAimS->StopValue = this->Width - inS->Width;
}
//---------------------------------------------------------------------------
void __fastcall Tfm::FAimSProcess(TObject *Sender)
{
	if ((imF->Position->X==FAimF->StopValue)
	|| (imF->Position->X==FAimF->StartValue)) {
	  imF->Bitmap->FlipHorizontal();
	}

	if ((inS->Position->X==FAimS->StopValue)
	|| (inS->Position->X==FAimS->StartValue)) {
	  inS->Bitmap->FlipHorizontal();
	}

}
//---------------------------------------------------------------------------

