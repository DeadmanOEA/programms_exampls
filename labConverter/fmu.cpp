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
void __fastcall Tfm::edTimeAllKeyUp(TObject *Sender, WORD &Key, System::WideChar &KeyChar,
		  TShiftState Shift)
{
	long double x;
	long double xSec;

	x = StrToFloatDef(((TEdit*)Sender)->Text, 0);

	switch (((TEdit*)Sender)->Tag) {
	case 0: xSec = x / 1000; break;
	case 1: xSec = x; break;
	case 2: xSec = x * 60; break;
	case 3: xSec = x * 60 * 60; break;
	case 4: xSec = x * 60 * 60 * 24; break;
	case 5: xSec = x * 60 * 60 * 24 * 365; break;
	}

	edMs->Text = FloatToStr(xSec * 1000);
	edSec->Text = FloatToStr(xSec);
	edMinutes->Text = FloatToStr(xSec / 60);
	edHours->Text = FloatToStr(xSec / 60 / 60);
	edDays->Text = FloatToStr(xSec / 60 / 60 / 24);
	edYears->Text = FloatToStr(xSec / 60 / 60 / 24 / 365);
}
//---------------------------------------------------------------------------
void __fastcall Tfm::FormCreate(TObject *Sender)
{
	tc->TabPosition = TTabPosition::None;
	tc->ActiveTab = tiMenu;
}
//---------------------------------------------------------------------------
void __fastcall Tfm::tcChange(TObject *Sender)
{
	buBack->Visible = (tc->ActiveTab != tiMenu);
}
//---------------------------------------------------------------------------
void __fastcall Tfm::buTimeClick(TObject *Sender)
{
	tc->GotoVisibleTab(tiTime->Index);
}
//---------------------------------------------------------------------------
void __fastcall Tfm::buDistanceClick(TObject *Sender)
{
	tc->GotoVisibleTab(tiDistance->Index);
}
//---------------------------------------------------------------------------
void __fastcall Tfm::buQuantitiesInfoClick(TObject *Sender)
{
	tc->GotoVisibleTab(tiQl->Index);
}
//---------------------------------------------------------------------------
void __fastcall Tfm::buTemperatureClick(TObject *Sender)
{
	tc->GotoVisibleTab(tiTemperature->Index);
}
//---------------------------------------------------------------------------
void __fastcall Tfm::edDistanceAllKeyUp(TObject *Sender, WORD &Key, System::WideChar &KeyChar,
          TShiftState Shift)
{
	long double x;
	long double xM;

	x = StrToFloatDef(((TEdit*)Sender)->Text, 0);

	switch (((TEdit*)Sender)->Tag) {
	case 0: xM = x / 1000 / 1000; break;
	case 1: xM = x / 1000; break;
	case 2: xM = x; break;
	case 3: xM = x * 10; break;
	case 4: xM = x * 10 * 10; break;
	case 5: xM = x * 10 * 10 * 10; break;
	}

	edNm->Text = FloatToStr(xM * 1000 * 1000);
	edMkm->Text = FloatToStr(xM * 1000);
	edMm->Text = FloatToStr(xM);
	edSm->Text = FloatToStr(xM / 10);
	edDm->Text = FloatToStr(xM / 10 / 10);
	Edm->Text = FloatToStr(xM / 10 / 10 / 10);
}
//---------------------------------------------------------------------------
void __fastcall Tfm::edQIAllKeyUp(TObject *Sender, WORD &Key, System::WideChar &KeyChar,
          TShiftState Shift)
{
	long double x;
	long double xM;

	x = StrToFloatDef(((TEdit*)Sender)->Text, 0);

	switch (((TEdit*)Sender)->Tag) {
	case 0: xM = x / 8 / 1024; break;
	case 1: xM = x / 1024; break;
	case 2: xM = x / 8; break;
	case 3: xM = x; break;
	case 4: xM = x * 8 * 1024; break;
	case 5: xM = x * 1024; break;
	}

	edKbi->Text = FloatToStr(xM * 8 * 1024);
	edKba->Text = FloatToStr(xM * 1024);
	edMbi->Text = FloatToStr(xM * 8);
	edMba->Text = FloatToStr(xM);
	edGbi->Text = FloatToStr(xM / 8 / 1024);
	edGba->Text = FloatToStr(xM / 1024);
}
//---------------------------------------------------------------------------
void __fastcall Tfm::edTempAllKeyUp(TObject *Sender, WORD &Key, System::WideChar &KeyChar,
          TShiftState Shift)
{
	long double x;
	long double xM;

	x = StrToFloatDef(((TEdit*)Sender)->Text, 0);

	switch (((TEdit*)Sender)->Tag) {
	case 0: xM = x; break;
	case 1: xM = x / 1.8 - 32; break;
	case 2: xM = x - 273.15; break;
	case 3: xM = x * 1.5 - 150; break;
	case 4: xM = x / 1.8 - 491.67; break;
	case 5: xM = x / 0.33; break;
	}

	edC->Text = FloatToStr(xM);
	edF->Text = FloatToStr(xM * 1.8 + 32);
	edK->Text = FloatToStr(xM + 273.15);
	edD->Text = FloatToStr(xM / 1.5 + 150);
	edRa->Text = FloatToStr(xM * 1.8 + 491.67);
	edN->Text = FloatToStr(xM * 0.33);
}
//---------------------------------------------------------------------------
void __fastcall Tfm::buBackClick(TObject *Sender)
{
	tc->GotoVisibleTab(tiMenu->Index);
}
//---------------------------------------------------------------------------
