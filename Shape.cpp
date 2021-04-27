﻿#include "pch.h"
#include "Shape.h"

int IShape::dx = 0;
int IShape::dy = 0;
int IShape::sizeOfPointToMoveAndChange = 3;
int IShape::countOfShape = 0;
set<int> IShape::IDs;
set<CString> IShape::names;
//CPoint IShape::firstPoint{ 0, 0 };



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
	//this->isNormalized = isNormalized;
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
	//this->isNormalized = isNormalized;
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
	//this->isNormalized = isNormalized;
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

	array<CPoint, 4> diffAr;
	for (int i = 0; i < 4; i++)
	{
		//diffAr[i] = CPoint(dx_dy[i].x + dx_dy_temp[i].x, dx_dy[i].y + dx_dy_temp[i].y);
		diffAr[i] = change.dxDy[i] + change.tempDxDy[i];
	}

	selectedAreaPoints[0] = CPoint(shapeMove.tempDxDy.x + circleCenter.x - size + diffAr[0].x + diffAr[3].x - (diffAr[1].x + diffAr[2].x), shapeMove.tempDxDy.y + circleCenter.y + size + diffAr[0].y + diffAr[1].y - (diffAr[2].y + diffAr[3].y)); //leftbottom
	selectedAreaPoints[1] = CPoint(shapeMove.tempDxDy.x + circleCenter.x + size + diffAr[1].x + diffAr[2].x - (diffAr[0].x + diffAr[3].x), shapeMove.tempDxDy.y + circleCenter.y + size + diffAr[0].y + diffAr[1].y - (diffAr[2].y + diffAr[3].y)); //rightbottom
	selectedAreaPoints[2] = CPoint(shapeMove.tempDxDy.x + circleCenter.x + size + diffAr[1].x + diffAr[2].x - (diffAr[0].x + diffAr[3].x), shapeMove.tempDxDy.y + circleCenter.y - size + diffAr[2].y + diffAr[3].y - (diffAr[0].y + diffAr[1].y)); //righttop
	selectedAreaPoints[3] = CPoint(shapeMove.tempDxDy.x + circleCenter.x - size + diffAr[0].x + diffAr[3].x - (diffAr[1].x + diffAr[2].x), shapeMove.tempDxDy.y + circleCenter.y - size + diffAr[2].y + diffAr[3].y - (diffAr[0].y + diffAr[1].y)); //lefttop

	
	//cout << points[0].y << " " << points[3].y << endl;
	// calculate coordinates for points, that are needed to draw links (lines)
	linkingPoints[0] = CPoint((selectedAreaPoints[1].x - selectedAreaPoints[0].x) / 2 + selectedAreaPoints[0].x, selectedAreaPoints[0].y);
	linkingPoints[1] = CPoint(selectedAreaPoints[1].x, (selectedAreaPoints[1].y + selectedAreaPoints[2].y) / 2);
	linkingPoints[2] = CPoint((selectedAreaPoints[2].x - selectedAreaPoints[3].x) / 2 + selectedAreaPoints[3].x, selectedAreaPoints[2].y);
	linkingPoints[3] = CPoint(selectedAreaPoints[3].x, (selectedAreaPoints[0].y + selectedAreaPoints[3].y) / 2);

	// points that needed for drawing rotate tool
	centerPoint23Bottom = CPoint((selectedAreaPoints[2].x - selectedAreaPoints[3].x) / 2 + selectedAreaPoints[3].x, selectedAreaPoints[2].y);
	if (selectedAreaPoints[0].y >= selectedAreaPoints[3].y)
	{
		centerPoint23Top = CPoint(centerPoint23Bottom.x, centerPoint23Bottom.y - 40);
		isReversedVar = false;
	}
	else
	{
		centerPoint23Top = CPoint(centerPoint23Bottom.x, centerPoint23Bottom.y + 40);
		isReversedVar = true;
	}
	firstPoint = centerPoint23Top;
	

	int a = abs((selectedAreaPoints[1].x - selectedAreaPoints[0].x) / 2);
	int b = abs((selectedAreaPoints[2].y - selectedAreaPoints[1].y) / 2);

	//vector<CPoint> eFP;
	eFP.clear();
	dc->MoveTo(circleCenter.x, circleCenter.y + b);
	for (int y = b - 1; y >= -b; y--)
	{
		double temp = sqrt((1 - (double)y / (double)b) * (1 + (double)y / (double)b));
		int x = a * temp;
		//dc->LineTo(circleCenter.x - x, circleCenter.y + y);
		CPoint temp1{ shapeMove.tempDxDy.x + circleCenter.x - x,shapeMove.tempDxDy.y + circleCenter.y + y };
		eFP.push_back(temp1);
		dc->MoveTo(shapeMove.tempDxDy.x + circleCenter.x - x, shapeMove.tempDxDy.y + circleCenter.y + y);
	}
	CPoint temp1{ shapeMove.tempDxDy.x + circleCenter.x, shapeMove.tempDxDy.y + circleCenter.y + b };
	eFP.push_back(temp1);
	//

	//
	eSP.clear();
	//vector<CPoint> eSP;
	dc->MoveTo(shapeMove.tempDxDy.x + circleCenter.x, shapeMove.tempDxDy.y + circleCenter.y + b);
	for (int y = b - 1; y >= -b; y--)
	{
		double temp = sqrt((1 - (double)y / (double)b) * (1 + (double)y / (double)b));
		int x = a * temp;
		//dc->LineTo(circleCenter.x + x, circleCenter.y + y);
		CPoint temp2{ shapeMove.tempDxDy.x + circleCenter.x + x, shapeMove.tempDxDy.y + circleCenter.y + y };
		eSP.push_back(temp2);
		dc->MoveTo(shapeMove.tempDxDy.x + circleCenter.x + x, shapeMove.tempDxDy.y + circleCenter.y + y);
	}
	CPoint temp2{ shapeMove.tempDxDy.x + circleCenter.x,shapeMove.tempDxDy.y + circleCenter.y + b };
	eSP.push_back(temp2);

	dc->MoveTo(circleCenter.x, circleCenter.y + b);

	ellipseFirstPart.clear();
	ellipseSecondPart.clear();

	shapePoints.clear();
	for (CPoint v1 : eFP)
	{
		ellipseFirstPart.push_back(v1);
		shapePoints.push_back(v1);
	}
	for (CPoint v2 : eSP)
	{
		ellipseSecondPart.push_back(v2);
		shapePoints.push_back(v2);
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

	for (int i = 0; i < shapePoints.size(); i++)
	{
		int tempX = shapePoints[i].x;
		int tempY = shapePoints[i].y;
		shapePoints[i].x = round(tempX * cos(ellipseAngleRad) - tempY * sin(ellipseAngleRad));
		shapePoints[i].y = round(tempX * sin(ellipseAngleRad) + tempY * cos(ellipseAngleRad));
		shapePoints[i].x += centerOfShape.x + dx;
		shapePoints[i].y += centerOfShape.y + dy;
	}


	for (int i = 0; i < 4; i++)
	{
		int tempX = selectedAreaPoints[i].x;
		int tempY = selectedAreaPoints[i].y;
		selectedAreaPoints[i].x = round(tempX * cos(ellipseAngleRad) - tempY * sin(ellipseAngleRad));
		selectedAreaPoints[i].y = round(tempX * sin(ellipseAngleRad) + tempY * cos(ellipseAngleRad));
		selectedAreaPoints[i].x += centerOfShape.x + dx;
		selectedAreaPoints[i].y += centerOfShape.y + dy;
	}

	int tempXBottom = centerPoint23Bottom.x;
	int tempYBottom = centerPoint23Bottom.y;
	centerPoint23Bottom.x = round(tempXBottom * cos(ellipseAngleRad) - tempYBottom * sin(ellipseAngleRad));
	centerPoint23Bottom.y = round(tempXBottom * sin(ellipseAngleRad) + tempYBottom * cos(ellipseAngleRad));
	centerPoint23Bottom.x += centerOfShape.x + dx;
	centerPoint23Bottom.y += centerOfShape.y + dy;

	int tempXTop = centerPoint23Top.x;
	int tempYTop = centerPoint23Top.y;
	centerPoint23Top.x = round(tempXTop * cos(ellipseAngleRad) - tempYTop * sin(ellipseAngleRad));
	centerPoint23Top.y = round(tempXTop * sin(ellipseAngleRad) + tempYTop * cos(ellipseAngleRad));
	centerPoint23Top.x += centerOfShape.x + dx;
	centerPoint23Top.y += centerOfShape.y + dy;

	int tempXFP = firstPoint.x;
	int tempYFP = firstPoint.y;
	firstPoint.x = round(tempXTop * 1 - tempYTop * 0);
	firstPoint.y = round(tempXTop * 0 + tempYTop * 1);
	firstPoint.x += centerOfShape.x + dx;
	firstPoint.y += centerOfShape.y + dy;
	
	// move and rotate points for lines
	for (int numPoint = 0; numPoint < linkingPoints.size(); numPoint++)
	{
		int tempX = linkingPoints[numPoint].x;
		int tempY = linkingPoints[numPoint].y;
		linkingPoints[numPoint].x = round(tempX * cos(ellipseAngleRad) - tempY * sin(ellipseAngleRad));
		linkingPoints[numPoint].y = round(tempX * sin(ellipseAngleRad) + tempY * cos(ellipseAngleRad));
		linkingPoints[numPoint].x += centerOfShape.x + dx;
		linkingPoints[numPoint].y += centerOfShape.y + dy;
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
		CPoint temp1{ shapeMove.tempDxDy.x + circleCenter.x - x,shapeMove.tempDxDy.y + circleCenter.y + y };
		smallerRgn1.push_back(temp1);
		dc->MoveTo(shapeMove.tempDxDy.x + circleCenter.x - x, shapeMove.tempDxDy.y + circleCenter.y + y);
	}
	CPoint temp1_2{ shapeMove.tempDxDy.x + circleCenter.x, shapeMove.tempDxDy.y + circleCenter.y + b };
	smallerRgn1.push_back(temp1);
	//

	//
	vector<CPoint> smallerRgn2;
	//vector<CPoint> eSP;
	dc->MoveTo(shapeMove.tempDxDy.x + circleCenter.x, shapeMove.tempDxDy.y + circleCenter.y + b);
	for (int y = b - 1; y >= -b; y--)
	{
		double temp = sqrt((1 - (double)y / (double)b) * (1 + (double)y / (double)b));
		int x = a * temp;
		//dc->LineTo(circleCenter.x + x, circleCenter.y + y);
		CPoint temp2{ shapeMove.tempDxDy.x + circleCenter.x + x, shapeMove.tempDxDy.y + circleCenter.y + y };
		smallerRgn2.push_back(temp2);
		dc->MoveTo(shapeMove.tempDxDy.x + circleCenter.x + x, shapeMove.tempDxDy.y + circleCenter.y + y);
	}
	CPoint temp2_2{ shapeMove.tempDxDy.x + circleCenter.x,shapeMove.tempDxDy.y + circleCenter.y + b };
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

	
	dc->SelectObject(pen);
	//dc->Ellipse(centerPoint23Bottom.x - 10, centerPoint23Bottom.y - 10, centerPoint23Bottom.x + 10, centerPoint23Bottom.y + 10);
	//dc->Polygon(&eFP[0], eFP.size());
	//dc->Polygon(&eSP[0], eSP.size());
	dc->Polygon(&shapePoints[0], shapePoints.size());
	dc->FillRgn(ellipseRgn1, ellipseBrush);
	dc->FillRgn(ellipseRgn2, ellipseBrush);


	if (isSelected)
	{
		CPen* tempPen = new CPen(1, 1, RGB(100, 100, 100));
		dc->SelectObject(tempPen);
		dc->MoveTo(centerPoint23Bottom);
		dc->LineTo(centerPoint23Top);

		

		dc->Ellipse(centerPoint23Top.x - SIZE_OF_ELLIPSE_FOR_ROTATE_TOOL, centerPoint23Top.y - SIZE_OF_ELLIPSE_FOR_ROTATE_TOOL, centerPoint23Top.x + SIZE_OF_ELLIPSE_FOR_ROTATE_TOOL, centerPoint23Top.y + SIZE_OF_ELLIPSE_FOR_ROTATE_TOOL);
		for (int i = 0; i < 4; i++)
			dc->Ellipse(selectedAreaPoints[i].x - SIZE_OF_POINT_FOR_CHANGE, selectedAreaPoints[i].y - SIZE_OF_POINT_FOR_CHANGE, selectedAreaPoints[i].x + SIZE_OF_POINT_FOR_CHANGE, selectedAreaPoints[i].y + SIZE_OF_POINT_FOR_CHANGE);
		
		
		// draw rectangle that demonstrates selecting shape
		for (int pointNum = 0; pointNum < 4; pointNum++)
		{
			if (pointNum == 3)
			{
				dc->MoveTo(selectedAreaPoints[3]);
				dc->LineTo(selectedAreaPoints[0]);
				break;
			}
			dc->MoveTo(selectedAreaPoints[pointNum]);
			dc->LineTo(selectedAreaPoints[pointNum + 1]);

		}

		tempPen->DeleteObject();
	}

	if (drawPointsForLines)
	{
		//draw points for lines
		for (int pointNum = 0; pointNum < linkingPoints.size(); pointNum++)
		{
			dc->Ellipse(linkingPoints[pointNum].x - SIZE_OF_ELLIPSE_FOR_LINES, linkingPoints[pointNum].y - SIZE_OF_ELLIPSE_FOR_LINES, linkingPoints[pointNum].x + SIZE_OF_ELLIPSE_FOR_LINES, linkingPoints[pointNum].y + SIZE_OF_ELLIPSE_FOR_LINES);
		}
	}

	ellipseRgn1->DeleteObject();
	ellipseRgn2->DeleteObject();
	pen->DeleteObject();
	ellipseBrush->DeleteObject();
}

