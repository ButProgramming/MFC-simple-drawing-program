#include "pch.h"
#include "Shape.h"

int IShape::dx = 0;
int IShape::dy = 0;
//int IShape::sizeOfPointToMoveAndChange = 3;
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
	this->type = type;
	this->size = size;
	this->centerOfShape = centerOfShape;
	constID = IShape::countOfShape;
	setShapeID();
	setShapeName();
	countOfShape++;
}

RectangleShape::RectangleShape(CPoint centerOfShape, bool isNormalized, int size, ShapeType type, COLORREF outlineColor, COLORREF fillColor, int outlineSize, int outlineType, int fillType)
{
	this->fillType = fillType;
	this->outlineType = outlineType;
	this->outlineSize = outlineSize;
	this->outlineColor = outlineColor;
	this->fillColor = fillColor;
	this->type = type;
	this->size = size;
	this->centerOfShape = centerOfShape;
	constID = IShape::countOfShape;
	setShapeID();
	setShapeName();
	countOfShape++;
}

TriangleShape::TriangleShape(CPoint centerOfShape, bool isNormalized, int size, ShapeType type, COLORREF outlineColor, COLORREF fillColor, int outlineSize, int outlineType, int fillType)
{
	this->fillType = fillType;
	this->outlineType = outlineType;
	this->outlineSize = outlineSize;
	this->outlineColor = outlineColor;
	this->fillColor = fillColor;
	this->type = type;
	this->size = size;
	this->centerOfShape = centerOfShape;
	constID = IShape::countOfShape;
	setShapeID();
	setShapeName();
	countOfShape++;
}

Line::Line(CPoint firstPointOfLine, ShapeType type, COLORREF lineColor, int lineSize, int lineType)
{
	this->type = type;
	pointsOfLine[0] = firstPointOfLine;
	pointsOfLine[1] = firstPointOfLine;
	constID = IShape::countOfShape;
	setShapeID();
	setShapeName();
}

void EllipseShape::draw(CDC* dc)
{
	//get outline colors
	oR = GetRValue(outlineColor);
	oG = GetGValue(outlineColor);
	oB = GetBValue(outlineColor);

	//get fill colors
	fR = GetRValue(fillColor);
	fG = GetGValue(fillColor);
	fB = GetBValue(fillColor);

	// create pen
	if (isSelected)
		pen = new CPen(outlineType, outlineSize, RGB(oR, oG, oB));
	else
		pen = new CPen(PS_SOLID, 4, RGB(100, 100, 100));

	// setect pen
	dc->SelectObject(pen);

	
	// array for convinience
	array<CPoint, 4> dxDyPlusTempDxDy;
	for (int i = 0; i < 4; i++)
	{
		dxDyPlusTempDxDy[i] = change.dxDy[i] + change.tempDxDy[i];
	}

	// fill array of points for selected area
	selectedAreaPoints[0] = CPoint(shapeMove.tempDxDy.x + shapeCenterBeforRotate.x - size + dxDyPlusTempDxDy[0].x + dxDyPlusTempDxDy[3].x - (dxDyPlusTempDxDy[1].x + dxDyPlusTempDxDy[2].x), shapeMove.tempDxDy.y + shapeCenterBeforRotate.y + size + dxDyPlusTempDxDy[0].y + dxDyPlusTempDxDy[1].y - (dxDyPlusTempDxDy[2].y + dxDyPlusTempDxDy[3].y)); //leftbottom
	selectedAreaPoints[1] = CPoint(shapeMove.tempDxDy.x + shapeCenterBeforRotate.x + size + dxDyPlusTempDxDy[1].x + dxDyPlusTempDxDy[2].x - (dxDyPlusTempDxDy[0].x + dxDyPlusTempDxDy[3].x), shapeMove.tempDxDy.y + shapeCenterBeforRotate.y + size + dxDyPlusTempDxDy[0].y + dxDyPlusTempDxDy[1].y - (dxDyPlusTempDxDy[2].y + dxDyPlusTempDxDy[3].y)); //rightbottom
	selectedAreaPoints[2] = CPoint(shapeMove.tempDxDy.x + shapeCenterBeforRotate.x + size + dxDyPlusTempDxDy[1].x + dxDyPlusTempDxDy[2].x - (dxDyPlusTempDxDy[0].x + dxDyPlusTempDxDy[3].x), shapeMove.tempDxDy.y + shapeCenterBeforRotate.y - size + dxDyPlusTempDxDy[2].y + dxDyPlusTempDxDy[3].y - (dxDyPlusTempDxDy[0].y + dxDyPlusTempDxDy[1].y)); //righttop
	selectedAreaPoints[3] = CPoint(shapeMove.tempDxDy.x + shapeCenterBeforRotate.x - size + dxDyPlusTempDxDy[0].x + dxDyPlusTempDxDy[3].x - (dxDyPlusTempDxDy[1].x + dxDyPlusTempDxDy[2].x), shapeMove.tempDxDy.y + shapeCenterBeforRotate.y - size + dxDyPlusTempDxDy[2].y + dxDyPlusTempDxDy[3].y - (dxDyPlusTempDxDy[0].y + dxDyPlusTempDxDy[1].y)); //lefttop

	// calculate coordinates for points, that are needed to draw links (lines)
	linkingPoints[0] = CPoint((selectedAreaPoints[1].x - selectedAreaPoints[0].x) / 2 + selectedAreaPoints[0].x, selectedAreaPoints[0].y);
	linkingPoints[1] = CPoint(selectedAreaPoints[1].x, (selectedAreaPoints[1].y + selectedAreaPoints[2].y) / 2);
	linkingPoints[2] = CPoint((selectedAreaPoints[2].x - selectedAreaPoints[3].x) / 2 + selectedAreaPoints[3].x, selectedAreaPoints[2].y);
	linkingPoints[3] = CPoint(selectedAreaPoints[3].x, (selectedAreaPoints[0].y + selectedAreaPoints[3].y) / 2);

	// points that needed for drawing rotate tool
	centerPoint23Bottom = CPoint((selectedAreaPoints[2].x - selectedAreaPoints[3].x) / 2 + selectedAreaPoints[3].x, selectedAreaPoints[2].y);
	if (selectedAreaPoints[0].y >= selectedAreaPoints[3].y)
	{
		centerPoint23Top = CPoint(centerPoint23Bottom.x, centerPoint23Bottom.y - LENGTH_OF_LINE_FOR_ELLIPSE_OF_ROTATE_TOOL);
		isReversedVar = false;
	}
	else
	{
		centerPoint23Top = CPoint(centerPoint23Bottom.x, centerPoint23Bottom.y + LENGTH_OF_LINE_FOR_ELLIPSE_OF_ROTATE_TOOL);
		isReversedVar = true;
	}

	// point for rotate tool (is used to calculate cos)
	firstPoint = centerPoint23Top;
	
	// a - semo-major axis, b - semi-minor axis
	int a = abs((selectedAreaPoints[1].x - selectedAreaPoints[0].x) / 2);
	int b = abs((selectedAreaPoints[2].y - selectedAreaPoints[1].y) / 2);

	// create temporary vector eFP - ellipse first points - points of first semicircle
	vector<CPoint> eFP;

	// calculate points of first semicircle
	dc->MoveTo(shapeCenterBeforRotate.x, shapeCenterBeforRotate.y + b);
	for (int y = b - 1; y >= -b; y--)
	{
		double temp = sqrt((1 - (double)y / (double)b) * (1 + (double)y / (double)b));
		int x = a * temp;
		CPoint temp1{ shapeMove.tempDxDy.x + shapeCenterBeforRotate.x - x,shapeMove.tempDxDy.y + shapeCenterBeforRotate.y + y };
		eFP.push_back(temp1);
		dc->MoveTo(shapeMove.tempDxDy.x + shapeCenterBeforRotate.x - x, shapeMove.tempDxDy.y + shapeCenterBeforRotate.y + y);
	}
	CPoint temp1{ shapeMove.tempDxDy.x + shapeCenterBeforRotate.x, shapeMove.tempDxDy.y + shapeCenterBeforRotate.y + b };
	eFP.push_back(temp1);
	
	// create temporary vector eSP - ellipse second points - points of second semicircle
	vector<CPoint> eSP;

	// calculate points of second semicircle
	dc->MoveTo(shapeMove.tempDxDy.x + shapeCenterBeforRotate.x, shapeMove.tempDxDy.y + shapeCenterBeforRotate.y + b);
	for (int y = b - 1; y >= -b; y--)
	{
		double temp = sqrt((1 - (double)y / (double)b) * (1 + (double)y / (double)b));
		int x = a * temp;
		CPoint temp2{ shapeMove.tempDxDy.x + shapeCenterBeforRotate.x + x, shapeMove.tempDxDy.y + shapeCenterBeforRotate.y + y };
		eSP.push_back(temp2);
		dc->MoveTo(shapeMove.tempDxDy.x + shapeCenterBeforRotate.x + x, shapeMove.tempDxDy.y + shapeCenterBeforRotate.y + y);
	}
	CPoint temp2{ shapeMove.tempDxDy.x + shapeCenterBeforRotate.x,shapeMove.tempDxDy.y + shapeCenterBeforRotate.y + b };
	eSP.push_back(temp2);


	//dc->MoveTo(shapeCenterBeforRotate.x, shapeCenterBeforRotate.y + b);

	// clear vector befor writting of new CPoints
	shapePoints.clear();

	// fill shapePoints vector
	for (int eFPoints = 0; eFPoints<eFP.size(); eFPoints++)
	{
		shapePoints.push_back(eFP[eFPoints]);
	}
	for (int eSPoints = 0; eSPoints < eSP.size(); eSPoints++)
	{
		shapePoints.push_back(eSP[eSPoints]);
	}

	// create brush depending on filltype
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

	
	/*for (int i = 0; i < eFP.size(); i++)
	{
		rotateAndMoveCoordinate(eFP[i], DRAW_METHOD);
	}
	for (int i = 0; i < eSP.size(); i++)
	{
		rotateAndMoveCoordinate(eSP[i], DRAW_METHOD);
	}*/
	// rotate and move points of: shape, selected area, points for rotate ellipse, 
	// of points, that used for calculate cos of angle, linging points
	for (int i = 0; i < shapePoints.size(); i++)
	{
		rotateAndMoveCoordinate(shapePoints[i], DRAW_METHOD);
	}
	for (int i = 0; i < 4; i++)
	{
		rotateAndMoveCoordinate(selectedAreaPoints[i], DRAW_METHOD);
	}
	for (int numPoint = 0; numPoint < linkingPoints.size(); numPoint++)
	{
		rotateAndMoveCoordinate(linkingPoints[numPoint], DRAW_METHOD);
	}
	rotateAndMoveCoordinate(centerPoint23Bottom, DRAW_METHOD);
	rotateAndMoveCoordinate(centerPoint23Top, DRAW_METHOD);

	int tempXFP = firstPoint.x;
	int tempYFP = firstPoint.y;
	//firstPoint.x = round(tempXFP * 1 - tempYFP * 0);
	//firstPoint.y = round(tempXFP * 0 + tempYFP * 1);
	firstPoint.x += centerOfShape.x + dx;
	firstPoint.y += centerOfShape.y + dy;

	// create smaller ellipse to fill region
	a = a - DIFFERENCE_FOR_FILL_RGN;
	b = b - DIFFERENCE_FOR_FILL_RGN;
	
	// create first temporary smaller rgn for filling points
	vector<CPoint> smallerRgn1;

	// calculate points of first smaller rgn
	dc->MoveTo(shapeCenterBeforRotate.x, shapeCenterBeforRotate.y + b);
	for (int y = b - 1; y >= -b; y--)
	{
		double temp = sqrt((1 - (double)y / (double)b) * (1 + (double)y / (double)b));
		int x = a * temp;
		//dc->LineTo(circleCenter.x - x, circleCenter.y + y);
		CPoint temp1{ shapeMove.tempDxDy.x + shapeCenterBeforRotate.x - x,shapeMove.tempDxDy.y + shapeCenterBeforRotate.y + y };
		smallerRgn1.push_back(temp1);
		dc->MoveTo(shapeMove.tempDxDy.x + shapeCenterBeforRotate.x - x, shapeMove.tempDxDy.y + shapeCenterBeforRotate.y + y);
	}
	CPoint temp1_2{ shapeMove.tempDxDy.x + shapeCenterBeforRotate.x, shapeMove.tempDxDy.y + shapeCenterBeforRotate.y + b };
	smallerRgn1.push_back(temp1);
	
	// create second temporary smaller rgn for filling points
	vector<CPoint> smallerRgn2;
	
	// calculate points of second smaller rgn
	dc->MoveTo(shapeMove.tempDxDy.x + shapeCenterBeforRotate.x, shapeMove.tempDxDy.y + shapeCenterBeforRotate.y + b);
	for (int y = b - 1; y >= -b; y--)
	{
		double temp = sqrt((1 - (double)y / (double)b) * (1 + (double)y / (double)b));
		int x = a * temp;
		//dc->LineTo(circleCenter.x + x, circleCenter.y + y);
		CPoint temp2{ shapeMove.tempDxDy.x + shapeCenterBeforRotate.x + x, shapeMove.tempDxDy.y + shapeCenterBeforRotate.y + y };
		smallerRgn2.push_back(temp2);
		dc->MoveTo(shapeMove.tempDxDy.x + shapeCenterBeforRotate.x + x, shapeMove.tempDxDy.y + shapeCenterBeforRotate.y + y);
	}
	CPoint temp2_2{ shapeMove.tempDxDy.x + shapeCenterBeforRotate.x,shapeMove.tempDxDy.y + shapeCenterBeforRotate.y + b };
	smallerRgn2.push_back(temp2);

	//dc->MoveTo(shapeCenterBeforRotate.x, shapeCenterBeforRotate.y + b);

	// delete old CPoints in fillAreaPoints and push CPoints form frist and second smallerRgns in fillAreaPoints
	fillAreaPoints.clear();
	for (int firstSmallerRgnPoint = 0; firstSmallerRgnPoint < smallerRgn1.size(); firstSmallerRgnPoint++)
	{
		fillAreaPoints.push_back(smallerRgn1[firstSmallerRgnPoint]);
	}
	for (int secondSmallerRgnPoint = 0; secondSmallerRgnPoint < smallerRgn2.size(); secondSmallerRgnPoint++)
	{
		fillAreaPoints.push_back(smallerRgn2[secondSmallerRgnPoint]);
	}

	// rotate and move fill area points
	for (int fillPointNum = 0; fillPointNum < fillAreaPoints.size(); fillPointNum++)
	{
		rotateAndMoveCoordinate(fillAreaPoints[fillPointNum], DRAW_METHOD);
	}

	// rgn for filling area of shape
	CRgn* fillAreaRgn = new CRgn;
	fillAreaRgn->CreatePolygonRgn(&fillAreaPoints[0], fillAreaPoints.size(), ALTERNATE);

	// select pen for drawing, draw polygon and fill it
	dc->SelectObject(pen);
	dc->Polygon(&shapePoints[0], shapePoints.size());
	dc->FillRgn(fillAreaRgn, ellipseBrush);

	// draw ellipse for change and rotate if shape is selected
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

		// delete pen
		tempPen->DeleteObject();
	}

	// draw points for lines if is true
	if (drawPointsForLines)
	{
		//draw points for lines
		for (int pointNum = 0; pointNum < linkingPoints.size(); pointNum++)
		{
			dc->Ellipse(linkingPoints[pointNum].x - SIZE_OF_ELLIPSE_FOR_LINES, linkingPoints[pointNum].y - SIZE_OF_ELLIPSE_FOR_LINES, linkingPoints[pointNum].x + SIZE_OF_ELLIPSE_FOR_LINES, linkingPoints[pointNum].y + SIZE_OF_ELLIPSE_FOR_LINES);
		}
	}

	// delete graphical objects
	pen->DeleteObject();
	ellipseBrush->DeleteObject();
	fillAreaRgn->DeleteObject();
}

