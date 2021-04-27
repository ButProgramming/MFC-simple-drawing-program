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
#define SIZE_OF_POINT_FOR_CHANGE 7
#define SIZE_OF_LINE_RGN 7
#define RATE_VALUE_FOR_POINT_FOR_CHANGE 1.5
#define MULTIPLIKATOR_FOR_LINES_ELLIPSE_RGN 4 // make easer connecting lines with shapes (rgn size * multiplikator)
// define for lines
#define FIRST_POINT_OF_LINE 0
#define SECOND_POINT_OF_LINE 1
// laws for rotate and move
#define MOUSE_MOVE 0
#define LBUTTON_UP 1

enum class Tools { select_tool, ellipse, rectangle, triangle, move, change, rotate, shapeNormalize, shapeMove, doubleSelectTool, basicLine, leftLine, rightLine, doubleLine };
enum class ShapeType { ellipse, rectangle, triangle, basicLine };

class IShape
{
public:
	
public:
	virtual void draw(CDC* dc) = 0;
	//void rotationOfAxes(int numberOfShapeInVector);

	virtual CPoint getPointForRotateTool() { return centerPoint23Top; };					// return point for rotate tool
	virtual void setFirstClickedPoint(CPoint point) { firstClickedPoint = point; };			// set first clicked points x, y before mouse get OnMouseMove and LButton is pressed down
	virtual CPoint getFirstClickedPoint() { return firstClickedPoint; };					// get first clicked points x, y before mouse get OnMouseMove and LButton is pressed down
	bool IsClickedOnPointForLines(CPoint point, int& numberOfPoint);						// check if is click point in one of the 4 points for lines 
	void setSelected(bool isSelected) { this->isSelected = isSelected; };					// set if is shape or line selected or not
	bool getSelected() { return isSelected; }												// get if is shape or line selected or not
	virtual bool isClickedOnShapeRgn(CPoint point) { return false; };						// ckecked if clickpoint is in shape region
	virtual bool isClickedPointForChange(CPoint point) { return false; };					// checked if clickpoint is in a point for change region
	int getNumberOfPointForChange() { return numberOfPoint; }								// get number of clicked point from method isClickedPointForChange
	virtual CPoint* getConstPointerForRgn(bool isFirstSemicircle) { return nullptr;  };		// pointer for HRGN function
	virtual int getSizeOfShapeArray(bool isFirstSemicircle) { return NULL; };				// size of array, that includes all points of shape
	virtual bool isReversed() { return isReversedVar; };									// is needed for rotate shape. Angle for rotate will be -, when return is true
	virtual CPoint getCoordinateForChange(int num) { return CPoint{ NULL, NULL }; };		// get coordinate of points that is used for change of shapes properites. Num -> number of point
	virtual void setCoordinateForChange(int num, CPoint point) {};							// set coordinate of points that is used for change of shapes properites. Num -> number of point
	CPoint getTemporaryDxDy(int num) { return (num < temporaryDxDy.size()) ? 
		temporaryDxDy[num] : CPoint{ NULL, NULL }; };										// getter for temporaryDxDy
	void setTemporaryDxDy(int num, CPoint point) { temporaryDxDy[num] = point; };			// setter for temporaryDxDy
	CPoint getDxDy(int num) { return (num < dxDy.size()) ?
			dxDy[num] : CPoint{ NULL, NULL }; };											// getter for dxDy
	void setDxDy(int num, CPoint point) { dxDy[num] = point; }								// setter for dxDy
	void setCanDrawPointsForLines(bool active) { drawPointsForLines = active; };			// setter for drawPointsForLines
	bool getCanDrawPointsForLines() { return drawPointsForLines; };							// getter for drawPointsForLines

	void setShapeMoveTempDxDy(CPoint point) { shapeMove.tempDxDy.x = point.x; shapeMove.tempDxDy.y = point.y; };
	CPoint getShapeMoveTempDxDy() { return shapeMove.tempDxDy; };
	void setShapeMoveStartClickedCoordinate(CPoint point) { shapeMove.startClickedCoordinate = point; };
	CPoint getShapeMoveStartClickedCoordinate() { return shapeMove.startClickedCoordinate; };

