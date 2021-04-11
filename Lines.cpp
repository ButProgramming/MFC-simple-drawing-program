#include "pch.h"
#include "Lines.h"

Lines::Lines(int FirstShapeConstID, int SecondShapeConstID, LineType type)
{
	this->FirstShapeConstID = FirstShapeConstID;
	this->SecondShapeConstID = SecondShapeConstID;
	this->type = type;
	CString strType;
	if (type == LineType::Basic)
	{
		strType = "Basic";
	}
	else if (type == LineType::Left)
	{
		strType = "Left";
	}
	else if (type == LineType::Right)
	{
		strType = "Right";
	}
	else
	{
		strType = "Double";
	}
	CString debug;
	debug.Format(_T("First: %d, second %d, line type: %s"), FirstShapeConstID, SecondShapeConstID, strType);
	//AfxMessageBox(debug);
}
