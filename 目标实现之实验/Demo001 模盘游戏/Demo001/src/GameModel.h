#ifndef _GAME_MODEL_H
#define _GAME_MODEL_H

#include "GameRole.h"
#include "GamePosition.h"

/* 棋盘数据 */
class GameModel
{
public:
	GameModel();

	// 重置游戏
	void reset();

	// 获取x,y处的角色
	GameRole* at(GamePosition pos);

	// 测试：是否可以从from位置移到to位置
	bool canMoveTo(GamePosition from, GamePosition to);

	// 移动
	void moveTo(GamePosition from, GamePosition to);

private:
	// 记录每一位置有哪个角色
	GameRole* m_layout[4][4];

	// 创建N个角色 (本例中一共2个角色)
	GameRole* m_roles[2];
};


#endif


