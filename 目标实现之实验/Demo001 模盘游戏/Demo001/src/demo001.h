#ifndef DEMO001_H
#define DEMO001_H

#include <QtGui/QWidget>
#include "ui_demo001.h"

class Demo001 : public QWidget
{
	Q_OBJECT

public:
	Demo001(QWidget *parent = 0, Qt::WFlags flags = 0);
	~Demo001();

private:
	Ui::Demo001Class ui;
};

#endif // DEMO001_H
