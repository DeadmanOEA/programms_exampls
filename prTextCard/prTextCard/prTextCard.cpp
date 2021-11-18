
// prTextCard.cpp : Определяет поведение классов для приложения.
//

#include "stdafx.h"
#include "prTextCard.h"
#include "prTextCardDlg.h"
#include "MashCard.h"
#include "afxwin.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#import <RxInventor.tlb> \
rename_namespace("InventorNative") \
named_guids raw_dispinterfaces \
high_method_prefix("Method") \
rename("DeleteFile", "APIDeleteFile") \
rename("CopyFile", "APICopyFile") \
rename("MoveFile", "APIMoveFile") \
rename("SetEnvironmentVariable", "APISetEnvironmentVariable") \
rename("GetObject", "APIGetObject") \
exclude("_FILETIME", "IStream", "ISequentialStream", \
"_LARGE_INTEGER", "_ULARGE_INTEGER", "tagSTATSTG", \
"IEnumUnknown", "IPersistFile", "IPersist", "IPictureDisp")

using namespace InventorNative;

CComPtr<Application> pInvApp;

InventorNative::AssemblyDocumentPtr pASDoc;
InventorNative::AssemblyComponentDefinitionPtr pAsmComDef;
InventorNative::TransientGeometry *pTransGeomAsm;
InventorNative::Matrix *oPositionMatrix;

InventorNative::DrawingDocumentPtr pDrawDoc;
InventorNative::TransientGeometry *pTransGeom;
InventorNative::Transaction *pTrans;

InventorNative::Sheet *sheet;
TransactionManagerPtr pTransManager;

Document *Doc;

SheetsPtr sh;
// CprTextCardApp

BEGIN_MESSAGE_MAP(CprTextCardApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// создание CprTextCardApp

CprTextCardApp::CprTextCardApp()
{
	// поддержка диспетчера перезагрузки
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;

	// TODO: добавьте код создания,
	// Размещает весь важный код инициализации в InitInstance
}

// Единственный объект CprTextCardApp

CprTextCardApp theApp;

// инициализация CprTextCardApp

BOOL CprTextCardApp::InitInstance()
{
	// InitCommonControlsEx() требуется для Windows XP, если манифест
	// приложения использует ComCtl32.dll версии 6 или более поздней версии для включения
	// стилей отображения.  В противном случае будет возникать сбой при создании любого окна.
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// Выберите этот параметр для включения всех общих классов управления, которые необходимо использовать
	// в вашем приложении.
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();


	AfxEnableControlContainer();

	// Создать диспетчер оболочки, в случае, если диалоговое окно содержит
	// представление дерева оболочки или какие-либо его элементы управления.
	CShellManager *pShellManager = new CShellManager;

	// Активация визуального диспетчера "Классический Windows" для включения элементов управления MFC
	CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));

	// Стандартная инициализация
	// Если эти возможности не используются и необходимо уменьшить размер
	// конечного исполняемого файла, необходимо удалить из следующих
	// конкретных процедур инициализации, которые не требуются
	// Измените раздел реестра, в котором хранятся параметры
	// TODO: следует изменить эту строку на что-нибудь подходящее,
	// например на название организации
	SetRegistryKey(_T("Локальные приложения, созданные с помощью мастера приложений"));

	CprTextCardDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Введите код для обработки закрытия диалогового окна
		//  с помощью кнопки "ОК"
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Введите код для обработки закрытия диалогового окна
		//  с помощью кнопки "Отмена"
	}
	else if (nResponse == -1)
	{
		TRACE(traceAppMsg, 0, "Предупреждение. Не удалось создать диалоговое окно, поэтому работа приложения неожиданно завершена.\n");
		TRACE(traceAppMsg, 0, "Предупреждение. При использовании элементов управления MFC для диалогового окна невозможно #define _AFX_NO_MFC_CONTROLS_IN_DIALOGS.\n");
	}

	// Удалить диспетчер оболочки, созданный выше.
	if (pShellManager != NULL)
	{
		delete pShellManager;
	}

	// Поскольку диалоговое окно закрыто, возвратите значение FALSE, чтобы можно было выйти из
	//  приложения вместо запуска генератора сообщений приложения.
	return FALSE;
}

void CprTextCardApp::MakeDocF(_bstr_t strTemplateFilename)
{
	pDrawDoc = pInvApp->Documents->MethodAdd(kDrawingDocumentObject, strTemplateFilename, true);//создание файла

	pDrawDoc->DisplayName = _T("MarshCard");//имя файла

	pDrawDoc->get_Sheets(&sh);//создание листа
							  //подготовка к работе с документом

	pInvApp->get_TransientGeometry(&pTransGeom);

	pTransManager = pInvApp->GetTransactionManager();

	Doc = CComQIPtr <Document>(pDrawDoc);

	pTransManager->raw_StartTransaction(Doc, _T(""), &pTrans);
}

void CprTextCardApp::MakeSq(double fx, double fy, int orient)
{
	double x[8];//координата х
	double y[8];//координата у

				//расчет дополнительных точек блока
	if (orient != 0) {
		x[0] = fx;//вверх лево
		y[0] = fy;

		x[1] = fx + 4;//вверх право
		y[1] = fy;

		x[2] = fx + 4;//низ право
		y[2] = fy - 0.9;

		x[3] = fx;//низ лево
		y[3] = fy - 0.9;

		x[4] = fx;//центр лево
		y[4] = fy - 0.45;

		x[5] = fx + 4;//центр право
		y[5] = fy - 0.45;

		x[6] = fx + 2.2;//раздел вверх
		y[6] = fy - 0.45;

		x[7] = fx + 2.2;//раздел низ
		y[7] = fy - 0.9;
	}
	else {
		x[0] = fx;//вверх лево
		y[0] = fy;

		x[1] = fx + 0.9;//вверх право
		y[1] = fy;

		x[2] = fx + 0.9;//низ право
		y[2] = fy - 4;

		x[3] = fx;//низ лево
		y[3] = fy - 4;

		x[4] = fx + 0.45;//центр лево
		y[4] = fy;

		x[5] = fx + 0.45;//центр право
		y[5] = fy - 4;

		x[6] = fx + 0.45;//раздел вверх
		y[6] = fy - 0.8;

		x[7] = fx + 0.9;//раздел низ
		y[7] = fy - 0.8;
	}

	SheetPtr sheet = sh->GetItem(1);//создание указателя на лист

	DrawingSketchPtr sk = sheet->GetSketches()->MethodAdd();//добавление эскиза на лист

	sk->raw_Edit();//начало редактирования эскиза

	SketchLinesPtr pSketchLines;

	sk->get_SketchLines(&pSketchLines);//создание указателя на коллекцию линий

	Point2dPtr poi[8];//переменная для хранения точек

	for (int i = 0; i < 8; i++) {//задаем точки бокса
		poi[i] = pTransGeom->MethodCreatePoint2d(x[i], y[i]);
	}

	for (int i = 0; i < 4; i++) {

		if (i < 3) {
			pSketchLines->MethodAddByTwoPoints(poi[i], poi[i + 1]);
		}
		else {
			pSketchLines->MethodAddByTwoPoints(poi[i], poi[0]);
		}

	}

	//создание линий внутри бокса

	pSketchLines->MethodAddByTwoPoints(poi[4], poi[5]);
	pSketchLines->MethodAddByTwoPoints(poi[6], poi[7]);

	sk->raw_ExitEdit();//закрытие редактирования чертежа

}

void CprTextCardApp::MakeLn(double fx, double fy, double sx, double sy)
{
	SheetPtr sheet = sh->GetItem(1);//создание указателя на лист

	DrawingSketchPtr sk = sheet->GetSketches()->MethodAdd();//добавление эскиза на лист

	sk->raw_Edit();//начало редактирования эскиза

	SketchLinesPtr pSketchLines;

	sk->get_SketchLines(&pSketchLines);//создание указателя на коллекцию линий

	Point2dPtr poi[2];//переменная для хранения точек

	poi[0] = pTransGeom->MethodCreatePoint2d(fx, fy);
	poi[1] = pTransGeom->MethodCreatePoint2d(sx, sy);

	pSketchLines->MethodAddByTwoPoints(poi[0], poi[1]);

	sk->raw_ExitEdit();//закрытие редактирования чертежа
}

void CprTextCardApp::AddText(double x, double y, _bstr_t text, _bstr_t position, _bstr_t num, int orient)
{
	double xText[3];
	double yText[3];

	if (orient != 0) {
		xText[0] = x + 0.05;
		yText[0] = y - 0.05;

		xText[1] = x + 0.05;
		yText[1] = y - 0.5;

		xText[2] = x + 2.25;
		yText[2] = y - 0.5;
	}
	else {
		xText[0] = x + 0.05;
		yText[0] = y - 2.95;

		xText[1] = x + 0.5;
		yText[1] = y - 2.95;

		xText[2] = x + 0.5;
		yText[2] = y - 0.75;
	}

	SheetPtr sheet = sh->GetItem(1);//создание указателя на лист

	DrawingSketchPtr sk = sheet->GetSketches()->MethodAdd();//добавление эскиза на лист

	sk->raw_Edit();//начало редактирования эскиза

	Point2dPtr poi[3];//переменная для хранения точек
	TextBoxPtr tb[3];

	for (int i = 0; i < 3; i++) {
		poi[i] = pTransGeom->MethodCreatePoint2d(xText[i], yText[i]);
	}

	tb[0] = sk->TextBoxes->MethodAddFitted(poi[0], text);
	tb[1] = sk->TextBoxes->MethodAddFitted(poi[1], position);
	tb[2] = sk->TextBoxes->MethodAddFitted(poi[2], num);

	if (orient == 0) {
		tb[0]->put_Rotation(1.57079633);
		tb[1]->put_Rotation(1.57079633);
		tb[2]->put_Rotation(1.57079633);
	}

	sk->raw_ExitEdit();//закрытие редактирования чертежа
}

void CprTextCardApp::MakeMark(double x, double y, _bstr_t text, int orient, int t)
{
	double xText[3];
	double yText[3];
	if (t == 1) {
		xText[0] = x;
		yText[0] = y;

		xText[1] = x - 0.5;
		yText[1] = y + 0.7;

		xText[2] = x - 3;
		yText[2] = y + 1.05;
	}
	else {
		if (orient == 0) {
			xText[0] = x;
			yText[0] = y;

			xText[1] = x + 0.5;
			yText[1] = y - 0.7;

			xText[2] = x + 1;
			yText[2] = y - 0.5;
		}
		else {
			xText[0] = x;
			yText[0] = y;

			xText[1] = x + 0.5;
			yText[1] = y + 0.7;

			xText[2] = x + 0.5;
			yText[2] = y + 1;
		}
	}

	SheetPtr sheet = sh->GetItem(1);//создание указателя на лист

	DrawingSketchPtr sk = sheet->GetSketches()->MethodAdd();//добавление эскиза на лист

	sk->raw_Edit();//начало редактирования эскиза

	Point2dPtr poi[3];//переменная для хранения точек
	TextBoxPtr tb[1];

	for (int i = 0; i < 3; i++) {
		poi[i] = pTransGeom->MethodCreatePoint2d(xText[i], yText[i]);
	}

	tb[0] = sk->TextBoxes->MethodAddFitted(poi[2], text);

	if (orient == 0) {
		tb[0]->put_Rotation(4.71238899);
	}

	SketchLinesPtr pSketchLines;

	sk->get_SketchLines(&pSketchLines);//создание указателя на коллекцию линий

	pSketchLines->MethodAddByTwoPoints(poi[0], poi[1]);

	sk->raw_ExitEdit();//закрытие редактирования чертежа
}

void CprTextCardApp::OpenInventor()
{
	BeginWaitCursor();

	// Get hold of the program id of Inventor.
	CLSID InvAppClsid;
	HRESULT hRes = CLSIDFromProgID(L"Inventor.Application", &InvAppClsid);
	if (FAILED(hRes)) {
		pInvApp = nullptr;
		return;// ReturnAndShowCOMError(hRes, L"ConnectToInventor,CLSIDFromProgID failed");
	}

	// See if Inventor is already running...
	CComPtr<IUnknown> pInvAppUnk = nullptr;
	hRes = ::GetActiveObject(InvAppClsid, NULL, &pInvAppUnk);
	if (FAILED(hRes)) {
		// Inventor is not already running, so try to start it...
		TRACE(L"Could not get hold of an active Inventor, will start a new session\n");
		hRes = CoCreateInstance(InvAppClsid, NULL, CLSCTX_LOCAL_SERVER, __uuidof(IUnknown), (void **)&pInvAppUnk);
		if (FAILED(hRes)) {
			pInvApp = nullptr;
			return;// ReturnAndShowCOMError(hRes, L"ConnectToInventor,CoCreateInstance failed");
		}
	}

	// Get the pointer to the Inventor application...
	hRes = pInvAppUnk->QueryInterface(__uuidof(Application), (void **)&pInvApp);
	if (FAILED(hRes)) {
		return;// ReturnAndShowCOMError(hRes, L"ConnectToInventor,QueryInterface failed");
	}

	pInvApp->put_Visible(TRUE);
}

void CprTextCardApp::OpenBOM(_bstr_t strTemplateFilenameBOM)
{
	int findBom;
	CprTextCardApp* pApp = (CprTextCardApp *)AfxGetApp();

	pASDoc = pInvApp->Documents->MethodOpen(strTemplateFilenameBOM, FALSE);
	pASDoc->get_ComponentDefinition(&pAsmComDef);
	pInvApp->get_TransientGeometry(&pTransGeomAsm);
	pTransGeomAsm->raw_CreateMatrix(&oPositionMatrix);

	BOMPtr pBOM;
	pAsmComDef->get_BOM(&pBOM);

	BOMViewsPtr pBOMViews;
	pBOM->get_BOMViews(&pBOMViews);
	long iNumBomViews;
	pBOMViews->get_Count(&iNumBomViews);
	findBom = 0;
	for (long bv = 1; bv <= iNumBomViews; bv++) {

		CComVariant varNum(bv);

		BOMViewPtr pBOMView;

		pBOMViews->get_Item(varNum, &pBOMView);

		BOMRowsEnumeratorPtr BomRows;

		pBOMView->get_BOMRows(&BomRows);

		// Look at each row in the bom
		for (long iRow = 1; iRow <= BomRows->Count; iRow++) {

			BOMRowPtr ThisBomRow;

			BomRows->get_Item(iRow, &ThisBomRow);

			// Of this row, what is the component? Usually there is only one...

			ComponentDefinitionsEnumeratorPtr pDefinitionsEnum;

			ThisBomRow->get_ComponentDefinitions(&pDefinitionsEnum);

			// ...assuming there is only one I get the first

			ComponentDefinitionPtr pCompDef;

			pDefinitionsEnum->get_Item(1, &pCompDef);

			// Get the definition of the part listed in this BOM row

			PartComponentDefinitionPtr pPartCompDef;

			AssemblyComponentDefinitionPtr pAssCompDef;

			pPartCompDef = pCompDef;

			pAssCompDef = pCompDef;

			_bstr_t y;

			y = ThisBomRow->GetItemNumber();

			if (findBom == 0) {
				if (CString(y.GetBSTR()) != L"") {
					CprTextCardApp* pApp = (CprTextCardApp *)AfxGetApp();

					pApp->csItemNumber.Add(CString(y.GetBSTR()));
						
					long z = ThisBomRow->GetItemQuantity();

					CString str;
					str.Format(L"%d", z);

					pApp->csItemQuantity.Add(str);

					DocumentPtr pDocument;

					HRESULT hRes; 

					if (pPartCompDef == NULL) {
						hRes = pAssCompDef->get_Document((IDispatch**)&pDocument);
					}
					else {
						hRes = pPartCompDef->get_Document((IDispatch**)&pDocument);
					}

					CComBSTR bstrPartName;

					hRes = pDocument->get_DisplayName(&bstrPartName);
						
					pApp->csPartName.Add(CString(bstrPartName));
				}
			}
		}

		if (pApp->csPartName.GetCount() != 0) {
			findBom = 1;
		}
	}
}

