#pragma once
#include <afx.h>
#include "Shape.h"
#include "Lines.h"

// List_Control dialog

class List_Control : public CDialogEx, public CObject
{
	DECLARE_DYNAMIC(List_Control)

public:
	List_Control(CWnd* pParent = nullptr);   // standard constructor
	virtual ~List_Control();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_LISTCONTROL };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_listControl_shapes;
	vector<IShape*> shapes;
	//vector<Lines*> lines;
	afx_msg void OnItemchangedListcontrolShapes(NMHDR* pNMHDR, LRESULT* pResult);
	CListCtrl m_listControl_lines;
};
