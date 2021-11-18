#pragma once
#include "afxwin.h"
#include "afxcmn.h"


// диалоговое окно CMashCard

class CMashCard : public CDialog
{
	DECLARE_DYNAMIC(CMashCard)

public:
	CMashCard(CWnd* pParent = NULL);   // стандартный конструктор
	virtual ~CMashCard();
	CprTextCardApp* m_pDoc;

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MashCard };
#endif
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV
	
protected:

	// Созданные функции схемы сообщений
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	
	DECLARE_MESSAGE_MAP()
public:
	int listItem;//хранит номер изменяемой строки
	int but;//переменная в какую табл идет добавление элемента
	bool faq;
	int openDef;//переменная хранит данные о том было ли уже запущен Inventor

	_bstr_t strTemplateFilenameBOM;//переменная хранит путь к файлу сборки инвентора
	_bstr_t strTemplateFilename;//переменная хранит путь к шаблону файла инвентора

	CString strDocFormat;//формат листа схемы

	int orientationDoc;//хранит ориентацию документа
	int numFirst;//основная деталь
	int numPlace;
	int numPlaceLev;
	double xLast;//знач х посл добавленного элемента
	double y0;//нулевая линия схемы
	double xMax;//макс знач х

	double firstElX;//х координата первого блока базовой
	double firstElY;//у координата первого блока базовой
	double secondElX;//х координата второго блока базовой
	double secondElY;//у координата второго блока базовой

	CArray<double, double> sqCoordSbX;//x координата блока текста
	CArray<double, double> sqCoordSbY;//у координата блока
	CArray<int, int> orientBloc;//ориентация блока
	CArray<_bstr_t, CString> sqPosText;
	CArray<_bstr_t, CString> sqNumText;
	CArray<_bstr_t, CString> sqNameText;

	CArray<double, double> lineCoordX;
	CArray<double, double> lineCoordY;

	CArray<double, double> coordMarkX;//x координата
	CArray<double, double> coordMarkY;//у координата
	CArray<_bstr_t, CString> markText;
	CArray<int, int> orientMark;//ориентация блока
	CArray<int, int> typeMark;//

	CArray<CString, CString> sqPos;
	CArray<int, int> orientEl;
	CArray<int, int> elIdM;
	CArray<double, double> coordElX;
	CArray<double, double> coordElY;

	//переменные элементов управления
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
	
	CListCtrl m_listCtrl;//первый список с деталями
	CListCtrl m_listCtrl2;//второй список с путями

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

	void MakeDoc();//созд документа
	void MakeCoord();//расчитывает координаты положения

	void MakeSb(int pos, int id);//расчет координат сборки
	void MakeSb2();
	void MakeDet(int pos, int id);//расчет координат блока детали
	void MakeTextSb(int id, int numBloc, int type);//вставка текста в блок

	void InitVarFormat();//инициализация нач координат

	void DelVar();//очистка массивов значений

	void FindPlace(int id, int pos);//расчет местоположения документа
	void makeLineCoord(double x1, double y1, double x2, double y2);
	void makeMarkCoord(double x, double y, CString text, int orientation, int t);
};
