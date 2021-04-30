// Dialog_Properties.cpp : implementation file
//

#include "pch.h"
#include "EgoSecure_Test_Assignment.h"
#include "Dialog_Properties.h"
#include "afxdialogex.h"


// Dialog_Properties dialog

IMPLEMENT_DYNAMIC(Dialog_Properties, CDialogEx)

Dialog_Properties::Dialog_Properties(CEgoSecureTestAssignmentDoc* pDoc, CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_PROPERTIES, pParent)
{
	this->pDoc = pDoc;
}

Dialog_Properties::~Dialog_Properties()
{
}

void Dialog_Properties::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_EDIT_X, editX);
	DDX_Control(pDX, IDC_EDITY, editY);

	DDX_Control(pDX, IDC_EDIT_OUTLINE_R, outlineR);
	DDX_Control(pDX, IDC_EDIT_OUTLINE_G, outlineG);
	DDX_Control(pDX, IDC_EDIT_OUTLINE_B, outlineB);
	DDX_Control(pDX, IDC_EDIT_DEGREE, editDegree);
	DDX_Control(pDX, IDC_EDIT_ID, editID);
	DDX_Control(pDX, IDC_EDIT_NAME, editName);
	DDX_Control(pDX, IDC_EDIT_OUTLINE_R2, editFillR);
	DDX_Control(pDX, IDC_EDIT_OUTLINE_G2, editFillG);
	DDX_Control(pDX, IDC_EDIT_OUTLINE_B2, editFillB);
	DDX_Control(pDX, IDC_COMBO1, bOutlineSize);

	DDX_Control(pDX, IDC_COMBO2, bOutlineType);
	DDX_Control(pDX, IDC_COMBO3, bFillType);
}


BEGIN_MESSAGE_MAP(Dialog_Properties, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_GET_DATA, &Dialog_Properties::OnBnClickedButtonGetData)
	//ON_EN_CHANGE(IDC_EDIT6, &Dialog_Properties::OnEnChangeEdit6)
	ON_BN_CLICKED(IDOK, &Dialog_Properties::OnBnClickedOk)
END_MESSAGE_MAP()


// Dialog_Properties message handlers


void Dialog_Properties::OnBnClickedButtonGetData()
{
	
	// TODO: Add your control notification handler code here
}




BOOL Dialog_Properties::ContinueModal()
{
	// TODO: Add your specialized code here and/or call the base class
	if (callFirstTime)
	{
		CString str;
		str.Format(_T("%d"), nX);
		editX.SetWindowTextW(str);
		str.Format(_T("%d"), nY);
		editY.SetWindowTextW(str);
		str.Format(_T("%d"), nOutlineR);
		outlineR.SetWindowTextW(str);
		str.Format(_T("%d"), nOutlineG);
		outlineG.SetWindowTextW(str);
		str.Format(_T("%d"), nOutlineB);
		outlineB.SetWindowTextW(str);
		str.Format(_T("%d"), nFillR);
		editFillR.SetWindowTextW(str);
		str.Format(_T("%d"), nFillG);
		editFillG.SetWindowTextW(str);
		str.Format(_T("%d"), nFillB);
		editFillB.SetWindowTextW(str);
		str.Format(_T("%d"), nDegree);
		editDegree.SetWindowTextW(str);
		str.Format(_T("%d"), nID);
		editID.SetWindowTextW(str);
		editName.SetWindowTextW(nName);
		str.Format(_T("%d"), nOutlineSize);
		bOutlineSize.SetCurSel(nOutlineSize);
		bOutlineType.SetCurSel(nOutlineType);
		bFillType.SetCurSel(nFillType+1);
		callFirstTime = false;
	}
	return CDialogEx::ContinueModal();
}


void Dialog_Properties::OnEnChangeEdit6()
{
	
}


