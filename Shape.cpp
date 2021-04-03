#include "pch.h"
#include "Shape.h"

EllipseShape::EllipseShape(CPoint centerOfShape, bool isNormalized, int size)
{
	this->size = size;
	this->centerOfShape = centerOfShape;
	this->isNormalized = isNormalized;
	//this->typeOfShape = typeOfShape;
}

RectangleShape::RectangleShape(CPoint centerOfShape, bool isNormalized, int size)
{
	this->size = size;
	this->centerOfShape = centerOfShape;
	this->isNormalized = isNormalized;
	//this->typeOfShape = typeOfShape;
}

TriangleShape::TriangleShape(CPoint centerOfShape, bool isNormalized, int size)
{
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
	//dc->Rectangle(centerOfShape.x - size, centerOfShape.y - size, centerOfShape.x + size, centerOfShape.y + size);
}

IShape::~IShape()
{

}
