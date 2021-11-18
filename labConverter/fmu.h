//---------------------------------------------------------------------------

#ifndef fmuH
#define fmuH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <FMX.Controls.hpp>
#include <FMX.Forms.hpp>
#include <FMX.Controls.Presentation.hpp>
#include <FMX.Layouts.hpp>
#include <FMX.StdCtrls.hpp>
#include <FMX.TabControl.hpp>
#include <FMX.Types.hpp>
#include <FMX.Edit.hpp>
#include <FMX.ListBox.hpp>
//---------------------------------------------------------------------------
class Tfm : public TForm
{
__published:	// IDE-managed Components
	TLayout *Layout1;
	TLabel *Label1;
	TButton *buBack;
	TButton *buAbout;
	TTabControl *tc;
	TTabItem *tiMenu;
	TTabItem *tiTime;
	TTabItem *tiDistance;
	TTabItem *tiQl;
	TTabItem *tiTemperature;
	TGridPanelLayout *GridPanelLayout1;
	TButton *buTime;
	TButton *buDistance;
	TButton *buQuantitiesInfo;
	TButton *buTemperature;
	TListBox *ListBox1;
	TListBoxItem *ListBoxItem1;
	TListBoxItem *ListBoxItem2;
	TListBoxItem *ListBoxItem3;
	TListBoxItem *ListBoxItem4;
	TListBoxItem *ListBoxItem5;
	TListBoxItem *ListBoxItem6;
	TEdit *edMs;
	TEdit *edSec;
	TEdit *edMinutes;
	TEdit *edHours;
	TEdit *edDays;
	TEdit *edYears;
	TListBox *ListBox2;
	TListBoxItem *ListBoxItem7;
	TEdit *edNm;
	TListBoxItem *ListBoxItem8;
	TEdit *edMkm;
	TListBoxItem *ListBoxItem9;
	TEdit *edMm;
	TListBoxItem *ListBoxItem10;
	TEdit *edSm;
	TListBoxItem *ListBoxItem11;
	TEdit *edDm;
	TListBoxItem *ListBoxItem12;
	TEdit *Edm;
	TListBox *ListBox3;
	TListBoxItem *ListBoxItem13;
	TEdit *edKbi;
	TListBoxItem *ListBoxItem14;
	TEdit *edKba;
	TListBoxItem *ListBoxItem15;
	TEdit *edMbi;
	TListBoxItem *ListBoxItem16;
	TEdit *edMba;
	TListBoxItem *ListBoxItem17;
	TEdit *edGbi;
	TListBoxItem *ListBoxItem18;
	TEdit *edGba;
	TListBox *ListBox4;
	TListBoxItem *ListBoxItem19;
	TEdit *edC;
	TListBoxItem *ListBoxItem20;
	TEdit *edF;
	TListBoxItem *ListBoxItem21;
	TEdit *edK;
	TListBoxItem *ListBoxItem22;
	TListBoxItem *ListBoxItem23;
	TListBoxItem *ListBoxItem24;
	TEdit *edD;
	TEdit *edRa;
	TEdit *edN;
	void __fastcall edTimeAllKeyUp(TObject *Sender, WORD &Key, System::WideChar &KeyChar,
          TShiftState Shift);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall tcChange(TObject *Sender);
	void __fastcall buTimeClick(TObject *Sender);
	void __fastcall buDistanceClick(TObject *Sender);
	void __fastcall buQuantitiesInfoClick(TObject *Sender);
	void __fastcall buTemperatureClick(TObject *Sender);
	void __fastcall edDistanceAllKeyUp(TObject *Sender, WORD &Key, System::WideChar &KeyChar,
          TShiftState Shift);
	void __fastcall edQIAllKeyUp(TObject *Sender, WORD &Key, System::WideChar &KeyChar,
          TShiftState Shift);
	void __fastcall edTempAllKeyUp(TObject *Sender, WORD &Key, System::WideChar &KeyChar,
          TShiftState Shift);
	void __fastcall buBackClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall Tfm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE Tfm *fm;
//---------------------------------------------------------------------------
#endif