	CPoint rotateAndMoveCoordinate(CPoint &point, Tools& toolIsUsed, int from);
	void rotateShape(CPoint point);
	void moveChangeRotate(vector<IShape*>& shapes, Tools& toolIsUsed, CPoint point, bool &canBeUnselected, bool &shapeIsFound);

	void setChangeStartClickedCoordinate(CPoint point) { change.startClickedCoordinate = point; };
	CPoint getChangeStartClickedCoordinate() { return change.startClickedCoordinate; };
	void setChangeTempDxDy(int num, CPoint point) { change.tempDxDy[num] = point; };
	CPoint getChangeTempDxDy(int num) { return change.tempDxDy[num]; };
	
	//void setTempDxDy()

	//pointsForLines
	CPoint getPointForLine(int numberOfPoint)
	{
		return (numberOfPoint >= 0 && numberOfPoint < 4) ? pointsForLines[numberOfPoint] : CPoint{ NULL, NULL }; //getter for pointsForLines
	}
	void createLineConnection(int numberOfPointOfLine, int shapeConstID, int numberOfPointForLines);
	void updateLineConnection(const vector<IShape*>& shapes);
	void lineDisconnecting(int numberOfPointOfLine, int shapeConstID);

	virtual ~IShape();

	static set<int> IDs;
	static set<CString> names;
 	static int dx;
	static int dy;
	static int sizeOfPointToMoveAndChange;
	static int countOfShape;
	CPoint firstPoint{0,0};

	
	
	int fillType = NULL;
	int outlineType = NULL;
	int outlineSize = NULL;
	COLORREF fillColor = NULL;
	int fR = NULL; int fG = NULL; int fB = NULL; // for safe convinience
	COLORREF outlineColor = NULL;
	int oR = NULL; int oG = NULL; int oB = NULL; // for safe convinience
	bool isSelectedFromDoubleSelectingTool = false;
	int constID = NULL;
	int ID = NULL;
	CString name = NULL;
	
	CPoint recFromRgn[4]  = { CPoint{0,0}, CPoint{0,0}, CPoint{0,0}, CPoint{0,0} };;
	//CPoint nextCenterTriangle{ -1,-1 };
	//bool isDrawFirstTime{ false };
	int lastY = NULL;
	vector<CPoint> eFP;
	vector<CPoint> eSP;
	vector<CPoint> ellipseFirstPart;
	vector<CPoint> ellipseSecondPart;
	double ellipseAngleDegree = 0;
	double rectEllipseDegree = 0;
	bool isSelected = false;
	double ellipseAngleRad = ellipseAngleDegree * 3.14159265359 / 180.0;
	double rectEllipseRad = rectEllipseDegree * 3.14159265359 / 180.0;
	CRect boxRect = NULL;
	
	//int numberOfAngle; //
	CPoint dx_dy_temp[4] = { CPoint{0,0}, CPoint{0,0}, CPoint{0,0}, CPoint{0,0} };
	CPoint dx_dy[4] = { CPoint{0,0}, CPoint{0,0}, CPoint{0,0}, CPoint{0,0} };
	CPoint rectangle_dx_dy_temp[3] = { CPoint{0,0}, CPoint{0,0}, CPoint{0,0}};
	CPoint rectangle_dx_dy[3] = { CPoint{0,0}, CPoint{0,0}, CPoint{0,0}};
	//CPoint points[4]; // the same array of points for triangle and rectangle shape
	array <CPoint, 4> points;
	
	//static CPoint pointsOfTriangle[3];
	
	CPen* pen = nullptr;
	ShapeType type;
	int size; // length of inscribed circle in shape
	//bool isNormalized = false;
	CPoint centerOfShape {NULL, NULL};
	//IShape(int size, CPoint centerOfShape, ShapeType typeOfShape, bool isNormalized = true);

