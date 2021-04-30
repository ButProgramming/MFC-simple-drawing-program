
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
	// create pointer on document
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
	}

	pDC->BitBlt(0, 0, rect.Width(), rect.Height(), &m_dc, 0, 0, SRCCOPY);



	// delete pointer on document
	DeleteObject(pDoc);
}

void CEgoSecureTestAssignmentView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CEgoSecureTestAssignmentView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
	// create pointer on document
	CEgoSecureTestAssignmentDoc* pDoc = GetDocument();

	// create menu
	CMenu menu;
	menu.LoadMenu(IDR_POPUP_EDIT);
	CMenu* pMenu = menu.GetSubMenu(0);

	// variable is true if selected shape don't exist. If false -> break next loop
	bool selectedShapeDontExcist = true;

	// search selected shape
	for (int shapeNum = 0; shapeNum < pDoc->getShapesVector().size(); shapeNum++)
	{
		if (pDoc->getShapesVector()[shapeNum]->getSelected())
		{
			selectedShapeDontExcist = false;
			break;
		}
	}

	// disabling "Normalize"
	if (selectedShapeDontExcist)
	{
		pMenu->EnableMenuItem(ID_EDIT_NORMALIZE, MF_DISABLED | MF_GRAYED);
	}

	pMenu->TrackPopupMenu(TPM_LEFTBUTTON, point.x, point.y, this, NULL);

	// delete objects
	DeleteObject(pDoc);
	DeleteObject(pMenu);
	DeleteObject(menu);

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
	// create pointer on document
	CEgoSecureTestAssignmentDoc* pDoc = GetDocument();

	// two bool for control next loops to break serach loop or unselect all shapes
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
		IShape* shape = new EllipseShape(point, true, 0, ShapeType::ellipse, pDoc->getOutlineColor(), pDoc->getFillColor(), pDoc->getOutlineSize(), pDoc->getOutlineType(), pDoc->getFillType());
		pDoc->getShapesVector().push_back(shape);
		break;
	}
	case Tools::rectangle:
	{
		IShape* shape = new RectangleShape(point, true, 0, ShapeType::rectangle, pDoc->getOutlineColor(), pDoc->getFillColor(), pDoc->getOutlineSize(), pDoc->getOutlineType(), pDoc->getFillType());
		pDoc->getShapesVector().push_back(shape);
		break;
	}
	case Tools::triangle:
	{
		IShape* shape = new TriangleShape(point, true, 0, ShapeType::triangle, pDoc->getOutlineColor(), pDoc->getFillColor(), pDoc->getOutlineSize(), pDoc->getOutlineType(), pDoc->getFillType());
		pDoc->getShapesVector().push_back(shape);
		break;
	}
	case Tools::basicLine:
	{
		IShape* line = new Line(point, ShapeType::basicLine, pDoc->getColorLink(), pDoc->getLineSize(), pDoc->getLinkType());
		pDoc->getShapesVector().push_back(line);
		break;
	}
	case Tools::rightLine:
	{
		IShape* line = new Line(point, ShapeType::rightLine, pDoc->getColorLink(), pDoc->getLineSize(), pDoc->getLinkType());
		pDoc->getShapesVector().push_back(line);
		break;
	}
	case Tools::leftLine:
	{
		IShape* line = new Line(point, ShapeType::leftLine, pDoc->getColorLink(), pDoc->getLineSize(), pDoc->getLinkType());
		pDoc->getShapesVector().push_back(line);
		break;
	}
	case Tools::doubleLine:
	{
		IShape* line = new Line(point, ShapeType::doubleLine, pDoc->getColorLink(), pDoc->getLineSize(), pDoc->getLinkType());
		pDoc->getShapesVector().push_back(line);
		break;
	}
	case Tools::move:
		pDoc->setFirstClickedPoint(point);
		break;
	case Tools::shapeMove:
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
		//bool selected = false;
		for (int i = 0; i < pDoc->getShapesVector().size(); i++)
		{
			if (pDoc->getShapesVector()[i]->getSelected())
			{
				// safe first clicked lButton point
				pDoc->getShapesVector()[i]->setFirstClickedPoint(point);
				//pDoc->getShapesVector()[i]->lastY = point.y;
				//selected = true;
			}
			if (pDoc->getShapesVector()[i]->getSelected()) break;
		}
		break;
	}
	case Tools::change:
		
		for (int shapeNum = 0; shapeNum < pDoc->getShapesVector().size(); shapeNum++)
		{
			if (pDoc->getShapesVector()[shapeNum]->getSelected())
			{
				// safe first clicked lButton point
				pDoc->getShapesVector()[shapeNum]->setChangeStartClickedCoordinate(point);
			}
		}
		
		for (int s = 0; s < pDoc->getShapesVector().size(); s++)
		{
			if (pDoc->getShapesVector()[s]->getSelected())
			{
				// this method set also number of clicked point for variable numberOfPoint
				pDoc->getShapesVector()[s]->isClickedPointForChange(point); 
			}
			if (pDoc->getShapesVector()[s]->getSelected())
				break;
		}
		break;
	}

	// delete object(s)
	DeleteObject(pDoc);

	CView::OnLButtonDown(nFlags, point);
}


