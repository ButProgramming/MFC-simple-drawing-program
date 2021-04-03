#pragma once
#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

enum ShapeType { ellipse, rectangle, triangle };

class IShape
{
protected:
	
	
	
	//ShapeType typeOfShape;
public:
	int size; // length of inscribed circle in shape
	bool isNormalized;
	CPoint centerOfShape;
	//IShape(int size, CPoint centerOfShape, ShapeType typeOfShape, bool isNormalized = true);
	virtual void draw(CDC *dc) = 0;
	virtual ~IShape();
};

class EllipseShape :public IShape
{
private:

public:
	EllipseShape(CPoint, bool, int);
	void draw(CDC* dc);
};

class RectangleShape :public IShape
{
private:

public:
	RectangleShape(CPoint, bool, int);
	void draw(CDC* dc);

};

class TriangleShape : public IShape
{
private:

public:
	TriangleShape(CPoint, bool, int);
	void draw(CDC* dc);
};

//My own global attributes


