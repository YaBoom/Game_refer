#ifndef _KEY_HANDLE_HEAD_H
#define _KEY_HANDLE_HEAD_H

#include <stdio.h>
#include <iostream>
#include <map>
#include <termios.h>
#include <unistd.h>
#include "Cursor.hpp"
#include <functional>

using namespace std;

#define PLACE_CHESS_KEY ' '

class KeyHandle
{
	public:
		
		KeyHandle(){
			struct termios attr; 
			tcgetattr(0,&attr); //获取属性 
			attr.c_lflag &= ~(ICANON | ECHO);//关闭回车确认和回显 
			tcsetattr(0,TCSANOW,&attr);//设置属性

			keyMap.insert(pair<char,function<void(void)>>('w',std::bind(&Cursor::move,&cursor,Cursor::UP)));
			keyMap.insert(pair<char,function<void(void)>>('W',std::bind(&Cursor::move,&cursor,Cursor::UP)));

			keyMap.insert(pair<char,function<void(void)>>('s',std::bind(&Cursor::move,&cursor,Cursor::DOWN)));
			keyMap.insert(pair<char,function<void(void)>>('S',std::bind(&Cursor::move,&cursor,Cursor::DOWN)));
		
			keyMap.insert(pair<char,function<void(void)>>('a',std::bind(&Cursor::move,&cursor,Cursor::LEFT)));
			keyMap.insert(pair<char,function<void(void)>>('A',std::bind(&Cursor::move,&cursor,Cursor::LEFT)));
		
			keyMap.insert(pair<char,function<void(void)>>('d',std::bind(&Cursor::move,&cursor,Cursor::RIGHT)));
			keyMap.insert(pair<char,function<void(void)>>('D',std::bind(&Cursor::move,&cursor,Cursor::RIGHT)));
		}

		~KeyHandle(){
			struct termios attr; 
			tcgetattr(0,&attr); //获取属性 
			attr.c_lflag |= (ICANON | ECHO);//回车确认和回显 
			tcsetattr(0,TCSANOW,&attr);//设置属性
		}
		
		void waitPlayerPlaceChess(Player *player)
		{
			int ch;
			bool ok = false;
			
			do{
				tcflush(0,TCIFLUSH);
				ch = getchar();
				if(ch == PLACE_CHESS_KEY){
					ok = player->placeChess(cursor.getX(),cursor.getY());
				}else{
					auto it = keyMap.find(ch);
					if(it != keyMap.end()){
						auto handle = it->second;
						handle();
					}
				}

			}while(!ok);
		}

		int getCursorX(void) const{
			return cursor.getX();
		}

		int getCursorY(void) const{
			return cursor.getY();
		}

		void setCursorPos(int x,int y)
		{
			cursor.setPos(x,y);
		}
	
	private:
		Cursor cursor;
		map<char,function<void(void)>> keyMap;
};

#endif
