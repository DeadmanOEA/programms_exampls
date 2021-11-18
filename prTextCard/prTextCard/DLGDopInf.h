#pragma once


// диалоговое окно CDLGDopInf

class CDLGDopInf : public CDialog
{
	DECLARE_DYNAMIC(CDLGDopInf)

public:
	CDLGDopInf(CWnd* pParent = NULL);   // стандартный конструктор
	virtual ~CDLGDopInf();

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOGDopInf };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
	bool faq;
	// Разработал
	CEdit m_edUser;
	// Проверил
	CEdit m_edCheck;
	// Принял
	CEdit m_edHasAccepted;
	// Утвердил
	CEdit m_edApproved;
	// Н. конрт.
	CEdit m_edNKontr;
	// Доп информация
	CEdit m_edAddInfo;
	// Обозанчения документа
	CEdit m_edDesignationNumDoc;
	// Обозанчения основного документа
	CEdit m_edDesignationMainDoc;
	// Общее количество листов
	CEdit m_edNumQuantity;
	// Порядковый номер листа
	CEdit m_edSequenceNumberSheet;
	// Наименование организации
	CEdit m_edNameCompony;
	// Обозначения изделия
	CEdit m_edProductDesignations;
	// Код классификационных групп
	CEdit m_edClassificationGroupCode;
	// Обозначения документа
	CEdit m_edDocumentDesignations;
	// Литера слева
	CEdit m_edLiteraLeft;
	// Литера по центру
	CEdit m_edLiteraCentr;
	// Литера справа
	CEdit m_edLiteraRight;
	// Наименование изделия
	CEdit m_edName;
	// Единица нормирования
	CEdit m_edStandardizationUnit;
	afx_msg void OnBnClickedOk();
	void BackTextEd();
};
