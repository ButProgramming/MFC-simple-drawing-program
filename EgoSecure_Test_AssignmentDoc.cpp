#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "EgoSecure_Test_Assignment.h"
#endif

#include "EgoSecure_Test_AssignmentDoc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#include <cmath>
using namespace std;

IMPLEMENT_DYNCREATE(CEgoSecureTestAssignmentDoc, CDocument)

BEGIN_MESSAGE_MAP(CEgoSecureTestAssignmentDoc, CDocument)
END_MESSAGE_MAP()


// CEgoSecureTestAssignmentDoc construction/destruction

CEgoSecureTestAssignmentDoc::CEgoSecureTestAssignmentDoc() noexcept
{

	

}

CEgoSecureTestAssignmentDoc::~CEgoSecureTestAssignmentDoc()
{
}

BOOL CEgoSecureTestAssignmentDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;
	for (auto s : shapes)
	{
		delete s;
	}
	shapes.clear();
	IShape::setCountOfShape(0);
	IShape::getIDs().clear();
	IShape::getNames().clear();

	return TRUE;
}




// CEgoSecureTestAssignmentDoc serialization

void CEgoSecureTestAssignmentDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		int shapeType = NULL;
		int vectorShapeSize = shapes.size();
		ar << vectorShapeSize;
		
		for (auto s : shapes)
		{
			ar << s->getCenterOfShape();
			ar << s->getSelected();
			ar << s->getSize();
			ar << s->getAngleRad();
			ar << s->getID();
			ar << s->getConstID();
			ar << s->getName();
			
			int oR = GetRValue(s->getOutlineColor());
			int oG = GetGValue(s->getOutlineColor());
			int oB = GetBValue(s->getOutlineColor());

			int fR = GetRValue(s->getFillColor());
			int fG = GetGValue(s->getFillColor());
			int fB = GetBValue(s->getFillColor());

			ar << oR;
			ar << oG;
			ar << oB;

			ar << fR;
			ar << fG;
			ar << fB;

			ar << s->getOutlineSize();
			ar << s->getOutlineType();
			ar << s->getFillType();

			ar << s->getCoordinateForChange(0);
			ar << s->getCoordinateForChange(1);

			ar << s->getPointForLine(0);
			ar << s->getPointForLine(1);
			ar << s->getPointForLine(2);
			ar << s->getPointForLine(3);
			
			for (int i = 0; i < 4; i++)
			{
				ar << s->getChangeDxDy(i);
			}

			switch (s->getShapeType())
			{
				case ShapeType::ellipse:
				{
					shapeType = 0;
					ar << shapeType;
					break;
				}
				case ShapeType::rectangle:
				{
					shapeType = 1;
					ar << shapeType;
					break;
				}
				case ShapeType::triangle:
				{
					shapeType = 2;
					ar << shapeType;
					break;
				}
				case ShapeType::basicLine:
				{
					shapeType = 3;
					ar << shapeType;
					break;
				}
				case ShapeType::rightLine:
				{
					shapeType = 4;
					ar << shapeType;
					break;
				}
				case ShapeType::leftLine:
				{
					shapeType = 5;
					ar << shapeType;
					break;
				}
				case ShapeType::doubleLine:
				{
					shapeType = 6;
					ar << shapeType;
					break;
				}
			}

			ar << s->getIsConnected(FIRST_POINT_OF_LINE);
			ar << s->getIsConnected(SECOND_POINT_OF_LINE);

			ar << s->getConnectedShapeConstID(FIRST_POINT_OF_LINE);
			ar << s->getConnectedShapeConstID(SECOND_POINT_OF_LINE);

			ar << s->getNumberOfShapesPointForLines(FIRST_POINT_OF_LINE);
			ar << s->getNumberOfShapesPointForLines(SECOND_POINT_OF_LINE);
						
		}
	}
	else
	{
		array <CPoint, 4> linkingPoints;
		bool isConnected1;
		bool isConnected2;
		int connectedShapeConstID1;
		int connectedShapeConstID2;
		int numberOfShapesPointForLines1;
		int numberOfShapesPointForLines2;

		CPoint coordinateForChange1;
		CPoint coordinateForChange2;
		IShape* shapeTemp;
		ShapeType shapeType;
		int ST;
		int size;
		CPoint centerOfShape;
		bool isSelected;
		int vectorShapeSize;
		int oR, oG, oB;
		int fR, fG, fB;
		CString shapeName;
		int outlineSize;
		int outlineType;
		int fillType;

		int line_Size;
		int line_Type;

		double angleRad;
		CPoint dx_dy[4];
		array <CPoint, 4> dxDy;
		int FirstShapeConstID;
		int SecondShapeConstID;
		int shapeConstID;
		int shapeID;
		int lineConstID;
		int lineID;
		//Lines* lineTemp;
		ar >> vectorShapeSize;

		for (int i = 0; i < vectorShapeSize; i++)
		{
			//ar >> centerOfShape.x >> centerOfShape.y;
			ar >> centerOfShape;
			ar >> isSelected;
			ar >> size;
			ar >> angleRad;
			ar >> shapeID;
			ar >> shapeConstID;
			ar >> shapeName;

			ar >> oR;
			ar >> oG;
			ar >> oB;
			
			ar >> fR;
			ar >> fG;
			ar >> fB;

			ar >> outlineSize;
			ar >> outlineType;
			ar >> fillType;

			ar >> coordinateForChange1;
			ar >> coordinateForChange2;

			for (int i = 0; i < 4; i++)
			{
				ar >> linkingPoints[i];
			}

			for (int i = 0; i < 4; i++)
			{
				ar >> dxDy[i];
			}

			ar >> ST;

			switch (ST)
			{
				case 0:
				{
					shapeType = ShapeType::ellipse;
					shapeTemp = new EllipseShape(centerOfShape, true, size, shapeType, RGB(oR, oG, oB), RGB(fR, fG, fB), outlineSize, outlineType, fillType);
					shapeTemp->setSelected(isSelected);
					break;
				}
				case 1:
				{
					shapeType = ShapeType::rectangle;
					shapeTemp = new RectangleShape(centerOfShape, true, size, shapeType, RGB(oR, oG, oB), RGB(fR, fG, fB), outlineSize, outlineType, fillType);
					shapeTemp->setSelected(isSelected);
					break;
				}
				case 2:
				{
					shapeType = ShapeType::triangle;
					shapeTemp = new TriangleShape(centerOfShape, true, size, shapeType, RGB(oR, oG, oB), RGB(fR, fG, fB), outlineSize, outlineType, fillType);
					shapeTemp->setSelected(isSelected);
					break;
				}
				case 3:
				{
					shapeType = ShapeType::basicLine;
					shapeTemp = new Line(CPoint{ 0, 0 }, shapeType, RGB(oR, oG, oB), outlineSize, outlineType);
					shapeTemp->setSelected(isSelected);
					break;
				}
				case 4:
				{
					shapeType = ShapeType::rightLine;
					shapeTemp = new Line(CPoint{ 0, 0 }, shapeType, RGB(oR, oG, oB), outlineSize, outlineType);
					shapeTemp->setSelected(isSelected);
					break;
				}
				case 5:
				{
					shapeType = ShapeType::leftLine;
					shapeTemp = new Line(CPoint{ 0, 0 }, shapeType, RGB(oR, oG, oB), outlineSize, outlineType);
					shapeTemp->setSelected(isSelected);
					break;
				}
				case 6:
				{
					shapeType = ShapeType::doubleLine;
					shapeTemp = new Line(CPoint{ 0, 0 }, shapeType, RGB(oR, oG, oB), outlineSize, outlineType);
					shapeTemp->setSelected(isSelected);
					break;
				}
			}

			ar >> isConnected1;
			ar >> isConnected2;
			ar >> connectedShapeConstID1;
			ar >> connectedShapeConstID2;
			ar >> numberOfShapesPointForLines1;
			ar >> numberOfShapesPointForLines2;

			
			shapes.push_back(shapeTemp);

			shapes[shapes.size() - 1]->setAngleRad(angleRad);

			IShape::getIDs().erase(shapes[shapes.size() - 1]->getID());
			shapes[shapes.size() - 1]->setID(shapeID);
			IShape::getIDs().insert(shapes[shapes.size() - 1]->getID());

			shapes[shapes.size() - 1]->setConstID(shapeConstID);
			
			IShape::getNames().erase(shapes[shapes.size() - 1]->getName());
			shapes[shapes.size() - 1]->setName(shapeName);
			IShape::getNames().insert(shapes[shapes.size() - 1]->getName());

			shapes[shapes.size() - 1]->setOutlineColor(RGB(oR, oG, oB));

			if (shapes[shapes.size() - 1]->getShapeType() != ShapeType::ellipse && shapes[shapes.size() - 1]->getShapeType() != ShapeType::rectangle && shapes[shapes.size() - 1]->getShapeType() != ShapeType::triangle)
			{
				shapes[shapes.size() - 1]->setCoordinateForChange(0, coordinateForChange1);
				shapes[shapes.size() - 1]->setCoordinateForChange(1, coordinateForChange2);
			}
			

			for (int i = 0; i < 4; i++)
			{
				shapes[shapes.size() - 1]->setChangeDxDy(i, dxDy[i]);
			}

			shapes[shapes.size() - 1]->setIsConnected(FIRST_POINT_OF_LINE, isConnected1);
			shapes[shapes.size() - 1]->setIsConnected(SECOND_POINT_OF_LINE, isConnected2);
			shapes[shapes.size() - 1]->setConnectedShapeConstID(FIRST_POINT_OF_LINE, connectedShapeConstID1);
			shapes[shapes.size() - 1]->setConnectedShapeConstID(SECOND_POINT_OF_LINE, connectedShapeConstID2);
			shapes[shapes.size() - 1]->setNumberOfShapesPointForLines(FIRST_POINT_OF_LINE, numberOfShapesPointForLines1);
			shapes[shapes.size() - 1]->setNumberOfShapesPointForLines(SECOND_POINT_OF_LINE, numberOfShapesPointForLines2);


			for (int i = 0; i < 4; i++)
			{
				shapes[shapes.size() - 1]->setPointsForLine(i, linkingPoints[i]);
			}

					

			}

		toolIsUsed = Tools::select_tool;

	}
	
}

#ifdef SHARED_HANDLERS

// Support for thumbnails
void CEgoSecureTestAssignmentDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// Modify this code to draw the document's data
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// Support for Search Handlers
void CEgoSecureTestAssignmentDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// Set search contents from document's data.
	// The content parts should be separated by ";"

	// For example:  strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CEgoSecureTestAssignmentDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = nullptr;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != nullptr)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CEgoSecureTestAssignmentDoc diagnostics

#ifdef _DEBUG
void CEgoSecureTestAssignmentDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CEgoSecureTestAssignmentDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CEgoSecureTestAssignmentDoc commands
