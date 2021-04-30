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

#define RIGHT_LINE 0
#define LEFT_LINE 1
#define PI 3.141592653
#define ANGLE_OF_ARROW_DEG 10
#define LENGTH_OF_LINE_FOR_ELLIPSE_OF_ROTATE_TOOL 40
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
#define DRAW_METHOD 2
#define DIFFERENCE_FOR_FILL_RGN 1
#define R_SELECTED_SHAPE 100
#define G_SELECTED_SHAPE 100
#define B_SELECTED_SHAPE 100

enum class Tools { select_tool, ellipse, rectangle, triangle, move, change, rotate, shapeNormalize, shapeMove, doubleSelectTool, basicLine, leftLine, rightLine, doubleLine };
enum class ShapeType { ellipse, rectangle, triangle, basicLine, rightLine, leftLine, doubleLine };

class IShape
{
public:
	virtual void draw(CDC* dc) = 0;
	virtual bool isClickedOnShapeRgn(CPoint point);											// ckecked if clickpoint is in shape region
	virtual bool isClickedPointForChange(CPoint point);										// checked if clickpoint is in a point for change region
	virtual CPoint getCoordinateForChange(int num) { if (num >= 0 && num < 4) return selectedAreaPoints[num]; };		// get coordinate of points that is used for change of shapes properites. Num -> number of point
	virtual void setCoordinateForChange(int num, CPoint point) { if (num >= 0 && num < 4) selectedAreaPoints[num] = point; };	// set coordinate of points that is used for change of shapes properites. Num -> number of point
																																//getters and setters for safe document
	// isSelected get and set
	bool getSelected() { return isSelected; }// get if is shape or line selected or not
	void setSelected(bool isSelected) { this->isSelected = isSelected; };

	// centerOfShape get and set
	CPoint getCenterOfShape() { return centerOfShape; };
	void setCenterOfShape(CPoint centerOfShape) { this->centerOfShape = centerOfShape; };

	// size get and set
	int getSize() { return size; };
	void setSize(int size) { this->size = size; };

	// angleRad get and set
	double getAngleRad() { return angleRad; };
	void setAngleRad(double angleRad) { this->angleRad = angleRad; };

	// ID get and set
	int getID() { return ID; };
	void setID(int ID) { this->ID = ID; };

	// constID get and set
	int getConstID() { return constID; };
	void setConstID(int constID) { this->constID = constID; };

	// name get and set
	CString getName() { return name; };
	void setName(CString name) { this->name = name; };

	// outlineColor get and set
	COLORREF getOutlineColor() { return outlineColor; };
	void setOutlineColor(COLORREF outlineColor) { this->outlineColor = outlineColor; };

	// fillColor get and set
	COLORREF getFillColor() { return fillColor; };
	void setFillColor(COLORREF fillColor) { this->fillColor = fillColor; };

	// outlineSize get and set
	int getOutlineSize() { return outlineSize; };
	void setOutlineSize(int outlineSize) { this->outlineSize = outlineSize; };

	// outlineType get and set
	int getOutlineType() { return outlineType; };
	void setOutlineType(int outlineType) { this->outlineType = outlineType; };

	// fillType get and set
	int getFillType() { return fillType; };
	void setFillType(int fillType) { this->fillType = fillType; };

	// isConnected get and set
	bool getIsConnected(int numberOfPoint);
	void setIsConnected(int numberOfPoint, bool isConnected);

	// connectedShapeConstID get and set
	int getConnectedShapeConstID(int numberOfPoint);
	void setConnectedShapeConstID(int numberOfPoint, int constID);

	// numberOfShapesPointForLines get and set
	int getNumberOfShapesPointForLines(int numberOfPoint);
	void setNumberOfShapesPointForLines(int numberOfPoint, int numberOfShapesPoint);

	// others getters and setters
	// temporaryDxDy get and set
	CPoint getTemporaryDxDy(int num) {
		return (num < temporaryDxDy.size()) ?
			temporaryDxDy[num] : CPoint{ NULL, NULL };
	};										// getter for temporaryDxDy
	void setTemporaryDxDy(int num, CPoint point) { temporaryDxDy[num] = point; };			// setter for temporaryDxDy

