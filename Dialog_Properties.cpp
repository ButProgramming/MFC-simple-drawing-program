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
	ON_BN_CLICKED(IDOK, &Dialog_Properties::OnBnClickedOk)
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


void Dialog_Properties::OnBnClickedOk()
{
	CString str;
	// coordinate X
	m_edit_x.GetWindowTextW(str);
	value_x = _ttoi(str);
	str.Format(_T("%d"), value_x);
	// coordinate Y
	m_edit_y.GetWindowTextW(str);
	value_y = _ttoi(str);
	// R outline color
	m_outline_R.GetWindowTextW(str);
	value_outline_R = _ttoi(str);
	if (value_outline_R > 255)
		value_outline_R = 0;
	// G outline color
	m_outline_G.GetWindowTextW(str);
	value_outline_G = _ttoi(str);
	if (value_outline_G > 255)
		value_outline_G = 0;
	// B outline color
	m_outline_B.GetWindowTextW(str);
	value_outline_B = _ttoi(str);
	if (value_outline_B > 255)
		value_outline_B = 0;
	// R outline color
	m_fill_R.GetWindowTextW(str);
	value_fill_R = _ttoi(str);
	if (value_fill_R > 255)
		value_fill_R = 0;
	// G outline color
	m_fill_G.GetWindowTextW(str);
	value_fill_G = _ttoi(str);
	if (value_fill_G > 255)
		value_fill_G = 0;
	// B outline color
	m_fill_B.GetWindowTextW(str);
	value_fill_B = _ttoi(str);
	if (value_fill_B > 255)
		value_fill_B = 0;
	// outline size
	value_outline_size = m_cb_outline_size.GetCurSel();
	// outline type
	value_outline_type = m_cb_outline_type.GetCurSel();
	// fill type
	value_fill_type = m_cb_fill_type.GetCurSel()-1;
	// degree
	m_degree.GetWindowTextW(str);
	value_degree = _ttoi(str);
	// ID
	m_id.GetWindowTextW(str);
	value_id = _ttoi(str);
	// name
	m_name.GetWindowTextW(value_name);

	//AfxMessageBox(str);
	// TODO: Add your control notification handler code here
	CDialogEx::OnOK();
}


void Dialog_Properties::getParameters(int numberOfShape)
{
	value_x = pDoc->getShapesVector()[numberOfShape]->getCenterOfShape().x;
	value_y = pDoc->getShapesVector()[numberOfShape]->getCenterOfShape().y;
	value_outline_R = GetRValue(pDoc->getShapesVector()[numberOfShape]->getOutlineColor());
	value_outline_G = GetGValue(pDoc->getShapesVector()[numberOfShape]->getOutlineColor());
	value_outline_B = GetBValue(pDoc->getShapesVector()[numberOfShape]->getOutlineColor());
	value_fill_R = GetRValue(pDoc->getShapesVector()[numberOfShape]->getFillColor());
	value_fill_G = GetGValue(pDoc->getShapesVector()[numberOfShape]->getFillColor());
	value_fill_B = GetBValue(pDoc->getShapesVector()[numberOfShape]->getFillColor());
	value_degree = pDoc->getShapesVector()[numberOfShape]->radToDeg(pDoc->getShapesVector()[numberOfShape]->getAngleRad());//getAngleRad() * 180.0 / 3.14;
	value_id = pDoc->getShapesVector()[numberOfShape]->getID();
	value_name = pDoc->getShapesVector()[numberOfShape]->getName();
	value_outline_size = pDoc->getShapesVector()[numberOfShape]->getOutlineSize();
	value_outline_type = pDoc->getShapesVector()[numberOfShape]->getOutlineType();
	value_fill_type = pDoc->getShapesVector()[numberOfShape]->getFillType();
}


void Dialog_Properties::setParameters(int numberOfShape)
{
	pDoc->getShapesVector()[numberOfShape]->setCenterOfShape(CPoint{ value_x, value_y });
	/*	pDoc->getShapesVector()[s]->centerOfShape.y = dlg.value_y;*/
		// outline color
	pDoc->getShapesVector()[numberOfShape]->setOutlineColor(RGB(value_outline_R, value_outline_G, value_outline_B));
	/*pDoc->getShapesVector()[s]->outlineColor = RGB(dlg.value_outline_R, GetGValue(pDoc->getShapesVector()[s]->outlineColor), GetBValue(pDoc->getShapesVector()[s]->outlineColor));
	pDoc->getShapesVector()[s]->outlineColor = RGB(GetRValue(pDoc->getShapesVector()[s]->outlineColor), dlg.value_outline_G, GetBValue(pDoc->getShapesVector()[s]->outlineColor));
	pDoc->getShapesVector()[s]->outlineColor = RGB(GetRValue(pDoc->getShapesVector()[s]->outlineColor), GetGValue(pDoc->getShapesVector()[s]->outlineColor), dlg.value_outline_B);*/
	// fill color
	pDoc->getShapesVector()[numberOfShape]->setFillColor(RGB(value_fill_R, value_fill_G, value_fill_B));
	//pDoc->getShapesVector()[s]->fillColor = RGB(dlg.value_fill_R, GetGValue(pDoc->getShapesVector()[s]->fillColor), GetBValue(pDoc->getShapesVector()[s]->fillColor));
	//pDoc->getShapesVector()[s]->fillColor = RGB(GetRValue(pDoc->getShapesVector()[s]->fillColor), dlg.value_fill_G, GetBValue(pDoc->getShapesVector()[s]->fillColor));
	//pDoc->getShapesVector()[s]->fillColor = RGB(GetRValue(pDoc->getShapesVector()[s]->fillColor), GetGValue(pDoc->getShapesVector()[s]->fillColor), dlg.value_fill_B);
	// outline size
	pDoc->getShapesVector()[numberOfShape]->setOutlineSize(value_outline_size);
	// outline type
	pDoc->getShapesVector()[numberOfShape]->setOutlineType(value_outline_type);
	// fill type
	pDoc->getShapesVector()[numberOfShape]->setFillType(value_fill_type);
	//pDoc->getShapesVector()[s]->fillType = ;
	// degree
	pDoc->getShapesVector()[numberOfShape]->setAngleRad(pDoc->getShapesVector()[numberOfShape]->degToRad(value_degree));
	//pDoc->getShapesVector()[s]->setAngleRad( * 3.14 / 180.0);
	// ID
	if (value_id >= 0)
	{
		if (IShape::getIDs().find(value_id) == IShape::getIDs().end())
		{
			IShape::getIDs().erase(pDoc->getShapesVector()[numberOfShape]->getID());
			pDoc->getShapesVector()[numberOfShape]->setID(value_id);
			IShape::getIDs().insert(value_id);
			//IShape::IDs.erase(dlg.value_id);
		}
	}
	// name
	if (IShape::getNames().find(value_name) == IShape::getNames().end())
	{
		IShape::getNames().erase(pDoc->getShapesVector()[numberOfShape]->getName());
		pDoc->getShapesVector()[numberOfShape]->setName(value_name);
		IShape::getNames().insert(value_name);

	}
	// TODO: Add your implementation code here.
}
