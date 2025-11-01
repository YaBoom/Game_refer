#ifndef _NETWORK_PLAYER_HEAD_H
#define _NETWORK_PLAYER_HEAD_H

#include "Player.hpp"
#include "KeyHandle.hpp"
#include <sys/types.h>	       /* See NOTES */
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "BlackChess.hpp"
#include "WhiteChess.hpp"
#include "ChessBoard.hpp"

class Point
{
public:
	Point(){}
	Point(int x,int y):x(x),y(y){}
	int getX(void) const{
		return x;
	}

	int getY(void) const{
		return y;
	}

private:
	int x;
	int y;
};

class NetworkPlayer:public Player
{
public:
	NetworkPlayer(
				  	const string &name,
				  	const string &color,
				  	KeyHandle *keyHandle,
				  	const string &ip,
				  	const string &port,
					bool localUser = false
				  ):Player(name,color),
					keyHandle(keyHandle),
					localUser(localUser)
	{
		sockfd = socket(AF_INET,SOCK_DGRAM,0);
		if(sockfd < 0){
			perror("Fail to socket");
			return;
		}

		if(localUser){
			this->peerIP   = ip;
			this->peerPort = port;
		}else{
			struct sockaddr_in sockaddr;
			sockaddr.sin_family = AF_INET;
			sockaddr.sin_port   = htons(atoi(port.c_str()));
			sockaddr.sin_addr.s_addr = inet_addr(ip.c_str());
			int ret = bind(sockfd,(struct sockaddr *)&sockaddr,sizeof(sockaddr));
			if(ret < 0){
				perror("Fail to bind");
				return;
			}
		}		
	}

	~NetworkPlayer()
	{
		close(sockfd);
	}

	bool recvPointFromPeer(Point &point)
	{
		int ret = recvfrom(sockfd,(void *)&point,sizeof(point),0,NULL,NULL);
		if(ret <= 0){
			perror("Fail to recvfrom");
			return false;
		}
	
		return true;
	}

	bool transPointToPeer(const Point &point,const string &ip,const string &port)
	{
		struct sockaddr_in sockaddr;
		sockaddr.sin_family = AF_INET;
		sockaddr.sin_port   = htons(atoi(port.c_str()));
		sockaddr.sin_addr.s_addr = inet_addr(ip.c_str());
		int ret = sendto(sockfd,(void *)&point,sizeof(point),0,(struct sockaddr *)&sockaddr,sizeof(sockaddr));
		if(ret < 0){
			perror("Fail to sendto");
			return false;
		}

		return true;
	}
	
	bool placeChess(int x,int y){
		ChessBoard *chessBoard = ChessBoard::getChessBoard();
		bool ok = chessBoard->isVaildPostion(x,y);
		if(ok){
			Chess *chess = nullptr;
			if(getColor() == "white"){
				chess = new WhiteChess(x,y);
			}else{
				chess = new BlackChess(x,y);
			}
			chessBoard->placeChess(chess);
		}

		return ok;
	}

	void waitPlaceChess(void)
	{
		if(!localUser){
			Point point;
			bool ok = recvPointFromPeer(point);
			if(ok){
				keyHandle->setCursorPos(point.getX(),point.getY());
				this->placeChess(point.getX(),point.getY());
			}
		}else{
			keyHandle->waitPlayerPlaceChess(this);
			this->transPointToPeer(Point(keyHandle->getCursorX(),keyHandle->getCursorY()),peerIP,peerPort);
		}	
	}

private:
	int sockfd;
	bool localUser;
	string peerIP;
	string peerPort;
	KeyHandle *keyHandle;
};

#endif
