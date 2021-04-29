
// EgoSecure_Test_AssignmentView.cpp : implementation of the CEgoSecureTestAssignmentView class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "EgoSecure_Test_Assignment.h"
#endif

#include "EgoSecure_Test_AssignmentDoc.h"
#include "EgoSecure_Test_AssignmentView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")
#endif
#include "Shape.h"
#include "List_Control.h"
#include "Default_draw_properties.h"
#include "Dialog_Properties.h"
#include "Dialog_Link_Properties.h"


using namespace std;

// CEgoSecureTestAssignmentView

IMPLEMENT_DYNCREATE(CEgoSecureTestAssignmentView, CView)

BEGIN_MESSAGE_MAP(CEgoSecureTestAssignmentView, CView)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_LBUTTONDOWN()
	ON_COMMAND(ID_BUTTON_ELLIPSE, &CEgoSecureTestAssignmentView::OnButtonEllipse)
	ON_COMMAND(ID_BUTTON_RECTANGLE, &CEgoSecureTestAssignmentView::OnButtonRectangle)
	ON_COMMAND(ID_BUTTON_TRIANGLE, &CEgoSecureTestAssignmentView::OnButtonTriangle)
	ON_WM_MOUSEMOVE()
	ON_WM_ERASEBKGND()
	ON_WM_CREATE()
	ON_COMMAND(ID_BUTTON_SELECT_TOOL, &CEgoSecureTestAssignmentView::OnButtonSelectTool)
	ON_WM_LBUTTONDBLCLK()
	ON_COMMAND(ID_BUTTON_MOVE, &CEgoSecureTestAssignmentView::OnButtonMove)
	ON_WM_LBUTTONUP()
	ON_COMMAND(ID_BUTTON_CHANGE, &CEgoSecureTestAssignmentView::OnButtonChange)
	ON_COMMAND(ID_BUTTON_ROTATE, &CEgoSecureTestAssignmentView::OnButtonRotate)
	ON_COMMAND(ID_BUTTON_SHAPE_NORMALIZE, &CEgoSecureTestAssignmentView::OnButtonShapeNormalize)
	ON_COMMAND(ID_BUTTON_SHAPE_MOVE, &CEgoSecureTestAssignmentView::OnButtonShapeMove)
	ON_COMMAND(ID_BUTTON_DELETE, &CEgoSecureTestAssignmentView::OnButtonDelete)
	ON_COMMAND(ID_BUTTON_DOUBLE_SELECT, &CEgoSecureTestAssignmentView::OnButtonDoubleSelect)
	ON_COMMAND(ID_BUTTON_BASIC_LINE, &CEgoSecureTestAssignmentView::OnButtonBasicLine)
	ON_COMMAND(ID_BUTTON_RIGHT_LINE, &CEgoSecureTestAssignmentView::OnButtonRightLine)
	ON_COMMAND(ID_BUTTON_LEFT_LINE, &CEgoSecureTestAssignmentView::OnButtonLeftLine)
	ON_COMMAND(ID_BUTTON_DOUBLE_LINE, &CEgoSecureTestAssignmentView::OnButtonDoubleLine)
	ON_COMMAND(ID_PROPERTIES_ALLSHAPESANDLINES, &CEgoSecureTestAssignmentView::OnPropertiesAllshapesandlines)
	ON_COMMAND(IDC_LISTCONTROL_SHAPES, &CEgoSecureTestAssignmentView::OnListcontrolShapes)
	ON_COMMAND(ID_PROPERTIES_DEFAULTDRAWPROPERTIES, &CEgoSecureTestAssignmentView::OnPropertiesDefaultdrawproperties)
	ON_COMMAND(ID_BUTTON_PROPERTIES, &CEgoSecureTestAssignmentView::OnButtonProperties)
	ON_COMMAND(ID_EDIT_NORMALIZE, &CEgoSecureTestAssignmentView::OnEditNormalize)
	ON_WM_HSCROLL()
	ON_WM_VSCROLL()
END_MESSAGE_MAP()

// CEgoSecureTestAssignmentView construction/destruction

CEgoSecureTestAssignmentView::CEgoSecureTestAssignmentView() noexcept
{

	// TODO: add construction code here

}

CEgoSecureTestAssignmentView::~CEgoSecureTestAssignmentView()
{
}

BOOL CEgoSecureTestAssignmentView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CEgoSecureTestAssignmentView drawing

void CEgoSecureTestAssignmentView::OnDraw(CDC* pDC)
{
	CEgoSecureTestAssignmentDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// get parameters for CDC
	CPoint point;
	CRect rect;
	GetCursorPos(&point);
	GetClientRect(&rect);
	point.x -= rect.left;
	point.y -= rect.top;
	m_dc.FillSolidRect(rect, RGB(255, 255, 255));


	//draw all shapes
	for (int shapeNum = 0; shapeNum<pDoc->getShapesVector().size(); shapeNum++)
	{
		pDoc->getShapesVector()[shapeNum]->draw(&m_dc);
		if (pDoc->getShapesVector()[shapeNum]->getShapeType() == ShapeType::basicLine)
		{
			cout << pDoc->getShapesVector()[shapeNum]->getCoordinateForChange(0).x << " " << pDoc->getShapesVector()[shapeNum]->getCoordinateForChange(0).y << endl;
			cout << pDoc->getShapesVector()[shapeNum]->getCoordinateForChange(1).x << " " << pDoc->getShapesVector()[shapeNum]->getCoordinateForChange(1).y << endl;
		}
	}

	//pen->DeleteObject();
	pDC->BitBlt(0, 0, rect.Width(), rect.Height(), &m_dc, 0, 0, SRCCOPY);



	
	// TODO: add draw code for native data here
}

void CEgoSecureTestAssignmentView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CEgoSecureTestAssignmentView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
	auto pDoc = GetDocument();
	CMenu menu;
	menu.LoadMenu(IDR_POPUP_EDIT);
	CMenu* pMenu = menu.GetSubMenu(0);

	//PopulateBookmarkMenu(pMenu);
	bool selectedShapeDontExcist = true;
	for (int shapeNum = 0; shapeNum < pDoc->getShapesVector().size(); shapeNum++)
	{
		if (pDoc->getShapesVector()[shapeNum]->getSelected())
		{
			selectedShapeDontExcist = false;
			break;
		}
	}
	if (selectedShapeDontExcist)
	{
		pMenu->EnableMenuItem(ID_EDIT_NORMALIZE, MF_DISABLED | MF_GRAYED);
	}

	pMenu->TrackPopupMenu(TPM_LEFTBUTTON, point.x, point.y, this, NULL);
#ifndef SHARED_HANDLERS
	//theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CEgoSecureTestAssignmentView diagnostics

#ifdef _DEBUG
void CEgoSecureTestAssignmentView::AssertValid() const
{
	CView::AssertValid();
}

void CEgoSecureTestAssignmentView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CEgoSecureTestAssignmentDoc* CEgoSecureTestAssignmentView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CEgoSecureTestAssignmentDoc)));
	return (CEgoSecureTestAssignmentDoc*)m_pDocument;
}
#endif //_DEBUG


// CEgoSecureTestAssignmentView message handlers


