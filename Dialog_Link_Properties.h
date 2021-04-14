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
	int value_link_color_R = 0;
	int value_link_color_G = 0;
	int value_link_color_B = 0;

	virtual BOOL ContinueModal();
	CEdit m_link_shape_first_id;
	CEdit m_link_shape_second_id;
	int value_link_shape_first_id = -1;
	int value_link_shape_second_id = -1;
//	CComboBox m_link_size;
	CComboBox m_cb_link_size;
	CComboBox m_cb_link_type;
	int value_link_size = 1;
	int value_link_type = 0;
//	CComboBox m_link_type_link;
	CComboBox m_cb_link_type_link;
	int value_link_type_link;
};
