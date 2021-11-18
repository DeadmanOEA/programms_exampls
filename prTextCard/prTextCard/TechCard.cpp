// TechCard.cpp: файл реализации
//

#include "stdafx.h"
#include "prTextCard.h"
#include "TechCard.h"
#include "afxdialogex.h"
#include "MashCard.h"
#include "DlgDetMake.h"
#include "DLGDopInf.h"
#include "odbcinst.h"
#include "afxdb.h"

// диалоговое окно CTechCard

IMPLEMENT_DYNAMIC(CTechCard, CDialog)

CTechCard::CTechCard(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_TechCard, pParent)
{

}

CTechCard::~CTechCard()
{
}

void CTechCard::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTSaveMake2, m_butSaveMake);
	DDX_Control(pDX, IDC_BUTOpenSave2, m_butOpenSave);
	DDX_Control(pDX, IDC_BUTLoadSb2, m_butLoadSb);
	DDX_Control(pDX, IDC_BUTTONCHANGEDLG2, m_butChangeDlg);
	DDX_Control(pDX, IDC_STATICA1, m_stCodeWorkshop);
	DDX_Control(pDX, IDC_STATICA2, m_stCodePlot);
	DDX_Control(pDX, IDC_STATICA3, m_stNumWorkplase);
	DDX_Control(pDX, IDC_STATICA4, m_stNumOperation);
	DDX_Control(pDX, IDC_STATICA5, m_stNameOperation);
	DDX_Control(pDX, IDC_EDITCex, m_edCodeWorkshop);
	DDX_Control(pDX, IDC_EDITUch, m_edCodePlot);
	DDX_Control(pDX, IDC_EDITPM, m_edNumWorkplase);
	DDX_Control(pDX, IDC_EDITOper, m_edNumOperation);
	DDX_Control(pDX, IDC_COMBONameOper, m_cbNameOperation);
	DDX_Control(pDX, IDC_STATICM1, m_stNameDetail);
	DDX_Control(pDX, IDC_STATICM2, m_stDesignationCode);
	DDX_Control(pDX, IDC_STATICM3, m_stDivisionDesignation);
	DDX_Control(pDX, IDC_STATICM4, m_stUnitCode);
	DDX_Control(pDX, IDC_STATICM5, m_stAmountData);
	DDX_Control(pDX, IDC_STATICM6, m_stConsumptionRate);
	DDX_Control(pDX, IDC_EDITM1, m_edNameMaterial);
	DDX_Control(pDX, IDC_EDITM2, m_edDesignationCode);
	DDX_Control(pDX, IDC_EDITM3, m_edDivisionDesignation);
	DDX_Control(pDX, IDC_EDITM4, m_edUnitCode);
	DDX_Control(pDX, IDC_EDITM5, m_edAmountData);
	DDX_Control(pDX, IDC_EDITM6, m_edConsumptionRate);
	DDX_Control(pDX, IDC_COMBOM1, m_cbNameDetail);
	DDX_Control(pDX, IDC_STATICT, m_stAccessoriesAuxiliaryTool);
	DDX_Control(pDX, IDC_EDITT1, m_edAccessoriesAuxiliaryTool);
	DDX_Control(pDX, IDC_LISTDet, m_listCtrl);
	DDX_Control(pDX, IDC_BUTTONAddtb, m_butAddTb);
	DDX_Control(pDX, IDC_BUTTONChange, m_butChangeTb);
	DDX_Control(pDX, IDC_BUTTONDel, m_butDelTb);
	DDX_Control(pDX, IDC_LISTMain, m_lcMain);
	DDX_Control(pDX, IDC_LISTO1, m_listO1);
	DDX_Control(pDX, IDC_LISTO2, m_listO2);
	DDX_Control(pDX, IDC_LISTO3, m_listO3);
	DDX_Control(pDX, IDC_LISTO4, m_listO4);
	DDX_Control(pDX, IDC_BUTTONOBut, m_butOBut);
	DDX_Control(pDX, IDC_EDITOEd, m_edOEd);
	DDX_Control(pDX, IDC_STATICB1, m_stCodeNameEquipment);
	DDX_Control(pDX, IDC_STATICB2, m_stDagreeMech);
	DDX_Control(pDX, IDC_STATICB3, m_stCodProf);
	DDX_Control(pDX, IDC_STATICB4, m_stRank);
	DDX_Control(pDX, IDC_STATICB5, m_stLaborCode);
	DDX_Control(pDX, IDC_STATICB6, m_stNumPerfomens);
	DDX_Control(pDX, IDC_STATICB7, m_stNumManuf);
	DDX_Control(pDX, IDC_STATICB8, m_stStrUnit);
	DDX_Control(pDX, IDC_STATICB9, m_stBatchSize);
	DDX_Control(pDX, IDC_STATICB10, m_stPieseTime);
	DDX_Control(pDX, IDC_STATICB11, m_stNormFinalTime);
	DDX_Control(pDX, IDC_STATICB12, m_stNormTime);
	DDX_Control(pDX, IDC_EDITB1, m_edCodeNameEquipment);
	DDX_Control(pDX, IDC_EDITB2, m_edDagreeMech);
	DDX_Control(pDX, IDC_EDITB3, m_edCodProf);
	DDX_Control(pDX, IDC_EDITB4, m_edRank);
	DDX_Control(pDX, IDC_EDITB5, m_edLaborCode);
	DDX_Control(pDX, IDC_EDITB6, m_edNumPerfomens);
	DDX_Control(pDX, IDC_EDITB7, m_edNumManuf);
	DDX_Control(pDX, IDC_EDITB8, m_edStrUnit);
	DDX_Control(pDX, IDC_EDITB9, m_edBatchSize);
	DDX_Control(pDX, IDC_EDITB10, m_edPieseTime);
	DDX_Control(pDX, IDC_EDITB11, m_edNormFinalTime);
	DDX_Control(pDX, IDC_EDITB12, m_edNormTime);
	DDX_Control(pDX, IDC_BUTTONO2, m_butO2);
	DDX_Control(pDX, IDC_BUTTONA, m_buA);
	DDX_Control(pDX, IDC_BUTTONB, m_buB);
	DDX_Control(pDX, IDC_BUTTONK, m_buK);
	DDX_Control(pDX, IDC_BUTTONM, m_buM);
	DDX_Control(pDX, IDC_BUTTONO, m_buO);
	DDX_Control(pDX, IDC_BUTTONT, m_buT);
	DDX_Control(pDX, IDC_STATICA6, m_stDesignationDoc);
	DDX_Control(pDX, IDC_EDITA6, m_edDesignationDoc);
	DDX_Control(pDX, IDC_STATICM7, m_stEdNorm);
	DDX_Control(pDX, IDC_EDITM7, m_edEdNorm);
}


BEGIN_MESSAGE_MAP(CTechCard, CDialog)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BUTOpenSave2, &CTechCard::OnBnClickedButopensave2)
	ON_BN_CLICKED(IDC_BUTSaveMake2, &CTechCard::OnBnClickedButsavemake2)
	ON_BN_CLICKED(IDC_BUTLoadSb2, &CTechCard::OnBnClickedButloadsb2)
	ON_BN_CLICKED(IDC_BUTTONCHANGEDLG2, &CTechCard::OnBnClickedButtonchangedlg2)
	ON_BN_CLICKED(IDOK, &CTechCard::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTONA, &CTechCard::OnBnClickedButtona)
	ON_BN_CLICKED(IDC_BUTTONK, &CTechCard::OnBnClickedButtonk)
	ON_BN_CLICKED(IDC_BUTTONO, &CTechCard::OnBnClickedButtono)
	ON_BN_CLICKED(IDC_BUTTONB, &CTechCard::OnBnClickedButtonb)
	ON_BN_CLICKED(IDC_BUTTONM, &CTechCard::OnBnClickedButtonm)
	ON_BN_CLICKED(IDC_BUTTONT, &CTechCard::OnBnClickedButtont)
	ON_BN_CLICKED(IDC_BUTTONDopInf, &CTechCard::OnBnClickedButtondopinf)
	ON_BN_CLICKED(IDC_BUTTONClean, &CTechCard::OnBnClickedButtonclean)
	ON_BN_CLICKED(IDC_BUTTONOBut, &CTechCard::OnBnClickedButtonobut)
	ON_BN_CLICKED(IDC_BUTTONO2, &CTechCard::OnBnClickedButtono2)
	ON_BN_CLICKED(IDC_BUTTONAddtb, &CTechCard::OnBnClickedButtonaddtb)
	ON_BN_CLICKED(IDC_BUTTONChange, &CTechCard::OnBnClickedButtonchange)
	ON_BN_CLICKED(IDC_BUTTONDel, &CTechCard::OnBnClickedButtondel)
END_MESSAGE_MAP()


// обработчики сообщений CTechCard


