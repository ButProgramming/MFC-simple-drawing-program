
// EgoSecure_Test_AssignmentDoc.cpp : implementation of the CEgoSecureTestAssignmentDoc class
//

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

// CEgoSecureTestAssignmentDoc

IMPLEMENT_DYNCREATE(CEgoSecureTestAssignmentDoc, CDocument)

BEGIN_MESSAGE_MAP(CEgoSecureTestAssignmentDoc, CDocument)
END_MESSAGE_MAP()


// CEgoSecureTestAssignmentDoc construction/destruction

CEgoSecureTestAssignmentDoc::CEgoSecureTestAssignmentDoc() noexcept
{

	// TODO: add one-time construction code here

}

CEgoSecureTestAssignmentDoc::~CEgoSecureTestAssignmentDoc()
{
}

BOOL CEgoSecureTestAssignmentDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;
	//shapes.clear();
	for (auto s : shapes)
	{
		delete s;
	}
	shapes.clear();
	/*for (auto l : lines)
	{
		delete l;
	}*/
	//lines.clear();
	IShape::countOfShape = 0;
	//Lines::countOfLines = 0;
	IShape::IDs.clear();
	//Lines::IDs.clear();
	IShape::names.clear();
	//Lines::names.clear();
	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

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
			ar << s->centerOfShape.x << s->centerOfShape.y;
			ar << s->isSelected;
			ar << s->size;
			ar << s->ellipseAngleRad;
			ar << s->ID;
			ar << s->constID;
			ar << s->name;
			
			ar << s->oR;
			ar << s->oG;
			ar << s->oB;

			ar << s->fR;
			ar << s->fG;
			ar << s->fB;

			ar << s->outlineSize;
			ar << s->outlineType;
			ar << s->fillType;

			ar << s->getCoordinateForChange(0);
			ar << s->getCoordinateForChange(1);

			
			for (int i = 0; i < 4; i++)
			{
				ar << s->getChangeDxDy(i);
			}

			switch (s->type)
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

			ar << s->connecting.isConnected.firstPointOfLine;
			ar << s->connecting.isConnected.secondPointOfLine;
			ar << s->connecting.connectedShapeConstID.firstPointOfLine;
			ar << s->connecting.connectedShapeConstID.secondPointOfLine;
			ar << s->connecting.numberOfShapesPointForLines.firstPointOfLine;
			ar << s->connecting.numberOfShapesPointForLines.secondPointOfLine;
						
		}
	}
	else
	{
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

		double ellipseAngleRad;
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
			ar >> centerOfShape.x >> centerOfShape.y;
			ar >> isSelected;
			ar >> size;
			ar >> ellipseAngleRad;
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
				//ar >> dx_dy[i];
				ar >> dxDy[i];
			}

			ar >> ST;
			//ar >> ST;
			//ar >> ST;
			switch (ST)
			{
				case 0:
				{
					shapeType = ShapeType::ellipse;
					shapeTemp = new EllipseShape(centerOfShape, true, size, shapeType, RGB(oR, oG, oB), RGB(fR, fG, fB), outlineSize, outlineType, fillType);
					shapeTemp->isSelected = isSelected;
					break;
				}
				case 1:
				{
					shapeType = ShapeType::rectangle;
					shapeTemp = new RectangleShape(centerOfShape, true, size, shapeType, RGB(oR, oG, oB), RGB(fR, fG, fB), outlineSize, outlineType, fillType);
					shapeTemp->isSelected = isSelected;
					break;
				}
				case 2:
				{
					shapeType = ShapeType::triangle;
					shapeTemp = new TriangleShape(centerOfShape, true, size, shapeType, RGB(oR, oG, oB), RGB(fR, fG, fB), outlineSize, outlineType, fillType);
					shapeTemp->isSelected = isSelected;
					break;
				}
				case 3:
				{
					shapeType = ShapeType::basicLine;
					shapeTemp = new Line(CPoint{ 0, 0 }, shapeType, RGB(0, 0, 0), 2, 1);
					shapeTemp->isSelected = isSelected;
					break;
				}
				case 4:
				{
					shapeType = ShapeType::rightLine;
					shapeTemp = new Line(CPoint{ 0, 0 }, shapeType, RGB(0, 0, 0), 2, 1);
					shapeTemp->isSelected = isSelected;
					break;
				}
				case 5:
				{
					shapeType = ShapeType::leftLine;
					shapeTemp = new Line(CPoint{ 0, 0 }, shapeType, RGB(0, 0, 0), 2, 1);
					shapeTemp->isSelected = isSelected;
					break;
				}
				case 6:
				{
					shapeType = ShapeType::doubleLine;
					shapeTemp = new Line(CPoint{ 0, 0 }, shapeType, RGB(0, 0, 0), 2, 1);
					shapeTemp->isSelected = isSelected;
					break;
				}
			}

			ar >> isConnected1;
			ar >> isConnected2;
			ar >> connectedShapeConstID1;
			ar >> connectedShapeConstID2;
			ar >> numberOfShapesPointForLines1;
			ar >> numberOfShapesPointForLines2;

			//shapes.emplace_back(shape);
			vector<IShape*> shapes2;
			shapes.push_back(shapeTemp);
			shapes[shapes.size() - 1]->constID;
			shapes[shapes.size() - 1]->ellipseAngleRad = ellipseAngleRad;
			shapes[shapes.size() - 1]->ID = shapeID;
			shapes[shapes.size() - 1]->constID = shapeConstID;
			shapes[shapes.size() - 1]->name = shapeName;
			//shapes[shapes.size() - 1]->isSelectedFromDoubleSelectingTool = isSelectedFromDoubleSelectingTool;
			shapes[shapes.size() - 1]->oR = oR;
			shapes[shapes.size() - 1]->oG = oG;
			shapes[shapes.size() - 1]->oB = oB;
			if (shapes[shapes.size() - 1]->type != ShapeType::ellipse && shapes[shapes.size() - 1]->type != ShapeType::rectangle && shapes[shapes.size() - 1]->type != ShapeType::triangle)
			{
				shapes[shapes.size() - 1]->setCoordinateForChange(0, coordinateForChange1);
				shapes[shapes.size() - 1]->setCoordinateForChange(1, coordinateForChange2);
			}
			

			for (int i = 0; i < 4; i++)
			{
				//shapes[shapes.size() - 1]->dx_dy[i] = dx_dy[i];
				shapes[shapes.size() - 1]->setChangeDxDy(i, dxDy[i]);
			}
			shapes[shapes.size() - 1]->connecting.isConnected.firstPointOfLine = isConnected1;
			shapes[shapes.size() - 1]->connecting.isConnected.secondPointOfLine = isConnected2;
			shapes[shapes.size() - 1]->connecting.connectedShapeConstID.firstPointOfLine = connectedShapeConstID1;
			shapes[shapes.size() - 1]->connecting.connectedShapeConstID.secondPointOfLine = connectedShapeConstID2;
			shapes[shapes.size() - 1]->connecting.numberOfShapesPointForLines.firstPointOfLine = numberOfShapesPointForLines1;
			shapes[shapes.size() - 1]->connecting.numberOfShapesPointForLines.secondPointOfLine = numberOfShapesPointForLines2;


			}
		//str.Format(_T("Shapes: %d, lines: %d"), shapes.size(), lines.size());

		toolIsUsed = Tools::select_tool;
		//Invalidate();
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
