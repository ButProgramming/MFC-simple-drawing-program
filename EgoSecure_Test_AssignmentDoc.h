
#pragma once
#include "Shape.h"

class CEgoSecureTestAssignmentDoc : public CDocument
{
protected: // create from serialization only
	CEgoSecureTestAssignmentDoc() noexcept;
	DECLARE_DYNCREATE(CEgoSecureTestAssignmentDoc)


public:
	vector<IShape*>& getShapesVector() { return shapes; };
	Tools& getToolIsUsed() { return toolIsUsed; };

	COLORREF getOutlineColor() { return outlineColor; };
	void setOutlineColor(COLORREF outlineColor) { this->outlineColor = outlineColor; };

	COLORREF getFillColor() { return fillColor; };
	void setFillColor(COLORREF fillColor) { this->fillColor = fillColor; };

	COLORREF getColorLink() { return colorLink; };
	void setColorLink(COLORREF colorLink) { this->colorLink = colorLink; };

	int getOutlineSize() { return outlineSize; };
	void setOutlineSize(int outlineSize) { this->outlineSize = outlineSize; };

	int getOutlineType() { return outlineType; };
	void setOutlineType(int outlineType) { this->outlineType = outlineType; };

	int getFillType() { return fillType; };
	void setFillType(int fillType) { this->fillType = fillType; };

	int getLinkType() { return linkType; };
	void setLinkType(int linkType) { this->linkType = linkType; };

	int getLineSize() { return lineSize; };
	void setLineSize(int lineSize) { this->lineSize = lineSize; };

	CPoint getFirstClickedPoint() { return firstClickedPoint; };
	void setFirstClickedPoint(CPoint firstClickedPoint) { this->firstClickedPoint = firstClickedPoint; };

private:
	CPoint firstClickedPoint{ NULL, NULL }; //point for first point of move feature
	Tools toolIsUsed;
	vector<IShape*> shapes;
	COLORREF outlineColor = RGB(0, 0, 0);
	COLORREF fillColor = RGB(255, 255, 255);
	COLORREF colorLink = RGB(0, 0, 0);
	int outlineSize = 2;
	int outlineType = 0;
	int fillType = -1;
	int linkType = 0;
	int lineSize = 1;


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


// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// Helper function that sets search content for a Search Handler
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
};
