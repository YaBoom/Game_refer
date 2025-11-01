#ifndef _WINLOGO_HEAD_H
#define _WINLOGO_HEAD_H
#include <stdio.h>

#define CHESSBOARD_WIDTH  57
#define CHESSbOARD_HEIGHT 29
#define X_OFFSET          3

class WinLogo
{

public:
	WinLogo(int x = 0,int y = 0,int width = 25,int height = 15)
	{
		this->width  = width;
		this->height = height;
		
		if(!x){
			this->x = CHESSBOARD_WIDTH + X_OFFSET;
		}else{
			this->x = x;
		}

		if(!y){
			this->y = (CHESSbOARD_HEIGHT - height)/2;
		}else{
			this->y = y;
		}
	}

	void drwaRectangle(int x,int y,int width,int height,int color)
	{
		fprintf(stderr,"\033[%d;%dH",y,x);
		for(int i = 0;i < height;i ++){
			for(int j = 0;j < width;j ++){
				fprintf(stderr,"\033[%dm \033[0m",color);
			}
		
			fprintf(stderr,"\033[%d;%dH",y + i,x);
		}
	}

	void drawText(int x,int y,const char *text,int background,int fontcolor)
	{
		fprintf(stderr,"\033[%d;%dH\033[%d;%dm%s\033[0m",y,x,background,fontcolor,text);
	}

	void showWinPlayer(const string &name,const string &color)
	{
		drwaRectangle(x,y,width,height,42);
		drwaRectangle(x + 2,y + 1,width,height,47);
		
		string text1 = "The color is ";
		text1 += color;
		drawText(x + 3,y + 1 + height/2 - 2,text1.c_str(),47,33);

		string text2 = "The Winner is ";
		text2 += name;
		drawText(x + 3,y + 2 + height/2 - 2,text2.c_str(),47,34);
		
		drawText(x + 3,y + 3 + height/2 - 2,"The deveoper is : ",47,35);
		drawText(x + 3 + 3,y + 4 + height/2 - 2,"Middle Uncle",47,36);
	}

private:
	int x;
	int y;
	int width;
	int height;
};

#endif
