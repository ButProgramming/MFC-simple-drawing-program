#include "pch.h"
#include "Lines.h"

set<int> Lines::IDs;
int Lines::countOfLines = 0;


Lines::Lines(int FirstShapeConstID, int SecondShapeConstID, LineType type)
{
	IDs.insert(-1);
	constID = Lines::countOfLines;
	
	bool isFound = false;
	for (int i = 0; i < countOfLines + 10; i++)
	{
		for (auto it = IDs.begin(); it != IDs.end(); it++)
		{
			int empt = IDs.empty();
			CString str;
			str.Format(_T("%d"), empt);

			auto pos = IDs.find(i);
			if (pos == IDs.end())
			{
				isFound = true;
				ID = i;
				IDs.insert(ID);
				break;
			}
		}
		if (isFound)
			break;
	}

	
	this->FirstShapeConstID = FirstShapeConstID;
	this->SecondShapeConstID = SecondShapeConstID;
	this->type = type;
	CString strType;
	if (type == LineType::Basic)
	{
		strType = "Basic";
		name.Format(_T("BasicLine%d"), countOfLines);
	}
	else if (type == LineType::Left)
	{
		strType = "Left";
		name.Format(_T("LeftLine%d"), countOfLines);
	}
	else if (type == LineType::Right)
	{
		strType = "Right";
		name.Format(_T("RightLine%d"), countOfLines);
	}
	else
	{
		strType = "Double";
		name.Format(_T("DoubleLine%d"), countOfLines);
	}
	CString debug;
	debug.Format(_T("First: %d, second %d, line type: %s"), FirstShapeConstID, SecondShapeConstID, strType);
	countOfLines++;
	//AfxMessageBox(debug);
}
