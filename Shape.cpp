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
	CPoint circleCenter{ 0,0 };

	//int circleRadius = 100;

	int a = size;
	int b = size;
	double t = 5.4;
	CString str;
	str.Format(_T("%g"), round(t));
	//AfxMessageBox(str);


	//
	vector<CPoint> vec1;
	dc->MoveTo(circleCenter.x, circleCenter.y + b);
	for (int y = b - 1; y >= -b; y--)
	{
		double temp = sqrt((1 - (double)y / (double)b) * (1 + (double)y / (double)b));
		int x = a * temp;
		//dc->LineTo(circleCenter.x - x, circleCenter.y + y);
		CPoint temp1{ circleCenter.x - x, circleCenter.y + y };
		vec1.push_back(temp1);
		dc->MoveTo(circleCenter.x - x, circleCenter.y + y);
	}
	CPoint temp1{ circleCenter.x, circleCenter.y + b };
	vec1.push_back(temp1);
	//

	//
	vector<CPoint> vec2;
	dc->MoveTo(circleCenter.x, circleCenter.y + b);
	for (int y = b - 1; y >= -b; y--)
	{
		double temp = sqrt((1 - (double)y / (double)b) * (1 + (double)y / (double)b));
		int x = a * temp;
		//dc->LineTo(circleCenter.x + x, circleCenter.y + y);
		CPoint temp2{ circleCenter.x + x, circleCenter.y + y };
		vec2.push_back(temp2);
		dc->MoveTo(circleCenter.x + x, circleCenter.y + y);
	}
	CPoint temp2{ circleCenter.x, circleCenter.y + b };
	vec2.push_back(temp2);
	//
	dc->MoveTo(circleCenter.x, circleCenter.y + b);
	/*CPoint* p1 = &vec1[0];
	CPoint* p2 = &vec2[0];*/
	//ellipseRgn1 = new CRgn;
	//ellipseRgn2 = new CRgn;

	//vector<CPoint> vecTest1(vec1);
	//vector<CPoint> vecTest2(vec2);
	//for(int i-9;)
	vecTest1.clear();
	vecTest2.clear();
	for (CPoint v1 : vec1)
	{
		vecTest1.push_back(v1);
	}
	for (CPoint v2 : vec2)
	{
		vecTest2.push_back(v2);
	}

	/*for (int i = 0; i < vec1.size(); i++)
	{
		vec1[i].x += centerOfShape.x;
		vec1[i].y += centerOfShape.y;
	}

	for (int i = 0; i < vec2.size(); i++)
	{
		vec2[i].x += centerOfShape.x;
		vec2[i].y += centerOfShape.y;
	}*/

	CBrush* brush = new CBrush;
	brush->CreateSolidBrush(RGB(0, 255, 0));
	//ellipseRgn1->CreatePolygonRgn(&vec1[0], vec1.size(), ALTERNATE);
	//dc->Polygon(&vec1[0], vec1.size());
	//dc->Polygon(&vec2[0], vec2.size());
	//dc->FillRgn(ellipseRgn1, brush);
	//ellipseRgn2->CreatePolygonRgn(&vec2[0], vec2.size(), ALTERNATE);
	//dc->FillRgn(ellipseRgn2, brush);



	

	for (int i = 0; i < vecTest1.size(); i++)
	{
		int tempX = vecTest1[i].x;
		int tempY = vecTest1[i].y;
		vecTest1[i].x = round(tempX * cos(ellipseAngleRad) - tempY * sin(ellipseAngleRad));
		vecTest1[i].y = round(tempX * sin(ellipseAngleRad) + tempY * cos(ellipseAngleRad));
		vecTest1[i].x += centerOfShape.x + dx;
		vecTest1[i].y += centerOfShape.y + dy;
		/*vecTest[i].x += 10;
		vecTest[i].y += 10;*/
	}
	double cosT1;
	double sinT1;


	for (int i = 0; i < vecTest2.size(); i++)
	{

		int tempX = vecTest2[i].x;
		int tempY = vecTest2[i].y;
		vecTest2[i].x = round(tempX * cos(ellipseAngleRad) - tempY * sin(ellipseAngleRad));
		vecTest2[i].y = round(tempX * sin(ellipseAngleRad) + tempY * cos(ellipseAngleRad));
		//vecTest2[i].x = vecTest2[i].x * double(cos(ellipseAngleRad)) - double(vecTest2[i].y) * sin(ellipseAngleRad);
		//vecTest2[i].y = vecTest2[i].x * double(sin(ellipseAngleRad)) + double(vecTest2[i].y) * cos(ellipseAngleRad);
		vecTest2[i].x += centerOfShape.x + dx;
		vecTest2[i].y += centerOfShape.y + dy;

	}




	/*for (int i = 0; i < vec1.size(); i++)
	{
		vec1[i].x += centerOfShape.x;
		vec1[i].y += centerOfShape.y;
	}
	for (int i = 0; i < vec2.size(); i++)
	{
		vec2[i].x += centerOfShape.x;
		vec2[i].y += centerOfShape.y;
	}*/
	//if (size > 20)
	//{
	//	AfxMessageBox(_T("0")); //debug
	//}
	//if (vecTest1.size() > 5) // correct region 6 points and more
	//{
	//	CPoint points[4];
	//	GetRgnBox(ellipseRgn1, &boxRect);
	//	points[0] = CPoint(boxRect.TopLeft().x, boxRect.TopLeft().y); //topleft
	//	dc->Rectangle(boxRect);
	//	GetRgnBox(ellipseRgn2, &boxRect);
	//	points[2] = CPoint(boxRect.BottomRight().x, boxRect.BottomRight().y); //bottomright
	//	points[1] = CPoint(points[2].x, points[0].y); //topright
	//	points[3] = CPoint(points[0].x, points[2].y); //bottomleft
	//	dc->Polygon(points, 4);
	//}
	//dc->Rectangle(boxRect);
	dc->Polygon(&vecTest1[0], vecTest1.size());
	dc->Polygon(&vecTest2[0], vecTest2.size());
	//ellipseRgn1 = new HRGN;
	//ellipseRgn2 = new HRGN;
	//*ellipseRgn1 = CreatePolygonRgn(&vecTest1[0], vecTest1.size(), ALTERNATE);
	//*ellipseRgn2 = CreatePolygonRgn(&vecTest2[0], vecTest2.size(), ALTERNATE);
	
	//ellipseRgn->CreatePolygonRgn(points, 4, ALTERNATE);
	/*delete p1;
	delete p2;*/
	delete pen;
	//delete ellipseRgn1;
	//delete ellipseRgn2;
	delete brush;













	//CRgn* ellipseRgn = new CRgn;
	//
	//points[0] = CPoint(centerOfShape.x + dx - size + dx_dy[3].x + dx_dy_temp[3].x + dx_dy[0].x + dx_dy_temp[0].x, centerOfShape.y + dy - size + dx_dy[0].y + dx_dy_temp[0].y + dx_dy[1].y + dx_dy_temp[1].y); // left top
	//points[1] = CPoint(centerOfShape.x + dx + size + dx_dy[1].x + dx_dy_temp[1].x + dx_dy[2].x + dx_dy_temp[2].x, centerOfShape.y + dy - size + dx_dy[0].y + dx_dy_temp[0].y + dx_dy[1].y + dx_dy_temp[1].y); // right top
	//points[2] = CPoint(centerOfShape.x + dx + size + dx_dy[1].x + dx_dy_temp[1].x + dx_dy[2].x + dx_dy_temp[2].x, centerOfShape.y + dy + size + dx_dy[2].y + dx_dy_temp[2].y + dx_dy[3].y + dx_dy_temp[3].y); //right bottom
	//points[3] = CPoint(centerOfShape.x + dx - size + dx_dy[3].x + dx_dy_temp[3].x + dx_dy[0].x + dx_dy_temp[0].x, centerOfShape.y + dy + size + dx_dy[2].y + dx_dy_temp[2].y + dx_dy[3].y + dx_dy_temp[3].y); // left bottom
	//
	//ellipseRgn->CreatePolygonRgn(points, 4, ALTERNATE);
	//dc->SelectObject(pen);
	//if (isSelected)
	//{
	//	//dc->Ellipse(0, 0, 200, 200);
	//	for (int i = 0; i < 4; i++)
	//		dc->Ellipse(points[i].x - sizeOfPointToMoveAndChange, points[i].y - sizeOfPointToMoveAndChange, points[i].x + sizeOfPointToMoveAndChange, points[i].y + sizeOfPointToMoveAndChange);
	//}																														/*HRGN ellipseReg = CreateEllipticRgn(centerOfShape.x + dx - size, centerOfShape.y + dy - size, centerOfShape.x + dx + size, centerOfShape.y + dy + size);
	//GetRgnBox(ellipseReg, boxRect);
	//dc->Rectangle(boxRect);*/

	//// synchronized moving
	////dc->Rectangle(boxRect);
	//dc->Polygon(points, 4);
	//GetRgnBox(*ellipseRgn, boxRect);
	////boxRect.BottomRight().x;
	////dc->Ellipse(centerOfShape.x + dx - size, centerOfShape.y + dy - size, centerOfShape.x + dx + size, centerOfShape.y + dy + size);
	////auto test = CreateEllipticRgn()

	//dc->Ellipse(boxRect);
	//
	//
	//
	////dc->SelectObject(OldFont);
	//////CPaintDC d(NULL);
	//delete ellipseRgn;
	//delete pen;
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


	points[0] = CPoint(centerOfShape.x + dx - size + dx_dy[0].x + dx_dy_temp[0].x, centerOfShape.y + dy - size + dx_dy[0].y + dx_dy_temp[0].y); // left top
	points[1] = CPoint(centerOfShape.x + dx + size + dx_dy[1].x + dx_dy_temp[1].x, centerOfShape.y + dy - size + dx_dy[1].y + dx_dy_temp[1].y); // right top
	points[2] = CPoint(centerOfShape.x + dx + size + dx_dy[2].x + dx_dy_temp[2].x, centerOfShape.y + dy + size + dx_dy[2].y + dx_dy_temp[2].y); //right bottom
	points[3] = CPoint(centerOfShape.x + dx - size + dx_dy[3].x + dx_dy_temp[3].x, centerOfShape.y + dy + size + dx_dy[3].y + dx_dy_temp[3].y); // left bottom
	CRgn* rectangleReg = new CRgn;

	rectangleReg->CreatePolygonRgn(points, 4, ALTERNATE);
	GetRgnBox(*rectangleReg, boxRect);
	dc->Rectangle(boxRect);
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
	delete rectangleReg;
}


