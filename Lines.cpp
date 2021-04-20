#include "pch.h"
#include "Lines.h"

set<int> Lines::IDs;
set<CString> Lines::names;
int Lines::countOfLines = 0;

void Lines::draw(CDC* dc)
{
	// draw line
	//dc->MoveTo(firstPoint);
	//dc->LineTo(secondPoint);
	//AfxMessageBox(_T("here"));

}

Lines::Lines(CPoint firstPoint, LineType type, COLORREF lineColor, int lineSize, int lineType)
{
	
	
	//this -> lineSize = lineSize;
	//this->lineColor = lineColor;
	//lR = GetRValue(lineColor);
	//lG = GetGValue(lineColor);
	//lB = GetBValue(lineColor);
	//this->lineType = lineType;
	//IDs.insert(-1);

	//constID = Lines::countOfLines;
	//
	//bool isNotFound = false;
	//for (int i = 0; i < countOfLines + 10; i++)
	//{
	//	for (auto it = IDs.begin(); it != IDs.end(); it++)
	//	{
	//		int empt = IDs.empty();
	//		CString str;
	//		str.Format(_T("%d"), empt);

	//		auto pos = IDs.find(i);
	//		if (pos == IDs.end())
	//		{
	//			isNotFound = true;
	//			ID = i;
	//			IDs.insert(ID);
	//			break;
	//		}
	//	}
	//	if (isNotFound)
	//		break;
	//}
	////////////////////////////////////////////////////
	//CString str;
	//str.Format(_T("-1"));
	//names.insert(str);
	//isNotFound = false;
	//for (int i = 0; i < countOfLines + 10; i++)
	//{
	//	for (auto it = names.begin(); it != names.end(); it++)
	//	{
	//		int empt = names.empty();
	//		//CString name;



	//		if (type == LineType::Basic)
	//		{

	//			name.Format(_T("BasicLine%d"), i);
	//		}
	//		else if (type == LineType::Left)
	//		{

	//			name.Format(_T("LeftLine%d"), i);
	//		}
	//		else if (type == LineType::Right)
	//		{

	//			name.Format(_T("RightLine%d"), i);
	//		}
	//		else
	//		{

	//			name.Format(_T("DoubleLine%d"), i);
	//		}


	//		//name.Format(_T("triangleShape%d"), i);

	//		auto pos = names.find(name);
	//		if (pos == names.end())
	//		{
	//			isNotFound = true;
	//			CString strType;
	//			if (type == LineType::Basic)
	//			{
	//				strType = "Basic";
	//				name.Format(_T("BasicLine%d"), i);
	//			}
	//			else if (type == LineType::Left)
	//			{
	//				strType = "Left";
	//				name.Format(_T("LeftLine%d"), i);
	//			}
	//			else if (type == LineType::Right)
	//			{
	//				strType = "Right";
	//				name.Format(_T("RightLine%d"), i);
	//			}
	//			else
	//			{
	//				strType = "Double";
	//				name.Format(_T("DoubleLine%d"), i);
	//			}
	//			names.insert(name);
	//			break;
	//		}
	//	}
	//	if (isNotFound)
	//		break;
	//}
	///////////////////////////////////////////////////
	//
	//this->FirstShapeConstID = FirstShapeConstID;
	//this->SecondShapeConstID = SecondShapeConstID;
	//this->type = type;
	//
	//CString debug;
	//debug.Format(_T("firstPoint x: %d, secondPoint y"), firstPoint.x, secondPoint.y);
	//countOfLines++;
	//AfxMessageBox(debug);
}

Lines::~Lines()
{
	Lines::IDs.erase(ID);
	Lines::names.erase(name);
}