bool EllipseShape::isClickedOnShapeRgn(CPoint point)
{
	HRGN ellipseRgn1 = CreatePolygonRgn(&eFP[0], eFP.size(), ALTERNATE);
	HRGN ellipseRgn2 = CreatePolygonRgn(&eSP[0], eSP.size(), ALTERNATE);
	if (PtInRegion(ellipseRgn1, point.x, point.y) || PtInRegion(ellipseRgn2, point.x, point.y))
	{
		DeleteObject(ellipseRgn1);
		DeleteObject(ellipseRgn2);
		return true;
	}
	DeleteObject(ellipseRgn1);
	DeleteObject(ellipseRgn2);
	return false;
}

bool EllipseShape::isClickedPointForChange(CPoint point)
{
	for (int pointNum = 0; pointNum < points.size(); pointNum++)
	{
		HRGN pointRgn = CreateEllipticRgn(selectedAreaPoints[pointNum].x - SIZE_OF_POINT_FOR_CHANGE, selectedAreaPoints[pointNum].y - SIZE_OF_POINT_FOR_CHANGE,
			selectedAreaPoints[pointNum].x + SIZE_OF_POINT_FOR_CHANGE, selectedAreaPoints[pointNum].y + SIZE_OF_POINT_FOR_CHANGE);
		if (PtInRegion(pointRgn, point.x, point.y))
		{
			numberOfPoint = pointNum;
			DeleteObject(pointRgn);
			return true;
		}
		DeleteObject(pointRgn);
	}

	numberOfPoint = -1;
	return false;
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

	points[0] = CPoint(shapeMove.tempDxDy.x + rectangleCenter.x - size + diffAr[0].x + diffAr[3].x - (diffAr[1].x + diffAr[2].x), shapeMove.tempDxDy.y + rectangleCenter.y + size + diffAr[0].y + diffAr[1].y - (diffAr[2].y + diffAr[3].y)); //leftbottom
	points[1] = CPoint(shapeMove.tempDxDy.x + rectangleCenter.x + size + diffAr[1].x + diffAr[2].x - (diffAr[0].x + diffAr[3].x), shapeMove.tempDxDy.y + rectangleCenter.y + size + diffAr[0].y + diffAr[1].y - (diffAr[2].y + diffAr[3].y)); //rightbottom
	points[2] = CPoint(shapeMove.tempDxDy.x + rectangleCenter.x + size + diffAr[1].x + diffAr[2].x - (diffAr[0].x + diffAr[3].x), shapeMove.tempDxDy.y + rectangleCenter.y - size + diffAr[2].y + diffAr[3].y - (diffAr[0].y + diffAr[1].y)); //righttop
	points[3] = CPoint(shapeMove.tempDxDy.x + rectangleCenter.x - size + diffAr[0].x + diffAr[3].x - (diffAr[1].x + diffAr[2].x), shapeMove.tempDxDy.y + rectangleCenter.y - size + diffAr[2].y + diffAr[3].y - (diffAr[0].y + diffAr[1].y)); //lefttop
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
	dc->Polygon(&points[0], 4);
	dc->FillRgn(rectangleReg, rectangleBrush);
	//dc->FillRgn(triangleReg, brush);
	/*delete pen;
	delete rectangleBrush;
	//delete rectangleReg;*/
	pen->DeleteObject();
	rectangleBrush->DeleteObject();
	rectangleReg->DeleteObject();

}

