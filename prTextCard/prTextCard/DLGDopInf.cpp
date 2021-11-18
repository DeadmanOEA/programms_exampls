// DLGDopInf.cpp: файл реализации
//

#include "stdafx.h"
#include "prTextCard.h"
#include "DLGDopInf.h"
#include "afxdialogex.h"


// диалоговое окно CDLGDopInf

IMPLEMENT_DYNAMIC(CDLGDopInf, CDialog)

CDLGDopInf::CDLGDopInf(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_DIALOGDopInf, pParent)
{

}

CDLGDopInf::~CDLGDopInf()
{
}

void CDLGDopInf::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_edUser);
	DDX_Control(pDX, IDC_EDIT2, m_edCheck);
	DDX_Control(pDX, IDC_EDIT3, m_edHasAccepted);
	DDX_Control(pDX, IDC_EDIT5, m_edApproved);
	DDX_Control(pDX, IDC_EDIT4, m_edNKontr);
	DDX_Control(pDX, IDC_EDIT6, m_edAddInfo);
	DDX_Control(pDX, IDC_EDIT7, m_edDesignationNumDoc);
	DDX_Control(pDX, IDC_EDIT8, m_edDesignationMainDoc);
	DDX_Control(pDX, IDC_EDIT9, m_edNumQuantity);
	DDX_Control(pDX, IDC_EDIT10, m_edSequenceNumberSheet);
	DDX_Control(pDX, IDC_EDIT11, m_edNameCompony);
	DDX_Control(pDX, IDC_EDIT12, m_edProductDesignations);
	DDX_Control(pDX, IDC_EDIT13, m_edClassificationGroupCode);
	DDX_Control(pDX, IDC_EDIT14, m_edDocumentDesignations);
	DDX_Control(pDX, IDC_EDIT15, m_edLiteraLeft);
	DDX_Control(pDX, IDC_EDIT16, m_edLiteraCentr);
	DDX_Control(pDX, IDC_EDIT17, m_edLiteraRight);
	DDX_Control(pDX, IDC_EDIT18, m_edName);
	DDX_Control(pDX, IDC_EDIT19, m_edStandardizationUnit);
}

BEGIN_MESSAGE_MAP(CDLGDopInf, CDialog)
	ON_BN_CLICKED(IDOK, &CDLGDopInf::OnBnClickedOk)
	ON_WM_PAINT()
END_MESSAGE_MAP()

// обработчики сообщений CDLGDopInf

void CDLGDopInf::OnPaint()
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

void CDLGDopInf::OnBnClickedOk()
{
	CprTextCardApp* pApp = (CprTextCardApp*)AfxGetApp();
	m_edUser.GetWindowTextW(pApp->m_edUser);
	m_edCheck.GetWindowTextW(pApp->m_edCheck);
	m_edHasAccepted.GetWindowTextW(pApp->m_edHasAccepted);
	m_edApproved.GetWindowTextW(pApp->m_edApproved);
	m_edNKontr.GetWindowTextW(pApp->m_edNKontr);
	m_edAddInfo.GetWindowTextW(pApp->m_edAddInfo);
	m_edDesignationNumDoc.GetWindowTextW(pApp->m_edDesignationNumDoc);
	m_edDesignationMainDoc.GetWindowTextW(pApp->m_edDesignationMainDoc);
	m_edNumQuantity.GetWindowTextW(pApp->m_edNumQuantity);
	m_edSequenceNumberSheet.GetWindowTextW(pApp->m_edSequenceNumberSheet);
	m_edNameCompony.GetWindowTextW(pApp->m_edNameCompony);
	m_edProductDesignations.GetWindowTextW(pApp->m_edProductDesignations);
	m_edClassificationGroupCode.GetWindowTextW(pApp->m_edClassificationGroupCode);
	m_edDocumentDesignations.GetWindowTextW(pApp->m_edDocumentDesignations);
	m_edLiteraLeft.GetWindowTextW(pApp->m_edLiteraLeft);
	m_edLiteraCentr.GetWindowTextW(pApp->m_edLiteraCentr);
	m_edLiteraRight.GetWindowTextW(pApp->m_edLiteraRight);
	m_edName.GetWindowTextW(pApp->m_edName);
	m_edStandardizationUnit.GetWindowTextW(pApp->m_edStandardizationUnit);
	CDialog::OnOK();
}

