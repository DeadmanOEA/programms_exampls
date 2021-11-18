// MashCard.cpp: файл реализации
//

#include "stdafx.h"
#include "prTextCard.h"
#include "MashCard.h"
#include "TechCard.h"
#include "afxdialogex.h"
#include "odbcinst.h"
#include "afxdb.h"

// диалоговое окно CMashCard

IMPLEMENT_DYNAMIC(CMashCard, CDialog)

CMashCard::CMashCard(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_MashCard, pParent)
{

}

CMashCard::~CMashCard()
{
}

void CMashCard::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTSaveMake, m_butSaveMake);
	DDX_Control(pDX, IDC_BUTOpenSave, m_butOpenSave);
	DDX_Control(pDX, IDC_BUTLoadSb, m_butLoadSb);
	DDX_Control(pDX, IDC_BUTTONCHANGEDLG, m_butChangeDlg);

	DDX_Control(pDX, IDC_LISTSb, m_listCtrl);
	DDX_Control(pDX, IDC_LISTSh, m_listCtrl2);

	DDX_Control(pDX, IDC_BUTAdd1, m_butAdd1);
	DDX_Control(pDX, IDC_BUTChange1, m_butChange1);
	DDX_Control(pDX, IDC_BUTDel1, m_butDel1);

	DDX_Control(pDX, IDC_BUTAdd2, m_butAdd2);
	DDX_Control(pDX, IDC_BUTChange2, m_butChange2);
	DDX_Control(pDX, IDC_BUTDel2, m_butDel2);

	DDX_Control(pDX, IDC_RADIOVert, m_rbVer);
	DDX_Control(pDX, IDC_RADIOGor, m_rbGor);
	DDX_Control(pDX, IDC_COMBO1, m_cbFormList);

	DDX_Control(pDX, IDC_NameF, m_stNameF);
	DDX_Control(pDX, IDC_PosF, m_PosF);
	DDX_Control(pDX, IDC_NumF, m_NumF);
	DDX_Control(pDX, IDC_View, m_View);
	DDX_Control(pDX, IDC_PutOn, m_PutOn);
	DDX_Control(pDX, IDC_AddMark, m_AddMark);
	DDX_Control(pDX, IDC_stEdSbName, m_stEdSbName);

	DDX_Control(pDX, IDC_edNameF, m_edNameF);
	DDX_Control(pDX, IDC_edPosF, m_edPosF);
	DDX_Control(pDX, IDC_edNumF, m_edNumF);

	DDX_Control(pDX, IDC_cbView, m_cbView);
	DDX_Control(pDX, IDC_cbPutOn, m_cbPutOn);
	DDX_Control(pDX, IDC_cbNameF, m_cbNameF);
	DDX_Control(pDX, IDC_cbPosF, m_cbPosF);
	DDX_Control(pDX, IDC_edSbName, m_edSbName);
	DDX_Control(pDX, IDC_cbMark, m_cbMark);

	DDX_Control(pDX, IDC_AddNote, m_AddNote);
	DDX_Control(pDX, IDC_butBack, m_butBack);

	faq = false;
	DDX_Control(pDX, IDC_AddNote2, m_butAddNote2);
	DDX_Control(pDX, IDC_butBack2, m_butBack2);
}

BEGIN_MESSAGE_MAP(CMashCard, CDialog)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BUTOpenSave, &CMashCard::OnBnClickedButopensave)
	ON_BN_CLICKED(IDC_BUTSaveMake, &CMashCard::OnBnClickedButsavemake)
	ON_BN_CLICKED(IDC_BUTLoadSb, &CMashCard::OnBnClickedButloadsb)
	ON_BN_CLICKED(IDOK, &CMashCard::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTAdd1, &CMashCard::OnBnClickedButadd1)
	ON_BN_CLICKED(IDC_BUTAdd2, &CMashCard::OnBnClickedButadd2)
	ON_BN_CLICKED(IDC_BUTChange1, &CMashCard::OnBnClickedButchange1)
	ON_BN_CLICKED(IDC_BUTChange2, &CMashCard::OnBnClickedButchange2)
	ON_BN_CLICKED(IDC_BUTDel1, &CMashCard::OnBnClickedButdel1)
	ON_BN_CLICKED(IDC_BUTDel2, &CMashCard::OnBnClickedButdel2)
	ON_BN_CLICKED(IDC_AddNote, &CMashCard::OnBnClickedAddnote)
	ON_BN_CLICKED(IDC_butBack, &CMashCard::OnBnClickedbutback)
	ON_BN_CLICKED(IDC_AddNote2, &CMashCard::OnBnClickedAddnote2)
	ON_BN_CLICKED(IDC_butBack2, &CMashCard::OnBnClickedbutback2)
	ON_BN_CLICKED(IDC_BUTTONCHANGEDLG, &CMashCard::OnBnClickedButtonchangedlg)
END_MESSAGE_MAP()

// обработчики сообщений CMashCard