//CPoint RectangleShape::getPointForRotateTool()
//{
//	return CPoint();
//}

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
	points[0] = CPoint(shapeMove.tempDxDy.x + rectangleCenter.x - 2 * sqrt(3) / 3 * size + diffAr[0].x + diffAr[3].x - (diffAr[1].x + diffAr[2].x), shapeMove.tempDxDy.y + rectangleCenter.y + size + diffAr[0].y + diffAr[1].y - (diffAr[2].y + diffAr[3].y)); //leftbottom
	points[1] = CPoint(shapeMove.tempDxDy.x + rectangleCenter.x + 2 * sqrt(3) / 3 * size + diffAr[1].x + diffAr[2].x - (diffAr[0].x + diffAr[3].x), shapeMove.tempDxDy.y + rectangleCenter.y + size + diffAr[0].y + diffAr[1].y - (diffAr[2].y + diffAr[3].y)); //rightbottom
	points[2] = CPoint(shapeMove.tempDxDy.x + rectangleCenter.x + 2 * sqrt(3) / 3 * size + diffAr[1].x + diffAr[2].x - (diffAr[0].x + diffAr[3].x), shapeMove.tempDxDy.y + rectangleCenter.y - size + diffAr[2].y + diffAr[3].y - (diffAr[0].y + diffAr[1].y)); //righttop
	points[3] = CPoint(shapeMove.tempDxDy.x + rectangleCenter.x - 2 * sqrt(3) / 3 * size + diffAr[0].x + diffAr[3].x - (diffAr[1].x + diffAr[2].x), shapeMove.tempDxDy.y + rectangleCenter.y - size + diffAr[2].y + diffAr[3].y - (diffAr[0].y + diffAr[1].y)); //lefttop

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
	triangleRgn->CreatePolygonRgn(&points[0], 4, ALTERNATE);
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
//
//CPoint TriangleShape::getPointForRotateTool()
//{
//	return CPoint();
//}


