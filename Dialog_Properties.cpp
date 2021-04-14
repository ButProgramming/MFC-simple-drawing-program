// Dialog_Properties.cpp : implementation file
//

#include "pch.h"
#include "EgoSecure_Test_Assignment.h"
#include "Dialog_Properties.h"
#include "afxdialogex.h"


// Dialog_Properties dialog

IMPLEMENT_DYNAMIC(Dialog_Properties, CDialogEx)

Dialog_Properties::Dialog_Properties(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_PROPERTIES, pParent)
{

}

Dialog_Properties::~Dialog_Properties()
{
}

void Dialog_Properties::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//  DDX_Control(pDX, IDC_EDIT1, test);
	//  DDX_Control(pDX, IDC_BUTTON_GET_DATA, m_getdate);
	DDX_Control(pDX, IDC_BUTTON_GET_DATA, m_get_data);
	DDX_Control(pDX, IDC_EDIT_X, m_edit_x);
	DDX_Control(pDX, IDC_EDITY, m_edit_y);
	//  DDX_Control(pDX, IDC_EDIT4, m_R);
	//  DDX_Control(pDX, IDC_EDIT_R, m_R);
	//  DDX_Control(pDX, IDC_EDIT_G, m_G);
	//  DDX_Control(pDX, IDC_EDIT_B, m_B);
	DDX_Control(pDX, IDC_EDIT_OUTLINE_R, m_outline_R);
	DDX_Control(pDX, IDC_EDIT_OUTLINE_G, m_outline_G);
	DDX_Control(pDX, IDC_EDIT_OUTLINE_B, m_outline_B);
	DDX_Control(pDX, IDC_EDIT_DEGREE, m_degree);
	DDX_Control(pDX, IDC_EDIT_ID, m_id);
	DDX_Control(pDX, IDC_EDIT_NAME, m_name);
	DDX_Control(pDX, IDC_EDIT_OUTLINE_R2, m_fill_R);
	DDX_Control(pDX, IDC_EDIT_OUTLINE_G2, m_fill_G);
	DDX_Control(pDX, IDC_EDIT_OUTLINE_B2, m_fill_B);
	DDX_Control(pDX, IDC_COMBO1, m_cb_outline_size);
	//  DDX_Control(pDX, IDC_COMBO2, m_outline_type);
	DDX_Control(pDX, IDC_COMBO2, m_cb_outline_type);
	DDX_Control(pDX, IDC_COMBO3, m_cb_fill_type);
}


BEGIN_MESSAGE_MAP(Dialog_Properties, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_GET_DATA, &Dialog_Properties::OnBnClickedButtonGetData)
	//ON_EN_CHANGE(IDC_EDIT6, &Dialog_Properties::OnEnChangeEdit6)
END_MESSAGE_MAP()


// Dialog_Properties message handlers


void Dialog_Properties::OnBnClickedButtonGetData()
{
	
	// TODO: Add your control notification handler code here
}


//INT_PTR Dialog_Properties::DoModal()
//{
//	// TODO: Add your specialized code here and/or call the base class
//	//OnBnClickedButtonGetData();
//	//text.Format(_T("111"));
//	return CDialogEx::DoModal();
//}


//BOOL Dialog_Properties::ContinueModal()
//{
//	// TODO: Add your specialized code here and/or call the base class
	//test.SetWindowTextW(text);
	//return CDialogEx::ContinueModal();
//}


BOOL Dialog_Properties::ContinueModal()
{
	// TODO: Add your specialized code here and/or call the base class
	if (firstTime)
	{
		CString str;
		str.Format(_T("%d"), value_x);
		m_edit_x.SetWindowTextW(str);
		str.Format(_T("%d"), value_y);
		m_edit_y.SetWindowTextW(str);
		str.Format(_T("%d"), value_outline_R);
		m_outline_R.SetWindowTextW(str);
		str.Format(_T("%d"), value_outline_G);
		m_outline_G.SetWindowTextW(str);
		str.Format(_T("%d"), value_outline_B);
		m_outline_B.SetWindowTextW(str);
		str.Format(_T("%d"), value_fill_R);
		m_fill_R.SetWindowTextW(str);
		str.Format(_T("%d"), value_fill_G);
		m_fill_G.SetWindowTextW(str);
		str.Format(_T("%d"), value_fill_B);
		m_fill_B.SetWindowTextW(str);
		str.Format(_T("%d"), value_degree);
		m_degree.SetWindowTextW(str);
		str.Format(_T("%d"), value_id);
		m_id.SetWindowTextW(str);
		m_name.SetWindowTextW(value_name);
		str.Format(_T("%d"), value_outline_size);
		m_cb_outline_size.SetCurSel(value_outline_size);
		m_cb_outline_type.SetCurSel(value_outline_type);
		m_cb_fill_type.SetCurSel(value_fill_type+1);
		firstTime = false;
	}
	return CDialogEx::ContinueModal();
}


void Dialog_Properties::OnEnChangeEdit6()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
}
