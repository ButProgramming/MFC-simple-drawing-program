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
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LISTCONTROL_SHAPES, m_listControl_shapes);

	// InsertColumt for shapes
	m_listControl_shapes.InsertColumn(0, _T("ID"), LVCFMT_LEFT, 50);
	m_listControl_shapes.InsertColumn(1, _T("Type"), LVCFMT_CENTER, 100);
	m_listControl_shapes.InsertColumn(2, _T("Name"), LVCFMT_CENTER, 100);
	m_listControl_shapes.InsertColumn(3, _T("Outline RGB"), LVCFMT_CENTER, 150);
	m_listControl_shapes.InsertColumn(4, _T("Outline size"), LVCFMT_CENTER, 100);
	m_listControl_shapes.InsertColumn(5, _T("Outline type"), LVCFMT_CENTER, 100);
	m_listControl_shapes.InsertColumn(6, _T("Center"), LVCFMT_CENTER, 150);
	m_listControl_shapes.InsertColumn(7, _T("Angle"), LVCFMT_CENTER, 100);
	m_listControl_shapes.InsertColumn(8, _T("Fill RGB"), LVCFMT_CENTER, 150);
	m_listControl_shapes.InsertColumn(9, _T("Fill type"), LVCFMT_CENTER, 100);
	m_listControl_shapes.InsertColumn(10, _T("First line coordinates"), LVCFMT_CENTER, 150);
	m_listControl_shapes.InsertColumn(11, _T("Second line coordinates"), LVCFMT_CENTER, 150);
	m_listControl_shapes.InsertColumn(12, _T("First linked shape ID"), LVCFMT_CENTER, 150);
	m_listControl_shapes.InsertColumn(13, _T("Second linked shape ID"), LVCFMT_CENTER, 150);


	// filling shapes listview
	int nItem = NULL;
	CString str = NULL;
	for (auto s : shapes)
	{
		str.Format(_T("%d"), s->getID());
		nItem = m_listControl_shapes.InsertItem(0, str);
		if (s->getShapeType() == ShapeType::ellipse)
		{
			m_listControl_shapes.SetItemText(nItem, 1, _T("Ellipse"));
		}
		else if (s->getShapeType() == ShapeType::rectangle)
		{
			m_listControl_shapes.SetItemText(nItem, 1, _T("Rectangle"));
		}
		else
		{
			m_listControl_shapes.SetItemText(nItem, 1, _T("Triangle"));
		}

		m_listControl_shapes.SetItemText(nItem, 2, s->getName());
		int oR = GetRValue(s->getOutlineColor());
		int oG = GetGValue(s->getOutlineColor());
		int oB = GetBValue(s->getOutlineColor());
		str.Format(_T("R: %d, G: %d, B: %d"), oR, oG, oB);
		m_listControl_shapes.SetItemText(nItem, 3, str);

		str.Format(_T("%d"), s->getOutlineSize());
		m_listControl_shapes.SetItemText(nItem, 4, str);

		// outlineType
		switch (s->getOutlineType())
		{
			case 0:
			{
				str.Format(_T("___"));
				break;
			}
			case 1:
			{
				str.Format(_T("_ _"));
				break;
			}
			case 2:
			{
				str.Format(_T("...."));
				break;
			}
			case 3:
			{
				str.Format(_T("_._"));
				break;
			}
			case 4:
			{
				str.Format(_T("_.._"));
				break;
			}
		}
		m_listControl_shapes.SetItemText(nItem, 5, str);

		if (s->getShapeType() == ShapeType::basicLine || s->getShapeType() == ShapeType::rightLine
			|| s->getShapeType() == ShapeType::leftLine || s->getShapeType() == ShapeType::doubleLine)
		{
			str.Format(_T("-"), s->getCenterOfShape().x, s->getCenterOfShape().y);
			m_listControl_shapes.SetItemText(nItem, 6, str);
			m_listControl_shapes.SetItemText(nItem, 7, str);
			m_listControl_shapes.SetItemText(nItem, 8, str);
			m_listControl_shapes.SetItemText(nItem, 9, str);
			str.Format(_T("x: %d, y: %d"), s->getCoordinateForChange(FIRST_POINT_OF_LINE).x, s->getCoordinateForChange(FIRST_POINT_OF_LINE).y);
			m_listControl_shapes.SetItemText(nItem, 10, str);
			str.Format(_T("x: %d, y: %d"), s->getCoordinateForChange(SECOND_POINT_OF_LINE).x, s->getCoordinateForChange(SECOND_POINT_OF_LINE).y);
			m_listControl_shapes.SetItemText(nItem, 11, str);
			int firstIDFromConstID = -1;
			int secondIDFromConstID = -1;
			for (int shapeNum = 0; shapeNum < shapes.size(); shapeNum++)
			{
				if (shapes[shapeNum]->getConstID() == s->getConnectedShapeConstID(FIRST_POINT_OF_LINE))
				{
					firstIDFromConstID = shapes[shapeNum]->getID();
					break;
				}
			}
			for (int shapeNum = 0; shapeNum < shapes.size(); shapeNum++)
			{
				if (shapes[shapeNum]->getConstID() == s->getConnectedShapeConstID(SECOND_POINT_OF_LINE))
				{
					secondIDFromConstID = shapes[shapeNum]->getID();
					break;
				}
			}
			if (firstIDFromConstID != -1)
			{
				str.Format(_T("ID: %d"), firstIDFromConstID);
				m_listControl_shapes.SetItemText(nItem, 12, str);
			}
			else
			{
				str.Format(_T("Is not connected"), firstIDFromConstID);
				m_listControl_shapes.SetItemText(nItem, 12, str);
			}
			if (secondIDFromConstID != -1)
			{
				str.Format(_T("ID: %d"), secondIDFromConstID);
				m_listControl_shapes.SetItemText(nItem, 13, str);
			}
			else
			{
				str.Format(_T("Is not connected"), firstIDFromConstID);
				m_listControl_shapes.SetItemText(nItem, 13, str);
			}
		}
		else
		{
			str.Format(_T("x: %d, y: %d"), s->getCenterOfShape().x, s->getCenterOfShape().y);
			m_listControl_shapes.SetItemText(nItem, 6, str);
			str.Format(_T("%g degree"), s->getAngleRad() * 180.f / 3.14);
			m_listControl_shapes.SetItemText(nItem, 7, str);
			int fR = GetRValue(s->getFillColor());
			int fG = GetGValue(s->getFillColor());
			int fB = GetBValue(s->getFillColor());
			str.Format(_T("R: %d, G: %d, B: %d"), fR, fG, fB);
			m_listControl_shapes.SetItemText(nItem, 8, str);
			//Normal;Horizontal hatch;Vertical hatch;Upward hatch;Downward hatch;Horizontal and vertical crosshatch;Crosshatch at 45 degrees;
			switch (s->getFillType())
			{
			case -1:
			{
				str.Format(_T("Normal"));
				break;
			}
			case 0:
			{
				str.Format(_T("Horizontal hatch"));
				break;
			}
			case 1:
			{
				str.Format(_T("Vertical hatch"));
				break;
			}
			case 2:
			{
				str.Format(_T("Upward hatch"));
				break;
			}
			case 3:
			{
				str.Format(_T("Downward hatch"));
				break;
			}
			case 4:
			{
				str.Format(_T("Horizontal and vertical crosshatch"));
				break;
			}
			case 5:
			{
				str.Format(_T("Crosshatch at 45 degrees"));
				break;
			}
			}
			m_listControl_shapes.SetItemText(nItem, 9, str);
			str.Format(_T("-"), s->getCenterOfShape().x, s->getCenterOfShape().y);
			m_listControl_shapes.SetItemText(nItem, 10, str);
			m_listControl_shapes.SetItemText(nItem, 11, str);
			m_listControl_shapes.SetItemText(nItem, 12, str);
			m_listControl_shapes.SetItemText(nItem, 13, str);
		}
		
		
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
