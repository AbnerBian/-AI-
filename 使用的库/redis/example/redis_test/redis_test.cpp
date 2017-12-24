#include "redis_test.h"
#include "ui_redis_test.h"
#include<QDebug>
redis_test::redis_test(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::redis_test)
{
    ui->setupUi(this);

    QString path=QApplication::applicationDirPath()+"/redis.ini";
    Redis4Qt *redis=new Redis4Qt;
    redis->setRedisCof(path);
    qDebug()<<redis->string_set("k","2");
    qDebug()<<redis->string_get("k");
    qDebug()<<redis->key_del("k");
    qDebug()<<redis->string_get("k");
}

redis_test::~redis_test()
{
    delete ui;
}
