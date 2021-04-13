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
	COLORREF m_color;
	afx_msg void OnBnClickedOk();
};
