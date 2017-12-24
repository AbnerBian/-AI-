#ifndef GAMEVIEW_H
#define GAMEVIEW_H

#include <QFrame>
#include <QtGui>

#include "GameModel.h"

class GameView : public QFrame
{
	Q_OBJECT

public:
	GameView(QWidget *parent);
	~GameView();

private:
	virtual void paintEvent ( QPaintEvent * event );
	virtual void resizeEvent ( QResizeEvent * event );

	// ���֧��
	void mouseDoubleClickEvent ( QMouseEvent * event );
	void mouseMoveEvent ( QMouseEvent * event );
	void mousePressEvent ( QMouseEvent * event );
	void mouseReleaseEvent ( QMouseEvent * event );

	// �Ϸ�֧��
	void dragEnterEvent(QDragEnterEvent *event);
	void dragLeaveEvent (QDragLeaveEvent * event );
	void dragMoveEvent (QDragMoveEvent * event );
	void dropEvent(QDropEvent *event);


private:
	// ������Ϸ
	void reset();

	// �����ڸı��Сʱ�����¼��㵥Ԫ���С
	void caculate();

	// �����λ�û������Ԫ������
	GamePosition getPostion(QPoint pt);

	// ��Ԫ�����ĵ��ȵ�����
	QRect hotArea(GamePosition pos);

	// ��Ԫ������
	QRect selectedArea(GamePosition pos);

private:
	QRect m_cells[4][4] ; // 4x4����,ÿ����Ԫ�ľ���λ��	
	GameModel m_gameModel;// ��Ϸ����

private:
	/* �ϷŲ��� */	
	bool m_mousePressed; // ��갴��ʱ����ʼ�϶�	
	QPoint m_dragPosition;  // �϶����������
	GamePosition m_posFrom; // ���϶����Ǹ���ʼ����
	GameRole* m_draggedIem; // ���϶����Ǹ���Ԫ����Ķ���

	bool m_allowDrop; // �Ϸ�̽�⣺����drop������
	GamePosition m_allowDropPos; // Ŀ�굥Ԫ��λ��
};

#endif // GAMEVIEW_H
