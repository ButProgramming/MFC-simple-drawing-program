#include "pch.h"
#include "Shape.h"

int IShape::dx = 0;
int IShape::dy = 0;
int IShape::sizeOfPointToMoveAndChange = 3;

EllipseShape::EllipseShape(CPoint centerOfShape, bool isNormalized, int size, ShapeType type)
{
	//type = ShapeType::ellipse;
	this->type = type;
	this->size = size;
	this->centerOfShape = centerOfShape;
	boxRect.CenterPoint() = centerOfShape;
	this->isNormalized = isNormalized;
	//this->typeOfShape = typeOfShape;
}

RectangleShape::RectangleShape(CPoint centerOfShape, bool isNormalized, int size, ShapeType type)
{
	//type = ShapeType::rectangle;
	this->type = type;
	this->size = size;
	this->centerOfShape = centerOfShape;
	this->isNormalized = isNormalized;
	//this->typeOfShape = typeOfShape;
}

TriangleShape::TriangleShape(CPoint centerOfShape, bool isNormalized, int size, ShapeType type)
{
	this->type = type;
	this->size = size;
	this->centerOfShape = centerOfShape;
	this->isNormalized = isNormalized;
	//this->typeOfShape = typeOfShape;
}

void EllipseShape::draw(CDC* dc)
{
	//size = 100;
	if (!isSelected)
		pen = new CPen(PS_SOLID, 4, RGB(255, 0, 0));
	else if (isSelected)
		pen = new CPen(PS_SOLID, 4, RGB(0, 0, 0));
	dc->SelectObject(pen);
	CPoint circleCenter{ 0, 0 };

	//points[0] = CPoint(centerOfShape.x + dx - size + dx_dy[0].x + dx_dy_temp[0].x, centerOfShape.y + dy - size + dx_dy[0].y + dx_dy_temp[0].y); // left top
	//points[1] = CPoint(centerOfShape.x + dx + size + dx_dy[1].x + dx_dy_temp[1].x, centerOfShape.y + dy - size + dx_dy[1].y + dx_dy_temp[1].y); // right top
	//points[2] = CPoint(centerOfShape.x + dx + size + dx_dy[2].x + dx_dy_temp[2].x, centerOfShape.y + dy + size + dx_dy[2].y + dx_dy_temp[2].y); //right bottom
	//points[3] = CPoint(centerOfShape.x + dx - size + dx_dy[3].x + dx_dy_temp[3].x, centerOfShape.y + dy + size + dx_dy[3].y + dx_dy_temp[3].y); // left bottom

	//points[0] = CPoint(circleCenter.x - size + dx_dy[0].x + dx_dy_temp[0].x + dx_dy[3].x + dx_dy_temp[3].x, circleCenter.y + size + dx_dy[0].y + dx_dy_temp[0].y + dx_dy[1].y + dx_dy_temp[1].y); //leftbottom
	//points[1] = CPoint(circleCenter.x + size - (dx_dy[0].x + dx_dy_temp[0].x + dx_dy[3].x + dx_dy_temp[3].x) + dx_dy[1].x + dx_dy_temp[1].x + dx_dy[2].x + dx_dy_temp[2].x, circleCenter.y + size + dx_dy[0].y + dx_dy_temp[0].y + dx_dy[1].y + dx_dy_temp[1].y); //rightbottom
	//points[2] = CPoint(circleCenter.x + size - (dx_dy[0].x + dx_dy_temp[0].x + dx_dy[3].x + dx_dy_temp[3].x) + dx_dy[1].x + dx_dy_temp[1].x + dx_dy[2].x + dx_dy_temp[2].x, circleCenter.y - size + dx_dy[2].y + dx_dy_temp[2].y + dx_dy[3].y + dx_dy_temp[3].y); //righttop
	//points[3] = CPoint(circleCenter.x - size + dx_dy[0].x + dx_dy_temp[0].x + dx_dy[3].x + dx_dy_temp[3].x, circleCenter.y - size - (dx_dy[0].y + dx_dy_temp[0].y + dx_dy[1].y + dx_dy_temp[1].y) + dx_dy[2].y + dx_dy_temp[2].y + dx_dy[3].y + dx_dy_temp[3].y); //lefttop
 	
	CPoint diffAr[4];
	for (int i = 0; i < 4; i++)
	{
		diffAr[i] = CPoint(dx_dy[i].x + dx_dy_temp[i].x, dx_dy[i].y + dx_dy_temp[i].y);
	}

	points[0] = CPoint(circleCenter.x - size + diffAr[0].x + diffAr[3].x - (diffAr[1].x + diffAr[2].x), circleCenter.y + size + diffAr[0].y + diffAr[1].y - (diffAr[2].y + diffAr[3].y)); //leftbottom
	points[1] = CPoint(circleCenter.x + size + diffAr[1].x + diffAr[2].x - (diffAr[0].x + diffAr[3].x), circleCenter.y + size + diffAr[0].y + diffAr[1].y - (diffAr[2].y + diffAr[3].y)); //rightbottom
	points[2] = CPoint(circleCenter.x + size + diffAr[1].x + diffAr[2].x - (diffAr[0].x + diffAr[3].x), circleCenter.y - size + diffAr[2].y + diffAr[3].y - (diffAr[0].y + diffAr[1].y)); //righttop
	points[3] = CPoint(circleCenter.x - size + diffAr[0].x + diffAr[3].x - (diffAr[1].x + diffAr[2].x), circleCenter.y - size + diffAr[2].y + diffAr[3].y - (diffAr[0].y + diffAr[1].y)); //lefttop

	//1
	//points[2].y += diffAr[2].y + diffAr[3].y;
	//points[3].y += diffAr[2].y + diffAr[3].y;

	int a = abs((points[1].x-points[0].x)/2);
	int b = abs((points[2].y-points[1].y)/2);

	//vector<CPoint> eFP;
	eFP.clear();
	dc->MoveTo(circleCenter.x, circleCenter.y + b);
	for (int y = b - 1; y >= -b; y--)
	{
		double temp = sqrt((1 - (double)y / (double)b) * (1 + (double)y / (double)b));
		int x = a * temp;
		//dc->LineTo(circleCenter.x - x, circleCenter.y + y);
		CPoint temp1{ circleCenter.x - x, circleCenter.y + y };
		eFP.push_back(temp1);
		dc->MoveTo(circleCenter.x - x, circleCenter.y + y);
	}
	CPoint temp1{ circleCenter.x, circleCenter.y + b };
	eFP.push_back(temp1);
	//

	//
	eSP.clear();
	//vector<CPoint> eSP;
	dc->MoveTo(circleCenter.x, circleCenter.y + b);
	for (int y = b - 1; y >= -b; y--)
	{
		double temp = sqrt((1 - (double)y / (double)b) * (1 + (double)y / (double)b));
		int x = a * temp;
		//dc->LineTo(circleCenter.x + x, circleCenter.y + y);
		CPoint temp2{ circleCenter.x + x, circleCenter.y + y };
		eSP.push_back(temp2);
		dc->MoveTo(circleCenter.x + x, circleCenter.y + y);
	}
	CPoint temp2{ circleCenter.x, circleCenter.y + b };
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


	CBrush* brush = new CBrush;
	brush->CreateSolidBrush(RGB(0, 255, 0));

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
	
	//points[0] = CPoint(centerOfShape.x + dx - size + dx_dy[0].x + dx_dy_temp[0].x, centerOfShape.y + dy - size + dx_dy[0].y + dx_dy_temp[0].y); // left top
	//points[1] = CPoint(centerOfShape.x + dx + size + dx_dy[1].x + dx_dy_temp[1].x, centerOfShape.y + dy - size + dx_dy[1].y + dx_dy_temp[1].y); // right top
	//points[2] = CPoint(centerOfShape.x + dx + size + dx_dy[2].x + dx_dy_temp[2].x, centerOfShape.y + dy + size + dx_dy[2].y + dx_dy_temp[2].y); //right bottom
	//points[3] = CPoint(centerOfShape.x + dx - size + dx_dy[3].x + dx_dy_temp[3].x, centerOfShape.y + dy + size + dx_dy[3].y + dx_dy_temp[3].y); // left bottom

	

	dc->Polygon(points, 4);
	dc->Polygon(&eFP[0], eFP.size());
	dc->Polygon(&eSP[0], eSP.size());
	
	if (isSelected)
	{
		//dc->Ellipse(0, 0, 200, 200);
		for (int i = 0; i < 4; i++)
			dc->Ellipse(points[i].x - sizeOfPointToMoveAndChange, points[i].y - sizeOfPointToMoveAndChange, points[i].x + sizeOfPointToMoveAndChange, points[i].y + sizeOfPointToMoveAndChange);
	}
	
	/*delete ellipseRgn1;
	delete ellipseRgn2;*/
	delete pen;
	delete brush;
}