BOOL CMashCard::OnInitDialog()
{
	CDialog::OnInitDialog();

	openDef = 0;//говорим что приложение только запущено
	////////////////////////////////////
	CString path;

	TCHAR buffer[MAX_PATH];
	DWORD size = GetCurrentDirectory(sizeof(buffer), buffer);

	path = buffer;
	path += L"\\DataBase.mdb";
	
	CDatabase database;
	CString SqlString;
	CString strName;
	CString sDriver = L"MICROSOFT ACCESS DRIVER (*.mdb)";
	CString sDsn;
	CString sFile = path;
	sDsn.Format(L"ODBC;DRIVER={%s};DSN='';DBQ=%s", sDriver, sFile);
	database.Open(NULL, false, false, sDsn);
	CRecordset recset(&database);

	SqlString = L"SELECT Name FROM NameАction";
	recset.Open(CRecordset::forwardOnly, SqlString, CRecordset::readOnly);
	int iRec = 0;
	while (!recset.IsEOF()) {
		recset.GetFieldValue(L"NameOp", strName);

		m_cbMark.AddString(strName);

		recset.MoveNext();
	}
	recset.Close();
	database.Close();
	m_cbMark.AddString(L"-");

	CString listFomr[5] = { L"А0", L"А1", L"А2", L"А3", L"А4" };
	for (int i = 0; i < 5; i++) {
		m_cbFormList.AddString(listFomr[i]);
	}
	m_cbFormList.SetCurSel(3);
	m_rbGor.SetCheck(1);
	
	CString Views[2] = { L"Сборка", L"Деталь" };
	for (int i = 0; i < 2; i++) {
		m_cbView.AddString(Views[i]);
	}

	//Создаем первую табл
	m_listCtrl.InsertColumn(
		0,              // Rank/order of item 
		L"ID",          // Caption for this header 
		LVCFMT_LEFT,    // Relative position of items under header 
		40);           // Width of items under header
					   //добавляем колонки
	m_listCtrl.InsertColumn(1, L"Название", LVCFMT_LEFT, 150);
	m_listCtrl.InsertColumn(2, L"Позиция", LVCFMT_LEFT, 100);
	m_listCtrl.InsertColumn(3, L"Количество", LVCFMT_LEFT, 120);

	////////////////////////////////////////////
	//Создаем вторую табл
	m_listCtrl2.InsertColumn(
		0,              // Rank/order of item 
		L"ID",          // Caption for this header 
		LVCFMT_LEFT,    // Relative position of items under header 
		40);           // Width of items under header
					   //добавляем колонки
	m_listCtrl2.InsertColumn(1, L"Вид", LVCFMT_LEFT, 120);
	m_listCtrl2.InsertColumn(2, L"Название", LVCFMT_LEFT, 150);
	m_listCtrl2.InsertColumn(3, L"Позиция", LVCFMT_LEFT, 100);
	m_listCtrl2.InsertColumn(4, L"Количество", LVCFMT_LEFT, 120);
	m_listCtrl2.InsertColumn(5, L"Крепить к", LVCFMT_LEFT, 100);
	m_listCtrl2.InsertColumn(6, L"Пояснение", LVCFMT_LEFT, 110);
	m_listCtrl2.InsertColumn(7, L"Сборочная ед", LVCFMT_LEFT, 135);

	m_listCtrl.SetExtendedStyle(m_listCtrl.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_listCtrl2.SetExtendedStyle(m_listCtrl2.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

	//Вставим изображение в кнопки//
	m_butSaveMake.LoadBitmaps(IDB_BITMAPSaveMake, IDB_BITMAPSaveMake, 0, IDB_BITMAPSaveMake);
	m_butOpenSave.LoadBitmaps(IDB_BITMAPOpenSave, IDB_BITMAPOpenSave, 0, IDB_BITMAPOpenSave);
	m_butLoadSb.LoadBitmaps(IDB_BITMAPLoadSb, IDB_BITMAPLoadSb, 0, IDB_BITMAPLoadSb);
	//
	m_butAdd1.LoadBitmaps(IDB_BITMAPAddTable, IDB_BITMAPAddTable, 0, IDB_BITMAPAddTable);
	m_butChange1.LoadBitmaps(IDB_BITMAPChangeTb, IDB_BITMAPChangeTb, 0, IDB_BITMAPChangeTb);
	m_butDel1.LoadBitmaps(IDB_BITMAPDelTb, IDB_BITMAPDelTb, 0, IDB_BITMAPDelTb);
	//
	m_butAdd2.LoadBitmaps(IDB_BITMAPAddTable, IDB_BITMAPAddTable, 0, IDB_BITMAPAddTable);
	m_butChange2.LoadBitmaps(IDB_BITMAPChangeTb, IDB_BITMAPChangeTb, 0, IDB_BITMAPChangeTb);
	m_butDel2.LoadBitmaps(IDB_BITMAPDelTb, IDB_BITMAPDelTb, 0, IDB_BITMAPDelTb);
	//
	m_butChangeDlg.LoadBitmaps(IDB_BITMAP1DLG13TXT, IDB_BITMAP1DLG13TXT, 0, IDB_BITMAP1DLG13TXT);
	//
	return TRUE;  // возврат значения TRUE, если фокус не передан элементу управления
}

void CMashCard::OnPaint()
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
		//
		pDC->Rectangle(rect.left, rect.top + 40, rect.left + 451, rect.bottom - 40);
		//
		pDC->Rectangle(rect.left + 451, rect.bottom - 410, rect.right - rect.left, rect.bottom - 40);
		//
		hBrush = CreateSolidBrush(RGB(64, 64, 64));
		pDC->SelectObject(hBrush);
		pDC->Rectangle(rect.left, rect.bottom - 40, rect.right - rect.left, rect.bottom - rect.top);
		//
		hBrush = CreateSolidBrush(RGB(255, 246, 158));
		pDC->SelectObject(hBrush);
		pDC->Rectangle(rect.left + 451, rect.top + 40, rect.right - 630, rect.bottom - 410);
		pDC->Rectangle(rect.right - 630, rect.top + 40, rect.right - rect.left, rect.bottom - 410);
		faq = true;
	}
}

void CMashCard::MakeDlgBkColor()
{
	CRect rect;
	GetClientRect(&rect);
	CDC *pDC = this->GetDC();
	HBRUSH  hBrush;
	hBrush = CreateSolidBrush(RGB(255, 246, 158));
	pDC->SelectObject(hBrush);
	pDC->Rectangle(rect.right - 630, rect.top + 40, rect.right - rect.left, rect.bottom - 410);
}

/*Кнопки меню*/

void CMashCard::OnBnClickedButopensave()
{
	// TODO: добавьте свой код обработчика уведомлений
	/*Чтение*/
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
		char szBuffer[1000];
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
							nItem = m_listCtrl2.InsertItem(0, textCol);
						}
						else {
							m_listCtrl2.SetItemText(nItem, numColl, textCol);
						}
					}
					//
				}
				/**/
				numColl++;
				textCol = L"";
			}
			else if(sText[i] == '\n') {
				numColl = 0;
				textCol = L"";
			}
			else {
				textCol += sText[i];
			}
		}	
	}
}

