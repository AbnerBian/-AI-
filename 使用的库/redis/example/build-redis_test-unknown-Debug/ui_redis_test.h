/********************************************************************************
** Form generated from reading UI file 'redis_test.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_REDIS_TEST_H
#define UI_REDIS_TEST_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_redis_test
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *redis_test)
    {
        if (redis_test->objectName().isEmpty())
            redis_test->setObjectName(QStringLiteral("redis_test"));
        redis_test->resize(400, 300);
        menuBar = new QMenuBar(redis_test);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        redis_test->setMenuBar(menuBar);
        mainToolBar = new QToolBar(redis_test);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        redis_test->addToolBar(mainToolBar);
        centralWidget = new QWidget(redis_test);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        redis_test->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(redis_test);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        redis_test->setStatusBar(statusBar);

        retranslateUi(redis_test);

        QMetaObject::connectSlotsByName(redis_test);
    } // setupUi

    void retranslateUi(QMainWindow *redis_test)
    {
        redis_test->setWindowTitle(QApplication::translate("redis_test", "redis_test", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class redis_test: public Ui_redis_test {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_REDIS_TEST_H
