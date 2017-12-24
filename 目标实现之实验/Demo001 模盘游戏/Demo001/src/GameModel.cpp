
#include <stdio.h>
#include <math.h>
#include <string.h>

#include "GameModel.h"
#include <QDebug>

GameModel::GameModel()
{
	// ������ɫ
	m_roles[0] = new GameRole(GameRole::RED, ":/Resources/roleRed.png");
	m_roles[1] = new GameRole(GameRole::BLUE, ":/Resources/roleBlue.png");

	reset();
}

void GameModel::reset()
{
	// ��ɫ�ĳ�ʼλ��
	memset(m_layout, 0, sizeof(m_layout));
	m_layout[0][0] = m_roles[0]; // ����
	m_layout[3][3] = m_roles[1]; // ����
}

// ��ȡx,y���Ľ�ɫ
GameRole* GameModel::at(GamePosition pos)
{
	return m_layout[pos.x][pos.y];
}

// ���ԣ��Ƿ���Դ�fromλ���Ƶ�toλ��
bool GameModel::canMoveTo(GamePosition from, GamePosition to)
{
	qDebug("canMoveTo: (%d,%d) -> (%d,%d) ", from.x, from.y, to.x, to.y);

	GameRole* roleFrom = at(from);
	GameRole* roleTo = at(to);
	if(roleTo != NULL)
		return false; // Ŀ��λ���Ѿ�������ռλ

	// �������
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

	// �������
	if(roleFrom->id == GameRole::BLUE)
	{
		int dx = from.x - to.x;
		int dy = from.y - to.y;
		if(abs(dx) == 1 && abs(dy) == 1)
			return true;
	}

	return false;
}

// �ƶ�
void GameModel::moveTo(GamePosition from, GamePosition to)
{
	GameRole* role = at(from);
	m_layout[from.x][from.y] = NULL;
	m_layout[to.x][to.y] = role;
}
