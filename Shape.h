#pragma once
#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <string>
#include <queue>
#include <set>
#include <array>
using namespace std;


#define SIZE_OF_ELLIPSE_FOR_ROTATE_TOOL 10

enum class Tools { select_tool, ellipse, rectangle, triangle, move, change, rotate, shapeNormalize, shapeMove, doubleSelectTool, basicLine, leftLine, rightLine, doubleLine };
enum class ShapeType { ellipse, rectangle, triangle };

class IShape
{
public:
	int lastValueY = 0;
	int lastValueX = 0;
public:
	virtual void draw(CDC* dc) = 0;
	virtual CPoint getPointForRotateTool() = 0;
	virtual void setFirstClickedPoint(CPoint point) {}; // set first clicked points x, y before mouse get OnMouseMove and LButton is pressed down
	virtual CPoint getFirstClickedPoint() { return CPoint(0, 0); }; // get first clicked points x, y before mouse get OnMouseMove and LButton is pressed down
	virtual ~IShape();

	static set<int> IDs;
	static set<CString> names;
 	static int dx;
	static int dy;
	static int sizeOfPointToMoveAndChange;
	static int countOfShape;
	

	
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
	
protected:
	CPoint centerPoint23Bottom;			// center of rectangle topside. Needed to select shape
	CPoint centerPoint23Top;			// point that lies higher of centerPoint23Bottom. Point is using for drawing ellipse for rotate tool
	CPoint firstClickedPoint{ NULL, NULL }; // array for x and y coordinates. It is using for save last X and Y before mouse get OnMouseMove and LButton is pressed down
	
};

class EllipseShape :public IShape
{
public:
	EllipseShape(CPoint centerOfShape, bool isNormalized, int size, ShapeType type, COLORREF outlineColor, COLORREF fillColor, int outlineSize, int outlineType, int fillType);
	void draw(CDC* dc);
	CPoint getPointForRotateTool() { return centerPoint23Top; };
	void setFirstClickedPoint(CPoint point)  { firstClickedPoint = point; };
	CPoint getFirstClickedPoint() { return firstClickedPoint; };
	
};

class RectangleShape :public IShape
{
public:
	RectangleShape(CPoint centerOfShape, bool isNormalized, int size, ShapeType type, COLORREF outlineColor, COLORREF fillColor, int outlineSize, int outlineType, int fillType);
	void draw(CDC* dc);
	CPoint getPointForRotateTool();
};

class TriangleShape : public IShape
{
public:
	TriangleShape(CPoint centerOfShape, bool isNormalized, int size, ShapeType type, COLORREF outlineColor, COLORREF fillColor, int outlineSize, int outlineType, int fillType);
	void draw(CDC* dc);
	CPoint getPointForRotateTool();
};