//MK
void CprTextCardApp::MakeSqMK() {
	MakeTxt(1.1, 14.15, L"01");
	MakeTxt(1.1, 13.3, L"02");
	MakeTxt(1.1, 12.45, L"03");
	MakeTxt(1.1, 11.6, L"04");
	MakeTxt(1.1, 10.75, L"05");
	MakeTxt(1.1, 9.9, L"06");
	MakeTxt(1.1, 9.05, L"07");
	MakeTxt(1.1, 8.2, L"08");
	MakeTxt(1.1, 7.35, L"09");
	MakeTxt(1.1, 6.5, L"10");
	MakeTxt(1.1, 5.65, L"11");
	MakeTxt(1.1, 4.8, L"12");
	MakeTxt(1.1, 3.95, L"13");
	MakeTxt(1.1, 3.1, L"14");
	MakeTxt(1.1, 2.25, L"15");
	MakeTxt(1.1, 1.4, L"16");

	SheetPtr sheet = sh->GetItem(1);//создание указателя на лист
	sheet->MethodUpdate();;
	sheet->Border->MethodDelete();
	sheet->TitleBlock->MethodDelete();
	sheet->put_Size(kCustomDrawingSheetSize);
	sheet->put_Height(21);
	sheet->put_Width(29.7);
	SketchedSymbolsPtr ss;

	DrawingSketchPtr sk = sheet->GetSketches()->MethodAdd();//добавление эскиза на лист

	sk->raw_Edit();//начало редактирования эскиза
	SketchLinesPtr pSketchLines;
	sk->get_SketchLines(&pSketchLines);//создание указателя на коллекцию линий

	Point2dPtr poiline[1000];//переменная для хранения точек
	TextBoxPtr tb[300];//переменная для хранения точек текста

					   /*Рамка*/
	poiline[0] = pTransGeom->MethodCreatePoint2d(0, 0);
	poiline[1] = pTransGeom->MethodCreatePoint2d(0, 21);
	poiline[2] = pTransGeom->MethodCreatePoint2d(29.7, 21);
	poiline[3] = pTransGeom->MethodCreatePoint2d(29.7, 0);

	pSketchLines->MethodAddByTwoPoints(poiline[0], poiline[1]);
	pSketchLines->MethodAddByTwoPoints(poiline[1], poiline[2]);
	pSketchLines->MethodAddByTwoPoints(poiline[2], poiline[3]);
	pSketchLines->MethodAddByTwoPoints(poiline[3], poiline[0]);

	/*Б6ф1*/
	poiline[4] = pTransGeom->MethodCreatePoint2d(0.55, 0.85);
	poiline[5] = pTransGeom->MethodCreatePoint2d(29.15, 0.85);

	pSketchLines->MethodAddByTwoPoints(poiline[4], poiline[5]);

	/*Таблица*/
	poiline[6] = pTransGeom->MethodCreatePoint2d(0.55, 0);
	poiline[7] = pTransGeom->MethodCreatePoint2d(29.15, 0);
	poiline[8] = pTransGeom->MethodCreatePoint2d(0.55, 15.725);
	poiline[9] = pTransGeom->MethodCreatePoint2d(29.15, 15.725);

	pSketchLines->MethodAddByTwoPoints(poiline[6], poiline[8]);
	pSketchLines->MethodAddByTwoPoints(poiline[7], poiline[9]);
	pSketchLines->MethodAddByTwoPoints(poiline[8], poiline[9]);

	/*Строки и столбцы в таблице*/
	poiline[10] = pTransGeom->MethodCreatePoint2d(0.55, 1.7);
	poiline[11] = pTransGeom->MethodCreatePoint2d(29.15, 1.7);
	poiline[12] = pTransGeom->MethodCreatePoint2d(0.55, 2.55);
	poiline[13] = pTransGeom->MethodCreatePoint2d(29.15, 2.55);
	poiline[14] = pTransGeom->MethodCreatePoint2d(0.55, 3.4);
	poiline[15] = pTransGeom->MethodCreatePoint2d(29.15, 3.4);
	poiline[16] = pTransGeom->MethodCreatePoint2d(0.55, 4.25);
	poiline[17] = pTransGeom->MethodCreatePoint2d(29.15, 4.25);
	poiline[18] = pTransGeom->MethodCreatePoint2d(0.55, 5.1);
	poiline[19] = pTransGeom->MethodCreatePoint2d(29.15, 5.1);
	poiline[20] = pTransGeom->MethodCreatePoint2d(0.55, 5.95);
	poiline[21] = pTransGeom->MethodCreatePoint2d(29.15, 5.95);
	poiline[22] = pTransGeom->MethodCreatePoint2d(0.55, 6.8);
	poiline[23] = pTransGeom->MethodCreatePoint2d(29.15, 6.8);
	poiline[24] = pTransGeom->MethodCreatePoint2d(0.55, 7.65);
	poiline[25] = pTransGeom->MethodCreatePoint2d(29.15, 7.65);
	poiline[26] = pTransGeom->MethodCreatePoint2d(0.55, 8.5);
	poiline[27] = pTransGeom->MethodCreatePoint2d(29.15, 8.5);
	poiline[28] = pTransGeom->MethodCreatePoint2d(0.55, 9.35);
	poiline[29] = pTransGeom->MethodCreatePoint2d(29.15, 9.35);
	poiline[30] = pTransGeom->MethodCreatePoint2d(0.55, 10.2);
	poiline[31] = pTransGeom->MethodCreatePoint2d(29.15, 10.2);
	poiline[32] = pTransGeom->MethodCreatePoint2d(0.55, 11.05);
	poiline[33] = pTransGeom->MethodCreatePoint2d(29.15, 11.05);
	poiline[34] = pTransGeom->MethodCreatePoint2d(0.55, 11.9);
	poiline[35] = pTransGeom->MethodCreatePoint2d(29.15, 11.9);
	poiline[36] = pTransGeom->MethodCreatePoint2d(0.55, 12.75);
	poiline[37] = pTransGeom->MethodCreatePoint2d(29.15, 12.75);
	poiline[38] = pTransGeom->MethodCreatePoint2d(0.55, 13.6);
	poiline[39] = pTransGeom->MethodCreatePoint2d(29.15, 13.6);
	poiline[40] = pTransGeom->MethodCreatePoint2d(0.55, 14.45);
	poiline[41] = pTransGeom->MethodCreatePoint2d(29.15, 14.45);
	poiline[42] = pTransGeom->MethodCreatePoint2d(0.55, 14.875);
	poiline[43] = pTransGeom->MethodCreatePoint2d(29.15, 14.875);
	poiline[44] = pTransGeom->MethodCreatePoint2d(0.55, 15.3);
	poiline[45] = pTransGeom->MethodCreatePoint2d(29.15, 15.3);
	poiline[46] = pTransGeom->MethodCreatePoint2d(1.85, 0.85);
	poiline[47] = pTransGeom->MethodCreatePoint2d(1.85, 15.725);
	poiline[48] = pTransGeom->MethodCreatePoint2d(2.89, 15.725);
	poiline[49] = pTransGeom->MethodCreatePoint2d(2.89, 15.3);
	poiline[50] = pTransGeom->MethodCreatePoint2d(3.93, 15.725);
	poiline[51] = pTransGeom->MethodCreatePoint2d(3.93, 15.3);
	poiline[52] = pTransGeom->MethodCreatePoint2d(4.97, 15.725);
	poiline[53] = pTransGeom->MethodCreatePoint2d(4.97, 15.3);
	poiline[54] = pTransGeom->MethodCreatePoint2d(6.27, 15.725);
	poiline[55] = pTransGeom->MethodCreatePoint2d(6.27, 15.3);
	poiline[56] = pTransGeom->MethodCreatePoint2d(13.81, 15.725);
	poiline[57] = pTransGeom->MethodCreatePoint2d(13.81, 14.45);
	poiline[58] = pTransGeom->MethodCreatePoint2d(14.85, 15.3);
	poiline[59] = pTransGeom->MethodCreatePoint2d(14.85, 14.875);
	poiline[60] = pTransGeom->MethodCreatePoint2d(16.67, 15.3);
	poiline[61] = pTransGeom->MethodCreatePoint2d(16.67, 14.875);
	poiline[62] = pTransGeom->MethodCreatePoint2d(17.71, 15.3);
	poiline[63] = pTransGeom->MethodCreatePoint2d(17.71, 14.875);
	poiline[64] = pTransGeom->MethodCreatePoint2d(19.01, 15.3);
	poiline[65] = pTransGeom->MethodCreatePoint2d(19.01, 14.875);
	poiline[66] = pTransGeom->MethodCreatePoint2d(20.05, 15.3);
	poiline[67] = pTransGeom->MethodCreatePoint2d(20.05, 14.875);
	poiline[68] = pTransGeom->MethodCreatePoint2d(21.35, 15.3);
	poiline[69] = pTransGeom->MethodCreatePoint2d(21.35, 14.45);
	poiline[70] = pTransGeom->MethodCreatePoint2d(22.65, 15.3);
	poiline[71] = pTransGeom->MethodCreatePoint2d(22.65, 14.45);
	poiline[72] = pTransGeom->MethodCreatePoint2d(23.95, 15.3);
	poiline[73] = pTransGeom->MethodCreatePoint2d(23.95, 14.45);
	poiline[74] = pTransGeom->MethodCreatePoint2d(25.25, 15.3);
	poiline[75] = pTransGeom->MethodCreatePoint2d(25.25, 14.45);
	poiline[76] = pTransGeom->MethodCreatePoint2d(27.07, 15.3);
	poiline[77] = pTransGeom->MethodCreatePoint2d(27.07, 14.45);

	pSketchLines->MethodAddByTwoPoints(poiline[10], poiline[11]);
	pSketchLines->MethodAddByTwoPoints(poiline[12], poiline[13]);
	pSketchLines->MethodAddByTwoPoints(poiline[14], poiline[15]);
	pSketchLines->MethodAddByTwoPoints(poiline[16], poiline[17]);
	pSketchLines->MethodAddByTwoPoints(poiline[18], poiline[19]);
	pSketchLines->MethodAddByTwoPoints(poiline[20], poiline[21]);
	pSketchLines->MethodAddByTwoPoints(poiline[22], poiline[23]);
	pSketchLines->MethodAddByTwoPoints(poiline[24], poiline[25]);
	pSketchLines->MethodAddByTwoPoints(poiline[26], poiline[27]);
	pSketchLines->MethodAddByTwoPoints(poiline[28], poiline[29]);
	pSketchLines->MethodAddByTwoPoints(poiline[30], poiline[31]);
	pSketchLines->MethodAddByTwoPoints(poiline[32], poiline[33]);
	pSketchLines->MethodAddByTwoPoints(poiline[34], poiline[35]);
	pSketchLines->MethodAddByTwoPoints(poiline[36], poiline[37]);
	pSketchLines->MethodAddByTwoPoints(poiline[38], poiline[39]);
	pSketchLines->MethodAddByTwoPoints(poiline[40], poiline[41]);
	pSketchLines->MethodAddByTwoPoints(poiline[42], poiline[43]);
	pSketchLines->MethodAddByTwoPoints(poiline[44], poiline[45]);
	pSketchLines->MethodAddByTwoPoints(poiline[46], poiline[47]);
	pSketchLines->MethodAddByTwoPoints(poiline[48], poiline[49]);
	pSketchLines->MethodAddByTwoPoints(poiline[50], poiline[51]);
	pSketchLines->MethodAddByTwoPoints(poiline[52], poiline[53]);
	pSketchLines->MethodAddByTwoPoints(poiline[54], poiline[55]);
	pSketchLines->MethodAddByTwoPoints(poiline[56], poiline[57]);
	pSketchLines->MethodAddByTwoPoints(poiline[58], poiline[59]);
	pSketchLines->MethodAddByTwoPoints(poiline[60], poiline[61]);
	pSketchLines->MethodAddByTwoPoints(poiline[62], poiline[63]);
	pSketchLines->MethodAddByTwoPoints(poiline[64], poiline[65]);
	pSketchLines->MethodAddByTwoPoints(poiline[66], poiline[67]);
	pSketchLines->MethodAddByTwoPoints(poiline[68], poiline[69]);
	pSketchLines->MethodAddByTwoPoints(poiline[70], poiline[71]);
	pSketchLines->MethodAddByTwoPoints(poiline[72], poiline[73]);
	pSketchLines->MethodAddByTwoPoints(poiline[74], poiline[75]);
	pSketchLines->MethodAddByTwoPoints(poiline[76], poiline[77]);

	/*Б2Ф2*/
	poiline[78] = pTransGeom->MethodCreatePoint2d(0.55, 15.725);
	poiline[79] = pTransGeom->MethodCreatePoint2d(0.55, 17.85);
	poiline[80] = pTransGeom->MethodCreatePoint2d(10.17, 17.85);
	poiline[81] = pTransGeom->MethodCreatePoint2d(10.17, 15.725);
	poiline[82] = pTransGeom->MethodCreatePoint2d(2.89, 15.725);
	poiline[83] = pTransGeom->MethodCreatePoint2d(2.89, 17.85);
	poiline[84] = pTransGeom->MethodCreatePoint2d(6.53, 15.725);
	poiline[85] = pTransGeom->MethodCreatePoint2d(6.53, 17.85);
	poiline[86] = pTransGeom->MethodCreatePoint2d(8.61, 15.725);
	poiline[87] = pTransGeom->MethodCreatePoint2d(8.61, 17.85);
	poiline[88] = pTransGeom->MethodCreatePoint2d(0.55, 17.425);
	poiline[89] = pTransGeom->MethodCreatePoint2d(10.17, 17.425);
	poiline[90] = pTransGeom->MethodCreatePoint2d(0.55, 17);
	poiline[91] = pTransGeom->MethodCreatePoint2d(10.17, 17);
	poiline[92] = pTransGeom->MethodCreatePoint2d(0.55, 16.15);
	poiline[93] = pTransGeom->MethodCreatePoint2d(10.17, 16.15);
	poiline[94] = pTransGeom->MethodCreatePoint2d(0.55, 16.575);
	poiline[95] = pTransGeom->MethodCreatePoint2d(10.17, 16.575);

	pSketchLines->MethodAddByTwoPoints(poiline[78], poiline[79]);
	pSketchLines->MethodAddByTwoPoints(poiline[79], poiline[80]);
	pSketchLines->MethodAddByTwoPoints(poiline[80], poiline[81]);
	pSketchLines->MethodAddByTwoPoints(poiline[82], poiline[83]);
	pSketchLines->MethodAddByTwoPoints(poiline[84], poiline[85]);
	pSketchLines->MethodAddByTwoPoints(poiline[86], poiline[87]);
	pSketchLines->MethodAddByTwoPoints(poiline[88], poiline[89]);
	pSketchLines->MethodAddByTwoPoints(poiline[90], poiline[91]);
	pSketchLines->MethodAddByTwoPoints(poiline[92], poiline[93]);
	pSketchLines->MethodAddByTwoPoints(poiline[94], poiline[95]);

	/*Б1Ф2*/
	poiline[96] = pTransGeom->MethodCreatePoint2d(10.17, 17.85);
	poiline[97] = pTransGeom->MethodCreatePoint2d(29.15, 17.85);
	poiline[98] = pTransGeom->MethodCreatePoint2d(29.15, 14.875);
	poiline[99] = pTransGeom->MethodCreatePoint2d(29.15, 16.575);
	poiline[100] = pTransGeom->MethodCreatePoint2d(10.17, 16.575);
	poiline[101] = pTransGeom->MethodCreatePoint2d(14.33, 17.85);
	poiline[102] = pTransGeom->MethodCreatePoint2d(14.33, 16.575);
	poiline[103] = pTransGeom->MethodCreatePoint2d(20.31, 17.85);
	poiline[104] = pTransGeom->MethodCreatePoint2d(20.31, 16.575);
	poiline[105] = pTransGeom->MethodCreatePoint2d(24.47, 17.85);
	poiline[106] = pTransGeom->MethodCreatePoint2d(24.47, 16.575);
	poiline[107] = pTransGeom->MethodCreatePoint2d(26.03, 16.575);
	poiline[108] = pTransGeom->MethodCreatePoint2d(26.03, 15.725);
	poiline[109] = pTransGeom->MethodCreatePoint2d(27.07, 16.575);
	poiline[110] = pTransGeom->MethodCreatePoint2d(27.07, 15.725);
	poiline[111] = pTransGeom->MethodCreatePoint2d(28.11, 16.575);
	poiline[112] = pTransGeom->MethodCreatePoint2d(28.11, 15.725);
	poiline[113] = pTransGeom->MethodCreatePoint2d(11.47, 16.575);
	poiline[114] = pTransGeom->MethodCreatePoint2d(11.47, 16.15);

	pSketchLines->MethodAddByTwoPoints(poiline[96], poiline[97]);
	pSketchLines->MethodAddByTwoPoints(poiline[97], poiline[98]);
	pSketchLines->MethodAddByTwoPoints(poiline[99], poiline[100]);
	pSketchLines->MethodAddByTwoPoints(poiline[101], poiline[102]);
	pSketchLines->MethodAddByTwoPoints(poiline[103], poiline[104]);
	pSketchLines->MethodAddByTwoPoints(poiline[105], poiline[106]);
	pSketchLines->MethodAddByTwoPoints(poiline[107], poiline[108]);
	pSketchLines->MethodAddByTwoPoints(poiline[109], poiline[110]);
	pSketchLines->MethodAddByTwoPoints(poiline[111], poiline[112]);
	pSketchLines->MethodAddByTwoPoints(poiline[113], poiline[114]);

	/*Б5Ф2*/
	poiline[115] = pTransGeom->MethodCreatePoint2d(0.55, 17.85);
	poiline[116] = pTransGeom->MethodCreatePoint2d(0.55, 18.7);
	poiline[117] = pTransGeom->MethodCreatePoint2d(29.15, 18.7);
	poiline[118] = pTransGeom->MethodCreatePoint2d(29.15, 17.85);
	poiline[119] = pTransGeom->MethodCreatePoint2d(15.37, 18.7);
	poiline[120] = pTransGeom->MethodCreatePoint2d(15.37, 18.5);
	poiline[121] = pTransGeom->MethodCreatePoint2d(21.35, 18.7);
	poiline[122] = pTransGeom->MethodCreatePoint2d(21.35, 17.85);
	poiline[123] = pTransGeom->MethodCreatePoint2d(26.03, 18.7);
	poiline[124] = pTransGeom->MethodCreatePoint2d(26.03, 17.85);
	poiline[125] = pTransGeom->MethodCreatePoint2d(27.59, 18.7);
	poiline[126] = pTransGeom->MethodCreatePoint2d(27.59, 17.85);

	pSketchLines->MethodAddByTwoPoints(poiline[115], poiline[116]);
	pSketchLines->MethodAddByTwoPoints(poiline[116], poiline[117]);
	pSketchLines->MethodAddByTwoPoints(poiline[117], poiline[118]);
	pSketchLines->MethodAddByTwoPoints(poiline[119], poiline[120]);
	pSketchLines->MethodAddByTwoPoints(poiline[121], poiline[122]);
	pSketchLines->MethodAddByTwoPoints(poiline[123], poiline[124]);
	pSketchLines->MethodAddByTwoPoints(poiline[125], poiline[126]);

	/*Б4Ф2*/
	poiline[127] = pTransGeom->MethodCreatePoint2d(0.55, 18.7);
	poiline[128] = pTransGeom->MethodCreatePoint2d(0.55, 19.975);
	poiline[129] = pTransGeom->MethodCreatePoint2d(8.09, 19.975);
	poiline[130] = pTransGeom->MethodCreatePoint2d(8.09, 18.7);
	poiline[131] = pTransGeom->MethodCreatePoint2d(2.37, 19.975);
	poiline[132] = pTransGeom->MethodCreatePoint2d(2.37, 18.7);
	poiline[133] = pTransGeom->MethodCreatePoint2d(4.45, 19.975);
	poiline[134] = pTransGeom->MethodCreatePoint2d(4.45, 18.7);
	poiline[135] = pTransGeom->MethodCreatePoint2d(6.53, 19.975);
	poiline[136] = pTransGeom->MethodCreatePoint2d(6.53, 18.7);
	poiline[137] = pTransGeom->MethodCreatePoint2d(0.55, 19.55);
	poiline[138] = pTransGeom->MethodCreatePoint2d(8.09, 19.55);
	poiline[139] = pTransGeom->MethodCreatePoint2d(0.55, 19.125);
	poiline[140] = pTransGeom->MethodCreatePoint2d(8.09, 19.125);

	pSketchLines->MethodAddByTwoPoints(poiline[127], poiline[128]);
	pSketchLines->MethodAddByTwoPoints(poiline[128], poiline[129]);
	pSketchLines->MethodAddByTwoPoints(poiline[129], poiline[130]);
	pSketchLines->MethodAddByTwoPoints(poiline[131], poiline[132]);
	pSketchLines->MethodAddByTwoPoints(poiline[133], poiline[134]);
	pSketchLines->MethodAddByTwoPoints(poiline[135], poiline[136]);
	pSketchLines->MethodAddByTwoPoints(poiline[137], poiline[138]);
	pSketchLines->MethodAddByTwoPoints(poiline[139], poiline[140]);

	/*Б3Ф1а*/
	poiline[141] = pTransGeom->MethodCreatePoint2d(21.09, 18.7);
	poiline[142] = pTransGeom->MethodCreatePoint2d(21.09, 20.4);
	poiline[143] = pTransGeom->MethodCreatePoint2d(29.15, 20.4);
	poiline[144] = pTransGeom->MethodCreatePoint2d(29.15, 18.7);
	poiline[145] = pTransGeom->MethodCreatePoint2d(21.09, 19.975);
	poiline[146] = pTransGeom->MethodCreatePoint2d(29.15, 19.975);
	poiline[147] = pTransGeom->MethodCreatePoint2d(21.09, 19.55);
	poiline[148] = pTransGeom->MethodCreatePoint2d(29.15, 19.55);
	poiline[149] = pTransGeom->MethodCreatePoint2d(21.09, 19.125);
	poiline[150] = pTransGeom->MethodCreatePoint2d(29.15, 19.125);
	poiline[151] = pTransGeom->MethodCreatePoint2d(22.13, 20.4);
	poiline[152] = pTransGeom->MethodCreatePoint2d(22.13, 18.7);
	poiline[153] = pTransGeom->MethodCreatePoint2d(23.17, 20.4);
	poiline[154] = pTransGeom->MethodCreatePoint2d(23.17, 18.7);
	poiline[155] = pTransGeom->MethodCreatePoint2d(25.51, 20.4);
	poiline[156] = pTransGeom->MethodCreatePoint2d(25.51, 18.7);
	poiline[157] = pTransGeom->MethodCreatePoint2d(27.59, 20.4);
	poiline[158] = pTransGeom->MethodCreatePoint2d(27.59, 18.7);

	pSketchLines->MethodAddByTwoPoints(poiline[141], poiline[142]);
	pSketchLines->MethodAddByTwoPoints(poiline[142], poiline[143]);
	pSketchLines->MethodAddByTwoPoints(poiline[143], poiline[144]);
	pSketchLines->MethodAddByTwoPoints(poiline[145], poiline[146]);
	pSketchLines->MethodAddByTwoPoints(poiline[147], poiline[148]);
	pSketchLines->MethodAddByTwoPoints(poiline[149], poiline[150]);
	pSketchLines->MethodAddByTwoPoints(poiline[151], poiline[152]);
	pSketchLines->MethodAddByTwoPoints(poiline[153], poiline[154]);
	pSketchLines->MethodAddByTwoPoints(poiline[155], poiline[156]);
	pSketchLines->MethodAddByTwoPoints(poiline[157], poiline[158]);

	/*Б3Ф2в*/
	poiline[159] = pTransGeom->MethodCreatePoint2d(13.03, 18.7);
	poiline[160] = pTransGeom->MethodCreatePoint2d(13.03, 19.55);
	poiline[161] = pTransGeom->MethodCreatePoint2d(21.09, 19.55);
	poiline[162] = pTransGeom->MethodCreatePoint2d(14.07, 18.7);
	poiline[163] = pTransGeom->MethodCreatePoint2d(14.07, 19.55);
	poiline[164] = pTransGeom->MethodCreatePoint2d(15.11, 18.7);
	poiline[165] = pTransGeom->MethodCreatePoint2d(15.11, 19.55);
	poiline[166] = pTransGeom->MethodCreatePoint2d(17.45, 18.7);
	poiline[167] = pTransGeom->MethodCreatePoint2d(17.45, 19.55);
	poiline[168] = pTransGeom->MethodCreatePoint2d(19.53, 18.7);
	poiline[169] = pTransGeom->MethodCreatePoint2d(19.53, 19.55);
	poiline[170] = pTransGeom->MethodCreatePoint2d(13.03, 19.125);
	poiline[171] = pTransGeom->MethodCreatePoint2d(21.09, 19.125);

	pSketchLines->MethodAddByTwoPoints(poiline[159], poiline[160]);
	pSketchLines->MethodAddByTwoPoints(poiline[160], poiline[161]);
	pSketchLines->MethodAddByTwoPoints(poiline[162], poiline[163]);
	pSketchLines->MethodAddByTwoPoints(poiline[164], poiline[165]);
	pSketchLines->MethodAddByTwoPoints(poiline[166], poiline[167]);
	pSketchLines->MethodAddByTwoPoints(poiline[168], poiline[169]);
	pSketchLines->MethodAddByTwoPoints(poiline[170], poiline[171]);

	/*Б6Ф2*/
	poiline[172] = pTransGeom->MethodCreatePoint2d(2.89, 0.85);
	poiline[173] = pTransGeom->MethodCreatePoint2d(2.89, 0);
	pSketchLines->MethodAddByTwoPoints(poiline[172], poiline[173]);

	/*2мм линии внутри таблицы*/
	poiline[244] = pTransGeom->MethodCreatePoint2d(2.89, 11.9);
	poiline[245] = pTransGeom->MethodCreatePoint2d(2.89, 11.7);
	poiline[246] = pTransGeom->MethodCreatePoint2d(2.89, 11.05);
	poiline[247] = pTransGeom->MethodCreatePoint2d(2.89, 10.85);
	poiline[248] = pTransGeom->MethodCreatePoint2d(2.89, 10.2);
	poiline[249] = pTransGeom->MethodCreatePoint2d(2.89, 10);
	poiline[250] = pTransGeom->MethodCreatePoint2d(2.89, 9.35);
	poiline[251] = pTransGeom->MethodCreatePoint2d(2.89, 9.15);
	poiline[252] = pTransGeom->MethodCreatePoint2d(2.89, 8.5);
	poiline[253] = pTransGeom->MethodCreatePoint2d(2.89, 8.3);
	poiline[254] = pTransGeom->MethodCreatePoint2d(2.89, 7.65);
	poiline[255] = pTransGeom->MethodCreatePoint2d(2.89, 7.45);
	poiline[256] = pTransGeom->MethodCreatePoint2d(2.89, 6.8);
	poiline[257] = pTransGeom->MethodCreatePoint2d(2.89, 6.6);
	poiline[258] = pTransGeom->MethodCreatePoint2d(2.89, 5.95);
	poiline[259] = pTransGeom->MethodCreatePoint2d(2.89, 5.75);
	poiline[260] = pTransGeom->MethodCreatePoint2d(2.89, 5.1);
	poiline[261] = pTransGeom->MethodCreatePoint2d(2.89, 4.9);
	poiline[262] = pTransGeom->MethodCreatePoint2d(2.89, 4.25);
	poiline[263] = pTransGeom->MethodCreatePoint2d(2.89, 4.05);
	poiline[264] = pTransGeom->MethodCreatePoint2d(2.89, 3.4);
	poiline[265] = pTransGeom->MethodCreatePoint2d(2.89, 3.2);
	poiline[266] = pTransGeom->MethodCreatePoint2d(2.89, 2.55);
	poiline[267] = pTransGeom->MethodCreatePoint2d(2.89, 2.35);
	poiline[268] = pTransGeom->MethodCreatePoint2d(2.89, 1.7);
	poiline[269] = pTransGeom->MethodCreatePoint2d(2.89, 1.5);
	poiline[270] = pTransGeom->MethodCreatePoint2d(3.93, 11.9);
	poiline[271] = pTransGeom->MethodCreatePoint2d(3.93, 11.7);
	poiline[272] = pTransGeom->MethodCreatePoint2d(3.93, 11.05);
	poiline[273] = pTransGeom->MethodCreatePoint2d(3.93, 10.85);
	poiline[274] = pTransGeom->MethodCreatePoint2d(3.93, 10.2);
	poiline[275] = pTransGeom->MethodCreatePoint2d(3.93, 10);
	poiline[276] = pTransGeom->MethodCreatePoint2d(3.93, 9.35);
	poiline[277] = pTransGeom->MethodCreatePoint2d(3.93, 9.15);
	poiline[278] = pTransGeom->MethodCreatePoint2d(3.93, 8.5);
	poiline[279] = pTransGeom->MethodCreatePoint2d(3.93, 8.3);
	poiline[280] = pTransGeom->MethodCreatePoint2d(3.93, 7.65);
	poiline[281] = pTransGeom->MethodCreatePoint2d(3.93, 7.45);
	poiline[282] = pTransGeom->MethodCreatePoint2d(3.93, 6.8);
	poiline[283] = pTransGeom->MethodCreatePoint2d(3.93, 6.6);
	poiline[284] = pTransGeom->MethodCreatePoint2d(3.93, 5.95);
	poiline[285] = pTransGeom->MethodCreatePoint2d(3.93, 5.75);
	poiline[286] = pTransGeom->MethodCreatePoint2d(3.93, 5.1);
	poiline[287] = pTransGeom->MethodCreatePoint2d(3.93, 4.9);
	poiline[288] = pTransGeom->MethodCreatePoint2d(3.93, 4.25);
	poiline[289] = pTransGeom->MethodCreatePoint2d(3.93, 4.05);
	poiline[290] = pTransGeom->MethodCreatePoint2d(3.93, 3.4);
	poiline[291] = pTransGeom->MethodCreatePoint2d(3.93, 3.2);
	poiline[292] = pTransGeom->MethodCreatePoint2d(3.93, 2.55);
	poiline[293] = pTransGeom->MethodCreatePoint2d(3.93, 2.35);
	poiline[294] = pTransGeom->MethodCreatePoint2d(3.93, 1.7);
	poiline[295] = pTransGeom->MethodCreatePoint2d(3.93, 1.5);
	poiline[296] = pTransGeom->MethodCreatePoint2d(4.97, 11.9);
	poiline[297] = pTransGeom->MethodCreatePoint2d(4.97, 11.7);
	poiline[298] = pTransGeom->MethodCreatePoint2d(4.97, 11.05);
	poiline[299] = pTransGeom->MethodCreatePoint2d(4.97, 10.85);
	poiline[300] = pTransGeom->MethodCreatePoint2d(4.97, 10.2);
	poiline[301] = pTransGeom->MethodCreatePoint2d(4.97, 10);
	poiline[302] = pTransGeom->MethodCreatePoint2d(4.97, 9.35);
	poiline[303] = pTransGeom->MethodCreatePoint2d(4.97, 9.15);
	poiline[304] = pTransGeom->MethodCreatePoint2d(4.97, 8.5);
	poiline[305] = pTransGeom->MethodCreatePoint2d(4.97, 8.3);
	poiline[306] = pTransGeom->MethodCreatePoint2d(4.97, 7.65);
	poiline[307] = pTransGeom->MethodCreatePoint2d(4.97, 7.45);
	poiline[308] = pTransGeom->MethodCreatePoint2d(4.97, 6.8);
	poiline[309] = pTransGeom->MethodCreatePoint2d(4.97, 6.6);
	poiline[310] = pTransGeom->MethodCreatePoint2d(4.97, 5.95);
	poiline[311] = pTransGeom->MethodCreatePoint2d(4.97, 5.75);
	poiline[312] = pTransGeom->MethodCreatePoint2d(4.97, 5.1);
	poiline[313] = pTransGeom->MethodCreatePoint2d(4.97, 4.9);
	poiline[314] = pTransGeom->MethodCreatePoint2d(4.97, 4.25);
	poiline[315] = pTransGeom->MethodCreatePoint2d(4.97, 4.05);
	poiline[316] = pTransGeom->MethodCreatePoint2d(4.97, 3.4);
	poiline[317] = pTransGeom->MethodCreatePoint2d(4.97, 3.2);
	poiline[318] = pTransGeom->MethodCreatePoint2d(4.97, 2.55);
	poiline[319] = pTransGeom->MethodCreatePoint2d(4.97, 2.35);
	poiline[320] = pTransGeom->MethodCreatePoint2d(4.97, 1.7);
	poiline[321] = pTransGeom->MethodCreatePoint2d(4.97, 1.5);
	poiline[322] = pTransGeom->MethodCreatePoint2d(6.27, 11.9);
	poiline[323] = pTransGeom->MethodCreatePoint2d(6.27, 11.7);
	poiline[324] = pTransGeom->MethodCreatePoint2d(6.27, 11.05);
	poiline[325] = pTransGeom->MethodCreatePoint2d(6.27, 10.85);
	poiline[326] = pTransGeom->MethodCreatePoint2d(6.27, 10.2);
	poiline[327] = pTransGeom->MethodCreatePoint2d(6.27, 10);
	poiline[328] = pTransGeom->MethodCreatePoint2d(6.27, 9.35);
	poiline[329] = pTransGeom->MethodCreatePoint2d(6.27, 9.15);
	poiline[330] = pTransGeom->MethodCreatePoint2d(6.27, 8.5);
	poiline[331] = pTransGeom->MethodCreatePoint2d(6.27, 8.3);
	poiline[332] = pTransGeom->MethodCreatePoint2d(6.27, 7.65);
	poiline[333] = pTransGeom->MethodCreatePoint2d(6.27, 7.45);
	poiline[334] = pTransGeom->MethodCreatePoint2d(6.27, 6.8);
	poiline[335] = pTransGeom->MethodCreatePoint2d(6.27, 6.6);
	poiline[336] = pTransGeom->MethodCreatePoint2d(6.27, 5.95);
	poiline[337] = pTransGeom->MethodCreatePoint2d(6.27, 5.75);
	poiline[338] = pTransGeom->MethodCreatePoint2d(6.27, 5.1);
	poiline[339] = pTransGeom->MethodCreatePoint2d(6.27, 4.9);
	poiline[340] = pTransGeom->MethodCreatePoint2d(6.27, 4.25);
	poiline[341] = pTransGeom->MethodCreatePoint2d(6.27, 4.05);
	poiline[342] = pTransGeom->MethodCreatePoint2d(6.27, 3.4);
	poiline[343] = pTransGeom->MethodCreatePoint2d(6.27, 3.2);
	poiline[344] = pTransGeom->MethodCreatePoint2d(6.27, 2.55);
	poiline[345] = pTransGeom->MethodCreatePoint2d(6.27, 2.35);
	poiline[346] = pTransGeom->MethodCreatePoint2d(6.27, 1.7);
	poiline[347] = pTransGeom->MethodCreatePoint2d(6.27, 1.5);
	poiline[348] = pTransGeom->MethodCreatePoint2d(13.81, 11.9);
	poiline[349] = pTransGeom->MethodCreatePoint2d(13.81, 11.7);
	poiline[350] = pTransGeom->MethodCreatePoint2d(13.81, 11.05);
	poiline[351] = pTransGeom->MethodCreatePoint2d(13.81, 10.85);
	poiline[352] = pTransGeom->MethodCreatePoint2d(13.81, 10.2);
	poiline[353] = pTransGeom->MethodCreatePoint2d(13.81, 10);
	poiline[354] = pTransGeom->MethodCreatePoint2d(13.81, 9.35);
	poiline[355] = pTransGeom->MethodCreatePoint2d(13.81, 9.15);
	poiline[356] = pTransGeom->MethodCreatePoint2d(13.81, 8.5);
	poiline[357] = pTransGeom->MethodCreatePoint2d(13.81, 8.3);
	poiline[358] = pTransGeom->MethodCreatePoint2d(13.81, 7.65);
	poiline[359] = pTransGeom->MethodCreatePoint2d(13.81, 7.45);
	poiline[360] = pTransGeom->MethodCreatePoint2d(13.81, 6.8);
	poiline[361] = pTransGeom->MethodCreatePoint2d(13.81, 6.6);
	poiline[362] = pTransGeom->MethodCreatePoint2d(13.81, 5.95);
	poiline[363] = pTransGeom->MethodCreatePoint2d(13.81, 5.75);
	poiline[364] = pTransGeom->MethodCreatePoint2d(13.81, 5.1);
	poiline[365] = pTransGeom->MethodCreatePoint2d(13.81, 4.9);
	poiline[366] = pTransGeom->MethodCreatePoint2d(13.81, 4.25);
	poiline[367] = pTransGeom->MethodCreatePoint2d(13.81, 4.05);
	poiline[368] = pTransGeom->MethodCreatePoint2d(13.81, 3.4);
	poiline[369] = pTransGeom->MethodCreatePoint2d(13.81, 3.2);
	poiline[370] = pTransGeom->MethodCreatePoint2d(13.81, 2.55);
	poiline[371] = pTransGeom->MethodCreatePoint2d(13.81, 2.35);
	poiline[372] = pTransGeom->MethodCreatePoint2d(13.81, 1.7);
	poiline[373] = pTransGeom->MethodCreatePoint2d(13.81, 1.5);
	poiline[374] = pTransGeom->MethodCreatePoint2d(14.85, 11.9);
	poiline[375] = pTransGeom->MethodCreatePoint2d(14.85, 11.7);
	poiline[376] = pTransGeom->MethodCreatePoint2d(14.85, 11.05);
	poiline[377] = pTransGeom->MethodCreatePoint2d(14.85, 10.85);
	poiline[378] = pTransGeom->MethodCreatePoint2d(14.85, 10.2);
	poiline[379] = pTransGeom->MethodCreatePoint2d(14.85, 10);
	poiline[380] = pTransGeom->MethodCreatePoint2d(14.85, 9.35);
	poiline[381] = pTransGeom->MethodCreatePoint2d(14.85, 9.15);
	poiline[382] = pTransGeom->MethodCreatePoint2d(14.85, 8.5);
	poiline[383] = pTransGeom->MethodCreatePoint2d(14.85, 8.3);
	poiline[384] = pTransGeom->MethodCreatePoint2d(14.85, 7.65);
	poiline[385] = pTransGeom->MethodCreatePoint2d(14.85, 7.45);
	poiline[386] = pTransGeom->MethodCreatePoint2d(14.85, 6.8);
	poiline[387] = pTransGeom->MethodCreatePoint2d(14.85, 6.6);
	poiline[388] = pTransGeom->MethodCreatePoint2d(14.85, 5.95);
	poiline[389] = pTransGeom->MethodCreatePoint2d(14.85, 5.75);
	poiline[390] = pTransGeom->MethodCreatePoint2d(14.85, 5.1);
	poiline[391] = pTransGeom->MethodCreatePoint2d(14.85, 4.9);
	poiline[392] = pTransGeom->MethodCreatePoint2d(14.85, 4.25);
	poiline[393] = pTransGeom->MethodCreatePoint2d(14.85, 4.05);
	poiline[394] = pTransGeom->MethodCreatePoint2d(14.85, 3.4);
	poiline[395] = pTransGeom->MethodCreatePoint2d(14.85, 3.2);
	poiline[396] = pTransGeom->MethodCreatePoint2d(14.85, 2.55);
	poiline[397] = pTransGeom->MethodCreatePoint2d(14.85, 2.35);
	poiline[398] = pTransGeom->MethodCreatePoint2d(14.85, 1.7);
	poiline[399] = pTransGeom->MethodCreatePoint2d(14.85, 1.5);
	poiline[400] = pTransGeom->MethodCreatePoint2d(16.67, 11.9);
	poiline[401] = pTransGeom->MethodCreatePoint2d(16.67, 11.7);
	poiline[402] = pTransGeom->MethodCreatePoint2d(16.67, 11.05);
	poiline[403] = pTransGeom->MethodCreatePoint2d(16.67, 10.85);
	poiline[404] = pTransGeom->MethodCreatePoint2d(16.67, 10.2);
	poiline[405] = pTransGeom->MethodCreatePoint2d(16.67, 10);
	poiline[406] = pTransGeom->MethodCreatePoint2d(16.67, 9.35);
	poiline[407] = pTransGeom->MethodCreatePoint2d(16.67, 9.15);
	poiline[408] = pTransGeom->MethodCreatePoint2d(16.67, 8.5);
	poiline[409] = pTransGeom->MethodCreatePoint2d(16.67, 8.3);
	poiline[410] = pTransGeom->MethodCreatePoint2d(16.67, 7.65);
	poiline[411] = pTransGeom->MethodCreatePoint2d(16.67, 7.45);
	poiline[412] = pTransGeom->MethodCreatePoint2d(16.67, 6.8);
	poiline[413] = pTransGeom->MethodCreatePoint2d(16.67, 6.6);
	poiline[414] = pTransGeom->MethodCreatePoint2d(16.67, 5.95);
	poiline[415] = pTransGeom->MethodCreatePoint2d(16.67, 5.75);
	poiline[416] = pTransGeom->MethodCreatePoint2d(16.67, 5.1);
	poiline[417] = pTransGeom->MethodCreatePoint2d(16.67, 4.9);
	poiline[418] = pTransGeom->MethodCreatePoint2d(16.67, 4.25);
	poiline[419] = pTransGeom->MethodCreatePoint2d(16.67, 4.05);
	poiline[420] = pTransGeom->MethodCreatePoint2d(16.67, 3.4);
	poiline[421] = pTransGeom->MethodCreatePoint2d(16.67, 3.2);
	poiline[422] = pTransGeom->MethodCreatePoint2d(16.67, 2.55);
	poiline[423] = pTransGeom->MethodCreatePoint2d(16.67, 2.35);
	poiline[424] = pTransGeom->MethodCreatePoint2d(16.67, 1.7);
	poiline[425] = pTransGeom->MethodCreatePoint2d(16.67, 1.5);
	poiline[426] = pTransGeom->MethodCreatePoint2d(17.71, 11.9);
	poiline[427] = pTransGeom->MethodCreatePoint2d(17.71, 11.7);
	poiline[428] = pTransGeom->MethodCreatePoint2d(17.71, 11.05);
	poiline[429] = pTransGeom->MethodCreatePoint2d(17.71, 10.85);
	poiline[430] = pTransGeom->MethodCreatePoint2d(17.71, 10.2);
	poiline[431] = pTransGeom->MethodCreatePoint2d(17.71, 10);
	poiline[432] = pTransGeom->MethodCreatePoint2d(17.71, 9.35);
	poiline[433] = pTransGeom->MethodCreatePoint2d(17.71, 9.15);
	poiline[434] = pTransGeom->MethodCreatePoint2d(17.71, 8.5);
	poiline[435] = pTransGeom->MethodCreatePoint2d(17.71, 8.3);
	poiline[436] = pTransGeom->MethodCreatePoint2d(17.71, 7.65);
	poiline[437] = pTransGeom->MethodCreatePoint2d(17.71, 7.45);
	poiline[438] = pTransGeom->MethodCreatePoint2d(17.71, 6.8);
	poiline[439] = pTransGeom->MethodCreatePoint2d(17.71, 6.6);
	poiline[440] = pTransGeom->MethodCreatePoint2d(17.71, 5.95);
	poiline[441] = pTransGeom->MethodCreatePoint2d(17.71, 5.75);
	poiline[442] = pTransGeom->MethodCreatePoint2d(17.71, 5.1);
	poiline[443] = pTransGeom->MethodCreatePoint2d(17.71, 4.9);
	poiline[444] = pTransGeom->MethodCreatePoint2d(17.71, 4.25);
	poiline[445] = pTransGeom->MethodCreatePoint2d(17.71, 4.05);
	poiline[446] = pTransGeom->MethodCreatePoint2d(17.71, 3.4);
	poiline[447] = pTransGeom->MethodCreatePoint2d(17.71, 3.2);
	poiline[448] = pTransGeom->MethodCreatePoint2d(17.71, 2.55);
	poiline[449] = pTransGeom->MethodCreatePoint2d(17.71, 2.35);
	poiline[450] = pTransGeom->MethodCreatePoint2d(17.71, 1.7);
	poiline[451] = pTransGeom->MethodCreatePoint2d(17.71, 1.5);
	poiline[452] = pTransGeom->MethodCreatePoint2d(19.01, 11.9);
	poiline[453] = pTransGeom->MethodCreatePoint2d(19.01, 11.7);
	poiline[454] = pTransGeom->MethodCreatePoint2d(19.01, 11.05);
	poiline[455] = pTransGeom->MethodCreatePoint2d(19.01, 10.85);
	poiline[456] = pTransGeom->MethodCreatePoint2d(19.01, 10.2);
	poiline[457] = pTransGeom->MethodCreatePoint2d(19.01, 10);
	poiline[458] = pTransGeom->MethodCreatePoint2d(19.01, 9.35);
	poiline[459] = pTransGeom->MethodCreatePoint2d(19.01, 9.15);
	poiline[460] = pTransGeom->MethodCreatePoint2d(19.01, 8.5);
	poiline[461] = pTransGeom->MethodCreatePoint2d(19.01, 8.3);
	poiline[462] = pTransGeom->MethodCreatePoint2d(19.01, 7.65);
	poiline[463] = pTransGeom->MethodCreatePoint2d(19.01, 7.45);
	poiline[464] = pTransGeom->MethodCreatePoint2d(19.01, 6.8);
	poiline[465] = pTransGeom->MethodCreatePoint2d(19.01, 6.6);
	poiline[466] = pTransGeom->MethodCreatePoint2d(19.01, 5.95);
	poiline[467] = pTransGeom->MethodCreatePoint2d(19.01, 5.75);
	poiline[468] = pTransGeom->MethodCreatePoint2d(19.01, 5.1);
	poiline[469] = pTransGeom->MethodCreatePoint2d(19.01, 4.9);
	poiline[470] = pTransGeom->MethodCreatePoint2d(19.01, 4.25);
	poiline[471] = pTransGeom->MethodCreatePoint2d(19.01, 4.05);
	poiline[472] = pTransGeom->MethodCreatePoint2d(19.01, 3.4);
	poiline[473] = pTransGeom->MethodCreatePoint2d(19.01, 3.2);
	poiline[474] = pTransGeom->MethodCreatePoint2d(19.01, 2.55);
	poiline[475] = pTransGeom->MethodCreatePoint2d(19.01, 2.35);
	poiline[476] = pTransGeom->MethodCreatePoint2d(19.01, 1.7);
	poiline[477] = pTransGeom->MethodCreatePoint2d(19.01, 1.5);
	poiline[478] = pTransGeom->MethodCreatePoint2d(20.05, 11.9);
	poiline[479] = pTransGeom->MethodCreatePoint2d(20.05, 11.7);
	poiline[480] = pTransGeom->MethodCreatePoint2d(20.05, 11.05);
	poiline[481] = pTransGeom->MethodCreatePoint2d(20.05, 10.85);
	poiline[482] = pTransGeom->MethodCreatePoint2d(20.05, 10.2);
	poiline[483] = pTransGeom->MethodCreatePoint2d(20.05, 10);
	poiline[484] = pTransGeom->MethodCreatePoint2d(20.05, 9.35);
	poiline[485] = pTransGeom->MethodCreatePoint2d(20.05, 9.15);
	poiline[486] = pTransGeom->MethodCreatePoint2d(20.05, 8.5);
	poiline[487] = pTransGeom->MethodCreatePoint2d(20.05, 8.3);
	poiline[488] = pTransGeom->MethodCreatePoint2d(20.05, 7.65);
	poiline[489] = pTransGeom->MethodCreatePoint2d(20.05, 7.45);
	poiline[490] = pTransGeom->MethodCreatePoint2d(20.05, 6.8);
	poiline[491] = pTransGeom->MethodCreatePoint2d(20.05, 6.6);
	poiline[492] = pTransGeom->MethodCreatePoint2d(20.05, 5.95);
	poiline[493] = pTransGeom->MethodCreatePoint2d(20.05, 5.75);
	poiline[494] = pTransGeom->MethodCreatePoint2d(20.05, 5.1);
	poiline[495] = pTransGeom->MethodCreatePoint2d(20.05, 4.9);
	poiline[496] = pTransGeom->MethodCreatePoint2d(20.05, 4.25);
	poiline[497] = pTransGeom->MethodCreatePoint2d(20.05, 4.05);
	poiline[498] = pTransGeom->MethodCreatePoint2d(20.05, 3.4);
	poiline[499] = pTransGeom->MethodCreatePoint2d(20.05, 3.2);
	poiline[500] = pTransGeom->MethodCreatePoint2d(20.05, 2.55);
	poiline[501] = pTransGeom->MethodCreatePoint2d(20.05, 2.35);
	poiline[502] = pTransGeom->MethodCreatePoint2d(20.05, 1.7);
	poiline[503] = pTransGeom->MethodCreatePoint2d(20.05, 1.5);
	poiline[504] = pTransGeom->MethodCreatePoint2d(21.35, 11.9);
	poiline[505] = pTransGeom->MethodCreatePoint2d(21.35, 11.7);
	poiline[506] = pTransGeom->MethodCreatePoint2d(21.35, 11.05);
	poiline[507] = pTransGeom->MethodCreatePoint2d(21.35, 10.85);
	poiline[508] = pTransGeom->MethodCreatePoint2d(21.35, 10.2);
	poiline[509] = pTransGeom->MethodCreatePoint2d(21.35, 10);
	poiline[510] = pTransGeom->MethodCreatePoint2d(21.35, 9.35);
	poiline[511] = pTransGeom->MethodCreatePoint2d(21.35, 9.15);
	poiline[512] = pTransGeom->MethodCreatePoint2d(21.35, 8.5);
	poiline[513] = pTransGeom->MethodCreatePoint2d(21.35, 8.3);
	poiline[514] = pTransGeom->MethodCreatePoint2d(21.35, 7.65);
	poiline[515] = pTransGeom->MethodCreatePoint2d(21.35, 7.45);
	poiline[516] = pTransGeom->MethodCreatePoint2d(21.35, 6.8);
	poiline[517] = pTransGeom->MethodCreatePoint2d(21.35, 6.6);
	poiline[518] = pTransGeom->MethodCreatePoint2d(21.35, 5.95);
	poiline[519] = pTransGeom->MethodCreatePoint2d(21.35, 5.75);
	poiline[520] = pTransGeom->MethodCreatePoint2d(21.35, 5.1);
	poiline[521] = pTransGeom->MethodCreatePoint2d(21.35, 4.9);
	poiline[522] = pTransGeom->MethodCreatePoint2d(21.35, 4.25);
	poiline[523] = pTransGeom->MethodCreatePoint2d(21.35, 4.05);
	poiline[524] = pTransGeom->MethodCreatePoint2d(21.35, 3.4);
	poiline[525] = pTransGeom->MethodCreatePoint2d(21.35, 3.2);
	poiline[526] = pTransGeom->MethodCreatePoint2d(21.35, 2.55);
	poiline[527] = pTransGeom->MethodCreatePoint2d(21.35, 2.35);
	poiline[528] = pTransGeom->MethodCreatePoint2d(21.35, 1.7);
	poiline[529] = pTransGeom->MethodCreatePoint2d(21.35, 1.5);
	poiline[530] = pTransGeom->MethodCreatePoint2d(22.65, 11.9);
	poiline[531] = pTransGeom->MethodCreatePoint2d(22.65, 11.7);
	poiline[532] = pTransGeom->MethodCreatePoint2d(22.65, 11.05);
	poiline[533] = pTransGeom->MethodCreatePoint2d(22.65, 10.85);
	poiline[534] = pTransGeom->MethodCreatePoint2d(22.65, 10.2);
	poiline[535] = pTransGeom->MethodCreatePoint2d(22.65, 10);
	poiline[536] = pTransGeom->MethodCreatePoint2d(22.65, 9.35);
	poiline[537] = pTransGeom->MethodCreatePoint2d(22.65, 9.15);
	poiline[538] = pTransGeom->MethodCreatePoint2d(22.65, 8.5);
	poiline[539] = pTransGeom->MethodCreatePoint2d(22.65, 8.3);
	poiline[540] = pTransGeom->MethodCreatePoint2d(22.65, 7.65);
	poiline[541] = pTransGeom->MethodCreatePoint2d(22.65, 7.45);
	poiline[542] = pTransGeom->MethodCreatePoint2d(22.65, 6.8);
	poiline[543] = pTransGeom->MethodCreatePoint2d(22.65, 6.6);
	poiline[544] = pTransGeom->MethodCreatePoint2d(22.65, 5.95);
	poiline[545] = pTransGeom->MethodCreatePoint2d(22.65, 5.75);
	poiline[546] = pTransGeom->MethodCreatePoint2d(22.65, 5.1);
	poiline[547] = pTransGeom->MethodCreatePoint2d(22.65, 4.9);
	poiline[548] = pTransGeom->MethodCreatePoint2d(22.65, 4.25);
	poiline[549] = pTransGeom->MethodCreatePoint2d(22.65, 4.05);
	poiline[550] = pTransGeom->MethodCreatePoint2d(22.65, 3.4);
	poiline[551] = pTransGeom->MethodCreatePoint2d(22.65, 3.2);
	poiline[552] = pTransGeom->MethodCreatePoint2d(22.65, 2.55);
	poiline[553] = pTransGeom->MethodCreatePoint2d(22.65, 2.35);
	poiline[554] = pTransGeom->MethodCreatePoint2d(22.65, 1.7);
	poiline[555] = pTransGeom->MethodCreatePoint2d(22.65, 1.5);
	poiline[556] = pTransGeom->MethodCreatePoint2d(23.95, 11.9);
	poiline[557] = pTransGeom->MethodCreatePoint2d(23.95, 11.7);
	poiline[558] = pTransGeom->MethodCreatePoint2d(23.95, 11.05);
	poiline[559] = pTransGeom->MethodCreatePoint2d(23.95, 10.85);
	poiline[560] = pTransGeom->MethodCreatePoint2d(23.95, 10.2);
	poiline[561] = pTransGeom->MethodCreatePoint2d(23.95, 10);
	poiline[562] = pTransGeom->MethodCreatePoint2d(23.95, 9.35);
	poiline[563] = pTransGeom->MethodCreatePoint2d(23.95, 9.15);
	poiline[564] = pTransGeom->MethodCreatePoint2d(23.95, 8.5);
	poiline[565] = pTransGeom->MethodCreatePoint2d(23.95, 8.3);
	poiline[566] = pTransGeom->MethodCreatePoint2d(23.95, 7.65);
	poiline[567] = pTransGeom->MethodCreatePoint2d(23.95, 7.45);
	poiline[568] = pTransGeom->MethodCreatePoint2d(23.95, 6.8);
	poiline[569] = pTransGeom->MethodCreatePoint2d(23.95, 6.6);
	poiline[570] = pTransGeom->MethodCreatePoint2d(23.95, 5.95);
	poiline[571] = pTransGeom->MethodCreatePoint2d(23.95, 5.75);
	poiline[572] = pTransGeom->MethodCreatePoint2d(23.95, 5.1);
	poiline[573] = pTransGeom->MethodCreatePoint2d(23.95, 4.9);
	poiline[574] = pTransGeom->MethodCreatePoint2d(23.95, 4.25);
	poiline[575] = pTransGeom->MethodCreatePoint2d(23.95, 4.05);
	poiline[576] = pTransGeom->MethodCreatePoint2d(23.95, 3.4);
	poiline[577] = pTransGeom->MethodCreatePoint2d(23.95, 3.2);
	poiline[578] = pTransGeom->MethodCreatePoint2d(23.95, 2.55);
	poiline[579] = pTransGeom->MethodCreatePoint2d(23.95, 2.35);
	poiline[580] = pTransGeom->MethodCreatePoint2d(23.95, 1.7);
	poiline[581] = pTransGeom->MethodCreatePoint2d(23.95, 1.5);
	poiline[582] = pTransGeom->MethodCreatePoint2d(25.25, 11.9);
	poiline[583] = pTransGeom->MethodCreatePoint2d(25.25, 11.7);
	poiline[584] = pTransGeom->MethodCreatePoint2d(25.25, 11.05);
	poiline[585] = pTransGeom->MethodCreatePoint2d(25.25, 10.85);
	poiline[586] = pTransGeom->MethodCreatePoint2d(25.25, 10.2);
	poiline[587] = pTransGeom->MethodCreatePoint2d(25.25, 10);
	poiline[588] = pTransGeom->MethodCreatePoint2d(25.25, 9.35);
	poiline[589] = pTransGeom->MethodCreatePoint2d(25.25, 9.15);
	poiline[590] = pTransGeom->MethodCreatePoint2d(25.25, 8.5);
	poiline[591] = pTransGeom->MethodCreatePoint2d(25.25, 8.3);
	poiline[592] = pTransGeom->MethodCreatePoint2d(25.25, 7.65);
	poiline[593] = pTransGeom->MethodCreatePoint2d(25.25, 7.45);
	poiline[594] = pTransGeom->MethodCreatePoint2d(25.25, 6.8);
	poiline[595] = pTransGeom->MethodCreatePoint2d(25.25, 6.6);
	poiline[596] = pTransGeom->MethodCreatePoint2d(25.25, 5.95);
	poiline[597] = pTransGeom->MethodCreatePoint2d(25.25, 5.75);
	poiline[598] = pTransGeom->MethodCreatePoint2d(25.25, 5.1);
	poiline[599] = pTransGeom->MethodCreatePoint2d(25.25, 4.9);
	poiline[600] = pTransGeom->MethodCreatePoint2d(25.25, 4.25);
	poiline[601] = pTransGeom->MethodCreatePoint2d(25.25, 4.05);
	poiline[602] = pTransGeom->MethodCreatePoint2d(25.25, 3.4);
	poiline[603] = pTransGeom->MethodCreatePoint2d(25.25, 3.2);
	poiline[604] = pTransGeom->MethodCreatePoint2d(25.25, 2.55);
	poiline[605] = pTransGeom->MethodCreatePoint2d(25.25, 2.35);
	poiline[606] = pTransGeom->MethodCreatePoint2d(25.25, 1.7);
	poiline[607] = pTransGeom->MethodCreatePoint2d(25.25, 1.5);
	poiline[608] = pTransGeom->MethodCreatePoint2d(27.07, 11.9);
	poiline[609] = pTransGeom->MethodCreatePoint2d(27.07, 11.7);
	poiline[610] = pTransGeom->MethodCreatePoint2d(27.07, 11.05);
	poiline[611] = pTransGeom->MethodCreatePoint2d(27.07, 10.85);
	poiline[612] = pTransGeom->MethodCreatePoint2d(27.07, 10.2);
	poiline[613] = pTransGeom->MethodCreatePoint2d(27.07, 10);
	poiline[614] = pTransGeom->MethodCreatePoint2d(27.07, 9.35);
	poiline[615] = pTransGeom->MethodCreatePoint2d(27.07, 9.15);
	poiline[616] = pTransGeom->MethodCreatePoint2d(27.07, 8.5);
	poiline[617] = pTransGeom->MethodCreatePoint2d(27.07, 8.3);
	poiline[618] = pTransGeom->MethodCreatePoint2d(27.07, 7.65);
	poiline[619] = pTransGeom->MethodCreatePoint2d(27.07, 7.45);
	poiline[620] = pTransGeom->MethodCreatePoint2d(27.07, 6.8);
	poiline[621] = pTransGeom->MethodCreatePoint2d(27.07, 6.6);
	poiline[622] = pTransGeom->MethodCreatePoint2d(27.07, 5.95);
	poiline[623] = pTransGeom->MethodCreatePoint2d(27.07, 5.75);
	poiline[624] = pTransGeom->MethodCreatePoint2d(27.07, 5.1);
	poiline[625] = pTransGeom->MethodCreatePoint2d(27.07, 4.9);
	poiline[626] = pTransGeom->MethodCreatePoint2d(27.07, 4.25);
	poiline[627] = pTransGeom->MethodCreatePoint2d(27.07, 4.05);
	poiline[628] = pTransGeom->MethodCreatePoint2d(27.07, 3.4);
	poiline[629] = pTransGeom->MethodCreatePoint2d(27.07, 3.2);
	poiline[630] = pTransGeom->MethodCreatePoint2d(27.07, 2.55);
	poiline[631] = pTransGeom->MethodCreatePoint2d(27.07, 2.35);
	poiline[632] = pTransGeom->MethodCreatePoint2d(27.07, 1.7);
	poiline[633] = pTransGeom->MethodCreatePoint2d(27.07, 1.5);
	poiline[634] = pTransGeom->MethodCreatePoint2d(2.89, 14.45);
	poiline[635] = pTransGeom->MethodCreatePoint2d(2.89, 14.25);
	poiline[636] = pTransGeom->MethodCreatePoint2d(2.89, 13.6);
	poiline[637] = pTransGeom->MethodCreatePoint2d(2.89, 13.4);
	poiline[638] = pTransGeom->MethodCreatePoint2d(2.89, 12.75);
	poiline[639] = pTransGeom->MethodCreatePoint2d(2.89, 12.55);
	poiline[640] = pTransGeom->MethodCreatePoint2d(3.93, 14.45);
	poiline[641] = pTransGeom->MethodCreatePoint2d(3.93, 14.25);
	poiline[642] = pTransGeom->MethodCreatePoint2d(3.93, 13.6);
	poiline[643] = pTransGeom->MethodCreatePoint2d(3.93, 13.4);
	poiline[644] = pTransGeom->MethodCreatePoint2d(3.93, 12.75);
	poiline[645] = pTransGeom->MethodCreatePoint2d(3.93, 12.55);
	poiline[646] = pTransGeom->MethodCreatePoint2d(4.97, 14.45);
	poiline[647] = pTransGeom->MethodCreatePoint2d(4.97, 14.25);
	poiline[648] = pTransGeom->MethodCreatePoint2d(4.97, 13.6);
	poiline[649] = pTransGeom->MethodCreatePoint2d(4.97, 13.4);
	poiline[650] = pTransGeom->MethodCreatePoint2d(4.97, 12.75);
	poiline[651] = pTransGeom->MethodCreatePoint2d(4.97, 12.55);
	poiline[652] = pTransGeom->MethodCreatePoint2d(6.27, 14.45);
	poiline[653] = pTransGeom->MethodCreatePoint2d(6.27, 14.25);
	poiline[654] = pTransGeom->MethodCreatePoint2d(6.27, 13.6);
	poiline[655] = pTransGeom->MethodCreatePoint2d(6.27, 13.4);
	poiline[656] = pTransGeom->MethodCreatePoint2d(6.27, 12.75);
	poiline[657] = pTransGeom->MethodCreatePoint2d(6.27, 12.55);
	poiline[658] = pTransGeom->MethodCreatePoint2d(13.81, 14.45);
	poiline[659] = pTransGeom->MethodCreatePoint2d(13.81, 14.25);
	poiline[660] = pTransGeom->MethodCreatePoint2d(13.81, 13.6);
	poiline[661] = pTransGeom->MethodCreatePoint2d(13.81, 13.4);
	poiline[662] = pTransGeom->MethodCreatePoint2d(13.81, 12.75);
	poiline[663] = pTransGeom->MethodCreatePoint2d(13.81, 12.55);
	poiline[664] = pTransGeom->MethodCreatePoint2d(14.85, 14.45);
	poiline[665] = pTransGeom->MethodCreatePoint2d(14.85, 14.25);
	poiline[666] = pTransGeom->MethodCreatePoint2d(14.85, 13.6);
	poiline[667] = pTransGeom->MethodCreatePoint2d(14.85, 13.4);
	poiline[668] = pTransGeom->MethodCreatePoint2d(14.85, 12.75);
	poiline[669] = pTransGeom->MethodCreatePoint2d(14.85, 12.55);
	poiline[670] = pTransGeom->MethodCreatePoint2d(16.67, 14.45);
	poiline[671] = pTransGeom->MethodCreatePoint2d(16.67, 14.25);
	poiline[672] = pTransGeom->MethodCreatePoint2d(16.67, 13.6);
	poiline[673] = pTransGeom->MethodCreatePoint2d(16.67, 13.4);
	poiline[674] = pTransGeom->MethodCreatePoint2d(16.67, 12.75);
	poiline[675] = pTransGeom->MethodCreatePoint2d(16.67, 12.55);
	poiline[676] = pTransGeom->MethodCreatePoint2d(17.71, 14.45);
	poiline[677] = pTransGeom->MethodCreatePoint2d(17.71, 14.25);
	poiline[678] = pTransGeom->MethodCreatePoint2d(17.71, 13.6);
	poiline[679] = pTransGeom->MethodCreatePoint2d(17.71, 13.4);
	poiline[680] = pTransGeom->MethodCreatePoint2d(17.71, 12.75);
	poiline[681] = pTransGeom->MethodCreatePoint2d(17.71, 12.55);
	poiline[682] = pTransGeom->MethodCreatePoint2d(19.01, 14.45);
	poiline[683] = pTransGeom->MethodCreatePoint2d(19.01, 14.25);
	poiline[684] = pTransGeom->MethodCreatePoint2d(19.01, 13.6);
	poiline[685] = pTransGeom->MethodCreatePoint2d(19.01, 13.4);
	poiline[686] = pTransGeom->MethodCreatePoint2d(19.01, 12.75);
	poiline[687] = pTransGeom->MethodCreatePoint2d(19.01, 12.55);
	poiline[688] = pTransGeom->MethodCreatePoint2d(20.05, 14.45);
	poiline[689] = pTransGeom->MethodCreatePoint2d(20.05, 14.25);
	poiline[690] = pTransGeom->MethodCreatePoint2d(20.05, 13.6);
	poiline[691] = pTransGeom->MethodCreatePoint2d(20.05, 13.4);
	poiline[692] = pTransGeom->MethodCreatePoint2d(20.05, 12.75);
	poiline[693] = pTransGeom->MethodCreatePoint2d(20.05, 12.55);
	poiline[694] = pTransGeom->MethodCreatePoint2d(21.35, 14.45);
	poiline[695] = pTransGeom->MethodCreatePoint2d(21.35, 14.25);
	poiline[696] = pTransGeom->MethodCreatePoint2d(21.35, 13.6);
	poiline[697] = pTransGeom->MethodCreatePoint2d(21.35, 13.4);
	poiline[698] = pTransGeom->MethodCreatePoint2d(21.35, 12.75);
	poiline[699] = pTransGeom->MethodCreatePoint2d(21.35, 12.55);
	poiline[700] = pTransGeom->MethodCreatePoint2d(22.65, 14.45);
	poiline[701] = pTransGeom->MethodCreatePoint2d(22.65, 14.25);
	poiline[702] = pTransGeom->MethodCreatePoint2d(22.65, 13.6);
	poiline[703] = pTransGeom->MethodCreatePoint2d(22.65, 13.4);
	poiline[704] = pTransGeom->MethodCreatePoint2d(22.65, 12.75);
	poiline[705] = pTransGeom->MethodCreatePoint2d(22.65, 12.55);
	poiline[706] = pTransGeom->MethodCreatePoint2d(23.95, 14.45);
	poiline[707] = pTransGeom->MethodCreatePoint2d(23.95, 14.25);
	poiline[708] = pTransGeom->MethodCreatePoint2d(23.95, 13.6);
	poiline[709] = pTransGeom->MethodCreatePoint2d(23.95, 13.4);
	poiline[710] = pTransGeom->MethodCreatePoint2d(23.95, 12.75);
	poiline[711] = pTransGeom->MethodCreatePoint2d(23.95, 12.55);
	poiline[712] = pTransGeom->MethodCreatePoint2d(25.25, 14.45);
	poiline[713] = pTransGeom->MethodCreatePoint2d(25.25, 14.25);
	poiline[714] = pTransGeom->MethodCreatePoint2d(25.25, 13.6);
	poiline[715] = pTransGeom->MethodCreatePoint2d(25.25, 13.4);
	poiline[716] = pTransGeom->MethodCreatePoint2d(25.25, 12.75);
	poiline[717] = pTransGeom->MethodCreatePoint2d(25.25, 12.55);
	poiline[718] = pTransGeom->MethodCreatePoint2d(27.07, 14.45);
	poiline[719] = pTransGeom->MethodCreatePoint2d(27.07, 14.25);
	poiline[720] = pTransGeom->MethodCreatePoint2d(27.07, 13.6);
	poiline[721] = pTransGeom->MethodCreatePoint2d(27.07, 13.4);
	poiline[722] = pTransGeom->MethodCreatePoint2d(27.07, 12.75);
	poiline[723] = pTransGeom->MethodCreatePoint2d(27.07, 12.55);

	pSketchLines->MethodAddByTwoPoints(poiline[244], poiline[245]);
	pSketchLines->MethodAddByTwoPoints(poiline[246], poiline[247]);
	pSketchLines->MethodAddByTwoPoints(poiline[248], poiline[249]);
	pSketchLines->MethodAddByTwoPoints(poiline[250], poiline[251]);
	pSketchLines->MethodAddByTwoPoints(poiline[252], poiline[253]);
	pSketchLines->MethodAddByTwoPoints(poiline[254], poiline[255]);
	pSketchLines->MethodAddByTwoPoints(poiline[256], poiline[257]);
	pSketchLines->MethodAddByTwoPoints(poiline[258], poiline[259]);
	pSketchLines->MethodAddByTwoPoints(poiline[260], poiline[261]);
	pSketchLines->MethodAddByTwoPoints(poiline[262], poiline[263]);
	pSketchLines->MethodAddByTwoPoints(poiline[264], poiline[265]);
	pSketchLines->MethodAddByTwoPoints(poiline[266], poiline[267]);
	pSketchLines->MethodAddByTwoPoints(poiline[268], poiline[269]);
	pSketchLines->MethodAddByTwoPoints(poiline[270], poiline[271]);
	pSketchLines->MethodAddByTwoPoints(poiline[272], poiline[273]);
	pSketchLines->MethodAddByTwoPoints(poiline[274], poiline[275]);
	pSketchLines->MethodAddByTwoPoints(poiline[276], poiline[277]);
	pSketchLines->MethodAddByTwoPoints(poiline[278], poiline[279]);
	pSketchLines->MethodAddByTwoPoints(poiline[280], poiline[281]);
	pSketchLines->MethodAddByTwoPoints(poiline[282], poiline[283]);
	pSketchLines->MethodAddByTwoPoints(poiline[284], poiline[285]);
	pSketchLines->MethodAddByTwoPoints(poiline[286], poiline[287]);
	pSketchLines->MethodAddByTwoPoints(poiline[288], poiline[289]);
	pSketchLines->MethodAddByTwoPoints(poiline[290], poiline[291]);
	pSketchLines->MethodAddByTwoPoints(poiline[292], poiline[293]);
	pSketchLines->MethodAddByTwoPoints(poiline[294], poiline[295]);
	pSketchLines->MethodAddByTwoPoints(poiline[296], poiline[297]);
	pSketchLines->MethodAddByTwoPoints(poiline[298], poiline[299]);
	pSketchLines->MethodAddByTwoPoints(poiline[300], poiline[301]);
	pSketchLines->MethodAddByTwoPoints(poiline[302], poiline[303]);
	pSketchLines->MethodAddByTwoPoints(poiline[304], poiline[305]);
	pSketchLines->MethodAddByTwoPoints(poiline[306], poiline[307]);
	pSketchLines->MethodAddByTwoPoints(poiline[308], poiline[309]);
	pSketchLines->MethodAddByTwoPoints(poiline[310], poiline[311]);
	pSketchLines->MethodAddByTwoPoints(poiline[312], poiline[313]);
	pSketchLines->MethodAddByTwoPoints(poiline[314], poiline[315]);
	pSketchLines->MethodAddByTwoPoints(poiline[316], poiline[317]);
	pSketchLines->MethodAddByTwoPoints(poiline[318], poiline[319]);
	pSketchLines->MethodAddByTwoPoints(poiline[320], poiline[321]);
	pSketchLines->MethodAddByTwoPoints(poiline[322], poiline[323]);
	pSketchLines->MethodAddByTwoPoints(poiline[324], poiline[325]);
	pSketchLines->MethodAddByTwoPoints(poiline[326], poiline[327]);
	pSketchLines->MethodAddByTwoPoints(poiline[328], poiline[329]);
	pSketchLines->MethodAddByTwoPoints(poiline[330], poiline[331]);
	pSketchLines->MethodAddByTwoPoints(poiline[332], poiline[333]);
	pSketchLines->MethodAddByTwoPoints(poiline[334], poiline[335]);
	pSketchLines->MethodAddByTwoPoints(poiline[336], poiline[337]);
	pSketchLines->MethodAddByTwoPoints(poiline[338], poiline[339]);
	pSketchLines->MethodAddByTwoPoints(poiline[340], poiline[341]);
	pSketchLines->MethodAddByTwoPoints(poiline[342], poiline[343]);
	pSketchLines->MethodAddByTwoPoints(poiline[344], poiline[345]);
	pSketchLines->MethodAddByTwoPoints(poiline[346], poiline[347]);
	pSketchLines->MethodAddByTwoPoints(poiline[348], poiline[349]);
	pSketchLines->MethodAddByTwoPoints(poiline[350], poiline[351]);
	pSketchLines->MethodAddByTwoPoints(poiline[352], poiline[353]);
	pSketchLines->MethodAddByTwoPoints(poiline[354], poiline[355]);
	pSketchLines->MethodAddByTwoPoints(poiline[356], poiline[357]);
	pSketchLines->MethodAddByTwoPoints(poiline[358], poiline[359]);
	pSketchLines->MethodAddByTwoPoints(poiline[360], poiline[361]);
	pSketchLines->MethodAddByTwoPoints(poiline[362], poiline[363]);
	pSketchLines->MethodAddByTwoPoints(poiline[364], poiline[365]);
	pSketchLines->MethodAddByTwoPoints(poiline[366], poiline[367]);
	pSketchLines->MethodAddByTwoPoints(poiline[368], poiline[369]);
	pSketchLines->MethodAddByTwoPoints(poiline[370], poiline[371]);
	pSketchLines->MethodAddByTwoPoints(poiline[372], poiline[373]);
	pSketchLines->MethodAddByTwoPoints(poiline[374], poiline[375]);
	pSketchLines->MethodAddByTwoPoints(poiline[376], poiline[377]);
	pSketchLines->MethodAddByTwoPoints(poiline[378], poiline[379]);
	pSketchLines->MethodAddByTwoPoints(poiline[380], poiline[381]);
	pSketchLines->MethodAddByTwoPoints(poiline[382], poiline[383]);
	pSketchLines->MethodAddByTwoPoints(poiline[384], poiline[385]);
	pSketchLines->MethodAddByTwoPoints(poiline[386], poiline[387]);
	pSketchLines->MethodAddByTwoPoints(poiline[388], poiline[389]);
	pSketchLines->MethodAddByTwoPoints(poiline[390], poiline[391]);
	pSketchLines->MethodAddByTwoPoints(poiline[392], poiline[393]);
	pSketchLines->MethodAddByTwoPoints(poiline[394], poiline[395]);
	pSketchLines->MethodAddByTwoPoints(poiline[396], poiline[397]);
	pSketchLines->MethodAddByTwoPoints(poiline[398], poiline[399]);
	pSketchLines->MethodAddByTwoPoints(poiline[400], poiline[401]);
	pSketchLines->MethodAddByTwoPoints(poiline[402], poiline[403]);
	pSketchLines->MethodAddByTwoPoints(poiline[404], poiline[405]);
	pSketchLines->MethodAddByTwoPoints(poiline[406], poiline[407]);
	pSketchLines->MethodAddByTwoPoints(poiline[408], poiline[409]);
	pSketchLines->MethodAddByTwoPoints(poiline[410], poiline[411]);
	pSketchLines->MethodAddByTwoPoints(poiline[412], poiline[413]);
	pSketchLines->MethodAddByTwoPoints(poiline[414], poiline[415]);
	pSketchLines->MethodAddByTwoPoints(poiline[416], poiline[417]);
	pSketchLines->MethodAddByTwoPoints(poiline[418], poiline[419]);
	pSketchLines->MethodAddByTwoPoints(poiline[420], poiline[421]);
	pSketchLines->MethodAddByTwoPoints(poiline[422], poiline[423]);
	pSketchLines->MethodAddByTwoPoints(poiline[424], poiline[425]);
	pSketchLines->MethodAddByTwoPoints(poiline[426], poiline[427]);
	pSketchLines->MethodAddByTwoPoints(poiline[428], poiline[429]);
	pSketchLines->MethodAddByTwoPoints(poiline[430], poiline[431]);
	pSketchLines->MethodAddByTwoPoints(poiline[432], poiline[433]);
	pSketchLines->MethodAddByTwoPoints(poiline[434], poiline[435]);
	pSketchLines->MethodAddByTwoPoints(poiline[436], poiline[437]);
	pSketchLines->MethodAddByTwoPoints(poiline[438], poiline[439]);
	pSketchLines->MethodAddByTwoPoints(poiline[440], poiline[441]);
	pSketchLines->MethodAddByTwoPoints(poiline[442], poiline[443]);
	pSketchLines->MethodAddByTwoPoints(poiline[444], poiline[445]);
	pSketchLines->MethodAddByTwoPoints(poiline[446], poiline[447]);
	pSketchLines->MethodAddByTwoPoints(poiline[448], poiline[449]);
	pSketchLines->MethodAddByTwoPoints(poiline[450], poiline[451]);
	pSketchLines->MethodAddByTwoPoints(poiline[452], poiline[453]);
	pSketchLines->MethodAddByTwoPoints(poiline[454], poiline[455]);
	pSketchLines->MethodAddByTwoPoints(poiline[456], poiline[457]);
	pSketchLines->MethodAddByTwoPoints(poiline[458], poiline[459]);
	pSketchLines->MethodAddByTwoPoints(poiline[460], poiline[461]);
	pSketchLines->MethodAddByTwoPoints(poiline[462], poiline[463]);
	pSketchLines->MethodAddByTwoPoints(poiline[464], poiline[465]);
	pSketchLines->MethodAddByTwoPoints(poiline[466], poiline[467]);
	pSketchLines->MethodAddByTwoPoints(poiline[468], poiline[469]);
	pSketchLines->MethodAddByTwoPoints(poiline[470], poiline[471]);
	pSketchLines->MethodAddByTwoPoints(poiline[472], poiline[473]);
	pSketchLines->MethodAddByTwoPoints(poiline[474], poiline[475]);
	pSketchLines->MethodAddByTwoPoints(poiline[476], poiline[477]);
	pSketchLines->MethodAddByTwoPoints(poiline[478], poiline[479]);
	pSketchLines->MethodAddByTwoPoints(poiline[480], poiline[481]);
	pSketchLines->MethodAddByTwoPoints(poiline[482], poiline[483]);
	pSketchLines->MethodAddByTwoPoints(poiline[484], poiline[485]);
	pSketchLines->MethodAddByTwoPoints(poiline[486], poiline[487]);
	pSketchLines->MethodAddByTwoPoints(poiline[488], poiline[489]);
	pSketchLines->MethodAddByTwoPoints(poiline[490], poiline[491]);
	pSketchLines->MethodAddByTwoPoints(poiline[492], poiline[493]);
	pSketchLines->MethodAddByTwoPoints(poiline[494], poiline[495]);
	pSketchLines->MethodAddByTwoPoints(poiline[496], poiline[497]);
	pSketchLines->MethodAddByTwoPoints(poiline[498], poiline[499]);
	pSketchLines->MethodAddByTwoPoints(poiline[500], poiline[501]);
	pSketchLines->MethodAddByTwoPoints(poiline[502], poiline[503]);
	pSketchLines->MethodAddByTwoPoints(poiline[504], poiline[505]);
	pSketchLines->MethodAddByTwoPoints(poiline[506], poiline[507]);
	pSketchLines->MethodAddByTwoPoints(poiline[508], poiline[509]);
	pSketchLines->MethodAddByTwoPoints(poiline[510], poiline[511]);
	pSketchLines->MethodAddByTwoPoints(poiline[512], poiline[513]);
	pSketchLines->MethodAddByTwoPoints(poiline[514], poiline[515]);
	pSketchLines->MethodAddByTwoPoints(poiline[516], poiline[517]);
	pSketchLines->MethodAddByTwoPoints(poiline[518], poiline[519]);
	pSketchLines->MethodAddByTwoPoints(poiline[520], poiline[521]);
	pSketchLines->MethodAddByTwoPoints(poiline[522], poiline[523]);
	pSketchLines->MethodAddByTwoPoints(poiline[524], poiline[525]);
	pSketchLines->MethodAddByTwoPoints(poiline[526], poiline[527]);
	pSketchLines->MethodAddByTwoPoints(poiline[528], poiline[529]);
	pSketchLines->MethodAddByTwoPoints(poiline[530], poiline[531]);
	pSketchLines->MethodAddByTwoPoints(poiline[532], poiline[533]);
	pSketchLines->MethodAddByTwoPoints(poiline[534], poiline[535]);
	pSketchLines->MethodAddByTwoPoints(poiline[536], poiline[537]);
	pSketchLines->MethodAddByTwoPoints(poiline[538], poiline[539]);
	pSketchLines->MethodAddByTwoPoints(poiline[540], poiline[541]);
	pSketchLines->MethodAddByTwoPoints(poiline[542], poiline[543]);
	pSketchLines->MethodAddByTwoPoints(poiline[544], poiline[545]);
	pSketchLines->MethodAddByTwoPoints(poiline[546], poiline[547]);
	pSketchLines->MethodAddByTwoPoints(poiline[548], poiline[549]);
	pSketchLines->MethodAddByTwoPoints(poiline[550], poiline[551]);
	pSketchLines->MethodAddByTwoPoints(poiline[552], poiline[553]);
	pSketchLines->MethodAddByTwoPoints(poiline[554], poiline[555]);
	pSketchLines->MethodAddByTwoPoints(poiline[556], poiline[557]);
	pSketchLines->MethodAddByTwoPoints(poiline[558], poiline[559]);
	pSketchLines->MethodAddByTwoPoints(poiline[560], poiline[561]);
	pSketchLines->MethodAddByTwoPoints(poiline[562], poiline[563]);
	pSketchLines->MethodAddByTwoPoints(poiline[564], poiline[565]);
	pSketchLines->MethodAddByTwoPoints(poiline[566], poiline[567]);
	pSketchLines->MethodAddByTwoPoints(poiline[568], poiline[569]);
	pSketchLines->MethodAddByTwoPoints(poiline[570], poiline[571]);
	pSketchLines->MethodAddByTwoPoints(poiline[572], poiline[573]);
	pSketchLines->MethodAddByTwoPoints(poiline[574], poiline[575]);
	pSketchLines->MethodAddByTwoPoints(poiline[576], poiline[577]);
	pSketchLines->MethodAddByTwoPoints(poiline[578], poiline[579]);
	pSketchLines->MethodAddByTwoPoints(poiline[580], poiline[581]);
	pSketchLines->MethodAddByTwoPoints(poiline[582], poiline[583]);
	pSketchLines->MethodAddByTwoPoints(poiline[584], poiline[585]);
	pSketchLines->MethodAddByTwoPoints(poiline[586], poiline[587]);
	pSketchLines->MethodAddByTwoPoints(poiline[588], poiline[589]);
	pSketchLines->MethodAddByTwoPoints(poiline[590], poiline[591]);
	pSketchLines->MethodAddByTwoPoints(poiline[592], poiline[593]);
	pSketchLines->MethodAddByTwoPoints(poiline[594], poiline[595]);
	pSketchLines->MethodAddByTwoPoints(poiline[596], poiline[597]);
	pSketchLines->MethodAddByTwoPoints(poiline[598], poiline[599]);
	pSketchLines->MethodAddByTwoPoints(poiline[600], poiline[601]);
	pSketchLines->MethodAddByTwoPoints(poiline[602], poiline[603]);
	pSketchLines->MethodAddByTwoPoints(poiline[604], poiline[605]);
	pSketchLines->MethodAddByTwoPoints(poiline[606], poiline[607]);
	pSketchLines->MethodAddByTwoPoints(poiline[608], poiline[609]);
	pSketchLines->MethodAddByTwoPoints(poiline[610], poiline[611]);
	pSketchLines->MethodAddByTwoPoints(poiline[612], poiline[613]);
	pSketchLines->MethodAddByTwoPoints(poiline[614], poiline[615]);
	pSketchLines->MethodAddByTwoPoints(poiline[616], poiline[617]);
	pSketchLines->MethodAddByTwoPoints(poiline[618], poiline[619]);
	pSketchLines->MethodAddByTwoPoints(poiline[620], poiline[621]);
	pSketchLines->MethodAddByTwoPoints(poiline[622], poiline[623]);
	pSketchLines->MethodAddByTwoPoints(poiline[624], poiline[625]);
	pSketchLines->MethodAddByTwoPoints(poiline[626], poiline[627]);
	pSketchLines->MethodAddByTwoPoints(poiline[628], poiline[629]);
	pSketchLines->MethodAddByTwoPoints(poiline[630], poiline[631]);
	pSketchLines->MethodAddByTwoPoints(poiline[632], poiline[633]);
	pSketchLines->MethodAddByTwoPoints(poiline[634], poiline[635]);
	pSketchLines->MethodAddByTwoPoints(poiline[636], poiline[637]);
	pSketchLines->MethodAddByTwoPoints(poiline[638], poiline[639]);
	pSketchLines->MethodAddByTwoPoints(poiline[640], poiline[641]);
	pSketchLines->MethodAddByTwoPoints(poiline[642], poiline[643]);
	pSketchLines->MethodAddByTwoPoints(poiline[644], poiline[645]);
	pSketchLines->MethodAddByTwoPoints(poiline[646], poiline[647]);
	pSketchLines->MethodAddByTwoPoints(poiline[648], poiline[649]);
	pSketchLines->MethodAddByTwoPoints(poiline[650], poiline[651]);
	pSketchLines->MethodAddByTwoPoints(poiline[652], poiline[653]);
	pSketchLines->MethodAddByTwoPoints(poiline[654], poiline[655]);
	pSketchLines->MethodAddByTwoPoints(poiline[656], poiline[657]);
	pSketchLines->MethodAddByTwoPoints(poiline[658], poiline[659]);
	pSketchLines->MethodAddByTwoPoints(poiline[660], poiline[661]);
	pSketchLines->MethodAddByTwoPoints(poiline[662], poiline[663]);
	pSketchLines->MethodAddByTwoPoints(poiline[664], poiline[665]);
	pSketchLines->MethodAddByTwoPoints(poiline[666], poiline[667]);
	pSketchLines->MethodAddByTwoPoints(poiline[668], poiline[669]);
	pSketchLines->MethodAddByTwoPoints(poiline[670], poiline[671]);
	pSketchLines->MethodAddByTwoPoints(poiline[672], poiline[673]);
	pSketchLines->MethodAddByTwoPoints(poiline[674], poiline[675]);
	pSketchLines->MethodAddByTwoPoints(poiline[676], poiline[677]);
	pSketchLines->MethodAddByTwoPoints(poiline[678], poiline[679]);
	pSketchLines->MethodAddByTwoPoints(poiline[680], poiline[681]);
	pSketchLines->MethodAddByTwoPoints(poiline[682], poiline[683]);
	pSketchLines->MethodAddByTwoPoints(poiline[684], poiline[685]);
	pSketchLines->MethodAddByTwoPoints(poiline[686], poiline[687]);
	pSketchLines->MethodAddByTwoPoints(poiline[688], poiline[689]);
	pSketchLines->MethodAddByTwoPoints(poiline[690], poiline[691]);
	pSketchLines->MethodAddByTwoPoints(poiline[692], poiline[693]);
	pSketchLines->MethodAddByTwoPoints(poiline[694], poiline[695]);
	pSketchLines->MethodAddByTwoPoints(poiline[696], poiline[697]);
	pSketchLines->MethodAddByTwoPoints(poiline[698], poiline[699]);
	pSketchLines->MethodAddByTwoPoints(poiline[700], poiline[701]);
	pSketchLines->MethodAddByTwoPoints(poiline[702], poiline[703]);
	pSketchLines->MethodAddByTwoPoints(poiline[704], poiline[705]);
	pSketchLines->MethodAddByTwoPoints(poiline[706], poiline[707]);
	pSketchLines->MethodAddByTwoPoints(poiline[708], poiline[709]);
	pSketchLines->MethodAddByTwoPoints(poiline[710], poiline[711]);
	pSketchLines->MethodAddByTwoPoints(poiline[712], poiline[713]);
	pSketchLines->MethodAddByTwoPoints(poiline[714], poiline[715]);
	pSketchLines->MethodAddByTwoPoints(poiline[716], poiline[717]);
	pSketchLines->MethodAddByTwoPoints(poiline[718], poiline[719]);
	pSketchLines->MethodAddByTwoPoints(poiline[720], poiline[721]);
	pSketchLines->MethodAddByTwoPoints(poiline[722], poiline[723]);

	/*Стандартный текст внутри таблице*/
	poiline[190] = pTransGeom->MethodCreatePoint2d(0.66, 19.9);
	tb[1] = sk->TextBoxes->MethodAddFitted(poiline[190], L"Дубл.");
	poiline[191] = pTransGeom->MethodCreatePoint2d(0.66, 19.48);
	tb[2] = sk->TextBoxes->MethodAddFitted(poiline[191], L"Взам.");
	poiline[192] = pTransGeom->MethodCreatePoint2d(0.66, 19.06);
	tb[3] = sk->TextBoxes->MethodAddFitted(poiline[192], L"Подп.");
	poiline[193] = pTransGeom->MethodCreatePoint2d(0.66, 17.8);
	tb[4] = sk->TextBoxes->MethodAddFitted(poiline[193], L"Разраб");
	poiline[194] = pTransGeom->MethodCreatePoint2d(0.66, 17.38);
	tb[5] = sk->TextBoxes->MethodAddFitted(poiline[194], L"Принял");
	poiline[225] = pTransGeom->MethodCreatePoint2d(0.66, 16.96);
	tb[36] = sk->TextBoxes->MethodAddFitted(poiline[225], L"Проверил");
	poiline[195] = pTransGeom->MethodCreatePoint2d(0.66, 16.54);
	tb[6] = sk->TextBoxes->MethodAddFitted(poiline[195], L"Утвердил");
	poiline[196] = pTransGeom->MethodCreatePoint2d(0.66, 16.12);
	tb[7] = sk->TextBoxes->MethodAddFitted(poiline[196], L"Н. контр.");
	poiline[197] = pTransGeom->MethodCreatePoint2d(1.05, 15.67);
	tb[8] = sk->TextBoxes->MethodAddFitted(poiline[197], L"А");
	poiline[198] = pTransGeom->MethodCreatePoint2d(1.05, 15.25);
	tb[9] = sk->TextBoxes->MethodAddFitted(poiline[198], L"Б");
	poiline[199] = pTransGeom->MethodCreatePoint2d(3.5, 14.8);
	tb[10] = sk->TextBoxes->MethodAddFitted(poiline[199], L"Наименование детали, сб. единицы или материала");
	poiline[200] = pTransGeom->MethodCreatePoint2d(16.45, 14.8);
	tb[11] = sk->TextBoxes->MethodAddFitted(poiline[200], L"Обозначение, код");
	poiline[201] = pTransGeom->MethodCreatePoint2d(21.64, 14.8);
	tb[12] = sk->TextBoxes->MethodAddFitted(poiline[201], L"ОПП");
	poiline[202] = pTransGeom->MethodCreatePoint2d(25.80, 14.8);
	tb[13] = sk->TextBoxes->MethodAddFitted(poiline[202], L"КИ");
	poiline[203] = pTransGeom->MethodCreatePoint2d(23, 14.8);
	tb[14] = sk->TextBoxes->MethodAddFitted(poiline[203], L"ЕВ");
	poiline[204] = pTransGeom->MethodCreatePoint2d(24.2, 14.8);
	tb[15] = sk->TextBoxes->MethodAddFitted(poiline[204], L"ЕН");
	poiline[205] = pTransGeom->MethodCreatePoint2d(27.5, 14.8);
	tb[16] = sk->TextBoxes->MethodAddFitted(poiline[205], L"Н.расх.");
	poiline[206] = pTransGeom->MethodCreatePoint2d(19.3, 15.25);
	tb[17] = sk->TextBoxes->MethodAddFitted(poiline[206], L"КР");
	poiline[207] = pTransGeom->MethodCreatePoint2d(2.14, 15.67);
	tb[18] = sk->TextBoxes->MethodAddFitted(poiline[207], L"Цех");
	poiline[208] = pTransGeom->MethodCreatePoint2d(3.22, 15.67);
	tb[19] = sk->TextBoxes->MethodAddFitted(poiline[208], L"Уч.");
	poiline[209] = pTransGeom->MethodCreatePoint2d(4.15, 15.67);
	tb[20] = sk->TextBoxes->MethodAddFitted(poiline[209], L"РМ");
	poiline[210] = pTransGeom->MethodCreatePoint2d(5.23, 15.67);
	tb[21] = sk->TextBoxes->MethodAddFitted(poiline[210], L"Опер.");
	poiline[211] = pTransGeom->MethodCreatePoint2d(7.64, 15.67);
	tb[22] = sk->TextBoxes->MethodAddFitted(poiline[211], L"Код, наименование операции");
	poiline[212] = pTransGeom->MethodCreatePoint2d(18, 15.67);
	tb[23] = sk->TextBoxes->MethodAddFitted(poiline[212], L"Обозначение документа");
	poiline[213] = pTransGeom->MethodCreatePoint2d(4.13, 15.25);
	tb[24] = sk->TextBoxes->MethodAddFitted(poiline[213], L"Код,наименование,оборудования");
	poiline[214] = pTransGeom->MethodCreatePoint2d(14.1, 15.25);
	tb[25] = sk->TextBoxes->MethodAddFitted(poiline[214], L"СМ");
	poiline[215] = pTransGeom->MethodCreatePoint2d(17, 15.25);
	tb[26] = sk->TextBoxes->MethodAddFitted(poiline[215], L"Р");
	poiline[216] = pTransGeom->MethodCreatePoint2d(18.23, 15.25);
	tb[27] = sk->TextBoxes->MethodAddFitted(poiline[216], L"УТ");
	poiline[217] = pTransGeom->MethodCreatePoint2d(20.2, 15.25);
	tb[28] = sk->TextBoxes->MethodAddFitted(poiline[217], L"КОНД");
	poiline[218] = pTransGeom->MethodCreatePoint2d(21.75, 15.25);
	tb[29] = sk->TextBoxes->MethodAddFitted(poiline[218], L"ЕН");
	poiline[219] = pTransGeom->MethodCreatePoint2d(23, 15.25);
	tb[30] = sk->TextBoxes->MethodAddFitted(poiline[219], L"ОП");
	poiline[220] = pTransGeom->MethodCreatePoint2d(24.1, 15.25);
	tb[31] = sk->TextBoxes->MethodAddFitted(poiline[220], L"К шт.");
	poiline[221] = pTransGeom->MethodCreatePoint2d(25.75, 15.25);
	tb[32] = sk->TextBoxes->MethodAddFitted(poiline[221], L"Т пз.");
	poiline[222] = pTransGeom->MethodCreatePoint2d(27.60, 15.25);
	tb[33] = sk->TextBoxes->MethodAddFitted(poiline[222], L"Т шт.");
	poiline[223] = pTransGeom->MethodCreatePoint2d(15.4, 15.25);
	tb[34] = sk->TextBoxes->MethodAddFitted(poiline[223], L"Проф.");
	poiline[226] = pTransGeom->MethodCreatePoint2d(0.85, 14.8);
	tb[37] = sk->TextBoxes->MethodAddFitted(poiline[226], L"К/М");
	poiline[227] = pTransGeom->MethodCreatePoint2d(1.1, 0.6);
	tb[38] = sk->TextBoxes->MethodAddFitted(poiline[227], L"МК");
	/*Конец (Стандартны текст внутри таблице)*/

	/*Размер шрифта*/
	TextStylePtr pStyle;
	pStyle = tb[1]->GetStyle();
	pStyle->PutFontSize(0.26);
	tb[1]->PutStyle(pStyle);

	sk->raw_ExitEdit();//закрытие редактирования чертежа
}

