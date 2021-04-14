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
	DDX_Control(pDX, IDC_EDIT_LINK_SHAPE_FIRST_ID, m_link_shape_first_id);
	DDX_Control(pDX, IDC_EDIT_LINK_SHAPE_SECOND_ID, m_link_shape_second_id);
	//  DDX_Control(pDX, IDC_COMBO_LINK_SIZE, m_link_size);
	DDX_Control(pDX, IDC_COMBO_LINK_SIZE, m_cb_link_size);
	DDX_Control(pDX, IDC_COMBO_LINK_TYPE, m_cb_link_type);
	//  DDX_Control(pDX, IDC_COMBO_LINK_TYPE_LINK, m_link_type_link);
	DDX_Control(pDX, IDC_COMBO_LINK_TYPE_LINK, m_cb_link_type_link);
	DDX_Control(pDX, IDC_EDIT_LINK_ID, m_link_id);
	DDX_Control(pDX, IDC_EDIT_LINK_NAME, m_link_name);
}


BEGIN_MESSAGE_MAP(Dialog_Link_Properties, CDialogEx)
	ON_BN_CLICKED(IDOK, &Dialog_Link_Properties::OnBnClickedOk)
END_MESSAGE_MAP()


// Dialog_Link_Properties message handlers


BOOL Dialog_Link_Properties::ContinueModal()
{
	// TODO: Add your specialized code here and/or call the base class
	if (firstTime)
	{
		firstTime = false;
		CString str;
		// set R color
		str.Format(_T("%d"), value_link_color_R);
		m_link_color_R.SetWindowTextW(str);
		// set G color
		str.Format(_T("%d"), value_link_color_G);
		m_link_color_G.SetWindowTextW(str);
		// set B color
		str.Format(_T("%d"), value_link_color_B);
		m_link_color_B.SetWindowTextW(str);
		// set first shape id
		str.Format(_T("%d"), value_link_shape_first_id);
		m_link_shape_first_id.SetWindowTextW(str);
		// set second shape id
		str.Format(_T("%d"), value_link_shape_second_id);
		m_link_shape_second_id.SetWindowTextW(str);
		// set link size
		m_cb_link_size.SetCurSel(value_link_size);
		// set link type (__, ..., _.._, ...)
		m_cb_link_type.SetCurSel(value_link_type);
		// set link type (basic, right, left, double)
		m_cb_link_type_link.SetCurSel(value_link_type_link);
		// set ID
		str.Format(_T("%d"), value_link_id);
		m_link_id.SetWindowTextW(str);
		// set name
		m_link_name.SetWindowTextW(name);
	}
	return CDialogEx::ContinueModal();
}


void Dialog_Link_Properties::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	CString str;

	// get R color
	m_link_color_R.GetWindowTextW(str);
	value_link_color_R = _ttoi(str);
	if (value_link_color_R > 255)
		value_link_color_R = 0;

	// get G color
	m_link_color_G.GetWindowTextW(str);
	value_link_color_G = _ttoi(str);
	if (value_link_color_G > 255)
		value_link_color_G = 0;

	// get B color
	m_link_color_B.GetWindowTextW(str);
	value_link_color_B = _ttoi(str);
	if (value_link_color_B > 255)
		value_link_color_B = 0;

	// get first shape
	m_link_shape_first_id.GetWindowTextW(str);
	value_link_shape_first_id = _ttoi(str);

	// get second shape
	m_link_shape_second_id.GetWindowTextW(str);
	value_link_shape_second_id = _ttoi(str);

	// get link size
	value_link_size = m_cb_link_size.GetCurSel();

	// get line type
	value_link_type = m_cb_link_type.GetCurSel();

	// get link type
	value_link_type_link = m_cb_link_type_link.GetCurSel();

	// get ID
	m_link_id.GetWindowTextW(str);
	value_link_id = _ttoi(str);

	// get name
	m_link_name.GetWindowTextW(name);

	CDialogEx::OnOK();
}
