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
void __fastcall Tfm::buNextAllClick(TObject *Sender)
{
	int xYes = 0;
	int xNo = 0;
	TControl* xParent = (TControl*)((TControl*)Sender)->ParentControl;
	TCheckBox* x;
	for (int i = 0; i < xParent->ControlsCount - 1; i++) {
		if (dynamic_cast<TCheckBox*>(xParent->Controls->Items[i])) {
			x = (TCheckBox*)(xParent->Controls->Items[i]);
			if (x->IsChecked) {
				if (x->Tag >= 1) {
					xYes++;
				} else {
					xNo++;
				}
			} else {
                if (x->Tag >= 1) {
					xNo++;
				}
            }
		}
	}

	FCountCorrect += xYes;
	FCountWrong += xNo;

	me->Lines->Add(Format(L"Вопрос %s - %d %%",
	ARRAYOFCONST((tc->ActiveTab->Text, xYes*100/(xYes + xNo) )) ));
	tc->Next(TTabTransition::None);
}
//---------------------------------------------------------------------------
void __fastcall Tfm::tcChange(TObject *Sender)
{
	pb->Value = tc->ActiveTab->Index;

	if (tc->ActiveTab == tiResult) {
		laRight->Text = Format(L"Вопрос %s - %d %%",
		ARRAYOFCONST((FCountCorrect*100/(FCountCorrect + FCountWrong) )) );
		laNone->Text = Format(L"Вопрос %s - %d %%",
		ARRAYOFCONST((FCountWrong*100/(FCountCorrect + FCountWrong) )) );
		imR->Visible = (FCountCorrect > FCountWrong);
		imN->Visible = !imR->Visible;
	}

	laNum->Text = Format(L"%d из %d",
		ARRAYOFCONST((tc->ActiveTab->Index, tc->TabCount - 2)) );
	laNum->Visible = (tc->ActiveTab != tiMenu) && (tc->ActiveTab != tiResult);
	pb->Visible = (tc->ActiveTab != tiMenu);
}
//---------------------------------------------------------------------------
void __fastcall Tfm::buStartClick(TObject *Sender)
{
	FCountCorrect = 0;
	FCountWrong = 0;
	me->Lines->Clear();
	tc->Next();
	imR->Visible = false;
	imN->Visible = false;
}
//---------------------------------------------------------------------------
void __fastcall Tfm::buResClick(TObject *Sender)
{
	tc->First();
}
//---------------------------------------------------------------------------
void __fastcall Tfm::Button1Click(TObject *Sender)
{
	ShowMessage("labTestSimple - Osokin Evgeniy");
}
//---------------------------------------------------------------------------
