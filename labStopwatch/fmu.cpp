//---------------------------------------------------------------------------

#include <fmx.h>
#pragma hdrstop

#include "fmu.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.fmx"
TFm *Fm;
//---------------------------------------------------------------------------
__fastcall TFm::TFm(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TFm::buStartClick(TObject *Sender)
{
	FTimeStart = Now();
	tm->Enabled = true;
}
//---------------------------------------------------------------------------
void __fastcall TFm::buStopClick(TObject *Sender)
{
	tm->Enabled = false;
}
//---------------------------------------------------------------------------
void __fastcall TFm::tmTimer(TObject *Sender)
{
	UnicodeString x;
	DateTimeToString(x, L"h:nn:ss.zzz", Now() - FTimeStart);
	laTime->Text = x.Delete(x.Length()- 2, 2);
	//laTime->Text = TimeToStr(Now() - FTimeStart);
}
//---------------------------------------------------------------------------
void __fastcall TFm::CircleClick(TObject *Sender)
{
	me->Lines->Add(laTime->Text);
}
//---------------------------------------------------------------------------
void __fastcall TFm::ClearClick(TObject *Sender)
{
	me->Lines->Clear();
    tm->Enabled = false;
	laTime->Text = "0:00:00";
}
//---------------------------------------------------------------------------
void __fastcall TFm::PauseClick(TObject *Sender)
{
	tm->Enabled = !tm->Enabled;


}
//---------------------------------------------------------------------------


