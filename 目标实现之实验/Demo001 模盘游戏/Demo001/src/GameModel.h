#ifndef _GAME_MODEL_H
#define _GAME_MODEL_H

#include "GameRole.h"
#include "GamePosition.h"

/* �������� */
class GameModel
{
public:
	GameModel();

	// ������Ϸ
	void reset();

	// ��ȡx,y���Ľ�ɫ
	GameRole* at(GamePosition pos);

	// ���ԣ��Ƿ���Դ�fromλ���Ƶ�toλ��
	bool canMoveTo(GamePosition from, GamePosition to);

	// �ƶ�
	void moveTo(GamePosition from, GamePosition to);

private:
	// ��¼ÿһλ�����ĸ���ɫ
	GameRole* m_layout[4][4];

	// ����N����ɫ (������һ��2����ɫ)
	GameRole* m_roles[2];
};


#endif


