#pragma once
#include "EgoSecure_Test_AssignmentDoc.h"

// Dialog_Link_Properties dialog

class Dialog_Link_Properties : public CDialogEx
{
	DECLARE_DYNAMIC(Dialog_Link_Properties)

public:
	Dialog_Link_Properties(CEgoSecureTestAssignmentDoc* pDoc,CWnd* pParent = nullptr);   // standard constructor
	virtual ~Dialog_Link_Properties();
	// control continueModal
	bool callcallFirstTime = true;
	virtual BOOL ContinueModal();
	afx_msg void OnBnClickedOk();
	void getParameters(int shapeNum);
	void setParameters(int shapeNum);

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_PROPERTIES_LINK };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
	
private:
	CEgoSecureTestAssignmentDoc* pDoc = nullptr;
	CEdit eLinkColorR;
	CEdit eLinkColorG;
	CEdit eLinkColorB;
	int nLinkColorR = NULL;
	int nLinkColorG = NULL;
	int nLinkColorB = NULL;	
	CEdit eLinkFirstPoint;
	CEdit eLinkSecondPoint;
	CPoint nLinkFirstPointStart{ NULL, NULL };
	CPoint nLinkSecondPointStart{ NULL, NULL };
	CPoint nLinkFirstPoint { NULL, NULL };
	CPoint nLinkSecondPoint{ NULL, NULL };
	CComboBox bLinkSize;
	CComboBox bLinkType;
	int nLinkSize = 1;
	int nLinkType = NULL;
	CComboBox bLinkTypeLink;
	int nLinkTypeLink = NULL;
	CEdit eLinkID;
	CEdit eLinkName;
	int nLinkID = NULL;
	CString name;

};
