#pragma once


// диалоговое окно CDlgDetMake

class CDlgDetMake : public CDialog
{
	DECLARE_DYNAMIC(CDlgDetMake)

public:
	CDlgDetMake(CWnd* pParent = NULL);   // стандартный конструктор
	virtual ~CDlgDetMake();

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOGMakeNameDet};
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV

	DECLARE_MESSAGE_MAP()
public:
	bool faq;
	afx_msg void OnPaint();
	void DetailAssembly();
	CComboBox m_cbNameDetail;// Наименование детали
	CComboBox m_cbPositionDetail;// Позиция детали
	CEdit m_edDeatil;
	afx_msg void OnBnClickedButton6();
	afx_msg void OnBnClickedOk();
};
