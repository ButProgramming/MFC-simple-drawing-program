#pragma once


// Default_draw_properties dialog

class Default_draw_properties : public CDialogEx
{
	DECLARE_DYNAMIC(Default_draw_properties)

public:
	Default_draw_properties(CWnd* pParent = nullptr);   // standard constructor
	virtual ~Default_draw_properties();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_DEFAULT_DRAW_PROPERTIES };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CMFCColorButton m_color_outline;
	CMFCColorButton m_color_fill;
	COLORREF m_color_outline_COLORREF;
	COLORREF m_color_fill_COLORREF;

	afx_msg void OnBnClickedOk();
//	CMFCColorButton m_fill_color;
	
//	CComboBox m_combobox_outline;
	CComboBox m_cb_outline_size;
	int num_cb_outline_size;
	CComboBox m_cb_outline_type;
	int num_cb_outline_type;
	CComboBox m_cb_fill_type;
	int num_cb_fill_type;
};
