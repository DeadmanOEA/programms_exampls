#pragma once
#include "afxwin.h"
#include "afxcmn.h"


// ���������� ���� CTechCard

class CTechCard : public CDialog
{
	DECLARE_DYNAMIC(CTechCard)

public:
	CTechCard(CWnd* pParent = NULL);   // ����������� �����������
	virtual ~CTechCard();
	CprTextCardApp* m_pDoc;

// ������ ����������� ����
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TechCard };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // ��������� DDX/DDV

	
protected:
	afx_msg void OnPaint();
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()

public:
	bool faq;
	//Det
	CListCtrl m_listCtrl;
	//Sxema
	CListCtrl m_lcMain;
	CBitmapButton m_butAddTb;
	CBitmapButton m_butChangeTb;
	CBitmapButton m_butDelTb;
	//���������� ��������� ����������
	//�
	CStatic m_stCodeWorkshop;
	CStatic m_stCodePlot;
	CStatic m_stNumWorkplase;
	CStatic m_stNumOperation;
	CStatic m_stNameOperation;
	CEdit m_edCodeWorkshop;
	CEdit m_edCodePlot;
	CEdit m_edNumWorkplase;
	CEdit m_edNumOperation;
	CComboBox m_cbNameOperation;
	//�
	CStatic m_stCodeNameEquipment;
	CStatic m_stDagreeMech;
	CStatic m_stCodProf;
	CStatic m_stRank;
	CStatic m_stLaborCode;
	CStatic m_stNumPerfomens;
	CStatic m_stNumManuf;
	CStatic m_stStrUnit;
	CStatic m_stBatchSize;
	CStatic m_stPieseTime;
	CStatic m_stNormFinalTime;
	CStatic m_stNormTime;
	CEdit m_edCodeNameEquipment;
	CEdit m_edDagreeMech;
	CEdit m_edCodProf;
	CEdit m_edRank;
	CEdit m_edLaborCode;
	CEdit m_edNumPerfomens;
	CEdit m_edNumManuf;
	CEdit m_edStrUnit;
	CEdit m_edBatchSize;
	CEdit m_edPieseTime;
	CEdit m_edNormFinalTime;
	CEdit m_edNormTime;
	//� �
	CStatic m_stNameDetail;
	CStatic m_stDesignationCode;
	CStatic m_stDivisionDesignation;
	CStatic m_stUnitCode;
	CStatic m_stAmountData;
	CStatic m_stConsumptionRate;
	CEdit m_edNameMaterial;
	CEdit m_edDesignationCode;
	CEdit m_edDivisionDesignation;
	CEdit m_edUnitCode;
	CEdit m_edAmountData;
	CEdit m_edConsumptionRate;
	CComboBox m_cbNameDetail;
	//�
	CListCtrl m_listO1;
	CListCtrl m_listO2;
	CListCtrl m_listO3;
	CListCtrl m_listO4;
	CButton m_butOBut;
	CEdit m_edOEd;
	CButton m_butO2;
	//�
	CStatic m_stAccessoriesAuxiliaryTool;
	CEdit m_edAccessoriesAuxiliaryTool;
	//
	CBitmapButton m_butOpenSave;
	CBitmapButton m_butSaveMake;
	CBitmapButton m_butLoadSb;
	CBitmapButton m_butChangeDlg;

	afx_msg void OnBnClickedButopensave2();
	afx_msg void OnBnClickedButsavemake2();
	afx_msg void OnBnClickedButloadsb2();
	void OnBnClickedButtonchangedlg2();
	afx_msg void OnBnClickedOk();
	void AddTextCar(double x, double y, CString text, int list);
	void DelVar();
	void MakeDoc();
	void AllEdText();
	void MakeTableText();
	afx_msg void OnBnClickedButtona();
	afx_msg void OnBnClickedButtonk();
	afx_msg void OnBnClickedButtono();
	afx_msg void OnBnClickedButtonb();
	afx_msg void OnBnClickedButtonm();
	afx_msg void OnBnClickedButtont();
	afx_msg void OnBnClickedButtondopinf();
	afx_msg void OnBnClickedButtonclean();
	afx_msg void OnBnClickedButtonobut();
	afx_msg void OnBnClickedButtono2();

	int ClickOff;// ���������� ��� ��������� ��������� �������� ��� ������� �� ������
	int openDef;
	int ListItem;// ������ ����� ���������� ������
	int VarBut;// ���������� ��� ���������� �������� � ��� ���������
	_bstr_t strTemplateFilenameBOM;//���������� ������ ���� � ����� ������ ���������
	_bstr_t strTemplateFilename;//���������� ������ ���� � ������� ����� ���������

	void openDb();// �������� � �������� �� ���� ������

	CButton m_buA;
	CButton m_buB;
	CButton m_buK;
	CButton m_buM;
	CButton m_buO;
	CButton m_buT;

	void MakeDlgBkColor();

	afx_msg void OnBnClickedButtonaddtb();
	afx_msg void OnBnClickedButtonchange();
	afx_msg void OnBnClickedButtondel();

	void AllStrText();

	int listText;

	double x0shem;
	double  y0shem;

	CArray<_bstr_t, CString> sqPos;
	CArray<double, double> coordX;
	CArray<double, double> coordY;
	CArray<int, int> listN;
	CStatic m_stDesignationDoc;
	CEdit m_edDesignationDoc;
	CStatic m_stEdNorm;
	CEdit m_edEdNorm;
};
