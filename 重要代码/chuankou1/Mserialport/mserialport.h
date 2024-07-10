#ifndef MSERIALPORT_H
#define MSERIALPORT_H

#include <QWidget>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QTime>
#include <QTimer>

#include <QDateTime>      //日期时间
#include <QLabel>         //标签
#include <QPainter>  //画家类
#include <QPaintEvent>   //
//#include <QImage>
#include <QIcon>
#include <QMovie>   //动画GIF

#include <QFont>

QT_BEGIN_NAMESPACE
namespace Ui { class Mserialport; }
QT_END_NAMESPACE

class Mserialport : public QWidget
{
    Q_OBJECT

public:
    Mserialport(QWidget *parent = nullptr);
    ~Mserialport();

private slots:
    void on_btnopen_clicked();

    void on_btnrefresh_clicked();

    void messlot();

    void sleep(int msec);

    void on_btnclose_clicked();

    void delay();

    void timerSLot();

private:
    Ui::Mserialport *ui;
    QSerialPort m_serial;
    QTimer  *timer;            //定时器*/
    QFont font;
};
#endif // MSERIALPORT_H
