#pragma once
#include <afx.h>

enum class LineType { Basic, Left, Right, Double };


class Lines :
    public CObject
{
public:
    int FirstShapeConstID;
    int SecondShapeConstID;
    LineType type;
    //void draw(int, int, LineType);
    Lines(int, int, LineType);
};


