// List_Control.cpp : implementation file
//

#include "pch.h"
#include "EgoSecure_Test_Assignment.h"
#include "List_Control.h"
#include "afxdialogex.h"


// List_Control dialog

IMPLEMENT_DYNAMIC(List_Control, CDialogEx)

List_Control::List_Control(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_LISTCONTROL, pParent)
{

}

List_Control::~List_Control()
{
}

void List_Control::DoDataExchange(CDataExchange* pDX)
{
	//auto pDoc = 
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LISTCONTROL_SHAPES, m_listControl_shapes);
	this->m_listControl_shapes.InsertColumn(0, _T("ID"), LVCFMT_LEFT, 30);
	this->m_listControl_shapes.InsertColumn(1, _T("Type"), LVCFMT_CENTER, 70);
	this->m_listControl_shapes.InsertColumn(2, _T("Name"), LVCFMT_CENTER, 100);
	this->m_listControl_shapes.InsertColumn(3, _T("Center"), LVCFMT_CENTER, 120);
	this->m_listControl_shapes.InsertColumn(4, _T("Angle"), LVCFMT_CENTER, 70);

	int nItem;
	for (auto s:shapes)
	{
	
		CString str;
		str.Format(_T("%d"), s->ID);
		nItem = m_listControl_shapes.InsertItem(0, str);
		if (s->type == ShapeType::ellipse)
		{
			m_listControl_shapes.SetItemText(nItem, 1, _T("Ellipse"));
		}
		else if (s->type == ShapeType::rectangle)
		{
			m_listControl_shapes.SetItemText(nItem, 1, _T("Rectangle"));
		}
		else
		{
			m_listControl_shapes.SetItemText(nItem, 1, _T("Triangle"));
		}
		
		m_listControl_shapes.SetItemText(nItem, 2, s->name);
		str.Format(_T("x: %d, y: %d"), s->centerOfShape.x, s->centerOfShape.y);
		m_listControl_shapes.SetItemText(nItem, 3, str);
		str.Format(_T("%g degree"), s->ellipseAngleRad*180.f/3.14);
		m_listControl_shapes.SetItemText(nItem, 4, str);
	}
	
}


BEGIN_MESSAGE_MAP(List_Control, CDialogEx)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LISTCONTROL_SHAPES, &List_Control::OnItemchangedListcontrolShapes)
END_MESSAGE_MAP()


// List_Control message handlers


void List_Control::OnItemchangedListcontrolShapes(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: Add your control notification handler code here
	*pResult = 0;
}
