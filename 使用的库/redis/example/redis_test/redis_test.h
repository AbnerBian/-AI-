#ifndef REDIS_TEST_H
#define REDIS_TEST_H

#include <QMainWindow>
#include "redis4qt.h"
namespace Ui {
class redis_test;
}

class redis_test : public QMainWindow
{
    Q_OBJECT

public:
    explicit redis_test(QWidget *parent = 0);
    ~redis_test();

private:
    Ui::redis_test *ui;
};

#endif // REDIS_TEST_H
