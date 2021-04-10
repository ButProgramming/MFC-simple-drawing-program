#include "pch.h"
#include "Lines.h"

void BasicLine::draw()
{
	AfxMessageBox(_T("BasicLine"));
}

void RightLine::draw()
{
	AfxMessageBox(_T("RightLine"));
}

void LeftLine::draw()
{
	AfxMessageBox(_T("LeftLine"));
}

void DoubleLine::draw()
{
	AfxMessageBox(_T("DoubleLine"));
}

Lines::~Lines()
{
}
