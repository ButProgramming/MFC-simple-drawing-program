// Dialog_Link_Properties.cpp : implementation file
//

#include "pch.h"
#include "EgoSecure_Test_Assignment.h"
#include "Dialog_Link_Properties.h"
#include "afxdialogex.h"


// Dialog_Link_Properties dialog

IMPLEMENT_DYNAMIC(Dialog_Link_Properties, CDialogEx)

Dialog_Link_Properties::Dialog_Link_Properties(CEgoSecureTestAssignmentDoc* pDoc, CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_PROPERTIES_LINK, pParent)
{
	this->pDoc = pDoc;
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
	DDX_Control(pDX, IDC_EDIT_LINK_SHAPE_FIRST_ID, eLinkFirstPoint);
	DDX_Control(pDX, IDC_EDIT_LINK_SHAPE_SECOND_ID, eLinkSecondPoint);
	DDX_Control(pDX, IDC_COMBO_LINK_SIZE, bLinkSize);
	DDX_Control(pDX, IDC_COMBO_LINK_TYPE, bLinkType);
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
		// set first coordinates
		str.Format(_T("%d, %d"), nLinkFirstPoint.x, nLinkFirstPoint.y);
		eLinkFirstPoint.SetWindowTextW(str);
		// set second coordinates
		str.Format(_T("%d, %d"), nLinkSecondPoint.x, nLinkSecondPoint.y);
		eLinkSecondPoint.SetWindowTextW(str);
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

	// get first point coordinate
	eLinkFirstPoint.GetWindowTextW(str);
	nLinkFirstPoint.x = _ttoi(str.Mid(0, str.Find(',')));
	nLinkFirstPoint.y = _ttoi(str.Mid(str.Find(',')+1));

	// get second point coordinate
	eLinkSecondPoint.GetWindowTextW(str);
	nLinkSecondPoint.x = _ttoi(str.Mid(0, str.Find(',')));
	nLinkSecondPoint.y = _ttoi(str.Mid(str.Find(',') + 1));

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


void Dialog_Link_Properties::getParameters(int shapeNum)
{
	nLinkColorR = GetRValue(pDoc->getShapesVector()[shapeNum]->getOutlineColor());
	nLinkColorG = GetGValue(pDoc->getShapesVector()[shapeNum]->getOutlineColor());
	nLinkColorB = GetBValue(pDoc->getShapesVector()[shapeNum]->getOutlineColor());
	nLinkFirstPoint = pDoc->getShapesVector()[shapeNum]->getCoordinateForChange(FIRST_POINT_OF_LINE);
	nLinkSecondPoint = pDoc->getShapesVector()[shapeNum]->getCoordinateForChange(SECOND_POINT_OF_LINE);
	nLinkFirstPointStart = nLinkFirstPoint;
	nLinkSecondPointStart = nLinkSecondPoint;

	nLinkSize = pDoc->getShapesVector()[shapeNum]->getOutlineSize();
	nLinkType = pDoc->getShapesVector()[shapeNum]->getOutlineType();
	switch (pDoc->getShapesVector()[shapeNum]->getShapeType())
	{
		case ShapeType::basicLine:
		{
			nLinkTypeLink = 0;
			break;
		}
		case ShapeType::rightLine:
		{
			nLinkTypeLink = 1;
			break;
		}
		case ShapeType::leftLine:
		{
			nLinkTypeLink = 2;
			break;
		}
		case ShapeType::doubleLine:
		{
			nLinkTypeLink = 3;
			break;
		}
	}
	nLinkID = pDoc->getShapesVector()[shapeNum]->getID();
	name = pDoc->getShapesVector()[shapeNum]->getName();

}


void Dialog_Link_Properties::setParameters(int shapeNum)
{
	// outline color
	pDoc->getShapesVector()[shapeNum]->setOutlineColor(RGB(nLinkColorR, nLinkColorG, nLinkColorB));
	pDoc->getShapesVector()[shapeNum]->setOutlineSize(nLinkSize);
	pDoc->getShapesVector()[shapeNum]->setOutlineType(nLinkType);

	if (pDoc->getShapesVector()[shapeNum]->getIsConnected(FIRST_POINT_OF_LINE))
	{
		if (nLinkFirstPoint != nLinkFirstPointStart)
		{
			pDoc->getShapesVector()[shapeNum]->lineDisconnecting(FIRST_POINT_OF_LINE, pDoc->getShapesVector()[shapeNum]->getConnectedShapeConstID(FIRST_POINT_OF_LINE));
		}
	}
	if (pDoc->getShapesVector()[shapeNum]->getIsConnected(SECOND_POINT_OF_LINE))
	{
		if (nLinkSecondPoint != nLinkSecondPointStart)
		{
			pDoc->getShapesVector()[shapeNum]->lineDisconnecting(SECOND_POINT_OF_LINE, pDoc->getShapesVector()[shapeNum]->getConnectedShapeConstID(SECOND_POINT_OF_LINE));
		}
	}
	pDoc->getShapesVector()[shapeNum]->setCoordinateForChange(FIRST_POINT_OF_LINE, nLinkFirstPoint);
	pDoc->getShapesVector()[shapeNum]->setCoordinateForChange(SECOND_POINT_OF_LINE, nLinkSecondPoint);
	// ID
	if (nLinkID >= 0)
	{
		if (IShape::getIDs().find(nLinkID) == IShape::getIDs().end())
		{
			IShape::getIDs().erase(pDoc->getShapesVector()[shapeNum]->getID());
			pDoc->getShapesVector()[shapeNum]->setID(nLinkID);
			IShape::getIDs().insert(nLinkID);
			//IShape::IDs.erase(dlg.nID);
		}
	}
	// name
	if (IShape::getNames().find(name) == IShape::getNames().end())
	{
		IShape::getNames().erase(pDoc->getShapesVector()[shapeNum]->getName());
		pDoc->getShapesVector()[shapeNum]->setName(name);
		IShape::getNames().insert(name);

	}
}
