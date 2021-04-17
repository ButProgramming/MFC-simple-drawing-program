﻿#include "pch.h"
#include "Shape.h"

int IShape::dx = 0;
int IShape::dy = 0;
int IShape::sizeOfPointToMoveAndChange = 3;
int IShape::countOfShape = 0;
set<int> IShape::IDs;
set<CString> IShape::names;


EllipseShape::EllipseShape(CPoint centerOfShape, bool isNormalized, int size, ShapeType type, COLORREF outlineColor, COLORREF fillColor, int outlineSize, int outlineType, int fillType)
{
	this->fillType = fillType;
	this->outlineType = outlineType;
	this->outlineSize = outlineSize;
	this->outlineColor = outlineColor;
	this->fillColor = fillColor;
	IDs.insert(-1);
	constID = IShape::countOfShape;
	bool isNotFound = false;
	for(int i=0; i<countOfShape+10; i++)
	{
		for (auto it = IDs.begin(); it != IDs.end(); it++)
		{
			int empt = IDs.empty();
			CString str;
			str.Format(_T("%d"), empt);
			
			auto pos = IDs.find(i);
			if (pos == IDs.end())
			{
				isNotFound = true;
				ID = i;
				IDs.insert(ID);
				break;
			}
		}
		if (isNotFound)
			break;
	}



	//////////////////////////////////////////////////
	CString str;
	str.Format(_T("-1"));
	names.insert(str);
	isNotFound = false;
	for (int i = 0; i < countOfShape + 10; i++)
	{
		for (auto it = names.begin(); it != names.end(); it++)
		{
			int empt = names.empty();
			//CString name;
			name.Format(_T("ellipseShape%d"), i);

			auto pos = names.find(name);
			if (pos == names.end())
			{
				isNotFound = true;
				name.Format(_T("ellipseShape%d"), i);
				names.insert(name);
				break;
			}
		}
		if (isNotFound)
			break;
	}
	/////////////////////////////////////////////////



	//name.Format(_T("ellipseShape%d"), constID);
	//type = ShapeType::ellipse;
	this->type = type;
	this->size = size;
	this->centerOfShape = centerOfShape;
	boxRect.CenterPoint() = centerOfShape;
	this->isNormalized = isNormalized;
	countOfShape++;
	//this->typeOfShape = typeOfShape;
}

RectangleShape::RectangleShape(CPoint centerOfShape, bool isNormalized, int size, ShapeType type, COLORREF outlineColor, COLORREF fillColor, int outlineSize, int outlineType, int fillType)
{
	this->fillType = fillType;
	this->outlineType = outlineType;
	this->outlineSize = outlineSize;
	this->outlineColor = outlineColor;
	this->fillColor = fillColor;
	IDs.insert(-1);
	constID = IShape::countOfShape;
	bool isNotFound = false;
	for (int i = 0; i < countOfShape + 10; i++)
	{
		for (auto it = IDs.begin(); it != IDs.end(); it++)
		{
			int empt = IDs.empty();
			CString str;
			str.Format(_T("%d"), empt);

			auto pos = IDs.find(i);
			if (pos == IDs.end())
			{
				isNotFound = true;
				ID = i;
				IDs.insert(ID);
				break;
			}
		}
		if (isNotFound)
			break;
	}
	//////////////////////////////////////////////////
	CString str;
	str.Format(_T("-1"));
	names.insert(str);
	isNotFound = false;
	for (int i = 0; i < countOfShape + 10; i++)
	{
		for (auto it = names.begin(); it != names.end(); it++)
		{
			int empt = names.empty();
			//CString name;
			name.Format(_T("rectangleShape%d"), i);

			auto pos = names.find(name);
			if (pos == names.end())
			{
				isNotFound = true;
				name.Format(_T("rectangleShape%d"), i);
				names.insert(name);
				break;
			}
		}
		if (isNotFound)
			break;
	}
	/////////////////////////////////////////////////


	//name.Format(_T("rectangleShape%d"), constID);
	//type = ShapeType::rectangle;
	this->type = type;
	this->size = size;
	this->centerOfShape = centerOfShape;
	this->isNormalized = isNormalized;
	countOfShape++;
	//this->typeOfShape = typeOfShape;
}

