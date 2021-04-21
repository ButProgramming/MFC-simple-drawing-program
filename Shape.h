#pragma once
#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <string>
#include <queue>
#include <set>
#include <array>
#include "Lines.h"
using namespace std;


#define SIZE_OF_ELLIPSE_FOR_ROTATE_TOOL 10
#define SIZE_OF_ELLIPSE_FOR_LINES 5
#define SIZE_OF_ELLIPSE_OF_SELECTED_LINE 3
#define SIZE_OF_LINE_RGN 5

enum class Tools { select_tool, ellipse, rectangle, triangle, move, change, rotate, shapeNormalize, shapeMove, doubleSelectTool, basicLine, leftLine, rightLine, doubleLine };
enum class ShapeType { ellipse, rectangle, triangle, basicLine };

class IShape
{
public:
	
public:
	virtual void draw(CDC* dc) = 0;
	virtual CPoint getPointForRotateTool() { return centerPoint23Top; };
	virtual void setFirstClickedPoint(CPoint point) { firstClickedPoint = point; }; // set first clicked points x, y before mouse get OnMouseMove and LButton is pressed down
	virtual CPoint getFirstClickedPoint() { return firstClickedPoint; }; // get first clicked points x, y before mouse get OnMouseMove and LButton is pressed down
	bool IsClickedOnPointForLines(CPoint point); // check if is click point in one of the 4 points for lines 
	void setSelected(bool isSelected) { this->isSelected = isSelected; }; // set if is shape or line selected or not
	bool getSelected() { return isSelected; } // get if is shape or line selected or not
	virtual bool isClickedOnShapeRgn(CPoint point) { return false; };
	virtual CPoint* getConstPointerForRgn(bool isFirstSemicircle) { return nullptr;  }; // pointer for HRGN function
	virtual int getSizeOfShapeArray(bool isFirstSemicircle) { return NULL; }; // size of array, that includes all points of shape
	virtual ~IShape();

	static set<int> IDs;
	static set<CString> names;
 	static int dx;
	static int dy;
	static int sizeOfPointToMoveAndChange;
	static int countOfShape;
	static CPoint firstPoint;

	
	int fillType;
	int outlineType;
	int outlineSize;
	COLORREF fillColor;
	int fR; int fG; int fB; // for safe convinience
	COLORREF outlineColor;
	int oR; int oG; int oB; // for safe convinience
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
	bool isSelected = false;
	double ellipseAngleRad = ellipseAngleDegree * 3.14159265359 / 180.0;
	double rectEllipseRad = rectEllipseDegree * 3.14159265359 / 180.0;
	CRect boxRect;
	int numberOfAngle; //
	CPoint dx_dy_temp[4];
	CPoint dx_dy[4];
	CPoint rectangle_dx_dy_temp[3];
	CPoint rectangle_dx_dy[3];
	CPoint points[4]; // the same array of points for triangle and rectangle shape
	
	//static CPoint pointsOfTriangle[3];
	
	CPen* pen = nullptr;
	ShapeType type;
	int size; // length of inscribed circle in shape
	bool isNormalized;
	CPoint centerOfShape;
	//IShape(int size, CPoint centerOfShape, ShapeType typeOfShape, bool isNormalized = true);

	CPoint firstPointOfLine{ 0, 0 };  // first point of line
	CPoint secondPointOfLine{ 0, 0 }; // second point of line
	

protected:
	CPoint centerPoint23Bottom{ NULL, NULL };			// center of rectangle topside. Needed to select shape
	CPoint centerPoint23Top{ NULL, NULL };			// point that lies higher of centerPoint23Bottom. Point is using for drawing ellipse for rotate tool
	CPoint firstClickedPoint{ NULL, NULL }; // array for x and y coordinates. It is using for save last X and Y before mouse get OnMouseMove and LButton is pressed down
	array <CPoint, 4> pointsForLines; // needed for linking of shapes
	array <CPoint, 2> pointsOfLine; // first and second point of any line [0] - first, [1] - second
	
	
};

class EllipseShape :public IShape
{
public:
	EllipseShape(CPoint centerOfShape, bool isNormalized, int size, ShapeType type, COLORREF outlineColor, COLORREF fillColor, int outlineSize, int outlineType, int fillType);
	void draw(CDC* dc);
	bool isClickedOnShapeRgn(CPoint point);
	CPoint* getConstPointerForRgn(bool firstSemicircle)  { return (firstSemicircle) ? &eFP[0] : &eSP[0]; };
	int getSizeOfShapeArray(bool isFirstSemicircle)		 { return (isFirstSemicircle) ? eFP.size() : eSP.size(); };
	//CPoint getPointForRotateTool() {  };
	/*void setFirstClickedPoint(CPoint point)  {  };
	CPoint getFirstClickedPoint() {  };*/
	
};

class RectangleShape :public IShape
{
public:
	RectangleShape(CPoint centerOfShape, bool isNormalized, int size, ShapeType type, COLORREF outlineColor, COLORREF fillColor, int outlineSize, int outlineType, int fillType);
	void draw(CDC* dc);
	//CPoint getPointForRotateTool();
};

class TriangleShape : public IShape
{
public:
	TriangleShape(CPoint centerOfShape, bool isNormalized, int size, ShapeType type, COLORREF outlineColor, COLORREF fillColor, int outlineSize, int outlineType, int fillType);
	void draw(CDC* dc);
	//CPoint getPointForRotateTool();
};

class Line :public IShape
{
public:
	Line(CPoint firstPointOfShape, ShapeType type, COLORREF lineColor, int lineSize, int lineType);
	void draw(CDC* dc);
	bool isClickedOnShapeRgn(CPoint point);
	
};