void CTechCard::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: добавьте свой код обработчика сообщений
					   // Не вызывать CDialog::OnPaint() для сообщений рисования
	CRect rect;
	GetClientRect(&rect);
	CDC *pDC = this->GetDC();

	if (faq == false) {
		HBRUSH  hBrush = CreateSolidBrush(RGB(255, 255, 255));
		pDC->SelectObject(hBrush);
		pDC->Rectangle(rect.left, rect.top, rect.right - rect.left, rect.top + 40);
		pDC->Rectangle(rect.left, rect.bottom - 438, rect.right - rect.left, rect.bottom - 40);
		//
		hBrush = CreateSolidBrush(RGB(64, 64, 64));
		pDC->SelectObject(hBrush);
		pDC->Rectangle(rect.left, rect.bottom - 40, rect.right - rect.left, rect.bottom - rect.top);
		//
		hBrush = CreateSolidBrush(RGB(255, 246, 158));
		pDC->SelectObject(hBrush);
		pDC->Rectangle(rect.left, rect.top + 40, rect.right - 451, rect.bottom - 438);
		pDC->Rectangle(rect.right - 451, rect.top + 40, rect.right - rect.left, rect.bottom - 608);
		faq = true;
	}
}


BOOL CTechCard::OnInitDialog()
{
	CDialog::OnInitDialog();
	
	// TODO:  Добавить дополнительную инициализацию
	//Вставим изображение в кнопки//
	m_butSaveMake.LoadBitmaps(IDB_BITMAPSaveMake, IDB_BITMAPSaveMake, 0, IDB_BITMAPSaveMake);
	m_butOpenSave.LoadBitmaps(IDB_BITMAPOpenSave, IDB_BITMAPOpenSave, 0, IDB_BITMAPOpenSave);
	m_butLoadSb.LoadBitmaps(IDB_BITMAPLoadSb, IDB_BITMAPLoadSb, 0, IDB_BITMAPLoadSb);
	//
	m_butChangeDlg.LoadBitmaps(IDB_BITMAP2DLG1TXTMENU, IDB_BITMAP2DLG1TXTMENU, 0, IDB_BITMAP2DLG1TXTMENU);
	//
	m_butAddTb.LoadBitmaps(IDB_BITMAPAddTable, IDB_BITMAPAddTable, 0, IDB_BITMAPAddTable);
	m_butChangeTb.LoadBitmaps(IDB_BITMAPChangeTb, IDB_BITMAPChangeTb, 0, IDB_BITMAPChangeTb);
	m_butDelTb.LoadBitmaps(IDB_BITMAPDelTb, IDB_BITMAPDelTb, 0, IDB_BITMAPDelTb);
	//
	/*Создание таблиц*/
	int nItem2;
	VarBut = 0;
	ClickOff = 0;
	openDef = 0;
	//Создание первой таблицы
	m_listCtrl.InsertColumn(0, L"ID", LVCFMT_LEFT, 40);
	m_listCtrl.InsertColumn(1, L"Название", LVCFMT_LEFT, 150);
	m_listCtrl.InsertColumn(2, L"Позиция", LVCFMT_LEFT, 100);
	m_listCtrl.InsertColumn(3, L"Количество", LVCFMT_LEFT, 120);
	m_listCtrl.SetExtendedStyle(m_lcMain.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	//Создание второй таблицы
	m_lcMain.InsertColumn(0, L"№", LVCFMT_LEFT, 60);
	//А
	m_lcMain.InsertColumn(1, L"Служ.символ", LVCFMT_LEFT, 130);
	m_lcMain.InsertColumn(2, L"Цех.", LVCFMT_LEFT, 60);
	m_lcMain.InsertColumn(3, L"Уч.", LVCFMT_LEFT, 60);
	m_lcMain.InsertColumn(4, L"РМ.", LVCFMT_LEFT, 60);
	m_lcMain.InsertColumn(5, L"Опер.", LVCFMT_LEFT, 70);
	m_lcMain.InsertColumn(6, L"Код,наименование операции", LVCFMT_LEFT, 320);
	m_lcMain.InsertColumn(7, L"Обозначение документа", LVCFMT_LEFT, 320);
	//Б
	m_lcMain.InsertColumn(8, L"Служ.символ", LVCFMT_LEFT, 130);
	m_lcMain.InsertColumn(9, L"Код,наименование,оборудования", LVCFMT_LEFT, 320);
	m_lcMain.InsertColumn(10, L"СМ", LVCFMT_LEFT, 60);
	m_lcMain.InsertColumn(11, L"Проф.", LVCFMT_LEFT, 80);
	m_lcMain.InsertColumn(12, L"Р", LVCFMT_LEFT, 60);
	m_lcMain.InsertColumn(13, L"УТ", LVCFMT_LEFT, 60);
	m_lcMain.InsertColumn(14, L"КР", LVCFMT_LEFT, 60);
	m_lcMain.InsertColumn(15, L"КОИД", LVCFMT_LEFT, 70);
	m_lcMain.InsertColumn(16, L"ЕН", LVCFMT_LEFT, 60);
	m_lcMain.InsertColumn(17, L"ОП", LVCFMT_LEFT, 60);
	m_lcMain.InsertColumn(18, L"Кшт.", LVCFMT_LEFT, 70);
	m_lcMain.InsertColumn(19, L"Тпз", LVCFMT_LEFT, 80);
	m_lcMain.InsertColumn(20, L"Тшт.", LVCFMT_LEFT, 80);
	//К М
	m_lcMain.InsertColumn(21, L"Служ.символ", LVCFMT_LEFT, 130);
	m_lcMain.InsertColumn(22, L"Наименование детали,сб.единицы или материала", LVCFMT_LEFT, 570);
	m_lcMain.InsertColumn(23, L"Обозначение,код", LVCFMT_LEFT, 350);
	m_lcMain.InsertColumn(24, L"ОПП", LVCFMT_LEFT, 70);
	m_lcMain.InsertColumn(25, L"ЕВ", LVCFMT_LEFT, 60);
	m_lcMain.InsertColumn(26, L"ЕН", LVCFMT_LEFT, 70);
	m_lcMain.InsertColumn(27, L"КИ", LVCFMT_LEFT, 80);
	m_lcMain.InsertColumn(28, L"Н.расх.", LVCFMT_LEFT, 80);
	//О
	m_lcMain.InsertColumn(29, L"Служ.символ", LVCFMT_LEFT, 130);
	m_lcMain.InsertColumn(30, L"Содержание операции (перехода)", LVCFMT_LEFT, 570);
	//Т
	m_lcMain.InsertColumn(31, L"Служ.символ", LVCFMT_LEFT, 130);
	m_lcMain.InsertColumn(32, L"Информация о применяемой при выполнении операции технологической оснастке", LVCFMT_LEFT, 750);
	m_lcMain.SetExtendedStyle(m_lcMain.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	//Создание третий таблицы
	m_listO1.InsertColumn(0, L"Наименование действия", LVCFMT_LEFT, 220);
	m_listO1.SetExtendedStyle(m_lcMain.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	//Создание четвертой таблицы
	m_listO2.InsertColumn(0, L"Конструкторский элемент", LVCFMT_LEFT, 460);
	m_listO2.SetExtendedStyle(m_lcMain.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	//Создание пятой таблицы
	m_listO3.InsertColumn(0, L"Вид конструкторского элемента", LVCFMT_LEFT, 280);
	m_listO3.SetExtendedStyle(m_lcMain.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	//Создание шестой таблицы
	m_listO4.InsertColumn(0, L"Дополнительная информация", LVCFMT_LEFT, 280);
	m_listO4.SetExtendedStyle(m_lcMain.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

	///*Тест пример для постояния*/
	//nItem2 = m_lcMain.InsertItem(0, L"01");//ID
	////А
	//m_lcMain.SetItemText(nItem2, 1, L"А");
	//m_lcMain.SetItemText(nItem2, 31, L"Т");
	//m_lcMain.SetItemText(nItem2, 29, L"О");
	//m_lcMain.SetItemText(nItem2, 2, L"001");
	//m_lcMain.SetItemText(nItem2, 3, L"001");
	//m_lcMain.SetItemText(nItem2, 4, L"010");
	//m_lcMain.SetItemText(nItem2, 5, L"0001");
	//m_lcMain.SetItemText(nItem2, 6, L"8800 Сборка");
	//m_lcMain.SetItemText(nItem2, 7, L"ИОТ №102.23.423");
	////Б
	//m_lcMain.SetItemText(nItem2, 8, L"Б");
	//m_lcMain.SetItemText(nItem2, 31, L"Т");
	//m_lcMain.SetItemText(nItem2, 29, L"О");
	//m_lcMain.SetItemText(nItem2, 9, L"Сборочно монтажный стол");
	//m_lcMain.SetItemText(nItem2, 10, L"1");
	//m_lcMain.SetItemText(nItem2, 11, L"18116");
	//m_lcMain.SetItemText(nItem2, 12, L"311");
	//m_lcMain.SetItemText(nItem2, 13, L"1");
	//m_lcMain.SetItemText(nItem2, 14, L"1");
	//m_lcMain.SetItemText(nItem2, 15, L"1");
	//m_lcMain.SetItemText(nItem2, 16, L"100");
	//m_lcMain.SetItemText(nItem2, 17, L"166");
	//m_lcMain.SetItemText(nItem2, 18, L"100");
	//m_lcMain.SetItemText(nItem2, 19, L"12");
	//m_lcMain.SetItemText(nItem2, 20, L"000.2");
	////К
	//m_lcMain.SetItemText(nItem2, 21, L"К/М");
	//m_lcMain.SetItemText(nItem2, 31, L"Т");
	//m_lcMain.SetItemText(nItem2, 29, L"О");
	//m_lcMain.SetItemText(nItem2, 22, L"Сборочно монтажный стол");
	//m_lcMain.SetItemText(nItem2, 23, L"ХХХ.ХХХ.ХХХ");
	//m_lcMain.SetItemText(nItem2, 24, L"11");
	//m_lcMain.SetItemText(nItem2, 25, L"ХХХ");
	//m_lcMain.SetItemText(nItem2, 26, L"1");
	//m_lcMain.SetItemText(nItem2, 27, L"-");
	//m_lcMain.SetItemText(nItem2, 28, L"-");
	////М
	//nItem2 = m_lcMain.InsertItem(0, L"02");//ID
	//m_lcMain.SetItemText(nItem2, 1, L"А");
	//m_lcMain.SetItemText(nItem2, 8, L"Б");
	//m_lcMain.SetItemText(nItem2, 21, L"К/М");
	//m_lcMain.SetItemText(nItem2, 31, L"Т");
	//m_lcMain.SetItemText(nItem2, 29, L"О");
	//m_lcMain.SetItemText(nItem2, 22, L"Смазка для деталей");
	//m_lcMain.SetItemText(nItem2, 23, L"АБВГ.ХХХХХХ.ХХХ");
	//m_lcMain.SetItemText(nItem2, 24, L"11");
	//m_lcMain.SetItemText(nItem2, 25, L"ХХХ");
	//m_lcMain.SetItemText(nItem2, 26, L"1");
	//m_lcMain.SetItemText(nItem2, 27, L"-");
	//m_lcMain.SetItemText(nItem2, 28, L"-");
	////О
	//nItem2 = m_lcMain.InsertItem(0, L"03");//ID
	//m_lcMain.SetItemText(nItem2, 1, L"А");
	//m_lcMain.SetItemText(nItem2, 8, L"Б");
	//m_lcMain.SetItemText(nItem2, 21, L"К/М");
	//m_lcMain.SetItemText(nItem2, 31, L"Т");
	//m_lcMain.SetItemText(nItem2, 29, L"О");
	//m_lcMain.SetItemText(nItem2, 30, L"1. Собрать деталь ручка (1) согласно чертежу");
	//nItem2 = m_lcMain.InsertItem(0, L"04");//ID
	//m_lcMain.SetItemText(nItem2, 1, L"А");
	//m_lcMain.SetItemText(nItem2, 8, L"Б");
	//m_lcMain.SetItemText(nItem2, 21, L"К/М");
	//m_lcMain.SetItemText(nItem2, 31, L"Т");
	//m_lcMain.SetItemText(nItem2, 29, L"О");
	//m_lcMain.SetItemText(nItem2, 30, L"2. Разобрать детали, корпус(3) сборочная единица по шаблону");
	//nItem2 = m_lcMain.InsertItem(0, L"05");//ID
	//m_lcMain.SetItemText(nItem2, 1, L"А");
	//m_lcMain.SetItemText(nItem2, 8, L"Б");
	//m_lcMain.SetItemText(nItem2, 21, L"К/М");
	//m_lcMain.SetItemText(nItem2, 31, L"Т");
	//m_lcMain.SetItemText(nItem2, 29, L"О");
	//m_lcMain.SetItemText(nItem2, 30, L"3. Установить детали, винт (4) и винт (5) согласно эскизу");
	////Т
	//m_lcMain.SetItemText(nItem2, 1, L"А");
	//m_lcMain.SetItemText(nItem2, 8, L"Б");
	//m_lcMain.SetItemText(nItem2, 21, L"К/М");
	//m_lcMain.SetItemText(nItem2, 31, L"Т");
	//m_lcMain.SetItemText(nItem2, 32, L"АБВГ.ХХХ.ХХХ.ХХХ Отвертки с прямым шлицем");

	openDb();
	AllStrText();
	return TRUE;  // return TRUE unless you set the focus to a control
				  // Исключение: страница свойств OCX должна возвращать значение FALSE
}

void CTechCard::OnBnClickedButopensave2()
{
	CString fileName;

	CFileDialog fileDialog(TRUE,
		NULL,
		L"save.ds",
		OFN_OVERWRITEPROMPT,
		NULL,
		NULL,
		0,
		TRUE);

	if (fileDialog.DoModal() == IDOK)
	{
		fileName = fileDialog.GetPathName();
		CFile cfile;
		cfile.Open(fileName, CFile::modeRead | CFile::modeReadWrite);
		char szBuffer[1200];
		CString sText;
		cfile.Read(szBuffer, sizeof(szBuffer));
		CStringW unicode = CA2W(szBuffer, CP_UTF8);
		sText = unicode;

		int iNum;
		int numColl = 0;
		int nItem;
		CString textCol;

		for (int i = 0; i < sText.GetLength(); i++) {
			if (sText[i] == '*') {
				i++;
				if (sText[i] == '1') {
					iNum = 1;
				}
				else {
					iNum = 2;
				}
				i++;
			}
			////////////////////////////////////////
			else if (sText[i] == '/') {
				/**/
				if (textCol != '&') {
					//
					if (iNum == 1) {
						if (numColl == 0) {
							nItem = m_listCtrl.InsertItem(0, textCol);
						}
						else {
							m_listCtrl.SetItemText(nItem, numColl, textCol);
						}
					}
					else {
						if (numColl == 0) {
							nItem = m_lcMain.InsertItem(0, textCol);
						}
						else {
							m_lcMain.SetItemText(nItem, numColl, textCol);
						}
					}
					//
				}
				numColl++;
				textCol = L"";
			}
			else if (sText[i] == '\n') {
				numColl = 0;
				textCol = L"";
			}
			else {
				textCol += sText[i];
			}
		}
	}
}

/*Сохранить файл*/
void CTechCard::OnBnClickedButsavemake2()
{
	CFileDialog fileDialog(FALSE,
		NULL,
		L"save.ds",
		OFN_OVERWRITEPROMPT,
		NULL,
		NULL,
		0,
		TRUE);
	int result = fileDialog.DoModal();    //запустить диалоговое окно
	if (result == IDOK)    //если файл выбран
	{
		CFile cfile(fileDialog.GetPathName(), CFile::modeWrite | CFile::modeCreate);
		CString sText;

		for (int i = 0; i < m_listCtrl.GetItemCount(); i++) {
			cfile.Write(L"*", 1);
			cfile.Write(L"1", 1);
			cfile.Write(L"*", 1);
			for (int k = 0; k < 4; k++) {
				sText = m_listCtrl.GetItemText(i, k);
				if (sText == L"") {
					sText = L"&";
				}
				CStringA sUTF8 = CW2A(sText, CP_UTF8);
				cfile.Write(sUTF8, sUTF8.GetLength());
				cfile.Write(L"/", 1);
			}
			cfile.Write(L"\n", 1);
		}
		for (int i = 0; i < m_lcMain.GetItemCount(); i++) {
			cfile.Write(L"*", 1);
			cfile.Write(L"2", 1);
			cfile.Write(L"*", 1);
			for (int k = 0; k < 33; k++) {
				sText = m_lcMain.GetItemText(i, k);
				if (sText == L"") {
					sText = L"&";
				}
				CStringA sUTF8 = CW2A(sText, CP_UTF8);
				cfile.Write(sUTF8, sUTF8.GetLength());
				cfile.Write(L"/", 1);
			}
			cfile.Write(L"\n", 1);
		}
	}
}

/*Кнопка открыть сборку*/
void CTechCard::OnBnClickedButloadsb2()
{
	CString fileName;

	CFileDialog* fd = new CFileDialog(true);

	if (fd->DoModal() == IDOK)
	{
		fileName = fd->GetPathName();

		strTemplateFilenameBOM = fileName;

		if (openDef == 0) {
			m_pDoc->OpenInventor();
			openDef = 1;
		}
		CprTextCardApp* pApp = (CprTextCardApp*)AfxGetApp();
		pApp->csPartName.RemoveAll();
		pApp->csItemNumber.RemoveAll();
		pApp->csItemQuantity.RemoveAll();

		m_pDoc->OpenBOM(strTemplateFilenameBOM);

		for (int i = 0; i < pApp->csPartName.GetCount(); i++) {
			int nCount = m_listCtrl.GetItemCount();
			int nItem;
			CString str;
			str.Format(L"%d", nCount);
			if (nCount < 10) {
				str = '0' + str;
			}

			nItem = m_listCtrl.InsertItem(0, str);
			m_listCtrl.SetItemText(nItem, 1, pApp->csPartName[i]);
			m_listCtrl.SetItemText(nItem, 2, pApp->csItemNumber[i]);
			m_listCtrl.SetItemText(nItem, 3, pApp->csItemQuantity[i]);
		}
	}
	for (int i = 0; i < m_listCtrl.GetItemCount(); i++) {
		m_cbNameDetail.AddString(m_listCtrl.GetItemText(i, 1));
	}

}

/*Кнопка переход на построения  "Маршрутной схемы сборки"*/
void CTechCard::OnBnClickedButtonchangedlg2()
{
	OnCancel();
	CMashCard openDialog;
	openDialog.DoModal();
}

/*Кнопка построения "Маршрутной карты сборки"*/
void CTechCard::OnBnClickedOk()
{
	CString path;

	TCHAR buffer[MAX_PATH];
	DWORD size = GetCurrentDirectory(sizeof(buffer), buffer);

	path = buffer;

	path += L"\\MK.idw";

	strTemplateFilename = path;//Путь к стандартному шаблону документа//

	if (openDef == 0) {
		m_pDoc->OpenInventor();
		openDef = 1;
	}
	DelVar();
	AllEdText();
	MakeTableText();
	MakeDoc();
}

void CTechCard::AddTextCar(double x, double y, CString text, int list)
{
	coordX.Add(x);
	coordY.Add(y);
	sqPos.Add(text);
	listN.Add(list);
}

void CTechCard::DelVar()
{
	sqPos.RemoveAll();
	coordX.RemoveAll();
	coordY.RemoveAll();
}

void CTechCard::MakeDoc() {
	m_pDoc->MakeDoc1(strTemplateFilename);

	for (int i = 0; i < coordX.GetCount(); i++) {
		if (i != 0) {
			if (listN[i] > listN[i - 1]) {
				//Создание 2 листа
			}
		}
		m_pDoc->MakeTxt(coordX[i], coordY[i], sqPos[i]);
	}

}

/*Запись в пополнительной информации в маршрутную карту*/
void CTechCard::AllEdText()
{
	CprTextCardApp* pApp = (CprTextCardApp*)AfxGetApp();

	AddTextCar(3, 17.79, pApp->m_edUser, 0);
	AddTextCar(3, 17.36, pApp->m_edCheck, 0);
	AddTextCar(3, 16.93, pApp->m_edHasAccepted, 0);
	AddTextCar(3, 16.08, pApp->m_edNKontr, 0);
	AddTextCar(3, 16.5, pApp->m_edApproved, 0);

	AddTextCar(1, 18.5, pApp->m_edAddInfo, 0);
	AddTextCar(15.7, 18.5, pApp->m_edDesignationNumDoc, 0);
	AddTextCar(21.7, 18.5, pApp->m_edDesignationMainDoc, 0);
	AddTextCar(26.64, 18.5, pApp->m_edNumQuantity, 0);
	AddTextCar(28.2, 18.5, pApp->m_edSequenceNumberSheet, 0);

	AddTextCar(10.4, 17.5, pApp->m_edNameCompony, 0);
	AddTextCar(14.6, 17.5, pApp->m_edProductDesignations, 0);
	AddTextCar(20.5, 17.5, pApp->m_edClassificationGroupCode, 0);
	AddTextCar(24.7, 17.5, pApp->m_edDocumentDesignations, 0);
	AddTextCar(26.20, 16.35, pApp->m_edLiteraLeft, 0);
	AddTextCar(27.30, 16.35, pApp->m_edLiteraCentr, 0);
	AddTextCar(28.30, 16.35, pApp->m_edLiteraRight, 0);
	AddTextCar(13.81, 16.35, pApp->m_edName, 0);
	AddTextCar(10.3, 16.35, pApp->m_edStandardizationUnit, 0);
}

void CTechCard::MakeTableText()
{
	x0shem = 1.85;
	y0shem = 14.15;
	listText = 1;
	int lineTxt = 16;
	int numLine = 0;

	for (int i = 0; i < m_lcMain.GetItemCount(); i++) {
		//A
		if ((m_lcMain.GetItemText(i, 2) != L"") || (m_lcMain.GetItemText(i, 3) != L"") || (m_lcMain.GetItemText(i, 4) != L"") ||
			(m_lcMain.GetItemText(i, 5) != L"") || (m_lcMain.GetItemText(i, 6) != L"") || (m_lcMain.GetItemText(i, 7) != L"")) {

			AddTextCar(0.75, y0shem - numLine * 0.85, L"А", listText);
			AddTextCar(2, y0shem - numLine * 0.85, m_lcMain.GetItemText(i, 2), listText);//Y = 14.15
			AddTextCar(3, y0shem - numLine * 0.85, m_lcMain.GetItemText(i, 3), listText);
			AddTextCar(4, y0shem - numLine * 0.85, m_lcMain.GetItemText(i, 4), listText);
			AddTextCar(5.1, y0shem - numLine * 0.85, m_lcMain.GetItemText(i, 5), listText);
			AddTextCar(6.6, y0shem - numLine * 0.85, m_lcMain.GetItemText(i, 6), listText);
			AddTextCar(14, y0shem - numLine * 0.85, m_lcMain.GetItemText(i, 7), listText);

			if (numLine < lineTxt) {
				numLine++;
			}
			else
			{
				numLine = 0;
				lineTxt = 17;
				listText++;
			}
		}

		//Б
		if ((m_lcMain.GetItemText(i, 9) != L"") || (m_lcMain.GetItemText(i, 10) != L"") || (m_lcMain.GetItemText(i, 11) != L"") ||
			(m_lcMain.GetItemText(i, 12) != L"") || (m_lcMain.GetItemText(i, 13) != L"") || (m_lcMain.GetItemText(i, 14) != L"") ||
			(m_lcMain.GetItemText(i, 15) != L"") || (m_lcMain.GetItemText(i, 16) != L"") || (m_lcMain.GetItemText(i, 17) != L"") ||
			(m_lcMain.GetItemText(i, 18) != L"") || (m_lcMain.GetItemText(i, 19) != L"") || (m_lcMain.GetItemText(i, 20) != L"")) {

			AddTextCar(0.75, y0shem - numLine * 0.85, L"Б", listText);
			AddTextCar(2, y0shem - numLine * 0.85, m_lcMain.GetItemText(i, 9), listText);//Y = 13.3
			AddTextCar(14, y0shem - numLine * 0.85, m_lcMain.GetItemText(i, 10), listText);
			AddTextCar(15, y0shem - numLine * 0.85, m_lcMain.GetItemText(i, 11), listText);
			AddTextCar(16.8, y0shem - numLine * 0.85, m_lcMain.GetItemText(i, 12), listText);
			AddTextCar(17.9, y0shem - numLine * 0.85, m_lcMain.GetItemText(i, 13), listText);
			AddTextCar(19.2, y0shem - numLine * 0.85, m_lcMain.GetItemText(i, 14), listText);
			AddTextCar(20.2, y0shem - numLine * 0.85, m_lcMain.GetItemText(i, 15), listText);
			AddTextCar(21.5, y0shem - numLine * 0.85, m_lcMain.GetItemText(i, 16), listText);
			AddTextCar(22.8, y0shem - numLine * 0.85, m_lcMain.GetItemText(i, 17), listText);
			AddTextCar(24.1, y0shem - numLine * 0.85, m_lcMain.GetItemText(i, 18), listText);
			AddTextCar(25.4, y0shem - numLine * 0.85, m_lcMain.GetItemText(i, 19), listText);
			AddTextCar(27.3, y0shem - numLine * 0.85, m_lcMain.GetItemText(i, 20), listText);

			if (numLine < lineTxt) {
				numLine++;
			}
			else
			{
				numLine = 0;
				lineTxt = 17;
				listText++;
			}
		}
		//К|М
		if ((m_lcMain.GetItemText(i, 22) != L"") || (m_lcMain.GetItemText(i, 23) != L"") || (m_lcMain.GetItemText(i, 24) != L"") ||
			(m_lcMain.GetItemText(i, 25) != L"") || (m_lcMain.GetItemText(i, 26) != L"") || (m_lcMain.GetItemText(i, 27) != L"") ||
			(m_lcMain.GetItemText(i, 28) != L"")) {

			AddTextCar(0.75, y0shem - numLine * 0.85, m_lcMain.GetItemText(i, 21), listText);
			AddTextCar(2, y0shem - numLine * 0.85, m_lcMain.GetItemText(i, 22), listText);//v12.45
			AddTextCar(14, y0shem - numLine * 0.85, m_lcMain.GetItemText(i, 23), listText);
			AddTextCar(21.5, y0shem - numLine * 0.85, m_lcMain.GetItemText(i, 24), listText);
			AddTextCar(22.8, y0shem - numLine * 0.85, m_lcMain.GetItemText(i, 25), listText);
			AddTextCar(24.1, y0shem - numLine * 0.85, m_lcMain.GetItemText(i, 26), listText);
			AddTextCar(25.4, y0shem - numLine * 0.85, m_lcMain.GetItemText(i, 27), listText);
			AddTextCar(27.3, y0shem - numLine * 0.85, m_lcMain.GetItemText(i, 28), listText);

			if (numLine < lineTxt) {
				numLine++;
			}
			else
			{
				numLine = 0;
				lineTxt = 17;
				listText++;
			}
		}
		//O
		if (m_lcMain.GetItemText(i, 30) != L"") {

			AddTextCar(0.75, y0shem - numLine * 0.85, L"O", listText);
			AddTextCar(2, y0shem - numLine * 0.85, m_lcMain.GetItemText(i, 30), listText);//Y = 10.75

			if (numLine < lineTxt) {
				numLine++;
			}
			else
			{
				numLine = 0;
				lineTxt = 17;
				listText++;
			}
		}
		//Т
		if (m_lcMain.GetItemText(i, 32) != L"") {

			AddTextCar(0.75, y0shem - numLine * 0.85, L"T", listText);
			AddTextCar(2, y0shem - numLine * 0.85, m_lcMain.GetItemText(i, 32), listText);//Y = 9.9

			if (numLine < lineTxt) {
				numLine++;
			}
			else
			{
				numLine = 0;
				lineTxt = 17;
				listText++;
			}
		}
	}
}

/*Кнопка A*/
void CTechCard::OnBnClickedButtona()
{
	// Включить видимости и отключение объектов
	if (ClickOff == 0) {

		ClickOff = 1;

		m_stCodeWorkshop.ShowWindow(TRUE);
		m_stCodePlot.ShowWindow(TRUE);
		m_stNumWorkplase.ShowWindow(TRUE);
		m_stNumOperation.ShowWindow(TRUE);
		m_stNameOperation.ShowWindow(TRUE);
		m_edCodeWorkshop.ShowWindow(TRUE);
		m_edCodePlot.ShowWindow(TRUE);
		m_edNumWorkplase.ShowWindow(TRUE);
		m_edNumOperation.ShowWindow(TRUE);
		m_cbNameOperation.ShowWindow(TRUE);

		m_buB.EnableWindow(FALSE);
		m_buK.EnableWindow(FALSE);
		m_buM.EnableWindow(FALSE);
		m_buO.EnableWindow(FALSE);
		m_buT.EnableWindow(FALSE);
	}
	else
	{
		ClickOff = 0;

		m_stCodeWorkshop.ShowWindow(FALSE);
		m_stCodePlot.ShowWindow(FALSE);
		m_stNumWorkplase.ShowWindow(FALSE);
		m_stNumOperation.ShowWindow(FALSE);
		m_stNameOperation.ShowWindow(FALSE);
		m_edCodeWorkshop.ShowWindow(FALSE);
		m_edCodePlot.ShowWindow(FALSE);
		m_edNumWorkplase.ShowWindow(FALSE);
		m_edNumOperation.ShowWindow(FALSE);
		m_cbNameOperation.ShowWindow(FALSE);

		m_buB.EnableWindow(TRUE);
		m_buK.EnableWindow(TRUE);
		m_buM.EnableWindow(TRUE);
		m_buO.EnableWindow(TRUE);
		m_buT.EnableWindow(TRUE);

		MakeDlgBkColor();
	}
}

/*Кнопка К*/
void CTechCard::OnBnClickedButtonk()
{
	// Включить видимости и отключение объектов
	if (ClickOff == 0) {

		ClickOff = 1;

		m_stNameDetail.ShowWindow(TRUE);
		m_stDesignationCode.ShowWindow(TRUE);
		m_stDivisionDesignation.ShowWindow(TRUE);
		m_stUnitCode.ShowWindow(TRUE);
		m_stAmountData.ShowWindow(TRUE);
		m_stConsumptionRate.ShowWindow(TRUE);
		m_edDesignationCode.ShowWindow(TRUE);
		m_edDivisionDesignation.ShowWindow(TRUE);
		m_edUnitCode.ShowWindow(TRUE);
		m_edAmountData.ShowWindow(TRUE);
		m_edConsumptionRate.ShowWindow(TRUE);
		m_cbNameDetail.ShowWindow(TRUE);

		m_buB.EnableWindow(FALSE);
		m_buM.EnableWindow(FALSE);
		m_buA.EnableWindow(FALSE);
		m_buO.EnableWindow(FALSE);
		m_buT.EnableWindow(FALSE);
	}
	else
	{
		ClickOff = 0;

		m_stNameDetail.ShowWindow(FALSE);
		m_stDesignationCode.ShowWindow(FALSE);
		m_stDivisionDesignation.ShowWindow(FALSE);
		m_stUnitCode.ShowWindow(FALSE);
		m_stAmountData.ShowWindow(FALSE);
		m_stConsumptionRate.ShowWindow(FALSE);
		m_edDesignationCode.ShowWindow(FALSE);
		m_edDivisionDesignation.ShowWindow(FALSE);
		m_edUnitCode.ShowWindow(FALSE);
		m_edAmountData.ShowWindow(FALSE);
		m_edConsumptionRate.ShowWindow(FALSE);
		m_cbNameDetail.ShowWindow(FALSE);

		m_buB.EnableWindow(TRUE);
		m_buM.EnableWindow(TRUE);
		m_buA.EnableWindow(TRUE);
		m_buO.EnableWindow(TRUE);
		m_buT.EnableWindow(TRUE);

		MakeDlgBkColor();
	}
}

/*Кнопка О*/
void CTechCard::OnBnClickedButtono()
{
	if (ClickOff == 0) {

		ClickOff = 1;

		m_listO1.ShowWindow(TRUE);
		m_listO2.ShowWindow(TRUE);
		m_listO3.ShowWindow(TRUE);
		m_listO4.ShowWindow(TRUE);
		m_butOBut.ShowWindow(TRUE);
		m_edOEd.ShowWindow(TRUE);
		m_butO2.ShowWindow(TRUE);

		m_buB.EnableWindow(FALSE);
		m_buK.EnableWindow(FALSE);
		m_buM.EnableWindow(FALSE);
		m_buA.EnableWindow(FALSE);
		m_buT.EnableWindow(FALSE);

	}
	else
	{
		ClickOff = 0;

		m_listO1.ShowWindow(FALSE);
		m_listO2.ShowWindow(FALSE);
		m_listO3.ShowWindow(FALSE);
		m_listO4.ShowWindow(FALSE);
		m_butOBut.ShowWindow(FALSE);
		m_edOEd.ShowWindow(FALSE);
		m_butO2.ShowWindow(FALSE);

		m_buB.EnableWindow(TRUE);
		m_buK.EnableWindow(TRUE);
		m_buM.EnableWindow(TRUE);
		m_buA.EnableWindow(TRUE);
		m_buT.EnableWindow(TRUE);

		MakeDlgBkColor();
	}

}

/*Кнопка Б*/
void CTechCard::OnBnClickedButtonb()
{
	if (ClickOff == 0) {

		ClickOff = 1;

		m_stCodeNameEquipment.ShowWindow(TRUE);
		m_stDagreeMech.ShowWindow(TRUE);
		m_stCodProf.ShowWindow(TRUE);
		m_stRank.ShowWindow(TRUE);
		m_stLaborCode.ShowWindow(TRUE);
		m_stNumPerfomens.ShowWindow(TRUE);
		m_stNumManuf.ShowWindow(TRUE);
		m_stStrUnit.ShowWindow(TRUE);
		m_stBatchSize.ShowWindow(TRUE);
		m_stPieseTime.ShowWindow(TRUE);
		m_stNormFinalTime.ShowWindow(TRUE);
		m_stNormTime.ShowWindow(TRUE);
		m_edCodeNameEquipment.ShowWindow(TRUE);
		m_edDagreeMech.ShowWindow(TRUE);
		m_edCodProf.ShowWindow(TRUE);
		m_edRank.ShowWindow(TRUE);
		m_edLaborCode.ShowWindow(TRUE);
		m_edNumPerfomens.ShowWindow(TRUE);
		m_edNumManuf.ShowWindow(TRUE);
		m_edStrUnit.ShowWindow(TRUE);
		m_edBatchSize.ShowWindow(TRUE);
		m_edPieseTime.ShowWindow(TRUE);
		m_edNormFinalTime.ShowWindow(TRUE);
		m_edNormTime.ShowWindow(TRUE);

		m_buA.EnableWindow(FALSE);
		m_buK.EnableWindow(FALSE);
		m_buM.EnableWindow(FALSE);
		m_buO.EnableWindow(FALSE);
		m_buT.EnableWindow(FALSE);
	}
	else
	{
		ClickOff = 0;

		m_stCodeNameEquipment.ShowWindow(FALSE);
		m_stDagreeMech.ShowWindow(FALSE);
		m_stCodProf.ShowWindow(FALSE);
		m_stRank.ShowWindow(FALSE);
		m_stLaborCode.ShowWindow(FALSE);
		m_stNumPerfomens.ShowWindow(FALSE);
		m_stNumManuf.ShowWindow(FALSE);
		m_stStrUnit.ShowWindow(FALSE);
		m_stBatchSize.ShowWindow(FALSE);
		m_stPieseTime.ShowWindow(FALSE);
		m_stNormFinalTime.ShowWindow(FALSE);
		m_stNormTime.ShowWindow(FALSE);
		m_edCodeNameEquipment.ShowWindow(FALSE);
		m_edDagreeMech.ShowWindow(FALSE);
		m_edCodProf.ShowWindow(FALSE);
		m_edRank.ShowWindow(FALSE);
		m_edLaborCode.ShowWindow(FALSE);
		m_edNumPerfomens.ShowWindow(FALSE);
		m_edNumManuf.ShowWindow(FALSE);
		m_edStrUnit.ShowWindow(FALSE);
		m_edBatchSize.ShowWindow(FALSE);
		m_edPieseTime.ShowWindow(FALSE);
		m_edNormFinalTime.ShowWindow(FALSE);
		m_edNormTime.ShowWindow(FALSE);

		m_buA.EnableWindow(TRUE);
		m_buK.EnableWindow(TRUE);
		m_buM.EnableWindow(TRUE);
		m_buO.EnableWindow(TRUE);
		m_buT.EnableWindow(TRUE);

		MakeDlgBkColor();
	}
}

/*Кнопка М*/
void CTechCard::OnBnClickedButtonm()
{
	// Включить видимости и отключение объектов
	if (ClickOff == 0) {

		ClickOff = 1;

		m_stNameDetail.ShowWindow(TRUE);
		m_stDesignationCode.ShowWindow(TRUE);
		m_stDivisionDesignation.ShowWindow(TRUE);
		m_stUnitCode.ShowWindow(TRUE);
		m_stAmountData.ShowWindow(TRUE);
		m_stConsumptionRate.ShowWindow(TRUE);
		m_edNameMaterial.ShowWindow(TRUE);
		m_edDesignationCode.ShowWindow(TRUE);
		m_edDivisionDesignation.ShowWindow(TRUE);
		m_edUnitCode.ShowWindow(TRUE);
		m_edAmountData.ShowWindow(TRUE);
		m_edConsumptionRate.ShowWindow(TRUE);

		m_buB.EnableWindow(FALSE);
		m_buK.EnableWindow(FALSE);
		m_buA.EnableWindow(FALSE);
		m_buO.EnableWindow(FALSE);
		m_buT.EnableWindow(FALSE);
	}
	else
	{
		ClickOff = 0;

		m_stNameDetail.ShowWindow(FALSE);
		m_stDesignationCode.ShowWindow(FALSE);
		m_stDivisionDesignation.ShowWindow(FALSE);
		m_stUnitCode.ShowWindow(FALSE);
		m_stAmountData.ShowWindow(FALSE);
		m_stConsumptionRate.ShowWindow(FALSE);
		m_edNameMaterial.ShowWindow(FALSE);
		m_edDesignationCode.ShowWindow(FALSE);
		m_edDivisionDesignation.ShowWindow(FALSE);
		m_edUnitCode.ShowWindow(FALSE);
		m_edAmountData.ShowWindow(FALSE);
		m_edConsumptionRate.ShowWindow(FALSE);

		m_buB.EnableWindow(TRUE);
		m_buK.EnableWindow(TRUE);
		m_buA.EnableWindow(TRUE);
		m_buO.EnableWindow(TRUE);
		m_buT.EnableWindow(TRUE);

		MakeDlgBkColor();
	}
}

/*Кнопка Т*/
void CTechCard::OnBnClickedButtont()
{
	// Включить видимости и отключение объектов
	if (ClickOff == 0) {

		ClickOff = 1;

		m_stAccessoriesAuxiliaryTool.ShowWindow(TRUE);
		m_edAccessoriesAuxiliaryTool.ShowWindow(TRUE);

		m_buB.EnableWindow(FALSE);
		m_buK.EnableWindow(FALSE);
		m_buM.EnableWindow(FALSE);
		m_buO.EnableWindow(FALSE);
		m_buA.EnableWindow(FALSE);
	}
	else
	{
		ClickOff = 0;

		m_stAccessoriesAuxiliaryTool.ShowWindow(FALSE);
		m_edAccessoriesAuxiliaryTool.ShowWindow(FALSE);

		m_buB.EnableWindow(TRUE);
		m_buK.EnableWindow(TRUE);
		m_buM.EnableWindow(TRUE);
		m_buO.EnableWindow(TRUE);
		m_buA.EnableWindow(TRUE);

		MakeDlgBkColor();
	}
}

/*Открыть и получить даынне из базы данных*/
void CTechCard::openDb()
{
	CString path;

	TCHAR buffer[MAX_PATH];
	DWORD size = GetCurrentDirectory(sizeof(buffer), buffer);

	path = buffer;
	path += L"\\DataBase.mdb";
	
	CDatabase database;
	CString SqlString;
	CString SqlString2;
	CString SqlString3;
	CString SqlString4;
	CString SqlString5;
	CString strName;
	CString sDriver = L"MICROSOFT ACCESS DRIVER (*.mdb)";
	CString sDsn;
	CString sFile = path;
	sDsn.Format(L"ODBC;DRIVER={%s};DSN='';DBQ=%s", sDriver, sFile);
	database.Open(NULL, false, false, sDsn);
	CRecordset recset(&database);

	SqlString = L"SELECT Name " "FROM NameАction";
	recset.Open(CRecordset::forwardOnly, SqlString, CRecordset::readOnly);
	int iRec = 0;
	while (!recset.IsEOF()) {
		recset.GetFieldValue(L"Name", strName);

		iRec = m_listO1.InsertItem(0, strName);

		recset.MoveNext();
	}
	recset.Close();
	database.Close();

	sDsn.Format(L"ODBC;DRIVER={%s};DSN='';DBQ=%s", sDriver, sFile);
	database.Open(NULL, false, false, sDsn);
	CRecordset recset2(&database);
	SqlString2 = L"SELECT Name " "FROM NameDetailProduct";
	recset2.Open(CRecordset::forwardOnly, SqlString2, CRecordset::readOnly);

	while (!recset2.IsEOF()) {
		recset2.GetFieldValue(L"Name", strName);

		iRec = m_listO2.InsertItem(0, strName);

		recset2.MoveNext();
	}
	recset.Close();
	database.Close();

	sDsn.Format(L"ODBC;DRIVER={%s};DSN='';DBQ=%s", sDriver, sFile);
	database.Open(NULL, false, false, sDsn);
	CRecordset recset3(&database);
	SqlString3 = L"SELECT ID, Name " "FROM VidDetailProduct";
	recset3.Open(CRecordset::forwardOnly, SqlString3, CRecordset::readOnly);

	while (!recset3.IsEOF()) {
		recset3.GetFieldValue(L"Name", strName);

		iRec = m_listO3.InsertItem(0, strName);

		recset3.MoveNext();
	}
	recset.Close();
	database.Close();

	sDsn.Format(L"ODBC;DRIVER={%s};DSN='';DBQ=%s", sDriver, sFile);
	database.Open(NULL, false, false, sDsn);
	CRecordset recset4(&database);
	SqlString4 = L"SELECT Name " "FROM AdditionalInformation";
	recset4.Open(CRecordset::forwardOnly, SqlString4, CRecordset::readOnly);

	while (!recset4.IsEOF()) {
		recset4.GetFieldValue(L"Name", strName);

		iRec = m_listO4.InsertItem(0, strName);

		recset4.MoveNext();
	}
	recset.Close();
	database.Close();

	sDsn.Format(L"ODBC;DRIVER={%s};DSN='';DBQ=%s", sDriver, sFile);
	database.Open(NULL, false, false, sDsn);
	CRecordset recset5(&database);
	SqlString5 = L"SELECT Name " "FROM NameOperation";
	recset5.Open(CRecordset::forwardOnly, SqlString5, CRecordset::readOnly);

	while (!recset5.IsEOF()) {
		recset5.GetFieldValue(L"Name", strName);

		m_cbNameOperation.AddString(strName);

		recset5.MoveNext();
	}
	recset.Close();
	database.Close();
}

void CTechCard::MakeDlgBkColor()
{
	CRect rect;
	GetClientRect(&rect);
	CDC* pDC = this->GetDC();
	HBRUSH  hBrush;
	hBrush = CreateSolidBrush(RGB(255, 246, 158));
	pDC->SelectObject(hBrush);
	pDC->Rectangle(rect.left, rect.top + 40, rect.right - 451, rect.bottom - 438);
}

/*Кнопка Доп. информация МК*/
void CTechCard::OnBnClickedButtondopinf()
{
	CDLGDopInf openDialog;
	openDialog.DoModal();
}

/*Кнопка Очистить поля от записей*/
void CTechCard::OnBnClickedButtonclean()
{
	m_edCodeWorkshop.SetSel(0, -1);
	m_edCodeWorkshop.Clear();
	m_edCodePlot.SetSel(0, -1);
	m_edCodePlot.Clear();
	m_edNumWorkplase.SetSel(0, -1);
	m_edNumWorkplase.Clear();
	m_edNumOperation.SetSel(0, -1);
	m_edNumOperation.Clear();
	m_cbNameOperation.SetWindowTextW(L"");
	m_edCodeNameEquipment.SetSel(0, -1);
	m_edCodeNameEquipment.Clear();
	m_edDagreeMech.SetSel(0, -1);
	m_edDagreeMech.Clear();
	m_edCodProf.SetSel(0, -1);
	m_edCodProf.Clear();
	m_edRank.SetSel(0, -1);
	m_edRank.Clear();
	m_edLaborCode.SetSel(0, -1);
	m_edLaborCode.Clear();
	m_edNumPerfomens.SetSel(0, -1);
	m_edNumPerfomens.Clear();
	m_edNumManuf.SetSel(0, -1);
	m_edNumManuf.Clear();
	m_edStrUnit.SetSel(0, -1);
	m_edStrUnit.Clear();
	m_edBatchSize.SetSel(0, -1);
	m_edBatchSize.Clear();
	m_edPieseTime.SetSel(0, -1);
	m_edPieseTime.Clear();
	m_edNormFinalTime.SetSel(0, -1);
	m_edNormFinalTime.Clear();
	m_edNormTime.SetSel(0, -1);
	m_edNormTime.Clear();
	m_edNameMaterial.SetSel(0, -1);
	m_edNameMaterial.Clear();
	m_edDesignationCode.SetSel(0, -1);
	m_edDesignationCode.Clear();
	m_edDivisionDesignation.SetSel(0, -1);
	m_edDivisionDesignation.Clear();
	m_edUnitCode.SetSel(0, -1);
	m_edUnitCode.Clear();
	m_edAmountData.SetSel(0, -1);
	m_edAmountData.Clear();
	m_edConsumptionRate.SetSel(0, -1);
	m_edConsumptionRate.Clear();
	//
	m_cbNameDetail.SetWindowTextW(L"");
	//m_cbNameDetail.Clear();
	//
	m_edOEd.SetSel(0, -1);
	m_edOEd.Clear();
	m_edAccessoriesAuxiliaryTool.SetSel(0, -1);
	m_edAccessoriesAuxiliaryTool.Clear();
}

/*Кнопка детали сборки*/
void CTechCard::OnBnClickedButtonobut()
{
	CDlgDetMake openDialog;
	int	result = openDialog.DoModal();
	if (result == IDOK) {
		CprTextCardApp* pApp = (CprTextCardApp*)AfxGetApp();
		CString text;
		m_edOEd.GetWindowTextW(text);
		text += L" " + pApp->m_edDeatil;
		m_edOEd.SetWindowTextW(text);
	}
}

/*Кнопка применить*/
void CTechCard::OnBnClickedButtono2()
{
	// GetFirstSelectedItemposition
	POSITION pos = m_listO1.GetFirstSelectedItemPosition();
	if (pos != NULL) {
		CString text;
		m_edOEd.GetWindowTextW(text);
		int nItem = m_listO1.GetNextSelectedItem(pos);

		text = text + L" " + m_listO1.GetItemText(nItem, 0);

		m_edOEd.SetWindowTextW(text);
		m_listO1.SetItemState(nItem, 0, LVIS_SELECTED);
	}
	POSITION pos2 = m_listO2.GetFirstSelectedItemPosition();
	if (pos2 != NULL) {
		CString text;
		m_edOEd.GetWindowTextW(text);
		int nItem = m_listO2.GetNextSelectedItem(pos2);

		text = text + L" " + m_listO2.GetItemText(nItem, 0);

		m_edOEd.SetWindowTextW(text);
		m_listO2.SetItemState(nItem, 0, LVIS_SELECTED);
	}
	POSITION pos3 = m_listO3.GetFirstSelectedItemPosition();
	if (pos3 != NULL) {
		CString text;
		m_edOEd.GetWindowTextW(text);
		int nItem = m_listO3.GetNextSelectedItem(pos3);

		text = text + L" " + m_listO3.GetItemText(nItem, 0);

		m_edOEd.SetWindowTextW(text);
		m_listO3.SetItemState(nItem, 0, LVIS_SELECTED);
	}
	POSITION pos4 = m_listO4.GetFirstSelectedItemPosition();
	if (pos4 != NULL) {
		CString text;
		m_edOEd.GetWindowTextW(text);
		int nItem = m_listO4.GetNextSelectedItem(pos4);

		text = text + L" " + m_listO4.GetItemText(nItem, 0);

		m_edOEd.SetWindowTextW(text);
		m_listO4.SetItemState(nItem, 0, LVIS_SELECTED);
	}

}

/*Кнопка запись в таблицу*/
void CTechCard::OnBnClickedButtonaddtb()
{
	if (VarBut == 0) {
		int nItem;
		int nCount = m_lcMain.GetItemCount();
		CString str,
			Column1, Column2, Column3, Column4, Column5,
			Column6, Column7, Column8, Column9, Column10,
			Column11, Column12, Column13, Column14, Column15,
			Column16, Column17, Column18, Column19, Column20,
			Column21, Column22, Column23, Column24, Column25,
			Column26, Column27, Column28, Column29, Column30,
			Column31, Column32;

		str.Format(L"%d", nCount + 1);
		if (nCount < 10) {
			str = '0' + str;
		}

		//А
		m_edCodeWorkshop.GetWindowTextW(Column2);
		m_edCodePlot.GetWindowTextW(Column3);
		m_edNumWorkplase.GetWindowTextW(Column4);
		m_edNumOperation.GetWindowTextW(Column5);
		m_cbNameOperation.GetWindowTextW(Column6);
		//Б
		m_edCodeNameEquipment.GetWindowTextW(Column9);
		m_edDagreeMech.GetWindowTextW(Column10);
		m_edCodProf.GetWindowTextW(Column11);
		m_edRank.GetWindowTextW(Column12);
		m_edLaborCode.GetWindowTextW(Column13);
		m_edNumPerfomens.GetWindowTextW(Column14);
		m_edNumManuf.GetWindowTextW(Column15);
		m_edStrUnit.GetWindowTextW(Column16);
		m_edBatchSize.GetWindowTextW(Column17);
		m_edPieseTime.GetWindowTextW(Column18);
		m_edNormFinalTime.GetWindowTextW(Column19);
		m_edNormTime.GetWindowTextW(Column20);

		//М/K	
		m_edNameMaterial.GetWindowTextW(Column22);//М
		m_cbNameDetail.GetWindowTextW(Column1);//К
		m_edDesignationCode.GetWindowTextW(Column23);
		m_edDivisionDesignation.GetWindowTextW(Column24);
		m_edUnitCode.GetWindowTextW(Column25);
		m_edAmountData.GetWindowTextW(Column27);
		m_edConsumptionRate.GetWindowTextW(Column28);
		m_cbNameDetail.GetWindowTextW(Column29);
		//О
		m_edOEd.GetWindowTextW(Column30);
		//Т
		m_edAccessoriesAuxiliaryTool.GetWindowTextW(Column32);
		if ((Column1 == L"") && (Column22 != L"")) {
		}
		else
		{
			//ID
			nItem = m_lcMain.InsertItem(0, str);
			//А
			m_lcMain.SetItemText(nItem, 1, L"А");
			m_lcMain.SetItemText(nItem, 2, Column2);
			m_lcMain.SetItemText(nItem, 3, Column3);
			m_lcMain.SetItemText(nItem, 4, Column4);
			m_lcMain.SetItemText(nItem, 5, Column5);
			m_lcMain.SetItemText(nItem, 6, Column6);
			m_lcMain.SetItemText(nItem, 7, L"ИОТ №102.23.423"); //Column7 ДОБАВИТЬ EDIT
																//Б
			m_lcMain.SetItemText(nItem, 8, L"Б");
			m_lcMain.SetItemText(nItem, 9, Column9);
			m_lcMain.SetItemText(nItem, 10, Column10);
			m_lcMain.SetItemText(nItem, 11, Column11);
			m_lcMain.SetItemText(nItem, 12, Column12);
			m_lcMain.SetItemText(nItem, 13, Column13);
			m_lcMain.SetItemText(nItem, 14, Column14);
			m_lcMain.SetItemText(nItem, 15, Column15);
			m_lcMain.SetItemText(nItem, 16, Column16);
			m_lcMain.SetItemText(nItem, 17, Column17);
			m_lcMain.SetItemText(nItem, 18, Column18);
			m_lcMain.SetItemText(nItem, 19, Column19);
			m_lcMain.SetItemText(nItem, 20, Column20);
			//М/К
			m_lcMain.SetItemText(nItem, 21, L"K");
			m_lcMain.SetItemText(nItem, 22, Column1);
			m_lcMain.SetItemText(nItem, 23, Column23);
			m_lcMain.SetItemText(nItem, 24, Column24);
			m_lcMain.SetItemText(nItem, 25, Column25);
			m_lcMain.SetItemText(nItem, 26, L"1"); //Column7 ДОБАВИТЬ EDIT
			m_lcMain.SetItemText(nItem, 27, Column27);
			m_lcMain.SetItemText(nItem, 28, Column28);
			//O
			m_lcMain.SetItemText(nItem, 29, L"O");
			m_lcMain.SetItemText(nItem, 30, Column30);
			//T
			m_lcMain.SetItemText(nItem, 31, L"Т");
			m_lcMain.SetItemText(nItem, 32, Column32);
		}
		if (Column22 != L"") {
			//ID
			nItem = m_lcMain.InsertItem(0, str);
			//А
			m_lcMain.SetItemText(nItem, 1, L"А");
			m_lcMain.SetItemText(nItem, 2, Column2);
			m_lcMain.SetItemText(nItem, 3, Column3);
			m_lcMain.SetItemText(nItem, 4, Column4);
			m_lcMain.SetItemText(nItem, 5, Column5);
			m_lcMain.SetItemText(nItem, 6, Column6);
			m_lcMain.SetItemText(nItem, 7, L"ИОТ №102.23.423"); //Column7 ДОБАВИТЬ EDIT
																//Б
			m_lcMain.SetItemText(nItem, 8, L"Б");
			m_lcMain.SetItemText(nItem, 9, Column9);
			m_lcMain.SetItemText(nItem, 10, Column10);
			m_lcMain.SetItemText(nItem, 11, Column11);
			m_lcMain.SetItemText(nItem, 12, Column12);
			m_lcMain.SetItemText(nItem, 13, Column13);
			m_lcMain.SetItemText(nItem, 14, Column14);
			m_lcMain.SetItemText(nItem, 15, Column15);
			m_lcMain.SetItemText(nItem, 16, Column16);
			m_lcMain.SetItemText(nItem, 17, Column17);
			m_lcMain.SetItemText(nItem, 18, Column18);
			m_lcMain.SetItemText(nItem, 19, Column19);
			m_lcMain.SetItemText(nItem, 20, Column20);
			//М/К
			m_lcMain.SetItemText(nItem, 21, L"M");
			m_lcMain.SetItemText(nItem, 22, Column22);
			m_lcMain.SetItemText(nItem, 23, Column23);
			m_lcMain.SetItemText(nItem, 24, Column24);
			m_lcMain.SetItemText(nItem, 25, Column25);
			m_lcMain.SetItemText(nItem, 26, L"1"); //Column7 ДОБАВИТЬ EDIT
			m_lcMain.SetItemText(nItem, 27, Column27);
			m_lcMain.SetItemText(nItem, 28, Column28);
			//O
			m_lcMain.SetItemText(nItem, 29, L"O");
			m_lcMain.SetItemText(nItem, 30, Column30);
			//T
			m_lcMain.SetItemText(nItem, 31, L"Т");
			m_lcMain.SetItemText(nItem, 32, Column32);
		}
	}
	else
	{
		int nItem;
		int nCount = m_lcMain.GetItemCount();
		CString Column1, Column2, Column3, Column4, Column5,
			Column6, Column7, Column8, Column9, Column10,
			Column11, Column12, Column13, Column14, Column15,
			Column16, Column17, Column18, Column19, Column20,
			Column21, Column22, Column23, Column24, Column25,
			Column26, Column27, Column28, Column29, Column30,
			Column31, Column32;

		//А
		m_edCodeWorkshop.GetWindowTextW(Column2);
		m_edCodePlot.GetWindowTextW(Column3);
		m_edNumWorkplase.GetWindowTextW(Column4);
		m_edNumOperation.GetWindowTextW(Column5);
		m_cbNameOperation.GetWindowTextW(Column6);
		//Б
		m_edCodeNameEquipment.GetWindowTextW(Column9);
		m_edDagreeMech.GetWindowTextW(Column10);
		m_edCodProf.GetWindowTextW(Column11);
		m_edRank.GetWindowTextW(Column12);
		m_edLaborCode.GetWindowTextW(Column13);
		m_edNumPerfomens.GetWindowTextW(Column14);
		m_edNumManuf.GetWindowTextW(Column15);
		m_edStrUnit.GetWindowTextW(Column16);
		m_edBatchSize.GetWindowTextW(Column17);
		m_edPieseTime.GetWindowTextW(Column18);
		m_edNormFinalTime.GetWindowTextW(Column19);
		m_edNormTime.GetWindowTextW(Column20);
		//М/K
		m_edNameMaterial.GetWindowTextW(Column22);//M
		m_cbNameDetail.GetWindowTextW(Column1);//К
		m_edDesignationCode.GetWindowTextW(Column23);
		m_edDivisionDesignation.GetWindowTextW(Column24);
		m_edUnitCode.GetWindowTextW(Column25);
		m_edAmountData.GetWindowTextW(Column27);
		m_edConsumptionRate.GetWindowTextW(Column28);
		m_cbNameDetail.GetWindowTextW(Column29);
		//О
		m_edOEd.GetWindowTextW(Column30);
		//Т
		m_edAccessoriesAuxiliaryTool.GetWindowTextW(Column32);

		nItem = ListItem;

		//А
		m_lcMain.SetItemText(nItem, 1, L"А");
		m_lcMain.SetItemText(nItem, 2, Column2);
		m_lcMain.SetItemText(nItem, 3, Column3);
		m_lcMain.SetItemText(nItem, 4, Column4);
		m_lcMain.SetItemText(nItem, 5, Column5);
		m_lcMain.SetItemText(nItem, 6, Column6);
		m_lcMain.SetItemText(nItem, 7, L"ИОТ №102.23.423"); //Column7 ДОБАВИТЬ EDIT
															//Б
		m_lcMain.SetItemText(nItem, 8, L"Б");
		m_lcMain.SetItemText(nItem, 9, Column9);
		m_lcMain.SetItemText(nItem, 10, Column10);
		m_lcMain.SetItemText(nItem, 11, Column11);
		m_lcMain.SetItemText(nItem, 12, Column12);
		m_lcMain.SetItemText(nItem, 13, Column13);
		m_lcMain.SetItemText(nItem, 14, Column14);
		m_lcMain.SetItemText(nItem, 15, Column15);
		m_lcMain.SetItemText(nItem, 16, Column16);
		m_lcMain.SetItemText(nItem, 17, Column17);
		m_lcMain.SetItemText(nItem, 18, Column18);
		m_lcMain.SetItemText(nItem, 19, Column19);
		m_lcMain.SetItemText(nItem, 20, Column20);
		//М/К
		m_lcMain.SetItemText(nItem, 21, L"K");
		m_lcMain.SetItemText(nItem, 22, Column1);//K
		m_lcMain.SetItemText(nItem, 23, Column23);
		m_lcMain.SetItemText(nItem, 24, Column24);
		m_lcMain.SetItemText(nItem, 25, Column25);
		m_lcMain.SetItemText(nItem, 26, L"1"); //Column7 ДОБАВИТЬ EDIT
		m_lcMain.SetItemText(nItem, 27, Column27);
		m_lcMain.SetItemText(nItem, 28, Column28);
		//O
		m_lcMain.SetItemText(nItem, 29, L"O");
		m_lcMain.SetItemText(nItem, 30, Column31);
		//T
		m_lcMain.SetItemText(nItem, 31, L"Т");
		m_lcMain.SetItemText(nItem, 32, Column32);
		VarBut = 0;
	}
}

/*Кнопка изменения в таблице*/
void CTechCard::OnBnClickedButtonchange()
{
	VarBut = 1;
	m_cbNameOperation.SetEditSel(0, -1);
	m_cbNameOperation.Clear();
	m_cbNameDetail.SetEditSel(0, -1);
	m_cbNameDetail.Clear();

	POSITION pos = m_lcMain.GetFirstSelectedItemPosition();
	int nItem = m_lcMain.GetNextSelectedItem(pos);

	m_cbNameOperation.SetWindowTextW(m_lcMain.GetItemText(nItem, 6));
	m_cbNameDetail.SetWindowTextW(m_lcMain.GetItemText(nItem, 22));

	ListItem = nItem;
}

/*Кнопка удаление из таблицы*/
void CTechCard::OnBnClickedButtondel()
{
	// удаляем объект из 1 табл
	POSITION pos = m_lcMain.GetFirstSelectedItemPosition();
	int nItem = m_lcMain.GetNextSelectedItem(pos);
	m_lcMain.DeleteItem(nItem);
}

/*Записаный текст в полях*/
void CTechCard::AllStrText()
{
	//A
	m_edCodeWorkshop.SetWindowTextW(L"001");
	m_edCodePlot.SetWindowTextW(L"001");
	m_edNumWorkplase.SetWindowTextW(L"010");
	m_edNumOperation.SetWindowTextW(L"0001");

	m_cbNameOperation.SetWindowTextW(L"8800 Сборка");
	//Б
	m_edCodeNameEquipment.SetWindowTextW(L"АБВГ.ХХХХХХ.ХХХ Сборочно монтажный стол");
	m_edDagreeMech.SetWindowTextW(L"1");
	m_edCodProf.SetWindowTextW(L"18116");
	m_edRank.SetWindowTextW(L"311");
	m_edLaborCode.SetWindowTextW(L"1");
	m_edNumPerfomens.SetWindowTextW(L"1");
	m_edNumManuf.SetWindowTextW(L"1");
	m_edStrUnit.SetWindowTextW(L"100");
	m_edBatchSize.SetWindowTextW(L"166");
	m_edPieseTime.SetWindowTextW(L"100");
	m_edNormFinalTime.SetWindowTextW(L"12");
	m_edNormTime.SetWindowTextW(L"000.2");
	//М К
	m_edNameMaterial.SetWindowTextW(L"Смазка для деталей");
	m_edDesignationCode.SetWindowTextW(L"АБВГ.ХХХХХХ.ХХХ");
	m_edDivisionDesignation.SetWindowTextW(L"1");
	m_edUnitCode.SetWindowTextW(L"ХХХ");

	m_edAmountData.SetWindowTextW(L"-");
	m_edConsumptionRate.SetWindowTextW(L"-");
	m_cbNameDetail.SetWindowTextW(L"Деталь1");
	//О
	m_edOEd.SetWindowTextW(L"1. Собрать деталь ручка (1) согласно чертежу");
	//Т
	m_edAccessoriesAuxiliaryTool.SetWindowTextW(L"АБВГ.ХХХ.ХХХ.ХХХ Отвертки с прямым шлицем");


	/*Ограничения на количество символом при вводе*/
	//A
	m_edCodeWorkshop.LimitText(4);
	m_edCodePlot.LimitText(4);
	m_edNumWorkplase.LimitText(4);
	m_edNumOperation.LimitText(5);

	m_cbNameOperation.LimitText(29);
	//Б
	m_edCodeNameEquipment.LimitText(46);
	m_edDagreeMech.LimitText(4);
	m_edCodProf.LimitText(7);
	m_edRank.LimitText(4);
	m_edLaborCode.LimitText(5);
	m_edNumPerfomens.LimitText(4);
	m_edNumManuf.LimitText(5);
	m_edStrUnit.LimitText(5);
	m_edBatchSize.LimitText(5);
	m_edPieseTime.LimitText(5);
	m_edNormFinalTime.LimitText(7);
	m_edNormTime.LimitText(8);
	//М К
	m_edNameMaterial.LimitText(46);
	m_edDesignationCode.LimitText(29);
	m_edDivisionDesignation.LimitText(5);
	m_edUnitCode.LimitText(4);

	m_edAmountData.LimitText(5);
	m_edConsumptionRate.LimitText(17);
	m_cbNameDetail.LimitText(46);
	//О
	m_edOEd.LimitText(46);
	//Т
	m_edAccessoriesAuxiliaryTool.LimitText(46);
}