void CprTextCardApp::MakeSqMKlist2()
{
	SheetPtr sheet = sh->GetItem(1);//создание указателя на лист
	sheet->MethodUpdate();;
	sheet->Border->MethodDelete();
	sheet->TitleBlock->MethodDelete();
	sheet->put_Size(kCustomDrawingSheetSize);
	sheet->put_Height(21);
	sheet->put_Width(29.7);
	SketchedSymbolsPtr ss;

	DrawingSketchPtr sk = sheet->GetSketches()->MethodAdd();//добавление эскиза на лист

	sk->raw_Edit();//начало редактирования эскиза
	SketchLinesPtr pSketchLines;
	sk->get_SketchLines(&pSketchLines);//создание указателя на коллекцию линий

	Point2dPtr poiline[1000];//переменная для хранения точек
	TextBoxPtr tb[300];//переменная для хранения точек текста

					   /*1 Лист*/

					   /*Рамка*/
	poiline[0] = pTransGeom->MethodCreatePoint2d(0, 0);
	poiline[1] = pTransGeom->MethodCreatePoint2d(0, 21);
	poiline[2] = pTransGeom->MethodCreatePoint2d(29.7, 21);
	poiline[3] = pTransGeom->MethodCreatePoint2d(29.7, 0);

	pSketchLines->MethodAddByTwoPoints(poiline[0], poiline[1]);
	pSketchLines->MethodAddByTwoPoints(poiline[1], poiline[2]);
	pSketchLines->MethodAddByTwoPoints(poiline[2], poiline[3]);
	pSketchLines->MethodAddByTwoPoints(poiline[3], poiline[0]);

	/*Б6ф1*/
	poiline[4] = pTransGeom->MethodCreatePoint2d(0.55, 0.85);
	poiline[5] = pTransGeom->MethodCreatePoint2d(29.15, 0.85);

	pSketchLines->MethodAddByTwoPoints(poiline[4], poiline[5]);

	/*Таблица*/
	poiline[6] = pTransGeom->MethodCreatePoint2d(0.55, 0);
	poiline[7] = pTransGeom->MethodCreatePoint2d(29.15, 0);
	poiline[8] = pTransGeom->MethodCreatePoint2d(0.55, 16.575);
	poiline[9] = pTransGeom->MethodCreatePoint2d(29.15, 16.575);

	pSketchLines->MethodAddByTwoPoints(poiline[6], poiline[8]);
	pSketchLines->MethodAddByTwoPoints(poiline[7], poiline[9]);
	pSketchLines->MethodAddByTwoPoints(poiline[8], poiline[9]);

	/*Строки и столбцы в таблице*/
	poiline[10] = pTransGeom->MethodCreatePoint2d(0.55, 1.7);
	poiline[11] = pTransGeom->MethodCreatePoint2d(29.15, 1.7);
	poiline[12] = pTransGeom->MethodCreatePoint2d(0.55, 2.55);
	poiline[13] = pTransGeom->MethodCreatePoint2d(29.15, 2.55);
	poiline[14] = pTransGeom->MethodCreatePoint2d(0.55, 3.4);
	poiline[15] = pTransGeom->MethodCreatePoint2d(29.15, 3.4);
	poiline[16] = pTransGeom->MethodCreatePoint2d(0.55, 4.25);
	poiline[17] = pTransGeom->MethodCreatePoint2d(29.15, 4.25);
	poiline[18] = pTransGeom->MethodCreatePoint2d(0.55, 5.1);
	poiline[19] = pTransGeom->MethodCreatePoint2d(29.15, 5.1);
	poiline[20] = pTransGeom->MethodCreatePoint2d(0.55, 5.95);
	poiline[21] = pTransGeom->MethodCreatePoint2d(29.15, 5.95);
	poiline[22] = pTransGeom->MethodCreatePoint2d(0.55, 6.8);
	poiline[23] = pTransGeom->MethodCreatePoint2d(29.15, 6.8);
	poiline[24] = pTransGeom->MethodCreatePoint2d(0.55, 7.65);
	poiline[25] = pTransGeom->MethodCreatePoint2d(29.15, 7.65);
	poiline[26] = pTransGeom->MethodCreatePoint2d(0.55, 8.5);
	poiline[27] = pTransGeom->MethodCreatePoint2d(29.15, 8.5);
	poiline[28] = pTransGeom->MethodCreatePoint2d(0.55, 9.35);
	poiline[29] = pTransGeom->MethodCreatePoint2d(29.15, 9.35);
	poiline[30] = pTransGeom->MethodCreatePoint2d(0.55, 10.2);
	poiline[31] = pTransGeom->MethodCreatePoint2d(29.15, 10.2);
	poiline[32] = pTransGeom->MethodCreatePoint2d(0.55, 11.05);
	poiline[33] = pTransGeom->MethodCreatePoint2d(29.15, 11.05);
	poiline[34] = pTransGeom->MethodCreatePoint2d(0.55, 11.9);
	poiline[35] = pTransGeom->MethodCreatePoint2d(29.15, 11.9);
	poiline[36] = pTransGeom->MethodCreatePoint2d(0.55, 12.75);
	poiline[37] = pTransGeom->MethodCreatePoint2d(29.15, 12.75);
	poiline[38] = pTransGeom->MethodCreatePoint2d(0.55, 13.6);
	poiline[39] = pTransGeom->MethodCreatePoint2d(29.15, 13.6);
	poiline[40] = pTransGeom->MethodCreatePoint2d(0.55, 15.3);
	poiline[41] = pTransGeom->MethodCreatePoint2d(29.15, 15.3);
	poiline[42] = pTransGeom->MethodCreatePoint2d(0.55, 15.725);
	poiline[43] = pTransGeom->MethodCreatePoint2d(29.15, 15.725);
	poiline[44] = pTransGeom->MethodCreatePoint2d(0.55, 16.15);
	poiline[45] = pTransGeom->MethodCreatePoint2d(29.15, 16.15);
	poiline[46] = pTransGeom->MethodCreatePoint2d(1.85, 0.85);
	poiline[47] = pTransGeom->MethodCreatePoint2d(1.85, 16.575);
	poiline[48] = pTransGeom->MethodCreatePoint2d(2.89, 16.575);
	poiline[49] = pTransGeom->MethodCreatePoint2d(2.89, 16.15);
	poiline[50] = pTransGeom->MethodCreatePoint2d(3.93, 16.575);
	poiline[51] = pTransGeom->MethodCreatePoint2d(3.93, 16.15);
	poiline[52] = pTransGeom->MethodCreatePoint2d(4.97, 16.575);
	poiline[53] = pTransGeom->MethodCreatePoint2d(4.97, 16.15);
	poiline[54] = pTransGeom->MethodCreatePoint2d(6.27, 16.575);
	poiline[55] = pTransGeom->MethodCreatePoint2d(6.27, 16.15);
	poiline[56] = pTransGeom->MethodCreatePoint2d(13.81, 16.575);
	poiline[57] = pTransGeom->MethodCreatePoint2d(13.81, 15.3);
	poiline[58] = pTransGeom->MethodCreatePoint2d(14.85, 16.15);
	poiline[59] = pTransGeom->MethodCreatePoint2d(14.85, 15.725);
	poiline[60] = pTransGeom->MethodCreatePoint2d(16.67, 16.15);
	poiline[61] = pTransGeom->MethodCreatePoint2d(16.67, 15.725);
	poiline[62] = pTransGeom->MethodCreatePoint2d(17.71, 16.15);
	poiline[63] = pTransGeom->MethodCreatePoint2d(17.71, 15.725);
	poiline[64] = pTransGeom->MethodCreatePoint2d(19.01, 16.15);
	poiline[65] = pTransGeom->MethodCreatePoint2d(19.01, 15.725);
	poiline[66] = pTransGeom->MethodCreatePoint2d(20.05, 16.15);
	poiline[67] = pTransGeom->MethodCreatePoint2d(20.05, 15.725);
	poiline[68] = pTransGeom->MethodCreatePoint2d(21.35, 16.15);
	poiline[69] = pTransGeom->MethodCreatePoint2d(21.35, 15.3);
	poiline[70] = pTransGeom->MethodCreatePoint2d(22.65, 16.15);
	poiline[71] = pTransGeom->MethodCreatePoint2d(22.65, 15.3);
	poiline[72] = pTransGeom->MethodCreatePoint2d(23.95, 16.15);
	poiline[73] = pTransGeom->MethodCreatePoint2d(23.95, 15.3);
	poiline[74] = pTransGeom->MethodCreatePoint2d(25.25, 16.15);
	poiline[75] = pTransGeom->MethodCreatePoint2d(25.25, 15.3);
	poiline[76] = pTransGeom->MethodCreatePoint2d(27.07, 16.15);
	poiline[77] = pTransGeom->MethodCreatePoint2d(27.07, 15.3);
	poiline[172] = pTransGeom->MethodCreatePoint2d(0.55, 14.45);
	poiline[173] = pTransGeom->MethodCreatePoint2d(29.15, 14.45);

	pSketchLines->MethodAddByTwoPoints(poiline[172], poiline[173]);
	pSketchLines->MethodAddByTwoPoints(poiline[10], poiline[11]);
	pSketchLines->MethodAddByTwoPoints(poiline[12], poiline[13]);
	pSketchLines->MethodAddByTwoPoints(poiline[14], poiline[15]);
	pSketchLines->MethodAddByTwoPoints(poiline[16], poiline[17]);
	pSketchLines->MethodAddByTwoPoints(poiline[18], poiline[19]);
	pSketchLines->MethodAddByTwoPoints(poiline[20], poiline[21]);
	pSketchLines->MethodAddByTwoPoints(poiline[22], poiline[23]);
	pSketchLines->MethodAddByTwoPoints(poiline[24], poiline[25]);
	pSketchLines->MethodAddByTwoPoints(poiline[26], poiline[27]);
	pSketchLines->MethodAddByTwoPoints(poiline[28], poiline[29]);
	pSketchLines->MethodAddByTwoPoints(poiline[30], poiline[31]);
	pSketchLines->MethodAddByTwoPoints(poiline[32], poiline[33]);
	pSketchLines->MethodAddByTwoPoints(poiline[34], poiline[35]);
	pSketchLines->MethodAddByTwoPoints(poiline[36], poiline[37]);
	pSketchLines->MethodAddByTwoPoints(poiline[38], poiline[39]);
	pSketchLines->MethodAddByTwoPoints(poiline[40], poiline[41]);
	pSketchLines->MethodAddByTwoPoints(poiline[42], poiline[43]);
	pSketchLines->MethodAddByTwoPoints(poiline[44], poiline[45]);
	pSketchLines->MethodAddByTwoPoints(poiline[46], poiline[47]);
	pSketchLines->MethodAddByTwoPoints(poiline[48], poiline[49]);
	pSketchLines->MethodAddByTwoPoints(poiline[50], poiline[51]);
	pSketchLines->MethodAddByTwoPoints(poiline[52], poiline[53]);
	pSketchLines->MethodAddByTwoPoints(poiline[54], poiline[55]);
	pSketchLines->MethodAddByTwoPoints(poiline[56], poiline[57]);
	pSketchLines->MethodAddByTwoPoints(poiline[58], poiline[59]);
	pSketchLines->MethodAddByTwoPoints(poiline[60], poiline[61]);
	pSketchLines->MethodAddByTwoPoints(poiline[62], poiline[63]);
	pSketchLines->MethodAddByTwoPoints(poiline[64], poiline[65]);
	pSketchLines->MethodAddByTwoPoints(poiline[66], poiline[67]);
	pSketchLines->MethodAddByTwoPoints(poiline[68], poiline[69]);
	pSketchLines->MethodAddByTwoPoints(poiline[70], poiline[71]);
	pSketchLines->MethodAddByTwoPoints(poiline[72], poiline[73]);
	pSketchLines->MethodAddByTwoPoints(poiline[74], poiline[75]);
	pSketchLines->MethodAddByTwoPoints(poiline[76], poiline[77]);

	/*Б2Ф2*/
	poiline[78] = pTransGeom->MethodCreatePoint2d(0.55, 17.85);
	poiline[79] = pTransGeom->MethodCreatePoint2d(29.15, 17.85);
	poiline[80] = pTransGeom->MethodCreatePoint2d(29.15, 14.875);
	poiline[81] = pTransGeom->MethodCreatePoint2d(29.15, 16.575);
	poiline[82] = pTransGeom->MethodCreatePoint2d(12.51, 17.85);
	poiline[83] = pTransGeom->MethodCreatePoint2d(12.51, 16.575);
	poiline[84] = pTransGeom->MethodCreatePoint2d(14.85, 17.85);
	poiline[85] = pTransGeom->MethodCreatePoint2d(14.85, 16.575);
	poiline[86] = pTransGeom->MethodCreatePoint2d(16.93, 17.85);
	poiline[87] = pTransGeom->MethodCreatePoint2d(16.93, 16.575);
	poiline[88] = pTransGeom->MethodCreatePoint2d(2.37, 17.425);
	poiline[89] = pTransGeom->MethodCreatePoint2d(18.49, 17.425);
	poiline[90] = pTransGeom->MethodCreatePoint2d(2.37, 17);
	poiline[91] = pTransGeom->MethodCreatePoint2d(18.49, 17);
	poiline[92] = pTransGeom->MethodCreatePoint2d(0.55, 16.15);
	poiline[93] = pTransGeom->MethodCreatePoint2d(18.49, 16.15);
	poiline[94] = pTransGeom->MethodCreatePoint2d(11.47, 17.85);
	poiline[95] = pTransGeom->MethodCreatePoint2d(11.47, 16.575);
	poiline[102] = pTransGeom->MethodCreatePoint2d(10.43, 17.85);
	poiline[103] = pTransGeom->MethodCreatePoint2d(10.43, 16.575);
	poiline[104] = pTransGeom->MethodCreatePoint2d(10.43, 17.85);
	poiline[105] = pTransGeom->MethodCreatePoint2d(10.43, 16.575);
	poiline[106] = pTransGeom->MethodCreatePoint2d(8.87, 17.85);
	poiline[107] = pTransGeom->MethodCreatePoint2d(8.87, 16.575);
	poiline[108] = pTransGeom->MethodCreatePoint2d(6.79, 17.85);
	poiline[109] = pTransGeom->MethodCreatePoint2d(6.79, 16.575);
	poiline[110] = pTransGeom->MethodCreatePoint2d(4.45, 17.85);
	poiline[111] = pTransGeom->MethodCreatePoint2d(4.45, 16.575);
	poiline[112] = pTransGeom->MethodCreatePoint2d(3.41, 17.85);
	poiline[113] = pTransGeom->MethodCreatePoint2d(3.41, 16.575);
	poiline[114] = pTransGeom->MethodCreatePoint2d(2.37, 17.85);
	poiline[174] = pTransGeom->MethodCreatePoint2d(2.37, 16.575);

	pSketchLines->MethodAddByTwoPoints(poiline[102], poiline[103]);
	pSketchLines->MethodAddByTwoPoints(poiline[104], poiline[105]);
	pSketchLines->MethodAddByTwoPoints(poiline[106], poiline[107]);
	pSketchLines->MethodAddByTwoPoints(poiline[108], poiline[109]);
	pSketchLines->MethodAddByTwoPoints(poiline[110], poiline[111]);
	pSketchLines->MethodAddByTwoPoints(poiline[112], poiline[113]);
	pSketchLines->MethodAddByTwoPoints(poiline[114], poiline[174]);

	pSketchLines->MethodAddByTwoPoints(poiline[78], poiline[79]);
	pSketchLines->MethodAddByTwoPoints(poiline[79], poiline[80]);
	pSketchLines->MethodAddByTwoPoints(poiline[80], poiline[81]);
	pSketchLines->MethodAddByTwoPoints(poiline[82], poiline[83]);
	pSketchLines->MethodAddByTwoPoints(poiline[84], poiline[85]);
	pSketchLines->MethodAddByTwoPoints(poiline[86], poiline[87]);
	pSketchLines->MethodAddByTwoPoints(poiline[88], poiline[89]);
	pSketchLines->MethodAddByTwoPoints(poiline[90], poiline[91]);
	pSketchLines->MethodAddByTwoPoints(poiline[92], poiline[93]);
	pSketchLines->MethodAddByTwoPoints(poiline[94], poiline[95]);

	///*Б1Ф2*/
	poiline[96] = pTransGeom->MethodCreatePoint2d(29.15, 16.575);
	poiline[97] = pTransGeom->MethodCreatePoint2d(29.15, 17.85);
	poiline[98] = pTransGeom->MethodCreatePoint2d(24.47, 16.575);
	poiline[99] = pTransGeom->MethodCreatePoint2d(24.47, 17.85);
	poiline[100] = pTransGeom->MethodCreatePoint2d(18.49, 16.575);
	poiline[101] = pTransGeom->MethodCreatePoint2d(18.49, 17.85);

	pSketchLines->MethodAddByTwoPoints(poiline[96], poiline[97]);
	pSketchLines->MethodAddByTwoPoints(poiline[97], poiline[99]);
	pSketchLines->MethodAddByTwoPoints(poiline[98], poiline[99]);
	pSketchLines->MethodAddByTwoPoints(poiline[100], poiline[101]);
	pSketchLines->MethodAddByTwoPoints(poiline[101], poiline[99]);

	/*Б5Ф2*/
	poiline[115] = pTransGeom->MethodCreatePoint2d(0.55, 16.575);
	poiline[116] = pTransGeom->MethodCreatePoint2d(0.55, 18.7);
	poiline[117] = pTransGeom->MethodCreatePoint2d(29.15, 18.7);
	poiline[118] = pTransGeom->MethodCreatePoint2d(29.15, 17.85);
	poiline[119] = pTransGeom->MethodCreatePoint2d(15.37, 18.7);
	poiline[120] = pTransGeom->MethodCreatePoint2d(15.37, 18.5);
	poiline[121] = pTransGeom->MethodCreatePoint2d(21.35, 18.7);
	poiline[122] = pTransGeom->MethodCreatePoint2d(21.35, 17.85);
	poiline[123] = pTransGeom->MethodCreatePoint2d(26.03, 18.7);
	poiline[124] = pTransGeom->MethodCreatePoint2d(26.03, 17.85);
	poiline[125] = pTransGeom->MethodCreatePoint2d(27.59, 18.7);
	poiline[126] = pTransGeom->MethodCreatePoint2d(27.59, 17.85);

	pSketchLines->MethodAddByTwoPoints(poiline[115], poiline[116]);
	pSketchLines->MethodAddByTwoPoints(poiline[116], poiline[117]);
	pSketchLines->MethodAddByTwoPoints(poiline[117], poiline[118]);
	pSketchLines->MethodAddByTwoPoints(poiline[119], poiline[120]);
	pSketchLines->MethodAddByTwoPoints(poiline[121], poiline[122]);
	pSketchLines->MethodAddByTwoPoints(poiline[123], poiline[124]);
	pSketchLines->MethodAddByTwoPoints(poiline[125], poiline[126]);

	/*Б4Ф2*/
	poiline[127] = pTransGeom->MethodCreatePoint2d(0.55, 18.7);
	poiline[128] = pTransGeom->MethodCreatePoint2d(0.55, 19.975);
	poiline[129] = pTransGeom->MethodCreatePoint2d(8.09, 19.975);
	poiline[130] = pTransGeom->MethodCreatePoint2d(8.09, 18.7);
	poiline[131] = pTransGeom->MethodCreatePoint2d(2.37, 19.975);
	poiline[132] = pTransGeom->MethodCreatePoint2d(2.37, 18.7);
	poiline[133] = pTransGeom->MethodCreatePoint2d(4.45, 19.975);
	poiline[134] = pTransGeom->MethodCreatePoint2d(4.45, 18.7);
	poiline[135] = pTransGeom->MethodCreatePoint2d(6.53, 19.975);
	poiline[136] = pTransGeom->MethodCreatePoint2d(6.53, 18.7);
	poiline[137] = pTransGeom->MethodCreatePoint2d(0.55, 19.55);
	poiline[138] = pTransGeom->MethodCreatePoint2d(8.09, 19.55);
	poiline[139] = pTransGeom->MethodCreatePoint2d(0.55, 19.125);
	poiline[140] = pTransGeom->MethodCreatePoint2d(8.09, 19.125);

	pSketchLines->MethodAddByTwoPoints(poiline[127], poiline[128]);
	pSketchLines->MethodAddByTwoPoints(poiline[128], poiline[129]);
	pSketchLines->MethodAddByTwoPoints(poiline[129], poiline[130]);
	pSketchLines->MethodAddByTwoPoints(poiline[131], poiline[132]);
	pSketchLines->MethodAddByTwoPoints(poiline[133], poiline[134]);
	pSketchLines->MethodAddByTwoPoints(poiline[135], poiline[136]);
	pSketchLines->MethodAddByTwoPoints(poiline[137], poiline[138]);
	pSketchLines->MethodAddByTwoPoints(poiline[139], poiline[140]);

	/*Б3Ф1а*/
	poiline[141] = pTransGeom->MethodCreatePoint2d(21.09, 18.7);
	poiline[142] = pTransGeom->MethodCreatePoint2d(21.09, 20.4);
	poiline[143] = pTransGeom->MethodCreatePoint2d(29.15, 20.4);
	poiline[144] = pTransGeom->MethodCreatePoint2d(29.15, 18.7);
	poiline[145] = pTransGeom->MethodCreatePoint2d(21.09, 19.975);
	poiline[146] = pTransGeom->MethodCreatePoint2d(29.15, 19.975);
	poiline[147] = pTransGeom->MethodCreatePoint2d(21.09, 19.55);
	poiline[148] = pTransGeom->MethodCreatePoint2d(29.15, 19.55);
	poiline[149] = pTransGeom->MethodCreatePoint2d(21.09, 19.125);
	poiline[150] = pTransGeom->MethodCreatePoint2d(29.15, 19.125);
	poiline[151] = pTransGeom->MethodCreatePoint2d(22.13, 20.4);
	poiline[152] = pTransGeom->MethodCreatePoint2d(22.13, 18.7);
	poiline[153] = pTransGeom->MethodCreatePoint2d(23.17, 20.4);
	poiline[154] = pTransGeom->MethodCreatePoint2d(23.17, 18.7);
	poiline[155] = pTransGeom->MethodCreatePoint2d(25.51, 20.4);
	poiline[156] = pTransGeom->MethodCreatePoint2d(25.51, 18.7);
	poiline[157] = pTransGeom->MethodCreatePoint2d(27.59, 20.4);
	poiline[158] = pTransGeom->MethodCreatePoint2d(27.59, 18.7);

	pSketchLines->MethodAddByTwoPoints(poiline[141], poiline[142]);
	pSketchLines->MethodAddByTwoPoints(poiline[142], poiline[143]);
	pSketchLines->MethodAddByTwoPoints(poiline[143], poiline[144]);
	pSketchLines->MethodAddByTwoPoints(poiline[145], poiline[146]);
	pSketchLines->MethodAddByTwoPoints(poiline[147], poiline[148]);
	pSketchLines->MethodAddByTwoPoints(poiline[149], poiline[150]);
	pSketchLines->MethodAddByTwoPoints(poiline[151], poiline[152]);
	pSketchLines->MethodAddByTwoPoints(poiline[153], poiline[154]);
	pSketchLines->MethodAddByTwoPoints(poiline[155], poiline[156]);
	pSketchLines->MethodAddByTwoPoints(poiline[157], poiline[158]);

	/*Б3Ф2в*/
	poiline[159] = pTransGeom->MethodCreatePoint2d(13.03, 18.7);
	poiline[160] = pTransGeom->MethodCreatePoint2d(13.03, 19.55);
	poiline[161] = pTransGeom->MethodCreatePoint2d(21.09, 19.55);
	poiline[162] = pTransGeom->MethodCreatePoint2d(14.07, 18.7);
	poiline[163] = pTransGeom->MethodCreatePoint2d(14.07, 19.55);
	poiline[164] = pTransGeom->MethodCreatePoint2d(15.11, 18.7);
	poiline[165] = pTransGeom->MethodCreatePoint2d(15.11, 19.55);
	poiline[166] = pTransGeom->MethodCreatePoint2d(17.45, 18.7);
	poiline[167] = pTransGeom->MethodCreatePoint2d(17.45, 19.55);
	poiline[168] = pTransGeom->MethodCreatePoint2d(19.53, 18.7);
	poiline[169] = pTransGeom->MethodCreatePoint2d(19.53, 19.55);
	poiline[170] = pTransGeom->MethodCreatePoint2d(13.03, 19.125);
	poiline[171] = pTransGeom->MethodCreatePoint2d(21.09, 19.125);

	pSketchLines->MethodAddByTwoPoints(poiline[159], poiline[160]);
	pSketchLines->MethodAddByTwoPoints(poiline[160], poiline[161]);
	pSketchLines->MethodAddByTwoPoints(poiline[162], poiline[163]);
	pSketchLines->MethodAddByTwoPoints(poiline[164], poiline[165]);
	pSketchLines->MethodAddByTwoPoints(poiline[166], poiline[167]);
	pSketchLines->MethodAddByTwoPoints(poiline[168], poiline[169]);
	pSketchLines->MethodAddByTwoPoints(poiline[170], poiline[171]);

	/*2мм линии внутри таблицы*/
	poiline[244] = pTransGeom->MethodCreatePoint2d(2.89, 11.9);
	poiline[245] = pTransGeom->MethodCreatePoint2d(2.89, 11.7);
	poiline[246] = pTransGeom->MethodCreatePoint2d(2.89, 11.05);
	poiline[247] = pTransGeom->MethodCreatePoint2d(2.89, 10.85);
	poiline[248] = pTransGeom->MethodCreatePoint2d(2.89, 10.2);
	poiline[249] = pTransGeom->MethodCreatePoint2d(2.89, 10);
	poiline[250] = pTransGeom->MethodCreatePoint2d(2.89, 9.35);
	poiline[251] = pTransGeom->MethodCreatePoint2d(2.89, 9.15);
	poiline[252] = pTransGeom->MethodCreatePoint2d(2.89, 8.5);
	poiline[253] = pTransGeom->MethodCreatePoint2d(2.89, 8.3);
	poiline[254] = pTransGeom->MethodCreatePoint2d(2.89, 7.65);
	poiline[255] = pTransGeom->MethodCreatePoint2d(2.89, 7.45);
	poiline[256] = pTransGeom->MethodCreatePoint2d(2.89, 6.8);
	poiline[257] = pTransGeom->MethodCreatePoint2d(2.89, 6.6);
	poiline[258] = pTransGeom->MethodCreatePoint2d(2.89, 5.95);
	poiline[259] = pTransGeom->MethodCreatePoint2d(2.89, 5.75);
	poiline[260] = pTransGeom->MethodCreatePoint2d(2.89, 5.1);
	poiline[261] = pTransGeom->MethodCreatePoint2d(2.89, 4.9);
	poiline[262] = pTransGeom->MethodCreatePoint2d(2.89, 4.25);
	poiline[263] = pTransGeom->MethodCreatePoint2d(2.89, 4.05);
	poiline[264] = pTransGeom->MethodCreatePoint2d(2.89, 3.4);
	poiline[265] = pTransGeom->MethodCreatePoint2d(2.89, 3.2);
	poiline[266] = pTransGeom->MethodCreatePoint2d(2.89, 2.55);
	poiline[267] = pTransGeom->MethodCreatePoint2d(2.89, 2.35);
	poiline[268] = pTransGeom->MethodCreatePoint2d(2.89, 1.7);
	poiline[269] = pTransGeom->MethodCreatePoint2d(2.89, 1.5);
	poiline[270] = pTransGeom->MethodCreatePoint2d(3.93, 11.9);
	poiline[271] = pTransGeom->MethodCreatePoint2d(3.93, 11.7);
	poiline[272] = pTransGeom->MethodCreatePoint2d(3.93, 11.05);
	poiline[273] = pTransGeom->MethodCreatePoint2d(3.93, 10.85);
	poiline[274] = pTransGeom->MethodCreatePoint2d(3.93, 10.2);
	poiline[275] = pTransGeom->MethodCreatePoint2d(3.93, 10);
	poiline[276] = pTransGeom->MethodCreatePoint2d(3.93, 9.35);
	poiline[277] = pTransGeom->MethodCreatePoint2d(3.93, 9.15);
	poiline[278] = pTransGeom->MethodCreatePoint2d(3.93, 8.5);
	poiline[279] = pTransGeom->MethodCreatePoint2d(3.93, 8.3);
	poiline[280] = pTransGeom->MethodCreatePoint2d(3.93, 7.65);
	poiline[281] = pTransGeom->MethodCreatePoint2d(3.93, 7.45);
	poiline[282] = pTransGeom->MethodCreatePoint2d(3.93, 6.8);
	poiline[283] = pTransGeom->MethodCreatePoint2d(3.93, 6.6);
	poiline[284] = pTransGeom->MethodCreatePoint2d(3.93, 5.95);
	poiline[285] = pTransGeom->MethodCreatePoint2d(3.93, 5.75);
	poiline[286] = pTransGeom->MethodCreatePoint2d(3.93, 5.1);
	poiline[287] = pTransGeom->MethodCreatePoint2d(3.93, 4.9);
	poiline[288] = pTransGeom->MethodCreatePoint2d(3.93, 4.25);
	poiline[289] = pTransGeom->MethodCreatePoint2d(3.93, 4.05);
	poiline[290] = pTransGeom->MethodCreatePoint2d(3.93, 3.4);
	poiline[291] = pTransGeom->MethodCreatePoint2d(3.93, 3.2);
	poiline[292] = pTransGeom->MethodCreatePoint2d(3.93, 2.55);
	poiline[293] = pTransGeom->MethodCreatePoint2d(3.93, 2.35);
	poiline[294] = pTransGeom->MethodCreatePoint2d(3.93, 1.7);
	poiline[295] = pTransGeom->MethodCreatePoint2d(3.93, 1.5);
	poiline[296] = pTransGeom->MethodCreatePoint2d(4.97, 11.9);
	poiline[297] = pTransGeom->MethodCreatePoint2d(4.97, 11.7);
	poiline[298] = pTransGeom->MethodCreatePoint2d(4.97, 11.05);
	poiline[299] = pTransGeom->MethodCreatePoint2d(4.97, 10.85);
	poiline[300] = pTransGeom->MethodCreatePoint2d(4.97, 10.2);
	poiline[301] = pTransGeom->MethodCreatePoint2d(4.97, 10);
	poiline[302] = pTransGeom->MethodCreatePoint2d(4.97, 9.35);
	poiline[303] = pTransGeom->MethodCreatePoint2d(4.97, 9.15);
	poiline[304] = pTransGeom->MethodCreatePoint2d(4.97, 8.5);
	poiline[305] = pTransGeom->MethodCreatePoint2d(4.97, 8.3);
	poiline[306] = pTransGeom->MethodCreatePoint2d(4.97, 7.65);
	poiline[307] = pTransGeom->MethodCreatePoint2d(4.97, 7.45);
	poiline[308] = pTransGeom->MethodCreatePoint2d(4.97, 6.8);
	poiline[309] = pTransGeom->MethodCreatePoint2d(4.97, 6.6);
	poiline[310] = pTransGeom->MethodCreatePoint2d(4.97, 5.95);
	poiline[311] = pTransGeom->MethodCreatePoint2d(4.97, 5.75);
	poiline[312] = pTransGeom->MethodCreatePoint2d(4.97, 5.1);
	poiline[313] = pTransGeom->MethodCreatePoint2d(4.97, 4.9);
	poiline[314] = pTransGeom->MethodCreatePoint2d(4.97, 4.25);
	poiline[315] = pTransGeom->MethodCreatePoint2d(4.97, 4.05);
	poiline[316] = pTransGeom->MethodCreatePoint2d(4.97, 3.4);
	poiline[317] = pTransGeom->MethodCreatePoint2d(4.97, 3.2);
	poiline[318] = pTransGeom->MethodCreatePoint2d(4.97, 2.55);
	poiline[319] = pTransGeom->MethodCreatePoint2d(4.97, 2.35);
	poiline[320] = pTransGeom->MethodCreatePoint2d(4.97, 1.7);
	poiline[321] = pTransGeom->MethodCreatePoint2d(4.97, 1.5);
	poiline[322] = pTransGeom->MethodCreatePoint2d(6.27, 11.9);
	poiline[323] = pTransGeom->MethodCreatePoint2d(6.27, 11.7);
	poiline[324] = pTransGeom->MethodCreatePoint2d(6.27, 11.05);
	poiline[325] = pTransGeom->MethodCreatePoint2d(6.27, 10.85);
	poiline[326] = pTransGeom->MethodCreatePoint2d(6.27, 10.2);
	poiline[327] = pTransGeom->MethodCreatePoint2d(6.27, 10);
	poiline[328] = pTransGeom->MethodCreatePoint2d(6.27, 9.35);
	poiline[329] = pTransGeom->MethodCreatePoint2d(6.27, 9.15);
	poiline[330] = pTransGeom->MethodCreatePoint2d(6.27, 8.5);
	poiline[331] = pTransGeom->MethodCreatePoint2d(6.27, 8.3);
	poiline[332] = pTransGeom->MethodCreatePoint2d(6.27, 7.65);
	poiline[333] = pTransGeom->MethodCreatePoint2d(6.27, 7.45);
	poiline[334] = pTransGeom->MethodCreatePoint2d(6.27, 6.8);
	poiline[335] = pTransGeom->MethodCreatePoint2d(6.27, 6.6);
	poiline[336] = pTransGeom->MethodCreatePoint2d(6.27, 5.95);
	poiline[337] = pTransGeom->MethodCreatePoint2d(6.27, 5.75);
	poiline[338] = pTransGeom->MethodCreatePoint2d(6.27, 5.1);
	poiline[339] = pTransGeom->MethodCreatePoint2d(6.27, 4.9);
	poiline[340] = pTransGeom->MethodCreatePoint2d(6.27, 4.25);
	poiline[341] = pTransGeom->MethodCreatePoint2d(6.27, 4.05);
	poiline[342] = pTransGeom->MethodCreatePoint2d(6.27, 3.4);
	poiline[343] = pTransGeom->MethodCreatePoint2d(6.27, 3.2);
	poiline[344] = pTransGeom->MethodCreatePoint2d(6.27, 2.55);
	poiline[345] = pTransGeom->MethodCreatePoint2d(6.27, 2.35);
	poiline[346] = pTransGeom->MethodCreatePoint2d(6.27, 1.7);
	poiline[347] = pTransGeom->MethodCreatePoint2d(6.27, 1.5);
	poiline[348] = pTransGeom->MethodCreatePoint2d(13.81, 11.9);
	poiline[349] = pTransGeom->MethodCreatePoint2d(13.81, 11.7);
	poiline[350] = pTransGeom->MethodCreatePoint2d(13.81, 11.05);
	poiline[351] = pTransGeom->MethodCreatePoint2d(13.81, 10.85);
	poiline[352] = pTransGeom->MethodCreatePoint2d(13.81, 10.2);
	poiline[353] = pTransGeom->MethodCreatePoint2d(13.81, 10);
	poiline[354] = pTransGeom->MethodCreatePoint2d(13.81, 9.35);
	poiline[355] = pTransGeom->MethodCreatePoint2d(13.81, 9.15);
	poiline[356] = pTransGeom->MethodCreatePoint2d(13.81, 8.5);
	poiline[357] = pTransGeom->MethodCreatePoint2d(13.81, 8.3);
	poiline[358] = pTransGeom->MethodCreatePoint2d(13.81, 7.65);
	poiline[359] = pTransGeom->MethodCreatePoint2d(13.81, 7.45);
	poiline[360] = pTransGeom->MethodCreatePoint2d(13.81, 6.8);
	poiline[361] = pTransGeom->MethodCreatePoint2d(13.81, 6.6);
	poiline[362] = pTransGeom->MethodCreatePoint2d(13.81, 5.95);
	poiline[363] = pTransGeom->MethodCreatePoint2d(13.81, 5.75);
	poiline[364] = pTransGeom->MethodCreatePoint2d(13.81, 5.1);
	poiline[365] = pTransGeom->MethodCreatePoint2d(13.81, 4.9);
	poiline[366] = pTransGeom->MethodCreatePoint2d(13.81, 4.25);
	poiline[367] = pTransGeom->MethodCreatePoint2d(13.81, 4.05);
	poiline[368] = pTransGeom->MethodCreatePoint2d(13.81, 3.4);
	poiline[369] = pTransGeom->MethodCreatePoint2d(13.81, 3.2);
	poiline[370] = pTransGeom->MethodCreatePoint2d(13.81, 2.55);
	poiline[371] = pTransGeom->MethodCreatePoint2d(13.81, 2.35);
	poiline[372] = pTransGeom->MethodCreatePoint2d(13.81, 1.7);
	poiline[373] = pTransGeom->MethodCreatePoint2d(13.81, 1.5);
	poiline[374] = pTransGeom->MethodCreatePoint2d(14.85, 11.9);
	poiline[375] = pTransGeom->MethodCreatePoint2d(14.85, 11.7);
	poiline[376] = pTransGeom->MethodCreatePoint2d(14.85, 11.05);
	poiline[377] = pTransGeom->MethodCreatePoint2d(14.85, 10.85);
	poiline[378] = pTransGeom->MethodCreatePoint2d(14.85, 10.2);
	poiline[379] = pTransGeom->MethodCreatePoint2d(14.85, 10);
	poiline[380] = pTransGeom->MethodCreatePoint2d(14.85, 9.35);
	poiline[381] = pTransGeom->MethodCreatePoint2d(14.85, 9.15);
	poiline[382] = pTransGeom->MethodCreatePoint2d(14.85, 8.5);
	poiline[383] = pTransGeom->MethodCreatePoint2d(14.85, 8.3);
	poiline[384] = pTransGeom->MethodCreatePoint2d(14.85, 7.65);
	poiline[385] = pTransGeom->MethodCreatePoint2d(14.85, 7.45);
	poiline[386] = pTransGeom->MethodCreatePoint2d(14.85, 6.8);
	poiline[387] = pTransGeom->MethodCreatePoint2d(14.85, 6.6);
	poiline[388] = pTransGeom->MethodCreatePoint2d(14.85, 5.95);
	poiline[389] = pTransGeom->MethodCreatePoint2d(14.85, 5.75);
	poiline[390] = pTransGeom->MethodCreatePoint2d(14.85, 5.1);
	poiline[391] = pTransGeom->MethodCreatePoint2d(14.85, 4.9);
	poiline[392] = pTransGeom->MethodCreatePoint2d(14.85, 4.25);
	poiline[393] = pTransGeom->MethodCreatePoint2d(14.85, 4.05);
	poiline[394] = pTransGeom->MethodCreatePoint2d(14.85, 3.4);
	poiline[395] = pTransGeom->MethodCreatePoint2d(14.85, 3.2);
	poiline[396] = pTransGeom->MethodCreatePoint2d(14.85, 2.55);
	poiline[397] = pTransGeom->MethodCreatePoint2d(14.85, 2.35);
	poiline[398] = pTransGeom->MethodCreatePoint2d(14.85, 1.7);
	poiline[399] = pTransGeom->MethodCreatePoint2d(14.85, 1.5);
	poiline[400] = pTransGeom->MethodCreatePoint2d(16.67, 11.9);
	poiline[401] = pTransGeom->MethodCreatePoint2d(16.67, 11.7);
	poiline[402] = pTransGeom->MethodCreatePoint2d(16.67, 11.05);
	poiline[403] = pTransGeom->MethodCreatePoint2d(16.67, 10.85);
	poiline[404] = pTransGeom->MethodCreatePoint2d(16.67, 10.2);
	poiline[405] = pTransGeom->MethodCreatePoint2d(16.67, 10);
	poiline[406] = pTransGeom->MethodCreatePoint2d(16.67, 9.35);
	poiline[407] = pTransGeom->MethodCreatePoint2d(16.67, 9.15);
	poiline[408] = pTransGeom->MethodCreatePoint2d(16.67, 8.5);
	poiline[409] = pTransGeom->MethodCreatePoint2d(16.67, 8.3);
	poiline[410] = pTransGeom->MethodCreatePoint2d(16.67, 7.65);
	poiline[411] = pTransGeom->MethodCreatePoint2d(16.67, 7.45);
	poiline[412] = pTransGeom->MethodCreatePoint2d(16.67, 6.8);
	poiline[413] = pTransGeom->MethodCreatePoint2d(16.67, 6.6);
	poiline[414] = pTransGeom->MethodCreatePoint2d(16.67, 5.95);
	poiline[415] = pTransGeom->MethodCreatePoint2d(16.67, 5.75);
	poiline[416] = pTransGeom->MethodCreatePoint2d(16.67, 5.1);
	poiline[417] = pTransGeom->MethodCreatePoint2d(16.67, 4.9);
	poiline[418] = pTransGeom->MethodCreatePoint2d(16.67, 4.25);
	poiline[419] = pTransGeom->MethodCreatePoint2d(16.67, 4.05);
	poiline[420] = pTransGeom->MethodCreatePoint2d(16.67, 3.4);
	poiline[421] = pTransGeom->MethodCreatePoint2d(16.67, 3.2);
	poiline[422] = pTransGeom->MethodCreatePoint2d(16.67, 2.55);
	poiline[423] = pTransGeom->MethodCreatePoint2d(16.67, 2.35);
	poiline[424] = pTransGeom->MethodCreatePoint2d(16.67, 1.7);
	poiline[425] = pTransGeom->MethodCreatePoint2d(16.67, 1.5);
	poiline[426] = pTransGeom->MethodCreatePoint2d(17.71, 11.9);
	poiline[427] = pTransGeom->MethodCreatePoint2d(17.71, 11.7);
	poiline[428] = pTransGeom->MethodCreatePoint2d(17.71, 11.05);
	poiline[429] = pTransGeom->MethodCreatePoint2d(17.71, 10.85);
	poiline[430] = pTransGeom->MethodCreatePoint2d(17.71, 10.2);
	poiline[431] = pTransGeom->MethodCreatePoint2d(17.71, 10);
	poiline[432] = pTransGeom->MethodCreatePoint2d(17.71, 9.35);
	poiline[433] = pTransGeom->MethodCreatePoint2d(17.71, 9.15);
	poiline[434] = pTransGeom->MethodCreatePoint2d(17.71, 8.5);
	poiline[435] = pTransGeom->MethodCreatePoint2d(17.71, 8.3);
	poiline[436] = pTransGeom->MethodCreatePoint2d(17.71, 7.65);
	poiline[437] = pTransGeom->MethodCreatePoint2d(17.71, 7.45);
	poiline[438] = pTransGeom->MethodCreatePoint2d(17.71, 6.8);
	poiline[439] = pTransGeom->MethodCreatePoint2d(17.71, 6.6);
	poiline[440] = pTransGeom->MethodCreatePoint2d(17.71, 5.95);
	poiline[441] = pTransGeom->MethodCreatePoint2d(17.71, 5.75);
	poiline[442] = pTransGeom->MethodCreatePoint2d(17.71, 5.1);
	poiline[443] = pTransGeom->MethodCreatePoint2d(17.71, 4.9);
	poiline[444] = pTransGeom->MethodCreatePoint2d(17.71, 4.25);
	poiline[445] = pTransGeom->MethodCreatePoint2d(17.71, 4.05);
	poiline[446] = pTransGeom->MethodCreatePoint2d(17.71, 3.4);
	poiline[447] = pTransGeom->MethodCreatePoint2d(17.71, 3.2);
	poiline[448] = pTransGeom->MethodCreatePoint2d(17.71, 2.55);
	poiline[449] = pTransGeom->MethodCreatePoint2d(17.71, 2.35);
	poiline[450] = pTransGeom->MethodCreatePoint2d(17.71, 1.7);
	poiline[451] = pTransGeom->MethodCreatePoint2d(17.71, 1.5);
	poiline[452] = pTransGeom->MethodCreatePoint2d(19.01, 11.9);
	poiline[453] = pTransGeom->MethodCreatePoint2d(19.01, 11.7);
	poiline[454] = pTransGeom->MethodCreatePoint2d(19.01, 11.05);
	poiline[455] = pTransGeom->MethodCreatePoint2d(19.01, 10.85);
	poiline[456] = pTransGeom->MethodCreatePoint2d(19.01, 10.2);
	poiline[457] = pTransGeom->MethodCreatePoint2d(19.01, 10);
	poiline[458] = pTransGeom->MethodCreatePoint2d(19.01, 9.35);
	poiline[459] = pTransGeom->MethodCreatePoint2d(19.01, 9.15);
	poiline[460] = pTransGeom->MethodCreatePoint2d(19.01, 8.5);
	poiline[461] = pTransGeom->MethodCreatePoint2d(19.01, 8.3);
	poiline[462] = pTransGeom->MethodCreatePoint2d(19.01, 7.65);
	poiline[463] = pTransGeom->MethodCreatePoint2d(19.01, 7.45);
	poiline[464] = pTransGeom->MethodCreatePoint2d(19.01, 6.8);
	poiline[465] = pTransGeom->MethodCreatePoint2d(19.01, 6.6);
	poiline[466] = pTransGeom->MethodCreatePoint2d(19.01, 5.95);
	poiline[467] = pTransGeom->MethodCreatePoint2d(19.01, 5.75);
	poiline[468] = pTransGeom->MethodCreatePoint2d(19.01, 5.1);
	poiline[469] = pTransGeom->MethodCreatePoint2d(19.01, 4.9);
	poiline[470] = pTransGeom->MethodCreatePoint2d(19.01, 4.25);
	poiline[471] = pTransGeom->MethodCreatePoint2d(19.01, 4.05);
	poiline[472] = pTransGeom->MethodCreatePoint2d(19.01, 3.4);
	poiline[473] = pTransGeom->MethodCreatePoint2d(19.01, 3.2);
	poiline[474] = pTransGeom->MethodCreatePoint2d(19.01, 2.55);
	poiline[475] = pTransGeom->MethodCreatePoint2d(19.01, 2.35);
	poiline[476] = pTransGeom->MethodCreatePoint2d(19.01, 1.7);
	poiline[477] = pTransGeom->MethodCreatePoint2d(19.01, 1.5);
	poiline[478] = pTransGeom->MethodCreatePoint2d(20.05, 11.9);
	poiline[479] = pTransGeom->MethodCreatePoint2d(20.05, 11.7);
	poiline[480] = pTransGeom->MethodCreatePoint2d(20.05, 11.05);
	poiline[481] = pTransGeom->MethodCreatePoint2d(20.05, 10.85);
	poiline[482] = pTransGeom->MethodCreatePoint2d(20.05, 10.2);
	poiline[483] = pTransGeom->MethodCreatePoint2d(20.05, 10);
	poiline[484] = pTransGeom->MethodCreatePoint2d(20.05, 9.35);
	poiline[485] = pTransGeom->MethodCreatePoint2d(20.05, 9.15);
	poiline[486] = pTransGeom->MethodCreatePoint2d(20.05, 8.5);
	poiline[487] = pTransGeom->MethodCreatePoint2d(20.05, 8.3);
	poiline[488] = pTransGeom->MethodCreatePoint2d(20.05, 7.65);
	poiline[489] = pTransGeom->MethodCreatePoint2d(20.05, 7.45);
	poiline[490] = pTransGeom->MethodCreatePoint2d(20.05, 6.8);
	poiline[491] = pTransGeom->MethodCreatePoint2d(20.05, 6.6);
	poiline[492] = pTransGeom->MethodCreatePoint2d(20.05, 5.95);
	poiline[493] = pTransGeom->MethodCreatePoint2d(20.05, 5.75);
	poiline[494] = pTransGeom->MethodCreatePoint2d(20.05, 5.1);
	poiline[495] = pTransGeom->MethodCreatePoint2d(20.05, 4.9);
	poiline[496] = pTransGeom->MethodCreatePoint2d(20.05, 4.25);
	poiline[497] = pTransGeom->MethodCreatePoint2d(20.05, 4.05);
	poiline[498] = pTransGeom->MethodCreatePoint2d(20.05, 3.4);
	poiline[499] = pTransGeom->MethodCreatePoint2d(20.05, 3.2);
	poiline[500] = pTransGeom->MethodCreatePoint2d(20.05, 2.55);
	poiline[501] = pTransGeom->MethodCreatePoint2d(20.05, 2.35);
	poiline[502] = pTransGeom->MethodCreatePoint2d(20.05, 1.7);
	poiline[503] = pTransGeom->MethodCreatePoint2d(20.05, 1.5);
	poiline[504] = pTransGeom->MethodCreatePoint2d(21.35, 11.9);
	poiline[505] = pTransGeom->MethodCreatePoint2d(21.35, 11.7);
	poiline[506] = pTransGeom->MethodCreatePoint2d(21.35, 11.05);
	poiline[507] = pTransGeom->MethodCreatePoint2d(21.35, 10.85);
	poiline[508] = pTransGeom->MethodCreatePoint2d(21.35, 10.2);
	poiline[509] = pTransGeom->MethodCreatePoint2d(21.35, 10);
	poiline[510] = pTransGeom->MethodCreatePoint2d(21.35, 9.35);
	poiline[511] = pTransGeom->MethodCreatePoint2d(21.35, 9.15);
	poiline[512] = pTransGeom->MethodCreatePoint2d(21.35, 8.5);
	poiline[513] = pTransGeom->MethodCreatePoint2d(21.35, 8.3);
	poiline[514] = pTransGeom->MethodCreatePoint2d(21.35, 7.65);
	poiline[515] = pTransGeom->MethodCreatePoint2d(21.35, 7.45);
	poiline[516] = pTransGeom->MethodCreatePoint2d(21.35, 6.8);
	poiline[517] = pTransGeom->MethodCreatePoint2d(21.35, 6.6);
	poiline[518] = pTransGeom->MethodCreatePoint2d(21.35, 5.95);
	poiline[519] = pTransGeom->MethodCreatePoint2d(21.35, 5.75);
	poiline[520] = pTransGeom->MethodCreatePoint2d(21.35, 5.1);
	poiline[521] = pTransGeom->MethodCreatePoint2d(21.35, 4.9);
	poiline[522] = pTransGeom->MethodCreatePoint2d(21.35, 4.25);
	poiline[523] = pTransGeom->MethodCreatePoint2d(21.35, 4.05);
	poiline[524] = pTransGeom->MethodCreatePoint2d(21.35, 3.4);
	poiline[525] = pTransGeom->MethodCreatePoint2d(21.35, 3.2);
	poiline[526] = pTransGeom->MethodCreatePoint2d(21.35, 2.55);
	poiline[527] = pTransGeom->MethodCreatePoint2d(21.35, 2.35);
	poiline[528] = pTransGeom->MethodCreatePoint2d(21.35, 1.7);
	poiline[529] = pTransGeom->MethodCreatePoint2d(21.35, 1.5);
	poiline[530] = pTransGeom->MethodCreatePoint2d(22.65, 11.9);
	poiline[531] = pTransGeom->MethodCreatePoint2d(22.65, 11.7);
	poiline[532] = pTransGeom->MethodCreatePoint2d(22.65, 11.05);
	poiline[533] = pTransGeom->MethodCreatePoint2d(22.65, 10.85);
	poiline[534] = pTransGeom->MethodCreatePoint2d(22.65, 10.2);
	poiline[535] = pTransGeom->MethodCreatePoint2d(22.65, 10);
	poiline[536] = pTransGeom->MethodCreatePoint2d(22.65, 9.35);
	poiline[537] = pTransGeom->MethodCreatePoint2d(22.65, 9.15);
	poiline[538] = pTransGeom->MethodCreatePoint2d(22.65, 8.5);
	poiline[539] = pTransGeom->MethodCreatePoint2d(22.65, 8.3);
	poiline[540] = pTransGeom->MethodCreatePoint2d(22.65, 7.65);
	poiline[541] = pTransGeom->MethodCreatePoint2d(22.65, 7.45);
	poiline[542] = pTransGeom->MethodCreatePoint2d(22.65, 6.8);
	poiline[543] = pTransGeom->MethodCreatePoint2d(22.65, 6.6);
	poiline[544] = pTransGeom->MethodCreatePoint2d(22.65, 5.95);
	poiline[545] = pTransGeom->MethodCreatePoint2d(22.65, 5.75);
	poiline[546] = pTransGeom->MethodCreatePoint2d(22.65, 5.1);
	poiline[547] = pTransGeom->MethodCreatePoint2d(22.65, 4.9);
	poiline[548] = pTransGeom->MethodCreatePoint2d(22.65, 4.25);
	poiline[549] = pTransGeom->MethodCreatePoint2d(22.65, 4.05);
	poiline[550] = pTransGeom->MethodCreatePoint2d(22.65, 3.4);
	poiline[551] = pTransGeom->MethodCreatePoint2d(22.65, 3.2);
	poiline[552] = pTransGeom->MethodCreatePoint2d(22.65, 2.55);
	poiline[553] = pTransGeom->MethodCreatePoint2d(22.65, 2.35);
	poiline[554] = pTransGeom->MethodCreatePoint2d(22.65, 1.7);
	poiline[555] = pTransGeom->MethodCreatePoint2d(22.65, 1.5);
	poiline[556] = pTransGeom->MethodCreatePoint2d(23.95, 11.9);
	poiline[557] = pTransGeom->MethodCreatePoint2d(23.95, 11.7);
	poiline[558] = pTransGeom->MethodCreatePoint2d(23.95, 11.05);
	poiline[559] = pTransGeom->MethodCreatePoint2d(23.95, 10.85);
	poiline[560] = pTransGeom->MethodCreatePoint2d(23.95, 10.2);
	poiline[561] = pTransGeom->MethodCreatePoint2d(23.95, 10);
	poiline[562] = pTransGeom->MethodCreatePoint2d(23.95, 9.35);
	poiline[563] = pTransGeom->MethodCreatePoint2d(23.95, 9.15);
	poiline[564] = pTransGeom->MethodCreatePoint2d(23.95, 8.5);
	poiline[565] = pTransGeom->MethodCreatePoint2d(23.95, 8.3);
	poiline[566] = pTransGeom->MethodCreatePoint2d(23.95, 7.65);
	poiline[567] = pTransGeom->MethodCreatePoint2d(23.95, 7.45);
	poiline[568] = pTransGeom->MethodCreatePoint2d(23.95, 6.8);
	poiline[569] = pTransGeom->MethodCreatePoint2d(23.95, 6.6);
	poiline[570] = pTransGeom->MethodCreatePoint2d(23.95, 5.95);
	poiline[571] = pTransGeom->MethodCreatePoint2d(23.95, 5.75);
	poiline[572] = pTransGeom->MethodCreatePoint2d(23.95, 5.1);
	poiline[573] = pTransGeom->MethodCreatePoint2d(23.95, 4.9);
	poiline[574] = pTransGeom->MethodCreatePoint2d(23.95, 4.25);
	poiline[575] = pTransGeom->MethodCreatePoint2d(23.95, 4.05);
	poiline[576] = pTransGeom->MethodCreatePoint2d(23.95, 3.4);
	poiline[577] = pTransGeom->MethodCreatePoint2d(23.95, 3.2);
	poiline[578] = pTransGeom->MethodCreatePoint2d(23.95, 2.55);
	poiline[579] = pTransGeom->MethodCreatePoint2d(23.95, 2.35);
	poiline[580] = pTransGeom->MethodCreatePoint2d(23.95, 1.7);
	poiline[581] = pTransGeom->MethodCreatePoint2d(23.95, 1.5);
	poiline[582] = pTransGeom->MethodCreatePoint2d(25.25, 11.9);
	poiline[583] = pTransGeom->MethodCreatePoint2d(25.25, 11.7);
	poiline[584] = pTransGeom->MethodCreatePoint2d(25.25, 11.05);
	poiline[585] = pTransGeom->MethodCreatePoint2d(25.25, 10.85);
	poiline[586] = pTransGeom->MethodCreatePoint2d(25.25, 10.2);
	poiline[587] = pTransGeom->MethodCreatePoint2d(25.25, 10);
	poiline[588] = pTransGeom->MethodCreatePoint2d(25.25, 9.35);
	poiline[589] = pTransGeom->MethodCreatePoint2d(25.25, 9.15);
	poiline[590] = pTransGeom->MethodCreatePoint2d(25.25, 8.5);
	poiline[591] = pTransGeom->MethodCreatePoint2d(25.25, 8.3);
	poiline[592] = pTransGeom->MethodCreatePoint2d(25.25, 7.65);
	poiline[593] = pTransGeom->MethodCreatePoint2d(25.25, 7.45);
	poiline[594] = pTransGeom->MethodCreatePoint2d(25.25, 6.8);
	poiline[595] = pTransGeom->MethodCreatePoint2d(25.25, 6.6);
	poiline[596] = pTransGeom->MethodCreatePoint2d(25.25, 5.95);
	poiline[597] = pTransGeom->MethodCreatePoint2d(25.25, 5.75);
	poiline[598] = pTransGeom->MethodCreatePoint2d(25.25, 5.1);
	poiline[599] = pTransGeom->MethodCreatePoint2d(25.25, 4.9);
	poiline[600] = pTransGeom->MethodCreatePoint2d(25.25, 4.25);
	poiline[601] = pTransGeom->MethodCreatePoint2d(25.25, 4.05);
	poiline[602] = pTransGeom->MethodCreatePoint2d(25.25, 3.4);
	poiline[603] = pTransGeom->MethodCreatePoint2d(25.25, 3.2);
	poiline[604] = pTransGeom->MethodCreatePoint2d(25.25, 2.55);
	poiline[605] = pTransGeom->MethodCreatePoint2d(25.25, 2.35);
	poiline[606] = pTransGeom->MethodCreatePoint2d(25.25, 1.7);
	poiline[607] = pTransGeom->MethodCreatePoint2d(25.25, 1.5);
	poiline[608] = pTransGeom->MethodCreatePoint2d(27.07, 11.9);
	poiline[609] = pTransGeom->MethodCreatePoint2d(27.07, 11.7);
	poiline[610] = pTransGeom->MethodCreatePoint2d(27.07, 11.05);
	poiline[611] = pTransGeom->MethodCreatePoint2d(27.07, 10.85);
	poiline[612] = pTransGeom->MethodCreatePoint2d(27.07, 10.2);
	poiline[613] = pTransGeom->MethodCreatePoint2d(27.07, 10);
	poiline[614] = pTransGeom->MethodCreatePoint2d(27.07, 9.35);
	poiline[615] = pTransGeom->MethodCreatePoint2d(27.07, 9.15);
	poiline[616] = pTransGeom->MethodCreatePoint2d(27.07, 8.5);
	poiline[617] = pTransGeom->MethodCreatePoint2d(27.07, 8.3);
	poiline[618] = pTransGeom->MethodCreatePoint2d(27.07, 7.65);
	poiline[619] = pTransGeom->MethodCreatePoint2d(27.07, 7.45);
	poiline[620] = pTransGeom->MethodCreatePoint2d(27.07, 6.8);
	poiline[621] = pTransGeom->MethodCreatePoint2d(27.07, 6.6);
	poiline[622] = pTransGeom->MethodCreatePoint2d(27.07, 5.95);
	poiline[623] = pTransGeom->MethodCreatePoint2d(27.07, 5.75);
	poiline[624] = pTransGeom->MethodCreatePoint2d(27.07, 5.1);
	poiline[625] = pTransGeom->MethodCreatePoint2d(27.07, 4.9);
	poiline[626] = pTransGeom->MethodCreatePoint2d(27.07, 4.25);
	poiline[627] = pTransGeom->MethodCreatePoint2d(27.07, 4.05);
	poiline[628] = pTransGeom->MethodCreatePoint2d(27.07, 3.4);
	poiline[629] = pTransGeom->MethodCreatePoint2d(27.07, 3.2);
	poiline[630] = pTransGeom->MethodCreatePoint2d(27.07, 2.55);
	poiline[631] = pTransGeom->MethodCreatePoint2d(27.07, 2.35);
	poiline[632] = pTransGeom->MethodCreatePoint2d(27.07, 1.7);
	poiline[633] = pTransGeom->MethodCreatePoint2d(27.07, 1.5);
	poiline[634] = pTransGeom->MethodCreatePoint2d(2.89, 14.45);
	poiline[635] = pTransGeom->MethodCreatePoint2d(2.89, 14.25);
	poiline[636] = pTransGeom->MethodCreatePoint2d(2.89, 13.6);
	poiline[637] = pTransGeom->MethodCreatePoint2d(2.89, 13.4);
	poiline[638] = pTransGeom->MethodCreatePoint2d(2.89, 12.75);
	poiline[639] = pTransGeom->MethodCreatePoint2d(2.89, 12.55);
	poiline[640] = pTransGeom->MethodCreatePoint2d(3.93, 14.45);
	poiline[641] = pTransGeom->MethodCreatePoint2d(3.93, 14.25);
	poiline[642] = pTransGeom->MethodCreatePoint2d(3.93, 13.6);
	poiline[643] = pTransGeom->MethodCreatePoint2d(3.93, 13.4);
	poiline[644] = pTransGeom->MethodCreatePoint2d(3.93, 12.75);
	poiline[645] = pTransGeom->MethodCreatePoint2d(3.93, 12.55);
	poiline[646] = pTransGeom->MethodCreatePoint2d(4.97, 14.45);
	poiline[647] = pTransGeom->MethodCreatePoint2d(4.97, 14.25);
	poiline[648] = pTransGeom->MethodCreatePoint2d(4.97, 13.6);
	poiline[649] = pTransGeom->MethodCreatePoint2d(4.97, 13.4);
	poiline[650] = pTransGeom->MethodCreatePoint2d(4.97, 12.75);
	poiline[651] = pTransGeom->MethodCreatePoint2d(4.97, 12.55);
	poiline[652] = pTransGeom->MethodCreatePoint2d(6.27, 14.45);
	poiline[653] = pTransGeom->MethodCreatePoint2d(6.27, 14.25);
	poiline[654] = pTransGeom->MethodCreatePoint2d(6.27, 13.6);
	poiline[655] = pTransGeom->MethodCreatePoint2d(6.27, 13.4);
	poiline[656] = pTransGeom->MethodCreatePoint2d(6.27, 12.75);
	poiline[657] = pTransGeom->MethodCreatePoint2d(6.27, 12.55);
	poiline[658] = pTransGeom->MethodCreatePoint2d(13.81, 14.45);
	poiline[659] = pTransGeom->MethodCreatePoint2d(13.81, 14.25);
	poiline[660] = pTransGeom->MethodCreatePoint2d(13.81, 13.6);
	poiline[661] = pTransGeom->MethodCreatePoint2d(13.81, 13.4);
	poiline[662] = pTransGeom->MethodCreatePoint2d(13.81, 12.75);
	poiline[663] = pTransGeom->MethodCreatePoint2d(13.81, 12.55);
	poiline[664] = pTransGeom->MethodCreatePoint2d(14.85, 14.45);
	poiline[665] = pTransGeom->MethodCreatePoint2d(14.85, 14.25);
	poiline[666] = pTransGeom->MethodCreatePoint2d(14.85, 13.6);
	poiline[667] = pTransGeom->MethodCreatePoint2d(14.85, 13.4);
	poiline[668] = pTransGeom->MethodCreatePoint2d(14.85, 12.75);
	poiline[669] = pTransGeom->MethodCreatePoint2d(14.85, 12.55);
	poiline[670] = pTransGeom->MethodCreatePoint2d(16.67, 14.45);
	poiline[671] = pTransGeom->MethodCreatePoint2d(16.67, 14.25);
	poiline[672] = pTransGeom->MethodCreatePoint2d(16.67, 13.6);
	poiline[673] = pTransGeom->MethodCreatePoint2d(16.67, 13.4);
	poiline[674] = pTransGeom->MethodCreatePoint2d(16.67, 12.75);
	poiline[675] = pTransGeom->MethodCreatePoint2d(16.67, 12.55);
	poiline[676] = pTransGeom->MethodCreatePoint2d(17.71, 14.45);
	poiline[677] = pTransGeom->MethodCreatePoint2d(17.71, 14.25);
	poiline[678] = pTransGeom->MethodCreatePoint2d(17.71, 13.6);
	poiline[679] = pTransGeom->MethodCreatePoint2d(17.71, 13.4);
	poiline[680] = pTransGeom->MethodCreatePoint2d(17.71, 12.75);
	poiline[681] = pTransGeom->MethodCreatePoint2d(17.71, 12.55);
	poiline[682] = pTransGeom->MethodCreatePoint2d(19.01, 14.45);
	poiline[683] = pTransGeom->MethodCreatePoint2d(19.01, 14.25);
	poiline[684] = pTransGeom->MethodCreatePoint2d(19.01, 13.6);
	poiline[685] = pTransGeom->MethodCreatePoint2d(19.01, 13.4);
	poiline[686] = pTransGeom->MethodCreatePoint2d(19.01, 12.75);
	poiline[687] = pTransGeom->MethodCreatePoint2d(19.01, 12.55);
	poiline[688] = pTransGeom->MethodCreatePoint2d(20.05, 14.45);
	poiline[689] = pTransGeom->MethodCreatePoint2d(20.05, 14.25);
	poiline[690] = pTransGeom->MethodCreatePoint2d(20.05, 13.6);
	poiline[691] = pTransGeom->MethodCreatePoint2d(20.05, 13.4);
	poiline[692] = pTransGeom->MethodCreatePoint2d(20.05, 12.75);
	poiline[693] = pTransGeom->MethodCreatePoint2d(20.05, 12.55);
	poiline[694] = pTransGeom->MethodCreatePoint2d(21.35, 14.45);
	poiline[695] = pTransGeom->MethodCreatePoint2d(21.35, 14.25);
	poiline[696] = pTransGeom->MethodCreatePoint2d(21.35, 13.6);
	poiline[697] = pTransGeom->MethodCreatePoint2d(21.35, 13.4);
	poiline[698] = pTransGeom->MethodCreatePoint2d(21.35, 12.75);
	poiline[699] = pTransGeom->MethodCreatePoint2d(21.35, 12.55);
	poiline[700] = pTransGeom->MethodCreatePoint2d(22.65, 14.45);
	poiline[701] = pTransGeom->MethodCreatePoint2d(22.65, 14.25);
	poiline[702] = pTransGeom->MethodCreatePoint2d(22.65, 13.6);
	poiline[703] = pTransGeom->MethodCreatePoint2d(22.65, 13.4);
	poiline[704] = pTransGeom->MethodCreatePoint2d(22.65, 12.75);
	poiline[705] = pTransGeom->MethodCreatePoint2d(22.65, 12.55);
	poiline[706] = pTransGeom->MethodCreatePoint2d(23.95, 14.45);
	poiline[707] = pTransGeom->MethodCreatePoint2d(23.95, 14.25);
	poiline[708] = pTransGeom->MethodCreatePoint2d(23.95, 13.6);
	poiline[709] = pTransGeom->MethodCreatePoint2d(23.95, 13.4);
	poiline[710] = pTransGeom->MethodCreatePoint2d(23.95, 12.75);
	poiline[711] = pTransGeom->MethodCreatePoint2d(23.95, 12.55);
	poiline[712] = pTransGeom->MethodCreatePoint2d(25.25, 14.45);
	poiline[713] = pTransGeom->MethodCreatePoint2d(25.25, 14.25);
	poiline[714] = pTransGeom->MethodCreatePoint2d(25.25, 13.6);
	poiline[715] = pTransGeom->MethodCreatePoint2d(25.25, 13.4);
	poiline[716] = pTransGeom->MethodCreatePoint2d(25.25, 12.75);
	poiline[717] = pTransGeom->MethodCreatePoint2d(25.25, 12.55);
	poiline[718] = pTransGeom->MethodCreatePoint2d(27.07, 14.45);
	poiline[719] = pTransGeom->MethodCreatePoint2d(27.07, 14.25);
	poiline[720] = pTransGeom->MethodCreatePoint2d(27.07, 13.6);
	poiline[721] = pTransGeom->MethodCreatePoint2d(27.07, 13.4);
	poiline[722] = pTransGeom->MethodCreatePoint2d(27.07, 12.75);
	poiline[723] = pTransGeom->MethodCreatePoint2d(27.07, 12.55);

	poiline[724] = pTransGeom->MethodCreatePoint2d(2.89, 15.3);
	poiline[725] = pTransGeom->MethodCreatePoint2d(2.89, 15.1);
	poiline[726] = pTransGeom->MethodCreatePoint2d(3.93, 15.3);
	poiline[727] = pTransGeom->MethodCreatePoint2d(3.93, 15.1);
	poiline[728] = pTransGeom->MethodCreatePoint2d(4.97, 15.3);
	poiline[729] = pTransGeom->MethodCreatePoint2d(4.97, 15.1);
	poiline[730] = pTransGeom->MethodCreatePoint2d(6.27, 15.3);
	poiline[731] = pTransGeom->MethodCreatePoint2d(6.27, 15.1);
	poiline[732] = pTransGeom->MethodCreatePoint2d(13.81, 15.3);
	poiline[733] = pTransGeom->MethodCreatePoint2d(13.81, 15.1);
	poiline[734] = pTransGeom->MethodCreatePoint2d(14.85, 15.3);
	poiline[735] = pTransGeom->MethodCreatePoint2d(14.85, 15.1);
	poiline[736] = pTransGeom->MethodCreatePoint2d(16.67, 15.3);
	poiline[737] = pTransGeom->MethodCreatePoint2d(16.67, 15.1);
	poiline[738] = pTransGeom->MethodCreatePoint2d(17.71, 15.3);
	poiline[739] = pTransGeom->MethodCreatePoint2d(17.71, 15.1);
	poiline[740] = pTransGeom->MethodCreatePoint2d(19.01, 15.3);
	poiline[741] = pTransGeom->MethodCreatePoint2d(19.01, 15.1);
	poiline[742] = pTransGeom->MethodCreatePoint2d(20.05, 15.3);
	poiline[743] = pTransGeom->MethodCreatePoint2d(20.05, 15.1);
	poiline[744] = pTransGeom->MethodCreatePoint2d(21.35, 15.3);
	poiline[745] = pTransGeom->MethodCreatePoint2d(21.35, 15.1);
	poiline[746] = pTransGeom->MethodCreatePoint2d(22.65, 15.3);
	poiline[747] = pTransGeom->MethodCreatePoint2d(22.65, 15.1);
	poiline[748] = pTransGeom->MethodCreatePoint2d(23.95, 15.3);
	poiline[749] = pTransGeom->MethodCreatePoint2d(23.95, 15.1);
	poiline[750] = pTransGeom->MethodCreatePoint2d(25.25, 15.3);
	poiline[751] = pTransGeom->MethodCreatePoint2d(25.25, 15.1);
	poiline[752] = pTransGeom->MethodCreatePoint2d(27.07, 15.3);
	poiline[753] = pTransGeom->MethodCreatePoint2d(27.07, 15.1);

	pSketchLines->MethodAddByTwoPoints(poiline[244], poiline[245]);
	pSketchLines->MethodAddByTwoPoints(poiline[246], poiline[247]);
	pSketchLines->MethodAddByTwoPoints(poiline[248], poiline[249]);
	pSketchLines->MethodAddByTwoPoints(poiline[250], poiline[251]);
	pSketchLines->MethodAddByTwoPoints(poiline[252], poiline[253]);
	pSketchLines->MethodAddByTwoPoints(poiline[254], poiline[255]);
	pSketchLines->MethodAddByTwoPoints(poiline[256], poiline[257]);
	pSketchLines->MethodAddByTwoPoints(poiline[258], poiline[259]);
	pSketchLines->MethodAddByTwoPoints(poiline[260], poiline[261]);
	pSketchLines->MethodAddByTwoPoints(poiline[262], poiline[263]);
	pSketchLines->MethodAddByTwoPoints(poiline[264], poiline[265]);
	pSketchLines->MethodAddByTwoPoints(poiline[266], poiline[267]);
	pSketchLines->MethodAddByTwoPoints(poiline[268], poiline[269]);
	pSketchLines->MethodAddByTwoPoints(poiline[270], poiline[271]);
	pSketchLines->MethodAddByTwoPoints(poiline[272], poiline[273]);
	pSketchLines->MethodAddByTwoPoints(poiline[274], poiline[275]);
	pSketchLines->MethodAddByTwoPoints(poiline[276], poiline[277]);
	pSketchLines->MethodAddByTwoPoints(poiline[278], poiline[279]);
	pSketchLines->MethodAddByTwoPoints(poiline[280], poiline[281]);
	pSketchLines->MethodAddByTwoPoints(poiline[282], poiline[283]);
	pSketchLines->MethodAddByTwoPoints(poiline[284], poiline[285]);
	pSketchLines->MethodAddByTwoPoints(poiline[286], poiline[287]);
	pSketchLines->MethodAddByTwoPoints(poiline[288], poiline[289]);
	pSketchLines->MethodAddByTwoPoints(poiline[290], poiline[291]);
	pSketchLines->MethodAddByTwoPoints(poiline[292], poiline[293]);
	pSketchLines->MethodAddByTwoPoints(poiline[294], poiline[295]);
	pSketchLines->MethodAddByTwoPoints(poiline[296], poiline[297]);
	pSketchLines->MethodAddByTwoPoints(poiline[298], poiline[299]);
	pSketchLines->MethodAddByTwoPoints(poiline[300], poiline[301]);
	pSketchLines->MethodAddByTwoPoints(poiline[302], poiline[303]);
	pSketchLines->MethodAddByTwoPoints(poiline[304], poiline[305]);
	pSketchLines->MethodAddByTwoPoints(poiline[306], poiline[307]);
	pSketchLines->MethodAddByTwoPoints(poiline[308], poiline[309]);
	pSketchLines->MethodAddByTwoPoints(poiline[310], poiline[311]);
	pSketchLines->MethodAddByTwoPoints(poiline[312], poiline[313]);
	pSketchLines->MethodAddByTwoPoints(poiline[314], poiline[315]);
	pSketchLines->MethodAddByTwoPoints(poiline[316], poiline[317]);
	pSketchLines->MethodAddByTwoPoints(poiline[318], poiline[319]);
	pSketchLines->MethodAddByTwoPoints(poiline[320], poiline[321]);
	pSketchLines->MethodAddByTwoPoints(poiline[322], poiline[323]);
	pSketchLines->MethodAddByTwoPoints(poiline[324], poiline[325]);
	pSketchLines->MethodAddByTwoPoints(poiline[326], poiline[327]);
	pSketchLines->MethodAddByTwoPoints(poiline[328], poiline[329]);
	pSketchLines->MethodAddByTwoPoints(poiline[330], poiline[331]);
	pSketchLines->MethodAddByTwoPoints(poiline[332], poiline[333]);
	pSketchLines->MethodAddByTwoPoints(poiline[334], poiline[335]);
	pSketchLines->MethodAddByTwoPoints(poiline[336], poiline[337]);
	pSketchLines->MethodAddByTwoPoints(poiline[338], poiline[339]);
	pSketchLines->MethodAddByTwoPoints(poiline[340], poiline[341]);
	pSketchLines->MethodAddByTwoPoints(poiline[342], poiline[343]);
	pSketchLines->MethodAddByTwoPoints(poiline[344], poiline[345]);
	pSketchLines->MethodAddByTwoPoints(poiline[346], poiline[347]);
	pSketchLines->MethodAddByTwoPoints(poiline[348], poiline[349]);
	pSketchLines->MethodAddByTwoPoints(poiline[350], poiline[351]);
	pSketchLines->MethodAddByTwoPoints(poiline[352], poiline[353]);
	pSketchLines->MethodAddByTwoPoints(poiline[354], poiline[355]);
	pSketchLines->MethodAddByTwoPoints(poiline[356], poiline[357]);
	pSketchLines->MethodAddByTwoPoints(poiline[358], poiline[359]);
	pSketchLines->MethodAddByTwoPoints(poiline[360], poiline[361]);
	pSketchLines->MethodAddByTwoPoints(poiline[362], poiline[363]);
	pSketchLines->MethodAddByTwoPoints(poiline[364], poiline[365]);
	pSketchLines->MethodAddByTwoPoints(poiline[366], poiline[367]);
	pSketchLines->MethodAddByTwoPoints(poiline[368], poiline[369]);
	pSketchLines->MethodAddByTwoPoints(poiline[370], poiline[371]);
	pSketchLines->MethodAddByTwoPoints(poiline[372], poiline[373]);
	pSketchLines->MethodAddByTwoPoints(poiline[374], poiline[375]);
	pSketchLines->MethodAddByTwoPoints(poiline[376], poiline[377]);
	pSketchLines->MethodAddByTwoPoints(poiline[378], poiline[379]);
	pSketchLines->MethodAddByTwoPoints(poiline[380], poiline[381]);
	pSketchLines->MethodAddByTwoPoints(poiline[382], poiline[383]);
	pSketchLines->MethodAddByTwoPoints(poiline[384], poiline[385]);
	pSketchLines->MethodAddByTwoPoints(poiline[386], poiline[387]);
	pSketchLines->MethodAddByTwoPoints(poiline[388], poiline[389]);
	pSketchLines->MethodAddByTwoPoints(poiline[390], poiline[391]);
	pSketchLines->MethodAddByTwoPoints(poiline[392], poiline[393]);
	pSketchLines->MethodAddByTwoPoints(poiline[394], poiline[395]);
	pSketchLines->MethodAddByTwoPoints(poiline[396], poiline[397]);
	pSketchLines->MethodAddByTwoPoints(poiline[398], poiline[399]);
	pSketchLines->MethodAddByTwoPoints(poiline[400], poiline[401]);
	pSketchLines->MethodAddByTwoPoints(poiline[402], poiline[403]);
	pSketchLines->MethodAddByTwoPoints(poiline[404], poiline[405]);
	pSketchLines->MethodAddByTwoPoints(poiline[406], poiline[407]);
	pSketchLines->MethodAddByTwoPoints(poiline[408], poiline[409]);
	pSketchLines->MethodAddByTwoPoints(poiline[410], poiline[411]);
	pSketchLines->MethodAddByTwoPoints(poiline[412], poiline[413]);
	pSketchLines->MethodAddByTwoPoints(poiline[414], poiline[415]);
	pSketchLines->MethodAddByTwoPoints(poiline[416], poiline[417]);
	pSketchLines->MethodAddByTwoPoints(poiline[418], poiline[419]);
	pSketchLines->MethodAddByTwoPoints(poiline[420], poiline[421]);
	pSketchLines->MethodAddByTwoPoints(poiline[422], poiline[423]);
	pSketchLines->MethodAddByTwoPoints(poiline[424], poiline[425]);
	pSketchLines->MethodAddByTwoPoints(poiline[426], poiline[427]);
	pSketchLines->MethodAddByTwoPoints(poiline[428], poiline[429]);
	pSketchLines->MethodAddByTwoPoints(poiline[430], poiline[431]);
	pSketchLines->MethodAddByTwoPoints(poiline[432], poiline[433]);
	pSketchLines->MethodAddByTwoPoints(poiline[434], poiline[435]);
	pSketchLines->MethodAddByTwoPoints(poiline[436], poiline[437]);
	pSketchLines->MethodAddByTwoPoints(poiline[438], poiline[439]);
	pSketchLines->MethodAddByTwoPoints(poiline[440], poiline[441]);
	pSketchLines->MethodAddByTwoPoints(poiline[442], poiline[443]);
	pSketchLines->MethodAddByTwoPoints(poiline[444], poiline[445]);
	pSketchLines->MethodAddByTwoPoints(poiline[446], poiline[447]);
	pSketchLines->MethodAddByTwoPoints(poiline[448], poiline[449]);
	pSketchLines->MethodAddByTwoPoints(poiline[450], poiline[451]);
	pSketchLines->MethodAddByTwoPoints(poiline[452], poiline[453]);
	pSketchLines->MethodAddByTwoPoints(poiline[454], poiline[455]);
	pSketchLines->MethodAddByTwoPoints(poiline[456], poiline[457]);
	pSketchLines->MethodAddByTwoPoints(poiline[458], poiline[459]);
	pSketchLines->MethodAddByTwoPoints(poiline[460], poiline[461]);
	pSketchLines->MethodAddByTwoPoints(poiline[462], poiline[463]);
	pSketchLines->MethodAddByTwoPoints(poiline[464], poiline[465]);
	pSketchLines->MethodAddByTwoPoints(poiline[466], poiline[467]);
	pSketchLines->MethodAddByTwoPoints(poiline[468], poiline[469]);
	pSketchLines->MethodAddByTwoPoints(poiline[470], poiline[471]);
	pSketchLines->MethodAddByTwoPoints(poiline[472], poiline[473]);
	pSketchLines->MethodAddByTwoPoints(poiline[474], poiline[475]);
	pSketchLines->MethodAddByTwoPoints(poiline[476], poiline[477]);
	pSketchLines->MethodAddByTwoPoints(poiline[478], poiline[479]);
	pSketchLines->MethodAddByTwoPoints(poiline[480], poiline[481]);
	pSketchLines->MethodAddByTwoPoints(poiline[482], poiline[483]);
	pSketchLines->MethodAddByTwoPoints(poiline[484], poiline[485]);
	pSketchLines->MethodAddByTwoPoints(poiline[486], poiline[487]);
	pSketchLines->MethodAddByTwoPoints(poiline[488], poiline[489]);
	pSketchLines->MethodAddByTwoPoints(poiline[490], poiline[491]);
	pSketchLines->MethodAddByTwoPoints(poiline[492], poiline[493]);
	pSketchLines->MethodAddByTwoPoints(poiline[494], poiline[495]);
	pSketchLines->MethodAddByTwoPoints(poiline[496], poiline[497]);
	pSketchLines->MethodAddByTwoPoints(poiline[498], poiline[499]);
	pSketchLines->MethodAddByTwoPoints(poiline[500], poiline[501]);
	pSketchLines->MethodAddByTwoPoints(poiline[502], poiline[503]);
	pSketchLines->MethodAddByTwoPoints(poiline[504], poiline[505]);
	pSketchLines->MethodAddByTwoPoints(poiline[506], poiline[507]);
	pSketchLines->MethodAddByTwoPoints(poiline[508], poiline[509]);
	pSketchLines->MethodAddByTwoPoints(poiline[510], poiline[511]);
	pSketchLines->MethodAddByTwoPoints(poiline[512], poiline[513]);
	pSketchLines->MethodAddByTwoPoints(poiline[514], poiline[515]);
	pSketchLines->MethodAddByTwoPoints(poiline[516], poiline[517]);
	pSketchLines->MethodAddByTwoPoints(poiline[518], poiline[519]);
	pSketchLines->MethodAddByTwoPoints(poiline[520], poiline[521]);
	pSketchLines->MethodAddByTwoPoints(poiline[522], poiline[523]);
	pSketchLines->MethodAddByTwoPoints(poiline[524], poiline[525]);
	pSketchLines->MethodAddByTwoPoints(poiline[526], poiline[527]);
	pSketchLines->MethodAddByTwoPoints(poiline[528], poiline[529]);
	pSketchLines->MethodAddByTwoPoints(poiline[530], poiline[531]);
	pSketchLines->MethodAddByTwoPoints(poiline[532], poiline[533]);
	pSketchLines->MethodAddByTwoPoints(poiline[534], poiline[535]);
	pSketchLines->MethodAddByTwoPoints(poiline[536], poiline[537]);
	pSketchLines->MethodAddByTwoPoints(poiline[538], poiline[539]);
	pSketchLines->MethodAddByTwoPoints(poiline[540], poiline[541]);
	pSketchLines->MethodAddByTwoPoints(poiline[542], poiline[543]);
	pSketchLines->MethodAddByTwoPoints(poiline[544], poiline[545]);
	pSketchLines->MethodAddByTwoPoints(poiline[546], poiline[547]);
	pSketchLines->MethodAddByTwoPoints(poiline[548], poiline[549]);
	pSketchLines->MethodAddByTwoPoints(poiline[550], poiline[551]);
	pSketchLines->MethodAddByTwoPoints(poiline[552], poiline[553]);
	pSketchLines->MethodAddByTwoPoints(poiline[554], poiline[555]);
	pSketchLines->MethodAddByTwoPoints(poiline[556], poiline[557]);
	pSketchLines->MethodAddByTwoPoints(poiline[558], poiline[559]);
	pSketchLines->MethodAddByTwoPoints(poiline[560], poiline[561]);
	pSketchLines->MethodAddByTwoPoints(poiline[562], poiline[563]);
	pSketchLines->MethodAddByTwoPoints(poiline[564], poiline[565]);
	pSketchLines->MethodAddByTwoPoints(poiline[566], poiline[567]);
	pSketchLines->MethodAddByTwoPoints(poiline[568], poiline[569]);
	pSketchLines->MethodAddByTwoPoints(poiline[570], poiline[571]);
	pSketchLines->MethodAddByTwoPoints(poiline[572], poiline[573]);
	pSketchLines->MethodAddByTwoPoints(poiline[574], poiline[575]);
	pSketchLines->MethodAddByTwoPoints(poiline[576], poiline[577]);
	pSketchLines->MethodAddByTwoPoints(poiline[578], poiline[579]);
	pSketchLines->MethodAddByTwoPoints(poiline[580], poiline[581]);
	pSketchLines->MethodAddByTwoPoints(poiline[582], poiline[583]);
	pSketchLines->MethodAddByTwoPoints(poiline[584], poiline[585]);
	pSketchLines->MethodAddByTwoPoints(poiline[586], poiline[587]);
	pSketchLines->MethodAddByTwoPoints(poiline[588], poiline[589]);
	pSketchLines->MethodAddByTwoPoints(poiline[590], poiline[591]);
	pSketchLines->MethodAddByTwoPoints(poiline[592], poiline[593]);
	pSketchLines->MethodAddByTwoPoints(poiline[594], poiline[595]);
	pSketchLines->MethodAddByTwoPoints(poiline[596], poiline[597]);
	pSketchLines->MethodAddByTwoPoints(poiline[598], poiline[599]);
	pSketchLines->MethodAddByTwoPoints(poiline[600], poiline[601]);
	pSketchLines->MethodAddByTwoPoints(poiline[602], poiline[603]);
	pSketchLines->MethodAddByTwoPoints(poiline[604], poiline[605]);
	pSketchLines->MethodAddByTwoPoints(poiline[606], poiline[607]);
	pSketchLines->MethodAddByTwoPoints(poiline[608], poiline[609]);
	pSketchLines->MethodAddByTwoPoints(poiline[610], poiline[611]);
	pSketchLines->MethodAddByTwoPoints(poiline[612], poiline[613]);
	pSketchLines->MethodAddByTwoPoints(poiline[614], poiline[615]);
	pSketchLines->MethodAddByTwoPoints(poiline[616], poiline[617]);
	pSketchLines->MethodAddByTwoPoints(poiline[618], poiline[619]);
	pSketchLines->MethodAddByTwoPoints(poiline[620], poiline[621]);
	pSketchLines->MethodAddByTwoPoints(poiline[622], poiline[623]);
	pSketchLines->MethodAddByTwoPoints(poiline[624], poiline[625]);
	pSketchLines->MethodAddByTwoPoints(poiline[626], poiline[627]);
	pSketchLines->MethodAddByTwoPoints(poiline[628], poiline[629]);
	pSketchLines->MethodAddByTwoPoints(poiline[630], poiline[631]);
	pSketchLines->MethodAddByTwoPoints(poiline[632], poiline[633]);
	pSketchLines->MethodAddByTwoPoints(poiline[634], poiline[635]);
	pSketchLines->MethodAddByTwoPoints(poiline[636], poiline[637]);
	pSketchLines->MethodAddByTwoPoints(poiline[638], poiline[639]);
	pSketchLines->MethodAddByTwoPoints(poiline[640], poiline[641]);
	pSketchLines->MethodAddByTwoPoints(poiline[642], poiline[643]);
	pSketchLines->MethodAddByTwoPoints(poiline[644], poiline[645]);
	pSketchLines->MethodAddByTwoPoints(poiline[646], poiline[647]);
	pSketchLines->MethodAddByTwoPoints(poiline[648], poiline[649]);
	pSketchLines->MethodAddByTwoPoints(poiline[650], poiline[651]);
	pSketchLines->MethodAddByTwoPoints(poiline[652], poiline[653]);
	pSketchLines->MethodAddByTwoPoints(poiline[654], poiline[655]);
	pSketchLines->MethodAddByTwoPoints(poiline[656], poiline[657]);
	pSketchLines->MethodAddByTwoPoints(poiline[658], poiline[659]);
	pSketchLines->MethodAddByTwoPoints(poiline[660], poiline[661]);
	pSketchLines->MethodAddByTwoPoints(poiline[662], poiline[663]);
	pSketchLines->MethodAddByTwoPoints(poiline[664], poiline[665]);
	pSketchLines->MethodAddByTwoPoints(poiline[666], poiline[667]);
	pSketchLines->MethodAddByTwoPoints(poiline[668], poiline[669]);
	pSketchLines->MethodAddByTwoPoints(poiline[670], poiline[671]);
	pSketchLines->MethodAddByTwoPoints(poiline[672], poiline[673]);
	pSketchLines->MethodAddByTwoPoints(poiline[674], poiline[675]);
	pSketchLines->MethodAddByTwoPoints(poiline[676], poiline[677]);
	pSketchLines->MethodAddByTwoPoints(poiline[678], poiline[679]);
	pSketchLines->MethodAddByTwoPoints(poiline[680], poiline[681]);
	pSketchLines->MethodAddByTwoPoints(poiline[682], poiline[683]);
	pSketchLines->MethodAddByTwoPoints(poiline[684], poiline[685]);
	pSketchLines->MethodAddByTwoPoints(poiline[686], poiline[687]);
	pSketchLines->MethodAddByTwoPoints(poiline[688], poiline[689]);
	pSketchLines->MethodAddByTwoPoints(poiline[690], poiline[691]);
	pSketchLines->MethodAddByTwoPoints(poiline[692], poiline[693]);
	pSketchLines->MethodAddByTwoPoints(poiline[694], poiline[695]);
	pSketchLines->MethodAddByTwoPoints(poiline[696], poiline[697]);
	pSketchLines->MethodAddByTwoPoints(poiline[698], poiline[699]);
	pSketchLines->MethodAddByTwoPoints(poiline[700], poiline[701]);
	pSketchLines->MethodAddByTwoPoints(poiline[702], poiline[703]);
	pSketchLines->MethodAddByTwoPoints(poiline[704], poiline[705]);
	pSketchLines->MethodAddByTwoPoints(poiline[706], poiline[707]);
	pSketchLines->MethodAddByTwoPoints(poiline[708], poiline[709]);
	pSketchLines->MethodAddByTwoPoints(poiline[710], poiline[711]);
	pSketchLines->MethodAddByTwoPoints(poiline[712], poiline[713]);
	pSketchLines->MethodAddByTwoPoints(poiline[714], poiline[715]);
	pSketchLines->MethodAddByTwoPoints(poiline[716], poiline[717]);
	pSketchLines->MethodAddByTwoPoints(poiline[718], poiline[719]);
	pSketchLines->MethodAddByTwoPoints(poiline[720], poiline[721]);
	pSketchLines->MethodAddByTwoPoints(poiline[722], poiline[723]);

	pSketchLines->MethodAddByTwoPoints(poiline[724], poiline[725]);
	pSketchLines->MethodAddByTwoPoints(poiline[726], poiline[727]);
	pSketchLines->MethodAddByTwoPoints(poiline[728], poiline[729]);
	pSketchLines->MethodAddByTwoPoints(poiline[730], poiline[731]);
	pSketchLines->MethodAddByTwoPoints(poiline[732], poiline[733]);
	pSketchLines->MethodAddByTwoPoints(poiline[734], poiline[735]);
	pSketchLines->MethodAddByTwoPoints(poiline[736], poiline[737]);
	pSketchLines->MethodAddByTwoPoints(poiline[738], poiline[739]);
	pSketchLines->MethodAddByTwoPoints(poiline[740], poiline[741]);
	pSketchLines->MethodAddByTwoPoints(poiline[742], poiline[743]);
	pSketchLines->MethodAddByTwoPoints(poiline[744], poiline[745]);
	pSketchLines->MethodAddByTwoPoints(poiline[746], poiline[747]);
	pSketchLines->MethodAddByTwoPoints(poiline[748], poiline[749]);
	pSketchLines->MethodAddByTwoPoints(poiline[750], poiline[751]);
	pSketchLines->MethodAddByTwoPoints(poiline[752], poiline[753]);

	/*Стандартный текст внутри таблице*/
	poiline[190] = pTransGeom->MethodCreatePoint2d(0.66, 19.9);
	tb[1] = sk->TextBoxes->MethodAddFitted(poiline[190], L"Дубл.");
	poiline[191] = pTransGeom->MethodCreatePoint2d(0.66, 19.48);
	tb[2] = sk->TextBoxes->MethodAddFitted(poiline[191], L"Взам.");
	//poiline[192] = pTransGeom->MethodCreatePoint2d(0.66, 19.06);
	//tb[3] = sk->TextBoxes->MethodAddFitted(poiline[192], L"Подп.");
	//poiline[193] = pTransGeom->MethodCreatePoint2d(0.66, 17.8);
	//tb[4] = sk->TextBoxes->MethodAddFitted(poiline[193], L"Разраб");
	//poiline[194] = pTransGeom->MethodCreatePoint2d(0.66, 17.38);
	//tb[5] = sk->TextBoxes->MethodAddFitted(poiline[194], L"Принял");
	//poiline[225] = pTransGeom->MethodCreatePoint2d(0.66, 16.96);
	//tb[36] = sk->TextBoxes->MethodAddFitted(poiline[225], L"Проверил");	
	//poiline[195] = pTransGeom->MethodCreatePoint2d(0.66, 16.54);
	//tb[6] = sk->TextBoxes->MethodAddFitted(poiline[195], L"Утвердил");
	//poiline[196] = pTransGeom->MethodCreatePoint2d(0.66, 16.12);
	//tb[7] = sk->TextBoxes->MethodAddFitted(poiline[196], L"Н. контр.");
	poiline[197] = pTransGeom->MethodCreatePoint2d(1.05, 16.52);
	tb[8] = sk->TextBoxes->MethodAddFitted(poiline[197], L"А");
	poiline[198] = pTransGeom->MethodCreatePoint2d(1.05, 16.1);
	tb[9] = sk->TextBoxes->MethodAddFitted(poiline[198], L"Б");
	poiline[199] = pTransGeom->MethodCreatePoint2d(3.5, 15.65);
	tb[10] = sk->TextBoxes->MethodAddFitted(poiline[199], L"Наименование детали, сб. единицы или материала");
	poiline[200] = pTransGeom->MethodCreatePoint2d(16.45, 15.65);
	tb[11] = sk->TextBoxes->MethodAddFitted(poiline[200], L"Обозначение, код");
	poiline[201] = pTransGeom->MethodCreatePoint2d(21.64, 15.65);
	tb[12] = sk->TextBoxes->MethodAddFitted(poiline[201], L"ОПП");
	poiline[202] = pTransGeom->MethodCreatePoint2d(25.80, 15.65);
	tb[13] = sk->TextBoxes->MethodAddFitted(poiline[202], L"КИ");
	poiline[203] = pTransGeom->MethodCreatePoint2d(23, 15.65);
	tb[14] = sk->TextBoxes->MethodAddFitted(poiline[203], L"ЕВ");
	poiline[204] = pTransGeom->MethodCreatePoint2d(24.2, 15.65);
	tb[15] = sk->TextBoxes->MethodAddFitted(poiline[204], L"ЕН");
	poiline[205] = pTransGeom->MethodCreatePoint2d(27.5, 15.65);
	tb[16] = sk->TextBoxes->MethodAddFitted(poiline[205], L"Н.расх.");
	//poiline[206] = pTransGeom->MethodCreatePoint2d(23.7, 13.95);
	//tb[17] = sk->TextBoxes->MethodAddFitted(poiline[206], L"МЗ");
	poiline[207] = pTransGeom->MethodCreatePoint2d(2.14, 16.52);
	tb[18] = sk->TextBoxes->MethodAddFitted(poiline[207], L"Цех");
	poiline[208] = pTransGeom->MethodCreatePoint2d(3.22, 16.52);
	tb[19] = sk->TextBoxes->MethodAddFitted(poiline[208], L"Уч.");
	poiline[209] = pTransGeom->MethodCreatePoint2d(4.15, 16.52);
	tb[20] = sk->TextBoxes->MethodAddFitted(poiline[209], L"РМ");
	poiline[210] = pTransGeom->MethodCreatePoint2d(5.23, 16.52);
	tb[21] = sk->TextBoxes->MethodAddFitted(poiline[210], L"Опер.");
	poiline[211] = pTransGeom->MethodCreatePoint2d(7.64, 16.52);
	tb[22] = sk->TextBoxes->MethodAddFitted(poiline[211], L"Код, наименование операции");
	poiline[212] = pTransGeom->MethodCreatePoint2d(18, 16.52);
	tb[23] = sk->TextBoxes->MethodAddFitted(poiline[212], L"Обозначение документа");
	poiline[213] = pTransGeom->MethodCreatePoint2d(4.13, 16.1);
	tb[24] = sk->TextBoxes->MethodAddFitted(poiline[213], L"Код,наименование,оборудования");
	poiline[214] = pTransGeom->MethodCreatePoint2d(14.1, 16.1);
	tb[25] = sk->TextBoxes->MethodAddFitted(poiline[214], L"СМ");
	poiline[215] = pTransGeom->MethodCreatePoint2d(17, 16.1);
	tb[26] = sk->TextBoxes->MethodAddFitted(poiline[215], L"Р");
	poiline[216] = pTransGeom->MethodCreatePoint2d(18.23, 16.1);
	tb[27] = sk->TextBoxes->MethodAddFitted(poiline[216], L"УТ");
	poiline[217] = pTransGeom->MethodCreatePoint2d(20.2, 16.1);
	tb[28] = sk->TextBoxes->MethodAddFitted(poiline[217], L"КОНД");
	poiline[218] = pTransGeom->MethodCreatePoint2d(21.75, 16.1);
	tb[29] = sk->TextBoxes->MethodAddFitted(poiline[218], L"ЕН");
	poiline[219] = pTransGeom->MethodCreatePoint2d(23, 16.1);
	tb[30] = sk->TextBoxes->MethodAddFitted(poiline[219], L"ОП");
	poiline[220] = pTransGeom->MethodCreatePoint2d(24.1, 16.1);
	tb[31] = sk->TextBoxes->MethodAddFitted(poiline[220], L"К шт.");
	poiline[221] = pTransGeom->MethodCreatePoint2d(25.75, 16.1);
	tb[32] = sk->TextBoxes->MethodAddFitted(poiline[221], L"Т пз.");
	poiline[222] = pTransGeom->MethodCreatePoint2d(27.60, 16.1);
	tb[33] = sk->TextBoxes->MethodAddFitted(poiline[222], L"Т шт.");
	poiline[223] = pTransGeom->MethodCreatePoint2d(15.4, 16.1);
	tb[34] = sk->TextBoxes->MethodAddFitted(poiline[223], L"Проф.");
	/*Нумерация*/
	poiline[226] = pTransGeom->MethodCreatePoint2d(0.85, 15.65);
	tb[37] = sk->TextBoxes->MethodAddFitted(poiline[226], L"К/М");
	poiline[227] = pTransGeom->MethodCreatePoint2d(0.75, 13.6);
	tb[38] = sk->TextBoxes->MethodAddFitted(poiline[227], L"01");
	poiline[228] = pTransGeom->MethodCreatePoint2d(0.75, 12.67);
	tb[39] = sk->TextBoxes->MethodAddFitted(poiline[228], L"02");
	poiline[229] = pTransGeom->MethodCreatePoint2d(0.75, 12.25);
	tb[40] = sk->TextBoxes->MethodAddFitted(poiline[229], L"03");
	poiline[230] = pTransGeom->MethodCreatePoint2d(0.75, 11.6);
	tb[41] = sk->TextBoxes->MethodAddFitted(poiline[230], L"04");
	poiline[231] = pTransGeom->MethodCreatePoint2d(0.75, 10.7);
	tb[42] = sk->TextBoxes->MethodAddFitted(poiline[231], L"05");
	poiline[232] = pTransGeom->MethodCreatePoint2d(0.75, 9.8);
	tb[43] = sk->TextBoxes->MethodAddFitted(poiline[232], L"06");
	poiline[233] = pTransGeom->MethodCreatePoint2d(0.75, 9.08);
	tb[44] = sk->TextBoxes->MethodAddFitted(poiline[233], L"07");
	poiline[234] = pTransGeom->MethodCreatePoint2d(0.75, 8.2);
	tb[45] = sk->TextBoxes->MethodAddFitted(poiline[234], L"08");
	poiline[235] = pTransGeom->MethodCreatePoint2d(0.75, 7.4);
	tb[46] = sk->TextBoxes->MethodAddFitted(poiline[235], L"09");
	poiline[236] = pTransGeom->MethodCreatePoint2d(0.75, 6.52);
	tb[47] = sk->TextBoxes->MethodAddFitted(poiline[236], L"10");
	poiline[237] = pTransGeom->MethodCreatePoint2d(0.75, 5.6);
	tb[48] = sk->TextBoxes->MethodAddFitted(poiline[237], L"11");
	poiline[238] = pTransGeom->MethodCreatePoint2d(0.75, 4.8);
	tb[49] = sk->TextBoxes->MethodAddFitted(poiline[238], L"12");
	poiline[239] = pTransGeom->MethodCreatePoint2d(0.75, 4);
	tb[50] = sk->TextBoxes->MethodAddFitted(poiline[239], L"13");
	poiline[240] = pTransGeom->MethodCreatePoint2d(0.75, 3.1);
	tb[51] = sk->TextBoxes->MethodAddFitted(poiline[240], L"14");
	poiline[241] = pTransGeom->MethodCreatePoint2d(0.75, 2.25);
	tb[52] = sk->TextBoxes->MethodAddFitted(poiline[241], L"15");
	poiline[242] = pTransGeom->MethodCreatePoint2d(0.75, 1.4);
	tb[53] = sk->TextBoxes->MethodAddFitted(poiline[242], L"16");
	poiline[243] = pTransGeom->MethodCreatePoint2d(1.1, 0.6);
	tb[54] = sk->TextBoxes->MethodAddFitted(poiline[243], L"МК");
	/*Конец (Стандартны текст внутри таблице)*/

	/*Размер шрифта*/
	TextStylePtr pStyle;
	pStyle = tb[54]->GetStyle();
	pStyle->PutFontSize(0.26);

	sk->raw_ExitEdit();//закрытие редактирования чертежа
}