void CEgoSecureTestAssignmentView::OnLButtonDown(UINT nFlags, CPoint point)
{
	auto pDoc = GetDocument();
	bool canBeUnselected = true;
	bool shapeIsFound = false;

	// check if tool is not line to draw on shape and don't select it
	if (pDoc->getToolIsUsed() != Tools::basicLine && pDoc->getToolIsUsed() != Tools::rightLine 
		&& pDoc->getToolIsUsed() != Tools::leftLine && pDoc->getToolIsUsed() != Tools::doubleLine)
	{
		// start from the end because we click on shapes, that are located on the surface
		for (int shapeNum = pDoc->getShapesVector().size() - 1; shapeNum >= 0; shapeNum--)
		{
			// move, change, or rotate shape
			pDoc->getShapesVector()[shapeNum]->moveChangeRotate(pDoc->getShapesVector(), pDoc->getToolIsUsed(), point, canBeUnselected, shapeIsFound); // return true if can be unselected

			//break loop if shape is found
			if (shapeIsFound) break;
		}
	}

	//check if can be all shapes unselected
	if (canBeUnselected)
	{
		if (pDoc->getToolIsUsed() != Tools::basicLine && pDoc->getToolIsUsed() != Tools::rightLine 
			&& pDoc->getToolIsUsed() != Tools::leftLine && pDoc->getToolIsUsed() != Tools::doubleLine)
		{
			for (int shapeNum = 0; shapeNum < pDoc->getShapesVector().size(); shapeNum++)
			{
				pDoc->getShapesVector()[shapeNum]->setSelected(false);
				pDoc->getShapesVector()[shapeNum]->setCanDrawPointsForLines(false);
			}
		}
	}
	
	// update drawing
	Invalidate();
	
	// create shape or choose an other tool
	switch (pDoc->getToolIsUsed())
	{
	case Tools::ellipse:
	{
		IShape* shape = new EllipseShape(point, true, 0, ShapeType::ellipse, pDoc->m_outline_color, pDoc->m_fill_color, pDoc->num_cb_outline_size, pDoc->num_cb_outline_type, pDoc->num_cb_fill_type);
		pDoc->getShapesVector().push_back(shape);
		break;
	}
	case Tools::rectangle:
	{
		IShape* shape = new RectangleShape(point, true, 0, ShapeType::rectangle, pDoc->m_outline_color, pDoc->m_fill_color, pDoc->num_cb_outline_size, pDoc->num_cb_outline_type, pDoc->num_cb_fill_type);
		pDoc->getShapesVector().push_back(shape);
		break;
	}
	case Tools::triangle:
	{
		IShape* shape = new TriangleShape(point, true, 0, ShapeType::triangle, pDoc->m_outline_color, pDoc->m_fill_color, pDoc->num_cb_outline_size, pDoc->num_cb_outline_type, pDoc->num_cb_fill_type);
		pDoc->getShapesVector().push_back(shape);
		break;
	}
	case Tools::basicLine:
	{
		IShape* line = new Line(point, ShapeType::basicLine, RGB(0, 0, 0), 1, 1);
		pDoc->getShapesVector().push_back(line);
		break;
	}
	case Tools::rightLine:
	{
		IShape* line = new Line(point, ShapeType::rightLine, RGB(0, 0, 0), 1, 1);
		pDoc->getShapesVector().push_back(line);
		break;
	}
	case Tools::leftLine:
	{
		IShape* line = new Line(point, ShapeType::leftLine, RGB(0, 0, 0), 1, 1);
		pDoc->getShapesVector().push_back(line);
		break;
	}
	case Tools::doubleLine:
	{
		IShape* line = new Line(point, ShapeType::doubleLine, RGB(0, 0, 0), 1, 1);
		pDoc->getShapesVector().push_back(line);
		break;
	}
	case Tools::move:
		pDoc->first.x = point.x;
		pDoc->first.y = point.y;
		break;
	case Tools::shapeMove:
		/*pDoc->first.x = point.x;
		pDoc->first.y = point.y;*/
		for (int shapeNum = 0; shapeNum < pDoc->getShapesVector().size(); shapeNum++)
		{
			if (pDoc->getShapesVector()[shapeNum]->getSelected())
			{
				pDoc->getShapesVector()[shapeNum]->setShapeMoveStartClickedCoordinate(point);
			}
		}
		break;
	case Tools::rotate:
	{
		bool selected = false;
		for (int i = 0; i < pDoc->getShapesVector().size(); i++)
		{
			if (pDoc->getShapesVector()[i]->getSelected())
			{
				pDoc->getShapesVector()[i]->setFirstClickedPoint(point);
				//pDoc->getShapesVector()[i]->lastY = point.y;
				selected = true;
			}
			if (selected) break;
		}
		break;
	}
	case Tools::change:
		
		//new
		for (int shapeNum = 0; shapeNum < pDoc->getShapesVector().size(); shapeNum++)
		{
			if (pDoc->getShapesVector()[shapeNum]->getSelected())
			{
				pDoc->getShapesVector()[shapeNum]->setChangeStartClickedCoordinate(point);
			}
		}
		//bool selected = false; // control of the next loop
		for (int s = 0; s < pDoc->getShapesVector().size(); s++)
		{
			if (pDoc->getShapesVector()[s]->getSelected())
			{
				
				//selected = true;
				//pDoc->getShapesVector()[s]->numberOfAngle = -1;

				pDoc->getShapesVector()[s]->isClickedPointForChange(point); // this method set also number of clicked point for variable numberOfPoint
				

		

			}
			if (pDoc->getShapesVector()[s]->getSelected())
				break;
		}
		break;
	}
	CView::OnLButtonDown(nFlags, point);
}


void CEgoSecureTestAssignmentView::OnButtonEllipse()
{
	// TODO: Add your command handler code here
	auto pDoc = GetDocument();
	for(int shapeNum = 0; shapeNum< pDoc->getShapesVector().size(); shapeNum++)
	{
		pDoc->getShapesVector()[shapeNum]->setSelected(false);
		pDoc->getShapesVector()[shapeNum]->setCanDrawPointsForLines(false);
	}
	pDoc->getToolIsUsed() = Tools::ellipse;
	Invalidate();

}


void CEgoSecureTestAssignmentView::OnButtonRectangle()
{
	// TODO: Add your command handler code here}
	auto pDoc = GetDocument();
	for (int shapeNum = 0; shapeNum < pDoc->getShapesVector().size(); shapeNum++)
	{
		pDoc->getShapesVector()[shapeNum]->setSelected(false);
		pDoc->getShapesVector()[shapeNum]->setCanDrawPointsForLines(false);
	}
	/*for (auto s : pDoc->getShapesVector())
	{
		s->isSelected = false;
	}*/
	pDoc->getToolIsUsed() = Tools::rectangle;
	Invalidate();
}


void CEgoSecureTestAssignmentView::OnButtonTriangle()
{
	// TODO: Add your command handler code here
	auto pDoc = GetDocument();
	for (int shapeNum = 0; shapeNum < pDoc->getShapesVector().size(); shapeNum++)
	{
		pDoc->getShapesVector()[shapeNum]->setSelected(false);
		pDoc->getShapesVector()[shapeNum]->setCanDrawPointsForLines(false);
	}
	/*for (auto s : pDoc->getShapesVector())
	{
		s->isSelected = false;
	}*/
	pDoc->getToolIsUsed() = Tools::triangle;
	Invalidate();
}


