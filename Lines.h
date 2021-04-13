#pragma once
#include <afx.h>
#include <set>
using namespace std;

enum class LineType { Basic, Left, Right, Double };


class Lines :
    public CObject
{
public:
    static set<int> IDs;
    static int countOfLines;

    int constID;
    int ID;
    bool first_ID_not_excist = false; //default
    bool second_ID_not_exceist = false; //default
    int FirstShapeConstID;
    int SecondShapeConstID;
    LineType type;
    //void draw(int, int, LineType);
    Lines(int, int, LineType);
};


