// DlgDetMake.cpp: файл реализации
//

#include "stdafx.h"
#include "prTextCard.h"
#include "DlgDetMake.h"
#include "afxdialogex.h"


// диалоговое окно CDlgDetMake

IMPLEMENT_DYNAMIC(CDlgDetMake, CDialog)

CDlgDetMake::CDlgDetMake(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_DIALOGMakeNameDet, pParent)
{

}

CDlgDetMake::~CDlgDetMake()
{
}

void CDlgDetMake::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, m_cbNameDetail);
	DDX_Control(pDX, IDC_COMBO2, m_cbPositionDetail);
	DDX_Control(pDX, IDC_EDIT1, m_edDeatil);
}


BEGIN_MESSAGE_MAP(CDlgDetMake, CDialog)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BUTTON6, &CDlgDetMake::OnBnClickedButton6)
	ON_BN_CLICKED(IDOK, &CDlgDetMake::OnBnClickedOk)
END_MESSAGE_MAP()


// обработчики сообщений CDlgDetMake


void CDlgDetMake::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: добавьте свой код обработчика сообщений
					   // Не вызывать CDialog::OnPaint() для сообщений рисования

	CRect rect;
	GetClientRect(&rect);
	CDC *pDC = this->GetDC();

	if (faq == false) {
		HBRUSH  hBrush;
		hBrush = CreateSolidBrush(RGB(255, 246, 158));
		pDC->SelectObject(hBrush);
		pDC->Rectangle(rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top);
		faq = true;
	}
}

void CDlgDetMake::DetailAssembly()
{
	CprTextCardApp* pApp = (CprTextCardApp*)AfxGetApp();
	for (int i = 0; i < pApp->csPartName.GetCount(); i++) {
		m_cbNameDetail.AddString(pApp->csPartName[i]);
		m_cbPositionDetail.AddString(pApp->csItemNumber[i]);
	}
}

/*Кнопка вставить*/
void CDlgDetMake::OnBnClickedButton6()
{
	CString text, text1, text2;
	m_edDeatil.GetWindowTextW(text);
	m_cbNameDetail.GetWindowTextW(text1);
	m_cbPositionDetail.GetWindowTextW(text2);
	text = text + text1 + L" (" + text2 + L")";

	m_edDeatil.SetWindowTextW(text);
}

/*Кнопка применить*/
void CDlgDetMake::OnBnClickedOk()
{
	CprTextCardApp* pApp = (CprTextCardApp*)AfxGetApp();
	m_edDeatil.GetWindowTextW(pApp->m_edDeatil);
	CDialog::OnOK();
}