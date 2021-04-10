
// EgoSecure_Test_AssignmentDoc.h : interface of the CEgoSecureTestAssignmentDoc class
//


#pragma once
#include "Shape.h"
#include "Lines.h"

class CEgoSecureTestAssignmentDoc : public CDocument
{
protected: // create from serialization only
	CEgoSecureTestAssignmentDoc() noexcept;
	DECLARE_DYNCREATE(CEgoSecureTestAssignmentDoc)

// Attributes
public:
	vector<IShape*> shapes;
	vector<Lines*> lines;
	Tools toolIsUsed;
	//screen move dx and dy
	struct first { int x; int y; } first; //point for first point of move feature
	struct second { int x; int y; } second;//point for second point of move feature
	

	int dx = 0;
	int dy = 0;
// Operations
public:

// Overrides
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// Implementation
public:
	virtual ~CEgoSecureTestAssignmentDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// Helper function that sets search content for a Search Handler
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
};