void CEgoSecureTestAssignmentView::OnButtonEllipse()
{
	// create pointer on document
	CEgoSecureTestAssignmentDoc* pDoc = GetDocument();

	// disable selecting all shapes
	for(int shapeNum = 0; shapeNum< pDoc->getShapesVector().size(); shapeNum++)
	{
		pDoc->getShapesVector()[shapeNum]->setSelected(false);
		pDoc->getShapesVector()[shapeNum]->setCanDrawPointsForLines(false);
	}

	// use ellipse tool
	pDoc->getToolIsUsed() = Tools::ellipse;

	// delete object(s)
	DeleteObject(pDoc);

	// update drawing
	Invalidate();

}


void CEgoSecureTestAssignmentView::OnButtonRectangle()
{
	// create pointer on document
	CEgoSecureTestAssignmentDoc* pDoc = GetDocument();

	// disable selecting all shapes
	for (int shapeNum = 0; shapeNum < pDoc->getShapesVector().size(); shapeNum++)
	{
		pDoc->getShapesVector()[shapeNum]->setSelected(false);
		pDoc->getShapesVector()[shapeNum]->setCanDrawPointsForLines(false);
	}
	
	// use rectangle tool
	pDoc->getToolIsUsed() = Tools::rectangle;

	// delete object(s)
	DeleteObject(pDoc);

	// update drawing
	Invalidate();
}


void CEgoSecureTestAssignmentView::OnButtonTriangle()
{
	// create pointer on document
	CEgoSecureTestAssignmentDoc* pDoc = GetDocument();

	// disable selecting all shapes
	for (int shapeNum = 0; shapeNum < pDoc->getShapesVector().size(); shapeNum++)
	{
		pDoc->getShapesVector()[shapeNum]->setSelected(false);
		pDoc->getShapesVector()[shapeNum]->setCanDrawPointsForLines(false);
	}
	
	// use triangle tool
	pDoc->getToolIsUsed() = Tools::triangle;

	// delete object(s)
	DeleteObject(pDoc);

	// update drawing
	Invalidate();
}


void CEgoSecureTestAssignmentView::OnMouseMove(UINT nFlags, CPoint point)
{
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
	
	// set size of shapes when is drawn the first time
	if (nFlags == MK_LBUTTON && (pDoc->getToolIsUsed() == Tools::ellipse || pDoc->getToolIsUsed() == Tools::rectangle || pDoc->getToolIsUsed() == Tools::triangle))
	{
		pDoc->getShapesVector()[pDoc->getShapesVector().size() - 1]->setSize(sqrt(pow((pDoc->getShapesVector()[pDoc->getShapesVector().size() - 1])->getCenterOfShape().x - point.x, 2) + pow((pDoc->getShapesVector()[pDoc->getShapesVector().size() - 1])->getCenterOfShape().y - point.y, 2)));
	}

	else if (nFlags == MK_LBUTTON && pDoc->getToolIsUsed() == Tools::move)
	{
		IShape::setDx(point.x - pDoc->getFirstClickedPoint().x);
		IShape::setDy(point.y - pDoc->getFirstClickedPoint().y);

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
	/*queue<int> clear;
	swap(clear, pDoc->selectedShapesIDs);*/
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

}


void CEgoSecureTestAssignmentView::OnButtonMove()
{
	auto pDoc = GetDocument();
	pDoc->getToolIsUsed() = Tools::move;
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

	}
	Invalidate();
	// TODO: Add your command handler code here
}


void CEgoSecureTestAssignmentView::OnButtonDoubleSelect()
{

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



