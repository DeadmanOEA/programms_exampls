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
#include <FMX.Memo.hpp>
#include <FMX.Objects.hpp>
#include <FMX.ScrollBox.hpp>
#include <FMX.StdCtrls.hpp>
#include <FMX.Types.hpp>
#include <FMX.ActnList.hpp>
#include <IdBaseComponent.hpp>
#include <IdComponent.hpp>
#include <IdTCPClient.hpp>
#include <IdTCPConnection.hpp>
#include <System.Actions.hpp>
//---------------------------------------------------------------------------
class Tfm : public TForm
{
__published:	// IDE-managed Components
	TLayout *Layout1;
	TMemo *me;
	TEdit *edHost;
	TEdit *edPort;
	TButton *buConnect;
	TButton *buDisconnect;
	TButton *buTime;
	TButton *buStr;
	TButton *buImage;
	TImage *im;
	TIdTCPClient *IdTCPClient;
	TActionList *al;
	TAction *acConnect;
	TAction *acDisconnect;
	TAction *acGetTime;
	TAction *acGetStr;
	TAction *acGetImage;
	TButton *buInf;
	TAction *acServerInfo;
	TButton *buGIndex;
	TAction *acGIndex;
	void __fastcall acConnectExecute(TObject *Sender);
	void __fastcall acDisconnectExecute(TObject *Sender);
	void __fastcall acGetTimeExecute(TObject *Sender);
	void __fastcall acGetStrExecute(TObject *Sender);
	void __fastcall acGetImageExecute(TObject *Sender);
	void __fastcall alUpdate(TBasicAction *Action, bool &Handled);
	void __fastcall acServerInfoExecute(TObject *Sender);
	void __fastcall acGIndexExecute(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall Tfm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE Tfm *fm;
//---------------------------------------------------------------------------
#endif
