// Default_draw_properties.cpp : implementation file
//

#include "pch.h"
#include "EgoSecure_Test_Assignment.h"
#include "Default_draw_properties.h"
#include "afxdialogex.h"


// Default_draw_properties dialog

IMPLEMENT_DYNAMIC(Default_draw_properties, CDialogEx)

Default_draw_properties::Default_draw_properties(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_DEFAULT_DRAW_PROPERTIES, pParent)
{
	//SetDataDefaultDrawProperties();
}

Default_draw_properties::~Default_draw_properties()
{
}

void Default_draw_properties::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MFCCOLORBUTTON_OUTLINE, m_color_outline);
	//  DDX_Control(pDX, IDC_MFCCOLORBUTTON_FILL, m_fill_color);
	DDX_Control(pDX, IDC_MFCCOLORBUTTON_FILL, m_color_fill);
	//  DDX_Control(pDX, IDC_COMBO_OUTLINE_SIZE, m_combobox_outline);
	DDX_Control(pDX, IDC_COMBO_OUTLINE_SIZE, m_cb_outline_size);
	DDX_Control(pDX, IDC_COMBO_OUTLINE_TYPE, m_cb_outline_type);
	DDX_Control(pDX, IDC_COMBO_FILL_TYPE, m_cb_fill_type);
	DDX_Control(pDX, IDC_MFCCOLORBUTTON3, m_color_link);
	DDX_Control(pDX, IDC_COMBO5, m_cb_link_type);
	DDX_Control(pDX, IDC_COMBO_LINE_SIZE, m_cb_line_size);
}


BEGIN_MESSAGE_MAP(Default_draw_properties, CDialogEx)
	ON_BN_CLICKED(IDOK, &Default_draw_properties::OnBnClickedOk)
END_MESSAGE_MAP()


// Default_draw_properties message handlers


void Default_draw_properties::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	m_cb_outline_size.SetCurSel(1);
	m_color_outline_COLORREF = m_color_outline.GetColor();
	m_color_fill_COLORREF = m_color_fill.GetColor();
	m_color_link_COLORREF = m_color_link.GetColor();
	num_cb_outline_size = m_cb_outline_size.GetCurSel();
	num_cb_outline_type = m_cb_outline_type.GetCurSel();
	num_cb_fill_type = m_cb_fill_type.GetCurSel() - 1; // because #DEFINE beginn with 0
	num_cb_link_type = m_cb_link_type.GetCurSel();
	num_cb_line_size = m_cb_line_size.GetCurSel();
	if (num_cb_outline_size == -1)
		num_cb_outline_size = 2;
	if (num_cb_outline_type == -1)
		num_cb_outline_type = 0;
	if (num_cb_fill_type == -2)
		num_cb_fill_type = -1;
	if (num_cb_link_type == -1)
		num_cb_link_type = 0;
	if (num_cb_line_size == -1)
		num_cb_line_size = 1;

	CDialogEx::OnOK();
}


//void Default_draw_properties::SetDataDefaultDrawProperties()
//{
//	m_cb_outline_size.SelectString(0, _T("123"));
//	//m_cb_outline_size.SetCurSel(size);
//	// TODO: Add your implementation code here.
//}
