
// prTextCardDlg.h : ���� ���������
//

#pragma once
#include "afxwin.h"


// ���������� ���� CprTextCardDlg
class CprTextCardDlg : public CDialogEx
{
// ��������
public:
	CprTextCardDlg(CWnd* pParent = NULL);	// ����������� �����������
// ������ ����������� ����
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PRTEXTCARD_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// ��������� DDX/DDV


// ����������
protected:
	HICON m_hIcon;

	// ��������� ������� ����� ���������
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	bool faq;

	CBitmapButton m_butMashSh;
	CBitmapButton m_butMashCard;
	CBitmapButton m_butMashShTxt;
	CBitmapButton m_butMashCardTxt;

	afx_msg void OnBnClickedButmashsh();
	afx_msg void OnBnClickedButmashcard();
	afx_msg void OnBnClickedButmashshtxt();
	afx_msg void OnBnClickedButmashcardtxt();
};