TriangleShape::TriangleShape(CPoint centerOfShape, bool isNormalized, int size, ShapeType type, COLORREF outlineColor, COLORREF fillColor, int outlineSize, int outlineType, int fillType)
{
	this->fillType = fillType;
	this->outlineType = outlineType;
	this->outlineSize = outlineSize;
	this->outlineColor = outlineColor;
	this->fillColor = fillColor;
	IDs.insert(-1);
	constID = IShape::countOfShape;
	bool isNotFound = false;
	for (int i = 0; i < countOfShape + 10; i++)
	{
		for (auto it = IDs.begin(); it != IDs.end(); it++)
		{
			int empt = IDs.empty();
			CString str;
			str.Format(_T("%d"), empt);

			auto pos = IDs.find(i);
			if (pos == IDs.end())
			{
				isNotFound = true;
				ID = i;
				IDs.insert(ID);
				break;
			}
		}
		if (isNotFound)
			break;
	}
	//////////////////////////////////////////////////
	CString str;
	str.Format(_T("-1"));
	names.insert(str);
	isNotFound = false;
	for (int i = 0; i < countOfShape + 10; i++)
	{
		for (auto it = names.begin(); it != names.end(); it++)
		{
			int empt = names.empty();
			//CString name;
			name.Format(_T("triangleShape%d"), i);

			auto pos = names.find(name);
			if (pos == names.end())
			{
				isNotFound = true;
				name.Format(_T("triangleShape%d"), i);
				names.insert(name);
				break;
			}
		}
		if (isNotFound)
			break;
	}
	/////////////////////////////////////////////////
	//name.Format(_T("triangleShape%d"), constID);
	this->type = type;
	this->size = size;
	this->centerOfShape = centerOfShape;
	this->isNormalized = isNormalized;
	countOfShape++;
	//this->typeOfShape = typeOfShape;
}