//void IShape::rotationOfAxes(int numberOfShapeInVector)
//{
//	int tempX = dSM.x;
//	int tempY = dSM.y;
//	dSM.x = round(tempX * cos(-(ellipseAngleRad)) - tempY * sin(-(ellipseAngleRad)));
//	dSM.y = round(tempX * sin(-(ellipseAngleRad)) + tempY * cos(-(ellipseAngleRad)));
//}

bool IShape::IsClickedOnPointForLines(CPoint point, int& numberOfPoint)
{
	
	for (int pointNum = 0; pointNum < linkingPoints.size(); pointNum++)
	{
		
		HRGN pointForLinesRgn = CreateEllipticRgn(linkingPoints[pointNum].x - SIZE_OF_ELLIPSE_FOR_LINES * MULTIPLIKATOR_FOR_LINES_ELLIPSE_RGN, linkingPoints[pointNum].y - SIZE_OF_ELLIPSE_FOR_LINES * MULTIPLIKATOR_FOR_LINES_ELLIPSE_RGN, linkingPoints[pointNum].x + SIZE_OF_ELLIPSE_FOR_LINES * MULTIPLIKATOR_FOR_LINES_ELLIPSE_RGN, linkingPoints[pointNum].y + SIZE_OF_ELLIPSE_FOR_LINES * MULTIPLIKATOR_FOR_LINES_ELLIPSE_RGN);
		if(PtInRegion(pointForLinesRgn, point.x, point.y))
		{
			numberOfPoint = pointNum;
			DeleteObject(pointForLinesRgn);
			return true;
		}
		DeleteObject(pointForLinesRgn);
	}
	//delete pointForLinesRgn;
	return false;
}

CPoint IShape::rotateAndMoveCoordinate(CPoint &point, Tools& toolIsUsed, int from)
{
	if (toolIsUsed == Tools::shapeMove)
	{
		
		if (from == MOUSE_MOVE)
		{
			int tempX = point.x;
			int tempY = point.y;
			point.x = round(tempX * cos(-(ellipseAngleRad)) - tempY * sin(-(ellipseAngleRad)));
			point.y = round(tempX * sin(-(ellipseAngleRad)) + tempY * cos(-(ellipseAngleRad)));
			return point;
		}
		else if (from == LBUTTON_UP)
		{
			int tempX = point.x;
			int tempY = point.y;

			point.x = round(tempX * cos((ellipseAngleRad)) - tempY * sin((ellipseAngleRad)));
			point.y = round(tempX * sin((ellipseAngleRad)) + tempY * cos((ellipseAngleRad)));
			centerOfShape.x += point.x;
			centerOfShape.y += point.y;
			return point;
		}
	}
	else if (toolIsUsed == Tools::change)
	{
		if (from == MOUSE_MOVE)
		{
			int tempX = point.x;
			int tempY = point.y;
			point.x = round(tempX * cos(-(ellipseAngleRad)) - tempY * sin(-(ellipseAngleRad)));
			point.y = round(tempX * sin(-(ellipseAngleRad)) + tempY * cos(-(ellipseAngleRad)));
			return point;
		}
	}
}

