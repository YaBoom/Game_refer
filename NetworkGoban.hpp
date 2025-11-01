#ifndef _NETWORKGOBAN_HEAD_H
#define _NETWORKGOBAN_HEAD_H

#include "NetworkPlayer.hpp"
#include "KeyHandle.hpp"
#include "Judge.hpp"
#include "WinLogo.hpp"

class NetworkGoban
{
public:
	NetworkGoban(const string &blackPlayerName,const string &whitePlayerName)
	{
		inputInfo();

		ChessBoard *chessBoard = ChessBoard::getChessBoard();
		chessBoard->show();	
		keyHandle = new KeyHandle;
		
		if(chessColor == "white"){
			whitePlayer = new NetworkPlayer(
						whitePlayerName,
						"white",
						keyHandle,
						peerIP,
						peerPort,
						true
					);

			blackPlayer = new NetworkPlayer(
						blackPlayerName,
						"black",
						keyHandle,
						selfIP,
						selfPort
					);
		}else{
			blackPlayer = new NetworkPlayer(
						blackPlayerName,
						"black",
						keyHandle,
						peerIP,
						peerPort,
						true
					);

			whitePlayer = new NetworkPlayer(
						whitePlayerName,
						"white",
						keyHandle,
						selfIP,
						selfPort
					);
		}	
	}

	void run(void)
	{
		bool win = false;
		NetworkPlayer *players[] = {whitePlayer,blackPlayer};	
		
		while(!win){
			for(NetworkPlayer *player:players){
				player->waitPlaceChess();	
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

	~NetworkGoban()
	{
		delete whitePlayer;
		delete blackPlayer;
		delete keyHandle;
	}

	void inputInfo(void)
	{
		cout << "Input chess color : ";
		cin >> chessColor;
		cout << "Input Self IP : ";
		cin >> selfIP;
		cout << "Input Self Port : ";
		cin >> selfPort;
		cout << "Input peer IP : ";
		cin >> peerIP;
		cout << "Input peer Port : ";
		cin >> peerPort;
	}

private:
	Judge judge;
	WinLogo logo;
	string chessColor;
	string selfIP;
	string selfPort;
	string peerIP;
	string peerPort;
	KeyHandle *keyHandle;
	NetworkPlayer *whitePlayer;
	NetworkPlayer *blackPlayer;
};

#endif
