#include "pch.h"
#include "Shape.h"

EllipseShape::EllipseShape(CPoint centerOfShape, bool isNormalized, int size)
{
	type = ellipse;
	this->size = size;
	this->centerOfShape = centerOfShape;
	this->isNormalized = isNormalized;
	//this->typeOfShape = typeOfShape;
}

RectangleShape::RectangleShape(CPoint centerOfShape, bool isNormalized, int size)
{
	type = rectangle;
	this->size = size;
	this->centerOfShape = centerOfShape;
	this->isNormalized = isNormalized;
	//this->typeOfShape = typeOfShape;
}

TriangleShape::TriangleShape(CPoint centerOfShape, bool isNormalized, int size)
{
	type = triangle;
	this->size = size;
	this->centerOfShape = centerOfShape;
	this->isNormalized = isNormalized;
	//this->typeOfShape = typeOfShape;
}

void EllipseShape::draw(CDC* dc)
{
	//size = 100;
	dc->Ellipse(centerOfShape.x - size, centerOfShape.y - size, centerOfShape.x + size, centerOfShape.y + size);
}


void RectangleShape::draw(CDC* dc)
{
	dc->Rectangle(centerOfShape.x - size, centerOfShape.y - size, centerOfShape.x + size, centerOfShape.y + size);
}


void TriangleShape::draw(CDC* dc)
{
	CBrush* brush = new CBrush;
	brush->CreateSolidBrush(RGB(0, 255, 0));
	int radius = size; // for convinient

	int h = 3 * size;
	int side =  2 * h / sqrt(3);
	
	CPoint triangle[3];
	triangle[0] = CPoint(centerOfShape.x, centerOfShape.y - 2*radius); //top
	triangle[1] = CPoint(centerOfShape.x - side / 2, centerOfShape.y + radius); //left
	triangle[2] = CPoint(centerOfShape.x + side / 2, centerOfShape.y + radius); //right

	CRgn* triangleReg = new CRgn;
	triangleReg->CreatePolygonRgn(triangle, 3, ALTERNATE);
	/*CBrush* triangleBrush = new CBrush;
	triangleBrush->CreateSolidBrush(RGB(0, 255, 0));*/ // Microsoft C++ exception: CResourceException at memory location 0x0098F310
	dc->Polygon(triangle, 3);
	dc->FillRgn(triangleReg, brush);
	delete brush;
	delete triangleReg;
}

IShape::~IShape()
{

}
