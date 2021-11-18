//---------------------------------------------------------------------------

#ifndef dmuH
#define dmuH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Data.DB.hpp>
#include <FireDAC.Comp.Client.hpp>
#include <FireDAC.FMXUI.Wait.hpp>
#include <FireDAC.Phys.FB.hpp>
#include <FireDAC.Phys.FBDef.hpp>
#include <FireDAC.Phys.hpp>
#include <FireDAC.Phys.Intf.hpp>
#include <FireDAC.Stan.Async.hpp>
#include <FireDAC.Stan.Def.hpp>
#include <FireDAC.Stan.Error.hpp>
#include <FireDAC.Stan.Intf.hpp>
#include <FireDAC.Stan.Option.hpp>
#include <FireDAC.Stan.Pool.hpp>
#include <FireDAC.UI.Intf.hpp>
#include <FireDAC.Comp.DataSet.hpp>
#include <FireDAC.DApt.hpp>
#include <FireDAC.DApt.Intf.hpp>
#include <FireDAC.DatS.hpp>
#include <FireDAC.Stan.Param.hpp>
#include <FireDAC.UI.Intf.hpp>
//---------------------------------------------------------------------------
class Tdm : public TDataModule
{
__published:	// IDE-managed Components
	TFDConnection *FDConnection;
	TFDQuery *quCategory;
	TFDQuery *quProduct;
	TIntegerField *quProductID;
	TIntegerField *quProductCATEGORY_ID;
	TWideStringField *quProductNAME;
	TBlobField *quProductIMAGE;
	TIntegerField *quProductGRAM;
	TIntegerField *quProductKCAL;
	TFloatField *quProductPRICE;
	TWideStringField *quProductNOTE;
	TIntegerField *quProductSTICKER;
	TWideStringField *quCategoryNAME;
	TIntegerField *quCategorySORT_INDEX;
	TIntegerField *quCategoryID;
	TFDQuery *FDQuery1;
	TFDStoredProc *spFeedbackIns;
	void __fastcall quCategoryAfterScroll(TDataSet *DataSet);
private:	// User declarations
public:		// User declarations
	__fastcall Tdm(TComponent* Owner);
    void FeedbackIns(UnicodeString aFio, UnicodeString aEmail, UnicodeString aNote);
};
//---------------------------------------------------------------------------
extern PACKAGE Tdm *dm;
//---------------------------------------------------------------------------
#endif
