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
}


BEGIN_MESSAGE_MAP(Default_draw_properties, CDialogEx)
	ON_BN_CLICKED(IDOK, &Default_draw_properties::OnBnClickedOk)
END_MESSAGE_MAP()


// Default_draw_properties message handlers


void Default_draw_properties::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	
	m_color_outline_COLORREF = m_color_outline.GetColor();
	int outlineR = GetRValue(m_color_outline_COLORREF);
	int outlineG = GetGValue(m_color_outline_COLORREF);
	int outlineB = GetBValue(m_color_outline_COLORREF);
	CString str;
	str.Format(_T("R: %d, G: %d, B: %d"), outlineR, outlineG, outlineB);
	CDialogEx::OnOK();

	m_color_fill_COLORREF = m_color_fill.GetColor();
}
