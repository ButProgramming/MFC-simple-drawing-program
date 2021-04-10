// Default_config.cpp : implementation file
//

#include "pch.h"
#include "EgoSecure_Test_Assignment.h"
#include "Default_config.h"
#include "afxdialogex.h"


// Default_config dialog

IMPLEMENT_DYNAMIC(Default_config, CDialogEx)

Default_config::Default_config(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DEFAULT_CONFIG, pParent)
{

}

Default_config::~Default_config()
{
}

void Default_config::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, combo_test);
}


BEGIN_MESSAGE_MAP(Default_config, CDialogEx)
	ON_CBN_SELCHANGE(IDC_COMBO1, &Default_config::OnCbnSelchangeCombo1)
END_MESSAGE_MAP()


// Default_config message handlers


void Default_config::OnCbnSelchangeCombo1()
{
	// TODO: Add your control notification handler code here
}
