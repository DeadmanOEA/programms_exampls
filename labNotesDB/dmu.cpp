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
void __fastcall Tdm::FDConnection1AfterConnect(TObject *Sender)
{
	FDConnection1->ExecSQL(
		"CREATE TABLE IF NOT EXISTS [Notes] ("
		" [Caption]  VARCHAR (50)  NOT NULL,"
		" [Priority] INT NOT NULL,"
		" [Detail] VARCHAR (500))"
	);
	taNotes->Open();
}
//---------------------------------------------------------------------------
void __fastcall Tdm::FDConnection1BeforeConnect(TObject *Sender)
{
	FDConnection1->Params->Values["Database"] =
	#ifdef _Windows
		"..\\..\\" + cNameDB;
	#else
		System::Ioutils::TPath::GetDocumentsPath() + PathDelim + cNameDB;
	#endif
}
//---------------------------------------------------------------------------
