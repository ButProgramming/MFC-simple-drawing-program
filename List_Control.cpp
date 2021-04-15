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
	m_listControl_shapes.InsertColumn(0, _T("ID"), LVCFMT_LEFT, 50);
	m_listControl_shapes.InsertColumn(1, _T("Type"), LVCFMT_CENTER, 100);
	m_listControl_shapes.InsertColumn(2, _T("Name"), LVCFMT_CENTER, 100);
	m_listControl_shapes.InsertColumn(3, _T("Center"), LVCFMT_CENTER, 150);
	m_listControl_shapes.InsertColumn(4, _T("Angle"), LVCFMT_CENTER, 100);
	m_listControl_shapes.InsertColumn(5, _T("Outline RGB"), LVCFMT_CENTER, 150);
	m_listControl_shapes.InsertColumn(6, _T("Outline size"), LVCFMT_CENTER, 100);
	m_listControl_shapes.InsertColumn(7, _T("Outline type"), LVCFMT_CENTER, 100);
	m_listControl_shapes.InsertColumn(8, _T("Fill RGB"), LVCFMT_CENTER, 150);
	m_listControl_shapes.InsertColumn(9, _T("Fill type"), LVCFMT_CENTER, 100);


	//m_listControl_shapes.InsertColumn(5, _T("Is selected"), LVCFMT_CENTER, 70);

	// InsertColumnt for lines
	DDX_Control(pDX, IDC_LISTCONTROL_LINES, m_listControl_lines);
	m_listControl_lines.InsertColumn(0, _T("ID"), LVCFMT_CENTER, 50);
	m_listControl_lines.InsertColumn(1, _T("Type"), LVCFMT_CENTER, 100);
	m_listControl_lines.InsertColumn(2, _T("Name"), LVCFMT_CENTER, 100);
	m_listControl_lines.InsertColumn(3, _T("First shape id"), LVCFMT_CENTER, 100);
	m_listControl_lines.InsertColumn(4, _T("First shape type"), LVCFMT_CENTER, 150);
	m_listControl_lines.InsertColumn(5, _T("Second shape id"), LVCFMT_CENTER, 100);
	m_listControl_lines.InsertColumn(6, _T("Second shape type"), LVCFMT_CENTER, 150);
	m_listControl_lines.InsertColumn(7, _T("Line RGB"), LVCFMT_CENTER, 150);
	m_listControl_lines.InsertColumn(8, _T("Line size"), LVCFMT_CENTER, 100);
	m_listControl_lines.InsertColumn(9, _T("Line type"), LVCFMT_CENTER, 100);

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
		str.Format(_T("R: %d, G: %d, B: %d"), s->oR, s->oG, s->oB);
		m_listControl_shapes.SetItemText(nItem, 5, str);
		str.Format(_T("%d"), s->outlineSize);
		m_listControl_shapes.SetItemText(nItem, 6, str);
		// outlineType
		switch (s->outlineType)
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
		m_listControl_shapes.SetItemText(nItem, 7, str);
		str.Format(_T("R: %d, G: %d, B: %d"), s->fR, s->fG, s->fB);
		m_listControl_shapes.SetItemText(nItem, 8, str);
		//Normal;Horizontal hatch;Vertical hatch;Upward hatch;Downward hatch;Horizontal and vertical crosshatch;Crosshatch at 45 degrees;
		switch (s->fillType)
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
		str.Format(_T("R: %d, G: %d, B: %d"), l->lR, l->lG, l->lB);
		m_listControl_lines.SetItemText(nItem, 7, str);
		str.Format(_T("%d"), l->lineSize);
		m_listControl_lines.SetItemText(nItem, 8, str);
		// ____ ;_ _ _;.....;_._;_.._;
		switch (l->lineType)
		{
			case 0:
			{
				str.Format(_T("____"));
				break;
			}
			case 1:
			{
				str.Format(_T("_ _ _"));
				break;
			}
			case 2:
			{
				str.Format(_T("....."));
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
		//str.Format(_T("%d"), l->lineSize);
		m_listControl_lines.SetItemText(nItem, 9, str);
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
