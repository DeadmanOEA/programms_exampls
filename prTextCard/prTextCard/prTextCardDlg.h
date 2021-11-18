
// prTextCardDlg.h : файл заголовка
//

#pragma once
#include "afxwin.h"


// диалоговое окно CprTextCardDlg
class CprTextCardDlg : public CDialogEx
{
// Создание
public:
	CprTextCardDlg(CWnd* pParent = NULL);	// стандартный конструктор
// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PRTEXTCARD_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// поддержка DDX/DDV


// Реализация
protected:
	HICON m_hIcon;

	// Созданные функции схемы сообщений
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
