
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
#endif
#include "Shape.h"

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
	
	CPoint point;
	CRect rect;
	GetCursorPos(&point);
	GetClientRect(&rect);
	point.x -= rect.left;
	point.y -= rect.top;
	m_dc.FillSolidRect(rect, RGB(255, 255, 255));
	

	
	/*CRect rect;
	GetClientRect(&rect);
	m_dc.FillSolidRect(rect, RGB(255, 255, 255));*/
	/*CPen* pen = new CPen(PS_SOLID, 4, RGB(255, 0, 0));
	m_dc.SelectObject(pen);*/
	//pDC->SelectObject(pen);
	for (IShape* s : pDoc->shapes)
	{
		s->draw(&m_dc);
		//m_dc.Ellipse(0, 0, 200, 200);
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
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
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
	// TODO: Add your message handler code here and/or call default
	//Shape* s = new Shape;
	auto pDoc = GetDocument();
	/*CString str;
	str.Format(_T("%d"), pDoc->typeOfShape);
	AfxMessageBox(str);*/
	switch (pDoc->toolIsUsed)
	{
		case Tools::ellipse:
		{
			
			IShape* shape = new EllipseShape(point, true, 0, ShapeType::ellipse);
			pDoc->shapes.push_back(shape);
			/*CString str;
			str.Format(_T("%d"), pDoc->shapes.size());
			AfxMessageBox(str);*/
			//delete shape;
			break;
		}
		case Tools::rectangle:
		{
			IShape* shape = new RectangleShape(point, true, 0, ShapeType::rectangle);
			pDoc->shapes.push_back(shape);
			//delete shape;
			break;
		}
		case Tools::triangle:
		{
			IShape* shape = new TriangleShape(point, true, 0, ShapeType::triangle);
			pDoc->shapes.push_back(shape);
			//delete shape;
			break;
		}
	}
	if (pDoc->toolIsUsed == Tools::move)
	{
		pDoc->first.x = point.x;
		pDoc->first.y = point.y;
		
	}
	
	
	//AfxMessageBox(_T("123"));
	
	
	//Invalidate();
	CView::OnLButtonDown(nFlags, point);
}


void CEgoSecureTestAssignmentView::OnButtonEllipse()
{
	// TODO: Add your command handler code here
	auto pDoc = GetDocument();
	pDoc->toolIsUsed = Tools::ellipse;

}


void CEgoSecureTestAssignmentView::OnButtonRectangle()
{
	// TODO: Add your command handler code here}
	auto pDoc = GetDocument();
	pDoc->toolIsUsed = Tools::rectangle;
}


void CEgoSecureTestAssignmentView::OnButtonTriangle()
{
	// TODO: Add your command handler code here
	auto pDoc = GetDocument();
	pDoc->toolIsUsed = Tools::triangle;
}


void CEgoSecureTestAssignmentView::OnMouseMove(UINT nFlags, CPoint point)
{
	int dx = 0;
	int dy = 0;
	auto pDoc = GetDocument();
	if (nFlags == MK_LBUTTON && (pDoc->toolIsUsed==Tools::ellipse || pDoc->toolIsUsed == Tools::rectangle || pDoc->toolIsUsed == Tools::triangle))
	{
		//auto pDoc = GetDocument();
		//pDoc->shapes.at(pDoc->shapes.size() - 1)->size; //sqrt(pow((pDoc->shapes.at(v.size() - 1).c_shapeCenter.x - point.x), 2) + pow((v.at(v.size() - 1).c_shapeCenter.y - point.y), 2));
		//if (pDoc->shapes.size() > 0)
		pDoc->shapes[pDoc->shapes.size()-1]->size = sqrt(pow((pDoc->shapes[pDoc->shapes.size() - 1])->centerOfShape.x - point.x, 2) + pow((pDoc->shapes[pDoc->shapes.size() - 1])->centerOfShape.y - point.y, 2));
		//Invalidate();
	}
	else if (nFlags == MK_LBUTTON && pDoc->toolIsUsed == Tools::move)
	{
		pDoc->second.x = point.x;
		pDoc->second.y = point.y;
		IShape::dx = pDoc->second.x - pDoc->first.x;
		IShape::dy = pDoc->second.y - pDoc->first.y;

		
		//int d = sqrt(pow(dx, 2) + pow(dx, 2));


		
		//CPoint firstPoint = point;

		/*pDoc->dx = pDoc->second.x - pDoc->first.x;
		if (pDoc->second.x - pDoc->first.x > 100)
		{
			CString str;
			int a = pDoc->second.x - pDoc->first.x;
			str.Format(_T("%d"), a);
			AfxMessageBox(str);
		}*/
		//pDoc->dx += sqrt(pow((pDoc->shapes[pDoc->shapes.size() - 1])->centerOfShape.x - point.x, 2) + pow((pDoc->shapes[pDoc->shapes.size() - 1])->centerOfShape.y - p;
	}
	/*if (nFlags != MK_LBUTTON && pDoc->toolIsUsed == Tools::move)
	{
	
	}*/
	
	//pDoc->dx_global += dx;
	//pDoc->dy_global += dy;
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
	// TODO:  Add your specialized creation code here

	return 0;
}


