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
void __fastcall Tfm::buAllStartClick(TObject *Sender)
{
	//обработчик нажатий на кнопку, старта выбор режима
	if (((TControl *)Sender)->Tag == 1) {
		bTimerOn = true;
	} else {
		bTimerOn = false;
	}
	tc->ActiveTab = tiChooseGame;
}
//---------------------------------------------------------------------------

void __fastcall Tfm::buSettingsClick(TObject *Sender)
{
	//переход в настройки
	tc->ActiveTab = tiSettings;
}
//---------------------------------------------------------------------------

void __fastcall Tfm::buComplexityClick(TObject *Sender)
{
	//выбор сложности
	iComplexity = ((TControl *)Sender)->Tag;

	Start(iComplexity);

	tc->ActiveTab = tiGame;
}
//---------------------------------------------------------------------------

void __fastcall Tfm::buThemeClick(TObject *Sender)
{
	//переход в выбор темы
	tc->ActiveTab = tiTheme;

}
//---------------------------------------------------------------------------

void __fastcall Tfm::buAboutClick(TObject *Sender)
{
	//переход в поле About
	tc->ActiveTab = tiAbout;
}
//---------------------------------------------------------------------------


void __fastcall Tfm::ThemeClick(TObject *Sender)
{
	//Выбор темы
	if (((TControl *)Sender)->Tag == 0) {
		fm->StyleBook = StyleBook1;
	} else {
		fm->StyleBook = StyleBook2;
    }
}
//---------------------------------------------------------------------------

void __fastcall Tfm::FormCreate(TObject *Sender)
{
	tc->ActiveTab = tiMainMenu;
	tc->TabPosition = TTabPosition::None;
	bigtxt = 28;
	smalltxt = 9;
	iComplexityConst = 25;  //25
	choseitem = false;
    for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			i1Num[i][j] = " ";
			i2Num[i][j] = " ";
			i3Num[i][j] = " ";
			i4Num[i][j] = " ";
			i5Num[i][j] = " ";
			i6Num[i][j] = " ";
			i7Num[i][j] = " ";
			i8Num[i][j] = " ";
			i9Num[i][j] = " ";
		}
	}
	laResInf->Visible = false;
	laTimeRes->Visible = false;
	laTime->Visible = false;
	fm->StyleBook = StyleBook2;
}
//---------------------------------------------------------------------------


void __fastcall Tfm::buBackClick(TObject *Sender)
{
	//кнопки возврата
	if (((TControl *)Sender)->Tag == 1) {
		tc->ActiveTab = tiMainMenu;
	} else {
		tc->ActiveTab = tiSettings;
	}
}
//---------------------------------------------------------------------------


