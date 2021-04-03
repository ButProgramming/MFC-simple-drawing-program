#include "pch.h"
#include "Shape.h"

Ellipse::Ellipse(int size, CPoint centerOfShape, ShapeType typeOfShape, bool isNormalized = true)
{
	this->size = size;
	this->centerOfShape = centerOfShape;
	this->isNormalized = isNormalized;
	this->typeOfShape = typeOfShape;
}