void Dialog_Properties::OnBnClickedOk()
{
	CString str;
	// coordinate X
	editX.GetWindowTextW(str);
	nX = _ttoi(str);
	str.Format(_T("%d"), nX);
	// coordinate Y
	editY.GetWindowTextW(str);
	nY = _ttoi(str);
	// R outline color
	outlineR.GetWindowTextW(str);
	nOutlineR = _ttoi(str);
	if (nOutlineR > 255)
		nOutlineR = 0;
	// G outline color
	outlineG.GetWindowTextW(str);
	nOutlineG = _ttoi(str);
	if (nOutlineG > 255)
		nOutlineG = 0;
	// B outline color
	outlineB.GetWindowTextW(str);
	nOutlineB = _ttoi(str);
	if (nOutlineB > 255)
		nOutlineB = 0;
	// R outline color
	editFillR.GetWindowTextW(str);
	nFillR = _ttoi(str);
	if (nFillR > 255)
		nFillR = 0;
	// G outline color
	editFillG.GetWindowTextW(str);
	nFillG = _ttoi(str);
	if (nFillG > 255)
		nFillG = 0;
	// B outline color
	editFillB.GetWindowTextW(str);
	nFillB = _ttoi(str);
	if (nFillB > 255)
		nFillB = 0;
	// outline size
	nOutlineSize = bOutlineSize.GetCurSel();
	// outline type
	nOutlineType = bOutlineType.GetCurSel();
	// fill type
	nFillType = bFillType.GetCurSel()-1;
	// degree
	editDegree.GetWindowTextW(str);
	nDegree = _ttoi(str);
	// ID
	editID.GetWindowTextW(str);
	nID = _ttoi(str);
	// name
	editName.GetWindowTextW(nName);


	CDialogEx::OnOK();
}


void Dialog_Properties::getParameters(int numberOfShape)
{
	nX = pDoc->getShapesVector()[numberOfShape]->getCenterOfShape().x;
	nY = pDoc->getShapesVector()[numberOfShape]->getCenterOfShape().y;
	nOutlineR = GetRValue(pDoc->getShapesVector()[numberOfShape]->getOutlineColor());
	nOutlineG = GetGValue(pDoc->getShapesVector()[numberOfShape]->getOutlineColor());
	nOutlineB = GetBValue(pDoc->getShapesVector()[numberOfShape]->getOutlineColor());
	nFillR = GetRValue(pDoc->getShapesVector()[numberOfShape]->getFillColor());
	nFillG = GetGValue(pDoc->getShapesVector()[numberOfShape]->getFillColor());
	nFillB = GetBValue(pDoc->getShapesVector()[numberOfShape]->getFillColor());
	nDegree = pDoc->getShapesVector()[numberOfShape]->radToDeg(pDoc->getShapesVector()[numberOfShape]->getAngleRad());//getAngleRad() * 180.0 / 3.14;
	nID = pDoc->getShapesVector()[numberOfShape]->getID();
	nName = pDoc->getShapesVector()[numberOfShape]->getName();
	nOutlineSize = pDoc->getShapesVector()[numberOfShape]->getOutlineSize();
	nOutlineType = pDoc->getShapesVector()[numberOfShape]->getOutlineType();
	nFillType = pDoc->getShapesVector()[numberOfShape]->getFillType();
}


void Dialog_Properties::setParameters(int numberOfShape)
{
	pDoc->getShapesVector()[numberOfShape]->setCenterOfShape(CPoint{ nX, nY });
		// outline color
	pDoc->getShapesVector()[numberOfShape]->setOutlineColor(RGB(nOutlineR, nOutlineG, nOutlineB));

	// fill color
	pDoc->getShapesVector()[numberOfShape]->setFillColor(RGB(nFillR, nFillG, nFillB));
	// outline size
	pDoc->getShapesVector()[numberOfShape]->setOutlineSize(nOutlineSize);
	// outline type
	pDoc->getShapesVector()[numberOfShape]->setOutlineType(nOutlineType);
	cout << pDoc->getShapesVector()[numberOfShape]->getOutlineType() << endl;
	// fill type
	pDoc->getShapesVector()[numberOfShape]->setFillType(nFillType);
	// degree
	pDoc->getShapesVector()[numberOfShape]->setAngleRad(pDoc->getShapesVector()[numberOfShape]->degToRad(nDegree));
	// ID
	if (nID >= 0)
	{
		if (IShape::getIDs().find(nID) == IShape::getIDs().end())
		{
			IShape::getIDs().erase(pDoc->getShapesVector()[numberOfShape]->getID());
			pDoc->getShapesVector()[numberOfShape]->setID(nID);
			IShape::getIDs().insert(nID);
		
		}
	}
	// name
	if (IShape::getNames().find(nName) == IShape::getNames().end())
	{
		IShape::getNames().erase(pDoc->getShapesVector()[numberOfShape]->getName());
		pDoc->getShapesVector()[numberOfShape]->setName(nName);
		IShape::getNames().insert(nName);

	}

}
