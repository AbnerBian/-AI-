
#ifndef _GAME_ROLE_H
#define _GAME_ROLE_H

#include <QPixmap>

/* ��ɫ���� */

class GameRole
{
public:
	GameRole():id(-1)
	{
	}
	GameRole(int id, QString imagePath)
	{
		this->id = id;
		icon.load(imagePath);
	}

public:
	// ÿ����ɫ����һ��ID����
	enum{ BLUE, RED };

public:
	int id; // ID
	QPixmap icon; // ��Ӧ��ͼ����ʾ
};




#endif

