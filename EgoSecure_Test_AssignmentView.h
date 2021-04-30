
// EgoSecure_Test_AssignmentView.h : interface of the CEgoSecureTestAssignmentView class
//

#pragma once
#define START_HORIZONTAL_SCROLL_RANGE_MIN -500
#define START_HORIZONTAL_SCROLL_RANGE_MAX 500
#define HORIZONTAL_SCROLLBAR_DX 300
#define START_VERTICAL_SCROLL_RANGE_MIN -250
#define START_VERTICAL_SCROLL_RANGE_MAX 250
#define VERTICAL_SCROLLBAR_DX 150
#define MULTIPLIER_DOWN_POS_HORIZONTAL_SCROLL_BAR_1080_Y 0.89
#define MULTIPLIER_DOWN_POS_HORIZONTAL_SCROLL_BAR_1050_Y 0.89
#define MULTIPLIER_DOWN_POS_HORIZONTAL_SCROLL_BAR_900_Y 0.87
#define MULTIPLIER_DOWN_POS_HORIZONTAL_SCROLL_BAR_768_Y 0.85
#define MULTIPLIER_DOWN_POS_HORIZONTAL_SCROLL_BAR_1024_Y 0.89
#define MULTIPLIER_DOWN_POS_HORIZONTAL_SCROLL_BAR_960_Y 0.88
#define MULTIPLIER_DOWN_POS_HORIZONTAL_SCROLL_BAR_800_Y 0.85
#define MULTIPLIER_DOWN_POS_HORIZONTAL_SCROLL_BAR_720_Y 0.85
#define MULTIPLIER_DOWN_POS_HORIZONTAL_SCROLL_BAR_864_Y 0.86
#define MULTIPLIER_DOWN_POS_HORIZONTAL_SCROLL_BAR_600_Y 0.82
#define MULTIPLIER_RIGHT_POS_HORIZONTAL_SCROLL_BAR 0.96

constexpr UINT IDC_BUTTON1{ 101 };
constexpr UINT IDC_SB_HOR{ 102 };
constexpr UINT IDC_SB_VERT{ 103 };

class CEgoSecureTestAssignmentView : public CView
{

// Attributes
public:
	CEgoSecureTestAssignmentDoc* GetDocument() const;
	CDC m_dc;
	CBitmap m_bmt;
	



protected: // create from serialization only
	CEgoSecureTestAssignmentView() noexcept;
	DECLARE_DYNCREATE(CEgoSecureTestAssignmentView)

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
	afx_msg void OnButtonEllipse();
	afx_msg void OnButtonRectangle();
	afx_msg void OnButtonTriangle();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnButtonSelectTool();
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnButtonMove();
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnButtonChange();
	afx_msg void OnButtonRotate();
	afx_msg void OnButtonShapeNormalize();
	afx_msg void OnButtonShapeMove();
	afx_msg void OnButtonDelete();
	afx_msg void OnButtonDoubleSelect();
	afx_msg void OnButtonBasicLine();
	afx_msg void OnButtonRightLine();
	afx_msg void OnButtonLeftLine();
	afx_msg void OnButtonDoubleLine();
	afx_msg void OnPropertiesAllshapesandlines();
	afx_msg void OnListcontrolShapes();
	afx_msg void OnPropertiesDefaultdrawproperties();
	afx_msg void OnButtonProperties();
	afx_msg void OnEditNormalize();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	void createHorizontalAndVecticalSB(int x, int y);


private:
	// horizontal and vertical scrollbar common variables
	CPoint prevCoordinate{ 0, 0 }; // previous coordinate, that is needed to calculate a difference between currently position of horizontal scrollbar
								   // and previous. This CPoint is used for movement all shapes

	// horizontal scrollbar
	CScrollBar m_hsb; // horizontal scrollbar
	int horizontalScrollBarValue = 0; 
	struct valueOfHorizontalScrollBar { int min = START_HORIZONTAL_SCROLL_RANGE_MIN; int max = START_HORIZONTAL_SCROLL_RANGE_MAX; } valueOfHorizontalScrollBar; // currently min and max coordinates of horizontal scrollbar

	//vertical scrollbar
	CScrollBar m_vsb; // vertical scrollbar
	int verticalScrollBarValue = 0; 
	struct valueOfVerticalScrollBar { int min = START_VERTICAL_SCROLL_RANGE_MIN; int max = START_VERTICAL_SCROLL_RANGE_MAX; } valueOfVerticalScrollBar; // currently min and max coordinates of vertical scrollbar
public:
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
};

#ifndef _DEBUG  // debug version in EgoSecure_Test_AssignmentView.cpp
inline CEgoSecureTestAssignmentDoc* CEgoSecureTestAssignmentView::GetDocument() const
   { return reinterpret_cast<CEgoSecureTestAssignmentDoc*>(m_pDocument); }
#endif

