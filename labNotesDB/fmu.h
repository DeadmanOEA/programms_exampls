//---------------------------------------------------------------------------

#ifndef fmuH
#define fmuH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <FMX.Controls.hpp>
#include <FMX.Forms.hpp>
#include <FMX.Controls.Presentation.hpp>
#include <FMX.Edit.hpp>
#include <FMX.Layouts.hpp>
#include <FMX.ListView.Adapters.Base.hpp>
#include <FMX.ListView.Appearances.hpp>
#include <FMX.ListView.hpp>
#include <FMX.ListView.Types.hpp>
#include <FMX.Memo.hpp>
#include <FMX.ScrollBox.hpp>
#include <FMX.StdCtrls.hpp>
#include <FMX.TabControl.hpp>
#include <FMX.Types.hpp>
#include <Data.Bind.Components.hpp>
#include <Data.Bind.DBScope.hpp>
#include <Data.Bind.EngExt.hpp>
#include <Fmx.Bind.DBEngExt.hpp>
#include <Fmx.Bind.Editors.hpp>
#include <System.Bindings.Outputs.hpp>
#include <System.Rtti.hpp>
//---------------------------------------------------------------------------
class Tfm : public TForm
{
__published:	// IDE-managed Components
	TToolBar *ToolBar1;
	TButton *buAbout;
	TLabel *Label1;
	TTabControl *tc;
	TTabItem *tiList;
	TTabItem *tiItem;
	TToolBar *ToolBar2;
	TButton *buAdd;
	TListView *lv;
	TLayout *Layout1;
	TLabel *Label2;
	TLabel *Label3;
	TLabel *Label4;
	TEdit *edCaption;
	TTrackBar *tbPriority;
	TMemo *meDetail;
	TToolBar *ToolBar3;
	TButton *buSave;
	TButton *buCancel;
	TButton *buDelete;
	TBindSourceDB *BindSourceDB1;
	TBindingsList *BindingsList1;
	TLinkListControlToField *LinkListControlToField1;
	TLinkControlToField *LinkControlToField1;
	TLinkControlToField *LinkControlToField2;
	TLinkControlToField *LinkControlToField3;
	void __fastcall buAboutClick(TObject *Sender);
	void __fastcall buAddClick(TObject *Sender);
	void __fastcall buSaveClick(TObject *Sender);
	void __fastcall buCancelClick(TObject *Sender);
	void __fastcall buDeleteClick(TObject *Sender);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall lvItemClick(TObject * const Sender, TListViewItem * const AItem);

private:	// User declarations
public:		// User declarations
	__fastcall Tfm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE Tfm *fm;
//---------------------------------------------------------------------------
#endif