bool IShape::isClickedOnShapeRgn(CPoint point)
{
	HRGN ellipseRgn = CreatePolygonRgn(&shapePoints[0], shapePoints.size(), ALTERNATE);
	if (PtInRegion(ellipseRgn, point.x, point.y))
	{
		DeleteObject(ellipseRgn);
		return true;
	}
	DeleteObject(ellipseRgn);
	return false;
}

bool IShape::isClickedPointForChange(CPoint point)
{
	for (int pointNum = 0; pointNum < selectedAreaPoints.size(); pointNum++)
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

	if (isSelected)
		pen = new CPen(outlineType, outlineSize, RGB(oR, oG, oB));
	else
		pen = new CPen(PS_SOLID, 4, RGB(100, 100, 100));
	dc->SelectObject(pen);

	CPoint dxDyPlusTempDxDy[4];
	for (int i = 0; i < 4; i++)
	{
		dxDyPlusTempDxDy[i] = CPoint(change.dxDy[i].x + change.tempDxDy[i].x, change.dxDy[i].y + change.tempDxDy[i].y);
	}

	shapePoints.resize(4);
	shapePoints[0] = CPoint(shapeMove.tempDxDy.x + shapeCenterBeforRotate.x - size + dxDyPlusTempDxDy[0].x + dxDyPlusTempDxDy[3].x - (dxDyPlusTempDxDy[1].x + dxDyPlusTempDxDy[2].x), shapeMove.tempDxDy.y + shapeCenterBeforRotate.y + size + dxDyPlusTempDxDy[0].y + dxDyPlusTempDxDy[1].y - (dxDyPlusTempDxDy[2].y + dxDyPlusTempDxDy[3].y)); //leftbottom
	shapePoints[1] = CPoint(shapeMove.tempDxDy.x + shapeCenterBeforRotate.x + size + dxDyPlusTempDxDy[1].x + dxDyPlusTempDxDy[2].x - (dxDyPlusTempDxDy[0].x + dxDyPlusTempDxDy[3].x), shapeMove.tempDxDy.y + shapeCenterBeforRotate.y + size + dxDyPlusTempDxDy[0].y + dxDyPlusTempDxDy[1].y - (dxDyPlusTempDxDy[2].y + dxDyPlusTempDxDy[3].y)); //rightbottom
	shapePoints[2] = CPoint(shapeMove.tempDxDy.x + shapeCenterBeforRotate.x + size + dxDyPlusTempDxDy[1].x + dxDyPlusTempDxDy[2].x - (dxDyPlusTempDxDy[0].x + dxDyPlusTempDxDy[3].x), shapeMove.tempDxDy.y + shapeCenterBeforRotate.y - size + dxDyPlusTempDxDy[2].y + dxDyPlusTempDxDy[3].y - (dxDyPlusTempDxDy[0].y + dxDyPlusTempDxDy[1].y)); //righttop
	shapePoints[3] = CPoint(shapeMove.tempDxDy.x + shapeCenterBeforRotate.x - size + dxDyPlusTempDxDy[0].x + dxDyPlusTempDxDy[3].x - (dxDyPlusTempDxDy[1].x + dxDyPlusTempDxDy[2].x), shapeMove.tempDxDy.y + shapeCenterBeforRotate.y - size + dxDyPlusTempDxDy[2].y + dxDyPlusTempDxDy[3].y - (dxDyPlusTempDxDy[0].y + dxDyPlusTempDxDy[1].y)); //lefttop
	

	centerPoint23Bottom = CPoint((shapePoints[2].x - shapePoints[3].x) / 2 + shapePoints[3].x, shapePoints[2].y);
	if (shapePoints[0].y >= shapePoints[3].y)
	{
		centerPoint23Top = CPoint(centerPoint23Bottom.x, centerPoint23Bottom.y - LENGTH_OF_LINE_FOR_ELLIPSE_OF_ROTATE_TOOL);
		isReversedVar = false;
	}
	else
	{
		centerPoint23Top = CPoint(centerPoint23Bottom.x, centerPoint23Bottom.y + LENGTH_OF_LINE_FOR_ELLIPSE_OF_ROTATE_TOOL);
		isReversedVar = true;
	}
	firstPoint = centerPoint23Top;


	//fillAreaPoints.clear();
	fillAreaPoints.resize(4);
	
	if ((shapePoints[3].x < shapePoints[1].x) && (shapePoints[3].y < shapePoints[1].y))
	{
		fillAreaPoints[0] = CPoint{ shapePoints[0].x + 1, shapePoints[0].y - 1 }; //lb
		fillAreaPoints[1] = CPoint{ shapePoints[1].x - 1, shapePoints[1].y - 1 }; //rb
		fillAreaPoints[2] = CPoint{ shapePoints[2].x - 1, shapePoints[2].y + 1 }; //rt
		fillAreaPoints[3] = CPoint{ shapePoints[3].x + 1, shapePoints[3].y + 1 }; //lt
	}
	else if ((shapePoints[3].x > shapePoints[1].x) && (shapePoints[3].y < shapePoints[1].y))
	{
		fillAreaPoints[0] = CPoint{ shapePoints[0].x - 1, shapePoints[0].y - 1 }; //lb
		fillAreaPoints[1] = CPoint{ shapePoints[1].x + 1, shapePoints[1].y - 1 }; //rb
		fillAreaPoints[2] = CPoint{ shapePoints[2].x + 1, shapePoints[2].y + 1 }; //rt
		fillAreaPoints[3] = CPoint{ shapePoints[3].x - 1, shapePoints[3].y + 1 }; //lt
	}
	else if ((shapePoints[3].x > shapePoints[1].x) && (shapePoints[3].y > shapePoints[1].y))
	{
		fillAreaPoints[0] = CPoint{ shapePoints[0].x - 1, shapePoints[0].y + 1 }; //lb
		fillAreaPoints[1] = CPoint{ shapePoints[1].x + 1, shapePoints[1].y + 1 }; //rb
		fillAreaPoints[2] = CPoint{ shapePoints[2].x + 1, shapePoints[2].y - 1 }; //rt
		fillAreaPoints[3] = CPoint{ shapePoints[3].x - 1, shapePoints[3].y - 1 }; //lt
	}
	else
	{
		fillAreaPoints[0] = CPoint{ shapePoints[0].x + 1, shapePoints[0].y + 1 }; //lb
		fillAreaPoints[1] = CPoint{ shapePoints[1].x - 1, shapePoints[1].y + 1 }; //rb
		fillAreaPoints[2] = CPoint{ shapePoints[2].x - 1, shapePoints[2].y - 1 }; //rt
		fillAreaPoints[3] = CPoint{ shapePoints[3].x + 1, shapePoints[3].y - 1 }; //lt

	}
	
	linkingPoints[0] = CPoint((shapePoints[1].x - shapePoints[0].x) / 2 + shapePoints[0].x, shapePoints[0].y);
	linkingPoints[1] = CPoint(shapePoints[1].x, (shapePoints[1].y + shapePoints[2].y) / 2);
	linkingPoints[2] = CPoint((shapePoints[2].x - shapePoints[3].x) / 2 + shapePoints[3].x, shapePoints[2].y);
	linkingPoints[3] = CPoint(shapePoints[3].x, (shapePoints[0].y + shapePoints[3].y) / 2);


	// rotate shape
	for (int i = 0; i < shapePoints.size(); i++)
	{
		rotateAndMoveCoordinate(shapePoints[i], DRAW_METHOD);
		/*int tempX = points[i].x;
		int tempY = points[i].y;
		points[i].x = round(tempX * cos(angleRad) - tempY * sin(angleRad));
		points[i].y = round(tempX * sin(angleRad) + tempY * cos(angleRad));
		points[i].x += centerOfShape.x + dx;
		points[i].y += centerOfShape.y + dy;*/
	}

	//rotate shape region points
	for (int i = 0; i < fillAreaPoints.size(); i++)
	{
		rotateAndMoveCoordinate(fillAreaPoints[i], DRAW_METHOD);
		/*int tempX = pointsReg[i].x;
		int tempY = pointsReg[i].y;
		pointsReg[i].x = round(tempX * cos(angleRad) - tempY * sin(angleRad));
		pointsReg[i].y = round(tempX * sin(angleRad) + tempY * cos(angleRad));
		pointsReg[i].x += centerOfShape.x + dx;
		pointsReg[i].y += centerOfShape.y + dy;*/
	}
	rotateAndMoveCoordinate(centerPoint23Bottom, DRAW_METHOD);
	rotateAndMoveCoordinate(centerPoint23Top, DRAW_METHOD);

	// move and rotate points for lines
	for (int numPoint = 0; numPoint < linkingPoints.size(); numPoint++)
	{
		rotateAndMoveCoordinate(linkingPoints[numPoint], DRAW_METHOD);
	}
	int tempXFP = firstPoint.x;
	int tempYFP = firstPoint.y;
	firstPoint.x = round(tempXFP * 1 - tempYFP * 0);
	firstPoint.y = round(tempXFP * 0 + tempYFP * 1);
	firstPoint.x += centerOfShape.x + dx;
	firstPoint.y += centerOfShape.y + dy;

	for (int pointNum = 0; pointNum < shapePoints.size(); pointNum++)
	{
		selectedAreaPoints[pointNum] = shapePoints[pointNum];
	}




	//rectangleReg->CreatePolygonRgn(points, 4, ALTERNATE);
	//GetRgnBox(*rectangleReg, boxRect);
	//dc->Rectangle(boxRect);
	//if (isSelected)
	//{
	//	//dc->Ellipse(0, 0, 200, 200);
	//	for (int i = 0; i < 4; i++)
	//		dc->Ellipse(shapePoints[i].x - sizeOfPointToMoveAndChange, shapePoints[i].y - sizeOfPointToMoveAndChange, shapePoints[i].x + sizeOfPointToMoveAndChange, shapePoints[i].y + sizeOfPointToMoveAndChange);
	//}
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
	rectangleReg->CreatePolygonRgn(&fillAreaPoints[0], 4, ALTERNATE);
	dc->Polygon(&shapePoints[0], 4);
	dc->FillRgn(rectangleReg, rectangleBrush);

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

	/*if (!isSelected && !isSelectedFromDoubleSelectingTool)
		pen = new CPen(outlineType, outlineSize, RGB(oR, oG, oB));*/
	if (isSelected)
		pen = new CPen(PS_SOLID, 4, RGB(0, 0, 0));
	else
		pen = new CPen(PS_SOLID, 4, RGB(100, 100, 100));
	dc->SelectObject(pen);
	//CPoint rectangleCenter{ 0, 0 };
	CPoint dxDyPlusTempDxDy[4];
	for (int i = 0; i < 4; i++)
	{
		dxDyPlusTempDxDy[i] = CPoint(change.dxDy[i].x + change.tempDxDy[i].x, change.dxDy[i].y + change.tempDxDy[i].y);
	}
	selectedAreaPoints[0] = CPoint(shapeMove.tempDxDy.x + shapeCenterBeforRotate.x - 2 * sqrt(3) / 3 * size + dxDyPlusTempDxDy[0].x + dxDyPlusTempDxDy[3].x - (dxDyPlusTempDxDy[1].x + dxDyPlusTempDxDy[2].x), shapeMove.tempDxDy.y + shapeCenterBeforRotate.y + size + dxDyPlusTempDxDy[0].y + dxDyPlusTempDxDy[1].y - (dxDyPlusTempDxDy[2].y + dxDyPlusTempDxDy[3].y)); //leftbottom
	selectedAreaPoints[1] = CPoint(shapeMove.tempDxDy.x + shapeCenterBeforRotate.x + 2 * sqrt(3) / 3 * size + dxDyPlusTempDxDy[1].x + dxDyPlusTempDxDy[2].x - (dxDyPlusTempDxDy[0].x + dxDyPlusTempDxDy[3].x), shapeMove.tempDxDy.y + shapeCenterBeforRotate.y + size + dxDyPlusTempDxDy[0].y + dxDyPlusTempDxDy[1].y - (dxDyPlusTempDxDy[2].y + dxDyPlusTempDxDy[3].y)); //rightbottom
	selectedAreaPoints[2] = CPoint(shapeMove.tempDxDy.x + shapeCenterBeforRotate.x + 2 * sqrt(3) / 3 * size + dxDyPlusTempDxDy[1].x + dxDyPlusTempDxDy[2].x - (dxDyPlusTempDxDy[0].x + dxDyPlusTempDxDy[3].x), shapeMove.tempDxDy.y + shapeCenterBeforRotate.y - size + dxDyPlusTempDxDy[2].y + dxDyPlusTempDxDy[3].y - (dxDyPlusTempDxDy[0].y + dxDyPlusTempDxDy[1].y)); //righttop
	selectedAreaPoints[3] = CPoint(shapeMove.tempDxDy.x + shapeCenterBeforRotate.x - 2 * sqrt(3) / 3 * size + dxDyPlusTempDxDy[0].x + dxDyPlusTempDxDy[3].x - (dxDyPlusTempDxDy[1].x + dxDyPlusTempDxDy[2].x), shapeMove.tempDxDy.y + shapeCenterBeforRotate.y - size + dxDyPlusTempDxDy[2].y + dxDyPlusTempDxDy[3].y - (dxDyPlusTempDxDy[0].y + dxDyPlusTempDxDy[1].y)); //lefttop


	centerPoint23Bottom = CPoint((selectedAreaPoints[2].x - selectedAreaPoints[3].x) / 2 + selectedAreaPoints[3].x, selectedAreaPoints[2].y);
	if (selectedAreaPoints[0].y >= selectedAreaPoints[3].y)
	{
		centerPoint23Top = CPoint(centerPoint23Bottom.x, centerPoint23Bottom.y - LENGTH_OF_LINE_FOR_ELLIPSE_OF_ROTATE_TOOL);
		isReversedVar = false;
	}
	else
	{
		centerPoint23Top = CPoint(centerPoint23Bottom.x, centerPoint23Bottom.y + LENGTH_OF_LINE_FOR_ELLIPSE_OF_ROTATE_TOOL);
		isReversedVar = true;
	}
	firstPoint = centerPoint23Top;
	//CPoint triangle[4];
	shapePoints.resize(3);
	shapePoints[0] = CPoint(selectedAreaPoints[3].x + (selectedAreaPoints[2].x - selectedAreaPoints[3].x) / 2, selectedAreaPoints[3].y + (selectedAreaPoints[2].y - selectedAreaPoints[3].y) / 2); //top
	shapePoints[1] = selectedAreaPoints[0]; // left
	shapePoints[2] = selectedAreaPoints[1]; // right

	linkingPoints[0] = CPoint{ (shapePoints[2].x - shapePoints[1].x) / 2 + shapePoints[1].x, shapePoints[1].y };  //bottom
	linkingPoints[1] = CPoint{ (shapePoints[0].x - shapePoints[1].x) / 2 + shapePoints[1].x,  (shapePoints[0].y - shapePoints[1].y) / 2 + shapePoints[1].y }; // left
	linkingPoints[2] = CPoint{ (shapePoints[0].x - shapePoints[2].x) / 2 + shapePoints[2].x,  (shapePoints[0].y - shapePoints[2].y) / 2 + shapePoints[2].y }; // right
	linkingPoints[3] = shapePoints[0]; // top

	// create smaller triangle for smaller region
	//CPoint trianglePointsRgn[3];
	fillAreaPoints.resize(3);
	/*fillAreaPoints[0].x = shapePoints[0].x;
	fillAreaPoints[0].y = shapePoints[0].y + 1;

	fillAreaPoints[1].x = shapePoints[1].x + 1;
	fillAreaPoints[1].y = shapePoints[1].y - 1;

	fillAreaPoints[2].x = shapePoints[2].x - 1;
	fillAreaPoints[2].y = shapePoints[2].y - 1;*/

	if ((selectedAreaPoints[3].x < selectedAreaPoints[1].x) && (selectedAreaPoints[3].y < selectedAreaPoints[1].y))
	{
		fillAreaPoints[0] = CPoint{ shapePoints[0].x, shapePoints[0].y + 1 };
		fillAreaPoints[1] = CPoint{ shapePoints[1].x + 1, shapePoints[1].y - 1 };
		fillAreaPoints[2] = CPoint{ shapePoints[2].x - 1, shapePoints[2].y - 1 };
	}
	else if ((selectedAreaPoints[3].x > selectedAreaPoints[1].x) && (selectedAreaPoints[3].y < selectedAreaPoints[1].y))
	{
		fillAreaPoints[0] = CPoint{ shapePoints[0].x, shapePoints[0].y + 1 };
		fillAreaPoints[1] = CPoint{ shapePoints[1].x - 1, shapePoints[1].y - 1 };
		fillAreaPoints[2] = CPoint{ shapePoints[2].x + 1, shapePoints[2].y - 1 };
	}
	else if ((selectedAreaPoints[3].x > selectedAreaPoints[1].x) && (selectedAreaPoints[3].y > selectedAreaPoints[1].y))
	{
		fillAreaPoints[0] = CPoint{ shapePoints[0].x, shapePoints[0].y + 1 };
		fillAreaPoints[1] = CPoint{ shapePoints[1].x - 1, shapePoints[1].y + 1 };
		fillAreaPoints[2] = CPoint{ shapePoints[2].x + 1, shapePoints[2].y + 1 };
	}
	else
	{
		fillAreaPoints[0] = CPoint{ shapePoints[0].x, shapePoints[0].y + 1 };
		fillAreaPoints[1] = CPoint{ shapePoints[1].x + 1, shapePoints[1].y + 1 };
		fillAreaPoints[2] = CPoint{ shapePoints[2].x - 1, shapePoints[2].y + 1 };
	}
	


	//CRgn* triangleRgn = new CRgn;
	//triangleRgn->CreatePolygonRgn(&points[0], 4, ALTERNATE);
	//GetRgnBox(*triangleRgn, boxRect);

	/*recFromRgn[0] = CPoint(boxRect.TopLeft().x, boxRect.BottomRight().y);
	recFromRgn[1] = CPoint(boxRect.BottomRight());
	recFromRgn[2] = CPoint(boxRect.BottomRight().x, boxRect.TopLeft().y);
	recFromRgn[3] = CPoint(boxRect.TopLeft());*/



	for (int i = 0; i < 4; i++)
	{
		rotateAndMoveCoordinate(selectedAreaPoints[i], DRAW_METHOD);
		


		/*tempX = recFromRgn[i].x;
		tempY = recFromRgn[i].y;
		recFromRgn[i].x = round(tempX * cos(angleRad) - tempY * sin(angleRad));
		recFromRgn[i].y = round(tempX * sin(angleRad) + tempY * cos(angleRad));
		recFromRgn[i].x += centerOfShape.x + dx;
		recFromRgn[i].y += centerOfShape.y + dy;*/
	}


	for (int i = 0; i < 3; i++)
	{
		rotateAndMoveCoordinate(shapePoints[i], DRAW_METHOD);
	}

	for (int i = 0; i < 3; i++)
	{
		rotateAndMoveCoordinate(fillAreaPoints[i], DRAW_METHOD);
		
	}

	for (int pointNum = 0; pointNum < linkingPoints.size(); pointNum++)
	{
		rotateAndMoveCoordinate(linkingPoints[pointNum], DRAW_METHOD);
	}
	rotateAndMoveCoordinate(centerPoint23Bottom, DRAW_METHOD);
	rotateAndMoveCoordinate(centerPoint23Top, DRAW_METHOD);

	int tempXFP = firstPoint.x;
	int tempYFP = firstPoint.y;
	firstPoint.x = round(tempXFP * 1 - tempYFP * 0);
	firstPoint.y = round(tempXFP * 0 + tempYFP * 1);
	firstPoint.x += centerOfShape.x + dx;
	firstPoint.y += centerOfShape.y + dy;

	//rectangleReg->CreatePolygonRgn(points, 4, ALTERNATE);
	//GetRgnBox(*rectangleReg, boxRect);
	//dc->Rectangle(boxRect);

	/*points[0] = triangle[1];
	points[1] = triangle[2];
	points[2] = triangle[0];*/
	//if (isSelected)
	//{
	//	//dc->Ellipse(0, 0, 200, 200);
	//	for (int i = 0; i < 3; i++)
	//		dc->Ellipse(shapePoints[i].x - sizeOfPointToMoveAndChange, shapePoints[i].y - sizeOfPointToMoveAndChange, shapePoints[i].x + sizeOfPointToMoveAndChange, shapePoints[i].y + sizeOfPointToMoveAndChange);
	//}
	CRgn* triangleNewRgn = new CRgn;
	triangleNewRgn->CreatePolygonRgn(&fillAreaPoints[0], 3, ALTERNATE);
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
	dc->Polygon(&shapePoints[0], 3);
	dc->FillRgn(triangleNewRgn, triangleBrush);
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

	//dc->Polygon(points, 4);
	
	/*delete triangleNewRgn;
	delete triangleBrush;
	delete triangleRgn;
	delete pen;*/
	pen->DeleteObject();
	//triangleRgn->DeleteObject();
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
//	dSM.x = round(tempX * cos(-(angleRad)) - tempY * sin(-(angleRad)));
//	dSM.y = round(tempX * sin(-(angleRad)) + tempY * cos(-(angleRad)));
//}

bool IShape::getIsConnected(int numberOfPoint)
{
	if (numberOfPoint == FIRST_POINT_OF_LINE)
	{
		return connecting.isConnected.firstPointOfLine;
	}
	else if (numberOfPoint == SECOND_POINT_OF_LINE)
	{
		return connecting.isConnected.secondPointOfLine;
	}
	return false;
}

void IShape::setIsConnected(int numberOfPoint, bool isConnected)
{
	if (numberOfPoint == FIRST_POINT_OF_LINE)
	{
		connecting.isConnected.firstPointOfLine = isConnected;
	}
	else if (numberOfPoint == SECOND_POINT_OF_LINE)
	{
		connecting.isConnected.secondPointOfLine = isConnected;
	}
}


int IShape::getConnectedShapeConstID(int numberOfPoint)
{
	if (numberOfPoint == FIRST_POINT_OF_LINE)
	{
		return connecting.connectedShapeConstID.firstPointOfLine;
	}
	else if (numberOfPoint == SECOND_POINT_OF_LINE)
	{
		return connecting.connectedShapeConstID.secondPointOfLine;
	}
	return NULL;
}

void IShape::setConnectedShapeConstID(int numberOfPoint, int constID)
{
	if (numberOfPoint == FIRST_POINT_OF_LINE)
	{
		connecting.connectedShapeConstID.firstPointOfLine = constID;
	}
	else if (numberOfPoint == SECOND_POINT_OF_LINE)
	{
		connecting.connectedShapeConstID.secondPointOfLine = constID;
	}
}

int IShape::getNumberOfShapesPointForLines(int numberOfPoint)
{
	if (numberOfPoint == FIRST_POINT_OF_LINE)
	{
		return connecting.numberOfShapesPointForLines.firstPointOfLine;
	}
	else if (numberOfPoint == SECOND_POINT_OF_LINE)
	{
		return connecting.numberOfShapesPointForLines.secondPointOfLine;
	}
	return NULL;
}

void IShape::setNumberOfShapesPointForLines(int numberOfPoint, int numberOfShapesPoint)
{
	if (numberOfPoint == FIRST_POINT_OF_LINE)
	{
		connecting.numberOfShapesPointForLines.firstPointOfLine = numberOfShapesPoint;
	}
	else if (numberOfPoint == SECOND_POINT_OF_LINE)
	{
		connecting.numberOfShapesPointForLines.secondPointOfLine = numberOfShapesPoint;
	}
}


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

CPoint IShape::rotateAndMoveCoordinate(CPoint &point/*, Tools& toolIsUsed*/, int from)
{
	//if (toolIsUsed == Tools::shapeMove)
	{
		
		if (from == MOUSE_MOVE)
		{
			int tempX = point.x;
			int tempY = point.y;
			point.x = round(tempX * cos(-(angleRad)) - tempY * sin(-(angleRad)));
			point.y = round(tempX * sin(-(angleRad)) + tempY * cos(-(angleRad)));
			return point;
		}
		else if (from == LBUTTON_UP)
		{
			int tempX = point.x;
			int tempY = point.y;

			point.x = round(tempX * cos((angleRad)) - tempY * sin((angleRad)));
			point.y = round(tempX * sin((angleRad)) + tempY * cos((angleRad)));
			centerOfShape.x += point.x;
			centerOfShape.y += point.y;
			return point;
		}
		else if (from == DRAW_METHOD)
		{
			int tempX = point.x;
			int tempY = point.y;
			point.x = round(tempX * cos(angleRad) - tempY * sin(angleRad));
			point.y = round(tempX * sin(angleRad) + tempY * cos(angleRad));
			point.x += centerOfShape.x + dx;
			point.y += centerOfShape.y + dy;
		}
	}
	//else if (toolIsUsed == Tools::change)
	/*{
		if (from == MOUSE_MOVE)
		{
			int tempX = point.x;
			int tempY = point.y;
			point.x = round(tempX * cos(-(angleRad)) - tempY * sin(-(angleRad)));
			point.y = round(tempX * sin(-(angleRad)) + tempY * cos(-(angleRad)));
			return point;
		}
	}*/
}

void IShape::rotateShape(CPoint point)
{
	enum circleQuarter { first, second, third, fourth };
	circleQuarter tempEnum = first;
	if (point.x >= centerOfShape.x && point.y <= centerOfShape.x)
	{
		tempEnum = first;
	}
	else if (point.x > centerOfShape.x && point.y > centerOfShape.x)
	{
		tempEnum = second;
	}
	else if (point.x <= centerOfShape.x && point.y >= centerOfShape.x)
	{
		tempEnum = third;
	}
	else
	{
		tempEnum = fourth;
	}
	getFirstClickedPoint().y;
	//int temp2 = point.y - pDoc->getShapesVector()[s]->getFirstClickedPoint().y;
	array<double, 3> sides; // 0 - side from centerOfShape to firstClickedPoint; 1 - side form firstClickedPoint to point; 2 - the remaining side
	//sides[0] = sqrt(pow(pDoc->getShapesVector()[s]->getFirstClickedPoint().x - pDoc->getShapesVector()[s]->centerOfShape.x, 2) + pow(pDoc->getShapesVector()[s]->getFirstClickedPoint().y - pDoc->getShapesVector()[s]->centerOfShape.y, 2));
	sides[0] = sqrt(pow(firstPoint.x - centerOfShape.x, 2) + pow(firstPoint.y - centerOfShape.y, 2));
	
	sides[1] = sqrt(pow(firstPoint.x - point.x, 2) + pow(firstPoint.y - point.y, 2));
	sides[2] = sqrt(pow(centerOfShape.x - point.x, 2) + pow(centerOfShape.y - point.y, 2));
	/*sides[0] /= 100;
	sides[1] /= 100;
	sides[2] /= 100;*/

	double cosOfCenterAngle = (pow(sides[0], 2) + pow(sides[2], 2) - pow(sides[1], 2)) / ((2 * sides[0] * sides[2]));//using law of cosines

	double centerAngleRad = acos(cosOfCenterAngle);


	double centerAngleDegree = centerAngleRad * 180.0 / 3.14;

	if (tempEnum == third || tempEnum == fourth)
	{
		//pDoc->getShapesVector()[s]->angleRad = -centerAngleDegree * 3.14 / 180.0;
		centerAngleDegree = 360 - centerAngleDegree;
	}

	//int temp = point.y - pDoc->getShapesVector()[s]->lastY;

	//check if is shape reversed
	if (isReversed())
	{
		angleRad = -centerAngleDegree * 3.14 / 180.0;
	}
	else
	{
		angleRad = centerAngleDegree * 3.14 / 180.0;

	}
}

void IShape::moveChangeRotate(vector <IShape*>& shapes, Tools& toolIsUsed, CPoint point, bool& canBeUnselected, bool& shapeIsFound)
{
	//bool canBeUnselected = true; // is used for unselecting all shapes, when clicked on space place
	
	//bool isShapeFound = false; // if shape is found, then break loop
	if (type == ShapeType::ellipse || type == ShapeType::rectangle || type == ShapeType::triangle)
	{
		
		// check if is clicked on "rotate ellipse"
		if (getSelected() == true)
		{
			CPoint ellipseCenter = getPointForRotateTool(); // for convinience
			HRGN ellipseForRotateTool = CreateEllipticRgn(ellipseCenter.x - SIZE_OF_ELLIPSE_FOR_ROTATE_TOOL, ellipseCenter.y - SIZE_OF_ELLIPSE_FOR_ROTATE_TOOL,
				ellipseCenter.x + SIZE_OF_ELLIPSE_FOR_ROTATE_TOOL, ellipseCenter.y + SIZE_OF_ELLIPSE_FOR_ROTATE_TOOL); // create region for "rotate tool ellipse"
			if (PtInRegion(ellipseForRotateTool, point.x, point.y))
			{
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
	else if (type == ShapeType::basicLine || type == ShapeType::rightLine || type == ShapeType::leftLine || type == ShapeType::doubleLine)
	{

		//bool breakLoop = false; // bool variable that is need for loop control
		// check if clicked on points that changing the size of shape
		//canBeUnselected = false;
		if (isClickedPointForChange(point))
		{
			shapeIsFound = true;
			toolIsUsed = Tools::change;
			//canBeUnselected = true;
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
		
		if (shapeIsFound) return;
	}
	//return true;
}

void IShape::normalizeShape()
{
	if (isSelected)
	{


		//pDoc->getShapesVector()[s]->isNormalized = true;
		angleRad = 0;
		CPoint tmp[4];
		if (type == ShapeType::triangle)
		{
			for (int i = 0; i < 4; i++)
			{
				tmp[i] = selectedAreaPoints[i];
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
	if (numberOfPointOfLine == FIRST_POINT_OF_LINE)
	{
		connecting.isConnected.firstPointOfLine = true;
		connecting.connectedShapeConstID.firstPointOfLine = shapeConstID;
		connecting.numberOfShapesPointForLines.firstPointOfLine = numberOfPointForLines;

	}
	else if (numberOfPointOfLine == SECOND_POINT_OF_LINE)
	{
		connecting.isConnected.secondPointOfLine = true;
		connecting.connectedShapeConstID.secondPointOfLine = shapeConstID;
		connecting.numberOfShapesPointForLines.secondPointOfLine = numberOfPointForLines;

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
			if (shapes[shapeNum]->type != ShapeType::basicLine && shapes[shapeNum]->type != ShapeType::rightLine 
				&& shapes[shapeNum]->type != ShapeType::leftLine && shapes[shapeNum]->type != ShapeType::doubleLine)
			{
				if (shapes[shapeNum]->constID == connecting.connectedShapeConstID.firstPointOfLine)
				{
					setCoordinateForChange(FIRST_POINT_OF_LINE, shapes[shapeNum]->getPointForLine(connecting.numberOfShapesPointForLines.firstPointOfLine));
					//cout << connecting.numberOfShapesPointForLines.firstPointOfLine << endl;
					//cout << getCoordinateForChange(0).x << " " << getCoordinateForChange(0).y << endl;
					
				}
			}
		}
	}
	if (connecting.isConnected.secondPointOfLine)
	{
		for (int shapeNum = 0; shapeNum < shapes.size(); shapeNum++)
		{
			if (shapes[shapeNum]->type != ShapeType::basicLine && shapes[shapeNum]->type != ShapeType::rightLine
				&& shapes[shapeNum]->type != ShapeType::leftLine && shapes[shapeNum]->type != ShapeType::doubleLine)
			{
				if (shapes[shapeNum]->constID == connecting.connectedShapeConstID.secondPointOfLine)
				{
					setCoordinateForChange(SECOND_POINT_OF_LINE, shapes[shapeNum]->getPointForLine(connecting.numberOfShapesPointForLines.secondPointOfLine));

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
		
			connecting.isConnected.firstPointOfLine = false;
			connecting.connectedShapeConstID.firstPointOfLine = -1;
			connecting.numberOfShapesPointForLines.firstPointOfLine = -1;
		}

		
	}
	else if (numberOfPointOfLine == SECOND_POINT_OF_LINE)
	{
		if (connecting.connectedShapeConstID.secondPointOfLine == shapeConstID) // disconnect not always (if id of connected Shape == shape constID to disconnect)
		{
			connecting.isConnected.secondPointOfLine = false;
			connecting.connectedShapeConstID.secondPointOfLine = -1;
			connecting.numberOfShapesPointForLines.secondPointOfLine = -1;
		}
		

		
	}
}

void IShape::setShapeID()
{
	IDs.insert(-1);
	bool isNotFound = false;
	for (int i = 0; i < countOfShape + 10; i++)
	{
		for (auto it = IDs.begin(); it != IDs.end(); it++)
		{
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
}


void IShape::setShapeName()
{
	CString str = NULL;
	str.Format(_T("-1"));
	names.insert(str);
	bool isNotFound = false;
	switch (type)
	{
		case ShapeType::ellipse:
		{
			for (int i = 0; i < countOfShape + 10; i++)
			{
				for (auto it = names.begin(); it != names.end(); it++)
				{

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
			break;
		}
		case ShapeType::rectangle:
		{
			for (int i = 0; i < countOfShape + 10; i++)
			{
				for (auto it = names.begin(); it != names.end(); it++)
				{

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
			break;
		}
		case ShapeType::triangle:
		{
			for (int i = 0; i < countOfShape + 10; i++)
			{
				for (auto it = names.begin(); it != names.end(); it++)
				{

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
			break;
		}
		case ShapeType::basicLine:
		{
			for (int i = 0; i < countOfShape + 10; i++)
			{
				for (auto it = names.begin(); it != names.end(); it++)
				{

					name.Format(_T("basicLine%d"), i);

					auto pos = names.find(name);
					if (pos == names.end())
					{
						isNotFound = true;
						name.Format(_T("basicLine%d"), i);
						names.insert(name);
						break;
					}

				}
				if (isNotFound)
					break;
			}
			break;
		}
		case ShapeType::rightLine:
		{
			for (int i = 0; i < countOfShape + 10; i++)
			{
				for (auto it = names.begin(); it != names.end(); it++)
				{

					name.Format(_T("rightLine%d"), i);

					auto pos = names.find(name);
					if (pos == names.end())
					{
						isNotFound = true;
						name.Format(_T("rightLine%d"), i);
						names.insert(name);
						break;
					}

				}
				if (isNotFound)
					break;
			}
			break;
		}
		case ShapeType::leftLine:
		{
			for (int i = 0; i < countOfShape + 10; i++)
			{
				for (auto it = names.begin(); it != names.end(); it++)
				{

					name.Format(_T("leftLine%d"), i);

					auto pos = names.find(name);
					if (pos == names.end())
					{
						isNotFound = true;
						name.Format(_T("leftLine%d"), i);
						names.insert(name);
						break;
					}

				}
				if (isNotFound)
					break;
			}
			break;
		}
		case ShapeType::doubleLine:
		{
			for (int i = 0; i < countOfShape + 10; i++)
			{
				for (auto it = names.begin(); it != names.end(); it++)
				{

					name.Format(_T("doubleLine%d"), i);

					auto pos = names.find(name);
					if (pos == names.end())
					{
						isNotFound = true;
						name.Format(_T("doubleLine%d"), i);
						names.insert(name);
						break;
					}

				}
				if (isNotFound)
					break;
			}
			break;
		}
	}
}

IShape::~IShape()
{
	IShape::IDs.erase(ID); // erase ID because ID won't exist
	IShape::names.erase(name);
}


void Line::draw(CDC* dc)
{

	//updateLineConnection(getShapesVector());
	//dc->Polygon(&tempLineRectRgn1[0], tempLineRectRgn1.size());
	//dc->Polygon(&tempLineRectRgn2[0], tempLineRectRgn2.size());

	if (isSelected)
	{
		for (int pointNum = 0; pointNum < pointsOfLine.size(); pointNum++)
		{
			dc->Ellipse(pointsOfLine[pointNum].x - SIZE_OF_POINT_FOR_CHANGE + change.tempDxDy[pointNum].x + change.dxDy[pointNum].x, pointsOfLine[pointNum].y + change.tempDxDy[pointNum].y + - SIZE_OF_POINT_FOR_CHANGE + change.dxDy[pointNum].y,
				pointsOfLine[pointNum].x + change.tempDxDy[pointNum].x + SIZE_OF_POINT_FOR_CHANGE + change.dxDy[pointNum].x, pointsOfLine[pointNum].y + change.tempDxDy[pointNum].y + SIZE_OF_POINT_FOR_CHANGE+ change.dxDy[pointNum].y);
		}
	}
	dc->MoveTo(CPoint(pointsOfLine[0].x + change.tempDxDy[0].x + change.dxDy[0].x, pointsOfLine[0].y + change.tempDxDy[0].y+ change.dxDy[0].y));
	dc->LineTo(CPoint(pointsOfLine[1].x + change.tempDxDy[1].x + change.dxDy[1].x, pointsOfLine[1].y + change.tempDxDy[1].y+ change.dxDy[1].y));

	if (type == ShapeType::rightLine)
	{
		//if (pointsOfLine[0] != pointsOfLine[1])
		{
			CPoint firstPointOfArrow = NULL;
			CPoint secondPointOfArrow = NULL;
			getPointsOfArrow(RIGHT_LINE, firstPointOfArrow, secondPointOfArrow);
			dc->MoveTo(pointsOfLine[SECOND_POINT_OF_LINE] + change.tempDxDy[SECOND_POINT_OF_LINE]);
			dc->LineTo(firstPointOfArrow);
			dc->MoveTo(pointsOfLine[SECOND_POINT_OF_LINE] + change.tempDxDy[SECOND_POINT_OF_LINE]);
			dc->LineTo(secondPointOfArrow);

		}
		
	}
	else if (type == ShapeType::leftLine)
	{
		CPoint firstPointOfArrow = NULL;
		CPoint secondPointOfArrow = NULL;
		getPointsOfArrow(LEFT_LINE, firstPointOfArrow, secondPointOfArrow);
		dc->MoveTo(pointsOfLine[FIRST_POINT_OF_LINE] + change.tempDxDy[FIRST_POINT_OF_LINE]);
		dc->LineTo(firstPointOfArrow);
		dc->MoveTo(pointsOfLine[FIRST_POINT_OF_LINE] + change.tempDxDy[FIRST_POINT_OF_LINE]);
		dc->LineTo(secondPointOfArrow);
	}
	else if (type == ShapeType::doubleLine)
	{
		CPoint firstPointOfArrow = NULL;
		CPoint secondPointOfArrow = NULL;
		
		// points for right line
		getPointsOfArrow(RIGHT_LINE, firstPointOfArrow, secondPointOfArrow);
		dc->MoveTo(pointsOfLine[SECOND_POINT_OF_LINE] + change.tempDxDy[SECOND_POINT_OF_LINE]);
		dc->LineTo(firstPointOfArrow);
		dc->MoveTo(pointsOfLine[SECOND_POINT_OF_LINE] + change.tempDxDy[SECOND_POINT_OF_LINE]);
		dc->LineTo(secondPointOfArrow);

		// points for left line
		getPointsOfArrow(LEFT_LINE, firstPointOfArrow, secondPointOfArrow);
		dc->MoveTo(pointsOfLine[FIRST_POINT_OF_LINE] + change.tempDxDy[FIRST_POINT_OF_LINE]);
		dc->LineTo(firstPointOfArrow);
		dc->MoveTo(pointsOfLine[FIRST_POINT_OF_LINE] + change.tempDxDy[FIRST_POINT_OF_LINE]);
		dc->LineTo(secondPointOfArrow);
		
	}

	//draw all lines
	//for (int i=0; i<pDoc->lines.size(); i++)
	//{
	//	CPen* linePen;
	//	pDoc->lines[i]->lR = GetRValue(pDoc->lines[i]->lineColor);
	//	pDoc->lines[i]->lG = GetGValue(pDoc->lines[i]->lineColor);
	//	pDoc->lines[i]->lB = GetBValue(pDoc->lines[i]->lineColor);
	//	linePen = new CPen(pDoc->lines[i]->lineType, pDoc->lines[i]->lineSize, RGB(pDoc->lines[i]->lR, pDoc->lines[i]->lG, pDoc->lines[i]->lB));
	//	CPoint firstPoint;
	//	CPoint secondPoint;
	//	int firstID = pDoc->lines[i]->FirstShapeConstID;
	//	int secondID = pDoc->lines[i]->SecondShapeConstID;
	//	bool found = false;
	//	for (auto s : pDoc->getShapesVector())
	//	{
	//		CString d;
	//		d.Format(_T("%d"), s->constID);
	//		//AfxMessageBox(d);
	//		if (s->constID == firstID)
	//		{
	//			found = true;
	//			firstPoint = s->centerOfShape;
	//			int temp_dSM_x = s->dSM.x;
	//			int temp_dSM_y = s->dSM.y;
	//			int temp2_dSM_x = temp_dSM_x;
	//			int temp2_dSM_y = temp_dSM_y;
	//			temp_dSM_x = round(temp2_dSM_x * cos((s->angleRad)) - temp2_dSM_y * sin((s->angleRad)));
	//			temp_dSM_y = round(temp2_dSM_x * sin((s->angleRad)) + temp2_dSM_y * cos((s->angleRad)));

	//			firstPoint.x += temp_dSM_x + IShape::dx;
	//			firstPoint.y += temp_dSM_y + IShape::dy;
	//			//Invalidate();
	//			break;
	//		}
	//	}
	//	if (!found)
	//	{
	//		pDoc->lines[i]->first_ID_not_excist = true;
	//	}
	//	found = false;
	//	for (auto s : pDoc->getShapesVector())
	//	{
	//		if (s->constID == secondID)
	//		{
	//			secondPoint = s->centerOfShape;
	//			found = true;
	//			int temp_dSM_x = s->dSM.x;
	//			int temp_dSM_y = s->dSM.y;
	//			int temp2_dSM_x = temp_dSM_x;
	//			int temp2_dSM_y = temp_dSM_y;
	//			temp_dSM_x = round(temp2_dSM_x * cos((s->angleRad)) - temp2_dSM_y * sin((s->angleRad)));
	//			temp_dSM_y = round(temp2_dSM_x * sin((s->angleRad)) + temp2_dSM_y * cos((s->angleRad)));
	//			secondPoint.x += temp_dSM_x + IShape::dx;
	//			secondPoint.y += temp_dSM_y + IShape::dy;
	//			break;
	//		}
	//	}
	//	if (!found)
	//	{
	//		pDoc->lines[i]->second_ID_not_exceist = true;
	//	}
	//	bool deleteThisLine = pDoc->lines[i]->first_ID_not_excist || pDoc->lines[i]->second_ID_not_exceist;
	//	if (deleteThisLine)
	//	{
	//		
	//		
	//		delete pDoc->lines[i];
	//		pDoc->lines.erase(pDoc->lines.begin() + i);
	//		CString str;
	//		int size = pDoc->lines.size();
	//		str.Format(_T("Size of lines vector: %d"), size);
	//		//AfxMessageBox(str);
	//		break;
	//	}
	//	m_dc.SelectObject(linePen);
	//	m_dc.MoveTo(firstPoint);
	//	m_dc.LineTo(secondPoint);
	//	
	//	if (pDoc->lines[i]->type == LineType::Right) // draw right line
	//	{
	//		CPoint centerOfArrowGround = CPoint(firstPoint.x + (secondPoint.x - firstPoint.x) / 1.07, firstPoint.y + (secondPoint.y - firstPoint.y) / 1.07);
	//		//m_dc.Ellipse(centerOfArrowGround.x - 5, centerOfArrowGround.y - 5, centerOfArrowGround.x + 5, centerOfArrowGround.y + 5);
	//		double angleOfTriangleDeg = 12;
	//		double angleOfTriangleRad = angleOfTriangleDeg * 3.14 / 180.f;
	//		double angleBigTriangleRad;
	//		double angleBigTriangleDeg;

	//		double lengthOFLeg;
	//		double lengthOfHypotenuse;
	//		CPoint secondLegPoint = CPoint(centerOfArrowGround.x, firstPoint.y);
	//		CPoint firstLegPoint = CPoint(firstPoint.x, firstPoint.y);
	//		lengthOfHypotenuse = sqrt(pow(centerOfArrowGround.x - firstLegPoint.x, 2) + pow(centerOfArrowGround.y - firstLegPoint.y, 2));
	//		CString dbug;


	//		lengthOFLeg = sqrt(pow(secondLegPoint.x - firstLegPoint.x, 2) + pow(secondLegPoint.y - firstLegPoint.y, 2));
	//		angleBigTriangleRad = acos(lengthOFLeg / lengthOfHypotenuse);
	//		angleBigTriangleDeg = angleBigTriangleRad * 180.0f / 3.14;
	//		//dbug.Format(_T("Length of hyp: %g, leg: %g, deg: %g"), lengthOfHypotenuse, lengthOFLeg, angleBigTriangleDeg);

	//		double lengthOfArrow = sqrt(pow(centerOfArrowGround.x - secondPoint.x, 2) + pow(centerOfArrowGround.y - secondPoint.y, 2));
	//		double lengthOfPerpendicular = lengthOfArrow * tan(angleOfTriangleRad);
	//		double legX = cos(90 * 3.14 / 180.f - angleBigTriangleRad) * lengthOfPerpendicular;
	//		double legY = sin(90 * 3.14 / 180.f - angleBigTriangleRad) * lengthOfPerpendicular;
	//		if (centerOfArrowGround.x - firstPoint.x > 0 && centerOfArrowGround.y - firstPoint.y < 0 || centerOfArrowGround.x - firstPoint.x < 0 && centerOfArrowGround.y - firstPoint.y > 0)
	//		{
	//			//continue;
	//			//AfxMessageBox(_T("True"));
	//		}
	//		else
	//		{
	//			legX = -legX;
	//			//continue;
	//		}

	//		CPoint firstPointOfArrow = CPoint(centerOfArrowGround.x - legX, centerOfArrowGround.y - legY);
	//		CPoint secondPointOfArrow = CPoint(centerOfArrowGround.x + legX, centerOfArrowGround.y + legY);
	//		dbug.Format(_T("legX: %g, legY: %g"), legX, legY);

	//		if (lengthOFLeg > 80 && lengthOFLeg < 120)
	//		{
	//			//AfxMessageBox(dbug);
	//		}

	//		//m_dc.Ellipse(firstLegPoint.x - 5, firstLegPoint.y - 5, firstLegPoint.x + 5, firstLegPoint.y + 5);
	//		//m_dc.Ellipse(firstPointOfArrow.x - 5, firstPointOfArrow.y - 5, firstPointOfArrow.x + 5, firstPointOfArrow.y + 5);
	//		//m_dc.Ellipse(secondPointOfArrow.x - 5, secondPointOfArrow.y - 5, secondPointOfArrow.x + 5, secondPointOfArrow.y + 5);
	//		//m_dc.Ellipse(secondLegPoint.x - 5, secondLegPoint.y - 5, secondLegPoint.x + 5, secondLegPoint.y + 5);
	//		m_dc.MoveTo(secondPoint);
	//		m_dc.LineTo(firstPointOfArrow);
	//		m_dc.MoveTo(secondPoint);
	//		m_dc.LineTo(secondPointOfArrow);

	//		//lenghtOfHypotenuse = 
	//		//m_dc.Ellipse(centerOfArrowGround.x - 5, centerOfArrowGround.y - 5, centerOfArrowGround.x + 5, centerOfArrowGround.y + 5);
	//		/*int angleDegree = 45;
	//		double angleRadian = (double)angleDegree * 3.14 / 180.0f;
	//		double tempX = (centerOfArrowGround.x - secondPoint.x) * tan(angleRadian);
	//		double tempY = (centerOfArrowGround.y - secondPoint.y) * tan(angleRadian);
	//		CPoint leftPointOfArrowGround = CPoint(centerOfArrowGround.x, centerOfArrowGround.y + 20);
	//		m_dc.Ellipse(leftPointOfArrowGround.x - 5, leftPointOfArrowGround.y - 5, leftPointOfArrowGround.x + 5, leftPointOfArrowGround.y + 5);*/
	//		
	//	}

	//	// draw left line
	//	else if (pDoc->lines[i]->type == LineType::Left)
	//	{
	//		CPoint centerOfArrowGround = CPoint(secondPoint.x - (secondPoint.x - firstPoint.x) / 1.07, secondPoint.y - (secondPoint.y - firstPoint.y) / 1.07);
	//		//m_dc.Ellipse(centerOfArrowGround.x - 5, centerOfArrowGround.y - 5, centerOfArrowGround.x + 5, centerOfArrowGround.y + 5);
	//		double angleOfTriangleDeg = 12;
	//		double angleOfTriangleRad = angleOfTriangleDeg * 3.14 / 180.f;
	//		double angleBigTriangleRad;
	//		double angleBigTriangleDeg;

	//		double lengthOFLeg;
	//		double lengthOfHypotenuse;
	//		CPoint firstLegPoint = CPoint(firstPoint.x, firstPoint.y);
	//		CPoint secondLegPoint = CPoint(centerOfArrowGround.x, firstPoint.y);
	//		lengthOfHypotenuse = sqrt(pow(centerOfArrowGround.x - firstLegPoint.x, 2) + pow(centerOfArrowGround.y - firstLegPoint.y, 2));
	//		CString dbug;


	//		lengthOFLeg = sqrt(pow(secondLegPoint.x - firstLegPoint.x, 2) + pow(secondLegPoint.y - firstLegPoint.y, 2));
	//		angleBigTriangleRad = acos(lengthOFLeg / lengthOfHypotenuse);
	//		angleBigTriangleDeg = angleBigTriangleRad * 180.0f / 3.14;
	//		dbug.Format(_T("Length of hyp: %g, leg: %g, deg: %g"), lengthOfHypotenuse, lengthOFLeg, angleBigTriangleDeg);
	//		//AfxMessageBox(dbug);

	//		double lengthOfArrow = sqrt(pow(centerOfArrowGround.x - firstPoint.x, 2) + pow(centerOfArrowGround.y - firstPoint.y, 2));
	//		double lengthOfPerpendicular = lengthOfArrow * tan(angleOfTriangleRad);
	//		double legX = cos(90 * 3.14 / 180.f - angleBigTriangleRad) * lengthOfPerpendicular;
	//		double legY = sin(90 * 3.14 / 180.f - angleBigTriangleRad) * lengthOfPerpendicular;
	//		if (centerOfArrowGround.x - firstPoint.x > 0 && centerOfArrowGround.y - firstPoint.y < 0 || centerOfArrowGround.x - firstPoint.x < 0 && centerOfArrowGround.y - firstPoint.y > 0)
	//		{
	//			//continue;
	//			//AfxMessageBox(_T("True"));
	//		}
	//		else
	//		{
	//			legX = -legX;
	//			//continue;
	//		}

	//		CPoint firstPointOfArrow = CPoint(centerOfArrowGround.x - legX, centerOfArrowGround.y - legY);
	//		CPoint secondPointOfArrow = CPoint(centerOfArrowGround.x + legX, centerOfArrowGround.y + legY);

	//		m_dc.MoveTo(firstPoint);
	//		m_dc.LineTo(firstPointOfArrow);
	//		m_dc.MoveTo(firstPoint);
	//		m_dc.LineTo(secondPointOfArrow);


	//	}
	//	else if (pDoc->lines[i]->type == LineType::Double) // draw double line
	//	{

	//	//drawing first arrow
	//	CPoint centerOfArrowGround = CPoint(firstPoint.x + (secondPoint.x - firstPoint.x) / 1.07, firstPoint.y + (secondPoint.y - firstPoint.y) / 1.07);
	//	//m_dc.Ellipse(centerOfArrowGround.x - 5, centerOfArrowGround.y - 5, centerOfArrowGround.x + 5, centerOfArrowGround.y + 5);
	//	double angleOfTriangleDeg = 12;
	//	double angleOfTriangleRad = angleOfTriangleDeg * 3.14 / 180.f;
	//	double angleBigTriangleRad;
	//	double angleBigTriangleDeg;

	//	double lengthOFLeg;
	//	double lengthOfHypotenuse;
	//	CPoint secondLegPoint = CPoint(centerOfArrowGround.x, firstPoint.y);
	//	CPoint firstLegPoint = CPoint(firstPoint.x, firstPoint.y);
	//	lengthOfHypotenuse = sqrt(pow(centerOfArrowGround.x - firstLegPoint.x, 2) + pow(centerOfArrowGround.y - firstLegPoint.y, 2));
	//	CString dbug;


	//	lengthOFLeg = sqrt(pow(secondLegPoint.x - firstLegPoint.x, 2) + pow(secondLegPoint.y - firstLegPoint.y, 2));
	//	angleBigTriangleRad = acos(lengthOFLeg / lengthOfHypotenuse);
	//	angleBigTriangleDeg = angleBigTriangleRad * 180.0f / 3.14;
	//	//dbug.Format(_T("Length of hyp: %g, leg: %g, deg: %g"), lengthOfHypotenuse, lengthOFLeg, angleBigTriangleDeg);

	//	double lengthOfArrow = sqrt(pow(centerOfArrowGround.x - secondPoint.x, 2) + pow(centerOfArrowGround.y - secondPoint.y, 2));
	//	double lengthOfPerpendicular = lengthOfArrow * tan(angleOfTriangleRad);
	//	double legX = cos(90 * 3.14 / 180.f - angleBigTriangleRad) * lengthOfPerpendicular;
	//	double legY = sin(90 * 3.14 / 180.f - angleBigTriangleRad) * lengthOfPerpendicular;
	//	if (centerOfArrowGround.x - firstPoint.x > 0 && centerOfArrowGround.y - firstPoint.y < 0 || centerOfArrowGround.x - firstPoint.x < 0 && centerOfArrowGround.y - firstPoint.y > 0)
	//	{
	//		//continue;
	//		//AfxMessageBox(_T("True"));
	//	}
	//	else
	//	{
	//		legX = -legX;
	//		//continue;
	//	}

	//	CPoint firstPointOfArrow = CPoint(centerOfArrowGround.x - legX, centerOfArrowGround.y - legY);
	//	CPoint secondPointOfArrow = CPoint(centerOfArrowGround.x + legX, centerOfArrowGround.y + legY);
	//	dbug.Format(_T("legX: %g, legY: %g"), legX, legY);

	//	if (lengthOFLeg > 80 && lengthOFLeg < 120)
	//	{
	//		//AfxMessageBox(dbug);
	//	}


	//	m_dc.MoveTo(secondPoint);
	//	m_dc.LineTo(firstPointOfArrow);
	//	m_dc.MoveTo(secondPoint);
	//	m_dc.LineTo(secondPointOfArrow);

	//




	//	//drawing second arrow
	//	centerOfArrowGround = CPoint(secondPoint.x - (secondPoint.x - firstPoint.x) / 1.07, secondPoint.y - (secondPoint.y - firstPoint.y) / 1.07);

	//	angleOfTriangleDeg = 12;
	//	angleOfTriangleRad = angleOfTriangleDeg * 3.14 / 180.f;

	//	firstLegPoint = CPoint(firstPoint.x, firstPoint.y);
	//	secondLegPoint = CPoint(centerOfArrowGround.x, firstPoint.y);
	//	lengthOfHypotenuse = sqrt(pow(centerOfArrowGround.x - firstLegPoint.x, 2) + pow(centerOfArrowGround.y - firstLegPoint.y, 2));


	//	lengthOFLeg = sqrt(pow(secondLegPoint.x - firstLegPoint.x, 2) + pow(secondLegPoint.y - firstLegPoint.y, 2));
	//	angleBigTriangleRad = acos(lengthOFLeg / lengthOfHypotenuse);
	//	angleBigTriangleDeg = angleBigTriangleRad * 180.0f / 3.14;
	//	dbug.Format(_T("Length of hyp: %g, leg: %g, deg: %g"), lengthOfHypotenuse, lengthOFLeg, angleBigTriangleDeg);


	//	lengthOfArrow = sqrt(pow(centerOfArrowGround.x - firstPoint.x, 2) + pow(centerOfArrowGround.y - firstPoint.y, 2));
	//	lengthOfPerpendicular = lengthOfArrow * tan(angleOfTriangleRad);
	//	legX = cos(90 * 3.14 / 180.f - angleBigTriangleRad) * lengthOfPerpendicular;
	//	legY = sin(90 * 3.14 / 180.f - angleBigTriangleRad) * lengthOfPerpendicular;
	//	if (centerOfArrowGround.x - firstPoint.x > 0 && centerOfArrowGround.y - firstPoint.y < 0 || centerOfArrowGround.x - firstPoint.x < 0 && centerOfArrowGround.y - firstPoint.y > 0)
	//	{
	//		//continue;
	//		//AfxMessageBox(_T("True"));
	//	}
	//	else
	//	{
	//		legX = -legX;
	//		//continue;
	//	}

	//	firstPointOfArrow = CPoint(centerOfArrowGround.x - legX, centerOfArrowGround.y - legY);
	//	secondPointOfArrow = CPoint(centerOfArrowGround.x + legX, centerOfArrowGround.y + legY);

	//	m_dc.MoveTo(firstPoint);
	//	m_dc.LineTo(firstPointOfArrow);
	//	m_dc.MoveTo(firstPoint);
	//	m_dc.LineTo(secondPointOfArrow);


	//	linePen->DeleteObject();
 //}
	//}

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
		DeleteObject(lineRgnHor);
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

void Line::getPointsOfArrow(int forLineType, CPoint& firstPointOfArrow, CPoint& secondPointOfArrow)
{
	int firstNumber = NULL;
	int secondNumber = NULL;
	if (forLineType == RIGHT_LINE)
	{
		firstNumber = FIRST_POINT_OF_LINE;
		secondNumber = SECOND_POINT_OF_LINE;
	}
	else if(forLineType == LEFT_LINE)
	{
		firstNumber = SECOND_POINT_OF_LINE;
		secondNumber = FIRST_POINT_OF_LINE;
	}
	CPoint centerOfArrowGround = CPoint(pointsOfLine[firstNumber].x + change.tempDxDy[firstNumber].x + (pointsOfLine[secondNumber].x + change.tempDxDy[secondNumber].x - (pointsOfLine[firstNumber].x + change.tempDxDy[firstNumber].x)) / 1.07, pointsOfLine[firstNumber].y + change.tempDxDy[firstNumber].y + (pointsOfLine[secondNumber].y + change.tempDxDy[secondNumber].y - (pointsOfLine[firstNumber].y + change.tempDxDy[firstNumber].y)) / 1.07);

	double angleOfArrowDeg = ANGLE_OF_ARROW_DEG;
	double angleOfArrowRad = degToRad(angleOfArrowDeg);
	double angleOfTriangleRad = NULL;
	double lengthOfLeg = NULL;
	double lengthOfHypotenuse = NULL;
	CPoint secondLegPoint = CPoint(centerOfArrowGround.x, pointsOfLine[firstNumber].y + change.tempDxDy[firstNumber].y);
	CPoint firstLegPoint = CPoint(pointsOfLine[firstNumber].x + change.tempDxDy[firstNumber].x, pointsOfLine[firstNumber].y + change.tempDxDy[firstNumber].y);
	lengthOfHypotenuse = sqrt(pow(centerOfArrowGround.x - firstLegPoint.x, 2) + pow(centerOfArrowGround.y - firstLegPoint.y, 2));
	//CString dbug;


	lengthOfLeg = sqrt(pow(secondLegPoint.x - firstLegPoint.x, 2) + pow(secondLegPoint.y - firstLegPoint.y, 2));
	angleOfTriangleRad = acos(lengthOfLeg / lengthOfHypotenuse);
	//angleOfTriangleDeg = radToDeg(angleOfTriangleRad);

	double lengthOfArrow = sqrt(pow(centerOfArrowGround.x - (pointsOfLine[secondNumber].x + change.tempDxDy[secondNumber].x), 2) + pow(centerOfArrowGround.y - (pointsOfLine[secondNumber].y + change.tempDxDy[secondNumber].y), 2));
	double lengthOfPerpendicular = lengthOfArrow * tan(angleOfArrowRad);
	double legX = cos(90 * 3.14 / 180.0 - angleOfTriangleRad) * lengthOfPerpendicular;
	double legY = sin(90 * 3.14 / 180.0 - angleOfTriangleRad) * lengthOfPerpendicular;
	if(isnan(legX) || isnan(legY))
	{
		legX = 0;
		legY = 0;
	}
	if (!(centerOfArrowGround.x - (pointsOfLine[firstNumber].x + change.tempDxDy[firstNumber].x) > 0 && centerOfArrowGround.y - (pointsOfLine[firstNumber].y + change.tempDxDy[firstNumber].y) < 0 || centerOfArrowGround.x - (pointsOfLine[firstNumber].x + change.tempDxDy[firstNumber].x) < 0 && centerOfArrowGround.y - (pointsOfLine[firstNumber].y + change.tempDxDy[firstNumber].y) > 0))
	{
		legX = -legX;
	}

	firstPointOfArrow = CPoint(centerOfArrowGround.x - legX, centerOfArrowGround.y - legY);
	secondPointOfArrow = CPoint(centerOfArrowGround.x + legX, centerOfArrowGround.y + legY);
	

}

