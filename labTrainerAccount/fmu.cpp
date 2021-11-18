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
void Tfm::DoReset(){
	FCountCorrect = 0;
	FLeverComplexity = 20;
	FCountWrong = 0;
	FXir = 1;
	DoContinue();
}
//---------------------------------------------------------------------------
void Tfm::DoContinue(){
	laCorrect->Text = Format(L"Correct = %d", ARRAYOFCONST((FCountCorrect)));
	laWrong->Text = Format(L"Wrong = %d", ARRAYOFCONST((FCountWrong)));
	//
	int xValue1 = Random(FLeverComplexity);
	int xValue2 = Random(FLeverComplexity);
	int xResult;
	int FXer;
	if (FXir == 1) {
	  FXer = 1;
	} else if (FXir == 2) {
			 FXer = Random(2);
		   } else {
			 FXer = Random(3);
		   }
	if (FXer == 1) {
	  xResult = xValue1 + xValue2;
	} else if (FXer == 2) {
			 xResult = xValue1 - xValue2;
		   } else {
		   xResult = xValue1 * xValue2;
		   }
	int xSign = (Random(2) == 1) ? 1 : -1;
	int xResultNew = (Random(2) == 1) ? xResult : xResult + (Random(7) * xSign);
	//
	FAnswerCorrect = (xResult == xResultNew);
	if (FXer == 1) {
	  laCode->Text = Format("%d + %d = %d",
		ARRAYOFCONST((xValue1, xValue2, xResultNew)));
	} else if (FXer == 2) {
			 laCode->Text = Format("%d - %d = %d",
		ARRAYOFCONST((xValue1, xValue2, xResultNew)));
		   } else {
		   laCode->Text = Format("%d * %d = %d",
		ARRAYOFCONST((xValue1, xValue2, xResultNew)));
		   }

}
//---------------------------------------------------------------------------
void Tfm::DoAnswer (bool aValue){
	(aValue == FAnswerCorrect) ? FCountCorrect++ : FCountWrong++;
	DoContinue();
}
//---------------------------------------------------------------------------
void __fastcall Tfm::FormCreate(TObject *Sender)
{
	Randomize();
    DoReset();
}
//---------------------------------------------------------------------------

void __fastcall Tfm::buRestartClick(TObject *Sender)
{
	DoReset();
}
//---------------------------------------------------------------------------

void __fastcall Tfm::buYesClick(TObject *Sender)
{
	DoAnswer(true);
}
//---------------------------------------------------------------------------

void __fastcall Tfm::buNoClick(TObject *Sender)
{
    DoAnswer(false);
}
//---------------------------------------------------------------------------

void __fastcall Tfm::buAboutClick(TObject *Sender)
{
	ShowMessage(L"labTrainerAccount - Osokin Evgeniy");
}
//---------------------------------------------------------------------------

void __fastcall Tfm::buEasyClick(TObject *Sender)
{
	FLeverComplexity = 20;
	DoReset();
	FXir = 1;
}
//---------------------------------------------------------------------------

void __fastcall Tfm::buMediumClick(TObject *Sender)
{
	FLeverComplexity = 70;
	DoReset();
	FXir = 2;
}
//---------------------------------------------------------------------------

void __fastcall Tfm::buHardClick(TObject *Sender)
{
   FLeverComplexity = 300;
   DoReset();
   FXir = 3;
}
//---------------------------------------------------------------------------