void EllipseShape::draw(CDC* dc)
{
	
	//size = 100;
	oR = GetRValue(outlineColor);
	oG = GetGValue(outlineColor);
	oB = GetBValue(outlineColor);

	fR = GetRValue(fillColor);
	fG = GetGValue(fillColor);
	fB = GetBValue(fillColor);

	if (!isSelectedFromDoubleSelectingTool)
		pen = new CPen(outlineType, outlineSize, RGB(oR, oG, oB));
	/*else if (isSelected)
		pen = new CPen(PS_SOLID, 4, RGB(0, 0, 0));*/
	else
		pen = new CPen(PS_SOLID, 4, RGB(100, 100, 100));
	dc->SelectObject(pen);
	CPoint circleCenter{ 0, 0 };

	CPoint diffAr[4];
	for (int i = 0; i < 4; i++)
	{
		diffAr[i] = CPoint(dx_dy[i].x + dx_dy_temp[i].x, dx_dy[i].y + dx_dy_temp[i].y);
	}

	points[0] = CPoint(dSM.x + circleCenter.x - size + diffAr[0].x + diffAr[3].x - (diffAr[1].x + diffAr[2].x), dSM.y + circleCenter.y + size + diffAr[0].y + diffAr[1].y - (diffAr[2].y + diffAr[3].y)); //leftbottom
	points[1] = CPoint(dSM.x + circleCenter.x + size + diffAr[1].x + diffAr[2].x - (diffAr[0].x + diffAr[3].x), dSM.y + circleCenter.y + size + diffAr[0].y + diffAr[1].y - (diffAr[2].y + diffAr[3].y)); //rightbottom
	points[2] = CPoint(dSM.x + circleCenter.x + size + diffAr[1].x + diffAr[2].x - (diffAr[0].x + diffAr[3].x), dSM.y + circleCenter.y - size + diffAr[2].y + diffAr[3].y - (diffAr[0].y + diffAr[1].y)); //righttop
	points[3] = CPoint(dSM.x + circleCenter.x - size + diffAr[0].x + diffAr[3].x - (diffAr[1].x + diffAr[2].x), dSM.y + circleCenter.y - size + diffAr[2].y + diffAr[3].y - (diffAr[0].y + diffAr[1].y)); //lefttop


	int a = abs((points[1].x - points[0].x) / 2);
	int b = abs((points[2].y - points[1].y) / 2);

	//vector<CPoint> eFP;
	eFP.clear();
	dc->MoveTo(circleCenter.x, circleCenter.y + b);
	for (int y = b - 1; y >= -b; y--)
	{
		double temp = sqrt((1 - (double)y / (double)b) * (1 + (double)y / (double)b));
		int x = a * temp;
		//dc->LineTo(circleCenter.x - x, circleCenter.y + y);
		CPoint temp1{ dSM.x + circleCenter.x - x,dSM.y + circleCenter.y + y };
		eFP.push_back(temp1);
		dc->MoveTo(dSM.x + circleCenter.x - x, dSM.y + circleCenter.y + y);
	}
	CPoint temp1{ dSM.x + circleCenter.x, dSM.y + circleCenter.y + b };
	eFP.push_back(temp1);
	//

	//
	eSP.clear();
	//vector<CPoint> eSP;
	dc->MoveTo(dSM.x + circleCenter.x, dSM.y + circleCenter.y + b);
	for (int y = b - 1; y >= -b; y--)
	{
		double temp = sqrt((1 - (double)y / (double)b) * (1 + (double)y / (double)b));
		int x = a * temp;
		//dc->LineTo(circleCenter.x + x, circleCenter.y + y);
		CPoint temp2{ dSM.x + circleCenter.x + x, dSM.y + circleCenter.y + y };
		eSP.push_back(temp2);
		dc->MoveTo(dSM.x + circleCenter.x + x, dSM.y + circleCenter.y + y);
	}
	CPoint temp2{ dSM.x + circleCenter.x,dSM.y + circleCenter.y + b };
	eSP.push_back(temp2);

	dc->MoveTo(circleCenter.x, circleCenter.y + b);

	ellipseFirstPart.clear();
	ellipseSecondPart.clear();
	for (CPoint v1 : eFP)
	{
		ellipseFirstPart.push_back(v1);
	}
	for (CPoint v2 : eSP)
	{
		ellipseSecondPart.push_back(v2);
	}

	CBrush* ellipseBrush = NULL;
	if (fillType == -1)
	{
		ellipseBrush = new CBrush;
		ellipseBrush->CreateSolidBrush(RGB(fR, fG, fB));
	}
	else
	{
		ellipseBrush = new CBrush(fillType, RGB(fR, fG, fB));
	}

	for (int i = 0; i < eFP.size(); i++)
	{
		int tempX = eFP[i].x;
		int tempY = eFP[i].y;
		eFP[i].x = round(tempX * cos(ellipseAngleRad) - tempY * sin(ellipseAngleRad));
		eFP[i].y = round(tempX * sin(ellipseAngleRad) + tempY * cos(ellipseAngleRad));
		eFP[i].x += centerOfShape.x + dx;
		eFP[i].y += centerOfShape.y + dy;
	}

	for (int i = 0; i < eSP.size(); i++)
	{
		int tempX = eSP[i].x;
		int tempY = eSP[i].y;
		eSP[i].x = round(tempX * cos(ellipseAngleRad) - tempY * sin(ellipseAngleRad));
		eSP[i].y = round(tempX * sin(ellipseAngleRad) + tempY * cos(ellipseAngleRad));
		eSP[i].x += centerOfShape.x + dx;
		eSP[i].y += centerOfShape.y + dy;
	}

	for (int i = 0; i < 4; i++)
	{
		int tempX = points[i].x;
		int tempY = points[i].y;
		points[i].x = round(tempX * cos(ellipseAngleRad) - tempY * sin(ellipseAngleRad));
		points[i].y = round(tempX * sin(ellipseAngleRad) + tempY * cos(ellipseAngleRad));
		points[i].x += centerOfShape.x + dx;
		points[i].y += centerOfShape.y + dy;
	}

	// create smaller ellipse to fill region
	a = a - 1;
	b = b - 1;
	///
	vector<CPoint> smallerRgn1;
	dc->MoveTo(circleCenter.x, circleCenter.y + b);
	for (int y = b - 1; y >= -b; y--)
	{
		double temp = sqrt((1 - (double)y / (double)b) * (1 + (double)y / (double)b));
		int x = a * temp;
		//dc->LineTo(circleCenter.x - x, circleCenter.y + y);
		CPoint temp1{ dSM.x + circleCenter.x - x,dSM.y + circleCenter.y + y };
		smallerRgn1.push_back(temp1);
		dc->MoveTo(dSM.x + circleCenter.x - x, dSM.y + circleCenter.y + y);
	}
	CPoint temp1_2{ dSM.x + circleCenter.x, dSM.y + circleCenter.y + b };
	smallerRgn1.push_back(temp1);
	//

	//
	vector<CPoint> smallerRgn2;
	//vector<CPoint> eSP;
	dc->MoveTo(dSM.x + circleCenter.x, dSM.y + circleCenter.y + b);
	for (int y = b - 1; y >= -b; y--)
	{
		double temp = sqrt((1 - (double)y / (double)b) * (1 + (double)y / (double)b));
		int x = a * temp;
		//dc->LineTo(circleCenter.x + x, circleCenter.y + y);
		CPoint temp2{ dSM.x + circleCenter.x + x, dSM.y + circleCenter.y + y };
		smallerRgn2.push_back(temp2);
		dc->MoveTo(dSM.x + circleCenter.x + x, dSM.y + circleCenter.y + y);
	}
	CPoint temp2_2{ dSM.x + circleCenter.x,dSM.y + circleCenter.y + b };
	smallerRgn2.push_back(temp2);

	dc->MoveTo(circleCenter.x, circleCenter.y + b);

	ellipseFirstPart.clear();
	ellipseSecondPart.clear();
	for (CPoint v1 : smallerRgn1)
	{
		ellipseFirstPart.push_back(v1);
	}
	for (CPoint v2 : smallerRgn2)
	{
		ellipseSecondPart.push_back(v2);
	}

	for (int i = 0; i < smallerRgn1.size(); i++)
	{
		int tempX = smallerRgn1[i].x;
		int tempY = smallerRgn1[i].y;
		smallerRgn1[i].x = round(tempX * cos(ellipseAngleRad) - tempY * sin(ellipseAngleRad));
		smallerRgn1[i].y = round(tempX * sin(ellipseAngleRad) + tempY * cos(ellipseAngleRad));
		smallerRgn1[i].x += centerOfShape.x + dx;
		smallerRgn1[i].y += centerOfShape.y + dy;
	}

	for (int i = 0; i < smallerRgn2.size(); i++)
	{
		int tempX = smallerRgn2[i].x;
		int tempY = smallerRgn2[i].y;
		smallerRgn2[i].x = round(tempX * cos(ellipseAngleRad) - tempY * sin(ellipseAngleRad));
		smallerRgn2[i].y = round(tempX * sin(ellipseAngleRad) + tempY * cos(ellipseAngleRad));
		smallerRgn2[i].x += centerOfShape.x + dx;
		smallerRgn2[i].y += centerOfShape.y + dy;
	}

	CRgn* ellipseRgn1 = new CRgn;
	ellipseRgn1->CreatePolygonRgn(&smallerRgn1[0], smallerRgn1.size(), ALTERNATE);
	CRgn* ellipseRgn2 = new CRgn;
	ellipseRgn2->CreatePolygonRgn(&smallerRgn2[0], smallerRgn2.size(), ALTERNATE);

	if (isSelected)
	{
		CPen* tempPen = new CPen(1, 1, RGB(100,100,100));
		dc->SelectObject(tempPen);
		// draw rectangle that demonstrate selecting shape
		for (int pointNum = 0; pointNum < 4; pointNum++)
		{
			if (pointNum == 3)
			{
				dc->MoveTo(points[3]);
				dc->LineTo(points[0]);
				break;
			}
			dc->MoveTo(points[pointNum]);
			dc->LineTo(points[pointNum+1]);
			
		}
		
		tempPen->DeleteObject();
	}
	
	dc->SelectObject(pen);
	dc->Polygon(&eFP[0], eFP.size());
	dc->Polygon(&eSP[0], eSP.size());
	dc->FillRgn(ellipseRgn1, ellipseBrush);
	dc->FillRgn(ellipseRgn2, ellipseBrush);


	if (isSelected)
	{
		//dc->Ellipse(0, 0, 200, 200);
		for (int i = 0; i < 4; i++)
			dc->Ellipse(points[i].x - sizeOfPointToMoveAndChange, points[i].y - sizeOfPointToMoveAndChange, points[i].x + sizeOfPointToMoveAndChange, points[i].y + sizeOfPointToMoveAndChange);
	}

	ellipseRgn1->DeleteObject();
	ellipseRgn2->DeleteObject();
	pen->DeleteObject();
	ellipseBrush->DeleteObject();
}


