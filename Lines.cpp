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
	countOfLines++;
	//AfxMessageBox(debug);
}
