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

	// InsertColumt for shapes
	m_listControl_shapes.InsertColumn(0, _T("ID"), LVCFMT_LEFT, 30);
	m_listControl_shapes.InsertColumn(1, _T("Type"), LVCFMT_CENTER, 70);
	m_listControl_shapes.InsertColumn(2, _T("Name"), LVCFMT_CENTER, 100);
	m_listControl_shapes.InsertColumn(3, _T("Center"), LVCFMT_CENTER, 120);
	m_listControl_shapes.InsertColumn(4, _T("Angle"), LVCFMT_CENTER, 70);
	//m_listControl_shapes.InsertColumn(5, _T("Is selected"), LVCFMT_CENTER, 70);

	// InsertColumnt for lines
	DDX_Control(pDX, IDC_LISTCONTROL_LINES, m_listControl_lines);
	m_listControl_lines.InsertColumn(0, _T("ID"), LVCFMT_CENTER, 50);
	m_listControl_lines.InsertColumn(1, _T("Type"), LVCFMT_CENTER, 100);
	m_listControl_lines.InsertColumn(2, _T("Name"), LVCFMT_CENTER, 100);
	m_listControl_lines.InsertColumn(3, _T("First shape id"), LVCFMT_CENTER, 50);
	m_listControl_lines.InsertColumn(4, _T("First shape type"), LVCFMT_CENTER, 100);
	m_listControl_lines.InsertColumn(5, _T("Second shape id"), LVCFMT_CENTER, 50);
	m_listControl_lines.InsertColumn(6, _T("Second shape type"), LVCFMT_CENTER, 100);

	// filling shapes listview
	int nItem;
	CString str;
	for (auto s : shapes)
	{
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
		str.Format(_T("%g degree"), s->ellipseAngleRad * 180.f / 3.14);
		m_listControl_shapes.SetItemText(nItem, 4, str);
		if (s->isSelected)
		{
			str.Format(_T("true"));
			m_listControl_shapes.SetItemText(nItem, 5, str);
		}
		else
		{
			str.Format(_T("false"));
			m_listControl_shapes.SetItemText(nItem, 5, str);
		}
	}

	// filling line listview
	for (auto l : lines)
	{
		str.Format(_T("%d"), l->ID);
		nItem = m_listControl_lines.InsertItem(0, str);
		if (l->type == LineType::Basic)
		{
			m_listControl_lines.SetItemText(nItem, 1, _T("Basic line"));
		}
		else if (l->type == LineType::Right)
		{
			m_listControl_lines.SetItemText(nItem, 1, _T("Right line"));
		}
		else if (l->type == LineType::Left)
		{
			m_listControl_lines.SetItemText(nItem, 1, _T("Left line"));
		}
		else
		{
			m_listControl_lines.SetItemText(nItem, 1, _T("Double line"));
		}
		m_listControl_lines.SetItemText(nItem, 2, l->name);
		// find ID from constID
		int tempFoundedID1;
		int tempFoundedID2;
		CString type1; // type of shapes that will be founded
		CString type2; // ---
		for (auto s : shapes)
		{
			if (s->constID == l->FirstShapeConstID)
			{
				tempFoundedID1 = s->ID;
				switch (s->type)
				{
					case ShapeType::ellipse:
					{
						type1 = _T("Ellipse");
						break;
					}
					case ShapeType::rectangle:
					{
						type1 = _T("Rectangle");
						break;
					}
					case ShapeType::triangle:
					{
						type1 = _T("Triangle");
						break;
					}
					
				}
				//break; don't need because constID's are unique
				
			}
			else if (s->constID == l->SecondShapeConstID)
			{
				tempFoundedID2 = s->ID;
				switch (s->type)
				{
				case ShapeType::ellipse:
				{
					type2 = _T("Ellipse");
					break;
				}
				case ShapeType::rectangle:
				{
					type2 = _T("Rectangle");
					break;
				}
				case ShapeType::triangle:
				{
					type2 = _T("Triangle");
					break;
				}
				}
				//break; don't need because constID's are unique
			}
		}

		str.Format(_T("%d"), tempFoundedID1);
		m_listControl_lines.SetItemText(nItem, 3, str);
		m_listControl_lines.SetItemText(nItem, 4, type1);
		str.Format(_T("%d"), tempFoundedID2);
		m_listControl_lines.SetItemText(nItem, 5, str);
		m_listControl_lines.SetItemText(nItem, 6, type2);
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
