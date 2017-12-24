#include "GameView.h"

GameView::GameView(QWidget *parent)
	: QFrame(parent)
{
	// ����Ϸ�֧��
	setAcceptDrops(true);

	reset();

}

GameView::~GameView()
{

}

// ������Ϸ
void GameView::reset()
{
	m_gameModel.reset();
	m_mousePressed = false;
	update();
}

// �����ڸı��Сʱ�����¼��㵥Ԫ���С
void GameView::caculate()
{
	int width = this->width();
	int height = this->height();

	// ����4�������λ��
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

// �����λ�û������Ԫ������
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

// ��Ԫ�����ĵ��ȵ�����
QRect GameView::hotArea(GamePosition pos)
{
	QRect rRed = m_cells[pos.x][pos.y];
	QRect rHot = QRect(0,0,33,33);
	rHot.moveCenter(rRed.center());
	return rHot;
}

// ��Ԫ������
QRect GameView::selectedArea(GamePosition pos)
{
	QRect rSelected = m_cells[pos.x][pos.y];
	return rSelected.adjusted(1,1,-1,-1);
}

// Widget�¼�
void GameView::resizeEvent ( QResizeEvent * event )
{
	caculate();
}
// Widget�¼�
void GameView::paintEvent ( QPaintEvent * event )
{
	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing, true);

	int width = this->width();
	int height = this->height();
	QRect rect(0,0, width, height);

	QPen pen;

	// ����
	painter.setPen(Qt::NoPen);
	painter.setBrush(QBrush(QColor(0xFF,0xFF, 0xFF)));
	painter.drawRect(rect);

	// 4x4����
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

	// ���ӣ�����õ�Ԫ���������ӣ��򻭳�������
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

	// �Ϸ���ʾ������ѡ��Ŀ�굥Ԫ��
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

// ����˫���¼�
void GameView::mouseDoubleClickEvent ( QMouseEvent * event )
{
	QWidget::mouseDoubleClickEvent(event);
}

// ��갴��
void GameView::mousePressEvent ( QMouseEvent * event )
{
	m_mousePressed = true;
	m_draggedIem = NULL;
	m_allowDrop = false;

	// �������
	m_dragPosition = event->pos();
	m_posFrom = getPostion(event->pos());
	QRect hot = hotArea(m_posFrom);
	if(hot.contains(event->pos()))
	{
		m_draggedIem = m_gameModel.at(m_posFrom);
	}


	QFrame::mousePressEvent(event);
}
// ����ɿ�
void GameView::mouseReleaseEvent ( QMouseEvent * event )
{
	m_mousePressed = false;
	m_allowDrop = false;
	update();
}
// ����ƶ�
void GameView::mouseMoveEvent ( QMouseEvent * event )
{
	if(!m_mousePressed) return;
	if(!m_draggedIem) return;

	// ֻ����������϶�
	if (!(event->buttons() & Qt::LeftButton))
		return;

	// �ƶ�һ������󣬲����ǿ�ʼ�϶�
	if ((event->pos() - m_dragPosition).manhattanLength()
		< QApplication::startDragDistance())
		return;

	// �ҵ��϶�����
	QString text = "what";

	// ��������
	QDrag *drag = new QDrag(this);

	QMimeData *mimeData = new QMimeData;
	mimeData->setData("game/move", QByteArray("no need"));
	drag->setMimeData(mimeData);
	//drag->setPixmap(m_draggedIem->icon);

	// �����Ϸ�start a drag
	Qt::DropAction result = drag->exec(Qt::CopyAction | Qt::MoveAction);

	// ��������û�гɹ�/��û�б�ȡ��
	if(Qt::IgnoreAction != result)
	{

	}
	else
	{
		// ��סctrl��: Qt::CopyAction
		// û���� Qt::MoveAction
	}
	m_mousePressed = false;
	m_allowDrop = false;
}

// �Ϸ��¼�
// �ж������Ͻ���(���š�δ�ɿ���꣩
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
// �Ϸ��¼�: ����Ŀ�굥Ԫ��ʱ��Ҫ����Ƿ�����Ƶ�����
void GameView::dragMoveEvent (QDragMoveEvent * event )
{
	GamePosition posTo = getPostion(event->pos());

	// ����Ƿ�����ƶ���Ŀ��λ�� 
	if(m_gameModel.canMoveTo(m_posFrom, posTo) )
	{
		if (event->mimeData()->hasFormat("game/move"))
		{
			event->acceptProposedAction();

			// ������ʾ
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
// �Ϸ��¼�
void GameView::dragLeaveEvent (QDragLeaveEvent * event )
{
	QFrame::dragLeaveEvent(event);
}


// �ж���������(�ɿ���꣩
void GameView::dropEvent(QDropEvent *event)
{
	if (event->mimeData()->hasFormat("game/move"))
	{
		QString text  = event->mimeData()->text();	
		
		// �ƶ���Ŀ�굥Ԫ�񣬲��ػ�
		GamePosition posTo = getPostion(event->pos());
		m_gameModel.moveTo(m_posFrom, posTo);
		update();

		event->acceptProposedAction();
	}

}