void CDLGDopInf::BackTextEd()
{
	CprTextCardApp* pApp = (CprTextCardApp*)AfxGetApp();
	m_edUser.SetWindowTextW(pApp->m_edUser);
	m_edCheck.SetWindowTextW(pApp->m_edCheck);
	m_edHasAccepted.SetWindowTextW(pApp->m_edHasAccepted);
	m_edApproved.SetWindowTextW(pApp->m_edApproved);
	m_edNKontr.SetWindowTextW(pApp->m_edNKontr);
	m_edAddInfo.SetWindowTextW(pApp->m_edAddInfo);
	m_edDesignationNumDoc.SetWindowTextW(pApp->m_edDesignationNumDoc);
	m_edDesignationMainDoc.SetWindowTextW(pApp->m_edDesignationMainDoc);
	m_edNumQuantity.SetWindowTextW(pApp->m_edNumQuantity);
	m_edSequenceNumberSheet.SetWindowTextW(pApp->m_edSequenceNumberSheet);
	m_edNameCompony.SetWindowTextW(pApp->m_edNameCompony);
	m_edProductDesignations.SetWindowTextW(pApp->m_edProductDesignations);
	m_edClassificationGroupCode.SetWindowTextW(pApp->m_edClassificationGroupCode);
	m_edDocumentDesignations.SetWindowTextW(pApp->m_edDocumentDesignations);
	m_edLiteraLeft.SetWindowTextW(pApp->m_edLiteraLeft);
	m_edLiteraCentr.SetWindowTextW(pApp->m_edLiteraCentr);
	m_edLiteraRight.SetWindowTextW(pApp->m_edLiteraRight);
	m_edName.SetWindowTextW(pApp->m_edName);
	m_edStandardizationUnit.SetWindowTextW(pApp->m_edStandardizationUnit);

	/*Стандартый текст*/
	m_edUser.SetWindowTextW(L"Копылов Д.А.");
	m_edUser.LimitText(18);
	m_edCheck.SetWindowTextW(L"Толстиков А.В.");
	m_edCheck.LimitText(18);
	m_edHasAccepted.SetWindowTextW(L"Каволёва А.А.");
	m_edHasAccepted.LimitText(18);
	m_edNKontr.SetWindowTextW(L"Толстиков А.В.");
	m_edNKontr.LimitText(18);
	m_edApproved.SetWindowTextW(L"Каволёва А.А.");
	m_edApproved.LimitText(18);

	m_edAddInfo.SetWindowTextW(L"1. Дополнительная информация при сброке...");
	m_edAddInfo.LimitText(29);
	m_edDesignationNumDoc.SetWindowTextW(L"ХХХХ.ХХХХХХ.ХХХ");
	m_edDesignationNumDoc.LimitText(13);
	m_edDesignationMainDoc.SetWindowTextW(L"АБВГ.ХХХХХХ.ХХХ");
	m_edDesignationMainDoc.LimitText(15);
	m_edNumQuantity.SetWindowTextW(L"1");
	m_edNumQuantity.LimitText(2);
	m_edSequenceNumberSheet.SetWindowTextW(L"2");
	m_edSequenceNumberSheet.LimitText(2);

	m_edNameCompony.SetWindowTextW(L"МПУ");
	m_edNameCompony.LimitText(6);
	m_edProductDesignations.SetWindowTextW(L"Сборка Верстачные тиски");
	m_edProductDesignations.LimitText(16);
	m_edClassificationGroupCode.SetWindowTextW(L"ХХХХХХ.ХХХ");
	m_edClassificationGroupCode.LimitText(9);
	m_edDocumentDesignations.SetWindowTextW(L"ХХХХХХ.ХХХ");
	m_edDocumentDesignations.LimitText(12);
	m_edLiteraLeft.SetWindowTextW(L"А");
	m_edLiteraLeft.LimitText(3);
	m_edLiteraCentr.SetWindowTextW(L"Э");
	m_edLiteraCentr.LimitText(3);
	m_edLiteraRight.SetWindowTextW(L"Т");
	m_edLiteraRight.LimitText(3);
	m_edName.SetWindowTextW(L"Верстачные тиски");
	m_edName.LimitText(22);
	m_edStandardizationUnit.SetWindowTextW(L"833");
	m_edStandardizationUnit.LimitText(6);
}