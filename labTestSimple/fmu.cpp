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
void __fastcall Tfm::FormCreate(TObject *Sender)
{
	tc->ActiveTab = tiMenu;
	tc->TabPosition = TTabPosition::None;
	pb->Max = tc->TabCount-1;
	tcChange(Sender);

}
//---------------------------------------------------------------------------
void __fastcall Tfm::buStartClick(TObject *Sender)
{
	FCountCorrect = 0;
	FCountWrong = 0;
	me->Lines->Clear();
	tc->Next();
	im1->Visible = false;
	im2->Visible = false;
}
//---------------------------------------------------------------------------
void __fastcall Tfm::ButtonAllClick(TObject *Sender)
{
	UnicodeString x;



	if (((TControl *)Sender)->Tag == 1) {
		x = L"Верно";
		FCountCorrect++;

	} else {
		x = L"Неверно";
		FCountWrong++;
	}

	me->Lines->Add(L"Вопрос " + tc->ActiveTab->Text +" - " + x);

	tc->Next();
}
//---------------------------------------------------------------------------
void __fastcall Tfm::buRestartClick(TObject *Sender)
{
	tc->First();
}
//---------------------------------------------------------------------------
void __fastcall Tfm::bAboutClick(TObject *Sender)
{
	ShowMessage("labTestSimple - Osokin Evgeniy");
}
//---------------------------------------------------------------------------
void __fastcall Tfm::tcChange(TObject *Sender)
{
	pb->Value = tc->ActiveTab->Index;
	if (tc->ActiveTab == tiResult) {
		laCorrect->Text = Format(L"Верно - %d", ARRAYOFCONST((FCountCorrect)));
		laWrong->Text = Format(L"Неверно - %d", ARRAYOFCONST((FCountWrong)));
        fa1->Enabled = true;
		if (FCountCorrect > FCountWrong) {
			im1->Visible = true;
		} else {
			im2->Visible = true;
		}
	}




	laNum->Text = Format(L"%d из %d",
		ARRAYOFCONST((tc->ActiveTab->Index, tc->TabCount-2)));
	laNum->Visible = ((tc->ActiveTab != tiMenu) && (tc->ActiveTab != tiResult));
    //https://yadi.sk/d/UvOaN4wFzhx87
}
//---------------------------------------------------------------------------
void __fastcall Tfm::buCTClick(TObject *Sender)
{
	if (fm->StyleBook == StyleBook1) {
		fm->StyleBook = StyleBook2;
	} else {
		fm->StyleBook = StyleBook1;
	}

}
//---------------------------------------------------------------------------
