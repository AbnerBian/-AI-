#include "GameView.h"

GameView::GameView(QWidget *parent)
	: QFrame(parent)
{
	// 添加拖放支持
	setAcceptDrops(true);

	reset();

}

GameView::~GameView()
{

}

// 重置游戏
void GameView::reset()
{
	m_gameModel.reset();
	m_mousePressed = false;
	update();
}

// 当窗口改变大小时，重新计算单元格大小
void GameView::caculate()
{
	int width = this->width();
	int height = this->height();

	// 计算4个方格的位置
	for(int i=0; i<4; i++)
	{
		int top = i*height/4;
		int bottom = (i+1) * height/4;

		for(int j=0; j<4; j++)
		{
			int left = j*width/4;
			int right = j*height/4;

			m_cells[i][j] = QRect(left, top, width/4,height/4);
		}
	}
}

// 从鼠标位置换算出单元格坐标
GamePosition GameView::getPostion(QPoint pt)
{
	for(int i=0; i<4; i++)
	{
		for(int j=0; j<4; j++)
		{
			QRect r = m_cells[i][j];
			//r.adjust(2,2,-2,-2);

			if(r.contains(pt))
			{
				return GamePosition(i,j);
			}
		}
	}
	return GamePosition();
}

// 单元格中心的热点区域
QRect GameView::hotArea(GamePosition pos)
{
	QRect rRed = m_cells[pos.x][pos.y];
	QRect rHot = QRect(0,0,33,33);
	rHot.moveCenter(rRed.center());
	return rHot;
}

// 单元格区域
QRect GameView::selectedArea(GamePosition pos)
{
	QRect rSelected = m_cells[pos.x][pos.y];
	return rSelected.adjusted(1,1,-1,-1);
}

// Widget事件
void GameView::resizeEvent ( QResizeEvent * event )
{
	caculate();
}
// Widget事件
void GameView::paintEvent ( QPaintEvent * event )
{
	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing, true);

	int width = this->width();
	int height = this->height();
	QRect rect(0,0, width, height);

	QPen pen;

	// 背景
	painter.setPen(Qt::NoPen);
	painter.setBrush(QBrush(QColor(0xFF,0xFF, 0xFF)));
	painter.drawRect(rect);

	// 4x4方格
	pen.setStyle(Qt::SolidLine);
	pen.setColor(QColor(0x33,0x33, 0x33));
	painter.setPen(pen);
	int i,j;
	for(i=0; i<=4; i++)
	{
		int xpos = i*width/4;
		int ypos = i*height/4;
		painter.drawLine(xpos, 0, xpos, height);
		painter.drawLine(0, ypos, width, ypos);
	}

	// 棋子：如果该单元格里有棋子，则画出该棋子
	for(i=0; i<4; i++)
	{
		for(int j=0; j<4; j++)
		{
			GamePosition pos(i,j);
			GameRole* role = m_gameModel.at(pos);
			if(role != NULL)
			{
				QRect rRed = hotArea(pos);
				painter.drawPixmap(rRed, role->icon);
			}
		}
	}

	// 拖放显示：高亮选中目标单元格
	if(m_mousePressed && m_allowDrop)
	{
		QRect area = selectedArea(m_allowDropPos);
		painter.setBrush(QColor(0x66, 0x66, 0x66));
		painter.drawRect(area);

		QRect hot = hotArea(m_allowDropPos);
		painter.drawPixmap(hot, m_draggedIem->icon);

		pen.setStyle(Qt::DotLine);
		pen.setColor(QColor(0xEE, 0xEE, 0xEE));
		painter.setPen(pen);
		painter.setBrush(Qt::NoBrush);
		painter.drawEllipse(hot.adjusted(-2,-2,2,2));
	}
}

// 忽略双击事件
void GameView::mouseDoubleClickEvent ( QMouseEvent * event )
{
	QWidget::mouseDoubleClickEvent(event);
}

// 鼠标按下
void GameView::mousePressEvent ( QMouseEvent * event )
{
	m_mousePressed = true;
	m_draggedIem = NULL;
	m_allowDrop = false;

	// 记下起点
	m_dragPosition = event->pos();
	m_posFrom = getPostion(event->pos());
	QRect hot = hotArea(m_posFrom);
	if(hot.contains(event->pos()))
	{
		m_draggedIem = m_gameModel.at(m_posFrom);
	}


	QFrame::mousePressEvent(event);
}
// 鼠标松开
void GameView::mouseReleaseEvent ( QMouseEvent * event )
{
	m_mousePressed = false;
	m_allowDrop = false;
	update();
}
// 鼠标移动
void GameView::mouseMoveEvent ( QMouseEvent * event )
{
	if(!m_mousePressed) return;
	if(!m_draggedIem) return;

	// 只允许用左键拖动
	if (!(event->buttons() & Qt::LeftButton))
		return;

	// 移动一定距离后，才算是开始拖动
	if ((event->pos() - m_dragPosition).manhattanLength()
		< QApplication::startDragDistance())
		return;

	// 找到拖动的项
	QString text = "what";

	// 创建数据
	QDrag *drag = new QDrag(this);

	QMimeData *mimeData = new QMimeData;
	mimeData->setData("game/move", QByteArray("no need"));
	drag->setMimeData(mimeData);
	//drag->setPixmap(m_draggedIem->icon);

	// 启动拖放start a drag
	Qt::DropAction result = drag->exec(Qt::CopyAction | Qt::MoveAction);

	// 检查操作有没有成功/有没有被取消
	if(Qt::IgnoreAction != result)
	{

	}
	else
	{
		// 按住ctrl键: Qt::CopyAction
		// 没按： Qt::MoveAction
	}
	m_mousePressed = false;
	m_allowDrop = false;
}

// 拖放事件
// 有东西被拖进来(拖着、未松开鼠标）
void GameView::dragEnterEvent(QDragEnterEvent *event)
{	
	QStringList formats = event->mimeData()->formats();
	for(int i=0; i<formats.size(); i++)
	{
		QString fmt = formats.at(i);
		qDebug() << "Format:" << fmt;
	}

	if (event->mimeData()->hasFormat("game/move"))
	{
		event->acceptProposedAction();
	}	
}
// 拖放事件: 经过目标单元格时，要检查是否可以移到这里
void GameView::dragMoveEvent (QDragMoveEvent * event )
{
	GamePosition posTo = getPostion(event->pos());

	// 检查是否可以移动到目标位置 
	if(m_gameModel.canMoveTo(m_posFrom, posTo) )
	{
		if (event->mimeData()->hasFormat("game/move"))
		{
			event->acceptProposedAction();

			// 更新显示
			m_allowDrop = true;
			m_allowDropPos = posTo;
			update();
			return;
		}	
	}

	m_allowDrop = false;
	update();
	event->ignore();
}
// 拖放事件
void GameView::dragLeaveEvent (QDragLeaveEvent * event )
{
	QFrame::dragLeaveEvent(event);
}


// 有东西被放下(松开鼠标）
void GameView::dropEvent(QDropEvent *event)
{
	if (event->mimeData()->hasFormat("game/move"))
	{
		QString text  = event->mimeData()->text();	
		
		// 移动到目标单元格，并重绘
		GamePosition posTo = getPostion(event->pos());
		m_gameModel.moveTo(m_posFrom, posTo);
		update();

		event->acceptProposedAction();
	}

}



