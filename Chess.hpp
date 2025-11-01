#ifndef _CHESS_HEAD_H
#define _CHESS_HEAD_H

#include <iostream>

using namespace std;

class Chess
{
public:
	Chess(const string &color,int x,int y):color(color),x(x),y(y){}
	int getX(void)  const 
	{
		return x;
	}

	int getY(void) const
	{
		return y;
	}


	string getColor(void) const
	{
		return color;
	}

	virtual void show(void) const = 0;
	virtual ~Chess(){}

private:
	int x;
	int y;
	string color;
};

#endif
