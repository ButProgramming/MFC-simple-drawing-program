#include "pch.h"
#include "Shape.h"

EllipseShape::EllipseShape(CPoint centerOfShape, bool isNormalized, int size)
{
	this->size = size;
	this->centerOfShape = centerOfShape;
	this->isNormalized = isNormalized;
	//this->typeOfShape = typeOfShape;
}

IShape::~IShape()
{

}
