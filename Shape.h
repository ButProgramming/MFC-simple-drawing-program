#pragma once
#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

//int move_dx=0; 
//int move_dy=0;
//int globalInt;

enum class Tools { select_tool, ellipse, rectangle, triangle, move };
enum class ShapeType { ellipse, rectangle, triangle };

class IShape
{
protected:
	
	
	
	//ShapeType typeOfShape;
public:
	static int dx;
	static int dy;
	bool isSelected = false;
	CPen* pen;
	ShapeType type;
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
	EllipseShape(CPoint, bool, int, ShapeType);
	void draw(CDC* dc);
};

class RectangleShape :public IShape
{
private:

public:
	RectangleShape(CPoint, bool, int, ShapeType);
	void draw(CDC* dc);

};

class TriangleShape : public IShape
{
private:

public:
	TriangleShape(CPoint, bool, int, ShapeType);
	void draw(CDC* dc);
};

//My own global attributes


