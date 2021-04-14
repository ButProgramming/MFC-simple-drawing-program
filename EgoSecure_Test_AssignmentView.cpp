
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
#include "List_Control.h"
#include "Default_draw_properties.h"
#include "Dialog_Properties.h"
#include "Dialog_Link_Properties.h"

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
	for (IShape* s : pDoc->shapes)
	{
		s->draw(&m_dc);
	}
	
	for (int i=0; i<pDoc->lines.size(); i++)
	{
		CPen* linePen;
		pDoc->lines[i]->lR = GetRValue(pDoc->lines[i]->lineColor);
		pDoc->lines[i]->lG = GetGValue(pDoc->lines[i]->lineColor);
		pDoc->lines[i]->lB = GetBValue(pDoc->lines[i]->lineColor);
		linePen = new CPen(pDoc->lines[i]->lineType, pDoc->lines[i]->lineSize, RGB(pDoc->lines[i]->lR, pDoc->lines[i]->lG, pDoc->lines[i]->lB));
		CPoint firstPoint;
		CPoint secondPoint;
		int firstID = pDoc->lines[i]->FirstShapeConstID;
		int secondID = pDoc->lines[i]->SecondShapeConstID;
		
		
	
		bool found = false;
		for (auto s : pDoc->shapes)
		{
			CString d;
			d.Format(_T("%d"), s->constID);
			//AfxMessageBox(d);
			if (s->constID == firstID)
			{
				found = true;
				firstPoint = s->centerOfShape;


				int temp_dSM_x = s->dSM.x;
				int temp_dSM_y = s->dSM.y;
				int temp2_dSM_x = temp_dSM_x;
				int temp2_dSM_y = temp_dSM_y;
				temp_dSM_x = round(temp2_dSM_x * cos((s->ellipseAngleRad)) - temp2_dSM_y * sin((s->ellipseAngleRad)));
				temp_dSM_y = round(temp2_dSM_x * sin((s->ellipseAngleRad)) + temp2_dSM_y * cos((s->ellipseAngleRad)));

				firstPoint.x += temp_dSM_x + IShape::dx;
				firstPoint.y += temp_dSM_y + IShape::dy;
				//Invalidate();
				break;
			}
		}
		if (!found)
		{
			pDoc->lines[i]->first_ID_not_excist = true;
		}
		found = false;
		for (auto s : pDoc->shapes)
		{
			if (s->constID == secondID)
			{
				secondPoint = s->centerOfShape;
				found = true;
				int temp_dSM_x = s->dSM.x;
				int temp_dSM_y = s->dSM.y;
				int temp2_dSM_x = temp_dSM_x;
				int temp2_dSM_y = temp_dSM_y;
				temp_dSM_x = round(temp2_dSM_x * cos((s->ellipseAngleRad)) - temp2_dSM_y * sin((s->ellipseAngleRad)));
				temp_dSM_y = round(temp2_dSM_x * sin((s->ellipseAngleRad)) + temp2_dSM_y * cos((s->ellipseAngleRad)));
				secondPoint.x += temp_dSM_x + IShape::dx;
				secondPoint.y += temp_dSM_y + IShape::dy;
				break;
			}
		}
		if (!found)
		{
			pDoc->lines[i]->second_ID_not_exceist = true;
		}
		bool deleteThisLine = pDoc->lines[i]->first_ID_not_excist || pDoc->lines[i]->second_ID_not_exceist;
		if (deleteThisLine)
		{
			
			
			delete pDoc->lines[i];
			pDoc->lines.erase(pDoc->lines.begin() + i);
			CString str;
			int size = pDoc->lines.size();
			str.Format(_T("Size of lines vector: %d"), size);
			//AfxMessageBox(str);
			break;
		}
		m_dc.SelectObject(linePen);
		m_dc.MoveTo(firstPoint);
		m_dc.LineTo(secondPoint);
		
		if (pDoc->lines[i]->type == LineType::Right)
		{
			CPoint centerOfArrowGround = CPoint(firstPoint.x + (secondPoint.x - firstPoint.x) / 1.07, firstPoint.y + (secondPoint.y - firstPoint.y) / 1.07);
			//m_dc.Ellipse(centerOfArrowGround.x - 5, centerOfArrowGround.y - 5, centerOfArrowGround.x + 5, centerOfArrowGround.y + 5);
			double angleOfTriangleDeg = 12;
			double angleOfTriangleRad = angleOfTriangleDeg * 3.14 / 180.f;
			double angleBigTriangleRad;
			double angleBigTriangleDeg;

			double lengthOFLeg;
			double lengthOfHypotenuse;
			CPoint secondLegPoint = CPoint(centerOfArrowGround.x, firstPoint.y);
			CPoint firstLegPoint = CPoint(firstPoint.x, firstPoint.y);
			lengthOfHypotenuse = sqrt(pow(centerOfArrowGround.x - firstLegPoint.x, 2) + pow(centerOfArrowGround.y - firstLegPoint.y, 2));
			CString dbug;


			lengthOFLeg = sqrt(pow(secondLegPoint.x - firstLegPoint.x, 2) + pow(secondLegPoint.y - firstLegPoint.y, 2));
			angleBigTriangleRad = acos(lengthOFLeg / lengthOfHypotenuse);
			angleBigTriangleDeg = angleBigTriangleRad * 180.0f / 3.14;
			//dbug.Format(_T("Length of hyp: %g, leg: %g, deg: %g"), lengthOfHypotenuse, lengthOFLeg, angleBigTriangleDeg);

			double lengthOfArrow = sqrt(pow(centerOfArrowGround.x - secondPoint.x, 2) + pow(centerOfArrowGround.y - secondPoint.y, 2));
			double lengthOfPerpendicular = lengthOfArrow * tan(angleOfTriangleRad);
			double legX = cos(90 * 3.14 / 180.f - angleBigTriangleRad) * lengthOfPerpendicular;
			double legY = sin(90 * 3.14 / 180.f - angleBigTriangleRad) * lengthOfPerpendicular;
			if (centerOfArrowGround.x - firstPoint.x > 0 && centerOfArrowGround.y - firstPoint.y < 0 || centerOfArrowGround.x - firstPoint.x < 0 && centerOfArrowGround.y - firstPoint.y > 0)
			{
				//continue;
				//AfxMessageBox(_T("True"));
			}
			else
			{
				legX = -legX;
				//continue;
			}

			CPoint firstPointOfArrow = CPoint(centerOfArrowGround.x - legX, centerOfArrowGround.y - legY);
			CPoint secondPointOfArrow = CPoint(centerOfArrowGround.x + legX, centerOfArrowGround.y + legY);
			dbug.Format(_T("legX: %g, legY: %g"), legX, legY);

			if (lengthOFLeg > 80 && lengthOFLeg < 120)
			{
				//AfxMessageBox(dbug);
			}

			//m_dc.Ellipse(firstLegPoint.x - 5, firstLegPoint.y - 5, firstLegPoint.x + 5, firstLegPoint.y + 5);
			//m_dc.Ellipse(firstPointOfArrow.x - 5, firstPointOfArrow.y - 5, firstPointOfArrow.x + 5, firstPointOfArrow.y + 5);
			//m_dc.Ellipse(secondPointOfArrow.x - 5, secondPointOfArrow.y - 5, secondPointOfArrow.x + 5, secondPointOfArrow.y + 5);
			//m_dc.Ellipse(secondLegPoint.x - 5, secondLegPoint.y - 5, secondLegPoint.x + 5, secondLegPoint.y + 5);
			m_dc.MoveTo(secondPoint);
			m_dc.LineTo(firstPointOfArrow);
			m_dc.MoveTo(secondPoint);
			m_dc.LineTo(secondPointOfArrow);

			//lenghtOfHypotenuse = 
			//m_dc.Ellipse(centerOfArrowGround.x - 5, centerOfArrowGround.y - 5, centerOfArrowGround.x + 5, centerOfArrowGround.y + 5);
			/*int angleDegree = 45;
			double angleRadian = (double)angleDegree * 3.14 / 180.0f;
			double tempX = (centerOfArrowGround.x - secondPoint.x) * tan(angleRadian);
			double tempY = (centerOfArrowGround.y - secondPoint.y) * tan(angleRadian);
			CPoint leftPointOfArrowGround = CPoint(centerOfArrowGround.x, centerOfArrowGround.y + 20);
			m_dc.Ellipse(leftPointOfArrowGround.x - 5, leftPointOfArrowGround.y - 5, leftPointOfArrowGround.x + 5, leftPointOfArrowGround.y + 5);*/
			
		}



		else if (pDoc->lines[i]->type == LineType::Left)
		{
			CPoint centerOfArrowGround = CPoint(secondPoint.x - (secondPoint.x - firstPoint.x) / 1.07, secondPoint.y - (secondPoint.y - firstPoint.y) / 1.07);
			//m_dc.Ellipse(centerOfArrowGround.x - 5, centerOfArrowGround.y - 5, centerOfArrowGround.x + 5, centerOfArrowGround.y + 5);
			double angleOfTriangleDeg = 12;
			double angleOfTriangleRad = angleOfTriangleDeg * 3.14 / 180.f;
			double angleBigTriangleRad;
			double angleBigTriangleDeg;

			double lengthOFLeg;
			double lengthOfHypotenuse;
			CPoint firstLegPoint = CPoint(firstPoint.x, firstPoint.y);
			CPoint secondLegPoint = CPoint(centerOfArrowGround.x, firstPoint.y);
			lengthOfHypotenuse = sqrt(pow(centerOfArrowGround.x - firstLegPoint.x, 2) + pow(centerOfArrowGround.y - firstLegPoint.y, 2));
			CString dbug;


			lengthOFLeg = sqrt(pow(secondLegPoint.x - firstLegPoint.x, 2) + pow(secondLegPoint.y - firstLegPoint.y, 2));
			angleBigTriangleRad = acos(lengthOFLeg / lengthOfHypotenuse);
			angleBigTriangleDeg = angleBigTriangleRad * 180.0f / 3.14;
			dbug.Format(_T("Length of hyp: %g, leg: %g, deg: %g"), lengthOfHypotenuse, lengthOFLeg, angleBigTriangleDeg);
			//AfxMessageBox(dbug);

			double lengthOfArrow = sqrt(pow(centerOfArrowGround.x - firstPoint.x, 2) + pow(centerOfArrowGround.y - firstPoint.y, 2));
			double lengthOfPerpendicular = lengthOfArrow * tan(angleOfTriangleRad);
			double legX = cos(90 * 3.14 / 180.f - angleBigTriangleRad) * lengthOfPerpendicular;
			double legY = sin(90 * 3.14 / 180.f - angleBigTriangleRad) * lengthOfPerpendicular;
			if (centerOfArrowGround.x - firstPoint.x > 0 && centerOfArrowGround.y - firstPoint.y < 0 || centerOfArrowGround.x - firstPoint.x < 0 && centerOfArrowGround.y - firstPoint.y > 0)
			{
				//continue;
				//AfxMessageBox(_T("True"));
			}
			else
			{
				legX = -legX;
				//continue;
			}

			CPoint firstPointOfArrow = CPoint(centerOfArrowGround.x - legX, centerOfArrowGround.y - legY);
			CPoint secondPointOfArrow = CPoint(centerOfArrowGround.x + legX, centerOfArrowGround.y + legY);

			m_dc.MoveTo(firstPoint);
			m_dc.LineTo(firstPointOfArrow);
			m_dc.MoveTo(firstPoint);
			m_dc.LineTo(secondPointOfArrow);


		}
		else if (pDoc->lines[i]->type == LineType::Double)
		{

		//drawing first arrow
		CPoint centerOfArrowGround = CPoint(firstPoint.x + (secondPoint.x - firstPoint.x) / 1.07, firstPoint.y + (secondPoint.y - firstPoint.y) / 1.07);
		//m_dc.Ellipse(centerOfArrowGround.x - 5, centerOfArrowGround.y - 5, centerOfArrowGround.x + 5, centerOfArrowGround.y + 5);
		double angleOfTriangleDeg = 12;
		double angleOfTriangleRad = angleOfTriangleDeg * 3.14 / 180.f;
		double angleBigTriangleRad;
		double angleBigTriangleDeg;

		double lengthOFLeg;
		double lengthOfHypotenuse;
		CPoint secondLegPoint = CPoint(centerOfArrowGround.x, firstPoint.y);
		CPoint firstLegPoint = CPoint(firstPoint.x, firstPoint.y);
		lengthOfHypotenuse = sqrt(pow(centerOfArrowGround.x - firstLegPoint.x, 2) + pow(centerOfArrowGround.y - firstLegPoint.y, 2));
		CString dbug;


		lengthOFLeg = sqrt(pow(secondLegPoint.x - firstLegPoint.x, 2) + pow(secondLegPoint.y - firstLegPoint.y, 2));
		angleBigTriangleRad = acos(lengthOFLeg / lengthOfHypotenuse);
		angleBigTriangleDeg = angleBigTriangleRad * 180.0f / 3.14;
		//dbug.Format(_T("Length of hyp: %g, leg: %g, deg: %g"), lengthOfHypotenuse, lengthOFLeg, angleBigTriangleDeg);

		double lengthOfArrow = sqrt(pow(centerOfArrowGround.x - secondPoint.x, 2) + pow(centerOfArrowGround.y - secondPoint.y, 2));
		double lengthOfPerpendicular = lengthOfArrow * tan(angleOfTriangleRad);
		double legX = cos(90 * 3.14 / 180.f - angleBigTriangleRad) * lengthOfPerpendicular;
		double legY = sin(90 * 3.14 / 180.f - angleBigTriangleRad) * lengthOfPerpendicular;
		if (centerOfArrowGround.x - firstPoint.x > 0 && centerOfArrowGround.y - firstPoint.y < 0 || centerOfArrowGround.x - firstPoint.x < 0 && centerOfArrowGround.y - firstPoint.y > 0)
		{
			//continue;
			//AfxMessageBox(_T("True"));
		}
		else
		{
			legX = -legX;
			//continue;
		}

		CPoint firstPointOfArrow = CPoint(centerOfArrowGround.x - legX, centerOfArrowGround.y - legY);
		CPoint secondPointOfArrow = CPoint(centerOfArrowGround.x + legX, centerOfArrowGround.y + legY);
		dbug.Format(_T("legX: %g, legY: %g"), legX, legY);

		if (lengthOFLeg > 80 && lengthOFLeg < 120)
		{
			//AfxMessageBox(dbug);
		}


		m_dc.MoveTo(secondPoint);
		m_dc.LineTo(firstPointOfArrow);
		m_dc.MoveTo(secondPoint);
		m_dc.LineTo(secondPointOfArrow);

	




		//drawing second arrow
		centerOfArrowGround = CPoint(secondPoint.x - (secondPoint.x - firstPoint.x) / 1.07, secondPoint.y - (secondPoint.y - firstPoint.y) / 1.07);

		angleOfTriangleDeg = 12;
		angleOfTriangleRad = angleOfTriangleDeg * 3.14 / 180.f;

		firstLegPoint = CPoint(firstPoint.x, firstPoint.y);
		secondLegPoint = CPoint(centerOfArrowGround.x, firstPoint.y);
		lengthOfHypotenuse = sqrt(pow(centerOfArrowGround.x - firstLegPoint.x, 2) + pow(centerOfArrowGround.y - firstLegPoint.y, 2));


		lengthOFLeg = sqrt(pow(secondLegPoint.x - firstLegPoint.x, 2) + pow(secondLegPoint.y - firstLegPoint.y, 2));
		angleBigTriangleRad = acos(lengthOFLeg / lengthOfHypotenuse);
		angleBigTriangleDeg = angleBigTriangleRad * 180.0f / 3.14;
		dbug.Format(_T("Length of hyp: %g, leg: %g, deg: %g"), lengthOfHypotenuse, lengthOFLeg, angleBigTriangleDeg);


		lengthOfArrow = sqrt(pow(centerOfArrowGround.x - firstPoint.x, 2) + pow(centerOfArrowGround.y - firstPoint.y, 2));
		lengthOfPerpendicular = lengthOfArrow * tan(angleOfTriangleRad);
		legX = cos(90 * 3.14 / 180.f - angleBigTriangleRad) * lengthOfPerpendicular;
		legY = sin(90 * 3.14 / 180.f - angleBigTriangleRad) * lengthOfPerpendicular;
		if (centerOfArrowGround.x - firstPoint.x > 0 && centerOfArrowGround.y - firstPoint.y < 0 || centerOfArrowGround.x - firstPoint.x < 0 && centerOfArrowGround.y - firstPoint.y > 0)
		{
			//continue;
			//AfxMessageBox(_T("True"));
		}
		else
		{
			legX = -legX;
			//continue;
		}

		firstPointOfArrow = CPoint(centerOfArrowGround.x - legX, centerOfArrowGround.y - legY);
		secondPointOfArrow = CPoint(centerOfArrowGround.x + legX, centerOfArrowGround.y + legY);

		m_dc.MoveTo(firstPoint);
		m_dc.LineTo(firstPointOfArrow);
		m_dc.MoveTo(firstPoint);
		m_dc.LineTo(secondPointOfArrow);


		linePen->DeleteObject();
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
	auto Ddp = new Default_draw_properties;
	/*CString str;
	str.Format(_T("%d"), pDoc->typeOfShape);
	AfxMessageBox(str);*/
	switch (pDoc->toolIsUsed)
	{
	case Tools::ellipse:
	{
		IShape* shape = new EllipseShape(point, true, 0, ShapeType::ellipse, pDoc->m_outline_color, pDoc->m_fill_color, pDoc->num_cb_outline_size, pDoc->num_cb_outline_type, pDoc->num_cb_fill_type);
		pDoc->shapes.push_back(shape);
		/*CString str;
		str.Format(_T("%d"), pDoc->shapes.size());
		AfxMessageBox(str);*/
		//delete shape;
		break;
	}
	case Tools::rectangle:
	{
		IShape* shape = new RectangleShape(point, true, 0, ShapeType::rectangle, pDoc->m_outline_color, pDoc->m_fill_color, pDoc->num_cb_outline_size, pDoc->num_cb_outline_type, pDoc->num_cb_fill_type);
		pDoc->shapes.push_back(shape);
		//delete shape;
		break;
	}
	case Tools::triangle:
	{
		IShape* shape = new TriangleShape(point, true, 0, ShapeType::triangle, pDoc->m_outline_color, pDoc->m_fill_color, pDoc->num_cb_outline_size, pDoc->num_cb_outline_type, pDoc->num_cb_fill_type);
		pDoc->shapes.push_back(shape);
		//delete shape;
		break;
	}
	case Tools::move:
		pDoc->first.x = point.x;
		pDoc->first.y = point.y;
		break;
	case Tools::shapeMove:
		pDoc->first.x = point.x;
		pDoc->first.y = point.y;
		break;
	case Tools::rotate:
	{
		bool selected = false;
		for (int i = 0; i < pDoc->shapes.size(); i++)
		{
			if (pDoc->shapes[i]->isSelected)
			{
				pDoc->shapes[i]->lastY = point.y;
				selected = true;
			}
			if (selected) break;
		}

		break;
	}
	case Tools::change:
		pDoc->first.x = point.x;
		pDoc->first.y = point.y;
		bool selected = false; // control of the next loop
		for (int s = 0; s < pDoc->shapes.size(); s++)
		{
			//
			if (pDoc->shapes[s]->isSelected)
			{
				int numberOfAngels = 0;
				if (pDoc->shapes[s]->type == ::ShapeType::triangle)
				{
					numberOfAngels = 3;
				}
				else //if (pDoc->shapes[s]->type == ::ShapeType::rectangle)
				{
					numberOfAngels = 4;
				}
				selected = true;
				pDoc->shapes[s]->numberOfAngle = -1;
				for (int a = 0; a < numberOfAngels; a++)
				{

					HRGN angle = CreateEllipticRgn(pDoc->shapes[s]->points[a].x - IShape::sizeOfPointToMoveAndChange * 4, pDoc->shapes[s]->points[a].y - IShape::sizeOfPointToMoveAndChange * 4, pDoc->shapes[s]->points[a].x + IShape::sizeOfPointToMoveAndChange * 4, pDoc->shapes[s]->points[a].y + IShape::sizeOfPointToMoveAndChange * 4);
					if (PtInRegion(angle, point.x, point.y))
					{

						pDoc->shapes[s]->numberOfAngle = a;
						Invalidate();
						CString str;
						str.Format(_T("%d"), a);
						//AfxMessageBox(str);
					}

				}
			}
			if (selected)
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
	for (auto s : pDoc->shapes)
	{
		s->isSelected = false;
	}
	pDoc->toolIsUsed = Tools::ellipse;
	Invalidate();

}


void CEgoSecureTestAssignmentView::OnButtonRectangle()
{
	// TODO: Add your command handler code here}
	auto pDoc = GetDocument();
	for (auto s : pDoc->shapes)
	{
		s->isSelected = false;
	}
	pDoc->toolIsUsed = Tools::rectangle;
	Invalidate();
}


void CEgoSecureTestAssignmentView::OnButtonTriangle()
{
	// TODO: Add your command handler code here
	auto pDoc = GetDocument();
	for (auto s : pDoc->shapes)
	{
		s->isSelected = false;
	}
	pDoc->toolIsUsed = Tools::triangle;
	Invalidate();
}


void CEgoSecureTestAssignmentView::OnMouseMove(UINT nFlags, CPoint point)
{
	int dx = 0;
	int dy = 0;
	CEgoSecureTestAssignmentDoc* pDoc = GetDocument();
	if (nFlags == MK_LBUTTON && (pDoc->toolIsUsed == Tools::ellipse || pDoc->toolIsUsed == Tools::rectangle || pDoc->toolIsUsed == Tools::triangle))
	{
		pDoc->shapes[pDoc->shapes.size() - 1]->size = sqrt(pow((pDoc->shapes[pDoc->shapes.size() - 1])->centerOfShape.x - point.x, 2) + pow((pDoc->shapes[pDoc->shapes.size() - 1])->centerOfShape.y - point.y, 2));
	}
	else if (nFlags == MK_LBUTTON && pDoc->toolIsUsed == Tools::move)
	{
		pDoc->second.x = point.x;
		pDoc->second.y = point.y;
		IShape::dx = pDoc->second.x - pDoc->first.x;
		IShape::dy = pDoc->second.y - pDoc->first.y;

	}
	else if (nFlags == MK_LBUTTON && pDoc->toolIsUsed == Tools::shapeMove)
	{
		pDoc->second.x = point.x;
		pDoc->second.y = point.y;
		for (int s = 0; s < pDoc->shapes.size(); s++)
		{
			if (pDoc->shapes[s]->isSelected)
			{
				pDoc->shapes[s]->dSM.x = pDoc->second.x - pDoc->first.x;
				pDoc->shapes[s]->dSM.y = pDoc->second.y - pDoc->first.y;

				int tempX = pDoc->shapes[s]->dSM.x;
				int tempY = pDoc->shapes[s]->dSM.y;
				pDoc->shapes[s]->dSM.x = round(tempX * cos(-(pDoc->shapes[s]->ellipseAngleRad)) - tempY * sin(-(pDoc->shapes[s]->ellipseAngleRad)));
				pDoc->shapes[s]->dSM.y = round(tempX * sin(-(pDoc->shapes[s]->ellipseAngleRad)) + tempY * cos(-(pDoc->shapes[s]->ellipseAngleRad)));
			}
		}

	}
	else if (nFlags == MK_LBUTTON && pDoc->toolIsUsed == Tools::change)
	{
		bool selected = false; // control of the next loop
		for (int s = 0; s < pDoc->shapes.size(); s++)
		{
			//
			if (pDoc->shapes[s]->isSelected)
			{
				selected = true;
				if (pDoc->shapes[s]->numberOfAngle != -1)
				{
					pDoc->shapes[s]->dx_dy_temp[pDoc->shapes[s]->numberOfAngle].x = point.x - pDoc->first.x;
					pDoc->shapes[s]->dx_dy_temp[pDoc->shapes[s]->numberOfAngle].y = point.y - pDoc->first.y;

					int tempX = pDoc->shapes[s]->dx_dy_temp[pDoc->shapes[s]->numberOfAngle].x;
					int tempY = pDoc->shapes[s]->dx_dy_temp[pDoc->shapes[s]->numberOfAngle].y;
					pDoc->shapes[s]->dx_dy_temp[pDoc->shapes[s]->numberOfAngle].x = round(tempX * cos(-(pDoc->shapes[s]->ellipseAngleRad)) - tempY * sin(-(pDoc->shapes[s]->ellipseAngleRad)));
					pDoc->shapes[s]->dx_dy_temp[pDoc->shapes[s]->numberOfAngle].y = round(tempX * sin(-(pDoc->shapes[s]->ellipseAngleRad)) + tempY * cos(-(pDoc->shapes[s]->ellipseAngleRad)));
					//eSP[i].x += centerOfShape.x + dx;
					//eSP[i].y += centerOfShape.y + dy;


					Invalidate();
					CString str;
					str.Format(_T("%d"), pDoc->shapes[s]->numberOfAngle);
					//AfxMessageBox(str);
				}

			}
			if (selected)
				break;
		}
	}
	else if (nFlags == MK_LBUTTON && pDoc->toolIsUsed == Tools::rotate)
	{
		for (int s = 0; s < pDoc->shapes.size(); s++)
		{
			if (pDoc->shapes[s]->isSelected)
			{
				int temp = point.y - pDoc->shapes[s]->lastY;
				pDoc->shapes[s]->ellipseAngleRad += temp * 0.01;
				double db = pDoc->shapes[s]->ellipseAngleRad;
				/*CString dbug;
				dbug.Format(_T("%g"), 0.5);
				AfxMessageBox(dbug);*/
				Invalidate();
			}
			pDoc->shapes[s]->lastY = point.y;
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
	for (auto s : pDoc->shapes)
	{
		s->isSelected = false;
	}
	queue<int> clear;
	swap(clear, pDoc->selectedShapesIDs);
	for (auto s : pDoc->shapes)
	{
		s->isSelectedFromDoubleSelectingTool = false;
	}
	pDoc->toolIsUsed = Tools::select_tool;
	Invalidate();
	// TODO: Add your command handler code here
}


void CEgoSecureTestAssignmentView::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	//AfxMessageBox(_T("123"));
	auto pDoc = GetDocument();
	int sizeOfShapesVector = pDoc->shapes.size();
	bool shapeIsFound = false; //exit from for loop if = true
	if (pDoc->toolIsUsed == Tools::select_tool)
	{
		for (int i = sizeOfShapesVector - 1; i >= 0; i--)
		{
			switch (pDoc->shapes[i]->type)
			{
			case ShapeType::ellipse:
			{
				//CPoint ellipseCenter = pDoc->shapes[i]->centerOfShape; //convinient
				//int ellipseSize = pDoc->shapes[i]->size; //convinient
				//HRGN ellipseRgn = CreateEllipticRgn(ellipseCenter.x - ellipseSize, ellipseCenter.y - ellipseSize, ellipseCenter.x + ellipseSize, ellipseCenter.y + ellipseSize);
				//
				//CRgn* ellipseRgn = new CRgn;
				//ellipseRgn->CreatePolygonRgn(pDoc->shapes[i]->points, 4, ALTERNATE);
				//CRect rect;
				//GetClientRect(&rect);
				//GetRgnBox(ellipseRgn, &rect);

				CPoint cp;
				//cp = rect.BottomRight();
				CString str;
				/*str.Format(_T("x: %d, y: %d"), cp.x, cp.y);
				AfxMessageBox(str);
				str.Format(_T("x: %d, y: %d"), pDoc->shapes[i]->centerOfShape.x, pDoc->shapes[i]->centerOfShape.y);
				AfxMessageBox(str);*/
				HRGN ellipseRgn1 = CreatePolygonRgn(&(pDoc->shapes[i]->eFP[0]), pDoc->shapes[i]->eFP.size(), ALTERNATE);// = CreatePolygonRgn(;
				HRGN ellipseRgn2 = CreatePolygonRgn(&(pDoc->shapes[i]->eSP[0]), pDoc->shapes[i]->eSP.size(), ALTERNATE);

				if (PtInRegion(ellipseRgn1, point.x, point.y) || PtInRegion(ellipseRgn2, point.x, point.y))
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
					//swap
					pDoc->shapes[i]->isSelected = true;

					/*auto s1 = pDoc->shapes[i];
					auto s2 = pDoc->shapes[pDoc->shapes.size()-1];
					pDoc->shapes[i] = s2;
					pDoc->shapes[pDoc->shapes.size() - 1] = s1;*/

					pDoc->shapes[i]->isSelected = true;
					IShape* shape;
					pDoc->shapes.push_back(shape);
					iter_swap(pDoc->shapes.begin() + i, pDoc->shapes.end() - 1);
					pDoc->shapes.erase(pDoc->shapes.begin() + i);
				}
				//delete ellipseRgn;
				//pDoc->shapes[i]->centerOfShape
				//AfxMessageBox(_T("ellipse"));
				break;
			}
			case ShapeType::rectangle:
			{
				CPoint rectangleCenter = pDoc->shapes[i]->centerOfShape; //convinient
				int rectangleSize = pDoc->shapes[i]->size; //convinient
				HRGN rectangleRgn = CreatePolygonRgn(pDoc->shapes[i]->points, 4, ALTERNATE);
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
					IShape* shape;
					pDoc->shapes.push_back(shape);
					iter_swap(pDoc->shapes.begin() + i, pDoc->shapes.end() - 1);
					pDoc->shapes.erase(pDoc->shapes.begin() + i);
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

				//CPoint triangle[3];
				//triangle[0] = CPoint(rectangleCenter.x, rectangleCenter.y - 2 * rectangleSize); //top
				//triangle[1] = CPoint(rectangleCenter.x - side / 2, rectangleCenter.y + rectangleSize); //left
				//triangle[2] = CPoint(rectangleCenter.x + side / 2, rectangleCenter.y + rectangleSize); //right

				HRGN rectangleRgn = CreatePolygonRgn(pDoc->shapes[i]->points, 3, ALTERNATE);
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
					IShape* shape;
					pDoc->shapes.push_back(shape);
					iter_swap(pDoc->shapes.begin() + i, pDoc->shapes.end() - 1);
					pDoc->shapes.erase(pDoc->shapes.begin() + i);
					Invalidate();

				}
				break;
			}
			}


			if (shapeIsFound)
			{
				break;
			}
		}
	}
	else if (pDoc->toolIsUsed == Tools::doubleSelectTool)
	{
	bool shapeIsFound = false;
		for (int i = sizeOfShapesVector - 1; i >= 0; i--)
		{
			switch (pDoc->shapes[i]->type)
			{
				case ShapeType::ellipse:
				{

					CPoint cp;
					CString str;
					HRGN ellipseRgn1 = CreatePolygonRgn(&(pDoc->shapes[i]->eFP[0]), pDoc->shapes[i]->eFP.size(), ALTERNATE);// = CreatePolygonRgn(;
					HRGN ellipseRgn2 = CreatePolygonRgn(&(pDoc->shapes[i]->eSP[0]), pDoc->shapes[i]->eSP.size(), ALTERNATE);

					if (PtInRegion(ellipseRgn1, point.x, point.y) || PtInRegion(ellipseRgn2, point.x, point.y))
					{
						if (pDoc->shapes[i]->isSelectedFromDoubleSelectingTool)
						{
							i = -1;
							break;
						}
						if (pDoc->selectedShapesIDs.size() > 0 && (pDoc->shapes[i]->constID == pDoc->selectedShapesIDs.front() || pDoc->shapes[i]->constID == pDoc->selectedShapesIDs.back()))
						{
							continue;
						}
						else
						{
							if (pDoc->selectedShapesIDs.size() < 2)
							{

								pDoc->selectedShapesIDs.push(pDoc->shapes[i]->constID);
							}
							else
							{
								pDoc->selectedShapesIDs.pop();
								pDoc->selectedShapesIDs.push(pDoc->shapes[i]->constID);
							}
							//unselected all shapes
							for (int it = 0; it < pDoc->shapes.size(); it++)
							{
								/*if (pDoc->shapes[it]->constID == pDoc->selectedShapesIDs.back())
									continue;
								else*/
									pDoc->shapes[it]->isSelectedFromDoubleSelectingTool = false;
							}
							for (int constIDit = 0; constIDit < IShape::countOfShape; constIDit++)
							{
								for (int s = pDoc->shapes.size() - 1; s >= 0 ; s--)
								{
									if (pDoc->shapes[s]->constID == constIDit)
									{
										if (constIDit == pDoc->selectedShapesIDs.front() || constIDit == pDoc->selectedShapesIDs.back())
										{
											//int contsID = pDoc->shapes[it]->constID;
											pDoc->shapes[s]->isSelectedFromDoubleSelectingTool = true;
											shapeIsFound = true;
											IShape* shape;
											pDoc->shapes.push_back(shape);
											iter_swap(pDoc->shapes.begin() + s, pDoc->shapes.end() - 1);
											pDoc->shapes.erase(pDoc->shapes.begin() + s);
											//Invalidate();
										}
									}
									else
									{
										continue;
									}
								}
							}
						}

					}
					break;
				}

				case ShapeType::rectangle:
				{

					CPoint cp;
					CString str;
					HRGN rectangleRgn = CreatePolygonRgn(pDoc->shapes[i]->points, 4, ALTERNATE);// = CreatePolygonRgn(;
					//HRGN ellipseRgn2 = CreatePolygonRgn(&(pDoc->shapes[i]->eSP[0]), pDoc->shapes[i]->eSP.size(), ALTERNATE);

					if (PtInRegion(rectangleRgn, point.x, point.y))
					{
						if (pDoc->shapes[i]->isSelectedFromDoubleSelectingTool)
						{
							i = -1;
							break;
						}
						if (pDoc->selectedShapesIDs.size() > 0 && (pDoc->shapes[i]->constID == pDoc->selectedShapesIDs.front() || pDoc->shapes[i]->constID == pDoc->selectedShapesIDs.back()))
						{
							continue;
						}
						else
						{
							if (pDoc->selectedShapesIDs.size() < 2)
							{

								pDoc->selectedShapesIDs.push(pDoc->shapes[i]->constID);
							}
							else
							{
								pDoc->selectedShapesIDs.pop();
								pDoc->selectedShapesIDs.push(pDoc->shapes[i]->constID);
							}
							//unselected all shapes
							for (int it = 0; it < pDoc->shapes.size(); it++)
							{
								/*if (pDoc->shapes[it]->constID == pDoc->selectedShapesIDs.back())
									continue;
								else*/
								pDoc->shapes[it]->isSelectedFromDoubleSelectingTool = false;
							}
							for (int constIDit = 0; constIDit < IShape::countOfShape; constIDit++)
							{
								for (int s = pDoc->shapes.size() - 1; s >= 0; s--)
								{
									if (pDoc->shapes[s]->constID == constIDit)
									{
										if (constIDit == pDoc->selectedShapesIDs.front() || constIDit == pDoc->selectedShapesIDs.back())
										{
											//int contsID = pDoc->shapes[it]->constID;
											pDoc->shapes[s]->isSelectedFromDoubleSelectingTool = true;
											shapeIsFound = true;
											IShape* shape;
											pDoc->shapes.push_back(shape);
											iter_swap(pDoc->shapes.begin() + s, pDoc->shapes.end() - 1);
											pDoc->shapes.erase(pDoc->shapes.begin() + s);
											//Invalidate();
										}
									}
									else
									{
										continue;
									}
								}
							}
						}

					}
					break;
				}

				case ShapeType::triangle:
				{

					CPoint cp;
					CString str;
					HRGN triangleRgn = CreatePolygonRgn(pDoc->shapes[i]->points, 3, ALTERNATE);// = CreatePolygonRgn(;
					//HRGN ellipseRgn2 = CreatePolygonRgn(&(pDoc->shapes[i]->eSP[0]), pDoc->shapes[i]->eSP.size(), ALTERNATE);

					if (PtInRegion(triangleRgn, point.x, point.y))
					{
						if (pDoc->shapes[i]->isSelectedFromDoubleSelectingTool)
						{
							i = -1;
							break;
						}
						if (pDoc->selectedShapesIDs.size() > 0 && (pDoc->shapes[i]->constID == pDoc->selectedShapesIDs.front() || pDoc->shapes[i]->constID == pDoc->selectedShapesIDs.back()))
						{
							continue;
						}
						else
						{
							if (pDoc->selectedShapesIDs.size() < 2)
							{

								pDoc->selectedShapesIDs.push(pDoc->shapes[i]->constID);
							}
							else
							{
								pDoc->selectedShapesIDs.pop();
								pDoc->selectedShapesIDs.push(pDoc->shapes[i]->constID);
							}
							//unselected all shapes
							for (int it = 0; it < pDoc->shapes.size(); it++)
							{
								/*if (pDoc->shapes[it]->constID == pDoc->selectedShapesIDs.back())
									continue;
								else*/
								pDoc->shapes[it]->isSelectedFromDoubleSelectingTool = false;
							}
							for (int constIDit = 0; constIDit < IShape::countOfShape; constIDit++)
							{
								for (int s = pDoc->shapes.size() - 1; s >= 0; s--)
								{
									if (pDoc->shapes[s]->constID == constIDit)
									{
										if (constIDit == pDoc->selectedShapesIDs.front() || constIDit == pDoc->selectedShapesIDs.back())
										{
											//int contsID = pDoc->shapes[it]->constID;
											pDoc->shapes[s]->isSelectedFromDoubleSelectingTool = true;
											shapeIsFound = true;
											IShape* shape;
											pDoc->shapes.push_back(shape);
											iter_swap(pDoc->shapes.begin() + s, pDoc->shapes.end() - 1);
											pDoc->shapes.erase(pDoc->shapes.begin() + s);
											//Invalidate();
										}
									}
									else
									{
										continue;
									}
								}
							}
						}

					}
					break;
				}
			
			}
			if (shapeIsFound)
			{
				break;
			}
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

}


void CEgoSecureTestAssignmentView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	auto pDoc = GetDocument();
	if (pDoc->toolIsUsed == Tools::move)
	{
		// move all shapes
		for (int i = 0; i < pDoc->shapes.size(); i++)
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
	else if (pDoc->toolIsUsed == Tools::change)
	{
		bool selected = false; // control of the next loop
		for (int s = 0; s < pDoc->shapes.size(); s++)
		{
			//
			if (pDoc->shapes[s]->isSelected)
			{
				int numberOfAngels = 0;
				if (pDoc->shapes[s]->type == ::ShapeType::triangle)
				{
					numberOfAngels = 3;
				}
				else// if (pDoc->shapes[s]->type == ::ShapeType::rectangle)
				{
					numberOfAngels = 4;
				}
				selected = true;
				for (int a = 0; a < numberOfAngels; a++)
				{
					pDoc->shapes[s]->dx_dy[a].x += pDoc->shapes[s]->dx_dy_temp[a].x;
					pDoc->shapes[s]->dx_dy[a].y += pDoc->shapes[s]->dx_dy_temp[a].y;
					pDoc->shapes[s]->dx_dy_temp[a].x = 0;
					pDoc->shapes[s]->dx_dy_temp[a].y = 0;
					//AfxMessageBox(_T("1"));

				}
			}
		}
	}
	CString str;
	if (pDoc->toolIsUsed == Tools::move)
	{
		str.Format(_T("centerOfShape: x: %d, y: %d"), pDoc->shapes[0]->centerOfShape.x, pDoc->shapes[0]->centerOfShape.y);
		//AfxMessageBox(str);
		str.Format(_T("boxRect: x: %d, y: %d"), pDoc->shapes[0]->boxRect.CenterPoint().x, pDoc->shapes[0]->boxRect.CenterPoint().y);
		//AfxMessageBox(str);
	}
	if (pDoc->toolIsUsed == Tools::shapeMove)
	{
		for (int s = 0; s < pDoc->shapes.size(); s++)
		{
			if (pDoc->shapes[s]->isSelected)
			{
				int tempX = pDoc->shapes[s]->dSM.x;
				int tempY = pDoc->shapes[s]->dSM.y;
				pDoc->shapes[s]->dSM.x = round(tempX * cos((pDoc->shapes[s]->ellipseAngleRad)) - tempY * sin((pDoc->shapes[s]->ellipseAngleRad)));
				pDoc->shapes[s]->dSM.y = round(tempX * sin((pDoc->shapes[s]->ellipseAngleRad)) + tempY * cos((pDoc->shapes[s]->ellipseAngleRad)));
				pDoc->shapes[s]->centerOfShape.x += pDoc->shapes[s]->dSM.x;
				pDoc->shapes[s]->centerOfShape.y += pDoc->shapes[s]->dSM.y;
			}
			pDoc->shapes[s]->dSM.x = 0;
			pDoc->shapes[s]->dSM.y = 0;
		}

		//IShape::diffShapeMove.y = 0;
	}
	CView::OnLButtonUp(nFlags, point);
}


void CEgoSecureTestAssignmentView::OnButtonChange()
{
	//AfxMessageBox(_T("Change"));
	auto pDoc = GetDocument();
	pDoc->toolIsUsed = Tools::change;
	// TODO: Add your command handler code here
}


void CEgoSecureTestAssignmentView::OnButtonRotate()
{
	auto pDoc = GetDocument();
	pDoc->toolIsUsed = Tools::rotate;

	CDC* pDC2 = GetDC();
	//pDC2->Ellipse(200 - 20, 200 - 30, 200 + 20, 200 + 30);
	int nGraphicsMode = SetGraphicsMode(*pDC2, GM_ADVANCED);
	XFORM xForm;
	int m_iAngle = 45;
	double fangle = (double)m_iAngle / 180. * 3.1415926;
	xForm.eM11 = (float)cos(fangle);
	xForm.eM12 = (float)sin(fangle);
	xForm.eM21 = (float)-sin(fangle);
	xForm.eM22 = (float)cos(fangle);
	//xForm.eDx = (float)220;
	//xForm.eDy = (float)-100;
	xForm.eDx = (float)(100 - cos(fangle) * 100 + sin(fangle) * 100);
	xForm.eDy = (float)(100 - cos(fangle) * 100 - sin(fangle) * 100);


	SetWorldTransform(*pDC2, &xForm);
	//pDC2->Ellipse(200 - 20, 200 - 30, 200 + 20, 200 + 30);



	//
	//pDC->Ellipse(pDoc->shapes[0]->centerOfShape.x - 50, pDoc->shapes[0]->centerOfShape.x - 30, pDoc->shapes[0]->centerOfShape.x + 20, pDoc->shapes[0]->centerOfShape.x + 30);

	//ModifyWorldTransform(dc->m_hDC, &xForm, MWT_IDENTITY);
	//ModifyWorldTransform(*pDC, &xForm, MWT_IDENTITY);
	xForm.eM11 = (float)1.0;
	xForm.eM12 = (float)0;
	xForm.eM21 = (float)0;
	xForm.eM22 = (float)1.0;
	xForm.eDx = (float)0;
	xForm.eDy = (float)0;

	SetWorldTransform(*pDC2, &xForm);
	SetGraphicsMode(*pDC2, GM_COMPATIBLE); // nGraphicsMode
	//AfxMessageBox(_T("123"));
	//SetWorldTransform()
	// TODO: Add your command handler code here
}


void CEgoSecureTestAssignmentView::OnButtonShapeNormalize()
{
	//AfxMessageBox(_T("1234567"));
	auto pDoc = GetDocument();
	//pDoc->toolIsUsed = Tools::shapeNormalize; //don't need
	for (int s = 0; s < pDoc->shapes.size(); s++)
	{
		if (pDoc->shapes[s]->isSelected)
		{


			//pDoc->shapes[s]->isNormalized = true;
			pDoc->shapes[s]->ellipseAngleRad = 0;
			CPoint tmp[4];
			if (pDoc->shapes[s]->type == ShapeType::triangle)
			{
				for (int i = 0; i < 4; i++)
				{
					tmp[i] = pDoc->shapes[s]->recFromRgn[i];
				}

			}
			else
			{
				for (int i = 0; i < 4; i++)
				{
					tmp[i] = pDoc->shapes[s]->points[i];
				}

			}

			CPoint centerSidesPoints[2];
			centerSidesPoints[0] = CPoint((tmp[1].x - tmp[0].x) / 2 + tmp[0].x, (tmp[1].y - tmp[0].y) / 2 + tmp[0].y);
			centerSidesPoints[1] = CPoint((tmp[2].x - tmp[1].x) / 2 + tmp[1].x, (tmp[2].y - tmp[1].y) / 2 + tmp[1].y);
			int l1 = (int)sqrt(pow(centerSidesPoints[0].x - pDoc->shapes[s]->centerOfShape.x, 2) + pow(centerSidesPoints[0].y - pDoc->shapes[s]->centerOfShape.y, 2));
			int l2 = (int)sqrt(pow(centerSidesPoints[1].x - pDoc->shapes[s]->centerOfShape.x, 2) + pow(centerSidesPoints[1].y - pDoc->shapes[s]->centerOfShape.y, 2));
			int min;
			min = (l1 < l2) ? l1 : l2;
			CString dbug;
			dbug.Format(_T("%d, %d"), l1, l2);
			//AfxMessageBox(dbug);
			for (int i = 0; i < 4; i++)
			{
				pDoc->shapes[s]->dx_dy[i].x = 0;
				pDoc->shapes[s]->dx_dy[i].y = 0;
				pDoc->shapes[s]->dx_dy_temp[i].x = 0;
				pDoc->shapes[s]->dx_dy_temp[i].y = 0;
			}
			pDoc->shapes[s]->size = min;
			Invalidate();
		}
	}

	// TODO: Add your command handler code here
}


void CEgoSecureTestAssignmentView::OnButtonShapeMove()
{
	auto pDoc = GetDocument();
	pDoc->toolIsUsed = Tools::shapeMove;

	for (int s = 0; s < pDoc->shapes.size(); s++)
	{
		pDoc->shapes[s]->dSM.x = 0;
		pDoc->shapes[s]->dSM.y = 0;
	}
	//pDoc->shapes[s]->diffShapeMove.x = 0;
	//IShape::diffShapeMove.y = 0;
	Invalidate();
	//AfxMessageBox(_T("ckeck"));
	// TODO: Add your command handler code here
}



void CEgoSecureTestAssignmentView::OnButtonDelete()
{
	auto pDoc = GetDocument();
	
		//AfxMessageBox(_T("del"));
		for (int i = 0; i < pDoc->shapes.size(); i++)
		{
			if (pDoc->shapes[i]->isSelected)
			{
				//IShape::IDs.erase(pDoc->shapes[i]->ID); // erase ID because ID won't exist
				//IShape::names.erase(pDoc->shapes[i]->name);
				/*IShape* shape;
				pDoc->shapes.push_back(shape);
				iter_swap(pDoc->shapes.begin() + i, pDoc->shapes.end() - 1);*/
				delete pDoc->shapes[i]; // memory clear
				pDoc->shapes.erase(pDoc->shapes.begin() + i); //erase from vector
				Invalidate();
			}
		}
		
	if (pDoc->toolIsUsed == Tools::doubleSelectTool)
	{
		int ID1_is_selected = pDoc->selectedShapesIDs.front(); //for convenience
		int ID2_is_selected = pDoc->selectedShapesIDs.back();
		for (int i=0; i<pDoc->lines.size(); i++)
		{
			if ((pDoc->lines[i]->FirstShapeConstID == ID1_is_selected && pDoc->lines[i]->SecondShapeConstID == ID2_is_selected) || (pDoc->lines[i]->SecondShapeConstID == ID1_is_selected && pDoc->lines[i]->FirstShapeConstID == ID2_is_selected))
			{
				//int deleteID = pDoc->lines[i]->ID;
				/*Lines::IDs.erase(deleteID);
				Lines::names.erase(pDoc->lines[i]->name);*/
				delete pDoc->lines[i];
				pDoc->lines.erase(pDoc->lines.begin() + i);
				
			}
		}
	}
	Invalidate();
	// TODO: Add your command handler code here
}


void CEgoSecureTestAssignmentView::OnButtonDoubleSelect()
{
	//AfxMessageBox(_T("DoubleSelect"));
	auto pDoc = GetDocument();
	pDoc->toolIsUsed = Tools::doubleSelectTool;
	int s = pDoc->lines.size();
	CString str;
	str.Format(_T("Size lines vector: %d"), s);
	//AfxMessageBox(str);
	//for (Lines* l : pDoc->lines)
	//{
	//	//l->draw();
	//}
	for (auto s : pDoc->shapes)
	{
		s->isSelected = false;
	}
	for (auto s : pDoc->shapes)
	{
		s->isSelectedFromDoubleSelectingTool = false;
	}
	queue<int> clear;
	swap(clear, pDoc->selectedShapesIDs);
	Invalidate();
}


void CEgoSecureTestAssignmentView::OnButtonBasicLine()
{
	auto pDoc = GetDocument();
	if (pDoc->selectedShapesIDs.size() > 1)
	{
		bool LineExists = false;
		for (auto l : pDoc->lines)
		{
			if ((l->FirstShapeConstID == pDoc->selectedShapesIDs.front() && l->SecondShapeConstID == pDoc->selectedShapesIDs.back()) || (l->FirstShapeConstID == pDoc->selectedShapesIDs.back() && l->SecondShapeConstID == pDoc->selectedShapesIDs.front()))
			{
				LineExists = true;
				break;
			}
		}
		if (!LineExists)
		{
			Lines* line = new Lines(pDoc->selectedShapesIDs.front(), pDoc->selectedShapesIDs.back(), LineType::Basic, pDoc->m_color_link, pDoc->num_cb_line_size, pDoc->num_cb_link_type);
			pDoc->lines.push_back(line);
			Invalidate();
		}
	}
	CString db;
	db.Format(_T("lines.size() = %d"), pDoc->lines.size()); 
	//AfxMessageBox(db);
	//AfxMessageBox(_T("BasicLine"));

	// TODO: Add your command handler code here
}


void CEgoSecureTestAssignmentView::OnButtonRightLine()
{
	auto pDoc = GetDocument();
	bool LineExists = false;
	for (auto l : pDoc->lines)
	{
		if ((l->FirstShapeConstID == pDoc->selectedShapesIDs.front() && l->SecondShapeConstID == pDoc->selectedShapesIDs.back()) || (l->FirstShapeConstID == pDoc->selectedShapesIDs.back() && l->SecondShapeConstID == pDoc->selectedShapesIDs.front()))
		{
			LineExists = true;
			break;
		}
	}
	if (!LineExists)
	{
		if (pDoc->selectedShapesIDs.size() > 1)
		{
			Lines* line = new Lines(pDoc->selectedShapesIDs.front(), pDoc->selectedShapesIDs.back(), LineType::Right, pDoc->m_color_link, pDoc->num_cb_line_size, pDoc->num_cb_link_type);
			pDoc->lines.push_back(line);
			Invalidate();
		}
	}
}


void CEgoSecureTestAssignmentView::OnButtonLeftLine()
{
	auto pDoc = GetDocument();
	bool LineExists = false;
	for (auto l : pDoc->lines)
	{
		if ((l->FirstShapeConstID == pDoc->selectedShapesIDs.front() && l->SecondShapeConstID == pDoc->selectedShapesIDs.back()) || (l->FirstShapeConstID == pDoc->selectedShapesIDs.back() && l->SecondShapeConstID == pDoc->selectedShapesIDs.front()))
		{
			LineExists = true;
			break;
		}
	}
	if (!LineExists)
	{
		if (pDoc->selectedShapesIDs.size() > 1)
		{
			Lines* line = new Lines(pDoc->selectedShapesIDs.front(), pDoc->selectedShapesIDs.back(), LineType::Left, pDoc->m_color_link, pDoc->num_cb_line_size, pDoc->num_cb_link_type);
			pDoc->lines.push_back(line);
			Invalidate();
		}
	}
	

}


void CEgoSecureTestAssignmentView::OnButtonDoubleLine()
{
	auto pDoc = GetDocument();
	bool LineExists = false;
	for (auto l : pDoc->lines)
	{
		if ((l->FirstShapeConstID == pDoc->selectedShapesIDs.front() && l->SecondShapeConstID == pDoc->selectedShapesIDs.back()) || (l->FirstShapeConstID == pDoc->selectedShapesIDs.back() && l->SecondShapeConstID == pDoc->selectedShapesIDs.front()))
		{
			LineExists = true;
			break;
		}
	}
	if (!LineExists)
	{
		if (pDoc->selectedShapesIDs.size() > 1)
		{
			Lines* line = new Lines(pDoc->selectedShapesIDs.front(), pDoc->selectedShapesIDs.back(), LineType::Double, pDoc->m_color_link, pDoc->num_cb_line_size, pDoc->num_cb_link_type);
			pDoc->lines.push_back(line);
			Invalidate();
		}
	}
	
	
}


void CEgoSecureTestAssignmentView::OnPropertiesAllshapesandlines()
{
	//AfxMessageBox(_T("12345"));
	auto pDoc = GetDocument();
	List_Control dlg;
	for (auto s : pDoc->shapes)
	{
		dlg.shapes.push_back(s);
	}
	for (auto l : pDoc->lines)
	{
		dlg.lines.push_back(l);
	}
	
	dlg.DoModal();
	
	

	// TODO: Add your command handler code here
}


void CEgoSecureTestAssignmentView::OnListcontrolShapes()
{
	// TODO: Add your command handler code here
}


void CEgoSecureTestAssignmentView::OnPropertiesDefaultdrawproperties()
{
	// TODO: Add your command handler code here
	auto pDoc = GetDocument();
	Default_draw_properties dlg;
	//dlg.SetDataDefaultDrawProperties(pDoc->num_cb_outline_size);
	//dlg.
	//dlg.m_color_outline.SetColor(pDoc->m_outline_color);
	//dlg.m_cb_outline_size.SelectString(0, _T("123"));
	//dlg.m_cb_outline_type.SetCurSel(2);

	dlg.DoModal();
	dlg.m_color_outline.SetColor(RGB(255, 0, 0));
	pDoc->m_outline_color = dlg.m_color_outline_COLORREF;
	pDoc->m_fill_color = dlg.m_color_fill_COLORREF;
	pDoc->num_cb_outline_size = dlg.num_cb_outline_size;
	pDoc->num_cb_outline_type = dlg.num_cb_outline_type;
	pDoc->num_cb_fill_type = dlg.num_cb_fill_type;
	pDoc->num_cb_link_type = dlg.num_cb_link_type;
	pDoc->m_color_link = dlg.m_color_link_COLORREF;
	pDoc->num_cb_line_size = dlg.num_cb_line_size;
	//dlg.UpdateData(true);
	//dlg.SetDataDefaultDrawProperties();
	//dlg.m_cb_outline_size.SetCurSel(0);
	//AfxMessageBox(_T("123"));
}


void CEgoSecureTestAssignmentView::OnButtonProperties()
{
	auto pDoc = GetDocument();
	for (int s = 0; s < pDoc->shapes.size(); s++)
	{
		/*CString str;
		str.Format(_T("%d"), s);
		AfxMessageBox(str);*/
		if (pDoc->shapes[s]->isSelected)
		{
			Dialog_Properties dlg;
			dlg.value_x = pDoc->shapes[s]->centerOfShape.x;
			dlg.value_y = pDoc->shapes[s]->centerOfShape.y;
			dlg.value_outline_R = pDoc->shapes[s]->oR;
			dlg.value_outline_G = pDoc->shapes[s]->oG;
			dlg.value_outline_B = pDoc->shapes[s]->oB;
			dlg.value_fill_R = pDoc->shapes[s]->fR;
			dlg.value_fill_G = pDoc->shapes[s]->fG;
			dlg.value_fill_B = pDoc->shapes[s]->fB;
			dlg.value_degree = pDoc->shapes[s]->ellipseAngleRad * 180.f / 3.14;
			dlg.value_id = pDoc->shapes[s]->ID;
			dlg.value_name = pDoc->shapes[s]->name;
			dlg.value_outline_size = pDoc->shapes[s]->outlineSize;
			dlg.value_outline_type = pDoc->shapes[s]->outlineType;
			dlg.value_fill_type = pDoc->shapes[s]->fillType;
			//AfxMessageBox(_T("1"));
			dlg.DoModal();
			pDoc->shapes[s]->centerOfShape.x = dlg.value_x;
			pDoc->shapes[s]->centerOfShape.y = dlg.value_y;
			// outline color
			pDoc->shapes[s]->outlineColor = RGB(dlg.value_outline_R, GetGValue(pDoc->shapes[s]->outlineColor), GetBValue(pDoc->shapes[s]->outlineColor));
			pDoc->shapes[s]->outlineColor = RGB(GetRValue(pDoc->shapes[s]->outlineColor), dlg.value_outline_G, GetBValue(pDoc->shapes[s]->outlineColor));
			pDoc->shapes[s]->outlineColor = RGB(GetRValue(pDoc->shapes[s]->outlineColor), GetGValue(pDoc->shapes[s]->outlineColor), dlg.value_outline_B);
			// fill color
			pDoc->shapes[s]->fillColor = RGB(dlg.value_fill_R, GetGValue(pDoc->shapes[s]->fillColor), GetBValue(pDoc->shapes[s]->fillColor));
			pDoc->shapes[s]->fillColor = RGB(GetRValue(pDoc->shapes[s]->fillColor), dlg.value_fill_G, GetBValue(pDoc->shapes[s]->fillColor));
			pDoc->shapes[s]->fillColor = RGB(GetRValue(pDoc->shapes[s]->fillColor), GetGValue(pDoc->shapes[s]->fillColor), dlg.value_fill_B);
			// outline size
			pDoc->shapes[s]->outlineSize = dlg.value_outline_size;
			// outline type
			pDoc->shapes[s]->outlineType = dlg.value_outline_type;
			// fill type
			pDoc->shapes[s]->fillType = dlg.value_fill_type;
			// degree
			pDoc->shapes[s]->ellipseAngleRad = dlg.value_degree * 3.14 / 180.f;
			// ID
			if (IShape::IDs.find(dlg.value_id) == IShape::IDs.end())
			{
				IShape::IDs.erase(pDoc->shapes[s]->ID);
				pDoc->shapes[s]->ID = dlg.value_id;
				IShape::IDs.insert(dlg.value_id);
				//IShape::IDs.erase(dlg.value_id);
			}
			// name
			if (IShape::names.find(dlg.value_name) == IShape::names.end())
			{
				IShape::names.erase(pDoc->shapes[s]->name);
				pDoc->shapes[s]->name = dlg.value_name;
				IShape::names.insert(dlg.value_name);

			}
			break;
		}
	}
	if (pDoc->selectedShapesIDs.size() > 1)
	{
		for (int l = 0; l < pDoc->lines.size(); l++)
		{
			if ((pDoc->lines[l]->FirstShapeConstID == pDoc->selectedShapesIDs.front() && pDoc->lines[l]->SecondShapeConstID == pDoc->selectedShapesIDs.back()) || (pDoc->lines[l]->FirstShapeConstID == pDoc->selectedShapesIDs.back() && pDoc->lines[l]->SecondShapeConstID == pDoc->selectedShapesIDs.front()))
			{
				int foundedFirstID;
				int foundedSecondID;
				Dialog_Link_Properties dlg;
				dlg.value_link_color_R = GetRValue(pDoc->lines[l]->lineColor);
				dlg.value_link_color_G = pDoc->lines[l]->lG;
				dlg.value_link_color_B = pDoc->lines[l]->lB;
				for (auto s : pDoc->shapes)
				{
					if (s->constID == pDoc->lines[l]->FirstShapeConstID)
					{
						foundedFirstID = s->ID;
					}
					else if (s->constID == pDoc->lines[l]->SecondShapeConstID)
					{
						foundedSecondID = s->ID;
					}

				}
				dlg.value_link_shape_first_id = foundedFirstID;
				dlg.value_link_shape_second_id = foundedSecondID;
				dlg.value_link_size = pDoc->lines[l]->lineSize;
				dlg.value_link_type = pDoc->lines[l]->lineType;
				if (pDoc->lines[l]->type == LineType::Basic)
				{
					dlg.value_link_type_link = 0;
				}
				else if (pDoc->lines[l]->type == LineType::Right)
				{
					dlg.value_link_type_link = 1;
				}
				else if (pDoc->lines[l]->type == LineType::Left)
				{
					dlg.value_link_type_link = 2;
				}
				else if (pDoc->lines[l]->type == LineType::Double)
				{
					dlg.value_link_type_link = 3;
				}
				dlg.value_link_id = pDoc->lines[l]->ID;
				dlg.name = pDoc->lines[l]->name;

					
				CString str;
				str.Format(_T("R: %d, G: %d, B: %d"), pDoc->lines[l]->lR, pDoc->lines[l]->lG, pDoc->lines[l]->lB);
				dlg.DoModal();
				pDoc->lines[l]->lineColor = RGB(dlg.value_link_color_R, dlg.value_link_color_G, dlg.value_link_color_B);
				if ((dlg.value_link_shape_first_id!= dlg.value_link_shape_second_id)) // can be swaped
				{
					set<int> tempConstIDs;
					for (auto s : pDoc->shapes)
					{
						tempConstIDs.insert(s->constID);
					}
					if (tempConstIDs.find(dlg.value_link_shape_first_id) != tempConstIDs.end() && tempConstIDs.find(dlg.value_link_shape_second_id) != tempConstIDs.end())
					{
						pDoc->lines[l]->FirstShapeConstID = dlg.value_link_shape_first_id;
						pDoc->lines[l]->SecondShapeConstID = dlg.value_link_shape_second_id;
					}

				}
				pDoc->lines[l]->lineSize = dlg.value_link_size;
				pDoc->lines[l]->lineType = dlg.value_link_type;
				switch (dlg.value_link_type_link)
				{
					case 0:
					{
						pDoc->lines[l]->type = LineType::Basic;
						break;
					}
					case 1:
					{
						pDoc->lines[l]->type = LineType::Right;
						break;
					}
					case 2:
					{
						pDoc->lines[l]->type = LineType::Left;
						break;
					}
					case 3:
					{
						pDoc->lines[l]->type = LineType::Double;
						break;
					}
				}
				if (Lines::IDs.find(dlg.value_link_id) == Lines::IDs.end())
				{
					Lines::IDs.erase(pDoc->lines[l]->ID);
					pDoc->lines[l]->ID = dlg.value_link_id;
					Lines::IDs.insert(dlg.value_link_id);
					//IShape::IDs.erase(dlg.value_id);
				}
				// name
				if (Lines::names.find(dlg.name) == Lines::names.end())
				{
					Lines::names.erase(pDoc->lines[l]->name);
					pDoc->lines[l]->name = dlg.name;
					Lines::names.insert(dlg.name);
				}
				/*pDoc->lines[l]->ID = dlg.value_link_id;
				pDoc->lines[l]->name = dlg.name;*/
				/*if ((pDoc->lines[l]->SecondShapeConstID != dlg.value_link_shape_first_id) && (pDoc->lines[l]->FirstShapeConstID != dlg.value_link_shape_second_id))
				{
					set<int> tempConstIDs;
					for (auto s : pDoc->shapes)
					{
						tempConstIDs.insert(s->constID);
					}
					if (tempConstIDs.find(dlg.value_link_shape_first_id) != tempConstIDs.end() && tempConstIDs.find(dlg.value_link_shape_second_id) != tempConstIDs.end())
					{
						pDoc->lines[l]->FirstShapeConstID = dlg.value_link_shape_first_id;
						pDoc->lines[l]->SecondShapeConstID = dlg.value_link_shape_second_id;
					}
					
				}*/
				//pDoc->lines[l]->FirstShapeConstID = dlg.value_link_shape_first_id;
				


				//AfxMessageBox(str);
			}
			//AfxMessageBox(_T("0"));
		}
		//dlg.OnBnClickedButtonGetData();
		//dlg.OnBnClickedButtonGetData();
		// AfxMessageBox(_T("123"));
		// TODO: Add your command handler code here
	}
}