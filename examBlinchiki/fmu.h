//---------------------------------------------------------------------------

#ifndef fmuH
#define fmuH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <FMX.Controls.hpp>
#include <FMX.Forms.hpp>
#include <FMX.Controls.Presentation.hpp>
#include <FMX.StdCtrls.hpp>
#include <FMX.Types.hpp>
#include <FMX.Layouts.hpp>
#include <FMX.Objects.hpp>
#include <FMX.TabControl.hpp>
#include <Data.Bind.Components.hpp>
#include <Data.Bind.DBScope.hpp>
#include <Data.Bind.EngExt.hpp>
#include <Fmx.Bind.DBEngExt.hpp>
#include <Fmx.Bind.Editors.hpp>
#include <FMX.ListView.Adapters.Base.hpp>
#include <FMX.ListView.Appearances.hpp>
#include <FMX.ListView.hpp>
#include <FMX.ListView.Types.hpp>
#include <System.Bindings.Outputs.hpp>
#include <System.Rtti.hpp>
#include <FMX.Edit.hpp>
#include <FMX.Memo.hpp>
#include <FMX.ScrollBox.hpp>
//---------------------------------------------------------------------------
class Tfm : public TForm
{
__published:	// IDE-managed Components
	TToolBar *ToolBar1;
	TLabel *Label1;
	TButton *buAbout;
	TTabControl *tc;
	TTabItem *tiMenu;
	TTabItem *tiCateg;
	TTabItem *tiProd;
	TTabItem *tiBucket;
	TTabItem *tiContacts;
	TTabItem *tiCallBack;
	TTabItem *tiCalls;
	TImage *imMain;
	TGridPanelLayout *GridPanelLayout1;
	TButton *buOrder;
	TButton *buVict;
	TButton *buCallB;
	TButton *buBucket;
	TButton *buDost;
	TButton *buTheme;
	TButton *buCont;
	TStyleBook *StyleBook1;
	TStyleBook *StyleBook2;
	TTabItem *tiDost;
	TTabItem *tiVict;
	TToolBar *ToolBar2;
	TListView *ListView1;
	TBindSourceDB *BindSourceDB1;
	TBindingsList *BindingsList1;
	TLinkListControlToField *LinkListControlToField1;
	TButton *buBackCat;
	TToolBar *ToolBar3;
	TButton *buBackProdList;
	TListView *ListView2;
	TBindSourceDB *BindSourceDB2;
	TLinkListControlToField *LinkListControlToField2;
	TTabItem *tiGood;
	TImage *Image1;
	TGridPanelLayout *GridPanelLayout2;
	TButton *buFastBuy;
	TButton *buBackListOfGoods;
	TGridPanelLayout *GridPanelLayout3;
	TLabel *Label2;
	TButton *Button1;
	TButton *Button2;
	TButton *buBucketAdd;
	TLabel *laName;
	TGridPanelLayout *GridPanelLayout4;
	TLabel *Label3;
	TLabel *laWeight;
	TLabel *Label6;
	TLabel *laKKall;
	TLabel *Label8;
	TLabel *laPrice;
	TBindSourceDB *BindSourceDB3;
	TBindSourceDB *BindSourceDB4;
	TLinkPropertyToField *LinkPropertyToFieldText;
	TLinkPropertyToField *LinkPropertyToFieldText2;
	TLinkPropertyToField *LinkPropertyToFieldText3;
	TLinkPropertyToField *LinkPropertyToFieldBitmap;
	TLinkPropertyToField *LinkPropertyToFieldText4;
	TMemo *meOpisanie;
	TLinkControlToField *LinkControlToField1;
	TLabel *laNum;
	TToolBar *ToolBar4;
	TButton *Button3;
	TLabel *Label4;
	TToolBar *ToolBar5;
	TButton *Button4;
	TLabel *Label5;
	TImage *Image2;
	TButton *buBegin;
	TTabItem *TabItem1;
	TTabItem *tiRes;
	TToolBar *ToolBar6;
	TButton *Button5;
	TToolBar *ToolBar7;
	TButton *Button6;
	TToolBar *ToolBar8;
	TButton *Button7;
	TToolBar *ToolBar9;
	TButton *Button8;
	TLabel *Label7;
	TImage *imVictor;
	TButton *bu1;
	TButton *bu2;
	TButton *bu3;
	TButton *bu4;
	TButton *bu5;
	TBindSourceDB *BindSourceDB5;
	TLinkPropertyToField *LinkPropertyToFieldText5;
	TLinkPropertyToField *LinkPropertyToFieldText6;
	TLinkPropertyToField *LinkPropertyToFieldText7;
	TLinkPropertyToField *LinkPropertyToFieldBitmap2;
	TLinkPropertyToField *LinkPropertyToFieldText8;
	TLinkPropertyToField *LinkPropertyToFieldText9;
	TImage *Image3;
	TButton *Button9;
	TLabel *Label9;
	TListView *ListView3;
	TButton *buAddCall;
	TToolBar *ToolBar10;
	TButton *Button10;
	TButton *buAddNewCall;
	TGridPanelLayout *GridPanelLayout5;
	TLabel *Label10;
	TEdit *edFIO;
	TLabel *Label11;
	TEdit *edMail;
	TLabel *Label12;
	TMemo *meCall;
	TButton *buMakeOrder;
	TTabItem *tiAddOrd;
	TToolBar *ToolBar11;
	TButton *Button11;
	TButton *Button12;
	void __fastcall buAboutClick(TObject *Sender);
	void __fastcall buThemeClick(TObject *Sender);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall buContClick(TObject *Sender);
	void __fastcall buDostClick(TObject *Sender);
	void __fastcall buCallBClick(TObject *Sender);
	void __fastcall buBucketClick(TObject *Sender);
	void __fastcall buVictClick(TObject *Sender);
	void __fastcall buOrderClick(TObject *Sender);
	void __fastcall buBackCatClick(TObject *Sender);
	void __fastcall tiProdClick(TObject *Sender);
	void __fastcall ListView1ItemClick(TObject * const Sender, TListViewItem * const AItem);
	void __fastcall ListView2ItemClick(TObject * const Sender, TListViewItem * const AItem);
	void __fastcall buBackListOfGoodsClick(TObject *Sender);
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall buBucketAddClick(TObject *Sender);
	void __fastcall buFastBuyClick(TObject *Sender);
	void __fastcall bu1Click(TObject *Sender);
	void __fastcall buBeginClick(TObject *Sender);
	void __fastcall Button9Click(TObject *Sender);
	void __fastcall buAddCallClick(TObject *Sender);
	void __fastcall buAddNewCallClick(TObject *Sender);
	void __fastcall buMakeOrderClick(TObject *Sender);
	void __fastcall Button12Click(TObject *Sender);
	void __fastcall Button11Click(TObject *Sender);


private:	// User declarations
    int numOfGood;
public:		// User declarations
	__fastcall Tfm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE Tfm *fm;
//---------------------------------------------------------------------------
#endif
