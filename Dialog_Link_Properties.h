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
	bool firstTime = true;


	CEdit m_link_color_R;
	CEdit m_link_color_G;
	CEdit m_link_color_B;
	int value_link_color_R;
	int value_link_color_G;
	int value_link_color_B;

	virtual BOOL ContinueModal();
};