void IShape::rotateShape(CPoint point)
{
	enum circleQuarter { first, second, third, fourth };
	circleQuarter tempEnum = first;
	if (point.x >= centerOfShape.x && point.y <= centerOfShape.x)
	{
		//cout << "1" << endl;
		tempEnum = first;
	}
	else if (point.x > centerOfShape.x && point.y > centerOfShape.x)
	{
		//cout << "2" << endl;
		tempEnum = second;
	}
	else if (point.x <= centerOfShape.x && point.y >= centerOfShape.x)
	{
		//cout << "3" << endl;
		tempEnum = third;
	}
	else
	{
		//cout << "4" << endl;
		tempEnum = fourth;
	}
	getFirstClickedPoint().y;
	//int temp2 = point.y - pDoc->getShapesVector()[s]->getFirstClickedPoint().y;
	array<double, 3> sides; // 0 - side from centerOfShape to firstClickedPoint; 1 - side form firstClickedPoint to point; 2 - the remaining side
	//sides[0] = sqrt(pow(pDoc->getShapesVector()[s]->getFirstClickedPoint().x - pDoc->getShapesVector()[s]->centerOfShape.x, 2) + pow(pDoc->getShapesVector()[s]->getFirstClickedPoint().y - pDoc->getShapesVector()[s]->centerOfShape.y, 2));
	//cout << "firstPoint x: " << firstPoint.x << " firstPoint y:" << firstPoint.y << endl;
	sides[0] = sqrt(pow(firstPoint.x - centerOfShape.x, 2) + pow(firstPoint.y - centerOfShape.y, 2));
	//cout << pDoc->getShapesVector()[s]->firstPoint.x << " " << pDoc->getShapesVector()[s]->firstPoint.y << endl;
	sides[1] = sqrt(pow(firstPoint.x - point.x, 2) + pow(firstPoint.y - point.y, 2));
	sides[2] = sqrt(pow(centerOfShape.x - point.x, 2) + pow(centerOfShape.y - point.y, 2));
	/*sides[0] /= 100;
	sides[1] /= 100;
	sides[2] /= 100;*/
	//cout << "sides[2]: " << sides[2] << endl;
	double cosOfCenterAngle = (pow(sides[0], 2) + pow(sides[2], 2) - pow(sides[1], 2)) / ((2 * sides[0] * sides[2]));//using law of cosines
	//cout << " cosOfCenterAngle " << cosOfCenterAngle << endl;
	//cout << "cos: " << cosOfCenterAngle << endl;
	double centerAngleRad = acos(cosOfCenterAngle);
	//cout << "rad: " << centerAngleRad << endl;

	double centerAngleDegree = centerAngleRad * 180.0 / 3.14;
	//cout << "deg: " << centerAngleDegree << endl;
	if (tempEnum == third || tempEnum == fourth)
	{
		//pDoc->getShapesVector()[s]->ellipseAngleRad = -centerAngleDegree * 3.14 / 180.0;
		centerAngleDegree = 360 - centerAngleDegree;
	}
	//cout << "ellipseAngleRad: " << pDoc->getShapesVector()[s]->ellipseAngleRad * 180.0 / 3.14 << endl;
	//cout << "deg: " << centerAngleDegree << endl;
	//int temp = point.y - pDoc->getShapesVector()[s]->lastY;

	//check if is shape reversed
	if (isReversed())
	{
		ellipseAngleRad = -centerAngleDegree * 3.14 / 180.0;
	}
	else
	{
		ellipseAngleRad = centerAngleDegree * 3.14 / 180.0;
		//cout << pDoc->getShapesVector()[s]->ellipseAngleRad << endl;
		//cout << centerAngleDegree * 3.14 / 180.0 <<endl;
	}
}

void IShape::moveChangeRotate(vector <IShape*>& shapes, Tools& toolIsUsed, CPoint point, bool& canBeUnselected, bool& shapeIsFound)
{
	//bool canBeUnselected = true; // is used for unselecting all shapes, when clicked on space place

	//bool isShapeFound = false; // if shape is found, then break loop
	if (type == ShapeType::ellipse)
	{
		
		// check if is clicked on "rotate ellipse"
		if (getSelected() == true)
		{
			CPoint ellipseCenter = getPointForRotateTool(); // for convinience
			HRGN ellipseForRotateTool = CreateEllipticRgn(ellipseCenter.x - SIZE_OF_ELLIPSE_FOR_ROTATE_TOOL, ellipseCenter.y - SIZE_OF_ELLIPSE_FOR_ROTATE_TOOL,
				ellipseCenter.x + SIZE_OF_ELLIPSE_FOR_ROTATE_TOOL, ellipseCenter.y + SIZE_OF_ELLIPSE_FOR_ROTATE_TOOL); // create region for "rotate tool ellipse"
			if (PtInRegion(ellipseForRotateTool, point.x, point.y))
			{
				cout << "here" << endl;
				toolIsUsed = Tools::rotate;
				canBeUnselected = false;
				shapeIsFound = true;
			}
			DeleteObject(ellipseForRotateTool);

			// check if clicked on points that changing the size of shape
			if (isClickedPointForChange(point))
			{
				shapeIsFound = true;
				canBeUnselected = false;
				toolIsUsed = Tools::change;
			}

		}

		//check if clicked on shape
		if (isClickedOnShapeRgn(point))
		{
			shapeIsFound = true; // is shape is found than break the loop

			// unselecting others shapes
			for (int shapeNumForUnselecting = shapes.size() - 1; shapeNumForUnselecting >= 0; shapeNumForUnselecting--) // because shapeNumForUnselecting and shapeNum names must be different
			{
				if (shapes[shapeNumForUnselecting]->getSelected() == true)
				{
					shapes[shapeNumForUnselecting]->setSelected(false);
				};
			}
			canBeUnselected = false;
			setSelected(true);

			//using shape move tool
			toolIsUsed = Tools::shapeMove;
		}

		if (shapeIsFound) return;

	}
	else if (type == ShapeType::basicLine)
	{
		//bool breakLoop = false; // bool variable that is need for loop control
		// check if clicked on points that changing the size of shape
		//cout <<"3: "<< pDoc->getShapesVector()[0]->getSelected() << endl;
		//cout << "breakLoop " << breakLoop << endl;
		if (isClickedPointForChange(point))
		{
			shapeIsFound = true;
			toolIsUsed = Tools::change;
		}

		//check if clicked in line region
		if (isClickedOnShapeRgn(point))
		{
			//unselectint all shapes and make true canDrawPointsForLines
			for (int shapeNumForChangeProperties = 0; shapeNumForChangeProperties < shapes.size(); shapeNumForChangeProperties++)
			{
				shapes[shapeNumForChangeProperties]->setSelected(false);
				shapes[shapeNumForChangeProperties]->setCanDrawPointsForLines(true);
			}
			//selecting clicked shape
			setSelected(true);

			shapeIsFound = true;
			canBeUnselected = false;
		}
		//cout << "4: " << pDoc->getShapesVector()[0]->getSelected() << endl;
		if (shapeIsFound) return;
	}
	//return true;
}