	// dxDy get and set
	CPoint getDxDy(int num) {
		return (num < dxDy.size()) ?
			dxDy[num] : CPoint{ NULL, NULL };
	};											// getter for dxDy
	void setDxDy(int num, CPoint point) { dxDy[num] = point; }								// setter for dxDy

	// drawPointsForLines get and set
	void setCanDrawPointsForLines(bool active) { drawPointsForLines = active; };			// setter for drawPointsForLines
	bool getCanDrawPointsForLines() { return drawPointsForLines; };							// getter for drawPointsForLines

	// tempDxDy get and set
	void setShapeMoveTempDxDy(CPoint point) { shapeMove.tempDxDy.x = point.x; shapeMove.tempDxDy.y = point.y; };
	CPoint getShapeMoveTempDxDy() { return shapeMove.tempDxDy; };

	// startClickedCoordinate get and set
	void setShapeMoveStartClickedCoordinate(CPoint point) { shapeMove.startClickedCoordinate = point; };
	CPoint getShapeMoveStartClickedCoordinate() { return shapeMove.startClickedCoordinate; };

	// startClickedCoordinate get and set
	void setChangeStartClickedCoordinate(CPoint point) { change.startClickedCoordinate = point; };
	CPoint getChangeStartClickedCoordinate() { return change.startClickedCoordinate; };

	// tempDxDy get and set
	void setChangeTempDxDy(int num, CPoint point) { change.tempDxDy[num] = point; };
	CPoint getChangeTempDxDy(int num) { return change.tempDxDy[num]; };

	// dxDy get and set
	void setChangeDxDy(int num, CPoint point) { change.dxDy[num] = point; };
	CPoint getChangeDxDy(int num) { return change.dxDy[num]; };

	// linkingPoints get and set
	void setPointsForLine(int numberOfPoint, CPoint coordinatesOfPoint)
	{
		if (numberOfPoint >= 0 && numberOfPoint < 4) { linkingPoints[numberOfPoint] = coordinatesOfPoint; };
	}
	CPoint getPointForLine(int numberOfPoint)
	{
		return (numberOfPoint >= 0 && numberOfPoint < 4) ? linkingPoints[numberOfPoint] : CPoint{ NULL, NULL }; //getter for pointsForLines
	}

	// firstClickedPoint get and set
	void setFirstClickedPoint(CPoint point) { firstClickedPoint = point; };			// set first clicked points x, y before mouse get OnMouseMove and LButton is pressed down
	CPoint getFirstClickedPoint() { return firstClickedPoint; };					// get first clicked points x, y before mouse get OnMouseMove and LButton is pressed down


	bool IsClickedOnPointForLines(CPoint point, int& numberOfPoint);						// check if is click point in one of the 4 points for lines 									
	int getNumberOfPointForChange() { return numberOfPoint; }								// get number of clicked point from method isClickedPointForChange
	CPoint rotateAndMoveCoordinate(CPoint &point, int from);								// is used for rotate coordinates of shape and move it
	void rotateShape(CPoint point);															// is used for rotating of shape 
	void moveChangeRotate(vector<IShape*>& shapes, Tools& toolIsUsed, CPoint point, bool &canBeUnselected, bool &shapeIsFound); // called after lButtonDown to get Tool
	void normalizeShape();																	// get normalized shape
	double degToRad(double degree) { return degree * PI / 180.0; };							// convert degree to radian
	double radToDeg(double radian) { return radian * 180.0 / PI; };							// convert radian to degree
	void createLineConnection(int numberOfPointOfLine, int shapeConstID, int numberOfPointForLines); // create connection for line
	void updateLineConnection(const vector<IShape*>& shapes);										// update connection for line
	void lineDisconnecting(int numberOfPointOfLine, int shapeConstID);								// disconnect line
	void setShapeID();														//set shape ID in constructor
	void setShapeName();													// set shape name in constructor
	CPoint getPointForRotateTool() { return centerPoint23Top; };			// return point for rotate tool
	int getSizeOfShapeArray(bool isFirstSemicircle) { return NULL; };				// size of array, that includes all points of shape
	bool isReversed() { return isReversedVar; };									// is needed for rotate shape. Angle for rotate will be -, when return is true
	ShapeType getShapeType() { return type; };								// get shape type
	
	static set <int>& getIDs() { return IDs; };								// getter for static IDs
	static set <CString>& getNames() { return names; };						// getter for static names
	static void setCountOfShape(int number) { countOfShape = number; };		// setter for static countOfShape