void CEgoSecureTestAssignmentView::OnMouseMove(UINT nFlags, CPoint point)
{
	
	int dx = 0;
	int dy = 0;

	// change size of shape
	CEgoSecureTestAssignmentDoc* pDoc = GetDocument();

	// update all connections
	for (int shapeNum = 0; shapeNum < pDoc->getShapesVector().size(); shapeNum++)
	{
		//pDoc->getShapesVector()[shapeNum]->type;
		if (pDoc->getShapesVector()[shapeNum]->getShapeType() == ShapeType::basicLine || pDoc->getShapesVector()[shapeNum]->getShapeType() == ShapeType::rightLine
			|| pDoc->getShapesVector()[shapeNum]->getShapeType() == ShapeType::leftLine || pDoc->getShapesVector()[shapeNum]->getShapeType() == ShapeType::doubleLine)
		{
			pDoc->getShapesVector()[shapeNum]->updateLineConnection(pDoc->getShapesVector());
		}
	}
	
	if (nFlags == MK_LBUTTON && (pDoc->getToolIsUsed() == Tools::ellipse || pDoc->getToolIsUsed() == Tools::rectangle || pDoc->getToolIsUsed() == Tools::triangle))
	{
		pDoc->getShapesVector()[pDoc->getShapesVector().size() - 1]->setSize(sqrt(pow((pDoc->getShapesVector()[pDoc->getShapesVector().size() - 1])->getCenterOfShape().x - point.x, 2) + pow((pDoc->getShapesVector()[pDoc->getShapesVector().size() - 1])->getCenterOfShape().y - point.y, 2)));
	}
	else if (nFlags == MK_LBUTTON && pDoc->getToolIsUsed() == Tools::move)
	{
		pDoc->second.x = point.x;
		pDoc->second.y = point.y;
		IShape::setDx(pDoc->second.x - pDoc->first.x);
		IShape::setDy(pDoc->second.y - pDoc->first.y);

	}
	else if (nFlags == MK_LBUTTON && pDoc->getToolIsUsed() == Tools::shapeMove)
	{
		/*pDoc->second.x = point.x;
		pDoc->second.y = point.y;*/
		for (int s = 0; s < pDoc->getShapesVector().size(); s++)
		{
			if (pDoc->getShapesVector()[s]->getSelected())
			{
				// set temp dx dy to move shape
				pDoc->getShapesVector()[s]->setShapeMoveTempDxDy(CPoint{ point.x - pDoc->getShapesVector()[s]->getShapeMoveStartClickedCoordinate().x, point.y - pDoc->getShapesVector()[s]->getShapeMoveStartClickedCoordinate().y });
				
				// rotate and move coordinate and set to temp dx dy
				pDoc->getShapesVector()[s]->setShapeMoveTempDxDy(pDoc->getShapesVector()[s]->rotateAndMoveCoordinate(pDoc->getShapesVector()[s]->getShapeMoveTempDxDy()/*, pDoc->getToolIsUsed()*/, MOUSE_MOVE));
			}
		}
		for (int lineNum = 0; lineNum < pDoc->getShapesVector().size(); lineNum++)
		{
			pDoc->getShapesVector()[lineNum]->updateLineConnection(pDoc->getShapesVector());
		}


	}
	else if (nFlags == MK_LBUTTON && pDoc->getToolIsUsed() == Tools::change)
	{
		bool selected = false; // control of the next loop
	
		for (int s = 0; s < pDoc->getShapesVector().size(); s++)
		{
			//
			if (pDoc->getShapesVector()[s]->getSelected())
			{
				
				//selected = true;
				if (pDoc->getShapesVector()[s]->getNumberOfPointForChange() != -1)
				{
					// set change of mouse movement 
					pDoc->getShapesVector()[s]->setChangeTempDxDy(pDoc->getShapesVector()[s]->getNumberOfPointForChange(), CPoint{ point - pDoc->getShapesVector()[s]->getChangeStartClickedCoordinate() });
					
					// use rotate method and set rotated coordinates
					pDoc->getShapesVector()[s]->setChangeTempDxDy(pDoc->getShapesVector()[s]->getNumberOfPointForChange(), pDoc->getShapesVector()[s]->rotateAndMoveCoordinate(pDoc->getShapesVector()[s]->getChangeTempDxDy(pDoc->getShapesVector()[s]->getNumberOfPointForChange())/*, pDoc->getToolIsUsed()*/, MOUSE_MOVE));
					Invalidate();
					
				}
			}
			if (pDoc->getShapesVector()[s]->getSelected())
				break;
		}
	}
	else if (nFlags == MK_LBUTTON && pDoc->getToolIsUsed() == Tools::rotate) // rotate shape
	{
		for (int s = 0; s < pDoc->getShapesVector().size(); s++)
		{
			if (pDoc->getShapesVector()[s]->getSelected())
			{
				pDoc->getShapesVector()[s]->rotateShape(point);
			}
			Invalidate();
		}

	}
	else if (nFlags == MK_LBUTTON && (pDoc->getToolIsUsed() == Tools::basicLine || pDoc->getToolIsUsed() == Tools::rightLine 
		|| pDoc->getToolIsUsed() == Tools::leftLine || pDoc->getToolIsUsed() == Tools::doubleLine))
	{
		if (!pDoc->getShapesVector().empty())
		{
			pDoc->getShapesVector()[pDoc->getShapesVector().size() - 1]->setCoordinateForChange(1, point);
		}
	}
	Invalidate();
	CView::OnMouseMove(nFlags, point);
}


BOOL CEgoSecureTestAssignmentView::OnEraseBkgnd(CDC* pDC)
{
	// TODO: Add your message handler code here and/or call default

	return true;
}

int CEgoSecureTestAssignmentView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	auto pDoc = GetDocument();
	CPoint point;
	CRect rect;
	GetCursorPos(&point);
	GetClientRect(&rect);
	point.x -= rect.left;
	point.y -= rect.top;
	CClientDC dc(this);
	int x = ::GetSystemMetrics(SM_CXSCREEN);
	int y = ::GetSystemMetrics(SM_CXSCREEN);
	m_dc.CreateCompatibleDC(&dc);
	m_bmt.CreateCompatibleBitmap(&dc, x, y);
	m_dc.SelectObject(&m_bmt);
	m_dc.FillSolidRect(rect, RGB(255, 255, 255));

	// create horizontal scroll bar and set range
	m_hsb.Create(SBS_HORZ | SBS_TOPALIGN | WS_CHILD | WS_VISIBLE,
		CRect(0, y / DIVISOR_DOWN_POS_HORIZONTAL_SCROLL_BAR, x * MULTIPLIER_RIGHT_POS_HORIZONTAL_SCROLL_BAR, 300), this, IDC_SB_HOR);
	m_hsb.SetScrollRange(START_HORIZONTAL_SCROLL_RANGE_MIN, START_HORIZONTAL_SCROLL_RANGE_MAX);

	// create vertical scroll bar and set range
	m_vsb.Create(SBS_VERT | SBS_LEFTALIGN | SBS_BOTTOMALIGN | WS_CHILD | WS_VISIBLE,
		CRect(0, 0, 0, y / DIVISOR_DOWN_POS_HORIZONTAL_SCROLL_BAR), this, IDC_SB_VERT);
	m_vsb.SetScrollRange(START_VERTICAL_SCROLL_RANGE_MIN, START_VERTICAL_SCROLL_RANGE_MAX);

	

	return 0;
}




void CEgoSecureTestAssignmentView::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// get document to have an access to shapes vector
	auto pDoc = GetDocument();

	// set position of scroll in horizontal scrollbar
	switch (nSBCode)
	{
	case SB_THUMBTRACK:
		horizontalScrollBarValue = nPos;
	}
	m_hsb.SetScrollPos(horizontalScrollBarValue);

	// update range of horizontal scrollbar
	if (m_hsb.GetScrollPos() == valueOfHorizontalScrollBar.min && !(GetKeyState(VK_LBUTTON) & 0x8000))
	{
		valueOfHorizontalScrollBar.min -= HORIZONTAL_SCROLLBAR_DX;
		m_hsb.SetScrollRange(valueOfHorizontalScrollBar.min, valueOfHorizontalScrollBar.max);
		m_hsb.SetScrollPos(valueOfHorizontalScrollBar.min + HORIZONTAL_SCROLLBAR_DX);
	}
	else if (m_hsb.GetScrollPos() == valueOfHorizontalScrollBar.max && !(GetKeyState(VK_LBUTTON) & 0x8000))
	{
		valueOfHorizontalScrollBar.max += HORIZONTAL_SCROLLBAR_DX;
		m_hsb.SetScrollRange(valueOfHorizontalScrollBar.min, valueOfHorizontalScrollBar.max);
		m_hsb.SetScrollPos(valueOfHorizontalScrollBar.max - HORIZONTAL_SCROLLBAR_DX);
	}

	// move the shapes
	IShape::setDx(prevCoordinate.x - 2 * m_hsb.GetScrollPos());
	for (int shapeNum = 0; shapeNum < pDoc->getShapesVector().size(); shapeNum++)
	{
		if (pDoc->getShapesVector()[shapeNum]->getShapeType() == ShapeType::basicLine || pDoc->getShapesVector()[shapeNum]->getShapeType() == ShapeType::rightLine
			|| pDoc->getShapesVector()[shapeNum]->getShapeType() == ShapeType::leftLine || pDoc->getShapesVector()[shapeNum]->getShapeType() == ShapeType::doubleLine)
		{
			pDoc->getShapesVector()[shapeNum]->setCoordinateForChange(0, CPoint(pDoc->getShapesVector()[shapeNum]->getCoordinateForChange(0).x + IShape::getDx(), pDoc->getShapesVector()[shapeNum]->getCoordinateForChange(0).y));
			pDoc->getShapesVector()[shapeNum]->setCoordinateForChange(1, CPoint(pDoc->getShapesVector()[shapeNum]->getCoordinateForChange(1).x + IShape::getDx(), pDoc->getShapesVector()[shapeNum]->getCoordinateForChange(1).y));
		}
		//pDoc->getShapesVector()[shapeNum]->centerOfShape.x += IShape::dx;
		pDoc->getShapesVector()[shapeNum]->setCenterOfShape(CPoint{ pDoc->getShapesVector()[shapeNum]->getCenterOfShape().x + IShape::getDx(), pDoc->getShapesVector()[shapeNum]->getCenterOfShape().y });
	}

	// reset dx
	IShape::setDx(NULL);

	// update draw
	Invalidate();

	// safe currently coordinate in previous coordinate to calculate dx for moving shapes in the next time
	prevCoordinate.x = 2 * m_hsb.GetScrollPos();

	CView::OnHScroll(nSBCode, nPos, pScrollBar);
}