void IShape::normalizeShape()
{
	if (isSelected)
	{


		//pDoc->getShapesVector()[s]->isNormalized = true;
		ellipseAngleRad = 0;
		CPoint tmp[4];
		if (type == ShapeType::triangle)
		{
			for (int i = 0; i < 4; i++)
			{
				tmp[i] = recFromRgn[i];
			}

		}
		else
		{
			for (int i = 0; i < 4; i++)
			{
				tmp[i] = selectedAreaPoints[i];
			}

		}

		CPoint centerSidesPoints[2];
		centerSidesPoints[0] = CPoint((tmp[1].x - tmp[0].x) / 2 + tmp[0].x, (tmp[1].y - tmp[0].y) / 2 + tmp[0].y);
		centerSidesPoints[1] = CPoint((tmp[2].x - tmp[1].x) / 2 + tmp[1].x, (tmp[2].y - tmp[1].y) / 2 + tmp[1].y);
		int l1 = (int)sqrt(pow(centerSidesPoints[0].x - centerOfShape.x, 2) + pow(centerSidesPoints[0].y - centerOfShape.y, 2));
		int l2 = (int)sqrt(pow(centerSidesPoints[1].x - centerOfShape.x, 2) + pow(centerSidesPoints[1].y - centerOfShape.y, 2));
		int min;
		min = (l1 < l2) ? l1 : l2;
		//CString dbug;
		//dbug.Format(_T("%d, %d"), l1, l2);
		////AfxMessageBox(dbug);
		for (int i = 0; i < 4; i++)
		{
			change.dxDy[i] = CPoint{ 0, 0 };
			change.tempDxDy[i] = CPoint{ 0, 0 };
		}
		size = min;
		
	}
}

void IShape::createLineConnection(int numberOfPointOfLine, int shapeConstID, int numberOfPointForLines)
{
	//cout << "here" << endl;
	if (numberOfPointOfLine == FIRST_POINT_OF_LINE)
	{
		//cout << "here2" << endl;
		connecting.isConnected.firstPointOfLine = true;
		connecting.connectedShapeConstID.firstPointOfLine = shapeConstID;
		connecting.numberOfShapesPointForLines.firstPointOfLine = numberOfPointForLines;

		//cout << "isConnected.firstPointOfLine: " << connecting.isConnected.firstPointOfLine << " connectedShapeConstID.firstPointOfLine: " << connecting.connectedShapeConstID.firstPointOfLine
			//<< " numberOfShapesPointForLines.firstPointOfLine: " << connecting.numberOfShapesPointForLines.firstPointOfLine << endl;
	}
	else if (numberOfPointOfLine == SECOND_POINT_OF_LINE)
	{
		//cout << "here3" << endl;
		connecting.isConnected.secondPointOfLine = true;
		connecting.connectedShapeConstID.secondPointOfLine = shapeConstID;
		connecting.numberOfShapesPointForLines.secondPointOfLine = numberOfPointForLines;

		//cout << "isConnected.firstPointOfLine: " << connecting.isConnected.secondPointOfLine << " connectedShapeConstID.firstPointOfLine: " << connecting.connectedShapeConstID.secondPointOfLine
			//<< " numberOfShapesPointForLines.firstPointOfLine: " << connecting.numberOfShapesPointForLines.secondPointOfLine << endl;
	}
	/*if (numberOfPointOfLine == FIRST_POINT_OF_LINE)
	{
		isConnected.firstPointOfLine = true;
		connectedShapeConstID = shapeConstID;
		numberOfShapesPointForLines = numberOfPointForLines;
	}*/
}

void IShape::updateLineConnection(const vector<IShape*>& shapes)
{
	if (connecting.isConnected.firstPointOfLine)
	{
		for (int shapeNum = 0; shapeNum < shapes.size(); shapeNum++)
		{
			if (shapes[shapeNum]->type != ShapeType::basicLine)
			{
				if (shapes[shapeNum]->constID == connecting.connectedShapeConstID.firstPointOfLine)
				{
					setCoordinateForChange(FIRST_POINT_OF_LINE, shapes[shapeNum]->getPointForLine(connecting.numberOfShapesPointForLines.firstPointOfLine));
					
					//cout << shapes[shapeNum]->getPointForLine(numberOfShapesPointForLines).x << " " << shapes[shapeNum]->getPointForLine(numberOfShapesPointForLines).y << endl;
					//AfxMessageBox(_T("000"));
				}
			}
		}
	}
	if (connecting.isConnected.secondPointOfLine)
	{
		for (int shapeNum = 0; shapeNum < shapes.size(); shapeNum++)
		{
			if (shapes[shapeNum]->type != ShapeType::basicLine)
			{
				if (shapes[shapeNum]->constID == connecting.connectedShapeConstID.secondPointOfLine)
				{
					setCoordinateForChange(SECOND_POINT_OF_LINE, shapes[shapeNum]->getPointForLine(connecting.numberOfShapesPointForLines.secondPointOfLine));

					//cout << shapes[shapeNum]->getPointForLine(numberOfShapesPointForLines).x << " " << shapes[shapeNum]->getPointForLine(numberOfShapesPointForLines).y << endl;
					//AfxMessageBox(_T("000"));
				}
			}
		}
	}
}

