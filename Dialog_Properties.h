#pragma once


// Dialog_Properties dialog

class Dialog_Properties : public CDialogEx
{
	DECLARE_DYNAMIC(Dialog_Properties)

public:
	Dialog_Properties(CWnd* pParent = nullptr);   // standard constructor
	virtual ~Dialog_Properties();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_PROPERTIES };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
//	CEdit test;
//	CButton m_getdate;
	CButton m_get_data;
	afx_msg void OnBnClickedButtonGetData();
	CString text;
//	virtual INT_PTR DoModal();
//	virtual BOOL ContinueModal();
	CEdit m_edit_x;
	int value_x;
	int value_y;
	CEdit m_edit_y;
	bool firstTime = true;
	virtual BOOL ContinueModal();
	afx_msg void OnEnChangeEdit6();
//	CEdit m_R;
//	CEdit m_R;
//	CEdit m_G;
//	CEdit m_B;
	CEdit m_outline_R;
	CEdit m_outline_G;
	CEdit m_outline_B;
	int value_outline_R;
	int value_outline_G;
	int value_outline_B;
	CEdit m_degree;
	CEdit m_id;
	CEdit m_name;
	int value_degree;
	int value_id;
	CString value_name;
	CEdit m_fill_R;
	CEdit m_fill_G;
	CEdit m_fill_B;
	int value_fill_R;
	int value_fill_G;
	int value_fill_B;
};
