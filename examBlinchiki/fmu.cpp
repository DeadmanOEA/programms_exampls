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
void __fastcall Tfm::buAboutClick(TObject *Sender)
{
    ShowMessage("Osokin 161-342");
}
//---------------------------------------------------------------------------
void __fastcall Tfm::buThemeClick(TObject *Sender)
{
	if (((TControl *)Sender)->Tag == 0) {
		fm->StyleBook = StyleBook2;
		((TControl *)Sender)->Tag = 1;
	} else {
		fm->StyleBook = StyleBook1;
		((TControl *)Sender)->Tag = 0;
	}
}
//---------------------------------------------------------------------------
void __fastcall Tfm::FormCreate(TObject *Sender)
{
	tc->ActiveTab = tiMenu;
	tc->TabPosition = TTabPosition::None;
    fm->StyleBook = StyleBook1;
}
//---------------------------------------------------------------------------
void __fastcall Tfm::buContClick(TObject *Sender)
{
	tc->GotoVisibleTab(tiContacts->Index);
}
//---------------------------------------------------------------------------
void __fastcall Tfm::buDostClick(TObject *Sender)
{
	tc->GotoVisibleTab(tiDost->Index);
}
//---------------------------------------------------------------------------
void __fastcall Tfm::buCallBClick(TObject *Sender)
{
	tc->GotoVisibleTab(tiCallBack->Index);
}
//---------------------------------------------------------------------------
void __fastcall Tfm::buBucketClick(TObject *Sender)
{
	tc->GotoVisibleTab(tiBucket->Index);
}
//---------------------------------------------------------------------------
void __fastcall Tfm::buVictClick(TObject *Sender)
{
	tc->GotoVisibleTab(tiVict->Index);
}
//---------------------------------------------------------------------------
void __fastcall Tfm::buOrderClick(TObject *Sender)
{
	tc->GotoVisibleTab(tiCateg->Index);
}
//---------------------------------------------------------------------------
void __fastcall Tfm::buBackCatClick(TObject *Sender)
{
	tc->GotoVisibleTab(tiMenu->Index);
}
//---------------------------------------------------------------------------

void __fastcall Tfm::tiProdClick(TObject *Sender)
{
	tc->GotoVisibleTab(tiCateg->Index);
}
//---------------------------------------------------------------------------

void __fastcall Tfm::ListView1ItemClick(TObject * const Sender, TListViewItem * const AItem)

{
	tc->GotoVisibleTab(tiProd->Index);
}
//---------------------------------------------------------------------------

void __fastcall Tfm::ListView2ItemClick(TObject * const Sender, TListViewItem * const AItem)

{
	tc->GotoVisibleTab(tiGood->Index);
}
//---------------------------------------------------------------------------

void __fastcall Tfm::buBackListOfGoodsClick(TObject *Sender)
{
	numOfGood = 0;
	laNum->Text = numOfGood;
	tc->GotoVisibleTab(tiProd->Index);
}
//---------------------------------------------------------------------------


void __fastcall Tfm::Button1Click(TObject *Sender)
{
	numOfGood += ((TControl *)Sender)->Tag;
	laNum->Text = numOfGood;
}
//---------------------------------------------------------------------------

void __fastcall Tfm::buBucketAddClick(TObject *Sender)
{
	tc->GotoVisibleTab(tiBucket->Index);
}
//---------------------------------------------------------------------------

void __fastcall Tfm::buFastBuyClick(TObject *Sender)
{
	tc->GotoVisibleTab(tiBucket->Index);
}
//---------------------------------------------------------------------------

void __fastcall Tfm::bu1Click(TObject *Sender)
{
	tc->GotoVisibleTab(tiRes->Index);
}
//---------------------------------------------------------------------------

void __fastcall Tfm::buBeginClick(TObject *Sender)
{
	tc->GotoVisibleTab(TabItem1->Index);
}
//---------------------------------------------------------------------------

void __fastcall Tfm::Button9Click(TObject *Sender)
{
	tc->GotoVisibleTab(tiVict->Index);
}
//---------------------------------------------------------------------------

void __fastcall Tfm::buAddCallClick(TObject *Sender)
{
	tc->GotoVisibleTab(tiCalls->Index);
}
//---------------------------------------------------------------------------

void __fastcall Tfm::buAddNewCallClick(TObject *Sender)
{
	tc->GotoVisibleTab(tiCallBack->Index);
	dm->FeedbackIns(edFIO->Text, edMail->Text, meCall->Text);

}
//---------------------------------------------------------------------------

void __fastcall Tfm::buMakeOrderClick(TObject *Sender)
{
	tc->GotoVisibleTab(tiAddOrd->Index);
}
//---------------------------------------------------------------------------

void __fastcall Tfm::Button12Click(TObject *Sender)
{
	tc->GotoVisibleTab(tiMenu->Index);
}
//---------------------------------------------------------------------------

void __fastcall Tfm::Button11Click(TObject *Sender)
{
	tc->GotoVisibleTab(tiBucket->Index);
}
//---------------------------------------------------------------------------