void CEgoSecureTestAssignmentView::OnButtonSelectTool()
{
	auto pDoc = GetDocument();
	pDoc->toolIsUsed = Tools::select_tool;
	// TODO: Add your command handler code here
}


void CEgoSecureTestAssignmentView::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	//AfxMessageBox(_T("123"));
	auto pDoc = GetDocument();
	int sizeOfShapesVector = pDoc->shapes.size();
	bool shapeIsFound =false; //exit from for loop if = true
	for (int i = sizeOfShapesVector - 1; i >= 0; i--)
	{
		switch (pDoc->shapes[i]->type)
		{
		case ShapeType::ellipse:
		{
			CPoint ellipseCenter = pDoc->shapes[i]->centerOfShape; //convinient
			int ellipseSize = pDoc->shapes[i]->size; //convinient
			HRGN ellipseRgn = CreateEllipticRgn(ellipseCenter.x - ellipseSize, ellipseCenter.y - ellipseSize, ellipseCenter.x + ellipseSize, ellipseCenter.y + ellipseSize);
			if (PtInRegion(ellipseRgn, point.x, point.y))
			{
				
				
				//AfxMessageBox(_T("Ellipse"));
				//pDoc->shapes[i]->pen=newPen;
				shapeIsFound = true;
				for (int i = sizeOfShapesVector - 1; i >= 0; i--)
				{
					//unselecting others shapes
					if (pDoc->shapes[i]->isSelected == true)
					{
						pDoc->shapes[i]->pen->DeleteObject();
						pDoc->shapes[i]->isSelected = false;
						break;
					};
				}
				pDoc->shapes[i]->isSelected = true;
				Invalidate();
			}
			//pDoc->shapes[i]->centerOfShape
			//AfxMessageBox(_T("ellipse"));
			break;
		}
		case ShapeType::rectangle:
		{	
			CPoint rectangleCenter = pDoc->shapes[i]->centerOfShape; //convinient
			int rectangleSize = pDoc->shapes[i]->size; //convinient
			HRGN rectangleRgn = CreateRectRgn(rectangleCenter.x - rectangleSize, rectangleCenter.y - rectangleSize, rectangleCenter.x + rectangleSize, rectangleCenter.y + rectangleSize);
			if (PtInRegion(rectangleRgn, point.x, point.y))
			{
				//AfxMessageBox(_T("Rectangle"));
				shapeIsFound = true;
				for (int i = sizeOfShapesVector - 1; i >= 0; i--)
				{
					//unselecting others shapes
					if (pDoc->shapes[i]->isSelected == true)
					{
						pDoc->shapes[i]->pen->DeleteObject();
						pDoc->shapes[i]->isSelected = false;
						break;
					};
				}
				pDoc->shapes[i]->isSelected = true;
				Invalidate();
			}
			
			break;
		}
		case ShapeType::triangle:
		{
			CPoint rectangleCenter = pDoc->shapes[i]->centerOfShape; //convinient
			int rectangleSize = pDoc->shapes[i]->size; //convinient
			int h = 3 * rectangleSize;
			int side = 2 * h / sqrt(3);

			CPoint triangle[3];
			triangle[0] = CPoint(rectangleCenter.x, rectangleCenter.y - 2 * rectangleSize); //top
			triangle[1] = CPoint(rectangleCenter.x - side / 2, rectangleCenter.y + rectangleSize); //left
			triangle[2] = CPoint(rectangleCenter.x + side / 2, rectangleCenter.y + rectangleSize); //right

			HRGN rectangleRgn = CreatePolygonRgn(triangle, 3, ALTERNATE);
			//CreateEllipticRgn(rectangleCenter.x - rectangleSize, rectangleCenter.y - rectangleSize, rectangleCenter.x + rectangleSize, rectangleCenter.y + rectangleSize);
			if (PtInRegion(rectangleRgn, point.x, point.y))
			{
				//AfxMessageBox(_T("Triangle"));
				shapeIsFound = true;
				for (int i = sizeOfShapesVector - 1; i >= 0; i--)
				{
					//unselecting others shapes
					if (pDoc->shapes[i]->isSelected == true)
					{
						pDoc->shapes[i]->pen->DeleteObject();
						pDoc->shapes[i]->isSelected = false;
						break;
					};
				}
				pDoc->shapes[i]->isSelected = true;
				Invalidate();

			}
			break;
		}
		}
	
		//AfxMessageBox(_T("Goto"));
		//break;
		if (shapeIsFound)
		{
			break;
		}
	}

	CView::OnLButtonDblClk(nFlags, point);
}


