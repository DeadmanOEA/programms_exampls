//---------------------------------------------------------------------------

#include <fmx.h>
#pragma hdrstop

#include "fmu.h"
#include "uUtils.h"
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
void __fastcall Tfm::buPasswordClick(TObject *Sender)
{
	edPassword->Text = RandomStr(edLength->Value, ckLower->IsChecked, ckUpper->IsChecked, ckNumber->IsChecked, ckSpec->IsChecked, ckRus->IsChecked, ckEng->IsChecked);
}
//---------------------------------------------------------------------------
void __fastcall Tfm::buAboutClick(TObject *Sender)
{
	ShowMessage("Osokin Evgeniy");
}
//---------------------------------------------------------------------------
