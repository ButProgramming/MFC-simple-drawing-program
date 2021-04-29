#pragma once


// Dialog_Link_Properties dialog

class Dialog_Link_Properties : public CDialogEx
{
	DECLARE_DYNAMIC(Dialog_Link_Properties)

public:
	Dialog_Link_Properties(CWnd* pParent = nullptr);   // standard constructor
	virtual ~Dialog_Link_Properties();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_PROPERTIES_LINK };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	// control continueModal
	bool callFirstTime = true;
	virtual BOOL ContinueModal();
	afx_msg void OnBnClickedOk();
private:

	CEdit eLinkColorR;
	CEdit eLinkColorG;
	CEdit eLinkColorB;
	int nLinkColorR = NULL;
	int nLinkColorG = NULL;
	int nLinkColorB = NULL;

	
	CEdit eLinkShapeFirstID;
	CEdit eLinkShapeSecondID;
	int nLinkShapeFirstID = -1;
	int nLinkShapeSecondID = -1;
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