void __fastcall Tfm::buAllSClick(TObject *Sender)
{
	//обработчик кнопок заметок
	int str;
	String send;
	send = "";
	if (choseitem == true) {
		str = ((TControl *)Sender)->Tag + 1;
		if (iStartNum[meXnow][meYnow] == 0) {
			if (meXnow == 0) {
				if (i1Num[meYnow][((TControl *)Sender)->Tag] == " ") {
					i1Num[meYnow][((TControl *)Sender)->Tag] = str;
				} else {
					i1Num[meYnow][((TControl *)Sender)->Tag] = " ";
				}

				send += i1Num[meYnow][0] + ' ' + i1Num[meYnow][1] + ' ' + i1Num[meYnow][2] + '\n' + i1Num[meYnow][3] + ' ' + i1Num[meYnow][4] + ' ' + i1Num[meYnow][5] + '\n' + i1Num[meYnow][6] + ' ' + i1Num[meYnow][7] + ' ' + i1Num[meYnow][8];
			}
			if (meXnow == 1) {
				if (i2Num[meYnow][((TControl *)Sender)->Tag] == " ") {
					i2Num[meYnow][((TControl *)Sender)->Tag] = str;
				} else {
					i2Num[meYnow][((TControl *)Sender)->Tag] = " ";
				}

				send += i2Num[meYnow][0] + ' ' + i2Num[meYnow][1] + ' ' + i2Num[meYnow][2] + '\n' + i2Num[meYnow][3] + ' ' + i2Num[meYnow][4] + ' ' + i2Num[meYnow][5] + '\n' + i2Num[meYnow][6] + ' ' + i2Num[meYnow][7] + ' ' + i2Num[meYnow][8];
			}
			if (meXnow == 2) {
				if (i3Num[meYnow][((TControl *)Sender)->Tag] == " ") {
					i3Num[meYnow][((TControl *)Sender)->Tag] = str;
				} else {
					i3Num[meYnow][((TControl *)Sender)->Tag] = " ";
				}

				send += i3Num[meYnow][0] + ' ' + i3Num[meYnow][1] + ' ' + i3Num[meYnow][2] + '\n' + i3Num[meYnow][3] + ' ' + i3Num[meYnow][4] + ' ' + i3Num[meYnow][5] + '\n' + i3Num[meYnow][6] + ' ' + i3Num[meYnow][7] + ' ' + i3Num[meYnow][8];
			}
			if (meXnow == 3) {
				if (i4Num[meYnow][((TControl *)Sender)->Tag] == " ") {
					i4Num[meYnow][((TControl *)Sender)->Tag] = str;
				} else {
					i4Num[meYnow][((TControl *)Sender)->Tag] = " ";
				}

				send += i4Num[meYnow][0] + ' ' + i4Num[meYnow][1] + ' ' + i4Num[meYnow][2] + '\n' + i4Num[meYnow][3] + ' ' + i4Num[meYnow][4] + ' ' + i4Num[meYnow][5] + '\n' + i4Num[meYnow][6] + ' ' + i4Num[meYnow][7] + ' ' + i4Num[meYnow][8];
			}
			if (meXnow == 4) {
				if (i5Num[meYnow][((TControl *)Sender)->Tag] == " ") {
					i5Num[meYnow][((TControl *)Sender)->Tag] = str;
				} else {
					i1Num[meYnow][((TControl *)Sender)->Tag] = " ";
				}

				send += i5Num[meYnow][0] + ' ' + i5Num[meYnow][1] + ' ' + i5Num[meYnow][2] + '\n' + i5Num[meYnow][3] + ' ' + i5Num[meYnow][4] + ' ' + i5Num[meYnow][5] + '\n' + i5Num[meYnow][6] + ' ' + i5Num[meYnow][7] + ' ' + i5Num[meYnow][8];
			}
			if (meXnow == 5) {
				if (i6Num[meYnow][((TControl *)Sender)->Tag] == " ") {
					i6Num[meYnow][((TControl *)Sender)->Tag] = str;
				} else {
					i6Num[meYnow][((TControl *)Sender)->Tag] = " ";
				}

				send += i6Num[meYnow][0] + ' ' + i6Num[meYnow][1] + ' ' + i6Num[meYnow][2] + '\n' + i6Num[meYnow][3] + ' ' + i6Num[meYnow][4] + ' ' + i6Num[meYnow][5] + '\n' + i6Num[meYnow][6] + ' ' + i6Num[meYnow][7] + ' ' + i6Num[meYnow][8];
			}
			if (meXnow == 6) {
				if (i7Num[meYnow][((TControl *)Sender)->Tag] == " ") {
					i7Num[meYnow][((TControl *)Sender)->Tag] = str;
				} else {
					i7Num[meYnow][((TControl *)Sender)->Tag] = " ";
				}

				send += i7Num[meYnow][0] + ' ' + i7Num[meYnow][1] + ' ' + i7Num[meYnow][2] + '\n' + i7Num[meYnow][3] + ' ' + i7Num[meYnow][4] + ' ' + i7Num[meYnow][5] + '\n' + i7Num[meYnow][6] + ' ' + i7Num[meYnow][7] + ' ' + i7Num[meYnow][8];
			}
			if (meXnow == 7) {
				if (i8Num[meYnow][((TControl *)Sender)->Tag] == " ") {
					i8Num[meYnow][((TControl *)Sender)->Tag] = str;
				} else {
					i8Num[meYnow][((TControl *)Sender)->Tag] = " ";
				}

				send += i8Num[meYnow][0] + ' ' + i8Num[meYnow][1] + ' ' + i8Num[meYnow][2] + '\n' + i8Num[meYnow][3] + ' ' + i8Num[meYnow][4] + ' ' + i8Num[meYnow][5] + '\n' + i8Num[meYnow][6] + ' ' + i8Num[meYnow][7] + ' ' + i8Num[meYnow][8];
			}
			if (meXnow == 8) {
				if (i9Num[meYnow][((TControl *)Sender)->Tag] == " ") {
					i9Num[meYnow][((TControl *)Sender)->Tag] = str;
				} else {
					i9Num[meYnow][((TControl *)Sender)->Tag] = " ";
				}

				send += i9Num[meYnow][0] + ' ' + i9Num[meYnow][1] + ' ' + i9Num[meYnow][2] + '\n' + i9Num[meYnow][3] + ' ' + i9Num[meYnow][4] + ' ' + i9Num[meYnow][5] + '\n' + i9Num[meYnow][6] + ' ' + i9Num[meYnow][7] + ' ' + i9Num[meYnow][8];
			}

			WorkWithTable(meXnow, meYnow, send, true, smalltxt, 1);
		}
	} else {
		ShowMessage("Select cell");
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfm::buAllBClick(TObject *Sender)
{
	//Обработчик основных кнопок цифр
	if (choseitem == true) {
		if (iStartNum[meXnow][meYnow] == 0) {
			WorkWithTable(meXnow, meYnow, ((TControl *)Sender)->Tag, true, bigtxt, 1);
			iResultNum[meXnow][meYnow] = ((TControl *)Sender)->Tag;
		}
	} else {
		ShowMessage("Select cell");
	}
	bEndGame = true;
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			if (iResultNum[i][j] != iFullNum[i][j]) {
				bEndGame = false;
			}
		}
	}

	if (bEndGame == true) {
		tc->ActiveTab = tiResult;
		if (bTimerOn == true) {
			tm->Enabled = false;
			laTimeRes->Text = laTime->Text;
			laResInf->Visible = true;
			laTimeRes->Visible = true;
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfm::buMenuClick(TObject *Sender)
{
    tc->ActiveTab = tiMainMenu;
}
//---------------------------------------------------------------------------

void __fastcall Tfm::buRestartClick(TObject *Sender)
{
	//кнопка обнуления поля
	FillTable(bigtxt);
}
//---------------------------------------------------------------------------
void Tfm::Start(int dif)
{
	//начало игры
	int num1;
	int num2;
	int num3;
    int n;
	int m;
	int x;
	bool next;
	int num;
	int count;
	//создание нулевого поля
	for (int i = 0; i < 3; i++) {
		num1 = i + 1;
		num2 = i + 4;
		num3 = i + 7;
		for (int j = 0; j < 9; j++) {
			if (i == 0) {
				iFullNum[i][j] = num1;
				iFullNum[i+1][j] = num2;
				iFullNum[i+2][j] = num3;
				num1++;
				num2++;
				num3++;
				if (num1 > 9) {
					num1 = 1;
				}
				if (num2 > 9) {
					num2 = 1;
				}
				if (num3 > 9) {
					num3 = 1;
				}
			}
			if (i == 1) {
				iFullNum[i+2][j] = num1;
				iFullNum[i+3][j] = num2;
				iFullNum[i+4][j] = num3;
				num1++;
				num2++;
				num3++;
				if (num1 > 9) {
					num1 = 1;
				}
				if (num2 > 9) {
					num2 = 1;
				}
				if (num3 > 9) {
					num3 = 1;
				}
			}
			if (i == 2) {
				iFullNum[i+4][j] = num1;
				iFullNum[i+5][j] = num2;
				iFullNum[i+6][j] = num3;
				num1++;
				num2++;
				num3++;
				if (num1 > 9) {
					num1 = 1;
				}
				if (num2 > 9) {
					num2 = 1;
				}
				if (num3 > 9) {
					num3 = 1;
				}
			}
		}
	}

	for (int f = 0; f < 50; f++) {
		for (int k = 0; k < 10; k++) {

			next = false;

			do {
				n = Random(2);
				m = Random(2);
				x = Random(2);
				next = true;

				if (m == n) {
					next = false;
				}

			} while(next != true);

			for (int i = 0; i < 9; i++) {
				for (int j = 0; j < 9; j++) {
					iStartNum[i][j] = iFullNum[i][j];
				}
			}

			for (int i = 0; i < 9; i++) {
				if (x == 0) {
					iStartNum[n][i] = iFullNum[m][i];
					iStartNum[m][i] = iFullNum[n][i];
				}
				if (x == 1) {
					iStartNum[n+3][i] = iFullNum[m+3][i];
					iStartNum[m+3][i] = iFullNum[n+3][i];
				}
				if (x == 2) {
					iStartNum[n+6][i] = iFullNum[m+6][i];
					iStartNum[m+6][i] = iFullNum[n+6][i];
				}
			}

			for (int i = 0; i < 9; i++) {
				for (int j = 0; j < 9; j++) {
					iFullNum[i][j] = iStartNum[i][j];
				}
			}
		}

		for (int k = 0; k < 10; k++) {

			next = false;

			do {
				n = Random(2);
				m = Random(2);
				x = Random(2);
				next = true;

				if (m == n) {
					next = false;
				}

			} while(next != true);

			for (int i = 0; i < 9; i++) {
				for (int j = 0; j < 9; j++) {
					iStartNum[i][j] = iFullNum[i][j];
				}
			}

			for (int i = 0; i < 9; i++) {
				if (x == 0) {
					iStartNum[i][n] = iFullNum[i][m];
					iStartNum[i][m] = iFullNum[i][n];
				}
				if (x == 1) {
					iStartNum[i][n+3] = iFullNum[i][m+3];
					iStartNum[i][m+3] = iFullNum[i][n+3];
				}
				if (x == 2) {
					iStartNum[i][n+6] = iFullNum[i][m+6];
					iStartNum[i][m+6] = iFullNum[i][n+6];
				}
			}

			for (int i = 0; i < 9; i++) {
				for (int j = 0; j < 9; j++) {
					iFullNum[i][j] = iStartNum[i][j];
				}
			}
		}
	}

	//скрытие символов
	num = iComplexityConst + dif * 10;

	count = 0;

	do {
		n = Random(9);
		m = Random(9);
		next = false;
		if (iStartNum[n][m] != 0) {
			for (int i = 0; i < 9; i++) {
				for (int j = 0; j < 9; j++) {
					if ((i != n) && (j != m)) {
						if (iStartNum[n][m] == iStartNum[i][j]) {
							next = true;
						}
					}
				}
			}

			if (next == true) {
				iStartNum[n][m] = 0;
				count++;
			}
		}

	} while (count < num);

    for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			iResultNum[i][j] = iStartNum[i][j];
		}
	}
	//
	FillTable(bigtxt);
}
//---------------------------------------------------------------------------
void Tfm::WorkWithTable(int i, int j, String str, bool onlyRead, int txtsize, int color)
{

	//(this->FindComponent("me"+IntToStr((i+1)*10+(j+1))))->Lines->Clear();
	//(this->FindComponent("me"+IntToStr((i+1)*10+(j+1))))->Font->Size = txtsize;
	//if (color == 0) {
	//	(this->FindComponent("me"+IntToStr((i+1)*10+(j+1))))->FontColor = claBlack;
	//}
	//if (color == 1) {
	//	(this->FindComponent("me"+IntToStr((i+1)*10+(j+1))))->FontColor = claBlue;
	//}
	//(this->FindComponent("me"+IntToStr((i+1)*10+(j+1))))->Lines->Add(str);
	//(this->FindComponent("me"+IntToStr((i+1)*10+(j+1))))->ReadOnly = onlyRead;
    if(i == 0 && j == 0) {
		me11->Lines->Clear();
		me11->Font->Size = txtsize;
		if (color == 0) {
			me11->FontColor = claBlack;
		}
		if (color == 1) {
			me11->FontColor = claBlue;
		}
		me11->Lines->Add(str);
		me11->ReadOnly = onlyRead;
	}
	if (i == 0 && j == 1) {
		me12->Lines->Clear();
		me12->Font->Size = txtsize;
		if (color == 0) {
			me12->FontColor = claBlack;
		} else {
			me12->FontColor = claBlue;
		}
		me12->Lines->Add(str);
		me12->ReadOnly = onlyRead;
	}
	if (i == 0 && j == 2) {
		me13->Lines->Clear();
		me13->Font->Size = txtsize;
        if (color == 0) {
			me13->FontColor = claBlack;
		} else {
			me13->FontColor = claBlue;
		}
		me13->Lines->Add(str);
		me13->ReadOnly = onlyRead;
	}
	if (i == 0 && j == 3) {
		me14->Lines->Clear();
		me14->Font->Size = txtsize;
		me14->Lines->Add(str);
		me14->ReadOnly = onlyRead;
	}
	if (i == 0 && j == 4) {
		me15->Lines->Clear();
		me15->Font->Size = txtsize;
        if (color == 0) {
			me15->FontColor = claBlack;
		} else {
			me15->FontColor = claBlue;
		}
		me15->Lines->Add(str);
		me15->ReadOnly = onlyRead;
	}
	if (i == 0 && j == 5) {
		me16->Lines->Clear();
		me16->Font->Size = txtsize;
		if (color == 0) {
			me16->FontColor = claBlack;
		} else {
			me16->FontColor = claBlue;
		}
		me16->Lines->Add(str);
		me16->ReadOnly = onlyRead;
	}
	if (i == 0 && j == 6) {
		me17->Lines->Clear();
		me17->Font->Size = txtsize;
		if (color == 0) {
			me17->FontColor = claBlack;
		} else {
			me17->FontColor = claBlue;
		}
		me17->Lines->Add(str);
		me17->ReadOnly = onlyRead;
	}
	if (i == 0 && j == 7) {
		me18->Lines->Clear();
		me18->Font->Size = txtsize;
		if (color == 0) {
			me18->FontColor = claBlack;
		} else {
			me18->FontColor = claBlue;
		}
		me18->Lines->Add(str);
		me18->ReadOnly = onlyRead;
	}
	if (i == 0 && j == 8) {
		me19->Lines->Clear();
		me19->Font->Size = txtsize;
		if (color == 0) {
			me19->FontColor = claBlack;
		} else {
			me19->FontColor = claBlue;
		}
		me19->Lines->Add(str);
		me19->ReadOnly = onlyRead;
	}
	//////

	if (i == 1 && j == 0) {
		me21->Lines->Clear();
		me21->Font->Size = txtsize;
		if (color == 0) {
			me21->FontColor = claBlack;
		} else {
			me21->FontColor = claBlue;
		}
		me21->Lines->Add(str);
		me21->ReadOnly = onlyRead;
	}
	if (i == 1 && j == 1) {
		me22->Lines->Clear();
		me22->Font->Size = txtsize;
		if (color == 0) {
			me22->FontColor = claBlack;
		} else {
			me22->FontColor = claBlue;
		}
		me22->Lines->Add(str);
		me22->ReadOnly = onlyRead;
	}
	if (i == 1 && j == 2) {
		me23->Lines->Clear();
		me23->Font->Size = txtsize;
        if (color == 0) {
			me23->FontColor = claBlack;
		} else {
			me23->FontColor = claBlue;
		}
		me23->Lines->Add(str);
		me23->ReadOnly = onlyRead;
	}
	if (i == 1 && j == 3) {
		me24->Lines->Clear();
		me24->Font->Size = txtsize;
		if (color == 0) {
			me24->FontColor = claBlack;
		} else {
			me24->FontColor = claBlue;
		}
		me24->Lines->Add(str);
		me24->ReadOnly = onlyRead;
	}
	if (i == 1 && j == 4) {
		me25->Lines->Clear();
		me25->Font->Size = txtsize;
		if (color == 0) {
			me25->FontColor = claBlack;
		} else {
			me25->FontColor = claBlue;
		}
		me25->Lines->Add(str);
		me25->ReadOnly = onlyRead;
	}
	if (i == 1 && j == 5) {
		me26->Lines->Clear();
		me26->Font->Size = txtsize;
		if (color == 0) {
			me26->FontColor = claBlack;
		} else {
			me26->FontColor = claBlue;
		}
		me26->Lines->Add(str);
		me26->ReadOnly = onlyRead;
	}
	if (i == 1 && j == 6) {
		me27->Lines->Clear();
		me27->Font->Size = txtsize;
        if (color == 0) {
			me27->FontColor = claBlack;
		} else {
			me27->FontColor = claBlue;
		}
		me27->Lines->Add(str);
		me27->ReadOnly = onlyRead;
	}
	if (i == 1 && j == 7) {
		me28->Lines->Clear();
		me28->Font->Size = txtsize;
        if (color == 0) {
			me28->FontColor = claBlack;
		} else {
			me28->FontColor = claBlue;
		}
		me28->Lines->Add(str);
		me28->ReadOnly = onlyRead;
	}
	if (i == 1 && j == 8) {
		me29->Lines->Clear();
		me29->Font->Size = txtsize;
        if (color == 0) {
			me29->FontColor = claBlack;
		} else {
			me29->FontColor = claBlue;
		}
		me29->Lines->Add(str);
		me29->ReadOnly = onlyRead;
	}
	//////

	if (i == 2 && j == 0) {
		me31->Lines->Clear();
		me31->Font->Size = txtsize;
		if (color == 0) {
			me31->FontColor = claBlack;
		} else {
			me31->FontColor = claBlue;
		}
		me31->Lines->Add(str);
		me31->ReadOnly = onlyRead;
	}
	if (i == 2 && j == 1) {
		me32->Lines->Clear();
		me32->Font->Size = txtsize;
		if (color == 0) {
			me32->FontColor = claBlack;
		} else {
			me32->FontColor = claBlue;
		}
		me32->Lines->Add(str);
		me32->ReadOnly = onlyRead;
	}
	if (i == 2 && j == 2) {
		me33->Lines->Clear();
		me33->Font->Size = txtsize;
        if (color == 0) {
			me33->FontColor = claBlack;
		} else {
			me33->FontColor = claBlue;
		}
		me33->Lines->Add(str);
		me33->ReadOnly = onlyRead;
	}
	if (i == 2 && j == 3) {
		me34->Lines->Clear();
		me34->Font->Size = txtsize;
        if (color == 0) {
			me34->FontColor = claBlack;
		} else {
			me34->FontColor = claBlue;
		}
		me34->Lines->Add(str);
		me34->ReadOnly = onlyRead;
	}
	if (i == 2 && j == 4) {
		me35->Lines->Clear();
		me35->Font->Size = txtsize;
        if (color == 0) {
			me35->FontColor = claBlack;
		} else {
			me35->FontColor = claBlue;
		}
		me35->Lines->Add(str);
		me35->ReadOnly = onlyRead;
	}
	if (i == 2 && j == 5) {
		me36->Lines->Clear();
		me36->Font->Size = txtsize;
        if (color == 0) {
			me36->FontColor = claBlack;
		} else {
			me36->FontColor = claBlue;
		}
		me36->Lines->Add(str);
		me36->ReadOnly = onlyRead;
	}
	if (i == 2 && j == 6) {
		me37->Lines->Clear();
		me37->Font->Size = txtsize;
        if (color == 0) {
			me37->FontColor = claBlack;
		} else {
			me37->FontColor = claBlue;
		}
		me37->Lines->Add(str);
		me37->ReadOnly = onlyRead;
	}
	if (i == 2 && j == 7) {
		me38->Lines->Clear();
		me38->Font->Size = txtsize;
        if (color == 0) {
			me38->FontColor = claBlack;
		} else {
			me38->FontColor = claBlue;
		}
		me38->Lines->Add(str);
		me38->ReadOnly = onlyRead;
	}
	if (i == 2 && j == 8) {
		me39->Lines->Clear();
		me39->Font->Size = txtsize;
        if (color == 0) {
			me39->FontColor = claBlack;
		} else {
			me39->FontColor = claBlue;
		}
		me39->Lines->Add(str);
		me39->ReadOnly = onlyRead;
	}
	//////

	if (i == 3 && j == 0) {
		me41->Lines->Clear();
		me41->Font->Size = txtsize;
		if (color == 0) {
			me41->FontColor = claBlack;
		} else {
			me41->FontColor = claBlue;
		}
		me41->Lines->Add(str);
		me41->ReadOnly = onlyRead;
	}
	if (i == 3 && j == 1) {
		me42->Lines->Clear();
		me42->Font->Size = txtsize;
        if (color == 0) {
			me42->FontColor = claBlack;
		} else {
			me42->FontColor = claBlue;
		}
		me42->Lines->Add(str);
		me42->ReadOnly = onlyRead;
	}
	if (i == 3 && j == 2) {
		me43->Lines->Clear();
		me43->Font->Size = txtsize;
        if (color == 0) {
			me43->FontColor = claBlack;
		} else {
			me43->FontColor = claBlue;
		}
		me43->Lines->Add(str);
		me43->ReadOnly = onlyRead;
	}
	if (i == 3 && j == 3) {
		me44->Lines->Clear();
		me44->Font->Size = txtsize;
        if (color == 0) {
			me44->FontColor = claBlack;
		} else {
			me44->FontColor = claBlue;
		}
		me44->Lines->Add(str);
		me44->ReadOnly = onlyRead;
	}
	if (i == 3 && j == 4) {
		me45->Lines->Clear();
		me45->Font->Size = txtsize;
        if (color == 0) {
			me45->FontColor = claBlack;
		} else {
			me45->FontColor = claBlue;
		}
		me45->Lines->Add(str);
		me45->ReadOnly = onlyRead;
	}
	if (i == 3 && j == 5) {
		me46->Lines->Clear();
		me46->Font->Size = txtsize;
        if (color == 0) {
			me46->FontColor = claBlack;
		} else {
			me46->FontColor = claBlue;
		}
		me46->Lines->Add(str);
		me46->ReadOnly = onlyRead;
	}
	if (i == 3 && j == 6) {
		me47->Lines->Clear();
		me47->Font->Size = txtsize;
        if (color == 0) {
			me47->FontColor = claBlack;
		} else {
			me47->FontColor = claBlue;
		}
		me47->Lines->Add(str);
		me47->ReadOnly = onlyRead;
	}
	if (i == 3 && j == 7) {
		me48->Lines->Clear();
		me48->Font->Size = txtsize;
        if (color == 0) {
			me48->FontColor = claBlack;
		} else {
			me48->FontColor = claBlue;
		}
		me48->Lines->Add(str);
		me48->ReadOnly = onlyRead;
	}
	if (i == 3 && j == 8) {
		me49->Lines->Clear();
		me49->Font->Size = txtsize;
        if (color == 0) {
			me49->FontColor = claBlack;
		} else {
			me49->FontColor = claBlue;
		}
		me49->Lines->Add(str);
		me49->ReadOnly = onlyRead;
	}


	if (i == 4 && j == 0) {
		me51->Lines->Clear();
		me51->Font->Size = txtsize;
		if (color == 0) {
			me51->FontColor = claBlack;
		} else {
			me51->FontColor = claBlue;
		}
		me51->Lines->Add(str);
		me51->ReadOnly = onlyRead;
	}
	if (i == 4 && j == 1) {
		me52->Lines->Clear();
		me52->Font->Size = txtsize;
        if (color == 0) {
			me52->FontColor = claBlack;
		} else {
			me52->FontColor = claBlue;
		}
		me52->Lines->Add(str);
		me52->ReadOnly = onlyRead;
	}
	if (i == 4 && j == 2) {
		me53->Lines->Clear();
		me53->Font->Size = txtsize;
		if (color == 0) {
			me53->FontColor = claBlack;
		} else {
			me53->FontColor = claBlue;
		}
		me53->Lines->Add(str);
		me53->ReadOnly = onlyRead;
	}
	if (i == 4 && j == 3) {
		me54->Lines->Clear();
		me54->Font->Size = txtsize;
		if (color == 0) {
			me54->FontColor = claBlack;
		} else {
			me54->FontColor = claBlue;
		}
		me54->Lines->Add(str);
		me54->ReadOnly = onlyRead;
	}
	if (i == 4 && j == 4) {
		me55->Lines->Clear();
		me55->Font->Size = txtsize;
        if (color == 0) {
			me55->FontColor = claBlack;
		} else {
			me55->FontColor = claBlue;
		}
		me55->Lines->Add(str);
		me55->ReadOnly = onlyRead;
	}
	if (i == 4 && j == 5) {
		me56->Lines->Clear();
		me56->Font->Size = txtsize;
		if (color == 0) {
			me56->FontColor = claBlack;
		} else {
			me56->FontColor = claBlue;
		}
		me56->Lines->Add(str);
		me56->ReadOnly = onlyRead;
	}
	if (i == 4 && j == 6) {
		me57->Lines->Clear();
		me57->Font->Size = txtsize;
        if (color == 0) {
			me57->FontColor = claBlack;
		} else {
			me57->FontColor = claBlue;
		}
		me57->Lines->Add(str);
		me57->ReadOnly = onlyRead;
	}
	if (i == 4 && j == 7) {
		me58->Lines->Clear();
		me58->Font->Size = txtsize;
		if (color == 0) {
			me58->FontColor = claBlack;
		} else {
			me58->FontColor = claBlue;
		}
		me58->Lines->Add(str);
		me58->ReadOnly = onlyRead;
	}
	if (i == 4 && j == 8) {
		me59->Lines->Clear();
		me59->Font->Size = txtsize;
		if (color == 0) {
			me59->FontColor = claBlack;
		} else {
			me59->FontColor = claBlue;
		}
		me59->Lines->Add(str);
		me59->ReadOnly = onlyRead;
	}
	//////

	if (i == 5 && j == 0) {
		me61->Lines->Clear();
		me61->Font->Size = txtsize;
		if (color == 0) {
			me61->FontColor = claBlack;
		} else {
			me61->FontColor = claBlue;
		}
		me61->Lines->Add(str);
		me61->ReadOnly = onlyRead;
	}
	if (i == 5 && j == 1) {
		me62->Lines->Clear();
		me62->Font->Size = txtsize;
        if (color == 0) {
			me62->FontColor = claBlack;
		} else {
			me62->FontColor = claBlue;
		}
		me62->Lines->Add(str);
		me62->ReadOnly = onlyRead;
	}
	if (i == 5 && j == 2) {
		me63->Lines->Clear();
		me63->Font->Size = txtsize;
		if (color == 0) {
			me63->FontColor = claBlack;
		} else {
			me63->FontColor = claBlue;
		}
		me63->Lines->Add(str);
		me63->ReadOnly = onlyRead;
	}
	if (i == 5 && j == 3) {
		me64->Lines->Clear();
		me64->Font->Size = txtsize;
		if (color == 0) {
			me64->FontColor = claBlack;
		} else {
			me64->FontColor = claBlue;
		}
		me64->Lines->Add(str);
		me64->ReadOnly = onlyRead;
	}
	if (i == 5 && j == 4) {
		me65->Lines->Clear();
		me65->Font->Size = txtsize;
        if (color == 0) {
			me65->FontColor = claBlack;
		} else {
			me65->FontColor = claBlue;
		}
		me65->Lines->Add(str);
		me65->ReadOnly = onlyRead;
	}
	if (i == 5 && j == 5) {
		me66->Lines->Clear();
		me66->Font->Size = txtsize;
        if (color == 0) {
			me66->FontColor = claBlack;
		} else {
			me66->FontColor = claBlue;
		}
		me66->Lines->Add(str);
		me66->ReadOnly = onlyRead;
	}
	if (i == 5 && j == 6) {
		me67->Lines->Clear();
		me67->Font->Size = txtsize;
        if (color == 0) {
			me67->FontColor = claBlack;
		} else {
			me67->FontColor = claBlue;
		}
		me67->Lines->Add(str);
		me67->ReadOnly = onlyRead;
	}
	if (i == 5 && j == 7) {
		me68->Lines->Clear();
		me68->Font->Size = txtsize;
		if (color == 0) {
			me68->FontColor = claBlack;
		} else {
			me68->FontColor = claBlue;
		}
		me68->Lines->Add(str);
		me68->ReadOnly = onlyRead;
	}
	if (i == 5 && j == 8) {
		me69->Lines->Clear();
		me69->Font->Size = txtsize;
        if (color == 0) {
			me69->FontColor = claBlack;
		} else {
			me69->FontColor = claBlue;
		}
		me69->Lines->Add(str);
		me69->ReadOnly = onlyRead;
	}
	//////

	if (i == 6 && j == 0) {
		me71->Lines->Clear();
		me71->Font->Size = txtsize;
		if (color == 0) {
			me71->FontColor = claBlack;
		} else {
			me71->FontColor = claBlue;
		}
		me71->Lines->Add(str);
		me71->ReadOnly = onlyRead;
	}
	if (i == 6 && j == 1) {
		me72->Lines->Clear();
		me72->Font->Size = txtsize;
        if (color == 0) {
			me72->FontColor = claBlack;
		} else {
			me72->FontColor = claBlue;
		}
		me72->Lines->Add(str);
		me72->ReadOnly = onlyRead;
	}
	if (i == 6 && j == 2) {
		me73->Lines->Clear();
		me73->Font->Size = txtsize;
		if (color == 0) {
			me73->FontColor = claBlack;
		} else {
			me73->FontColor = claBlue;
		}
		me73->Lines->Add(str);
		me73->ReadOnly = onlyRead;
	}
	if (i == 6 && j == 3) {
		me74->Lines->Clear();
		me74->Font->Size = txtsize;
		if (color == 0) {
			me74->FontColor = claBlack;
		} else {
			me74->FontColor = claBlue;
		}
		me74->Lines->Add(str);
		me74->ReadOnly = onlyRead;
	}
	if (i == 6 && j == 4) {
		me75->Lines->Clear();
		me75->Font->Size = txtsize;
		if (color == 0) {
			me75->FontColor = claBlack;
		} else {
			me75->FontColor = claBlue;
		}
		me75->Lines->Add(str);
		me75->ReadOnly = onlyRead;
	}
	if (i == 6 && j == 5) {
		me76->Lines->Clear();
		me76->Font->Size = txtsize;
        if (color == 0) {
			me76->FontColor = claBlack;
		} else {
			me76->FontColor = claBlue;
		}
		me76->Lines->Add(str);
		me76->ReadOnly = onlyRead;
	}
	if (i == 6 && j == 6) {
		me77->Lines->Clear();
		me77->Font->Size = txtsize;
		if (color == 0) {
			me77->FontColor = claBlack;
		} else {
			me77->FontColor = claBlue;
		}
		me77->Lines->Add(str);
		me77->ReadOnly = onlyRead;
	}
	if (i == 6 && j == 7) {
		me78->Lines->Clear();
		me78->Font->Size = txtsize;
		if (color == 0) {
			me78->FontColor = claBlack;
		} else {
			me78->FontColor = claBlue;
		}
		me78->Lines->Add(str);
		me78->ReadOnly = onlyRead;
	}
	if (i == 6 && j == 8) {
		me79->Lines->Clear();
		me79->Font->Size = txtsize;
		if (color == 0) {
			me79->FontColor = claBlack;
		} else {
			me79->FontColor = claBlue;
		}
		me79->Lines->Add(str);
		me79->ReadOnly = onlyRead;
	}
	//////

	if (i == 7 && j == 0) {
		me81->Lines->Clear();
		me81->Font->Size = txtsize;
		if (color == 0) {
			me81->FontColor = claBlack;
		} else {
			me81->FontColor = claBlue;
		}
		me81->Lines->Add(str);
		me81->ReadOnly = onlyRead;
	}
	if (i == 7 && j == 1) {
		me82->Lines->Clear();
		me82->Font->Size = txtsize;
		if (color == 0) {
			me82->FontColor = claBlack;
		} else {
			me82->FontColor = claBlue;
		}
		me82->Lines->Add(str);
		me82->ReadOnly = onlyRead;
	}
	if (i == 7 && j == 2) {
		me83->Lines->Clear();
		me83->Font->Size = txtsize;
		if (color == 0) {
			me83->FontColor = claBlack;
		} else {
			me83->FontColor = claBlue;
		}
		me83->Lines->Add(str);
		me83->ReadOnly = onlyRead;
	}
	if (i == 7 && j == 3) {
		me84->Lines->Clear();
		me84->Font->Size = txtsize;
		if (color == 0) {
			me84->FontColor = claBlack;
		} else {
			me84->FontColor = claBlue;
		}
		me84->Lines->Add(str);
		me84->ReadOnly = onlyRead;
	}
	if (i == 7 && j == 4) {
		me85->Lines->Clear();
		me85->Font->Size = txtsize;
		if (color == 0) {
			me85->FontColor = claBlack;
		} else {
			me85->FontColor = claBlue;
		}
		me85->Lines->Add(str);
		me85->ReadOnly = onlyRead;
	}
	if (i == 7 && j == 5) {
		me86->Lines->Clear();
		me86->Font->Size = txtsize;
		if (color == 0) {
			me86->FontColor = claBlack;
		} else {
			me86->FontColor = claBlue;
		}
		me86->Lines->Add(str);
		me86->ReadOnly = onlyRead;
	}
	if (i == 7 && j == 6) {
		me87->Lines->Clear();
		me87->Font->Size = txtsize;
		if (color == 0) {
			me87->FontColor = claBlack;
		} else {
			me87->FontColor = claBlue;
		}
		me87->Lines->Add(str);
		me87->ReadOnly = onlyRead;
	}
	if (i == 7 && j == 7) {
		me88->Lines->Clear();
		me88->Font->Size = txtsize;
        if (color == 0) {
			me88->FontColor = claBlack;
		} else {
			me88->FontColor = claBlue;
		}
		me88->Lines->Add(str);
		me88->ReadOnly = onlyRead;
	}
	if (i == 7 && j == 8) {
		me89->Lines->Clear();
		me89->Font->Size = txtsize;
		if (color == 0) {
			me89->FontColor = claBlack;
		} else {
			me89->FontColor = claBlue;
		}
		me89->Lines->Add(str);
		me89->ReadOnly = onlyRead;
	}
	//////

	if (i == 8 && j == 0) {
		me91->Lines->Clear();
		me91->Font->Size = txtsize;
		if (color == 0) {
			me91->FontColor = claBlack;
		} else {
			me91->FontColor = claBlue;
		}
		me91->Lines->Add(str);
		me91->ReadOnly = onlyRead;
	}
	if (i == 8 && j == 1) {
		me92->Lines->Clear();
		me92->Font->Size = txtsize;
		if (color == 0) {
			me92->FontColor = claBlack;
		} else {
			me92->FontColor = claBlue;
		}
		me92->Lines->Add(str);
		me92->ReadOnly = onlyRead;
	}
	if (i == 8 && j == 2) {
		me93->Lines->Clear();
		me93->Font->Size = txtsize;
		if (color == 0) {
			me93->FontColor = claBlack;
		} else {
			me93->FontColor = claBlue;
		}
		me93->Lines->Add(str);
		me93->ReadOnly = onlyRead;
	}
	if (i == 8 && j == 3) {
		me94->Lines->Clear();
		me94->Font->Size = txtsize;
		if (color == 0) {
			me94->FontColor = claBlack;
		} else {
			me94->FontColor = claBlue;
		}
		me94->Lines->Add(str);
		me94->ReadOnly = onlyRead;
	}
	if (i == 8 && j == 4) {
		me95->Lines->Clear();
		me95->Font->Size = txtsize;
		if (color == 0) {
			me95->FontColor = claBlack;
		} else {
			me95->FontColor = claBlue;
		}
		me95->Lines->Add(str);
		me95->ReadOnly = onlyRead;
	}
	if (i == 8 && j == 5) {
		me96->Lines->Clear();
		me96->Font->Size = txtsize;
		if (color == 0) {
			me96->FontColor = claBlack;
		} else {
			me96->FontColor = claBlue;
		}
		me96->Lines->Add(str);
		me96->ReadOnly = onlyRead;
	}
	if (i == 8 && j == 6) {
		me97->Lines->Clear();
		me97->Font->Size = txtsize;
		if (color == 0) {
			me97->FontColor = claBlack;
		} else {
			me97->FontColor = claBlue;
		}
		me97->Lines->Add(str);
		me97->ReadOnly = onlyRead;
	}
	if (i == 8 && j == 7) {
		me98->Lines->Clear();
		me98->Font->Size = txtsize;
        if (color == 0) {
			me98->FontColor = claBlack;
		} else {
			me98->FontColor = claBlue;
		}
		me98->Lines->Add(str);
		me98->ReadOnly = onlyRead;
	}
	if (i == 8 && j == 8) {
		me99->Lines->Clear();
		me99->Font->Size = txtsize;
		if (color == 0) {
			me99->FontColor = claBlack;
		} else {
			me99->FontColor = claBlue;
		}
		me99->Lines->Add(str);
		me99->ReadOnly = onlyRead;
	}
}
//---------------------------------------------------------------------------
void Tfm::FillTable(int txtsize)
{
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			if (iStartNum[i][j] == 0) {
				WorkWithTable(i, j, "", true, txtsize, 1);
			} else {
				WorkWithTable(i, j, iStartNum[i][j], true, txtsize, 0);
			}
		}
	}

    if (bTimerOn == true) {
			FTimeStart = Now();
			tm->Enabled = true;
			laTime->Visible = true;
	}
}
//---------------------------------------------------------------------------
void __fastcall Tfm::meTableAllClick(TObject *Sender)
{
	meXnow = ((TControl *)Sender)->Tag/10;
	meYnow = ((TControl *)Sender)->Tag%10;
	choseitem = true;
}
//---------------------------------------------------------------------------

void __fastcall Tfm::buResRestartClick(TObject *Sender)
{
	FillTable(bigtxt);

	tc->ActiveTab = tiGame;
}
//---------------------------------------------------------------------------

void __fastcall Tfm::tmTimer(TObject *Sender)
{
	DateTimeToString(xTime, L"h:nn:ss.zzz", Now() - FTimeStart);
	laTime->Text = xTime.Delete(xTime.Length()- 2, 2);
}
//---------------------------------------------------------------------------

