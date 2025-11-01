#ifndef _JUDEG_HEAD_H
#define _JUDEG_HEAD_H
#include "Player.hpp"
#include "ChessBoard.hpp"

class Judge
{
	public:
		bool isWin(Player *player)
		{
			bool ok = false;
			string chessColor = player->getColor();
		
			ok = isHorziontalWin(chessColor);
			if(ok){
				return true;
			}

			ok = isVerticalWin(chessColor);
			if(ok){
				return true;
			}

			ok = isUphillWin(chessColor);
			if(ok){
				return true;
			}

			ok = isDownhillWin(chessColor);
			if(ok){
				return true;
			}

			return ok;
		}

		bool isHorziontalWin(const string &chessColor)
		{
			int count = 0;
			ChessBoard *chessBoard = ChessBoard::getChessBoard();
			int curLine   = chessBoard->getCurrentLine();
			int curColumn = chessBoard->getCurrentColumn();

			//right
			for(int i = 0;i < 5;i ++){
				if(chessBoard->isSameColorChess(chessColor,curLine,curColumn + i)){
					count ++;
				}else{
					break;
				}
			}

			if(count >= 5){
				return true;
			}

			//left
			for(int i = 0;i < 5;i ++){
				if(chessBoard->isSameColorChess(chessColor,curLine,curColumn - i)){
					count ++;
				}else{
					break;
				}
			}

			
			return count - 1 >= 5 ? true:false;
		}

		bool isVerticalWin(const string &chessColor)
		{
			int count = 0;
			ChessBoard *chessBoard = ChessBoard::getChessBoard();
			int curLine   = chessBoard->getCurrentLine();
			int curColumn = chessBoard->getCurrentColumn();

			//up
			for(int i = 0;i < 5;i ++){
				if(chessBoard->isSameColorChess(chessColor,curLine - i,curColumn)){
					count ++;
				}else{
					break;
				}
			}

			if(count >= 5){
				return true;
			}

			//down
			for(int i = 0;i < 5;i ++){
				if(chessBoard->isSameColorChess(chessColor,curLine + i,curColumn)){
					count ++;
				}else{
					break;
				}
			}

			
			return count - 1 >= 5 ? true:false;
		}

		bool isUphillWin(const string &chessColor)
		{
			int count = 0;
			ChessBoard *chessBoard = ChessBoard::getChessBoard();
			int curLine   = chessBoard->getCurrentLine();
			int curColumn = chessBoard->getCurrentColumn();

			//uphill->up
			for(int i = 0;i < 5;i ++){
				if(chessBoard->isSameColorChess(chessColor,curLine - i,curColumn + i)){
					count ++;
				}else{
					break;
				}
			}

			if(count >= 5){
				return true;
			}

			//uphill->down
			for(int i = 0;i < 5;i ++){
				if(chessBoard->isSameColorChess(chessColor,curLine + i,curColumn - i)){
					count ++;
				}else{
					break;
				}
			}

			
			return count - 1 >= 5 ? true:false;
		}

		bool isDownhillWin(const string &chessColor)
		{
			int count = 0;
			ChessBoard *chessBoard = ChessBoard::getChessBoard();
			int curLine   = chessBoard->getCurrentLine();
			int curColumn = chessBoard->getCurrentColumn();

			//downhill->up
			for(int i = 0;i < 5;i ++){
				if(chessBoard->isSameColorChess(chessColor,curLine - i,curColumn - i)){
					count ++;
				}else{
					break;
				}
			}

			if(count >= 5){
				return true;
			}

			//downhill->down
			for(int i = 0;i < 5;i ++){
				if(chessBoard->isSameColorChess(chessColor,curLine + i,curColumn + i)){
					count ++;
				}else{
					break;
				}
			}

			
			return count - 1 >= 5 ? true:false;
		}
};

#endif
