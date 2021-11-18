#pragma once


// ���������� ���� CDLGDopInf

class CDLGDopInf : public CDialog
{
	DECLARE_DYNAMIC(CDLGDopInf)

public:
	CDLGDopInf(CWnd* pParent = NULL);   // ����������� �����������
	virtual ~CDLGDopInf();

// ������ ����������� ����
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOGDopInf };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // ��������� DDX/DDV

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
	bool faq;
	// ����������
	CEdit m_edUser;
	// ��������
	CEdit m_edCheck;
	// ������
	CEdit m_edHasAccepted;
	// ��������
	CEdit m_edApproved;
	// �. �����.
	CEdit m_edNKontr;
	// ��� ����������
	CEdit m_edAddInfo;
	// ����������� ���������
	CEdit m_edDesignationNumDoc;
	// ����������� ��������� ���������
	CEdit m_edDesignationMainDoc;
	// ����� ���������� ������
	CEdit m_edNumQuantity;
	// ���������� ����� �����
	CEdit m_edSequenceNumberSheet;
	// ������������ �����������
	CEdit m_edNameCompony;
	// ����������� �������
	CEdit m_edProductDesignations;
	// ��� ����������������� �����
	CEdit m_edClassificationGroupCode;
	// ����������� ���������
	CEdit m_edDocumentDesignations;
	// ������ �����
	CEdit m_edLiteraLeft;
	// ������ �� ������
	CEdit m_edLiteraCentr;
	// ������ ������
	CEdit m_edLiteraRight;
	// ������������ �������
	CEdit m_edName;
	// ������� ������������
	CEdit m_edStandardizationUnit;
	afx_msg void OnBnClickedOk();
	void BackTextEd();
};
