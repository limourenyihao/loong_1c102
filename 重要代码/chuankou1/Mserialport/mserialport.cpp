#include "mserialport.h"
#include "ui_mserialport.h"

Mserialport::Mserialport(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Mserialport)
{
    ui->setupUi(this);
    ui->le->clear();//清空提示信息
    on_btnrefresh_clicked();//刷新串口
    font = QFont("Arial",11);
    ui->ptereceive->setFont(font);
    //名称和图标
    this->setWindowTitle("智慧饮水机系统");
    //设置时间新
    timer = new QTimer();
    connect(timer,&QTimer::timeout,this,&Mserialport::timerSLot);
    timer->start(1000);
    ui->labelTimer->setStyleSheet("background:transparent;");//背景透明
    //设置字体
    ui->labelTimer->setStyleSheet("color:black");
}

Mserialport::~Mserialport()
{
    delete ui;
}

//打开串口读取数据
void Mserialport::on_btnopen_clicked()
{
    m_serial.setPortName(ui->cmbportname->currentText());
    m_serial.setBaudRate(ui->cmbportbaud->currentText().toInt());

    m_serial.open(QIODevice::ReadWrite);

    if(m_serial.isOpen())
    {
       // ui->le->setText("串口打开成功");
        connect(&m_serial,&QSerialPort::readyRead,this,&Mserialport::messlot);
    }else{
       //  ui->le->setText("串口打开失败！！！");
    }
}

void Mserialport::on_btnrefresh_clicked()
{
    //清除信息
    ui->ptereceive->clear();
    //清空串口名
    ui->cmbportname->clear();
    //遍历串口信息
    foreach(const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
    {
        ui->cmbportname->addItem(info.portName());
    }
}

//串口接受信息
void Mserialport::messlot()
{

    QByteArray array = m_serial.readAll();
    //ui->ptereceive->insertPlainText(array);
    ui->ptereceive->insertPlainText(array);
    sleep(1000);
    ui->ptereceive->clear();
}
void Mserialport::delay()
{
    int i,j;
    for (i=0;i<27700;i++)
    {
        for(j=0;j<11000;j++){

        }
    }
}
void Mserialport::sleep(int msec)
{
    //非阻塞方式延时,不会卡住主界面
    if (msec <= 0) {
        return;
    }

//#if (QT_VERSION >= QT_VERSION_CHECK(5,0,0))
//    QThread::msleep(msec);
//#else
    QTime endTime = QTime::currentTime().addMSecs(msec);
    while (QTime::currentTime() < endTime) {
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
    }
//#endif
}
void Mserialport::on_btnclose_clicked()
{
    m_serial.close();

    if(m_serial.isOpen())
    {
       // ui->le->setText("串口关闭失败");
    }else{
        // ui->le->setText("串口已关闭");
    }
}
void Mserialport::timerSLot()
{
    QDateTime time = QDateTime::currentDateTime();
    QString str = time.toString("yyyy-MM-dd hh:mm:ss dddd");
    ui->labelTimer->setText(str);
}