void CEgoSecureTestAssignmentView::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// get document to have an access to shapes vector
	auto pDoc = GetDocument();

	// set position of scroll in horizontal scrollbar
	switch (nSBCode)
	{
	case SB_THUMBTRACK:
		verticalScrollBarValue = nPos;
	}
	m_vsb.SetScrollPos(verticalScrollBarValue);

	// update range of vertical scrollbar
	if (m_vsb.GetScrollPos() == valueOfVerticalScrollBar.min && !(GetKeyState(VK_LBUTTON) & 0x8000))
	{
		valueOfVerticalScrollBar.min -= VERTICAL_SCROLLBAR_DX;
		m_vsb.SetScrollRange(valueOfVerticalScrollBar.min, valueOfVerticalScrollBar.max);
		m_vsb.SetScrollPos(valueOfVerticalScrollBar.min + VERTICAL_SCROLLBAR_DX);
	}
	else if (m_vsb.GetScrollPos() == valueOfVerticalScrollBar.max && !(GetKeyState(VK_LBUTTON) & 0x8000))
	{
		valueOfVerticalScrollBar.max += VERTICAL_SCROLLBAR_DX;
		m_vsb.SetScrollRange(valueOfVerticalScrollBar.min, valueOfVerticalScrollBar.max);
		m_vsb.SetScrollPos(valueOfVerticalScrollBar.max - VERTICAL_SCROLLBAR_DX);
	}

	// move the shapes
	IShape::setDy(prevCoordinate.y - 2 * m_vsb.GetScrollPos());
	for (int shapeNum = 0; shapeNum < pDoc->getShapesVector().size(); shapeNum++)
	{
		if (pDoc->getShapesVector()[shapeNum]->getShapeType() == ShapeType::basicLine || pDoc->getShapesVector()[shapeNum]->getShapeType() == ShapeType::rightLine
			|| pDoc->getShapesVector()[shapeNum]->getShapeType() == ShapeType::leftLine || pDoc->getShapesVector()[shapeNum]->getShapeType() == ShapeType::doubleLine)
		{
			//move y
			//pDoc->getShapesVector()[shapeNum]->firstPointOfLine.y += IShape::dy;
			//pDoc->getShapesVector()[shapeNum]->secondPointOfLine.y += IShape::dy;

			pDoc->getShapesVector()[shapeNum]->setCoordinateForChange(0, CPoint(pDoc->getShapesVector()[shapeNum]->getCoordinateForChange(0).x, pDoc->getShapesVector()[shapeNum]->getCoordinateForChange(0).y + IShape::getDy()));
			pDoc->getShapesVector()[shapeNum]->setCoordinateForChange(1, CPoint(pDoc->getShapesVector()[shapeNum]->getCoordinateForChange(1).x, pDoc->getShapesVector()[shapeNum]->getCoordinateForChange(1).y + IShape::getDy()));

		}
		//pDoc->getShapesVector()[shapeNum]->centerOfShape.y += IShape::dy;
		pDoc->getShapesVector()[shapeNum]->setCenterOfShape(CPoint{ pDoc->getShapesVector()[shapeNum]->getCenterOfShape().x, pDoc->getShapesVector()[shapeNum]->getCenterOfShape().y + IShape::getDy() });
	}

	// reset dx
	IShape::setDy(NULL);

	// update draw
	Invalidate();

	// safe currently coordinate in previous coordinate to calculate dx for moving shapes in the next time
	prevCoordinate.y = 2 * m_vsb.GetScrollPos();

	CView::OnVScroll(nSBCode, nPos, pScrollBar);
}


void CEgoSecureTestAssignmentView::OnButtonSelectTool()
{
	auto pDoc = GetDocument();
	for (auto s : pDoc->getShapesVector())
	{
		s->setSelected(false);
	}
	queue<int> clear;
	swap(clear, pDoc->selectedShapesIDs);
	/*for (auto s : pDoc->getShapesVector())
	{
		s->isSelectedFromDoubleSelectingTool = false;
	}*/
	pDoc->getToolIsUsed() = Tools::select_tool;
	Invalidate();
	// TODO: Add your command handler code here
}


