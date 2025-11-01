#ifndef _CHESSBOARD_HEAD_H
#define _CHESSBOARD_HEAD_H

#include <iostream>
#include "Chess.hpp"

#define MIN_X 1
#define MAX_X 57
#define MIN_Y 1
#define MAX_Y 29

#define X_SKIP 4
#define Y_SKIP 2

#define MAX_LINE   15
#define MAX_COLUMN 15

using namespace std;

class ChessBoard
{
public:
	~ChessBoard()
	{
		fprintf(stderr,"\033[%d;%dH",MAX_Y + 1,MIN_X);
		for(int i = 0;i < MAX_LINE;i ++){
			for(int j = 0;j < MAX_COLUMN;j ++){
				if(this->chess[i][j]){
					delete chess[i][j];
				}
			}
		}
	}
	
	bool isVaildPostion(int x,int y)
	{
		if(x < MIN_X || y < MIN_Y){
			return false;
		}

		if(x > MAX_X || y > MAX_Y){
			return false;
		}

		int line   = y  / Y_SKIP;
		int column = x  / X_SKIP;

		return chess[line][column] ? false:true;
	}

	static ChessBoard *getChessBoard(void)
	{
		if(!chessBoard){
			chessBoard = new ChessBoard;
		}

		return chessBoard;
	}

	void show(void) const
	{
		FILE *fp;
		char buf[1024];

		fp = fopen("ChessBoard.txt","r");
		if(!fp){
			perror("Fail to fopen ChessBoard.txt");
			return;
		}
		

		fprintf(stderr,"\033[%d;%dH",MIN_Y,MIN_X);

		while(fgets(buf,sizeof(buf),fp)){
			fprintf(stderr,"%s",buf);
		}

		fclose(fp);
	}

	void placeChess(const Chess *chess)
	{
		int line   = chess->getY()/Y_SKIP;
		int column = chess->getX()/X_SKIP;

		this->chess[line][column] = chess;
		chess->show();

		currentLine = line;
		currentColumn = column;

		return;
	}

	int getCurrentLine(void) const
	{
		return currentLine;
	}

	int getCurrentColumn(void) const
	{
		return currentColumn;
	}

	bool isSameColorChess(const string &color,int line,int column)
	{
		if(line < 0 || line >= MAX_LINE){
			return false;
		}

		if(column < 0 || column >= MAX_COLUMN){
			return false;
		}

		auto chess = this->chess[line][column];
		if(!chess || chess->getColor() != color){
			return false;
		}

		return true;
	}

	class GC
	{
		public:
			~GC()
			{
				if(chessBoard){
					delete chessBoard;
				}
			}
	};

private:
	ChessBoard()
	{
		for(int i = 0;i < MAX_LINE;i ++){
			for(int j = 0;j < MAX_COLUMN;j ++){
				this->chess[i][j] = nullptr;
			}
		}
	}
	
	int currentLine;
	int currentColumn;
	static ChessBoard *chessBoard;
	static GC gc;
	const Chess *chess[MAX_LINE][MAX_COLUMN];
};

ChessBoard *ChessBoard::chessBoard = nullptr;
ChessBoard::GC gc;

#endif
