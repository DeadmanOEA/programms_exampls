#pragma once


// ���������� ���� CDlgDetMake

class CDlgDetMake : public CDialog
{
	DECLARE_DYNAMIC(CDlgDetMake)

public:
	CDlgDetMake(CWnd* pParent = NULL);   // ����������� �����������
	virtual ~CDlgDetMake();

// ������ ����������� ����
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOGMakeNameDet};
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // ��������� DDX/DDV

	DECLARE_MESSAGE_MAP()
public:
	bool faq;
	afx_msg void OnPaint();
	void DetailAssembly();
	CComboBox m_cbNameDetail;// ������������ ������
	CComboBox m_cbPositionDetail;// ������� ������
	CEdit m_edDeatil;
	afx_msg void OnBnClickedButton6();
	afx_msg void OnBnClickedOk();
};
