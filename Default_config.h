#pragma once


// Default_config dialog

class Default_config : public CDialogEx
{
	DECLARE_DYNAMIC(Default_config)

public:
	Default_config(CWnd* pParent = nullptr);   // standard constructor
	virtual ~Default_config();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DEFAULT_CONFIG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CComboBox combo_test;
	afx_msg void OnCbnSelchangeCombo1();
};