void IShape::lineDisconnecting(int numberOfPointOfLine, int shapeConstID)
{
	if (numberOfPointOfLine == FIRST_POINT_OF_LINE)
	{
		if (connecting.connectedShapeConstID.firstPointOfLine == shapeConstID) // disconnect not always (if id of connected Shape == shape constID to disconnect)
		{
			//cout << "here2" << endl;
			connecting.isConnected.firstPointOfLine = false;
			connecting.connectedShapeConstID.firstPointOfLine = -1;
			connecting.numberOfShapesPointForLines.firstPointOfLine = -1;
		}

		//cout << "isConnected.firstPointOfLine: " << connecting.isConnected.firstPointOfLine << " connectedShapeConstID.firstPointOfLine: " << connecting.connectedShapeConstID.firstPointOfLine
			//<< " numberOfShapesPointForLines.firstPointOfLine: " << connecting.numberOfShapesPointForLines.firstPointOfLine << endl;
	}
	else if (numberOfPointOfLine == SECOND_POINT_OF_LINE)
	{
		if (connecting.connectedShapeConstID.secondPointOfLine == shapeConstID) // disconnect not always (if id of connected Shape == shape constID to disconnect)
		{
			connecting.isConnected.secondPointOfLine = false;
			connecting.connectedShapeConstID.secondPointOfLine = -1;
			connecting.numberOfShapesPointForLines.secondPointOfLine = -1;
		}
		

		//cout << "isConnected.secondPointOfLine: " << connecting.isConnected.secondPointOfLine << " connectedShapeConstID.secondPointOfLine: " << connecting.connectedShapeConstID.secondPointOfLine
			//<< " numberOfShapesPointForLines.secondPointOfLine: " << connecting.numberOfShapesPointForLines.secondPointOfLine << endl;
	}
}

IShape::~IShape()
{
	IShape::IDs.erase(ID); // erase ID because ID won't exist
	IShape::names.erase(name);
}

Line::Line(CPoint firstPointOfLine, ShapeType type, COLORREF lineColor, int lineSize, int lineType)
{
	this->type = type;
	pointsOfLine[0] = firstPointOfLine;
	pointsOfLine[1] = firstPointOfLine;
}

void Line::draw(CDC* dc)
{

	
	//dc->Polygon(&tempLineRectRgn1[0], tempLineRectRgn1.size());
	//dc->Polygon(&tempLineRectRgn2[0], tempLineRectRgn2.size());

	//cout << "dx_dy[0].x" << dx_dy[0].x << " " << "dxDy[0].x" << dxDy[0].x << endl;
	if (isSelected)
	{
		for (int pointNum = 0; pointNum < pointsOfLine.size(); pointNum++)
		{
			dc->Ellipse(pointsOfLine[pointNum].x - SIZE_OF_POINT_FOR_CHANGE + change.tempDxDy[pointNum].x + change.dxDy[pointNum].x, pointsOfLine[pointNum].y + change.tempDxDy[pointNum].y + - SIZE_OF_POINT_FOR_CHANGE + change.dxDy[pointNum].y,
				pointsOfLine[pointNum].x + change.tempDxDy[pointNum].x + SIZE_OF_POINT_FOR_CHANGE+change.dxDy[pointNum].x, pointsOfLine[pointNum].y + change.tempDxDy[pointNum].y + SIZE_OF_POINT_FOR_CHANGE+ change.dxDy[pointNum].y);
		}
	}
	dc->MoveTo(CPoint(pointsOfLine[0].x + change.tempDxDy[0].x + change.dxDy[0].x, pointsOfLine[0].y + change.tempDxDy[0].y+ change.dxDy[0].y));
	dc->LineTo(CPoint(pointsOfLine[1].x + change.tempDxDy[1].x + change.dxDy[1].x, pointsOfLine[1].y + change.tempDxDy[1].y+ change.dxDy[1].y));

	/*if (isSelected)
	{
		for (int pointNum = 0; pointNum < pointsOfLine.size(); pointNum++)
		{
			dc->Ellipse(pointsOfLine[pointNum].x - SIZE_OF_POINT_FOR_CHANGE + dx_dy_temp[pointNum].x + dx_dy[pointNum].x, pointsOfLine[pointNum].y + dx_dy_temp[pointNum].y + dx_dy[pointNum].y + - SIZE_OF_POINT_FOR_CHANGE,
				pointsOfLine[pointNum].x + dx_dy_temp[pointNum].x + dx_dy[pointNum].x + SIZE_OF_POINT_FOR_CHANGE, pointsOfLine[pointNum].y + dx_dy_temp[pointNum].y + dx_dy[pointNum].y + SIZE_OF_POINT_FOR_CHANGE);
		}
	}
	dc->MoveTo(CPoint(pointsOfLine[0].x + dx_dy_temp[0].x + dx_dy[0].x, pointsOfLine[0].y + dx_dy_temp[0].y + dx_dy[0].y));
	dc->LineTo(CPoint(pointsOfLine[1].x + dx_dy_temp[1].x + dx_dy[1].x, pointsOfLine[1].y + dx_dy_temp[1].y + dx_dy[1].y));*/

	//AfxMessageBox(_T("here"));

}

