#pragma once


// DialogTest dialog

class DialogTest : public CDialogEx
{
	DECLARE_DYNAMIC(DialogTest)

public:
	DialogTest(CWnd* pParent = nullptr);   // standard constructor
	virtual ~DialogTest();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CComboBox combo_box_1;
	CComboBoxEx combo_box_2;
	afx_msg void OnSelchangeCombo1();
	afx_msg void OnCbnSelchangeComboboxex1();
	afx_msg void OnBnClickedButton1();
	CButton ButtonTest;
	afx_msg void OnStatic();
	CStatic static_text_test;
	CEdit edit_test;
	afx_msg void OnLvnItemchangedList4(NMHDR* pNMHDR, LRESULT* pResult);
};
