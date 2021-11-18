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
void __fastcall Tfm::buStartClick(TObject *Sender)
{
	IdTCPServer->Active = true;
	me->Lines->Add("Active = true");

}
//---------------------------------------------------------------------------

void __fastcall Tfm::buStopClick(TObject *Sender)
{
	IdTCPServer->Active = false;
	me->Lines->Add("Active = false");
}
//---------------------------------------------------------------------------

void __fastcall Tfm::IdTCPServerConnect(TIdContext *AContext)
{
	me->Lines->Add(Format("[%s] - Client connected",
		ARRAYOFCONST((AContext->Connection->Socket->Binding->PeerIP))
	));
}
//---------------------------------------------------------------------------

void __fastcall Tfm::IdTCPServerDisconnect(TIdContext *AContext)
{
	me->Lines->Add(Format("[%s] - Client disconnect",
		ARRAYOFCONST((AContext->Connection->Socket->Binding->PeerIP))
	));
}
//---------------------------------------------------------------------------

void __fastcall Tfm::IdTCPServerExecute(TIdContext *AContext)
{
	UnicodeString x = AContext->Connection->Socket->ReadLn();
	me->Lines->Add("Input = " + x);
	//
	if (x == "time") {
		AContext->Connection->Socket->WriteLn(TimeToStr(Now()));
	}
	if (x == "str") {
		AContext->Connection->Socket->WriteLn(edStr->Text,
			IndyTextEncoding_UTF8());
	}
	if (x == "image") {
		TMemoryStream *x = new TMemoryStream();
		try {
			im->Bitmap->SaveToStream(x);
			x->Seek(0,0);
			AContext->Connection->Socket->Write(x->Size);
			AContext->Connection->Socket->Write(x);
		}
		__finally {
			delete x;
		}
	}
	if (x == "serinf") {
		AContext->Connection->Socket->WriteLn(laVer->Text + ' ' + laName->Text,
			IndyTextEncoding_UTF8());
	}
	if (x == "gindex") {
		AContext->Connection->Socket->WriteLn(IntToStr(gImage->ImageIndex),
			IndyTextEncoding_UTF8());
        TMemoryStream *x = new TMemoryStream();
		try {
			//gImage->Images->BitmapExists(gImage->ImageIndex)->SaveToStream(x);
            //il->
			im->Bitmap->SaveToStream(x);
			x->Seek(0,0);
			AContext->Connection->Socket->Write(x->Size);
			AContext->Connection->Socket->Write(x);
		}
		__finally {
			delete x;
		}
	}
}
//---------------------------------------------------------------------------



void __fastcall Tfm::buNextClick(TObject *Sender)
{
	gImage->ImageIndex = gImage->ImageIndex + 1;
}
//---------------------------------------------------------------------------

void __fastcall Tfm::buPrevClick(TObject *Sender)
{
    gImage->ImageIndex = gImage->ImageIndex - 1;
}
//---------------------------------------------------------------------------

