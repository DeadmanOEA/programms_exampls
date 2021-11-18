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
void __fastcall Tfm::buAddClick(TObject *Sender)
{
	dm->taNotes->Append();
	tc->GotoVisibleTab(tiItem->Index);
}
//---------------------------------------------------------------------------
void __fastcall Tfm::buSaveClick(TObject *Sender)
{
	dm->taNotes->Post();
	tc->GotoVisibleTab(tiList->Index);
}
//---------------------------------------------------------------------------
void __fastcall Tfm::buCancelClick(TObject *Sender)
{
	dm->taNotes->Cancel();
	tc->GotoVisibleTab(tiList->Index);
}
//---------------------------------------------------------------------------
void __fastcall Tfm::buDeleteClick(TObject *Sender)
{
    dm->taNotes->Delete();
	tc->GotoVisibleTab(tiList->Index);
}
//---------------------------------------------------------------------------
void __fastcall Tfm::FormCreate(TObject *Sender)
{
	tc->ActiveTab = tiList;
	tc->TabPosition = TTabPosition::None;
}
//---------------------------------------------------------------------------
void __fastcall Tfm::FormShow(TObject *Sender)
{
	dm->FDConnection1->Connected = true;
}
//---------------------------------------------------------------------------
void __fastcall Tfm::lvItemClick(TObject * const Sender, TListViewItem * const AItem)

{
	dm->taNotes->Edit();
	tc->GotoVisibleTab(tiItem->Index);
}
//---------------------------------------------------------------------------
