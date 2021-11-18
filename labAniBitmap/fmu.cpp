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
void __fastcall Tfm::FormResize(TObject *Sender)
{
	fa1->StopValue = this->Width - im1->Width;
}
//---------------------------------------------------------------------------

void __fastcall Tfm::fa1Process(TObject *Sender)
{
	if ((im1->Position->X==fa1->StopValue)
	|| (im1->Position->X==fa1->StartValue)) {
	  im1->Bitmap->FlipVertical();
	}
}
//---------------------------------------------------------------------------

