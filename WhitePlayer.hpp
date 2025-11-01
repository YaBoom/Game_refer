#ifndef _WHITE_PLAYER_HEAD_H
#define _WHITE_PLAYER_HEAD_H
#include "Player.hpp"
#include "WhiteChess.hpp"
#include "ChessBoard.hpp"

class WhitePlayer:public Player
{
	public:
		WhitePlayer(const string &name):Player(name,"white"){}
		bool placeChess(int x,int y){
			ChessBoard *chessBoard = ChessBoard::getChessBoard();
			bool ok = chessBoard->isVaildPostion(x,y);
			if(ok){
				chessBoard->placeChess(new WhiteChess(x,y));
			}
		}
};

#endif
