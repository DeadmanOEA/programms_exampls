
// prTextCard.h : главный файл заголовка для приложения PROJECT_NAME
//

#pragma once

#ifndef __AFXWIN_H__
	#error "включить stdafx.h до включения этого файла в PCH"
#endif

#include "resource.h"		// основные символы


// CprTextCardApp:
// О реализации данного класса см. prTextCard.cpp
//

class CprTextCardApp : public CWinApp
{
public:
	CprTextCardApp();

// Переопределение
public:
	virtual BOOL InitInstance();

// Реализация
	DECLARE_MESSAGE_MAP()

public:
	void OpenInventor(); //функция открытия инвентора
	void MakeDocF(_bstr_t strTemplateFilename);

	void MakeSq(double fx, double fy, int orient); //построение блока//х координата блока, у координата блока, ориентация блока
	void MakeLn(double fx, double fy, double sx, double sy);//проведение линии между блоками//x координата первой точки, y координата первой точки, x координата второй точки, y координата второй точки
	void AddText(double x, double y, _bstr_t text, _bstr_t position, _bstr_t num, int orient);//вставка текста//x координата положения блока, у координата блока, название детали, позиция в спецификации, количество деталей, ориентация блока
	void MakeMark(double x, double y, _bstr_t text, int orient, int t);//Добавить пометку

	void OpenBOM(_bstr_t strTemplateFilenameBOM);//получает данные спецификации

	CArray<CString, CString> csPartName;
	CArray<CString, CString> csItemNumber;
	CArray<CString, CString> csItemQuantity;
	//
	CString m_edUser;
	CString m_edCheck;
	CString m_edHasAccepted;
	CString m_edApproved;
	CString m_edNKontr;
	CString m_edAddInfo;
	CString m_edDesignationNumDoc;
	CString m_edDesignationMainDoc;
	CString m_edNumQuantity;
	CString m_edSequenceNumberSheet;
	CString m_edNameCompony;
	CString m_edProductDesignations;
	CString m_edClassificationGroupCode;
	CString m_edDocumentDesignations;
	CString m_edLiteraLeft;
	CString m_edLiteraCentr;
	CString m_edLiteraRight;
	CString m_edName;
	CString m_edStandardizationUnit;

	CString m_cbNameDetail;
	CString m_edDeatil;
	void MakeSqMK();
	void MakeSqMKlist2();
	void MakeTxt(double x, double y, _bstr_t text);
	void MakeDoc1(_bstr_t strTemplateFilename);
};

extern CprTextCardApp theApp;