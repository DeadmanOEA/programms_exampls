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
void __fastcall Tfm::FormSaveState(TObject *Sender)
{
	TBinaryWriter* x;
	SaveState->Stream->Clear();
	x = new TBinaryWriter (SaveState->Stream);
	try {
		x->Write(Edit1->Text);
		x->Write(DateEdit1->Date.Val);
		x->Write(TimeEdit1->Time.Val);
		x->Write(TrackBar1->Value);
		x->Write(Switch1->IsChecked);
		x->Write(TabControl1->ActiveTab->Index);
	} __finally {
		x->DisposeOf();
	}
}
//---------------------------------------------------------------------------
void __fastcall Tfm::FormCreate(TObject *Sender)
{
	TBinaryReader* x;
	if (SaveState->Stream->Size > 0) {
		x = new TBinaryReader (SaveState->Stream, TEncoding::UTF8, false);
		try {
			Edit1->Text = x->ReadString();
			DateEdit1->Date = x->ReadDouble();
			TimeEdit1->Time = x->ReadDouble();
			TrackBar1->Value = x->ReadSingle();
			Switch1->IsChecked = x->ReadBoolean();
			TabControl1->ActiveTab = TabControl1->Tabs[x->ReadInteger()];
		} __finally {
			x->DisposeOf();
		}
	}

}
//---------------------------------------------------------------------------