void CMashCard::OnBnClickedButsavemake()
{
	// TODO: добавьте свой код обработчика уведомлений
	CFileDialog fileDialog(FALSE,
		NULL,
		L"save.ds",
		OFN_OVERWRITEPROMPT,
		NULL,
		NULL,
		0,
		TRUE);
	int result = fileDialog.DoModal();	//запустить диалоговое окно
	if (result == IDOK)	//если файл выбран
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
		for (int i = 0; i < m_listCtrl2.GetItemCount(); i++) {
			cfile.Write(L"*", 1);
			cfile.Write(L"2", 1);
			cfile.Write(L"*", 1);
			for (int k = 0; k < 8; k++) {
				sText = m_listCtrl2.GetItemText(i, k);
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

void CMashCard::OnBnClickedButloadsb()
{
	CString fileName;

	CFileDialog *fd = new CFileDialog(true);

	if (fd->DoModal() == IDOK)
	{
		fileName = fd->GetPathName();

		strTemplateFilenameBOM = fileName;

		if (openDef == 0) {
			m_pDoc->OpenInventor();
			openDef = 1;
		}
		CprTextCardApp* pApp = (CprTextCardApp *)AfxGetApp();
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
}

void CMashCard::OnBnClickedButtonchangedlg()
{
	OnCancel();
	CTechCard openDialog;
	openDialog.DoModal();
}

/*Кнопка построения*/

void CMashCard::OnBnClickedOk()
{
	CString path;

	TCHAR buffer[MAX_PATH];
	DWORD size = GetCurrentDirectory(sizeof(buffer), buffer);

	m_cbFormList.GetWindowTextW(strDocFormat);

	path = buffer;

	//шаблоны
	if (strDocFormat == L"А0") {
		path += L"\\A0.idw";
	}
	if (strDocFormat == L"А1") {
		path += L"\\A1.idw";
	}
	if (strDocFormat == L"А2") {
		path += L"\\A2.idw";
	}
	if (strDocFormat == L"А3") {
		path += L"\\A3.idw";
	}
	if (strDocFormat == L"А4") {
		path += L"\\A4.idw";
	}

	strTemplateFilename = path;//Путь к стандартному шаблону документа//

	if (m_rbGor.GetCheck()) {
		orientationDoc = 0;
	}
	if (m_rbVer.GetCheck()) {
		orientationDoc = 1;
	}

	MakeCoord();
	if (openDef == 0) {
		m_pDoc->OpenInventor();
		openDef = 1;
	}
	MakeDoc();
	DelVar();
}

/*Кнопки управления таблицей*/

void CMashCard::OnBnClickedButadd1()
{
	OnBnClickedbutback();
	// Включаю видимость объектов
	m_AddNote.ShowWindow(TRUE);
	m_butBack.ShowWindow(TRUE);
	//
	m_stNameF.ShowWindow(TRUE);
	m_PosF.ShowWindow(TRUE);
	m_NumF.ShowWindow(TRUE);
	//
	m_edNameF.ShowWindow(TRUE);
	m_edPosF.ShowWindow(TRUE);
	m_edNumF.ShowWindow(TRUE);

	but = 0;//указываем в какую табл будет внесено значение //0 - 1 табл; 1 - 2 табл

	//очищаем элементы от значений
	m_edNameF.SetSel(0, -1);
	m_edNameF.Clear();
	m_edPosF.SetSel(0, -1);
	m_edPosF.Clear();
	m_edNumF.SetSel(0, -1);
	m_edNumF.Clear();
}

void CMashCard::OnBnClickedButadd2()
{
	OnBnClickedbutback();
	// Включаю видимость объектов
	m_butAddNote2.ShowWindow(TRUE);
	m_butBack2.ShowWindow(TRUE);
	//
	m_stNameF.ShowWindow(TRUE);
	m_PosF.ShowWindow(TRUE);
	m_NumF.ShowWindow(TRUE);
	m_View.ShowWindow(TRUE);
	m_PutOn.ShowWindow(TRUE);
	m_AddMark.ShowWindow(TRUE);
	m_stEdSbName.ShowWindow(TRUE);
	//
	m_cbMark.ShowWindow(TRUE);
	m_cbView.ShowWindow(TRUE);
	m_cbPutOn.ShowWindow(TRUE);
	m_cbNameF.ShowWindow(TRUE);
	m_cbPosF.ShowWindow(TRUE);
	m_edNumF.ShowWindow(TRUE);
	m_edSbName.ShowWindow(TRUE);

	but = 1;//указываем в какую табл будет внесено значение //0 - 1 табл; 1 - 2 табл

			//очищаем элементы от значений
	m_cbMark.SetEditSel(0, -1);
	m_cbMark.Clear();
	m_cbView.SetEditSel(0, -1);
	m_cbView.Clear();

	m_cbNameF.ResetContent();
	m_cbPutOn.ResetContent();
	m_cbPosF.ResetContent();

	m_edNumF.SetSel(0, -1);
	m_edNumF.Clear();

	m_edSbName.SetSel(0, -1);
	m_edSbName.Clear();

	//Добавляем элементы в комбо-боксы для добавления во 2 табл
	int count = m_listCtrl.GetItemCount();
	m_cbPutOn.AddString(L"-");
	for (int i = 0; i < count; i++) {
		CString name = m_listCtrl.GetItemText(i, 1);
		CString pos = m_listCtrl.GetItemText(i, 2);

		m_cbNameF.AddString(name);
		m_cbPosF.AddString(pos);
		m_cbPutOn.AddString(pos);
	}
}

void CMashCard::OnBnClickedButchange1()
{
	// Включаю видимость объектов
	m_AddNote.ShowWindow(TRUE);
	m_butBack.ShowWindow(TRUE);
	//
	m_stNameF.ShowWindow(TRUE);
	m_PosF.ShowWindow(TRUE);
	m_NumF.ShowWindow(TRUE);
	//
	m_edNameF.ShowWindow(TRUE);
	m_edPosF.ShowWindow(TRUE);
	m_edNumF.ShowWindow(TRUE);

	but = 2;//указываем в какую табл будет внесено значение //0 - 1 табл; 1 - 2 табл

	POSITION pos = m_listCtrl.GetFirstSelectedItemPosition();
	int nItem = m_listCtrl.GetNextSelectedItem(pos);

	m_edNameF.SetWindowTextW(m_listCtrl.GetItemText(nItem, 1));
	m_edPosF.SetWindowTextW(m_listCtrl.GetItemText(nItem, 2));
	m_edNumF.SetWindowTextW(m_listCtrl.GetItemText(nItem, 3));

	listItem = nItem;
}

void CMashCard::OnBnClickedButchange2()
{
	// Включаю видимость объектов
	m_butAddNote2.ShowWindow(TRUE);
	m_butBack2.ShowWindow(TRUE);
	//
	m_stNameF.ShowWindow(TRUE);
	m_PosF.ShowWindow(TRUE);
	m_NumF.ShowWindow(TRUE);
	m_View.ShowWindow(TRUE);
	m_PutOn.ShowWindow(TRUE);
	m_AddMark.ShowWindow(TRUE);
	m_stEdSbName.ShowWindow(TRUE);
	//
	m_cbMark.ShowWindow(TRUE);
	m_cbView.ShowWindow(TRUE);
	m_cbPutOn.ShowWindow(TRUE);
	m_cbNameF.ShowWindow(TRUE);
	m_cbPosF.ShowWindow(TRUE);
	m_edNumF.ShowWindow(TRUE);
	m_edSbName.ShowWindow(TRUE);

	but = 3;//указываем в какую табл будет внесено значение //0 - 1 табл; 1 - 2 табл

			//очищаем элементы от значений
	m_cbMark.SetEditSel(0, -1);
	m_cbMark.Clear();
	m_cbView.SetEditSel(0, -1);
	m_cbView.Clear();

	m_cbNameF.ResetContent();
	m_cbPutOn.ResetContent();
	m_cbPosF.ResetContent();

	m_edNumF.SetSel(0, -1);
	m_edNumF.Clear();

	m_edSbName.SetSel(0, -1);
	m_edSbName.Clear();

	//Добавляем элементы в комбо-боксы для добавления во 2 табл
	int count = m_listCtrl.GetItemCount();
	m_cbPutOn.AddString(L"-");
	for (int i = 0; i < count; i++) {
		CString name = m_listCtrl.GetItemText(i, 1);
		CString pos = m_listCtrl.GetItemText(i, 2);

		m_cbNameF.AddString(name);
		m_cbPosF.AddString(pos);
		m_cbPutOn.AddString(pos);
	}

	POSITION pos = m_listCtrl2.GetFirstSelectedItemPosition();
	int nItem = m_listCtrl2.GetNextSelectedItem(pos);

	m_cbNameF.SetWindowTextW(m_listCtrl2.GetItemText(nItem, 2));
	m_cbPosF.SetWindowTextW(m_listCtrl2.GetItemText(nItem, 3));
	m_edNumF.SetWindowTextW(m_listCtrl2.GetItemText(nItem, 4));
	m_cbMark.SetWindowTextW(m_listCtrl2.GetItemText(nItem, 6));
	m_cbView.SetWindowTextW(m_listCtrl2.GetItemText(nItem, 1));
	m_cbPutOn.SetWindowTextW(m_listCtrl2.GetItemText(nItem, 5));
	m_edSbName.SetWindowTextW(m_listCtrl2.GetItemText(nItem, 7));

	listItem = nItem;
}

void CMashCard::OnBnClickedButdel1()
{
	POSITION pos = m_listCtrl.GetFirstSelectedItemPosition();
	int nItem = m_listCtrl.GetNextSelectedItem(pos);
	m_listCtrl.DeleteItem(nItem);
}

void CMashCard::OnBnClickedButdel2()
{
	POSITION pos = m_listCtrl2.GetFirstSelectedItemPosition();
	int nItem = m_listCtrl2.GetNextSelectedItem(pos);
	m_listCtrl2.DeleteItem(nItem);
}

void CMashCard::OnBnClickedAddnote()
{
	// добавляем записи в табл
	if (but == 0) {//запись в 1 табл
		int nCount = m_listCtrl.GetItemCount();
		int nItem;
		CString str, strName, pos, num;
		str.Format(L"%d", nCount);
		if (nCount < 10) {
			str = '0' + str;
		}
		//берем значения с edit полей
		m_edNameF.GetWindowTextW(strName);
		m_edPosF.GetWindowTextW(pos);
		m_edNumF.GetWindowTextW(num);

		nItem = m_listCtrl.InsertItem(0, str);
		m_listCtrl.SetItemText(nItem, 1, strName);
		m_listCtrl.SetItemText(nItem, 2, pos);
		m_listCtrl.SetItemText(nItem, 3, num);
		//
		m_AddNote.ShowWindow(FALSE);
		m_butBack.ShowWindow(FALSE);
		//
		m_stNameF.ShowWindow(FALSE);
		m_PosF.ShowWindow(FALSE);
		m_NumF.ShowWindow(FALSE);
		//
		m_edNameF.ShowWindow(FALSE);
		m_edPosF.ShowWindow(FALSE);
		m_edNumF.ShowWindow(FALSE);

		MakeDlgBkColor();
	}
	else if (but == 1) {
		//запись во 2 табл
		int nCount = m_listCtrl2.GetItemCount();
		int nItem;
		CString str, strName, pos, num, view, mark, id, sbName;
		str.Format(L"%d", nCount);
		if (nCount < 10) {
			str = '0' + str;
		}

		m_cbView.GetWindowTextW(view);
		m_cbNameF.GetWindowTextW(strName);
		m_cbPosF.GetWindowTextW(pos);
		m_edNumF.GetWindowTextW(num);
		m_cbPutOn.GetWindowTextW(id);
		m_cbMark.GetWindowTextW(mark);
		m_edSbName.GetWindowTextW(sbName);

		nItem = m_listCtrl2.InsertItem(0, str);
		m_listCtrl2.SetItemText(nItem, 1, view);
		m_listCtrl2.SetItemText(nItem, 2, strName);
		m_listCtrl2.SetItemText(nItem, 3, pos);
		m_listCtrl2.SetItemText(nItem, 4, num);
		m_listCtrl2.SetItemText(nItem, 5, id);
		m_listCtrl2.SetItemText(nItem, 6, mark);
		m_listCtrl2.SetItemText(nItem, 7, sbName);
		//
		m_butAddNote2.ShowWindow(FALSE);
		m_butBack2.ShowWindow(FALSE);
		//
		m_stNameF.ShowWindow(FALSE);
		m_PosF.ShowWindow(FALSE);
		m_NumF.ShowWindow(FALSE);
		m_View.ShowWindow(FALSE);
		m_PutOn.ShowWindow(FALSE);
		m_AddMark.ShowWindow(FALSE);
		m_stEdSbName.ShowWindow(FALSE);
		//
		m_cbMark.ShowWindow(FALSE);
		m_cbView.ShowWindow(FALSE);
		m_cbPutOn.ShowWindow(FALSE);
		m_cbNameF.ShowWindow(FALSE);
		m_cbPosF.ShowWindow(FALSE);
		m_edNumF.ShowWindow(FALSE);
		m_edSbName.ShowWindow(FALSE);

		MakeDlgBkColor();
	}
	else if (but == 2) {
		int nItem;
		CString strName, pos, num;
		nItem = listItem;

		m_edNameF.GetWindowTextW(strName);
		m_edPosF.GetWindowTextW(pos);
		m_edNumF.GetWindowTextW(num);

		m_listCtrl.SetItemText(nItem, 1, strName);
		m_listCtrl.SetItemText(nItem, 2, pos);
		m_listCtrl.SetItemText(nItem, 3, num);

		//
		m_AddNote.ShowWindow(FALSE);
		m_butBack.ShowWindow(FALSE);
		//
		m_stNameF.ShowWindow(FALSE);
		m_PosF.ShowWindow(FALSE);
		m_NumF.ShowWindow(FALSE);
		//
		m_edNameF.ShowWindow(FALSE);
		m_edPosF.ShowWindow(FALSE);
		m_edNumF.ShowWindow(FALSE);

		MakeDlgBkColor();
	}
	else {
		int nItem;
		CString strName, pos, num, view, mark, id, sbName;
		nItem = listItem;

		m_cbView.GetWindowTextW(view);
		m_cbNameF.GetWindowTextW(strName);
		m_cbPosF.GetWindowTextW(pos);
		m_edNumF.GetWindowTextW(num);
		m_cbPutOn.GetWindowTextW(id);
		m_cbMark.GetWindowTextW(mark);
		m_edSbName.GetWindowTextW(sbName);

		m_listCtrl2.SetItemText(nItem, 1, view);
		m_listCtrl2.SetItemText(nItem, 2, strName);
		m_listCtrl2.SetItemText(nItem, 3, pos);
		m_listCtrl2.SetItemText(nItem, 4, num);
		m_listCtrl2.SetItemText(nItem, 5, id);
		m_listCtrl2.SetItemText(nItem, 6, mark);
		m_listCtrl2.SetItemText(nItem, 7, sbName);
		//
		m_butAddNote2.ShowWindow(FALSE);
		m_butBack2.ShowWindow(FALSE);
		//
		m_stNameF.ShowWindow(FALSE);
		m_PosF.ShowWindow(FALSE);
		m_NumF.ShowWindow(FALSE);
		m_View.ShowWindow(FALSE);
		m_PutOn.ShowWindow(FALSE);
		m_AddMark.ShowWindow(FALSE);
		m_stEdSbName.ShowWindow(FALSE);
		//
		m_cbMark.ShowWindow(FALSE);
		m_cbView.ShowWindow(FALSE);
		m_cbPutOn.ShowWindow(FALSE);
		m_cbNameF.ShowWindow(FALSE);
		m_cbPosF.ShowWindow(FALSE);
		m_edNumF.ShowWindow(FALSE);
		m_edSbName.ShowWindow(FALSE);

		MakeDlgBkColor();
	}
}

void CMashCard::OnBnClickedbutback()
{
	m_AddNote.ShowWindow(FALSE);
	m_butBack.ShowWindow(FALSE);
	//
	m_butAddNote2.ShowWindow(FALSE);
	m_butBack2.ShowWindow(FALSE);
	//
	m_stNameF.ShowWindow(FALSE);
	m_PosF.ShowWindow(FALSE);
	m_NumF.ShowWindow(FALSE);
	m_View.ShowWindow(FALSE);
	m_PutOn.ShowWindow(FALSE);
	m_AddMark.ShowWindow(FALSE);
	m_stEdSbName.ShowWindow(FALSE);
	//
	m_cbMark.ShowWindow(FALSE);
	m_cbView.ShowWindow(FALSE);
	m_cbPutOn.ShowWindow(FALSE);
	m_cbNameF.ShowWindow(FALSE);
	m_cbPosF.ShowWindow(FALSE);
	m_edNumF.ShowWindow(FALSE);
	m_edSbName.ShowWindow(FALSE);
	m_edNameF.ShowWindow(FALSE);
	m_edPosF.ShowWindow(FALSE);
	m_edNumF.ShowWindow(FALSE);

	MakeDlgBkColor();
}

void CMashCard::OnBnClickedAddnote2()
{
	OnBnClickedAddnote();
}

void CMashCard::OnBnClickedbutback2()
{
	OnBnClickedbutback();
}

/*Расчет и построение*/

void CMashCard::MakeDoc()
{
	m_pDoc->MakeDocF(strTemplateFilename);

	int num;//число блоков

	num = sqCoordSbX.GetCount();

	for (int i = 0; i < num; i++) {
		m_pDoc->MakeSq(sqCoordSbX[i], sqCoordSbY[i], orientBloc[i]);
		m_pDoc->AddText(sqCoordSbX[i], sqCoordSbY[i], sqNameText[i], sqPosText[i], sqNumText[i], orientBloc[i]);
	}

	for (int i = 0; i < lineCoordX.GetCount(); i += 2) {
		m_pDoc->MakeLn(lineCoordX[i], lineCoordY[i], lineCoordX[i + 1], lineCoordY[i + 1]);
	}

	for (int i = 0; i < coordMarkX.GetCount(); i++) {
		m_pDoc->MakeMark(coordMarkX[i], coordMarkY[i], markText[i], orientMark[i], typeMark[i]);
	}
}

void CMashCard::MakeCoord()
{
	/*расчет координат и заполнение*/
	int nCount = m_listCtrl2.GetItemCount();
	InitVarFormat();

	for (int i = 0; i < nCount; i++) {
		if ("Сборка" == m_listCtrl2.GetItemText(i, 1)) {
			if ("-" == m_listCtrl2.GetItemText(i, 5)) {
				MakeSb(0, i);
			}
			else {
				MakeSb(1, i);
			}
		}
		else {
			if (m_listCtrl2.GetItemText(numFirst, 3) == m_listCtrl2.GetItemText(i, 5)) {
				MakeDet(0, i);
			}
			else {
				MakeDet(1, i);
			}
		}
	}
	MakeSb2();
}

void CMashCard::MakeSb(int pos, int id)
{
	if (pos == 0) {//основа сборки
		if (orientationDoc == 0) {//вертикально строить схему
			sqCoordSbX.Add(firstElX);
			sqCoordSbY.Add(firstElY);
			orientBloc.Add(1);
			MakeTextSb(id, 0, 0);////////////////////////////////////////
		}
		else {//горизонтально строить схему
			sqCoordSbX.Add(firstElX);
			sqCoordSbY.Add(firstElY);
			orientBloc.Add(0);
			MakeTextSb(id, 0, 0);
		}
		numFirst = id;
	}
	else {//подсборки
		numPlace = 0;
		numPlaceLev = 0;
		double X, Y;
		if (m_listCtrl2.GetItemText(id, 5) == m_listCtrl2.GetItemText(numFirst, 3)) {
			if (orientationDoc == 0) {
				FindPlace(id, 0);

				if (numPlace == 0) {
					numPlace = 1;
				}
				xLast += 5;

				sqCoordSbX.Add(xLast - 0.45);
				sqCoordSbY.Add(y0 - 5 - numPlace * 2);
				orientBloc.Add(0);
				MakeTextSb(id, 0, 0);

				sqCoordSbX.Add(xLast - 0.45);
				sqCoordSbY.Add(y0 - 1);
				orientBloc.Add(0);
				MakeTextSb(id, 1, 0);

				X = xLast;
				Y = y0 - 5 - numPlace * 2;

				makeLineCoord(xLast, y0, xLast, y0 - 1);
				makeLineCoord(xLast, y0 - 5, xLast, y0 - 5 - numPlace * 2);

				if (m_listCtrl2.GetItemText(id, 6) != L"-") {
					makeMarkCoord(xLast, y0, m_listCtrl2.GetItemText(id, 6), 0, 0);
				}

				xLast += 1;
				xMax = xLast;
			}
			else {
				FindPlace(id, 0);
				if (numPlace == 0) {
					numPlace = 1;
				}

				xLast -= 1;

				sqCoordSbX.Add(y0 - 9 - numPlace * 2);
				sqCoordSbY.Add(xLast + 0.45);
				orientBloc.Add(1);
				MakeTextSb(id, 0, 0);

				sqCoordSbX.Add(y0 - 5);
				sqCoordSbY.Add(xLast + 0.45);
				orientBloc.Add(1);
				MakeTextSb(id, 1, 0);

				X = y0 - 5 - numPlace * 2;
				Y = xLast;

				makeLineCoord(y0 - 5 - numPlace * 2, xLast, y0 - 5, xLast);
				makeLineCoord(y0 - 1, xLast, y0, xLast);

				if (m_listCtrl2.GetItemText(id, 6) != L"-") {
					makeMarkCoord(y0, xLast, m_listCtrl2.GetItemText(id, 6), 1, 1);
				}

				xLast -= 1;
				xMax = xLast;
			}

			sqPos.Add(m_listCtrl2.GetItemText(id, 3));
			orientEl.Add(orientBloc[sqCoordSbX.GetCount() - 1]);
			coordElX.Add(X);
			coordElY.Add(Y);
			elIdM.Add(id);
		}//////////////////////////////////////////////////////
		else {
			int orientF, elId;
			int pos = 0;
			int posSb = 0;
			double line = 0;
			double coordX, coordY;
			for (int i = 0; i < sqPos.GetCount(); i++) {
				if (m_listCtrl2.GetItemText(id, 5) == sqPos[i]) {
					if (orientEl[i] == 1) {
						orientF = 0;
					}
					else {
						orientF = 1;
					}
					coordX = coordElX[i];
					coordY = coordElY[i];
					elId = elIdM[i];
				}
			}

			for (int i = 0; i < id; i++) {
				if (m_listCtrl2.GetItemText(i, 5) == m_listCtrl2.GetItemText(id, 5)) {
					pos++;
					if ("Сборка" == m_listCtrl2.GetItemText(i, 1)) {
						posSb++;
					}
				}
			}


			if (posSb == 0) {
				line = 2 + pos * 2;
			}
			else {
				for (int i = 0; i < id; i++) {
					if (m_listCtrl2.GetItemText(i, 5) == m_listCtrl2.GetItemText(id, 5)) {
						if ("Деталь" == m_listCtrl2.GetItemText(i, 1)) {
							line += 2;
						}
						else {
							bool yesSb = false;
							for (int k = 0; k < i; k++) {
								if (m_listCtrl2.GetItemText(k, 5) == m_listCtrl2.GetItemText(id, 5)) {
									if ("Сборка" == m_listCtrl2.GetItemText(k, 1)) {
										yesSb = true;
									}
								}
							}

							if (yesSb == false) {
								line += 2;
							}
							else {
								int id1, id2;
								id1 = 0;
								id2 = 0;
								for (int k = 0; k < i; k++) {
									if (m_listCtrl2.GetItemText(k, 5) == m_listCtrl2.GetItemText(id, 5)) {
										if (id1 == 0) {
											id1 = k;
										}
										else {
											id2 = id1;
											id1 = k;
										}
									}
								}

								if ("Деталь" == m_listCtrl2.GetItemText(id1, 1)) {
									if ("Деталь" == m_listCtrl2.GetItemText(id2, 1)) {
										line += 2;
									}
									else {
										line += 3;
									}
								}
								else {
									line += 3;
									FindPlace(elId, 0);
									line += numPlace * 2;

									numPlace = 0;
									numPlaceLev = 0;
								}

								FindPlace(elId, 0);
								line += numPlace * 2;

								numPlace = 0;
								numPlaceLev = 0;

							}
						}
					}
				}
			}

			if (orientF == 0) {//вертикаль
				FindPlace(id, 0);

				sqCoordSbX.Add(coordX + line - 1.45);
				sqCoordSbY.Add(coordY - 5 - numPlace * 2);
				orientBloc.Add(orientF);
				MakeTextSb(id, 0, 0);

				sqCoordSbX.Add(coordX + line - 1.45);
				sqCoordSbY.Add(coordY - 1);
				orientBloc.Add(orientF);
				MakeTextSb(id, 1, 0);

				X = coordX + line - 1;
				Y = coordY - 5 - numPlace * 2;

				makeLineCoord(coordX + line - 1, coordY, coordX + line - 1, coordY - 1);
				makeLineCoord(coordX + line - 1, coordY - 5, coordX + line - 1, coordY - 5 - numPlace * 2);

				if (m_listCtrl2.GetItemText(id, 6) != L"-") {
					makeMarkCoord(coordX + line - 1, coordY, m_listCtrl2.GetItemText(id, 6), 0, 0);
				}

				if (orientationDoc == 1) {///////////////
					double ycmax;
					ycmax = coordY - 8 - numPlace * 2;
					if (ycmax < xLast) {
						xLast = ycmax;
					}
				}
			}
			else {//горизонталь
				FindPlace(id, 0);

				sqCoordSbX.Add(coordX + 5 + numPlace * 2);
				sqCoordSbY.Add(coordY + line - 0.55);
				orientBloc.Add(orientF);
				MakeTextSb(id, 0, 0);

				sqCoordSbX.Add(coordX + 1);
				sqCoordSbY.Add(coordY + line - 0.55);
				orientBloc.Add(orientF);
				MakeTextSb(id, 1, 0);

				X = coordX + 5 + numPlace * 2;
				Y = coordY + line - 1;

				makeLineCoord(coordX, coordY + line - 1, coordX + 1, coordY + line - 1);
				makeLineCoord(coordX + 5, coordY + line - 1, coordX + 5 + numPlace * 2, coordY + line - 1);

				if (m_listCtrl2.GetItemText(id, 6) != L"-") {
					makeMarkCoord(coordX, coordY + line - 1, m_listCtrl2.GetItemText(id, 6), 1, 0);
				}

				if (orientationDoc == 0) {///////////////
					double xcmax;
					xcmax = coordX + 8 + numPlace * 2;
					if (xcmax > xLast) {
						xLast = xcmax;
					}
				}
			}

			sqPos.Add(m_listCtrl2.GetItemText(id, 3));
			orientEl.Add(orientBloc[sqCoordSbX.GetCount() - 1]);
			coordElX.Add(X);
			coordElY.Add(Y);
			elIdM.Add(id);
		}////////////////////////////////////////
	}
}

void CMashCard::MakeSb2()
{
	if (orientationDoc == 0) {
		sqCoordSbX.Add(xLast);
		sqCoordSbY.Add(secondElY);
		orientBloc.Add(1);
		MakeTextSb(numFirst, 1, 0);

		makeLineCoord(firstElX + 4, firstElY - 0.45, xLast, secondElY - 0.45);
	}
	else {
		sqCoordSbX.Add(secondElX);
		sqCoordSbY.Add(xLast);
		orientBloc.Add(0);
		MakeTextSb(numFirst, 1, 0);

		makeLineCoord(firstElX + 0.45, firstElY - 4, secondElX + 0.45, xLast);
	}
}

void CMashCard::FindPlace(int id, int pos)
{
	int nCount = m_listCtrl2.GetItemCount();

	if (pos == 0) {
		for (int i = 0; i < nCount; i++) {
			if (m_listCtrl2.GetItemText(id, 3) == m_listCtrl2.GetItemText(i, 5)) {
				if ("Сборка" == m_listCtrl2.GetItemText(i, 1)) {
					numPlaceLev++;
					FindPlace(i, 1);
					////////////////////
					int numSbOnEl = 0;
					for (int k = 0; k < m_listCtrl2.GetItemCount(); k++) {
						if (m_listCtrl2.GetItemText(id, 3) == m_listCtrl2.GetItemText(k, 5)) {
							if ("Сборка" == m_listCtrl2.GetItemText(k, 1)) {
								numSbOnEl++;
							}
						}
					}

					if (numSbOnEl == 1) {
						numPlace++;
					}
					else if (numSbOnEl > 1) {
						int f = 0;
						for (int k = 0; k < i; k++) {
							if (m_listCtrl2.GetItemText(id, 3) == m_listCtrl2.GetItemText(k, 5)) {
								if ("Сборка" == m_listCtrl2.GetItemText(k, 1)) {
									f++;
								}
							}
						}
						if (f == 0) {
							numPlace++;
						}
						else {
							if (numPlaceLev == 1) {
								numPlace++;
							}
							else if (numPlaceLev == 2) {
								numPlace += 5;
							}
							else if (numPlaceLev >= 4) {
								numPlace += 7;
							}
						}
					}

					numPlaceLev = 0;
				}
				else {
					numPlace++;
				}
			}
		}
	}
	else {
		for (int i = 0; i < nCount; i++) {
			if (m_listCtrl2.GetItemText(id, 3) == m_listCtrl2.GetItemText(i, 5)) {
				if ("Сборка" == m_listCtrl2.GetItemText(i, 1)) {
					numPlaceLev++;
					FindPlace(id, 1);
				}
			}
		}
	}
}

void CMashCard::makeLineCoord(double x1, double y1, double x2, double y2)
{
	lineCoordX.Add(x1);
	lineCoordY.Add(y1);

	lineCoordX.Add(x2);
	lineCoordY.Add(y2);
}

void CMashCard::makeMarkCoord(double x, double y, CString text, int orientation, int t)
{
	coordMarkX.Add(x);
	coordMarkY.Add(y);
	markText.Add(text);
	orientMark.Add(orientation);
	typeMark.Add(t);
}

void CMashCard::MakeDet(int pos, int id)
{
	if (pos == 0) {
		if (orientationDoc == 0) {
			xMax += 1;
			sqCoordSbX.Add(xMax - 0.45);
			sqCoordSbY.Add(y0 + 5);
			orientBloc.Add(0);
			MakeTextSb(id, 0, 1);
			makeLineCoord(xMax, y0, xMax, y0 + 1);
			if (m_listCtrl2.GetItemText(id, 6) != L"-") {
				makeMarkCoord(xMax, y0, m_listCtrl2.GetItemText(id, 6), 0, 0);
			}
			xMax += 1;
			if (xMax > xLast) {
				xLast = xMax;
			}
		}
		else {
			xMax -= 1;
			sqCoordSbX.Add(y0 + 1);
			sqCoordSbY.Add(xMax + 0.45);
			orientBloc.Add(1);
			MakeTextSb(id, 0, 1);
			makeLineCoord(y0, xMax, y0 + 1, xMax);
			if (m_listCtrl2.GetItemText(id, 6) != L"-") {
				makeMarkCoord(y0, xMax, m_listCtrl2.GetItemText(id, 6), 1, 0);
			}
			xMax -= 1;

			if (xMax > xLast) {
				xLast = xMax;
			}
		}
	}
	else {
		double X, Y;
		int orient, elId;

		for (int i = 0; i < sqPos.GetCount(); i++) {
			if (m_listCtrl2.GetItemText(id, 5) == sqPos[i]) {
				if (orientEl[i] == 0) {
					orient = 1;
				}
				else {
					orient = 0;
				}
				X = coordElX[i];
				Y = coordElY[i];
				elId = elIdM[i];
			}
		}
		int pos = 0;
		int posSb = 0;
		double line = 0;
		//////////////////////////////////////////////
		for (int i = 0; i < id; i++) {
			if (m_listCtrl2.GetItemText(i, 5) == m_listCtrl2.GetItemText(id, 5)) {
				pos++;
				if ("Сборка" == m_listCtrl2.GetItemText(i, 1)) {
					posSb++;
				}
			}
		}


		if (posSb == 0) {
			line = 2 + pos * 2;
		}
		else {
			for (int i = 0; i < id; i++) {
				if (m_listCtrl2.GetItemText(i, 5) == m_listCtrl2.GetItemText(id, 5)) {
					if ("Деталь" == m_listCtrl2.GetItemText(i, 1)) {
						line += 2;
					}
					else {
						bool yesSb = false;
						for (int k = 0; k < i; k++) {
							if (m_listCtrl2.GetItemText(k, 5) == m_listCtrl2.GetItemText(id, 5)) {
								if ("Сборка" == m_listCtrl2.GetItemText(k, 1)) {
									yesSb = true;
								}
							}
						}

						if (yesSb == false) {
							line += 2;
						}
						else {
							int id1, id2;
							id1 = 0;
							id2 = 0;
							for (int k = 0; k < i; k++) {
								if (m_listCtrl2.GetItemText(k, 5) == m_listCtrl2.GetItemText(id, 5)) {
									if (id1 == 0) {
										id1 = k;
									}
									else {
										id2 = id1;
										id1 = k;
									}
								}
							}

							if ("Деталь" == m_listCtrl2.GetItemText(id1, 1)) {
								if ("Деталь" == m_listCtrl2.GetItemText(id2, 1)) {
									line += 2;
								}
								else {
									line += 3;
								}
							}
							else {
								line += 3;
								FindPlace(elId, 0);
								line += numPlace * 2;

								numPlace = 0;
								numPlaceLev = 0;
							}

							FindPlace(elId, 0);
							line += numPlace * 2;

							numPlace = 0;
							numPlaceLev = 0;
						}
					}
				}
			}
		}


		if (orient == 0) {
			sqCoordSbX.Add(X + line - 1.55);
			sqCoordSbY.Add(Y + 5);
			orientBloc.Add(orient);
			MakeTextSb(id, 0, 1);
			makeLineCoord(X + line - 1, Y, X + line - 1, Y + 1);
			if (m_listCtrl2.GetItemText(id, 6) != L"-") {
				makeMarkCoord(X - line + 1, Y, m_listCtrl2.GetItemText(id, 6), orient, 0);
			}
		}
		else {
			sqCoordSbX.Add(X - 5);
			sqCoordSbY.Add(Y + line - 0.55);
			orientBloc.Add(orient);
			MakeTextSb(id, 0, 1);
			makeLineCoord(X, Y + line - 1, X - 1, Y + line - 1);
			if (m_listCtrl2.GetItemText(id, 6) != L"-") {
				makeMarkCoord(X, Y + line - 1, m_listCtrl2.GetItemText(id, 6), orient, 0);
			}
		}
	}
}

void CMashCard::MakeTextSb(int id, int numBloc, int type)//////////////////////////////////////////////
{
	CString str, str1;

	if (numBloc == 0) {
		str = m_listCtrl2.GetItemText(id, 2);
	}
	else {
		str = m_listCtrl2.GetItemText(id, 7);
	}

	if (type == 0) {
		int lev = 1;
		int nowID = id;
		if (m_listCtrl2.GetItemText(nowID, 3) == m_listCtrl2.GetItemText(numFirst, 3)) {
			str = L"Сб " + str;
		}
		else {
			while (m_listCtrl2.GetItemText(nowID, 5) != m_listCtrl2.GetItemText(numFirst, 3))
			{
				for (int i = 0; i < sqPos.GetCount(); i++) {
					if (m_listCtrl2.GetItemText(nowID, 5) == sqPos[i]) {
						nowID = elIdM[i];
						lev++;
					}
				}

			}
			str1.Format(L"%d", lev);
			str = str1 + " Сб " + str;
		}
	}


	sqNameText.Add(str);
	sqPosText.Add(m_listCtrl2.GetItemText(id, 3));
	sqNumText.Add(m_listCtrl2.GetItemText(id, 4));
}

void CMashCard::InitVarFormat()
{
	if ("А3" == strDocFormat) {
		if (orientationDoc == 0) {
			firstElX = 3;
			firstElY = 25.25;

			secondElX = 37.75;
			secondElY = 25.25;
		}
		else {
			firstElX = 36.25;
			firstElY = 28.4;

			secondElX = 36.25;
			secondElY = 9.4;
		}
	}
	else if ("А0" == strDocFormat) {
		if (orientationDoc == 0) {
			firstElX = 6;
			firstElY = 79.55;

			secondElX = 114.9;
			secondElY = 79.55;
		}
		else {
			firstElX = 113.45;
			firstElY = 83.1;

			secondElX = 113.45;
			secondElY = 9.5;
		}
	}
	else if ("А1" == strDocFormat) {
		if (orientationDoc == 0) {
			firstElX = 6;
			firstElY = 54.9;

			secondElX = 79;
			secondElY = 54.9;
		}
		else {
			firstElX = 78.65;
			firstElY = 58.3;

			secondElX = 78.65;
			secondElY = 9.5;
		}
	}
	else if ("А2" == strDocFormat) {
		if (orientationDoc == 0) {
			firstElX = 5.7;
			firstElY = 37.4;

			secondElX = 54.7;
			secondElY = 37.4;
		}
		else {
			firstElX = 53.5;
			firstElY = 41;

			secondElX = 53.5;
			secondElY = 9.5;
		}
	}
	else if ("А4" == strDocFormat) {
		if (orientationDoc == 0) {
			firstElX = 5.7;
			firstElY = 25.5;

			secondElX = 17;
			secondElY = 25.5;
		}
		else {
			firstElX = 15.55;
			firstElY = 29;

			secondElX = 15.55;
			secondElY = 9.5;
		}
	}

	if (orientationDoc == 0) {
		xLast = firstElX + 4;
		xMax = xLast;
		y0 = firstElY - 0.45;
	}
	else {
		xLast = firstElY - 4;
		xMax = xLast;
		y0 = firstElX + 0.45;
	}
}

void CMashCard::DelVar()
{
	sqCoordSbX.RemoveAll();
	sqCoordSbY.RemoveAll();
	orientBloc.RemoveAll();
	sqPosText.RemoveAll();
	sqNumText.RemoveAll();
	sqNameText.RemoveAll();

	lineCoordX.RemoveAll();
	lineCoordY.RemoveAll();

	coordMarkX.RemoveAll();
	coordMarkY.RemoveAll();
	markText.RemoveAll();
	orientMark.RemoveAll();
	typeMark.RemoveAll();

	sqPos.RemoveAll();
	orientEl.RemoveAll();
	elIdM.RemoveAll();
	coordElX.RemoveAll();
	coordElY.RemoveAll();
}

/*TextStylePtr pStyle, pStyle2;

pStyle = tb[0]->GetStyle();
pStyle2 = tb[0]->GetStyle();


pStyle->put_Font(text);
pStyle->PutFontSize(7);


pStyle->put_Font(position);
pStyle2->PutFontSize(2);

tb[0]->put_Style(pStyle);
tb[1]->put_Style(pStyle2);*/

/*
sheet->put_Orientation(kPortraitPageOrientation);
sheet->put_Size(DrawingSheetSizeEnum::kA4DrawingSheetSize);//DrawingSheetSizeEnum.kA0DrawingSheetSize
sheet->TitleBlock->MethodDelete();//Border
sheet->put_Size(kCustomDrawingSheetSize);
sheet->put_Height(10.0);*/

/*
в h
bool CheckPar();

в вызове
if (!CheckPar())//ф-ция инициализации переменных и их проверки
{
return;
}

в функции
if (m_V1d2 > df)
{
//изменить модуль или количество зубьев или диаметр вала 1
AfxMessageBox(_T("Измените модуль или количество зубьев шестерни"));
return false;
}
return true;
*/