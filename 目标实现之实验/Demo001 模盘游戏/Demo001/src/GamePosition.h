
#ifndef _GAME_POSTION_H
#define _GAME_POSTION_H

/* ��ά���̵�Ԫ���λ�� */

class GamePosition
{
public:
	int x, y;

	GamePosition():x(-1), y(-1)
	{}

	GamePosition(int x, int y) : x(x),y(y) 
	{}

	bool valid() const
	{
		return x>=0 && y>=0 ;
	}
};

#endif