void CEgoSecureTestAssignmentView::OnLButtonDblClk(UINT nFlags, CPoint point)
{
//	//AfxMessageBox(_T("123"));
//	auto pDoc = GetDocument();
//	int sizeOfShapesVector = pDoc->getShapesVector().size();
//	bool shapeIsFound = false; //exit from for loop if = true
//	if (pDoc->getToolIsUsed() == Tools::select_tool)
//	{
//		for (int i = sizeOfShapesVector - 1; i >= 0; i--)
//		{
//			switch (pDoc->getShapesVector()[i]->type)
//			{
//			case ShapeType::ellipse:
//			{
//				CPoint cp;
//				CString str;
//				HRGN ellipseRgn1 = CreatePolygonRgn(&(pDoc->getShapesVector()[i]->eFP[0]), pDoc->getShapesVector()[i]->eFP.size(), ALTERNATE);// = CreatePolygonRgn(;
//				HRGN ellipseRgn2 = CreatePolygonRgn(&(pDoc->getShapesVector()[i]->eSP[0]), pDoc->getShapesVector()[i]->eSP.size(), ALTERNATE);
//
//				if (PtInRegion(ellipseRgn1, point.x, point.y) || PtInRegion(ellipseRgn2, point.x, point.y))
//				{
//					shapeIsFound = true;
//					for (int i = sizeOfShapesVector - 1; i >= 0; i--)
//					{
//						//unselecting others shapes
//						if (pDoc->getShapesVector()[i]->isSelected == true)
//						{
//							pDoc->getShapesVector()[i]->pen->DeleteObject();
//							pDoc->getShapesVector()[i]->isSelected = false;
//							break;
//						};
//					}
//					//swap
//					pDoc->getShapesVector()[i]->isSelected = true;
//					/*pDoc->getShapesVector()[i]->isSelected = true;
//					IShape* shape;
//					pDoc->getShapesVector().push_back(shape);
//					iter_swap(pDoc->getShapesVector().begin() + i, pDoc->getShapesVector().end() - 1);
//					pDoc->getShapesVector().erase(pDoc->getShapesVector().begin() + i);*/
//				}
//				DeleteObject(ellipseRgn1);
//				DeleteObject(ellipseRgn2);
//				break;
//			}
//			case ShapeType::rectangle:
//			{
//				CPoint rectangleCenter = pDoc->getShapesVector()[i]->centerOfShape; //convinient
//				int rectangleSize = pDoc->getShapesVector()[i]->size; //convinient
//				HRGN rectangleRgn = CreatePolygonRgn(&(pDoc->getShapesVector()[i]->points[0]), 4, ALTERNATE);
//				if (PtInRegion(rectangleRgn, point.x, point.y))
//				{
//					//AfxMessageBox(_T("Rectangle"));
//					shapeIsFound = true;
//					for (int i = sizeOfShapesVector - 1; i >= 0; i--)
//					{
//						//unselecting others shapes
//						if (pDoc->getShapesVector()[i]->isSelected == true)
//						{
//							pDoc->getShapesVector()[i]->pen->DeleteObject();
//							pDoc->getShapesVector()[i]->isSelected = false;
//							break;
//						};
//					}
//					pDoc->getShapesVector()[i]->isSelected = true;
//					IShape* shape;
//					pDoc->getShapesVector().push_back(shape);
//					iter_swap(pDoc->getShapesVector().begin() + i, pDoc->getShapesVector().end() - 1);
//					pDoc->getShapesVector().erase(pDoc->getShapesVector().begin() + i);
//					Invalidate();
//				}
//				DeleteObject(rectangleRgn);
//
//				break;
//			}
//			case ShapeType::triangle:
//			{
//				CPoint rectangleCenter = pDoc->getShapesVector()[i]->centerOfShape; //convinient
//				int rectangleSize = pDoc->getShapesVector()[i]->size; //convinient
//				int h = 3 * rectangleSize;
//				int side = 2 * h / sqrt(3);
//
//				HRGN rectangleRgn = CreatePolygonRgn(&(pDoc->getShapesVector()[i]->points[0]), 3, ALTERNATE);
//				//CreateEllipticRgn(rectangleCenter.x - rectangleSize, rectangleCenter.y - rectangleSize, rectangleCenter.x + rectangleSize, rectangleCenter.y + rectangleSize);
//				if (PtInRegion(rectangleRgn, point.x, point.y))
//				{
//					shapeIsFound = true;
//					for (int i = sizeOfShapesVector - 1; i >= 0; i--)
//					{
//						//unselecting others shapes
//						if (pDoc->getShapesVector()[i]->isSelected == true)
//						{
//							pDoc->getShapesVector()[i]->pen->DeleteObject();
//							pDoc->getShapesVector()[i]->isSelected = false;
//							break;
//						};
//					}
//					pDoc->getShapesVector()[i]->isSelected = true;
//					IShape* shape;
//					pDoc->getShapesVector().push_back(shape);
//					iter_swap(pDoc->getShapesVector().begin() + i, pDoc->getShapesVector().end() - 1);
//					pDoc->getShapesVector().erase(pDoc->getShapesVector().begin() + i);
//					Invalidate();
//
//				}
//
//				break;
//			}
//			}
//
//
//			if (shapeIsFound)
//			{
//				break;
//			}
//		}
//	}
//	else if (pDoc->getToolIsUsed() == Tools::doubleSelectTool)
//	{
//		bool shapeIsFound = false;
//		for (int i = sizeOfShapesVector - 1; i >= 0; i--)
//		{
//			switch (pDoc->getShapesVector()[i]->type)
//			{
//			case ShapeType::ellipse:
//			{
//
//				CPoint cp;
//				CString str;
//				HRGN ellipseRgn1 = CreatePolygonRgn(&(pDoc->getShapesVector()[i]->eFP[0]), pDoc->getShapesVector()[i]->eFP.size(), ALTERNATE);// = CreatePolygonRgn(;
//				HRGN ellipseRgn2 = CreatePolygonRgn(&(pDoc->getShapesVector()[i]->eSP[0]), pDoc->getShapesVector()[i]->eSP.size(), ALTERNATE);
//
//				if (PtInRegion(ellipseRgn1, point.x, point.y) || PtInRegion(ellipseRgn2, point.x, point.y))
//				{
//					if (pDoc->getShapesVector()[i]->isSelectedFromDoubleSelectingTool)
//					{
//						i = -1;
//						break;
//					}
//					if (pDoc->selectedShapesIDs.size() > 0 && (pDoc->getShapesVector()[i]->constID == pDoc->selectedShapesIDs.front() || pDoc->getShapesVector()[i]->constID == pDoc->selectedShapesIDs.back()))
//					{
//						continue;
//					}
//					else
//					{
//						if (pDoc->selectedShapesIDs.size() < 2)
//						{
//
//							pDoc->selectedShapesIDs.push(pDoc->getShapesVector()[i]->constID);
//						}
//						else
//						{
//							pDoc->selectedShapesIDs.pop();
//							pDoc->selectedShapesIDs.push(pDoc->getShapesVector()[i]->constID);
//						}
//						//unselected all shapes
//						for (int it = 0; it < pDoc->getShapesVector().size(); it++)
//						{
//							/*if (pDoc->getShapesVector()[it]->constID == pDoc->selectedShapesIDs.back())
//								continue;
//							else*/
//							pDoc->getShapesVector()[it]->isSelectedFromDoubleSelectingTool = false;
//						}
//						for (int constIDit = 0; constIDit < IShape::countOfShape; constIDit++)
//						{
//							for (int s = pDoc->getShapesVector().size() - 1; s >= 0; s--)
//							{
//								if (pDoc->getShapesVector()[s]->constID == constIDit)
//								{
//									if (constIDit == pDoc->selectedShapesIDs.front() || constIDit == pDoc->selectedShapesIDs.back())
//									{
//										//int contsID = pDoc->getShapesVector()[it]->constID;
//										pDoc->getShapesVector()[s]->isSelectedFromDoubleSelectingTool = true;
//										shapeIsFound = true;
//										IShape* shape;
//										pDoc->getShapesVector().push_back(shape);
//										iter_swap(pDoc->getShapesVector().begin() + s, pDoc->getShapesVector().end() - 1);
//										pDoc->getShapesVector().erase(pDoc->getShapesVector().begin() + s);
//										//Invalidate();
//									}
//								}
//								else
//								{
//									continue;
//								}
//							}
//						}
//					}
//
//				}
//				break;
//			}
//
//			case ShapeType::rectangle:
//			{
//
//				CPoint cp;
//				CString str;
//				HRGN rectangleRgn = CreatePolygonRgn(&(pDoc->getShapesVector()[i]->points[0]), 4, ALTERNATE);// = CreatePolygonRgn(;
//				//HRGN ellipseRgn2 = CreatePolygonRgn(&(pDoc->getShapesVector()[i]->eSP[0]), pDoc->getShapesVector()[i]->eSP.size(), ALTERNATE);
//
//				if (PtInRegion(rectangleRgn, point.x, point.y))
//				{
//					if (pDoc->getShapesVector()[i]->isSelectedFromDoubleSelectingTool)
//					{
//						i = -1;
//						break;
//					}
//					if (pDoc->selectedShapesIDs.size() > 0 && (pDoc->getShapesVector()[i]->constID == pDoc->selectedShapesIDs.front() || pDoc->getShapesVector()[i]->constID == pDoc->selectedShapesIDs.back()))
//					{
//						continue;
//					}
//					else
//					{
//						if (pDoc->selectedShapesIDs.size() < 2)
//						{
//
//							pDoc->selectedShapesIDs.push(pDoc->getShapesVector()[i]->constID);
//						}
//						else
//						{
//							pDoc->selectedShapesIDs.pop();
//							pDoc->selectedShapesIDs.push(pDoc->getShapesVector()[i]->constID);
//						}
//						//unselected all shapes
//						for (int it = 0; it < pDoc->getShapesVector().size(); it++)
//						{
//							/*if (pDoc->getShapesVector()[it]->constID == pDoc->selectedShapesIDs.back())
//								continue;
//							else*/
//							pDoc->getShapesVector()[it]->isSelectedFromDoubleSelectingTool = false;
//						}
//						for (int constIDit = 0; constIDit < IShape::countOfShape; constIDit++)
//						{
//							for (int s = pDoc->getShapesVector().size() - 1; s >= 0; s--)
//							{
//								if (pDoc->getShapesVector()[s]->constID == constIDit)
//								{
//									if (constIDit == pDoc->selectedShapesIDs.front() || constIDit == pDoc->selectedShapesIDs.back())
//									{
//										//int contsID = pDoc->getShapesVector()[it]->constID;
//										pDoc->getShapesVector()[s]->isSelectedFromDoubleSelectingTool = true;
//										shapeIsFound = true;
//										IShape* shape;
//										pDoc->getShapesVector().push_back(shape);
//										iter_swap(pDoc->getShapesVector().begin() + s, pDoc->getShapesVector().end() - 1);
//										pDoc->getShapesVector().erase(pDoc->getShapesVector().begin() + s);
//										//Invalidate();
//									}
//								}
//								else
//								{
//									continue;
//								}
//							}
//						}
//					}
//
//				}
//				break;
//			}
//
//			case ShapeType::triangle:
//			{
//
//				CPoint cp;
//				CString str;
//				HRGN triangleRgn = CreatePolygonRgn(&(pDoc->getShapesVector()[i]->points[0]), 3, ALTERNATE);// = CreatePolygonRgn(;
//				//HRGN ellipseRgn2 = CreatePolygonRgn(&(pDoc->getShapesVector()[i]->eSP[0]), pDoc->getShapesVector()[i]->eSP.size(), ALTERNATE);
//
//				if (PtInRegion(triangleRgn, point.x, point.y))
//				{
//					if (pDoc->getShapesVector()[i]->isSelectedFromDoubleSelectingTool)
//					{
//						i = -1;
//						break;
//					}
//					if (pDoc->selectedShapesIDs.size() > 0 && (pDoc->getShapesVector()[i]->constID == pDoc->selectedShapesIDs.front() || pDoc->getShapesVector()[i]->constID == pDoc->selectedShapesIDs.back()))
//					{
//						continue;
//					}
//					else
//					{
//						if (pDoc->selectedShapesIDs.size() < 2)
//						{
//
//							pDoc->selectedShapesIDs.push(pDoc->getShapesVector()[i]->constID);
//						}
//						else
//						{
//							pDoc->selectedShapesIDs.pop();
//							pDoc->selectedShapesIDs.push(pDoc->getShapesVector()[i]->constID);
//						}
//						//unselected all shapes
//						for (int it = 0; it < pDoc->getShapesVector().size(); it++)
//						{
//							/*if (pDoc->getShapesVector()[it]->constID == pDoc->selectedShapesIDs.back())
//								continue;
//							else*/
//							pDoc->getShapesVector()[it]->isSelectedFromDoubleSelectingTool = false;
//						}
//						for (int constIDit = 0; constIDit < IShape::countOfShape; constIDit++)
//						{
//							for (int s = pDoc->getShapesVector().size() - 1; s >= 0; s--)
//							{
//								if (pDoc->getShapesVector()[s]->constID == constIDit)
//								{
//									if (constIDit == pDoc->selectedShapesIDs.front() || constIDit == pDoc->selectedShapesIDs.back())
//									{
//										//int contsID = pDoc->getShapesVector()[it]->constID;
//										pDoc->getShapesVector()[s]->isSelectedFromDoubleSelectingTool = true;
//										shapeIsFound = true;
//										IShape* shape;
//										pDoc->getShapesVector().push_back(shape);
//										iter_swap(pDoc->getShapesVector().begin() + s, pDoc->getShapesVector().end() - 1);
//										pDoc->getShapesVector().erase(pDoc->getShapesVector().begin() + s);
//										//Invalidate();
//									}
//								}
//								else
//								{
//									continue;
//								}
//							}
//						}
//					}
//
//				}
//				break;
//			}
//
//			}
//			if (shapeIsFound)
//			{
//				break;
//			}
//		}
//
//	}
//	CView::OnLButtonDblClk(nFlags, point);
}


