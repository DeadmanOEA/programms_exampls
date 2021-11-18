//---------------------------------------------------------------------------

#include <fmx.h>
#pragma hdrstop

#include "fmu.h"
#include "dmu.h"
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
void __fastcall Tfm::buCategClick(TObject *Sender)
{
	tc->GotoVisibleTab(tiCat->Index);
}
//---------------------------------------------------------------------------
void __fastcall Tfm::buFeedbackClick(TObject *Sender)
{
	tc->GotoVisibleTab(tiFeedback->Index);
}
//---------------------------------------------------------------------------
void __fastcall Tfm::buAboutClick(TObject *Sender)
{
    ShowMessage("Osokin 161-342");
}
//---------------------------------------------------------------------------
void __fastcall Tfm::FormCreate(TObject *Sender)
{
	tc->ActiveTab = tiMenu;
	tc->TabPosition = TTabPosition::None;
}
//---------------------------------------------------------------------------

void __fastcall Tfm::Button1Click(TObject *Sender)
{

	if (((TControl *)Sender)->Tag == 1) {
		tc->GotoVisibleTab(tiCat->Index);
	} else {
		tc->GotoVisibleTab(tiMenu->Index);
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfm::ListView1ItemClick(TObject * const Sender, TListViewItem * const AItem)

{
	tc->GotoVisibleTab(tiProd->Index);
}
//---------------------------------------------------------------------------


