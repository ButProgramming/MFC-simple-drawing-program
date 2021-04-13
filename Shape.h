#pragma once
#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <string>
#include <queue>
#include <set>
using namespace std;


//int move_dx=0; 
//int move_dy=0;
//int globalInt;

enum class Tools { select_tool, ellipse, rectangle, triangle, move, change, rotate, shapeNormalize, shapeMove, doubleSelectTool, basicLine, leftLine, rightLine, doubleLine
};
enum class ShapeType { ellipse, rectangle, triangle };


class IShape
{
protected:
	


	//ShapeType typeOfShape;
public:
	static set<int> IDs;
	static int dx;
	static int dy;
	static int sizeOfPointToMoveAndChange;
	static int countOfShape;
	
	int outlineType;
	int outlineSize;
	COLORREF fillColor;
	COLORREF outlineColor;
	bool isSelectedFromDoubleSelectingTool = false;
	int constID;
	int ID;
	CString name;
	struct diffShapeMove { int x = 0; int y = 0; } dSM; //is used for moving selected shapes
	CPoint recFromRgn[4];
	//CPoint nextCenterTriangle{ -1,-1 };
	//bool isDrawFirstTime{ false };
	int lastY;
	vector<CPoint> eFP;
	vector<CPoint> eSP;
	vector<CPoint> ellipseFirstPart;
	vector<CPoint> ellipseSecondPart;
	double ellipseAngleDegree = 0;
	double rectEllipseDegree = 0;
	
	double ellipseAngleRad = ellipseAngleDegree * 3.14159265359 / 180.0;
	double rectEllipseRad = rectEllipseDegree * 3.14159265359 / 180.0;
	CRect boxRect;
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
	EllipseShape(CPoint, bool, int, ShapeType, COLORREF, COLORREF, int, int);
	void draw(CDC* dc);
	
};

class RectangleShape :public IShape
{
private:
	
public:
	RectangleShape(CPoint, bool, int, ShapeType, COLORREF, COLORREF, int, int);
	void draw(CDC* dc);
	

};

class TriangleShape : public IShape
{
private:
	
public:
	CPoint triangle[3];
	int test;
	TriangleShape(CPoint, bool, int, ShapeType, COLORREF, COLORREF, int, int);
	void draw(CDC* dc);
	
};

//My own global attributes