void CEgoSecureTestAssignmentView::OnButtonMove()
{
	auto pDoc = GetDocument();
	pDoc->getToolIsUsed() = Tools::move;
	CString str;
	str.Format(_T("x: %d, y: %d"), pDoc->dx, pDoc->dy);

}


void CEgoSecureTestAssignmentView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	auto pDoc = GetDocument();
	if (pDoc->getToolIsUsed() == Tools::ellipse || pDoc->getToolIsUsed() == Tools::rectangle || pDoc->getToolIsUsed() == Tools::triangle)
	{
		pDoc->getShapesVector()[pDoc->getShapesVector().size() - 1]->setSelected(true);

		pDoc->getToolIsUsed() = Tools::change;
		
	}
	else if (pDoc->getToolIsUsed() == Tools::basicLine || pDoc->getToolIsUsed() == Tools::rightLine 
		|| pDoc->getToolIsUsed() == Tools::leftLine || pDoc->getToolIsUsed() == Tools::doubleLine)
	{
		pDoc->getShapesVector()[pDoc->getShapesVector().size() - 1]->setSelected(true);

		// make basicLine unactive
		pDoc->getToolIsUsed() = Tools::change;

	}

	if (pDoc->getToolIsUsed() == Tools::move)
	{
		// move all shapes
		for (int i = 0; i < pDoc->getShapesVector().size(); i++)
		{
			CString str;
			int size = pDoc->getShapesVector().size();
			//str.Format(_T("1 time: %d shape. X: %d, y: %d"), i, pDoc->getShapesVector()[i]->centerOfShape.x, pDoc->getShapesVector()[i]->centerOfShape.y);
			//AfxMessageBox(str);
			//str.Format(_T("dx: %d, dy: %d"), IShape::dx, IShape::dy);
			//AfxMessageBox(str);
			Invalidate();
			/*pDoc->getShapesVector()[i]->centerOfShape.x += IShape::dx;
			pDoc->getShapesVector()[i]->centerOfShape.y += IShape::dy;*/
			pDoc->getShapesVector()[i]->setCenterOfShape(CPoint{ pDoc->getShapesVector()[i]->getCenterOfShape().x + IShape::getDx(),  pDoc->getShapesVector()[i]->getCenterOfShape().y + IShape::getDy() });
			//str.Format(_T("2 time: %d shape. X: %d, y: %d"), i, pDoc->getShapesVector()[i]->centerOfShape.x, pDoc->getShapesVector()[i]->centerOfShape.y);
			//AfxMessageBox(str);
		}
		IShape::setDx(NULL);
		IShape::setDy(NULL);



	}
	else if (pDoc->getToolIsUsed() == Tools::change)
	{
		bool selected = false; // control of the next loop
		for (int s = 0; s < pDoc->getShapesVector().size(); s++)
		{
			//
			if (pDoc->getShapesVector()[s]->getSelected())
			{
				int numberOfAngels = 0;
				if (pDoc->getShapesVector()[s]->getShapeType() == ::ShapeType::triangle)
				{
					numberOfAngels = 3;
				}
				else if (pDoc->getShapesVector()[s]->getShapeType() == ShapeType::basicLine || pDoc->getShapesVector()[s]->getShapeType() == ShapeType::rightLine
					|| pDoc->getShapesVector()[s]->getShapeType() == ShapeType::leftLine || pDoc->getShapesVector()[s]->getShapeType() == ShapeType::doubleLine)
				{
					numberOfAngels = 2;
				}
				else// if (pDoc->getShapesVector()[s]->type == ::ShapeType::rectangle)
				{
					numberOfAngels = 4;
				}
				selected = true;
				for (int a = 0; a < numberOfAngels; a++)
				{
					if (pDoc->getShapesVector()[s]->getShapeType() == ShapeType::basicLine || pDoc->getShapesVector()[s]->getShapeType() == ShapeType::rightLine
						|| pDoc->getShapesVector()[s]->getShapeType() == ShapeType::leftLine || pDoc->getShapesVector()[s]->getShapeType() == ShapeType::doubleLine)
					{
						pDoc->getShapesVector()[s]->setChangeDxDy(a, pDoc->getShapesVector()[s]->getChangeDxDy(a) + pDoc->getShapesVector()[s]->getChangeTempDxDy(a));
						pDoc->getShapesVector()[s]->setCoordinateForChange(a, pDoc->getShapesVector()[s]->getCoordinateForChange(a) + pDoc->getShapesVector()[s]->getChangeDxDy(a));
						pDoc->getShapesVector()[s]->setChangeDxDy(a, CPoint{ 0,0 });
					}
					else
					{
						pDoc->getShapesVector()[s]->setChangeDxDy(a, pDoc->getShapesVector()[s]->getChangeDxDy(a) + pDoc->getShapesVector()[s]->getChangeTempDxDy(a));
					}
					
					
					pDoc->getShapesVector()[s]->setChangeTempDxDy(a, CPoint{ NULL, NULL });
				}
				
				for (int shapeNum = 0; shapeNum < pDoc->getShapesVector().size(); shapeNum++)
				{
					if (pDoc->getShapesVector()[shapeNum]->getShapeType() != ShapeType::basicLine && pDoc->getShapesVector()[shapeNum]->getShapeType() != ShapeType::rightLine
						&& pDoc->getShapesVector()[shapeNum]->getShapeType() != ShapeType::leftLine && pDoc->getShapesVector()[shapeNum]->getShapeType() != ShapeType::doubleLine)
					{
						int numberOfPointForLines0 = -1; // for FIRST_POINT_OF_LINE
						int numberOfPointForLines1 = -1; // for SECOND_POINT_OF_LINE
						if (pDoc->getShapesVector()[shapeNum]->IsClickedOnPointForLines(pDoc->getShapesVector()[s]->getCoordinateForChange(FIRST_POINT_OF_LINE), numberOfPointForLines0))
						{
							
							if (numberOfPointForLines0 != -1)
							{
							
								pDoc->getShapesVector()[s]->setCoordinateForChange(FIRST_POINT_OF_LINE, pDoc->getShapesVector()[shapeNum]->getPointForLine(numberOfPointForLines0));
								pDoc->getShapesVector()[s]->createLineConnection(FIRST_POINT_OF_LINE, pDoc->getShapesVector()[shapeNum]->getConstID(), numberOfPointForLines0);
								CString str = NULL;
								str.Format(_T("%d"), numberOfPointForLines0);
								//AfxMessageBox(str);
							}


							//if (numberOfPointForLines1 != -1)
							//{
				
							//	pDoc->getShapesVector()[s]->setCoordinateForChange(SECOND_POINT_OF_LINE, pDoc->getShapesVector()[shapeNum]->getPointForLine(numberOfPointForLines1));
							//	pDoc->getShapesVector()[s]->createLineConnection(SECOND_POINT_OF_LINE, pDoc->getShapesVector()[shapeNum]->constID, numberOfPointForLines1);
							//}
							//else
							//{
							//	//pDoc->getShapesVector()[s]->lineDisconnecting(SECOND_POINT_OF_LINE);
							//}
					

						}
						

						if (pDoc->getShapesVector()[shapeNum]->IsClickedOnPointForLines(pDoc->getShapesVector()[s]->getCoordinateForChange(SECOND_POINT_OF_LINE), numberOfPointForLines1))
						{
							if (numberOfPointForLines1 != -1)
							{
							
								pDoc->getShapesVector()[s]->setCoordinateForChange(SECOND_POINT_OF_LINE, pDoc->getShapesVector()[shapeNum]->getPointForLine(numberOfPointForLines1));
								pDoc->getShapesVector()[s]->createLineConnection(SECOND_POINT_OF_LINE, pDoc->getShapesVector()[shapeNum]->getConstID(), numberOfPointForLines1);
								CString str = NULL;
								str.Format(_T("%d"), numberOfPointForLines1);
								//AfxMessageBox(str);
							}
						}
						
						if (numberOfPointForLines0 == -1)
						{
				
							pDoc->getShapesVector()[s]->lineDisconnecting(FIRST_POINT_OF_LINE, pDoc->getShapesVector()[shapeNum]->getConstID());
						}
						if (numberOfPointForLines1 == -1)
						{
						
							pDoc->getShapesVector()[s]->lineDisconnecting(SECOND_POINT_OF_LINE, pDoc->getShapesVector()[shapeNum]->getConstID());
						}
					
						
		
					}
				}
			}
		}
	}
	CString str;
	if (pDoc->getToolIsUsed() == Tools::move)
	{
		//Format(_T("centerOfShape: x: %d, y: %d"), pDoc->getShapesVector()[0]->centerOfShape.x, pDoc->getShapesVector()[0]->centerOfShape.y);
		//AfxMessageBox(str);
		//str.Format(_T("boxRect: x: %d, y: %d"), pDoc->getShapesVector()[0]->boxRect.CenterPoint().x, pDoc->getShapesVector()[0]->boxRect.CenterPoint().y);
		//AfxMessageBox(str);
	}
	if (pDoc->getToolIsUsed() == Tools::shapeMove)
	{
		for (int s = 0; s < pDoc->getShapesVector().size(); s++)
		{
			if (pDoc->getShapesVector()[s]->getSelected())
			{
				pDoc->getShapesVector()[s]->setShapeMoveTempDxDy(pDoc->getShapesVector()[s]->rotateAndMoveCoordinate(pDoc->getShapesVector()[s]->getShapeMoveTempDxDy()/*, pDoc->getToolIsUsed()*/, LBUTTON_UP));
			}
			pDoc->getShapesVector()[s]->setShapeMoveTempDxDy(CPoint{ 0,0 });
		}
	}

	// shape is drawed then screen update
	Invalidate();
	CView::OnLButtonUp(nFlags, point);
}


