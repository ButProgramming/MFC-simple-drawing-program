
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
	for (auto l : lines)
	{
		delete l;
	}
	lines.clear();
	IShape::countOfShape = 0;
	Lines::countOfLines = 0;
	IShape::IDs.clear();
	Lines::IDs.clear();
	IShape::names.clear();
	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}




// CEgoSecureTestAssignmentDoc serialization

void CEgoSecureTestAssignmentDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		int ST; // shape type
		int LT; //line type
		int size; 
		int vectorShapeSize = shapes.size();
		int vectorLinesSize = lines.size();
		ar << vectorShapeSize;
		ar << vectorLinesSize;
		
		for (auto s : shapes)
		{
			ar << s->centerOfShape.x << s->centerOfShape.y;
			ar << s->isSelected;
			ar << s->isSelectedFromDoubleSelectingTool;
			ar << s->size;
			ar << s->ellipseAngleRad;
			ar << s->constID;
			
			ar << s->oR;
			ar << s->oG;
			ar << s->oB;

			ar << s->fR;
			ar << s->fG;
			ar << s->fB;

			ar << s->outlineSize;
			ar << s->outlineType;
			ar << s->fillType;

			//ar << s->GetRValue(outlineColor);

			
			for (int i = 0; i < 4; i++)
			{
				ar << s->dx_dy[i];
			}

			if (s->type == ShapeType::ellipse)
			{
				//ST = static_cast<ShapeType::ellipse>();
				ST = 0;
				ar << ST;
			}
			else if(s->type == ShapeType::rectangle)
			{
				ST = 1;
				ar << ST;
			}
			else //if(s->type == ShapeType::triangle)
			{
				ST = 2;
				ar << ST;
			}
			
		}
		for (auto l : lines)
		{
			ar << l->FirstShapeConstID;
			ar << l->SecondShapeConstID;

			ar << l->lR;
			ar << l->lG;
			ar << l->lB;

			ar << l->lineSize;
			ar << l->lineType;


			if (l->type == LineType::Basic)
			{
				//ST = static_cast<ShapeType::ellipse>();
				LT = 0;
				ar << LT;
			}
			else if (l->type == LineType::Right)
			{
				LT = 1;
				ar << LT;
			}
			else if(l->type == LineType::Left)
			{
				LT = 2;
				ar << LT;
			}
			else
			{
				LT = 3;
				ar << LT;
			}
		}

		
		// TODO: add storing code here
	}
	else
	{
		IShape* shapeTemp;
		ShapeType shapeType;
		LineType lineType;
		int ST;
		int LT;
		int size;
		CPoint centerOfShape;
		bool isSelected;
		bool isSelectedFromDoubleSelectingTool;
		int vectorShapeSize;
		int vectorLinesSize;
		int oR, oG, oB;
		int fR, fG, fB;
		int lR, lG, lB;

		int outlineSize;
		int outlineType;
		int fillType;

		int line_Size;
		int line_Type;

		double ellipseAngleRad;
		CPoint dx_dy[4];
		int FirstShapeConstID;
		int SecondShapeConstID;
		int constID;
		Lines* lineTemp;
		ar >> vectorShapeSize;
		ar >> vectorLinesSize;
		CString str;
		str.Format(_T("Shapes: %d, lines: %d"), vectorShapeSize, vectorLinesSize);
		AfxMessageBox(str);
		for (int i = 0; i < vectorShapeSize; i++)
		{
			ar >> centerOfShape.x >> centerOfShape.y;
			ar >> isSelected;
			ar >> isSelectedFromDoubleSelectingTool;
			ar >> size;
			ar >> ellipseAngleRad;
			ar >> constID;
			ar >> oR;
			ar >> oG;
			ar >> oB;
			
			ar >> fR;
			ar >> fG;
			ar >> fB;

			ar >> outlineSize;
			ar >> outlineType;
			ar >> fillType;

			for (int i = 0; i < 4; i++)
			{
				ar >> dx_dy[i];
			}

			ar >> ST;
			if (ST == 0)
			{
				shapeType = ShapeType::ellipse;
				shapeTemp = new EllipseShape(centerOfShape, true, size, shapeType, RGB(oR, oG, oB), RGB(fR, fG, fB), outlineSize, outlineType, fillType);
				shapeTemp->isSelected = isSelected;
			}
			else if (ST == 1)
			{
				shapeType = ShapeType::rectangle;
				shapeTemp = new RectangleShape(centerOfShape, true, size, shapeType, RGB(oR, oG, oB), RGB(fR, fG, fB), outlineSize, outlineType, fillType);
				shapeTemp->isSelected = isSelected;
			}
			else
			{
				shapeType = ShapeType::triangle;
				shapeTemp = new TriangleShape(centerOfShape, true, size, shapeType, RGB(oR, oG, oB), RGB(fR, fG, fB), outlineSize, outlineType, fillType);
				shapeTemp->isSelected = isSelected;
			}
			
			//shapes.emplace_back(shape);
			shapes.push_back(shapeTemp);
			shapes[shapes.size() - 1]->ellipseAngleRad = ellipseAngleRad;
			shapes[shapes.size() - 1]->constID = constID;
			shapes[shapes.size() - 1]->isSelectedFromDoubleSelectingTool = isSelectedFromDoubleSelectingTool;
			shapes[shapes.size() - 1]->oR = oR;
			shapes[shapes.size() - 1]->oG = oG;
			shapes[shapes.size() - 1]->oB = oB;

			for (int i = 0; i < 4; i++)
			{
				shapes[shapes.size() - 1]->dx_dy[i] = dx_dy[i];
			}

			}
			for (int i = 0; i < vectorLinesSize; i++)
			{
				ar >> FirstShapeConstID;
				ar >> SecondShapeConstID;

				ar >> lR;
				ar >> lG;
				ar >> lB;

				ar >> line_Size;
				ar >> line_Type;
				//ar >> lineType;

				ar >> LT;
				if (LT == 0)
				{
					lineType = LineType::Basic;
					lineTemp = new Lines(FirstShapeConstID, SecondShapeConstID, lineType, RGB(lR,lG,lB), line_Size, line_Type);
					//lineTemp->isSelected = isSelected;
				}
				else if (LT == 1)
				{
					lineType = LineType::Right;
					lineTemp = new Lines(FirstShapeConstID, SecondShapeConstID, lineType, RGB(lR, lG, lB), line_Size, line_Type);
					//lineTemp->isSelected = isSelected;
				}
				else if (LT == 2)
				{
					lineType = LineType::Left;
					lineTemp = new Lines(FirstShapeConstID, SecondShapeConstID, lineType, RGB(lR, lG, lB), line_Size, line_Type);
					//lineTemp->isSelected = isSelected;
				}
				else
				{
					lineType = LineType::Double;
					lineTemp = new Lines(FirstShapeConstID, SecondShapeConstID, lineType, RGB(lR, lG, lB), line_Size, line_Type);
					//lineTemp->isSelected = isSelected;
				}
				lines.push_back(lineTemp);
		}
		
		//CString str;
		str.Format(_T("Shapes: %d, lines: %d"), shapes.size(), lines.size());
		//AfxMessageBox(str);

		toolIsUsed = Tools::select_tool;
		// TODO: add loading code here
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
