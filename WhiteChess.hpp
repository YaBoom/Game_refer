#ifndef _WHITE_CHESS_HEAD_H
#define _WHITE_CHESS_HEAD_H

#include <iostream>
#include "Chess.hpp"

using namespace std;

class WhiteChess:public Chess
{
public:
	WhiteChess(int x,int y):Chess("white",x,y){}
	void show(void) const
	{
		fprintf(stderr,"\033[%d;%dH\033[44;35m[☺]\033[0m",getY(),getX() - 1);
		fprintf(stderr,"\033[%d;%dH",getY(),getX());
	}
};

#endif
