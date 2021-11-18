
// prTextCardDlg.cpp : файл реализации
//

#include "stdafx.h"
#include "prTextCard.h"
#include "prTextCardDlg.h"
#include "afxdialogex.h"
#include "TechCard.h"
#include "MashCard.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Диалоговое окно CAboutDlg используется для описания сведений о приложении

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV

// Реализация
protected:
	DECLARE_MESSAGE_MAP()
public:
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()

// диалоговое окно CprTextCardDlg

CprTextCardDlg::CprTextCardDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_PRTEXTCARD_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CprTextCardDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTMashSh, m_butMashSh);
	DDX_Control(pDX, IDC_BUTMashCard, m_butMashCard);
	DDX_Control(pDX, IDC_BUTMashShTxt, m_butMashShTxt);
	DDX_Control(pDX, IDC_BUTMashCardTxt, m_butMashCardTxt);
}

BEGIN_MESSAGE_MAP(CprTextCardDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTMashSh, &CprTextCardDlg::OnBnClickedButmashsh)
	ON_BN_CLICKED(IDC_BUTMashCard, &CprTextCardDlg::OnBnClickedButmashcard)
	ON_BN_CLICKED(IDC_BUTMashShTxt, &CprTextCardDlg::OnBnClickedButmashshtxt)
	ON_BN_CLICKED(IDC_BUTMashCardTxt, &CprTextCardDlg::OnBnClickedButmashcardtxt)
END_MESSAGE_MAP()

// обработчики сообщений CprTextCardDlg

BOOL CprTextCardDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Добавление пункта "О программе..." в системное меню.

	// IDM_ABOUTBOX должен быть в пределах системной команды.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	//// Задает значок для этого диалогового окна.  Среда делает это автоматически,
	////  если главное окно приложения не является диалоговым
	//SetIcon(m_hIcon, TRUE);			// Крупный значок
	//SetIcon(m_hIcon, FALSE);		// Мелкий значок

	// TODO: добавьте дополнительную инициализацию

	//Вставим изображение в кнопки//
	m_butMashSh.LoadBitmaps(IDB_BitMashShem, IDB_BitMashShem, 0, IDB_BitMashShem);
	m_butMashCard.LoadBitmaps(IDB_BitMashCard, IDB_BitMashCard, 0, IDB_BitMashCard);
	m_butMashShTxt.LoadBitmaps(IDB_BITMAPDLG1Text1, IDB_BITMAPDLG1Text1, 0, IDB_BITMAPDLG1Text1);
	m_butMashCardTxt.LoadBitmaps(IDB_BITMAPDLG1TXT2, IDB_BITMAPDLG1TXT2, 0, IDB_BITMAPDLG1TXT2);
	return TRUE;  // возврат значения TRUE, если фокус не передан элементу управления
}

void CprTextCardDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// При добавлении кнопки свертывания в диалоговое окно нужно воспользоваться приведенным ниже кодом,
//  чтобы нарисовать значок.  Для приложений MFC, использующих модель документов или представлений,
//  это автоматически выполняется рабочей областью.

void CprTextCardDlg::OnPaint()
{
	if (faq == false) {
		CRect rect;
		GetClientRect(&rect);
		CDC *pDC = this->GetDC();
		HBRUSH  hBrush = CreateSolidBrush(RGB(64, 64, 64));
		pDC->SelectObject(hBrush);
		pDC->Rectangle(rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top);
	}

	if (IsIconic())
	{
		CPaintDC dc(this); // контекст устройства для рисования

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Выравнивание значка по центру клиентского прямоугольника
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Нарисуйте значок
		dc.DrawIcon(x, y, m_hIcon);

		
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// Система вызывает эту функцию для получения отображения курсора при перемещении
//  свернутого окна.
HCURSOR CprTextCardDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CprTextCardDlg::OnBnClickedButmashsh()
{
	// TODO: добавьте свой код обработчика уведомлений
	OnCancel();
	CMashCard openDialog;
	openDialog.DoModal();
}

void CprTextCardDlg::OnBnClickedButmashcard()
{
	// TODO: добавьте свой код обработчика уведомлений
	OnCancel();
	CTechCard openDialog;
	openDialog.DoModal();
}

void CprTextCardDlg::OnBnClickedButmashshtxt()
{
	// TODO: добавьте свой код обработчика уведомлений
	OnBnClickedButmashsh();
}

void CprTextCardDlg::OnBnClickedButmashcardtxt()
{
	// TODO: добавьте свой код обработчика уведомлений
	OnBnClickedButmashcard();
}