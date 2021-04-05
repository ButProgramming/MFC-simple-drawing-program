#include "pch.h"
#include "Shape.h"

int IShape::dx = 0;
int IShape::dy = 0;


EllipseShape::EllipseShape(CPoint centerOfShape, bool isNormalized, int size, ShapeType type)
{
	//type = ShapeType::ellipse;
	this->type = type;
	this->size = size;
	this->centerOfShape = centerOfShape;
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
	dc->SelectObject(pen);
	// synchronized moving
	dc->Ellipse(centerOfShape.x + dx - size, centerOfShape.y + dy - size, centerOfShape.x + dx + size, centerOfShape.y + dy + size);
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
	dc->Rectangle(centerOfShape.x + dx - size, centerOfShape.y + dy - size, centerOfShape.x + dx + size, centerOfShape.y + dy + size);
	delete pen;
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
	CPoint triangle[3];
	triangle[0] = CPoint(centerOfShape.x + dx, centerOfShape.y + dy - 2*radius); //top
	triangle[1] = CPoint(centerOfShape.x + dx - side / 2, centerOfShape.y + dy + radius); //left
	triangle[2] = CPoint(centerOfShape.x + dx + side / 2, centerOfShape.y + dy + radius); //right
	
	CRgn* triangleReg = new CRgn;
	triangleReg->CreatePolygonRgn(triangle, 3, ALTERNATE);
	/*CBrush* triangleBrush = new CBrush;
	triangleBrush->CreateSolidBrush(RGB(0, 255, 0));*/ // Microsoft C++ exception: CResourceException at memory location 0x0098F310
	dc->Polygon(triangle, 3);
	dc->FillRgn(triangleReg, brush);
	if (isSelected)
	{
		for(int i=0; i<3; i++)
			dc->Ellipse(triangle[i].x - 3, triangle[i].y - 3, triangle[i].x + 3, triangle[i].y + 3);
	}
	delete pen;
	delete brush;
	delete triangleReg;
}

IShape::~IShape()
{

}
