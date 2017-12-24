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

	// 鼠标支持
	void mouseDoubleClickEvent ( QMouseEvent * event );
	void mouseMoveEvent ( QMouseEvent * event );
	void mousePressEvent ( QMouseEvent * event );
	void mouseReleaseEvent ( QMouseEvent * event );

	// 拖放支持
	void dragEnterEvent(QDragEnterEvent *event);
	void dragLeaveEvent (QDragLeaveEvent * event );
	void dragMoveEvent (QDragMoveEvent * event );
	void dropEvent(QDropEvent *event);


private:
	// 重置游戏
	void reset();

	// 当窗口改变大小时，重新计算单元格大小
	void caculate();

	// 从鼠标位置换算出单元格坐标
	GamePosition getPostion(QPoint pt);

	// 单元格中心的热点区域
	QRect hotArea(GamePosition pos);

	// 单元格区域
	QRect selectedArea(GamePosition pos);

private:
	QRect m_cells[4][4] ; // 4x4方格,每个单元的具体位置	
	GameModel m_gameModel;// 游戏数据

private:
	/* 拖放操作 */	
	bool m_mousePressed; // 鼠标按下时，开始拖动	
	QPoint m_dragPosition;  // 拖动操作的起点
	GamePosition m_posFrom; // 被拖动的那个起始坐标
	GameRole* m_draggedIem; // 被拖动的那个单元格里的对象

	bool m_allowDrop; // 拖放探测：允许drop在这里
	GamePosition m_allowDropPos; // 目标单元格位置
};

#endif // GAMEVIEW_H
