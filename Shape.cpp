#include "pch.h"
#include "Shape.h"

int IShape::dx = 0;
int IShape::dy = 0;
int IShape::sizeOfPointToMoveAndChange = 3;
int IShape::countOfShape = 0;
set<int> IShape::IDs;
set<CString> IShape::names;
CPoint IShape::firstPoint{ 0, 0 };



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

	
	//cout << points[0].y << " " << points[3].y << endl;
	// calculate coordinates for points, that are needed to draw links (lines)
	pointsForLines[0] = CPoint((points[1].x - points[0].x) / 2 + points[0].x, points[0].y);
	pointsForLines[1] = CPoint(points[1].x, (points[1].y + points[2].y) / 2);
	pointsForLines[2] = CPoint((points[2].x - points[3].x) / 2 + points[3].x, points[2].y);
	pointsForLines[3] = CPoint(points[3].x, (points[0].y + points[3].y) / 2);

	// points that needed for drawing rotate tool
	centerPoint23Bottom = CPoint((points[2].x - points[3].x) / 2 + points[3].x, points[2].y);
	if (points[0].y >= points[3].y)
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
	for (int numPoint = 0; numPoint < pointsForLines.size(); numPoint++)
	{
		int tempX = pointsForLines[numPoint].x;
		int tempY = pointsForLines[numPoint].y;
		pointsForLines[numPoint].x = round(tempX * cos(ellipseAngleRad) - tempY * sin(ellipseAngleRad));
		pointsForLines[numPoint].y = round(tempX * sin(ellipseAngleRad) + tempY * cos(ellipseAngleRad));
		pointsForLines[numPoint].x += centerOfShape.x + dx;
		pointsForLines[numPoint].y += centerOfShape.y + dy;
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

	
	dc->SelectObject(pen);
	//dc->Ellipse(centerPoint23Bottom.x - 10, centerPoint23Bottom.y - 10, centerPoint23Bottom.x + 10, centerPoint23Bottom.y + 10);
	dc->Polygon(&eFP[0], eFP.size());
	dc->Polygon(&eSP[0], eSP.size());
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
			dc->Ellipse(points[i].x - SIZE_OF_POINT_FOR_CHANGE, points[i].y - SIZE_OF_POINT_FOR_CHANGE, points[i].x + SIZE_OF_POINT_FOR_CHANGE, points[i].y + SIZE_OF_POINT_FOR_CHANGE);
		
		
		// draw rectangle that demonstrates selecting shape
		for (int pointNum = 0; pointNum < 4; pointNum++)
		{
			if (pointNum == 3)
			{
				dc->MoveTo(points[3]);
				dc->LineTo(points[0]);
				break;
			}
			dc->MoveTo(points[pointNum]);
			dc->LineTo(points[pointNum + 1]);

		}

		tempPen->DeleteObject();
	}

	if (drawPointsForLines)
	{
		//draw points for lines
		for (int pointNum = 0; pointNum < pointsForLines.size(); pointNum++)
		{
			dc->Ellipse(pointsForLines[pointNum].x - SIZE_OF_ELLIPSE_FOR_LINES, pointsForLines[pointNum].y - SIZE_OF_ELLIPSE_FOR_LINES, pointsForLines[pointNum].x + SIZE_OF_ELLIPSE_FOR_LINES, pointsForLines[pointNum].y + SIZE_OF_ELLIPSE_FOR_LINES);
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
		HRGN pointRgn = CreateEllipticRgn(points[pointNum].x - SIZE_OF_POINT_FOR_CHANGE, points[pointNum].y - SIZE_OF_POINT_FOR_CHANGE,
			points[pointNum].x + SIZE_OF_POINT_FOR_CHANGE, points[pointNum].y + SIZE_OF_POINT_FOR_CHANGE);
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


bool IShape::IsClickedOnPointForLines(CPoint point, int& numberOfPoint)
{
	
	for (int pointNum = 0; pointNum < pointsForLines.size(); pointNum++)
	{
		
		HRGN pointForLinesRgn = CreateEllipticRgn(pointsForLines[pointNum].x - SIZE_OF_ELLIPSE_FOR_LINES * MULTIPLIKATOR_FOR_LINES_ELLIPSE_RGN, pointsForLines[pointNum].y - SIZE_OF_ELLIPSE_FOR_LINES * MULTIPLIKATOR_FOR_LINES_ELLIPSE_RGN, pointsForLines[pointNum].x + SIZE_OF_ELLIPSE_FOR_LINES * MULTIPLIKATOR_FOR_LINES_ELLIPSE_RGN, pointsForLines[pointNum].y + SIZE_OF_ELLIPSE_FOR_LINES * MULTIPLIKATOR_FOR_LINES_ELLIPSE_RGN);
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
	this->firstPointOfLine = firstPointOfLine;
	this->secondPointOfLine = this->firstPointOfLine; // invisible line, bevor we change line secondPoint
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
			dc->Ellipse(pointsOfLine[pointNum].x - SIZE_OF_POINT_FOR_CHANGE + temporaryDxDy[pointNum].x, pointsOfLine[pointNum].y + temporaryDxDy[pointNum].y + - SIZE_OF_POINT_FOR_CHANGE,
				pointsOfLine[pointNum].x + temporaryDxDy[pointNum].x + SIZE_OF_POINT_FOR_CHANGE, pointsOfLine[pointNum].y + temporaryDxDy[pointNum].y + SIZE_OF_POINT_FOR_CHANGE);
		}
	}
	dc->MoveTo(CPoint(pointsOfLine[0].x + temporaryDxDy[0].x, pointsOfLine[0].y + temporaryDxDy[0].y));
	dc->LineTo(CPoint(pointsOfLine[1].x + temporaryDxDy[1].x, pointsOfLine[1].y + temporaryDxDy[1].y));

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

