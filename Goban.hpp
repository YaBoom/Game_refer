#ifndef _GOBAN_HEAD_H
#define _GOBAN_HEAD_H

#include "BlackPlayer.hpp"
#include "WhitePlayer.hpp"
#include "KeyHandle.hpp"
#include "Judge.hpp"
#include "WinLogo.hpp"

class Goban
{
public:
	Goban(const string &blackPlayerName,const string &whitePlayerName)
	{
		players[0] = new WhitePlayer(whitePlayerName);
		players[1] = new BlackPlayer(blackPlayerName);

		ChessBoard *chessBoard = ChessBoard::getChessBoard();
		chessBoard->show();
		
		keyHandle = new KeyHandle;
	}

	void run(void)
	{
		bool win = false;
		
		while(!win){
			for(Player *player:players){
				keyHandle->waitPlayerPlaceChess(player);
				bool ok = judge.isWin(player);
				if(ok){
					win = true;
					logo.showWinPlayer(player->getName(),
									   player->getColor());
					break;
				}
			}
		}
	}

	~Goban()
	{
		delete players[0];
		delete players[1];
		delete keyHandle;
	}

private:
	Player *players[2];
	Judge judge;
	WinLogo logo;
	KeyHandle *keyHandle;
};

#endif
