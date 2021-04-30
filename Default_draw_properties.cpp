// Default_draw_properties.cpp : implementation file
//

#include "pch.h"
#include "EgoSecure_Test_Assignment.h"
#include "Default_draw_properties.h"
#include "afxdialogex.h"



// Default_draw_properties dialog

IMPLEMENT_DYNAMIC(Default_draw_properties, CDialogEx)

Default_draw_properties::Default_draw_properties(CEgoSecureTestAssignmentDoc* pDoc, CWnd* pParent)
	: CDialogEx(IDD_DIALOG_DEFAULT_DRAW_PROPERTIES, pParent)
{
	this->pDoc = pDoc;
}

Default_draw_properties::~Default_draw_properties()
{
}

void Default_draw_properties::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MFCCOLORBUTTON_OUTLINE, bColorOutline);
	DDX_Control(pDX, IDC_MFCCOLORBUTTON_FILL, bColorFill);
	DDX_Control(pDX, IDC_COMBO_OUTLINE_SIZE, bOutlineSize);
	DDX_Control(pDX, IDC_COMBO_OUTLINE_TYPE, bOutlineType);
	DDX_Control(pDX, IDC_COMBO_FILL_TYPE, bFillType);
	DDX_Control(pDX, IDC_MFCCOLORBUTTON3, bColorLink);
	DDX_Control(pDX, IDC_COMBO5, bLinkType);
	DDX_Control(pDX, IDC_COMBO_LINE_SIZE, bLineSize);
}


BEGIN_MESSAGE_MAP(Default_draw_properties, CDialogEx)
	ON_BN_CLICKED(IDOK, &Default_draw_properties::OnBnClickedOk)
END_MESSAGE_MAP()


// Default_draw_properties message handlers


void Default_draw_properties::OnBnClickedOk()
{
	colorOutline = bColorOutline.GetColor();
	colorFill = bColorFill.GetColor();
	colorLink = bColorLink.GetColor();
	nOutlineSize = bOutlineSize.GetCurSel();
	nOutlineType = bOutlineType.GetCurSel();
	nFillType = bFillType.GetCurSel() - 1; // because #DEFINE beginn with 0
	nLinkType = bLinkType.GetCurSel();
	nLineSize = bLineSize.GetCurSel();
	if (nOutlineSize == -1)
		nOutlineSize = 2;
	if (nOutlineType == -1)
		nOutlineType = 0;
	if (nFillType == -2)
		nFillType = -1;
	if (nLinkType == -1)
		nLinkType = 0;
	if (nLineSize == -1)
		nLineSize = 1;

	CDialogEx::OnOK();
}


BOOL Default_draw_properties::ContinueModal()
{
	if (callcallFirstTime)
	{
		//color
		bColorOutline.SetColor(colorOutline);
		bColorFill.SetColor(colorFill);
		bColorLink.SetColor(colorLink);

		//outline size
		bOutlineSize.SetCurSel(nOutlineSize);

		//outline type
		bOutlineType.SetCurSel(nOutlineType);

		//fill type
		bFillType.SetCurSel(nFillType + 1);

		//link size
		bLineSize.SetCurSel(nLineSize);

		//link type
		bLinkType.SetCurSel(nLinkType);

		callcallFirstTime = false;
	}
	return CDialogEx::ContinueModal();
}


void Default_draw_properties::getParameters()
{
	colorOutline = pDoc->getOutlineColor();
	colorFill = pDoc->getFillColor();
	colorLink = pDoc->getColorLink();
	nOutlineSize = pDoc->getOutlineSize();
	nOutlineType = pDoc->getOutlineType();
	nFillType = pDoc->getFillType();
	nLineSize = pDoc->getLineSize();
	nLinkType = pDoc->getLinkType();
}


void Default_draw_properties::setParameters()
{
	bColorOutline.SetColor(RGB(255, 0, 0));
	pDoc->setOutlineColor(colorOutline);
	pDoc->setFillColor(colorFill);
	pDoc->setOutlineSize(nOutlineSize);
	pDoc->setOutlineType(nOutlineType);
	pDoc->setFillType(nFillType);
	pDoc->setLinkType(nLinkType);
	pDoc->setColorLink(colorLink);
	pDoc->setLineSize(nLineSize);
}
