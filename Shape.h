#pragma once
#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;

//int move_dx=0; 
//int move_dy=0;
//int globalInt;

enum class Tools { select_tool, ellipse, rectangle, triangle, move, change };
enum class ShapeType { ellipse, rectangle, triangle };

class IShape
{
protected:
	


	//ShapeType typeOfShape;
public:
	static int dx;
	static int dy;
	static int sizeOfPointToMoveAndChange;
	
	int numberOfAngle; //
	CPoint dx_dy_temp[4];
	CPoint dx_dy[4];
	CPoint rectangle_dx_dy_temp[3];
	CPoint rectangle_dx_dy[3];
	CPoint points[4]; // the same array of points for triangle and rectangle shape
	
	static CPoint pointsOfTriangle[3];
	bool isSelected = false;
	CPen* pen;
	ShapeType type;
	int size; // length of inscribed circle in shape
	bool isNormalized;
	CPoint centerOfShape;
	//IShape(int size, CPoint centerOfShape, ShapeType typeOfShape, bool isNormalized = true);
	virtual void draw(CDC* dc) = 0;
	
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
	CPoint triangle[3];
	int test;
	TriangleShape(CPoint, bool, int, ShapeType);
	void draw(CDC* dc);
	
};

//My own global attributes


