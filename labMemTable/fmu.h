//---------------------------------------------------------------------------

#ifndef fmuH
#define fmuH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <FMX.Controls.hpp>
#include <FMX.Forms.hpp>
#include <Data.Bind.Components.hpp>
#include <Data.Bind.DBScope.hpp>
#include <Data.Bind.EngExt.hpp>
#include <Data.Bind.Grid.hpp>
#include <Data.DB.hpp>
#include <FireDAC.Comp.Client.hpp>
#include <FireDAC.Comp.DataSet.hpp>
#include <FireDAC.DApt.Intf.hpp>
#include <FireDAC.DatS.hpp>
#include <FireDAC.Phys.Intf.hpp>
#include <FireDAC.Stan.Error.hpp>
#include <FireDAC.Stan.Intf.hpp>
#include <FireDAC.Stan.Option.hpp>
#include <FireDAC.Stan.Param.hpp>
#include <Fmx.Bind.DBEngExt.hpp>
#include <Fmx.Bind.Editors.hpp>
#include <Fmx.Bind.Grid.hpp>
#include <FMX.Controls.Presentation.hpp>
#include <FMX.Grid.hpp>
#include <FMX.Grid.Style.hpp>
#include <FMX.ScrollBox.hpp>
#include <FMX.Types.hpp>
#include <System.Bindings.Outputs.hpp>
#include <System.Rtti.hpp>
#include <Data.Bind.Controls.hpp>
#include <Fmx.Bind.Navigator.hpp>
#include <FMX.Layouts.hpp>
#include <FireDAC.Stan.StorageBin.hpp>
#include <FMX.Edit.hpp>
#include <FMX.StdCtrls.hpp>
#include <System.IOUtils.hpp>
#include <FireDAC.Stan.StorageJSON.hpp>
#include <FMX.Memo.hpp>
//---------------------------------------------------------------------------
class Tfm : public TForm
{
__published:	// IDE-managed Components
	TFDMemTable *ta;
	TStringField *taFIO;
	TStringField *taPhone;
	TSmallintField *taAge;
	TCurrencyField *taMoney;
	TGrid *Grid1;
	TBindSourceDB *BindSourceDB1;
	TBindingsList *BindingsList1;
	TLinkGridToDataSource *LinkGridToDataSourceBindSourceDB1;
	TEdit *Edit1;
	TEdit *Edit2;
	TEdit *Edit3;
	TEdit *Edit4;
	TButton *buSave;
	TButton *buCancel;
	TLinkControlToField *LinkControlToField1;
	TLinkControlToField *LinkControlToField2;
	TLinkControlToField *LinkControlToField3;
	TLinkControlToField *LinkControlToField4;
	TBindNavigator *NavigatorBindSourceDB1;
	TEdit *edFilter;
	TButton *buFilterOn;
	TButton *buFilterOff;
	TButton *buAddAge1;
	TButton *buAddAllMoney;
	TCheckBox *ckReadOnlyGrid;
	TCheckBox *ckReadOnlyTableChange;
	TEdit *edL;
	TButton *buLocate;
	TButton *buLookup;
	TButton *buGetAllMoney;
	TButton *buMin;
	TEdit *edFileName;
	TButton *buSaveTable;
	TButton *buLoadTable;
	TFDStanStorageJSONLink *FDStanStorageJSONLink1;
	TMemo *Memo1;
	void __fastcall buSaveClick(TObject *Sender);
	void __fastcall buCancelClick(TObject *Sender);
	void __fastcall buFilterOnClick(TObject *Sender);
	void __fastcall buFilterOffClick(TObject *Sender);
	void __fastcall buAddAge1Click(TObject *Sender);
	void __fastcall buAddAllMoneyClick(TObject *Sender);

	void __fastcall ckReadOnlyTableChangeChange(TObject *Sender);
	void __fastcall ckReadOnlyGridChange(TObject *Sender);
	void __fastcall buLocateClick(TObject *Sender);
	void __fastcall buLookupClick(TObject *Sender);
	void __fastcall buGetAllMoneyClick(TObject *Sender);
	void __fastcall buMinClick(TObject *Sender);
	void __fastcall buSaveTableClick(TObject *Sender);
	void __fastcall buLoadTableClick(TObject *Sender);
	void __fastcall taAfterScroll(TDataSet *DataSet);
	void __fastcall taBeforeScroll(TDataSet *DataSet);
private:	// User declarations
public:		// User declarations
	__fastcall Tfm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE Tfm *fm;
//---------------------------------------------------------------------------
#endif
