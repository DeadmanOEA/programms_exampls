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
#include <Fmx.Bind.DBEngExt.hpp>
#include <Fmx.Bind.Editors.hpp>
#include <Fmx.Bind.Grid.hpp>
#include <FMX.Controls.Presentation.hpp>
#include <FMX.Grid.hpp>
#include <FMX.Grid.Style.hpp>
#include <FMX.ListView.Adapters.Base.hpp>
#include <FMX.ListView.Appearances.hpp>
#include <FMX.ListView.hpp>
#include <FMX.ListView.Types.hpp>
#include <FMX.ScrollBox.hpp>
#include <FMX.Types.hpp>
#include <System.Bindings.Outputs.hpp>
#include <System.Rtti.hpp>
#include <FMX.TabControl.hpp>
#include <FMX.Layouts.hpp>
#include <FMX.StdCtrls.hpp>
//---------------------------------------------------------------------------
class Tfm : public TForm
{
__published:	// IDE-managed Components
	TBindSourceDB *BindSourceDB1;
	TBindingsList *BindingsList1;
	TListView *ListView1;
	TLinkListControlToField *LinkListControlToField1;
	TListView *ListView2;
	TBindSourceDB *BindSourceDB2;
	TLinkListControlToField *LinkListControlToField2;
	TListView *ListView3;
	TBindSourceDB *BindSourceDB3;
	TLinkListControlToField *LinkListControlToField3;
	TTabControl *tc;
	TTabItem *tiMenu;
	TTabItem *tiCat;
	TTabItem *tiProd;
	TTabItem *tiFeedback;
	TToolBar *ToolBar1;
	TTabItem *tiFeedC;
	TButton *buAbout;
	TLabel *Label1;
	TGridPanelLayout *GridPanelLayout1;
	TButton *buCateg;
	TButton *buFeedback;
	TToolBar *ToolBar2;
	TButton *Button1;
	TToolBar *ToolBar3;
	TButton *Button2;
	TToolBar *ToolBar4;
	TButton *Button3;
	TButton *buAdd;
	TButton *buCorz;
	void __fastcall buCategClick(TObject *Sender);
	void __fastcall buFeedbackClick(TObject *Sender);
	void __fastcall buAboutClick(TObject *Sender);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall ListView1ItemClick(TObject * const Sender, TListViewItem * const AItem);

private:	// User declarations
public:		// User declarations
	__fastcall Tfm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE Tfm *fm;
//---------------------------------------------------------------------------
#endif
