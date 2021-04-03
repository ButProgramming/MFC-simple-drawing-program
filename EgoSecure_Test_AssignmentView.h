
// EgoSecure_Test_AssignmentView.h : interface of the CEgoSecureTestAssignmentView class
//

#pragma once


class CEgoSecureTestAssignmentView : public CView
{
protected: // create from serialization only
	CEgoSecureTestAssignmentView() noexcept;
	DECLARE_DYNCREATE(CEgoSecureTestAssignmentView)

// Attributes
public:
	CEgoSecureTestAssignmentDoc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// Implementation
public:
	virtual ~CEgoSecureTestAssignmentView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
};

#ifndef _DEBUG  // debug version in EgoSecure_Test_AssignmentView.cpp
inline CEgoSecureTestAssignmentDoc* CEgoSecureTestAssignmentView::GetDocument() const
   { return reinterpret_cast<CEgoSecureTestAssignmentDoc*>(m_pDocument); }
#endif