void CEgoSecureTestAssignmentView::OnButtonMove()
{
	auto pDoc = GetDocument();
	pDoc->toolIsUsed = Tools::move;
	CString str;
	str.Format(_T("x: %d, y: %d"), pDoc->dx, pDoc->dy);
	//if(pDoc->dx_global>0)
	//AfxMessageBox(str);
	//AfxMessageBox(_T("Move"));
	// TODO: Add your command handler code here
}


void CEgoSecureTestAssignmentView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	auto pDoc = GetDocument();
	if (pDoc->toolIsUsed == Tools::move)
	{
		
		for (int i = 0; i<pDoc->shapes.size(); i++)
		{
			CString str;
			int size = pDoc->shapes.size();
			str.Format(_T("1 time: %d shape. X: %d, y: %d"), i, pDoc->shapes[0]->centerOfShape.x, pDoc->shapes[0]->centerOfShape.y);
			//AfxMessageBox(str);
			str.Format(_T("dx: %d, dy: %d"), IShape::dx, IShape::dy);
			//AfxMessageBox(str);
			Invalidate();
			pDoc->shapes[i]->centerOfShape.x += IShape::dx;
			pDoc->shapes[i]->centerOfShape.y += IShape::dy;
			str.Format(_T("2 time: %d shape. X: %d, y: %d"), i, pDoc->shapes[0]->centerOfShape.x, pDoc->shapes[0]->centerOfShape.y);
			//AfxMessageBox(str);
		}
		IShape::dx = 0;
		IShape::dy = 0;

		
	}
	//AfxMessageBox(_T("123"));
	//auto pDoc = GetDocument();
	//if (pDoc->toolIsUsed == Tools::move)
	//{
	//	IShape::dx = 0;
	//	IShape::dy = 0;
	//	IShape::dx = pDoc->second.x - pDoc->first.x;
	//	IShape::dy = pDoc->second.y - pDoc->first.y;

	//	if (pDoc->toolIsUsed == Tools::move)
	//	{
	//		for (auto s : pDoc->shapes)
	//		{
	//			CString str;
	//			str.Format(_T("%d, %d"), s->centerOfShape.x, s->centerOfShape.y);
	//			//AfxMessageBox(str);
	//			s->centerOfShape.x = s->centerOfShape.x;
	//			s->centerOfShape.y = s->centerOfShape.y;
	//		}
	//	}
	//}
	CView::OnLButtonUp(nFlags, point);
}