void CEgoSecureTestAssignmentView::OnButtonChange()
{
	//AfxMessageBox(_T("Change"));
	auto pDoc = GetDocument();
	pDoc->getToolIsUsed() = Tools::change;
	// TODO: Add your command handler code here
}


void CEgoSecureTestAssignmentView::OnButtonRotate()
{
	auto pDoc = GetDocument();
	pDoc->getToolIsUsed() = Tools::rotate;

	//AfxMessageBox(_T("123"));
	//SetWorldTransform()
	// TODO: Add your command handler code here
}


void CEgoSecureTestAssignmentView::OnButtonShapeNormalize()
{
	//AfxMessageBox(_T("1234567"));
	//auto pDoc = GetDocument();
	////pDoc->getToolIsUsed() = Tools::shapeNormalize; //don't need
	//for (int s = 0; s < pDoc->getShapesVector().size(); s++)
	//{
	//	if (pDoc->getShapesVector()[s]->isSelected)
	//	{


	//		//pDoc->getShapesVector()[s]->isNormalized = true;
	//		pDoc->getShapesVector()[s]->angleRad = 0;
	//		CPoint tmp[4];
	//		if (pDoc->getShapesVector()[s]->type == ShapeType::triangle)
	//		{
	//			for (int i = 0; i < 4; i++)
	//			{
	//				tmp[i] = pDoc->getShapesVector()[s]->recFromRgn[i];
	//			}

	//		}
	//		else
	//		{
	//			for (int i = 0; i < 4; i++)
	//			{
	//				tmp[i] = pDoc->getShapesVector()[s]->points[i];
	//			}

	//		}

	//		CPoint centerSidesPoints[2];
	//		centerSidesPoints[0] = CPoint((tmp[1].x - tmp[0].x) / 2 + tmp[0].x, (tmp[1].y - tmp[0].y) / 2 + tmp[0].y);
	//		centerSidesPoints[1] = CPoint((tmp[2].x - tmp[1].x) / 2 + tmp[1].x, (tmp[2].y - tmp[1].y) / 2 + tmp[1].y);
	//		int l1 = (int)sqrt(pow(centerSidesPoints[0].x - pDoc->getShapesVector()[s]->centerOfShape.x, 2) + pow(centerSidesPoints[0].y - pDoc->getShapesVector()[s]->centerOfShape.y, 2));
	//		int l2 = (int)sqrt(pow(centerSidesPoints[1].x - pDoc->getShapesVector()[s]->centerOfShape.x, 2) + pow(centerSidesPoints[1].y - pDoc->getShapesVector()[s]->centerOfShape.y, 2));
	//		int min;
	//		min = (l1 < l2) ? l1 : l2;
	//		CString dbug;
	//		dbug.Format(_T("%d, %d"), l1, l2);
	//		//AfxMessageBox(dbug);
	//		for (int i = 0; i < 4; i++)
	//		{
	//			pDoc->getShapesVector()[s]->dx_dy[i].x = 0;
	//			pDoc->getShapesVector()[s]->dx_dy[i].y = 0;
	//			pDoc->getShapesVector()[s]->dx_dy_temp[i].x = 0;
	//			pDoc->getShapesVector()[s]->dx_dy_temp[i].y = 0;
	//		}
	//		pDoc->getShapesVector()[s]->size = min;
	//		Invalidate();
	//	}
	//}

	// TODO: Add your command handler code here
}