	// dx set and get
	static void setDx(int dxSet) { dx = dxSet; };							
	static int getDx() { return dx; };

	// dy set and get
	static int getDy() { return dy; };
	static void setDy(int dySet) { dy = dySet; };
	
	//destructor
	virtual ~IShape();

protected:
	ShapeType type; //store types of all shapes
	static int dx; // is used to move all shapes (move tool and scrollbars) in the x direction
	static int dy; // is used to move all shapes (move tool and scrollbars) in the y direction
	static set<int> IDs; // is used to store all IDs of all shapes to check new IDs -> unique or not
	static set<CString> names; // is used to store all names of all shapes to check new names -> unique or not
	static int countOfShape; // store count of all shapes


	
	CPoint centerOfShape{ NULL, NULL };

	CPoint firstPoint{ 0,0 };
	int size; // length of inscribed circle in shape
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

	const CPoint shapeCenterBeforRotate{ 0, 0 };

	CPoint centerPoint23Bottom{ NULL, NULL };			// center of rectangle topside. Needed to select shape
	CPoint centerPoint23Top{ NULL, NULL };				// point that lies higher of centerPoint23Bottom. Point is using for drawing ellipse for rotate tool
	CPoint firstClickedPoint{ NULL, NULL };			    // array for x and y coordinates. It is using for save last X and Y before mouse get OnMouseMove and LButton is pressed down
	//array <CPoint, 4> pointsForLines;					// needed for linking of shapes
	array <CPoint, 2> pointsOfLine;						// first and second point of any line [0] - first, [1] - second
	bool isReversedVar = false;							// value that demonstrate if shape is reversed or not
	int numberOfPoint = NULL;							// number of clicked point for change the shape
	array <CPoint, 4> temporaryDxDy;					// array for temporary difference values for dx and dy, when shape is moved. 
	array <CPoint, 4> dxDy;								// array that contains dx and dy to change points coordinate (it contains also temporaryDxDy values)
	bool drawPointsForLines = false;					// var that set if is points for lines drawn or not
	bool isSelected = false;
	double angleRad = NULL;
	

	struct shapeMove
	{
		CPoint tempDxDy{ NULL, NULL }; //temporary coordinate that us used for displaying the movement of shapes, when lbutton is down
		CPoint startClickedCoordinate{ NULL, NULL }; // coordinate that saved when LButtonDown is clicked
	} shapeMove;

	struct change
	{
		array <CPoint, 4> dxDy;
		array <CPoint, 4> tempDxDy;
		CPoint startClickedCoordinate{ NULL, NULL }; // coordinate that saved when LButtonDown is clicked
	} change;

	struct connecting
	{
		struct isConnected { bool firstPointOfLine = false; bool secondPointOfLine = false; }isConnected;
		struct connectedShapeConstID { int firstPointOfLine = -1; int secondPointOfLine = -1; }connectedShapeConstID;
		struct numberOfShapesPointForLines { int firstPointOfLine = -1; int secondPointOfLine = -1; }numberOfShapesPointForLines;
	} connecting;

	//for shape
	array<CPoint, 4> selectedAreaPoints;
	array<CPoint, 4> linkingPoints;
	vector<CPoint> fillAreaPoints;
	vector<CPoint> shapePoints;
};

class EllipseShape :public IShape
{
public:
	EllipseShape(CPoint centerOfShape, bool isNormalized, int size, ShapeType type, COLORREF outlineColor, COLORREF fillColor, int outlineSize, int outlineType, int fillType);
	void draw(CDC* dc);	
};

class RectangleShape :public IShape
{
public:
	RectangleShape(CPoint centerOfShape, bool isNormalized, int size, ShapeType type, COLORREF outlineColor, COLORREF fillColor, int outlineSize, int outlineType, int fillType);
	void draw(CDC* dc);
};

class TriangleShape : public IShape
{
public:
	TriangleShape(CPoint centerOfShape, bool isNormalized, int size, ShapeType type, COLORREF outlineColor, COLORREF fillColor, int outlineSize, int outlineType, int fillType);
	void draw(CDC* dc);
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
	void getPointsOfArrow(int forLineType, CPoint& firstPointOfArrow, CPoint& secondPointOfArrow);
};



