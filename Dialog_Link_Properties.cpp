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
	DDX_Control(pDX, IDC_EDIT_LINK_COLOR_R, eLinkColorR);
	DDX_Control(pDX, IDC_EDIT_LINK_COLOR_G, eLinkColorG);
	DDX_Control(pDX, IDC_EDIT_LINK_COLOR_B, eLinkColorB);
	DDX_Control(pDX, IDC_EDIT_LINK_SHAPE_FIRST_ID, eLinkShapeFirstID);
	DDX_Control(pDX, IDC_EDIT_LINK_SHAPE_SECOND_ID, eLinkShapeSecondID);
	//  DDX_Control(pDX, IDC_COMBO_LINK_SIZE, m_link_size);
	DDX_Control(pDX, IDC_COMBO_LINK_SIZE, bLinkSize);
	DDX_Control(pDX, IDC_COMBO_LINK_TYPE, bLinkType);
	//  DDX_Control(pDX, IDC_COMBO_LINK_TYPE_LINK, m_link_type_link);
	DDX_Control(pDX, IDC_COMBO_LINK_TYPE_LINK, bLinkTypeLink);
	DDX_Control(pDX, IDC_EDIT_LINK_ID, eLinkID);
	DDX_Control(pDX, IDC_EDIT_LINK_NAME, eLinkName);
}


BEGIN_MESSAGE_MAP(Dialog_Link_Properties, CDialogEx)
	ON_BN_CLICKED(IDOK, &Dialog_Link_Properties::OnBnClickedOk)
END_MESSAGE_MAP()


// Dialog_Link_Properties message handlers


BOOL Dialog_Link_Properties::ContinueModal()
{
	// TODO: Add your specialized code here and/or call the base class
	if (callcallFirstTime)
	{
		callcallFirstTime = false;
		CString str;
		// set R color
		str.Format(_T("%d"), nLinkColorR);
		eLinkColorR.SetWindowTextW(str);
		// set G color
		str.Format(_T("%d"), nLinkColorG);
		eLinkColorG.SetWindowTextW(str);
		// set B color
		str.Format(_T("%d"), nLinkColorB);
		eLinkColorB.SetWindowTextW(str);
		// set first shape id
		str.Format(_T("%d"), nLinkShapeFirstID);
		eLinkShapeFirstID.SetWindowTextW(str);
		// set second shape id
		str.Format(_T("%d"), nLinkShapeSecondID);
		eLinkShapeSecondID.SetWindowTextW(str);
		// set link size
		bLinkSize.SetCurSel(nLinkSize);
		// set link type (__, ..., _.._, ...)
		bLinkType.SetCurSel(nLinkType);
		// set link type (basic, right, left, double)
		bLinkTypeLink.SetCurSel(nLinkTypeLink);
		// set ID
		str.Format(_T("%d"), nLinkID);
		eLinkID.SetWindowTextW(str);
		// set name
		eLinkName.SetWindowTextW(name);
	}
	return CDialogEx::ContinueModal();
}


void Dialog_Link_Properties::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	CString str;

	// get R color
	eLinkColorR.GetWindowTextW(str);
	nLinkColorR = _ttoi(str);
	if (nLinkColorR > 255)
		nLinkColorR = 0;

	// get G color
	eLinkColorG.GetWindowTextW(str);
	nLinkColorG = _ttoi(str);
	if (nLinkColorG > 255)
		nLinkColorG = 0;

	// get B color
	eLinkColorB.GetWindowTextW(str);
	nLinkColorB = _ttoi(str);
	if (nLinkColorB > 255)
		nLinkColorB = 0;

	// get first shape
	eLinkShapeFirstID.GetWindowTextW(str);
	nLinkShapeFirstID = _ttoi(str);

	// get second shape
	eLinkShapeSecondID.GetWindowTextW(str);
	nLinkShapeSecondID = _ttoi(str);

	// get link size
	nLinkSize = bLinkSize.GetCurSel();

	// get line type
	nLinkType = bLinkType.GetCurSel();

	// get link type
	nLinkTypeLink = bLinkTypeLink.GetCurSel();

	// get ID
	eLinkID.GetWindowTextW(str);
	nLinkID = _ttoi(str);

	// get name
	eLinkName.GetWindowTextW(name);

	CDialogEx::OnOK();
}
