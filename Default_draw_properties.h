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
	
	CMFCColorButton m_color_outline;
	CMFCColorButton m_color_fill;
	CMFCColorButton m_color_link;
	COLORREF m_color_outline_COLORREF;
	COLORREF m_color_fill_COLORREF;
	COLORREF m_color_link_COLORREF;

	afx_msg void OnBnClickedOk();
//	CMFCColorButton m_fill_color;
	
//	CComboBox m_combobox_outline;
	CComboBox m_cb_outline_size;
	int num_cb_outline_size = 2;
	CComboBox m_cb_outline_type;
	int num_cb_outline_type = 0;
	CComboBox m_cb_fill_type;
	int num_cb_fill_type = -1;
	//void SetDataDefaultDrawProperties();
	
	CComboBox m_cb_link_type;
	int num_cb_link_type = 0;
	CComboBox m_cb_line_size;
	int num_cb_line_size = 1; 
	virtual BOOL ContinueModal();

	//
	bool firstTime = true;
	COLORREF value_color;
	void getParameters();
	void setParameters();
};
