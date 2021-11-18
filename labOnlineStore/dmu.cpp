//---------------------------------------------------------------------------


#pragma hdrstop

#include "dmu.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma classgroup "FMX.Controls.TControl"
#pragma resource "*.dfm"
Tdm *dm;
//---------------------------------------------------------------------------
__fastcall Tdm::Tdm(TComponent* Owner)
	: TDataModule(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall Tdm::quCategoryAfterScroll(TDataSet *DataSet)
{
	quProduct->Filter =
        quProductCATEGORY_ID->FieldName + " = " + quCategoryID->AsString;
}
//---------------------------------------------------------------------------
void Tdm::FeedbackIns(UnicodeString aFio, UnicodeString aPhone, UnicodeString aEmail, UnicodeString aNote)
{
	spFeedbackIns->ParamByName("FIO")->Value = aFio;
	spFeedbackIns->ParamByName("PHONE")->Value = aPhone;
	spFeedbackIns->ParamByName("EMAIL")->Value = aEmail;
	spFeedbackIns->ParamByName("NOTE")->Value = aNote;
    spFeedbackIns->ExecProc();
}
