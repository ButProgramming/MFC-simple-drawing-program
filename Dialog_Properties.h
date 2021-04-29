#pragma once
#include <sstream>
#include <string>
#include <cstdlib>
#include "EgoSecure_Test_AssignmentDoc.h"
using namespace std;

// Dialog_Properties dialog

class Dialog_Properties : public CDialogEx
{
	DECLARE_DYNAMIC(Dialog_Properties)
private:
	CEgoSecureTestAssignmentDoc* pDoc = nullptr;

public:
	Dialog_Properties(CEgoSecureTestAssignmentDoc* pDoc ,CWnd* pParent = nullptr);   // standard constructor
	virtual ~Dialog_Properties();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_PROPERTIES };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	void getParameters(int numberOfShape);
	void setParameters(int numberOfShape);
	afx_msg void OnBnClickedButtonGetData();
	virtual BOOL ContinueModal();
	afx_msg void OnEnChangeEdit6();
private:
	
	CEdit editX;
	int nX = NULL;
	int nY = NULL;
	CEdit editY;
	bool callFirstTime = true;


	CEdit outlineR;
	CEdit outlineG;
	CEdit outlineB;
	int nOutlineR = NULL;
	int nOutlineG = NULL;
	int nOutlineB = NULL;
	CEdit editDegree;
	CEdit editID;
	CEdit editName;
	int nDegree = NULL;
	int nID = NULL;
	CString nName;
	CEdit editFillR;
	CEdit editFillG;
	CEdit editFillB;
	int nFillR = NULL;
	int nFillG = NULL;
	int nFillB = NULL;
	CComboBox bOutlineSize;
	int nOutlineSize = NULL;
	CComboBox bOutlineType;
	int nOutlineType = NULL;
	CComboBox bFillType;
	int nFillType = NULL;

};