void CprTextCardApp::MakeTxt(double x, double y, _bstr_t text)
{
	SheetPtr sheet = sh->GetItem(1);//создание указателя на лист
	DrawingSketchPtr sk = sheet->GetSketches()->MethodAdd();//добавление эскиза на лист
	sk->raw_Edit();//начало редактирования эскиза
	Point2dPtr poiline[5];//переменная для хранения точек
	TextBoxPtr tb[5];//переменная для хранения точек текста

	double x1 = 1.2;

	poiline[0] = pTransGeom->MethodCreatePoint2d(x, y);
	tb[0] = sk->TextBoxes->MethodAddFitted(poiline[0], text);

	sk->raw_ExitEdit();//закрытие редактирования чертежа
}

void CprTextCardApp::MakeDoc1(_bstr_t strTemplateFilename) {

	pDrawDoc = pInvApp->Documents->MethodAdd(kDrawingDocumentObject, strTemplateFilename, true);//создание файла

																								//sheet->put_Orientation(kPortraitPageOrientation);

	pDrawDoc->DisplayName = _T("MarshCard");//имя файла

	pDrawDoc->get_Sheets(&sh);//создание листа

							  //подготовка к работе с документом

	pInvApp->get_TransientGeometry(&pTransGeom);

	pTransManager = pInvApp->GetTransactionManager();

	Doc = CComQIPtr <Document>(pDrawDoc);

	pTransManager->raw_StartTransaction(Doc, _T(""), &pTrans);

	MakeSqMK();
}