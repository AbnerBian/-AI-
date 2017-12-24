#include "demo001.h"
#include <QtGui/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	Demo001 w;
	w.show();
	return a.exec();
}