void RectangleShape::draw(CDC* dc)
{
	oR = GetRValue(outlineColor);
	oG = GetGValue(outlineColor);
	oB = GetBValue(outlineColor);

	fR = GetRValue(fillColor);
	fG = GetGValue(fillColor);
	fB = GetBValue(fillColor);

	if (!isSelected && !isSelectedFromDoubleSelectingTool)
		pen = new CPen(outlineType, outlineSize, RGB(oR, oG, oB));
	else if (isSelected)
		pen = new CPen(PS_SOLID, 4, RGB(0, 0, 0));
	else
		pen = new CPen(PS_SOLID, 4, RGB(100, 100, 100));
	dc->SelectObject(pen);
	// synchronized moving
	//dc->Rectangle(centerOfShape.x + dx - size, centerOfShape.y + dy - size, centerOfShape.x + dx + size, centerOfShape.y + dy + size);
	CPoint rectangleCenter{ 0, 0 };

	CPoint diffAr[4];
	for (int i = 0; i < 4; i++)
	{
		diffAr[i] = CPoint(dx_dy[i].x + dx_dy_temp[i].x, dx_dy[i].y + dx_dy_temp[i].y);
	}


	//for (int i = 0; i < 4; i++)
	//{
	//	if (diffAr[i] != CPoint(0, 0) || ellipseAngleRad!=0)
	//	{
	//		isNormalized = false;

	//	}
	//}

	points[0] = CPoint(dSM.x + rectangleCenter.x - size + diffAr[0].x + diffAr[3].x - (diffAr[1].x + diffAr[2].x), dSM.y + rectangleCenter.y + size + diffAr[0].y + diffAr[1].y - (diffAr[2].y + diffAr[3].y)); //leftbottom
	points[1] = CPoint(dSM.x + rectangleCenter.x + size + diffAr[1].x + diffAr[2].x - (diffAr[0].x + diffAr[3].x), dSM.y + rectangleCenter.y + size + diffAr[0].y + diffAr[1].y - (diffAr[2].y + diffAr[3].y)); //rightbottom
	points[2] = CPoint(dSM.x + rectangleCenter.x + size + diffAr[1].x + diffAr[2].x - (diffAr[0].x + diffAr[3].x), dSM.y + rectangleCenter.y - size + diffAr[2].y + diffAr[3].y - (diffAr[0].y + diffAr[1].y)); //righttop
	points[3] = CPoint(dSM.x + rectangleCenter.x - size + diffAr[0].x + diffAr[3].x - (diffAr[1].x + diffAr[2].x), dSM.y + rectangleCenter.y - size + diffAr[2].y + diffAr[3].y - (diffAr[0].y + diffAr[1].y)); //lefttop
	//CRgn* rectangleReg = new CRgn;

	//create new smaller region
	CPoint pointsReg[4];
	pointsReg[0].x = points[0].x + 1; //bl
	pointsReg[0].y = points[0].y - 1;

	pointsReg[1].x = points[1].x - 1; //br
	pointsReg[1].y = points[1].y - 1;

	pointsReg[2].x = points[2].x - 1; //tr
	pointsReg[2].y = points[2].y + 1;

	pointsReg[3].x = points[3].x + 1; //tl
	pointsReg[3].y = points[3].y + 1;

	// rotate shape
	for (int i = 0; i < 4; i++)
	{
		int tempX = points[i].x;
		int tempY = points[i].y;
		points[i].x = round(tempX * cos(ellipseAngleRad) - tempY * sin(ellipseAngleRad));
		points[i].y = round(tempX * sin(ellipseAngleRad) + tempY * cos(ellipseAngleRad));
		points[i].x += centerOfShape.x + dx;
		points[i].y += centerOfShape.y + dy;
	}

	//rotate shape region points
	for (int i = 0; i < 4; i++)
	{
		int tempX = pointsReg[i].x;
		int tempY = pointsReg[i].y;
		pointsReg[i].x = round(tempX * cos(ellipseAngleRad) - tempY * sin(ellipseAngleRad));
		pointsReg[i].y = round(tempX * sin(ellipseAngleRad) + tempY * cos(ellipseAngleRad));
		pointsReg[i].x += centerOfShape.x + dx;
		pointsReg[i].y += centerOfShape.y + dy;
	}

	//rectangleReg->CreatePolygonRgn(points, 4, ALTERNATE);
	//GetRgnBox(*rectangleReg, boxRect);
	//dc->Rectangle(boxRect);
	if (isSelected)
	{
		//dc->Ellipse(0, 0, 200, 200);
		for (int i = 0; i < 4; i++)
			dc->Ellipse(points[i].x - sizeOfPointToMoveAndChange, points[i].y - sizeOfPointToMoveAndChange, points[i].x + sizeOfPointToMoveAndChange, points[i].y + sizeOfPointToMoveAndChange);
	}
	CBrush* rectangleBrush;
	if (fillType == -1)
	{
		rectangleBrush = new CBrush;
		rectangleBrush->CreateSolidBrush(RGB(fR, fG, fB));
	}
	else
	{
		rectangleBrush = new CBrush(fillType, RGB(fR, fG, fB));
	}
	
	

	CRgn* rectangleReg = new CRgn;
	rectangleReg->CreatePolygonRgn(pointsReg, 4, ALTERNATE);
	dc->Polygon(points, 4);
	dc->FillRgn(rectangleReg, rectangleBrush);
	//dc->FillRgn(triangleReg, brush);
	/*delete pen;
	delete rectangleBrush;
	//delete rectangleReg;*/
	pen->DeleteObject();
	rectangleBrush->DeleteObject();
	rectangleReg->DeleteObject();

}

