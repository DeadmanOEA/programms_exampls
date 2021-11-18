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
void __fastcall Tfm::buSaveClick(TObject *Sender)
{
    ta->Post();
}
//---------------------------------------------------------------------------
void __fastcall Tfm::buCancelClick(TObject *Sender)
{
	ta->Cancel() ;
}
//---------------------------------------------------------------------------
void __fastcall Tfm::buFilterOnClick(TObject *Sender)
{
    ta->Filter = edFilter->Text;
	ta->Filtered = true;
}
//---------------------------------------------------------------------------
void __fastcall Tfm::buFilterOffClick(TObject *Sender)
{
	ta->Filtered = false;
}
//---------------------------------------------------------------------------
void __fastcall Tfm::buAddAge1Click(TObject *Sender)
{
	ta->Edit();
	taAge->Value += 1;
    ta->Post();
}
//---------------------------------------------------------------------------
void __fastcall Tfm::buAddAllMoneyClick(TObject *Sender)
{
	ta->First();
	while (! ta->Eof) {
		ta->Edit();
		taMoney->Value += 100;
		ta->Post();
		ta->Next();
	}


}

//---------------------------------------------------------------------------
void __fastcall Tfm::ckReadOnlyTableChangeChange(TObject *Sender)
{
	ta->ReadOnly = ckReadOnlyTableChange->IsChecked;
}
//---------------------------------------------------------------------------
void __fastcall Tfm::ckReadOnlyGridChange(TObject *Sender)
{
	Grid1->ReadOnly = ckReadOnlyGrid->IsChecked;
}
//---------------------------------------------------------------------------
void __fastcall Tfm::buLocateClick(TObject *Sender)
{
	ta->Locate(taAge->FieldName, edL->Text);
}
//---------------------------------------------------------------------------
void __fastcall Tfm::buLookupClick(TObject *Sender)
{

	ShowMessage(ta->Lookup(taAge->FieldName, edL->Text, taFIO->FieldName));
}
//---------------------------------------------------------------------------
void __fastcall Tfm::buGetAllMoneyClick(TObject *Sender)
{
	double m=0;
	ta->First();
	while (! ta->Eof) {

		m += taMoney->Value;
		ta->Next();
	}

	ShowMessage(m);
}
//---------------------------------------------------------------------------
void __fastcall Tfm::buMinClick(TObject *Sender)
{
	double m;
	ta->First();
	m = taMoney->Value;
	while (! ta->Eof) {
		if (m > taMoney->Value) {
		   m = taMoney->Value;
		}

		ta->Next();
	}

	ShowMessage(m);
}
//---------------------------------------------------------------------------
void __fastcall Tfm::buSaveTableClick(TObject *Sender)
{
	ta->SaveToFile(Ioutils::TPath::GetDocumentsPath() + PathDelim + edFileName->Text + ".json");
}
//---------------------------------------------------------------------------
void __fastcall Tfm::buLoadTableClick(TObject *Sender)
{
	ta->LoadFromFile(Ioutils::TPath::GetDocumentsPath() + PathDelim + edFileName->Text + ".json");
}
//---------------------------------------------------------------------------
void __fastcall Tfm::taAfterScroll(TDataSet *DataSet)
{
	Memo1->Lines->Add("taAfterScroll - " + taFIO->Value);
}
//---------------------------------------------------------------------------
void __fastcall Tfm::taBeforeScroll(TDataSet *DataSet)
{
	Memo1->Lines->Add("taBeforeScroll - " + taFIO->Value);
}
//---------------------------------------------------------------------------
