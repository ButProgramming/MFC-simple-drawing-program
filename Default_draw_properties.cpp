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
}


BEGIN_MESSAGE_MAP(Default_draw_properties, CDialogEx)
	ON_BN_CLICKED(IDOK, &Default_draw_properties::OnBnClickedOk)
END_MESSAGE_MAP()


// Default_draw_properties message handlers


void Default_draw_properties::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	
	m_color = m_color_outline.GetColor();
	int outlineR = GetRValue(m_color);
	int outlineG = GetGValue(m_color);
	int outlineB = GetBValue(m_color);
	CString str;
	str.Format(_T("R: %d, G: %d, B: %d"), outlineR, outlineG, outlineB);
	CDialogEx::OnOK();
}