void RectangleShape::draw(CDC* dc)
{
	if (!isSelected)
		pen = new CPen(PS_SOLID, 4, RGB(255, 0, 0));
	else if (isSelected)
		pen = new CPen(PS_SOLID, 4, RGB(0, 0, 0));
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

	for (int i = 0; i < 4; i++)
	{
		int tempX = points[i].x;
		int tempY = points[i].y;
		points[i].x = round(tempX * cos(ellipseAngleRad) - tempY * sin(ellipseAngleRad));
		points[i].y = round(tempX * sin(ellipseAngleRad) + tempY * cos(ellipseAngleRad));
		points[i].x += centerOfShape.x + dx;
		points[i].y += centerOfShape.y + dy;
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

	/*CBrush* triangleBrush = new CBrush;
	triangleBrush->CreateSolidBrush(RGB(0, 255, 0));*/ // Microsoft C++ exception: CResourceException at memory location 0x0098F310
	dc->Polygon(points, 4);
	
	//dc->FillRgn(triangleReg, brush);
	delete pen;
	//delete rectangleReg;
}



//void TriangleShape::draw(CDC* dc)
//{
//	if (!isSelected)
//		pen = new CPen(PS_SOLID, 4, RGB(255, 0, 0));
//	else if (isSelected)
//		pen = new CPen(PS_SOLID, 4, RGB(0, 0, 0));
//	dc->SelectObject(pen);
//	
//
//	// create rectange to draw an triangle into
//	CPoint rectangleCenter{ 0, 0 };
//
//	CPoint diffAr[4];
//	for (int i = 0; i < 4; i++)
//	{
//		diffAr[i] = CPoint(dx_dy[i].x + dx_dy_temp[i].x, dx_dy[i].y + dx_dy_temp[i].y);
//	}
//
//	points[0] = CPoint(rectangleCenter.x - size + diffAr[0].x + diffAr[3].x - (diffAr[1].x + diffAr[2].x), rectangleCenter.y + size + diffAr[0].y + diffAr[1].y - (diffAr[2].y + diffAr[3].y)); //leftbottom
//	points[1] = CPoint(rectangleCenter.x + size + diffAr[1].x + diffAr[2].x - (diffAr[0].x + diffAr[3].x), rectangleCenter.y + size + diffAr[0].y + diffAr[1].y - (diffAr[2].y + diffAr[3].y)); //rightbottom
//	points[2] = CPoint(rectangleCenter.x + size + diffAr[1].x + diffAr[2].x - (diffAr[0].x + diffAr[3].x), rectangleCenter.y - size + diffAr[2].y + diffAr[3].y - (diffAr[0].y + diffAr[1].y)); //righttop
//	points[3] = CPoint(rectangleCenter.x - size + diffAr[0].x + diffAr[3].x - (diffAr[1].x + diffAr[2].x), rectangleCenter.y - size + diffAr[2].y + diffAr[3].y - (diffAr[0].y + diffAr[1].y)); //lefttop
//	
//	CPoint trianglePoints[3];
//
//	trianglePoints[0] = CPoint(points[3].x + (points[2].x - points[3].x) / 2 , points[3].y + (points[2].y - points[3].y) / 2);
//	trianglePoints[1] = points[0];
//	trianglePoints[2] = points[1];
//
//	
//		int diff1 = (trianglePoints[0].x - centerOfShape.x) - (abs(points[2].x) - centerOfShape.x);
//		//int diff2 = trianglePoints[0].x - abs(points[3].x);
//		if (diff1 > 0)
//		{
//			//AfxMessageBox(_T("123123123"));
//			points[2].x += diff1;
//			points[3].x -= diff1;
//			points[1].x += diff1;
//			points[0].x -= diff1;
//			trianglePoints[1] = points[0];
//			trianglePoints[2] = points[1];
//		}
//		/*else
//		{
//			points[2].x -= diff1;
//			points[3].x += diff1;
//			points[1].x -= diff1;
//			points[0].x += diff1;
//			trianglePoints[1] = points[0];
//			trianglePoints[2] = points[1];
//		}*/
//
//	/*trianglePoints[0] = CPoint(points[3].x + (points[2].x - points[3].x) / 0.5, points[3].y + (points[2].y - points[3].y) / 0.5);
//	trianglePoints[1] = points[0];
//	trianglePoints[2] = points[1];*/
//
//	for (int i = 0; i < 4; i++)
//	{
//		int tempX = points[i].x;
//		int tempY = points[i].y;
//		points[i].x = round(tempX * cos(ellipseAngleRad) - tempY * sin(ellipseAngleRad));
//		points[i].y = round(tempX * sin(ellipseAngleRad) + tempY * cos(ellipseAngleRad));
//		points[i].x += centerOfShape.x + dx;
//		points[i].y += centerOfShape.y + dy;
//	}
//
//	for (int i = 0; i < 3; i++)
//	{
//		int tempX = trianglePoints[i].x;
//		int tempY = trianglePoints[i].y;
//		trianglePoints[i].x = round(tempX * cos(ellipseAngleRad) - tempY * sin(ellipseAngleRad));
//		trianglePoints[i].y = round(tempX * sin(ellipseAngleRad) + tempY * cos(ellipseAngleRad));
//		trianglePoints[i].x += centerOfShape.x + dx;
//		trianglePoints[i].y += centerOfShape.y + dy;
//	}
//
//
//	if (isSelected)
//	{
//		//dc->Ellipse(0, 0, 200, 200);
//		for (int i = 0; i < 3; i++)
//			dc->Ellipse(trianglePoints[i].x - sizeOfPointToMoveAndChange, trianglePoints[i].y - sizeOfPointToMoveAndChange, trianglePoints[i].x + sizeOfPointToMoveAndChange, trianglePoints[i].y + sizeOfPointToMoveAndChange);
//	}
//	dc->Polygon(points, 4);
//
//	/*CPoint trianglePoints[3];
//
//	trianglePoints[0] = CPoint(points[3].x + (points[2].x - points[3].x) / 1.5, points[3].y + (points[2].y - points[3].y) / 1.5);
//	trianglePoints[1] = points[0];
//	trianglePoints[2] = points[1];*/
//	
//
//	dc->Polygon(trianglePoints, 3);
//
//	delete pen;
//}




void TriangleShape::draw(CDC* dc)
{
	//auto pDoc = GetDocument();

	if (!isSelected)
		pen = new CPen(PS_SOLID, 4, RGB(255, 0, 0));
	else if (isSelected)
		pen = new CPen(PS_SOLID, 4, RGB(0, 0, 0));
	dc->SelectObject(pen);
	CPoint rectangleCenter{ 0, 0 };
	CPoint diffAr[4];
	for (int i = 0; i < 4; i++)
	{
		diffAr[i] = CPoint(dx_dy[i].x + dx_dy_temp[i].x, dx_dy[i].y + dx_dy_temp[i].y);
	}
	points[0] = CPoint(rectangleCenter.x - 2*sqrt(3)/3*size + diffAr[0].x + diffAr[3].x - (diffAr[1].x + diffAr[2].x), rectangleCenter.y + size + diffAr[0].y + diffAr[1].y - (diffAr[2].y + diffAr[3].y)); //leftbottom
	points[1] = CPoint(rectangleCenter.x + 2 * sqrt(3) / 3 * size + diffAr[1].x + diffAr[2].x - (diffAr[0].x + diffAr[3].x), rectangleCenter.y + size + diffAr[0].y + diffAr[1].y - (diffAr[2].y + diffAr[3].y)); //rightbottom
	points[2] = CPoint(rectangleCenter.x + 2 * sqrt(3) / 3 * size + diffAr[1].x + diffAr[2].x - (diffAr[0].x + diffAr[3].x), rectangleCenter.y - size + diffAr[2].y + diffAr[3].y - (diffAr[0].y + diffAr[1].y)); //righttop
	points[3] = CPoint(rectangleCenter.x - 2 * sqrt(3) / 3 * size + diffAr[0].x + diffAr[3].x - (diffAr[1].x + diffAr[2].x), rectangleCenter.y - size + diffAr[2].y + diffAr[3].y - (diffAr[0].y + diffAr[1].y)); //lefttop
	
	CPoint triangle[4];
	triangle[0] = CPoint(points[3].x + (points[2].x - points[3].x) / 2, points[3].y + (points[2].y - points[3].y) / 2); 
	triangle[1] = points[0]; 
	triangle[2] = points[1]; 
	
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

	/*CBrush* triangleBrush = new CBrush;
	triangleBrush->CreateSolidBrush(RGB(0, 255, 0));*/ // Microsoft C++ exception: CResourceException at memory location 0x0098F310
	
	//dc->Polygon(recFromRgn, 4);
	
	//dc->Polygon(points, 4);
	dc->Polygon(triangle, 3);
	delete triangleRgn;
	delete pen;
}


IShape::~IShape()
{

}


