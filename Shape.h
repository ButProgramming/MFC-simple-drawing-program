#pragma once

enum ShapeType{ellipse, rectangle, triangle};

class IShape
{
protected:
	int size;
	CPoint centerOfShape;
	bool isNormalized;
	ShapeType typeOfShape;
public:
	//IShape(int size, CPoint centerOfShape, ShapeType typeOfShape, bool isNormalized = true);
	virtual void draw() = 0;
	virtual ~IShape();
};

class Ellipse :public IShape
{
public:
	Ellipse(int, CPoint, ShapeType, bool);
};

class Rectangle :public IShape
{
public:
	

};

class Triangle : public IShape
{
public:

};
