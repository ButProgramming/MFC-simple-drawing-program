#pragma once
#include "EgoSecure_Test_AssignmentDoc.h"

// Default_draw_properties dialog

class Default_draw_properties : public CDialogEx
{
	DECLARE_DYNAMIC(Default_draw_properties)
private:
	CEgoSecureTestAssignmentDoc* pDoc = nullptr;
public:
	Default_draw_properties(CEgoSecureTestAssignmentDoc* pDoc, CWnd* pParent = nullptr);   // standard constructor
	virtual ~Default_draw_properties();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_DEFAULT_DRAW_PROPERTIES };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	virtual BOOL ContinueModal();
	void getParameters();
	void setParameters();

private:
	CMFCColorButton bColorOutline;
	CMFCColorButton bColorFill;
	CMFCColorButton bColorLink;
	COLORREF colorOutline;
	COLORREF colorFill;
	COLORREF colorLink;
	CComboBox bOutlineSize;
	int nOutlineSize = 2;
	CComboBox bOutlineType;
	int nOutlineType = 0;
	CComboBox bFillType;
	int nFillType = -1;
	CComboBox bLinkType;
	int nLinkType = 0;
	CComboBox bLineSize;
	int nLineSize = 1;
	bool callcallFirstTime = true;
};