	//struct diffShapeMove { int x = 0; int y = 0; } dSM; //is used for moving selected shapes

	//struct rotate
	//{
	//	int lastY = 0; // is used for saving of last y 
	//};
	


	
protected:
	CPoint centerPoint23Bottom{ NULL, NULL };			// center of rectangle topside. Needed to select shape
	CPoint centerPoint23Top{ NULL, NULL };				// point that lies higher of centerPoint23Bottom. Point is using for drawing ellipse for rotate tool
	CPoint firstClickedPoint{ NULL, NULL };			    // array for x and y coordinates. It is using for save last X and Y before mouse get OnMouseMove and LButton is pressed down
	array <CPoint, 4> pointsForLines;					// needed for linking of shapes
	array <CPoint, 2> pointsOfLine;						// first and second point of any line [0] - first, [1] - second
	bool isReversedVar = false;							// value that demonstrate if shape is reversed or not
	int numberOfPoint = NULL;							// number of clicked point for change the shape
	array <CPoint, 4> temporaryDxDy;					// array for temporary difference values for dx and dy, when shape is moved. 
	array <CPoint, 4> dxDy;								// array that contains dx and dy to change points coordinate (it contains also temporaryDxDy values)
	bool drawPointsForLines = false;					// var that set if is points for lines drawn or not

	struct connecting
	{
		struct isConnected { bool firstPointOfLine = false; bool secondPointOfLine = false; }isConnected;
		struct connectedShapeConstID { int firstPointOfLine = -1; int secondPointOfLine = -1; }connectedShapeConstID;
		struct numberOfShapesPointForLines { int firstPointOfLine = -1; int secondPointOfLine = -1; }numberOfShapesPointForLines;
	} connecting;

	struct shapeMove
	{
		CPoint tempDxDy{ NULL, NULL }; //temporary coordinate that us used for displaying the movement of shapes, when lbutton is down
		CPoint startClickedCoordinate{ NULL, NULL }; // coordinate that saved when LButtonDown is clicked
		//CPoint currentCoordinate{ NULL, NULL }; // current coordinate of cursor
	} shapeMove;

	struct change
	{
		array <CPoint, 4> dxDy;
		array <CPoint, 4> tempDxDy;
		CPoint startClickedCoordinate{ NULL, NULL }; // coordinate that saved when LButtonDown is clicked

	} change;


	//struct isConnected { bool firstPointOfLine = false;
	//bool secondPointOfLine = false; } isConnected;		// when first or second point of line are connected - > true

	//int connectedShapeConstID = -1;	//const id of shape, with which is line connected
	//int numberOfShapesPointForLines = -1; // number of point of pointOfLine array. Need for linking 
};

class EllipseShape :public IShape
{
public:
	EllipseShape(CPoint centerOfShape, bool isNormalized, int size, ShapeType type, COLORREF outlineColor, COLORREF fillColor, int outlineSize, int outlineType, int fillType);
	void draw(CDC* dc);
	bool isClickedOnShapeRgn(CPoint point);
	CPoint* getConstPointerForRgn(bool firstSemicircle)  { return (firstSemicircle) ? &eFP[0] : &eSP[0]; };
	int getSizeOfShapeArray(bool isFirstSemicircle)		 { return (isFirstSemicircle) ? eFP.size() : eSP.size(); };
	bool isReversed() { return isReversedVar; }
	CPoint getCoordinateForChange(int num) { if (num >= 0 && num < 4) return points[num]; };
	void setCoordinateForChange(int num, CPoint point) { if (num >= 0 && num < 4) points[num] = point; };
	bool isClickedPointForChange(CPoint point);
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
	//CPoint getLineCoordinate();
	CPoint getCoordinateForChange(int num) { if (num >= 0 && num < 2) return pointsOfLine[num]; };
	void setCoordinateForChange(int num, CPoint point) { if (num >= 0 && num < 2) pointsOfLine[num] = point; };
	bool isClickedPointForChange(CPoint point);
	
};



