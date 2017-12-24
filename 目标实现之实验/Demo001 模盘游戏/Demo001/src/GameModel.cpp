
#include <stdio.h>
#include <math.h>
#include <string.h>

#include "GameModel.h"
#include <QDebug>

GameModel::GameModel()
{
	// 创建角色
	m_roles[0] = new GameRole(GameRole::RED, ":/Resources/roleRed.png");
	m_roles[1] = new GameRole(GameRole::BLUE, ":/Resources/roleBlue.png");

	reset();
}

void GameModel::reset()
{
	// 角色的初始位置
	memset(m_layout, 0, sizeof(m_layout));
	m_layout[0][0] = m_roles[0]; // 红棋
	m_layout[3][3] = m_roles[1]; // 蓝棋
}

// 获取x,y处的角色
GameRole* GameModel::at(GamePosition pos)
{
	return m_layout[pos.x][pos.y];
}

// 测试：是否可以从from位置移到to位置
bool GameModel::canMoveTo(GamePosition from, GamePosition to)
{
	qDebug("canMoveTo: (%d,%d) -> (%d,%d) ", from.x, from.y, to.x, to.y);

	GameRole* roleFrom = at(from);
	GameRole* roleTo = at(to);
	if(roleTo != NULL)
		return false; // 目标位置已经有棋子占位

	// 红棋规则
	if(roleFrom->id == GameRole::RED)
	{
		if(from.x == to.x)
		{
			if(abs(from.y - to.y) == 1) 
				return true;
		}
		else if(from.y == to.y)
		{
			if(abs(from.x - to.x) == 1) 
				return true;
		}
	}

	// 蓝棋规则
	if(roleFrom->id == GameRole::BLUE)
	{
		int dx = from.x - to.x;
		int dy = from.y - to.y;
		if(abs(dx) == 1 && abs(dy) == 1)
			return true;
	}

	return false;
}

// 移动
void GameModel::moveTo(GamePosition from, GamePosition to)
{
	GameRole* role = at(from);
	m_layout[from.x][from.y] = NULL;
	m_layout[to.x][to.y] = role;
}
