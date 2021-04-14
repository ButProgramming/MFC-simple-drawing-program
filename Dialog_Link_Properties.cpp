// Dialog_Link_Properties.cpp : implementation file
//

#include "pch.h"
#include "EgoSecure_Test_Assignment.h"
#include "Dialog_Link_Properties.h"
#include "afxdialogex.h"


// Dialog_Link_Properties dialog

IMPLEMENT_DYNAMIC(Dialog_Link_Properties, CDialogEx)

Dialog_Link_Properties::Dialog_Link_Properties(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_PROPERTIES_LINK, pParent)
{

}

Dialog_Link_Properties::~Dialog_Link_Properties()
{
}

void Dialog_Link_Properties::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_LINK_COLOR_R, m_link_color_R);
	DDX_Control(pDX, IDC_EDIT_LINK_COLOR_G, m_link_color_G);
	DDX_Control(pDX, IDC_EDIT_LINK_COLOR_B, m_link_color_B);
}


BEGIN_MESSAGE_MAP(Dialog_Link_Properties, CDialogEx)
END_MESSAGE_MAP()


// Dialog_Link_Properties message handlers


BOOL Dialog_Link_Properties::ContinueModal()
{
	// TODO: Add your specialized code here and/or call the base class
	if (firstTime)
	{
		CString str;
		str.Format(_T("%d"), value_link_color_R);
		m_link_color_R.SetWindowTextW(str);
		firstTime = false;
	}
	return CDialogEx::ContinueModal();
}
