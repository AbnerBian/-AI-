
#ifndef _GAME_ROLE_H
#define _GAME_ROLE_H

#include <QPixmap>

/* 角色定义 */

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
	// 每个角色设置一个ID类型
	enum{ BLUE, RED };

public:
	int id; // ID
	QPixmap icon; // 相应的图标显示
};




#endif