void CEgoSecureTestAssignmentView::OnButtonShapeMove()
{
	auto pDoc = GetDocument();
	pDoc->getToolIsUsed() = Tools::shapeMove;

	for (int s = 0; s < pDoc->getShapesVector().size(); s++)
	{
		pDoc->getShapesVector()[s]->setShapeMoveTempDxDy(CPoint{ 0,0 });
		/*pDoc->getShapesVector()[s]->shapeMove.tempDxDy.x = 0;
		pDoc->getShapesVector()[s]->shapeMove.tempDxDy.y = 0;*/
	}
	//pDoc->getShapesVector()[s]->diffShapeMove.x = 0;
	//IShape::diffShapeMove.y = 0;
	Invalidate();
	//AfxMessageBox(_T("ckeck"));
	// TODO: Add your command handler code here
}



void CEgoSecureTestAssignmentView::OnButtonDelete()
{
	auto pDoc = GetDocument();

	//AfxMessageBox(_T("del"));
	for (int i = 0; i < pDoc->getShapesVector().size(); i++)
	{
		if (pDoc->getShapesVector()[i]->getSelected())
		{
			//IShape::IDs.erase(pDoc->getShapesVector()[i]->ID); // erase ID because ID won't exist
			//IShape::names.erase(pDoc->getShapesVector()[i]->name);
			/*IShape* shape;
			pDoc->getShapesVector().push_back(shape);
			iter_swap(pDoc->getShapesVector().begin() + i, pDoc->getShapesVector().end() - 1);*/
			delete pDoc->getShapesVector()[i]; // memory clear
			pDoc->getShapesVector().erase(pDoc->getShapesVector().begin() + i); //erase from vector
			Invalidate();
		}
	}

	if (pDoc->getToolIsUsed() == Tools::doubleSelectTool)
	{
		//int ID1_is_selected = pDoc->selectedShapesIDs.front(); //for convenience
		//int ID2_is_selected = pDoc->selectedShapesIDs.back();
		//for (int i = 0; i < pDoc->lines.size(); i++)
		//{
		//	if ((pDoc->lines[i]->FirstShapeConstID == ID1_is_selected && pDoc->lines[i]->SecondShapeConstID == ID2_is_selected) || (pDoc->lines[i]->SecondShapeConstID == ID1_is_selected && pDoc->lines[i]->FirstShapeConstID == ID2_is_selected))
		//	{
		//		//int deleteID = pDoc->lines[i]->ID;
		//		/*Lines::IDs.erase(deleteID);
		//		Lines::names.erase(pDoc->lines[i]->name);*/
		//		delete pDoc->lines[i];
		//		pDoc->lines.erase(pDoc->lines.begin() + i);

		//	}
		//}
	}
	Invalidate();
	// TODO: Add your command handler code here
}


void CEgoSecureTestAssignmentView::OnButtonDoubleSelect()
{
//	//AfxMessageBox(_T("DoubleSelect"));
//	auto pDoc = GetDocument();
//	pDoc->getToolIsUsed() = Tools::doubleSelectTool;
//	int s = pDoc->lines.size();
//	CString str;
//	str.Format(_T("Size lines vector: %d"), s);
//	//AfxMessageBox(str);
//	//for (Lines* l : pDoc->lines)
//	//{
//	//	//l->draw();
//	//}
//	for (auto s : pDoc->getShapesVector())
//	{
//		s->isSelected = false;
//	}
//	for (auto s : pDoc->getShapesVector())
//	{
//		s->isSelectedFromDoubleSelectingTool = false;
//	}
//	queue<int> clear;
//	swap(clear, pDoc->selectedShapesIDs);
//	Invalidate();
}


void CEgoSecureTestAssignmentView::OnButtonBasicLine()
{
	auto pDoc = GetDocument();
	pDoc->getToolIsUsed() = Tools::basicLine;

	//unselect all others shapes and lines
	for (int shapeNum = 0; shapeNum < pDoc->getShapesVector().size(); shapeNum++)
	{
		pDoc->getShapesVector()[shapeNum]->setSelected(false);
		pDoc->getShapesVector()[shapeNum]->setCanDrawPointsForLines(true);
	}

	// update window
	Invalidate();
}


void CEgoSecureTestAssignmentView::OnButtonRightLine()
{
	auto pDoc = GetDocument();
	pDoc->getToolIsUsed() = Tools::rightLine;

	//unselect all others shapes and lines
	for (int shapeNum = 0; shapeNum < pDoc->getShapesVector().size(); shapeNum++)
	{
		pDoc->getShapesVector()[shapeNum]->setSelected(false);
		pDoc->getShapesVector()[shapeNum]->setCanDrawPointsForLines(true);
	}

	// update window
	Invalidate();
	
}


void CEgoSecureTestAssignmentView::OnButtonLeftLine()
{
	auto pDoc = GetDocument();
	pDoc->getToolIsUsed() = Tools::leftLine;

	//unselect all others shapes and lines
	for (int shapeNum = 0; shapeNum < pDoc->getShapesVector().size(); shapeNum++)
	{
		pDoc->getShapesVector()[shapeNum]->setSelected(false);
		pDoc->getShapesVector()[shapeNum]->setCanDrawPointsForLines(true);
	}

	// update window
	Invalidate();

}


void CEgoSecureTestAssignmentView::OnButtonDoubleLine()
{
	auto pDoc = GetDocument();
	pDoc->getToolIsUsed() = Tools::doubleLine;

	//unselect all others shapes and lines
	for (int shapeNum = 0; shapeNum < pDoc->getShapesVector().size(); shapeNum++)
	{
		pDoc->getShapesVector()[shapeNum]->setSelected(false);
		pDoc->getShapesVector()[shapeNum]->setCanDrawPointsForLines(true);
	}

	// update window
	Invalidate();

}


void CEgoSecureTestAssignmentView::OnPropertiesAllshapesandlines()
{
	//AfxMessageBox(_T("12345"));
	auto pDoc = GetDocument();
	List_Control dlg;
	for (auto s : pDoc->getShapesVector())
	{
		dlg.shapes.push_back(s);
	}
	/*for (auto l : pDoc->lines)
	{
		dlg.lines.push_back(l);
	}*/
	dlg.DoModal();



}


void CEgoSecureTestAssignmentView::OnListcontrolShapes()
{

}


void CEgoSecureTestAssignmentView::OnPropertiesDefaultdrawproperties()
{
	auto pDoc = GetDocument();
	Default_draw_properties dlg(pDoc);
	dlg.getParameters();
	dlg.DoModal();
	dlg.setParameters();
	DeleteObject(pDoc);
}


void CEgoSecureTestAssignmentView::OnButtonProperties()
{
	auto pDoc = GetDocument();
	for (int s = 0; s < pDoc->getShapesVector().size(); s++)
	{
		if (pDoc->getShapesVector()[s]->getSelected())
		{
			Dialog_Properties dlg(pDoc);
			dlg.getParameters(s);
			dlg.DoModal();
			dlg.setParameters(s);
			break;
		}
	}
}

void CEgoSecureTestAssignmentView::OnEditNormalize()
{
	auto pDoc = GetDocument();
	for (int s = 0; s < pDoc->getShapesVector().size(); s++)
	{
		pDoc->getShapesVector()[s]->normalizeShape();
	}
	Invalidate();
}



