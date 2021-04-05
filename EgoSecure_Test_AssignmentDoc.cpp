
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
	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}




// CEgoSecureTestAssignmentDoc serialization

void CEgoSecureTestAssignmentDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		int ST;
		int size;
		int vectorSize = shapes.size();
		ar << vectorSize;
		for (auto s : shapes)
		{
			ar << s->centerOfShape.x << s->centerOfShape.y;
			ar << s->isSelected;
			ar << s->size;
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
		// TODO: add storing code here
	}
	else
	{
		IShape* shape;
		ShapeType type;
		int ST;
		int size;
		CPoint centerOfShape;
		bool isSelected;
		int vectorSize;
		ar >> vectorSize;
		CString str;
		str.Format(_T("Size: %d"), vectorSize);
		AfxMessageBox(str);
		for (int i = 0; i < vectorSize; i++)
		{
			ar >> centerOfShape.x >> centerOfShape.y;
			ar >> isSelected;
			ar >> size;
			ar >> ST;
			
			if (ST == 0)
			{
				type = ShapeType::ellipse;
				shape = new EllipseShape(centerOfShape, true, size, type);
				shape->isSelected = isSelected;
			}
			else if (ST == 1)
			{
				type = ShapeType::rectangle;
				shape = new RectangleShape(centerOfShape, true, size, type);
				shape->isSelected = isSelected;
			}
			else
			{
				type = ShapeType::triangle;
				shape = new TriangleShape(centerOfShape, true, size, type);
				shape->isSelected = isSelected;
			}
			
			
			shapes.emplace_back(shape);
			
		}
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
