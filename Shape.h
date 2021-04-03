#pragma once
#include <iostream>
#include <vector>
using namespace std;

class IShape
{
protected:
	int size;
	CPoint centerOfShape;
	bool isNormalized;
	//ShapeType typeOfShape;
public:
	//IShape(int size, CPoint centerOfShape, ShapeType typeOfShape, bool isNormalized = true);
	virtual void draw() = 0;
	virtual ~IShape();
};

class EllipseShape :public IShape
{
private:

public:
	EllipseShape(CPoint, bool, int);
	void draw()
	{

	}
};

class RectangleShape :public IShape
{
private:

public:
	

};

class TriangleShape : public IShape
{
private:

public:

};

//My own global attributes
enum ShapeType { ellipse, rectangle, triangle };