bool Line::isClickedOnShapeRgn(CPoint point)
{
	array <CPoint, 4> tempLineRectRgnHorizontal;
	array <CPoint, 4> tempLineRectRgnVertical;
	if (pointsOfLine[0].x < pointsOfLine[1].x)
	{
		tempLineRectRgnHorizontal[0] = CPoint(pointsOfLine[0].x - SIZE_OF_LINE_RGN, pointsOfLine[0].y + SIZE_OF_LINE_RGN); // leftbottom
		tempLineRectRgnHorizontal[1] = CPoint(pointsOfLine[1].x + SIZE_OF_LINE_RGN, pointsOfLine[1].y + SIZE_OF_LINE_RGN); // rightbottom
		tempLineRectRgnHorizontal[2] = CPoint(pointsOfLine[1].x + SIZE_OF_LINE_RGN, pointsOfLine[1].y - SIZE_OF_LINE_RGN); // righttop
		tempLineRectRgnHorizontal[3] = CPoint(pointsOfLine[0].x - SIZE_OF_LINE_RGN, pointsOfLine[0].y - SIZE_OF_LINE_RGN); // lefttop
	}
	else
	{
		tempLineRectRgnHorizontal[0] = CPoint(pointsOfLine[0].x + SIZE_OF_LINE_RGN, pointsOfLine[0].y - SIZE_OF_LINE_RGN); // leftbottom
		tempLineRectRgnHorizontal[1] = CPoint(pointsOfLine[1].x - SIZE_OF_LINE_RGN, pointsOfLine[1].y - SIZE_OF_LINE_RGN); // rightbottom
		tempLineRectRgnHorizontal[2] = CPoint(pointsOfLine[1].x - SIZE_OF_LINE_RGN, pointsOfLine[1].y + SIZE_OF_LINE_RGN); // righttop
		tempLineRectRgnHorizontal[3] = CPoint(pointsOfLine[0].x + SIZE_OF_LINE_RGN, pointsOfLine[0].y + SIZE_OF_LINE_RGN); // lefttop
	}
	if (pointsOfLine[0].y < pointsOfLine[1].y)
	{
		tempLineRectRgnVertical[0] = CPoint(pointsOfLine[0].x + SIZE_OF_LINE_RGN, pointsOfLine[0].y - SIZE_OF_LINE_RGN); // leftbottom
		tempLineRectRgnVertical[1] = CPoint(pointsOfLine[0].x - SIZE_OF_LINE_RGN, pointsOfLine[0].y - SIZE_OF_LINE_RGN); // rightbottom
		tempLineRectRgnVertical[2] = CPoint(pointsOfLine[1].x - SIZE_OF_LINE_RGN, pointsOfLine[1].y + SIZE_OF_LINE_RGN); // righttop
		tempLineRectRgnVertical[3] = CPoint(pointsOfLine[1].x + SIZE_OF_LINE_RGN, pointsOfLine[1].y + SIZE_OF_LINE_RGN); // lefttop
	}
	else
	{
		tempLineRectRgnVertical[0] = CPoint(pointsOfLine[0].x - SIZE_OF_LINE_RGN, pointsOfLine[0].y + SIZE_OF_LINE_RGN); // leftbottom
		tempLineRectRgnVertical[1] = CPoint(pointsOfLine[0].x + SIZE_OF_LINE_RGN, pointsOfLine[0].y + SIZE_OF_LINE_RGN); // rightbottom
		tempLineRectRgnVertical[2] = CPoint(pointsOfLine[1].x + SIZE_OF_LINE_RGN, pointsOfLine[1].y - SIZE_OF_LINE_RGN); // righttop
		tempLineRectRgnVertical[3] = CPoint(pointsOfLine[1].x - SIZE_OF_LINE_RGN, pointsOfLine[1].y - SIZE_OF_LINE_RGN); // lefttop
	}
	

	
	HRGN lineRgnHor = CreatePolygonRgn(&tempLineRectRgnHorizontal[0], 4, ALTERNATE);
	HRGN lineRgnVert = CreatePolygonRgn(&tempLineRectRgnVertical[0], 4, ALTERNATE);
	if (PtInRegion(lineRgnHor, point.x, point.y) || PtInRegion(lineRgnVert, point.x, point.y))
	{
		::DeleteObject(lineRgnHor);
		DeleteObject(lineRgnVert);
		return true;
	}
	
	::DeleteObject(lineRgnHor);
	DeleteObject(lineRgnVert);
	return false;
}

bool Line::isClickedPointForChange(CPoint point)
{
	for (int pointNum = 0; pointNum<pointsOfLine.size(); pointNum++)
	{
		HRGN pointRgn = CreateEllipticRgn(pointsOfLine[pointNum].x - SIZE_OF_POINT_FOR_CHANGE * RATE_VALUE_FOR_POINT_FOR_CHANGE, pointsOfLine[pointNum].y - SIZE_OF_POINT_FOR_CHANGE * RATE_VALUE_FOR_POINT_FOR_CHANGE,
			pointsOfLine[pointNum].x + SIZE_OF_POINT_FOR_CHANGE * RATE_VALUE_FOR_POINT_FOR_CHANGE, pointsOfLine[pointNum].y + SIZE_OF_POINT_FOR_CHANGE * RATE_VALUE_FOR_POINT_FOR_CHANGE);
		if (PtInRegion(pointRgn, point.x, point.y))
		{
			numberOfPoint = pointNum;
			DeleteObject(pointRgn);
			return true;
		}
		DeleteObject(pointRgn);
	}

	numberOfPoint = -1;
	return false;
}

