#pragma once
#include <afx.h>
#include <set>
using namespace std;

enum class LineType { Basic, Left, Right, Double };

class Lines :
    public CObject
{
public:
    Lines(CPoint firstPoint, LineType, COLORREF, int, int);
    void draw(CDC *dc);
    ~Lines();
    static set<int> IDs;
    static set<CString> names;
    static int countOfLines;


    COLORREF lineColor;
    int lR, lG, lB;
    int lineType;
    int lineSize;
    CString name;
    int constID;
    int ID;
    bool first_ID_not_excist = false; //default
    bool second_ID_not_exceist = false; //default
    int FirstShapeConstID;
    int SecondShapeConstID;
    LineType type;
    //void draw(int, int, LineType);
    
};


