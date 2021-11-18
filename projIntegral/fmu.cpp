//---------------------------------------------------------------------------

#include <fmx.h>
#pragma hdrstop

#include "fmu.h"
#include "calc.h"
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
void __fastcall Tfm::FormCreate(TObject *Sender)
{
	tc->ActiveTab = tiMenu;
	tc->TabPosition = TTabPosition::None;
    fm->StyleBook = StyleBook2;
}
//---------------------------------------------------------------------------
void __fastcall Tfm::buSettingsClick(TObject *Sender)
{
    tc->GotoVisibleTab(tiSettings->Index);
}
//---------------------------------------------------------------------------
void __fastcall Tfm::buCalcClick(TObject *Sender)
{
	while (!MetCheck())
	return;
	if (ckSq->IsChecked) {
		laFirst->Text = CalcStrSq(ValStr, up, down, delta);
	}

	if (ckTrap->IsChecked) {
		laSecond->Text = CalcStrTrap(ValStr, up, down, delta);
	}
	tc->GotoVisibleTab(tiRes->Index);
}
//---------------------------------------------------------------------------
void __fastcall Tfm::buBackClick(TObject *Sender)
{
	tc->GotoVisibleTab(tiMenu->Index);
}
//---------------------------------------------------------------------------
void __fastcall Tfm::buAboutClick(TObject *Sender)
{
	ShowMessage("Osokin Evgeniy");
}
//---------------------------------------------------------------------------
void __fastcall Tfm::buStartClick(TObject *Sender)
{
	tc->GotoVisibleTab(tiBegin->Index);
}
//---------------------------------------------------------------------------
bool Tfm::MetCheck(){
	if (edVal->Text != "") {
		ValStr = edVal->Text;
	} else {
		ShowMessage("¬ведите выражение");
		return false;
	}

	if (edUp->Text != "") {
		up = StrToFloatDef(edUp->Text, 0);
	} else {
		ShowMessage("¬ведите верхний предел");
		return false;
	}

	if (edDown->Text != "") {
		down = StrToFloatDef(edDown->Text, 0);
	} else {
		ShowMessage("¬ведите нижний предел");
		return false;
	}

	if (edDelta->Text != "") {
		delta = StrToFloatDef(edDelta->Text, 0);
	} else {
		ShowMessage("¬ведите дельту");
		return false;
	}

	return true;
}
//---------------------------------------------------------------------------
void __fastcall Tfm::ThemeClick(TObject *Sender)
{
	if (((TControl *)Sender)->Tag == 0) {
		fm->StyleBook = StyleBook1;
	} else {
		fm->StyleBook = StyleBook2;
	}
}
//---------------------------------------------------------------------------

