#pragma once
#include "afxwin.h"
#include "afxcmn.h"


// ���������� ���� CMashCard

class CMashCard : public CDialog
{
	DECLARE_DYNAMIC(CMashCard)

public:
	CMashCard(CWnd* pParent = NULL);   // ����������� �����������
	virtual ~CMashCard();
	CprTextCardApp* m_pDoc;

// ������ ����������� ����
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MashCard };
#endif
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // ��������� DDX/DDV
	
protected:

	// ��������� ������� ����� ���������
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	
	DECLARE_MESSAGE_MAP()
public:
	int listItem;//������ ����� ���������� ������
	int but;//���������� � ����� ���� ���� ���������� ��������
	bool faq;
	int openDef;//���������� ������ ������ � ��� ���� �� ��� ������� Inventor

	_bstr_t strTemplateFilenameBOM;//���������� ������ ���� � ����� ������ ���������
	_bstr_t strTemplateFilename;//���������� ������ ���� � ������� ����� ���������

	CString strDocFormat;//������ ����� �����

	int orientationDoc;//������ ���������� ���������
	int numFirst;//�������� ������
	int numPlace;
	int numPlaceLev;
	double xLast;//���� � ���� ������������ ��������
	double y0;//������� ����� �����
	double xMax;//���� ���� �

	double firstElX;//� ���������� ������� ����� �������
	double firstElY;//� ���������� ������� ����� �������
	double secondElX;//� ���������� ������� ����� �������
	double secondElY;//� ���������� ������� ����� �������

	CArray<double, double> sqCoordSbX;//x ���������� ����� ������
	CArray<double, double> sqCoordSbY;//� ���������� �����
	CArray<int, int> orientBloc;//���������� �����
	CArray<_bstr_t, CString> sqPosText;
	CArray<_bstr_t, CString> sqNumText;
	CArray<_bstr_t, CString> sqNameText;

	CArray<double, double> lineCoordX;
	CArray<double, double> lineCoordY;

	CArray<double, double> coordMarkX;//x ����������
	CArray<double, double> coordMarkY;//� ����������
	CArray<_bstr_t, CString> markText;
	CArray<int, int> orientMark;//���������� �����
	CArray<int, int> typeMark;//

	CArray<CString, CString> sqPos;
	CArray<int, int> orientEl;
	CArray<int, int> elIdM;
	CArray<double, double> coordElX;
	CArray<double, double> coordElY;

	//���������� ��������� ����������
	CBitmapButton m_butOpenSave;
	CBitmapButton m_butSaveMake;
	CBitmapButton m_butLoadSb;

	CBitmapButton m_butAdd1;
	CBitmapButton m_butChange1;
	CBitmapButton m_butDel1;

	CBitmapButton m_butAdd2;
	CBitmapButton m_butChange2;
	CBitmapButton m_butDel2;

	CBitmapButton m_butChangeDlg;

	CComboBox m_cbMark;
	CComboBox m_cbView;
	CComboBox m_cbPutOn;
	CComboBox m_cbNameF;
	CComboBox m_cbPosF;
	CComboBox m_cbFormList;

	CButton m_rbGor;
	CButton m_rbVer;

	CButton m_AddNote;
	CButton m_butBack;
	CButton m_butAddNote2;
	CButton m_butBack2;

	CEdit m_edNameF;
	CEdit m_edPosF;
	CEdit m_edNumF;
	CEdit m_edSbName;
	
	CListCtrl m_listCtrl;//������ ������ � ��������
	CListCtrl m_listCtrl2;//������ ������ � ������

	CStatic m_stNameF;
	CStatic m_PosF;
	CStatic m_NumF;
	CStatic m_View;
	CStatic m_PutOn;
	CStatic m_AddMark;
	CStatic m_stEdSbName;

	afx_msg void OnBnClickedButopensave();
	afx_msg void OnBnClickedButsavemake();
	afx_msg void OnBnClickedButloadsb();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedButadd1();
	afx_msg void OnBnClickedButadd2();
	afx_msg void OnBnClickedButchange1();
	afx_msg void OnBnClickedButchange2();
	afx_msg void OnBnClickedButdel1();
	afx_msg void OnBnClickedButdel2();
	afx_msg void OnBnClickedAddnote();
	afx_msg void OnBnClickedbutback();
	afx_msg void OnBnClickedAddnote2();
	afx_msg void OnBnClickedbutback2();
	afx_msg void OnBnClickedButtonchangedlg();

	void MakeDlgBkColor();

	void MakeDoc();//���� ���������
	void MakeCoord();//����������� ���������� ���������

	void MakeSb(int pos, int id);//������ ��������� ������
	void MakeSb2();
	void MakeDet(int pos, int id);//������ ��������� ����� ������
	void MakeTextSb(int id, int numBloc, int type);//������� ������ � ����

	void InitVarFormat();//������������� ��� ���������

	void DelVar();//������� �������� ��������

	void FindPlace(int id, int pos);//������ �������������� ���������
	void makeLineCoord(double x1, double y1, double x2, double y2);
	void makeMarkCoord(double x, double y, CString text, int orientation, int t);
};