void TriangleShape::draw(CDC* dc)
{
	//auto pDoc = GetDocument();

	if (!isSelected)
		pen = new CPen(PS_SOLID, 4, RGB(255, 0, 0));
	else if (isSelected)
		pen = new CPen(PS_SOLID, 4, RGB(0, 0, 0));
	dc->SelectObject(pen);
	CBrush* brush = new CBrush;
	brush->CreateSolidBrush(RGB(0, 255, 0));
	int radius = size; // for convinient

	int h = 3 * size;
	int side = 2 * h / sqrt(3);
	// synchronized moving

	//dc->Ellipse()
	points[0] = CPoint(centerOfShape.x + dx + dx_dy[0].x + dx_dy_temp[0].x, centerOfShape.y + dy - 2 * radius + dx_dy[0].y + dx_dy_temp[0].y); //top
	points[1] = CPoint(centerOfShape.x + dx + dx_dy[1].x + dx_dy_temp[1].x - side / 2, centerOfShape.y + dy + radius + dx_dy[1].y + dx_dy_temp[1].y); //left
	points[2] = CPoint(centerOfShape.x + dx + dx_dy[2].x + dx_dy_temp[2].x + side / 2, centerOfShape.y + dy + radius + dx_dy[2].y + dx_dy_temp[2].y); //right

	/*rectangle_dx_dy[0].x = points[0].x;
	rectangle_dx_dy[0].y = points[0].y;
	rectangle_dx_dy[1].x = points[1].x;
	rectangle_dx_dy[1].y = points[1].y;
	rectangle_dx_dy[2].x = points[2].x;
	rectangle_dx_dy[2].y = points[2].y;*/
	//triangleArr[3] = triangle[3];

	CRgn* triangleReg = new CRgn;
	triangleReg->CreatePolygonRgn(points, 3, ALTERNATE);
	GetRgnBox(*triangleReg, boxRect);
	dc->Rectangle(boxRect);
	/*CBrush* triangleBrush = new CBrush;
	triangleBrush->CreateSolidBrush(RGB(0, 255, 0));*/ // Microsoft C++ exception: CResourceException at memory location 0x0098F310
	//GetRgnBox(*triangleReg, boxRect);
	//dc->Rectangle(boxRect);
	dc->Polygon(points, 3);
	dc->FillRgn(triangleReg, brush);




	//CString str;
	//str.Format(_T("%d"), rect.CenterPoint().x);
	//AfxMessageBox(str);
	// create points to change the triangle
	if (isSelected)
	{
		//dc->Ellipse(0, 0, 200, 200);
		for (int i = 0; i < 3; i++)
			dc->Ellipse(points[i].x - sizeOfPointToMoveAndChange, points[i].y - sizeOfPointToMoveAndChange, points[i].x + sizeOfPointToMoveAndChange, points[i].y + sizeOfPointToMoveAndChange);
	}

	//delete points;
	//delete triangleReg;
	//delete dc;
	delete pen;
	delete brush;
	delete triangleReg;
}


IShape::~IShape()
{

}