void TriangleShape::draw(CDC* dc)
{
	//auto pDoc = GetDocument();
	oR = GetRValue(outlineColor);
	oG = GetGValue(outlineColor);
	oB = GetBValue(outlineColor);

	fR = GetRValue(fillColor);
	fG = GetGValue(fillColor);
	fB = GetBValue(fillColor);

	if (!isSelected && !isSelectedFromDoubleSelectingTool)
		pen = new CPen(outlineType, outlineSize, RGB(oR, oG, oB));
	else if (isSelected)
		pen = new CPen(PS_SOLID, 4, RGB(0, 0, 0));
	else
		pen = new CPen(PS_SOLID, 4, RGB(100, 100, 100));
	dc->SelectObject(pen);
	CPoint rectangleCenter{ 0, 0 };
	CPoint diffAr[4];
	for (int i = 0; i < 4; i++)
	{
		diffAr[i] = CPoint(dx_dy[i].x + dx_dy_temp[i].x, dx_dy[i].y + dx_dy_temp[i].y);
	}
	points[0] = CPoint(dSM.x + rectangleCenter.x - 2 * sqrt(3) / 3 * size + diffAr[0].x + diffAr[3].x - (diffAr[1].x + diffAr[2].x), dSM.y + rectangleCenter.y + size + diffAr[0].y + diffAr[1].y - (diffAr[2].y + diffAr[3].y)); //leftbottom
	points[1] = CPoint(dSM.x + rectangleCenter.x + 2 * sqrt(3) / 3 * size + diffAr[1].x + diffAr[2].x - (diffAr[0].x + diffAr[3].x), dSM.y + rectangleCenter.y + size + diffAr[0].y + diffAr[1].y - (diffAr[2].y + diffAr[3].y)); //rightbottom
	points[2] = CPoint(dSM.x + rectangleCenter.x + 2 * sqrt(3) / 3 * size + diffAr[1].x + diffAr[2].x - (diffAr[0].x + diffAr[3].x), dSM.y + rectangleCenter.y - size + diffAr[2].y + diffAr[3].y - (diffAr[0].y + diffAr[1].y)); //righttop
	points[3] = CPoint(dSM.x + rectangleCenter.x - 2 * sqrt(3) / 3 * size + diffAr[0].x + diffAr[3].x - (diffAr[1].x + diffAr[2].x), dSM.y + rectangleCenter.y - size + diffAr[2].y + diffAr[3].y - (diffAr[0].y + diffAr[1].y)); //lefttop

	CPoint triangle[4];
	triangle[0] = CPoint(points[3].x + (points[2].x - points[3].x) / 2, points[3].y + (points[2].y - points[3].y) / 2); //top
	triangle[1] = points[0]; // left
	triangle[2] = points[1]; // right

	// create smaller triangle for smaller region
	CPoint trianglePointsRgn[3];
	trianglePointsRgn[0].x = triangle[0].x;
	trianglePointsRgn[0].y = triangle[0].y + 1;

	trianglePointsRgn[1].x = triangle[1].x + 1;
	trianglePointsRgn[1].y = triangle[1].y - 1;

	trianglePointsRgn[2].x = triangle[2].x - 1;
	trianglePointsRgn[2].y = triangle[2].y - 1;

	CRgn* triangleRgn = new CRgn;
	triangleRgn->CreatePolygonRgn(points, 4, ALTERNATE);
	GetRgnBox(*triangleRgn, boxRect);

	recFromRgn[0] = CPoint(boxRect.TopLeft().x, boxRect.BottomRight().y);
	recFromRgn[1] = CPoint(boxRect.BottomRight());
	recFromRgn[2] = CPoint(boxRect.BottomRight().x, boxRect.TopLeft().y);
	recFromRgn[3] = CPoint(boxRect.TopLeft());



	for (int i = 0; i < 4; i++)
	{
		int tempX = points[i].x;
		int tempY = points[i].y;
		points[i].x = round(tempX * cos(ellipseAngleRad) - tempY * sin(ellipseAngleRad));
		points[i].y = round(tempX * sin(ellipseAngleRad) + tempY * cos(ellipseAngleRad));
		points[i].x += centerOfShape.x + dx;
		points[i].y += centerOfShape.y + dy;


		tempX = recFromRgn[i].x;
		tempY = recFromRgn[i].y;
		recFromRgn[i].x = round(tempX * cos(ellipseAngleRad) - tempY * sin(ellipseAngleRad));
		recFromRgn[i].y = round(tempX * sin(ellipseAngleRad) + tempY * cos(ellipseAngleRad));
		recFromRgn[i].x += centerOfShape.x + dx;
		recFromRgn[i].y += centerOfShape.y + dy;
	}


	for (int i = 0; i < 3; i++)
	{
		int tempX = triangle[i].x;
		int tempY = triangle[i].y;
		triangle[i].x = round(tempX * cos(ellipseAngleRad) - tempY * sin(ellipseAngleRad));
		triangle[i].y = round(tempX * sin(ellipseAngleRad) + tempY * cos(ellipseAngleRad));
		triangle[i].x += centerOfShape.x + dx;
		triangle[i].y += centerOfShape.y + dy;
	}

	for (int i = 0; i < 3; i++)
	{
		int tempX = trianglePointsRgn[i].x;
		int tempY = trianglePointsRgn[i].y;
		trianglePointsRgn[i].x = round(tempX * cos(ellipseAngleRad) - tempY * sin(ellipseAngleRad));
		trianglePointsRgn[i].y = round(tempX * sin(ellipseAngleRad) + tempY * cos(ellipseAngleRad));
		trianglePointsRgn[i].x += centerOfShape.x + dx;
		trianglePointsRgn[i].y += centerOfShape.y + dy;
	}

	//rectangleReg->CreatePolygonRgn(points, 4, ALTERNATE);
	//GetRgnBox(*rectangleReg, boxRect);
	//dc->Rectangle(boxRect);

	points[0] = triangle[1];
	points[1] = triangle[2];
	points[2] = triangle[0];
	if (isSelected)
	{
		//dc->Ellipse(0, 0, 200, 200);
		for (int i = 0; i < 3; i++)
			dc->Ellipse(points[i].x - sizeOfPointToMoveAndChange, points[i].y - sizeOfPointToMoveAndChange, points[i].x + sizeOfPointToMoveAndChange, points[i].y + sizeOfPointToMoveAndChange);
	}
	CRgn* triangleNewRgn = new CRgn;
	triangleNewRgn->CreatePolygonRgn(trianglePointsRgn, 3, ALTERNATE);
	CBrush* triangleBrush;
	if (fillType == -1)
	{
		triangleBrush = new CBrush;
		triangleBrush->CreateSolidBrush(RGB(fR, fG, fB));
	}
	else
	{
		triangleBrush = new CBrush(fillType, RGB(fR, fG, fB));
	}
	//CBrush* triangleBrush = new CBrush;
	//triangleBrush->CreateSolidBrush(RGB(fR, fG, fB)); // Microsoft C++ exception: CResourceException at memory location 0x0098F310
	//triangleBrush->CreateSolidBrush(HS_DIAGCROSS);
	//dc->Polygon(recFromRgn, 4);

	//dc->Polygon(points, 4);
	dc->Polygon(triangle, 3);
	dc->FillRgn(triangleNewRgn, triangleBrush);
	/*delete triangleNewRgn;
	delete triangleBrush;
	delete triangleRgn;
	delete pen;*/
	pen->DeleteObject();
	triangleRgn->DeleteObject();
	triangleBrush->DeleteObject();
	triangleNewRgn->DeleteObject();
}


IShape::~IShape()
{
	IShape::IDs.erase(ID); // erase ID because ID won't exist
	IShape::names.erase(name);
}


