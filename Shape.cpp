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
	if(!isSelected)
		pen = new CPen(PS_SOLID, 4, RGB(255, 0, 0));
	else if(isSelected)
		pen = new CPen(PS_SOLID, 4, RGB(0, 0, 0));
	CRgn* ellipseRgn = new CRgn;
	//boxRect.BottomRight().x
	points[0] = CPoint(centerOfShape.x + dx - size + dx_dy[0].x + dx_dy_temp[0].x, centerOfShape.y + dy - size + dx_dy[0].y + dx_dy_temp[0].y); // left top
	points[1] = CPoint(centerOfShape.x + dx + size + dx_dy[1].x + dx_dy_temp[1].x, centerOfShape.y + dy - size + dx_dy[1].y + dx_dy_temp[1].y); // right top
	points[2] = CPoint(centerOfShape.x + dx + size + dx_dy[2].x + dx_dy_temp[2].x, centerOfShape.y + dy + size + dx_dy[2].y + dx_dy_temp[2].y); //right bottom
	points[3] = CPoint(centerOfShape.x + dx - size + dx_dy[3].x + dx_dy_temp[3].x, centerOfShape.y + dy + size + dx_dy[3].y + dx_dy_temp[3].y); // left bottom
	ellipseRgn->CreatePolygonRgn(points, 4, ALTERNATE);
	dc->SelectObject(pen);
	if (isSelected)
	{
		//dc->Ellipse(0, 0, 200, 200);
		for (int i = 0; i < 4; i++)
			dc->Ellipse(points[i].x - sizeOfPointToMoveAndChange, points[i].y - sizeOfPointToMoveAndChange, points[i].x + sizeOfPointToMoveAndChange, points[i].y + sizeOfPointToMoveAndChange);
	}																														/*HRGN ellipseReg = CreateEllipticRgn(centerOfShape.x + dx - size, centerOfShape.y + dy - size, centerOfShape.x + dx + size, centerOfShape.y + dy + size);
	GetRgnBox(ellipseReg, boxRect);
	dc->Rectangle(boxRect);*/
	
	// synchronized moving
	dc->Rectangle(boxRect);
	dc->Polygon(points, 4);
	GetRgnBox(*ellipseRgn, boxRect);
	//boxRect.BottomRight().x;
	//dc->Ellipse(centerOfShape.x + dx - size, centerOfShape.y + dy - size, centerOfShape.x + dx + size, centerOfShape.y + dy + size);
	//auto test = CreateEllipticRgn()
	dc->Ellipse(boxRect);
	delete ellipseRgn;
	delete pen;
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
	int side =  2 * h / sqrt(3);
	// synchronized moving
	

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
		for(int i=0; i<3; i++)
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
