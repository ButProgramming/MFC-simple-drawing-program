// DialogTest.cpp : implementation file
//

#include "pch.h"
#include "EgoSecure_Test_Assignment.h"
#include "DialogTest.h"
#include "afxdialogex.h"


// DialogTest dialog

IMPLEMENT_DYNAMIC(DialogTest, CDialogEx)

DialogTest::DialogTest(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG1, pParent)
{

}

DialogTest::~DialogTest()
{
}

void DialogTest::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, combo_box_1);
	DDX_Control(pDX, IDC_COMBOBOXEX1, combo_box_2);
	DDX_Control(pDX, IDC_BUTTON1, ButtonTest);
	DDX_Control(pDX, IDC_STATIC_TEST, static_text_test);
	DDX_Control(pDX, IDC_EDIT1, edit_test);
}


BEGIN_MESSAGE_MAP(DialogTest, CDialogEx)
	ON_CBN_SELCHANGE(IDC_COMBO1, &DialogTest::OnSelchangeCombo1)
	ON_CBN_SELCHANGE(IDC_COMBOBOXEX1, &DialogTest::OnCbnSelchangeComboboxex1)
	ON_BN_CLICKED(IDC_BUTTON1, &DialogTest::OnBnClickedButton1)
	ON_COMMAND(IDC_STATIC, &DialogTest::OnStatic)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST4, &DialogTest::OnLvnItemchangedList4)
END_MESSAGE_MAP()


// DialogTest message handlers


void DialogTest::OnSelchangeCombo1()
{
	int number = combo_box_1.GetCurSel();
	CString str;
	str.Format(_T("%d"), number);
	AfxMessageBox(str);
	// TODO: Add your control notification handler code here
}


void DialogTest::OnCbnSelchangeComboboxex1()
{
	// TODO: Add your control notification handler code here
}


void DialogTest::OnBnClickedButton1()
{
	//ATLASSERT(edit_test.IsWindow()); // Make sure the control holds a handle
	CString sWindowText;
	edit_test.GetWindowText(sWindowText);
	AfxMessageBox(sWindowText);
	static_text_test.SetWindowTextW(_T("123"));
	edit_test.SetWindowTextW(_T("123"));
	// TODO: Add your control notification handler code here
}


void DialogTest::OnStatic()
{
	// TODO: Add your command handler code here
}


void DialogTest::OnLvnItemchangedList4(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: Add your control notification handler code here
	*pResult = 0;
}
