
// prTextCard.h : ������� ���� ��������� ��� ���������� PROJECT_NAME
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�������� stdafx.h �� ��������� ����� ����� � PCH"
#endif

#include "resource.h"		// �������� �������


// CprTextCardApp:
// � ���������� ������� ������ ��. prTextCard.cpp
//

class CprTextCardApp : public CWinApp
{
public:
	CprTextCardApp();

// ���������������
public:
	virtual BOOL InitInstance();

// ����������
	DECLARE_MESSAGE_MAP()

public:
	void OpenInventor(); //������� �������� ���������
	void MakeDocF(_bstr_t strTemplateFilename);

	void MakeSq(double fx, double fy, int orient); //���������� �����//� ���������� �����, � ���������� �����, ���������� �����
	void MakeLn(double fx, double fy, double sx, double sy);//���������� ����� ����� �������//x ���������� ������ �����, y ���������� ������ �����, x ���������� ������ �����, y ���������� ������ �����
	void AddText(double x, double y, _bstr_t text, _bstr_t position, _bstr_t num, int orient);//������� ������//x ���������� ��������� �����, � ���������� �����, �������� ������, ������� � ������������, ���������� �������, ���������� �����
	void MakeMark(double x, double y, _bstr_t text, int orient, int t);//�������� �������

	void OpenBOM(_bstr_t strTemplateFilenameBOM);//�������� ������ ������������

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