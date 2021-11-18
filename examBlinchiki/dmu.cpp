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
	quProduct->Filter = quProductCATEGORY_ID->FieldName + " = " + quCategoryID->AsString;
}
//---------------------------------------------------------------------------
void Tdm::FeedbackIns(UnicodeString aFio, UnicodeString aEmail, UnicodeString aNote)
{
	spFeedbackIns->ParamByName("fio")->Value = aFio;
	spFeedbackIns->ParamByName("E-MAIL")->Value = aEmail;
	spFeedbackIns->ParamByName("deskrip")->Value = aNote;
	spFeedbackIns->ExecProc();
}
