#pragma once
#include <afx.h>

//enum class LinesTools { };


class Lines :
    public CObject
{
public:
    virtual void draw() = 0;
    virtual ~Lines();
};

class BasicLine : public Lines
{
public:
    void draw();

};

class RightLine : public Lines
{
public:
    void draw();
};

class LeftLine : public Lines
{
public:
    void draw();
};



class DoubleLine : public Lines
{
public:
    void draw();
};

