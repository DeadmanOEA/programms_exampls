//---------------------------------------------------------------------------

#include <fmx.h>
#pragma hdrstop

#include "fmu.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.fmx"
Tfm *fm;
//---------------------------------------------------------------------------
inline int Low(const System::UnicodeString &)
{
	#ifdef _DELPHI_STRING_ONE_BASED
		return 1;
	#else
		return 0;
	#endif
}
//---------------------------------------------------------------------------
inline int High(const System::UnicodeString &S)
{
	#ifdef _DELPHI_STRING_ONE_BASED
		return S.Length();
	#else
		return S.Length() - 1;
	#endif
} 
//---------------------------------------------------------------------------
__fastcall Tfm::Tfm(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall Tfm::FormCreate(TObject *Sender)
{
	tc->ActiveTab = tb1;
	UnicodeString x;
	UnicodeString y;
	UnicodeString z;
	int num;
	//через строчку
	for (int i = 2; i < meFull->Lines->Count; i++) {
		x = meFull->Lines->Strings[i];
		if (i % 2 == 1) {
			for (int j = Low(x); j <= High(x); j++) {
				if (x[j] != ' ')
					x[j] = 'x';
			}
		}
		me1->Lines->Add(x);
	}
	//первые слова
	bool xFlag;
	for (int i = 2; i < meFull->Lines->Count; i++) {
		x = meFull->Lines->Strings[i];
		xFlag = false;
		for (int j = Low(x); j <= High(x); j++) {
			if ((xFlag) && (x[j] != ' '))
				x[j] = 'x';
			if ((!xFlag) && (x[j] == ' '))
				xFlag = true;
		}
		me2->Lines->Add(x);
	}


	for (int i = 2; i < meFull->Lines->Count; i++) {
		x = meFull->Lines->Strings[i];
		xFlag = false;
		for (int j = Low(x); j <= High(x); j++) {
			if ((xFlag) && (x[j] != ' '))
				x[j] = 'x';
			if (x[j] == ' ')
				xFlag = !xFlag;
		}
		me3->Lines->Add(x);
	}
	
	for (int i = 2; i < meFull->Lines->Count; i++) {
	x = meFull->Lines->Strings[i];
	y = "";
		
	num = 0;
	for (int j = Low(x); j <= High(x); j++) {
			
		  if ((x[j] != ' ') && (x[j] != '-'))
		  {
			 y[num] = x[j];	
		 } else if(x[j] == ' '){
		 for (int v = num; v > 0; v--) {
				z = z + y[v];    
			}
			  
			  y = "";
			  num = 0;
			}
			
		}
		me4->Lines->Add(z);
	}
	
}
//---------------------------------------------------------------------------
void __fastcall Tfm::buPlusClick(TObject *Sender)
{
	meFull->Font->Size = meFull->Font->Size + 1;
	me1->Font->Size = meFull->Font->Size + 1;
	me2->Font->Size = meFull->Font->Size + 1;
}
//---------------------------------------------------------------------------
void __fastcall Tfm::buMinusClick(TObject *Sender)
{
	meFull->Font->Size = meFull->Font->Size - 1;
	me1->Font->Size = meFull->Font->Size - 1;
	me2->Font->Size = meFull->Font->Size - 1;	
}
//---------------------------------------------------------------------------
void __fastcall Tfm::buAboutClick(TObject *Sender)
{
	ShowMessage("labPoesy - Osokin Evgeniy");	
}
//---------------------------------------------------------------------------
