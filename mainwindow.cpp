#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->resize(800, 600);
    this->setWindowTitle("煤矿安全巡检系统");

    //枚举出当前的可用端口号
    int count = 0;
    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts()) {
        ui->SerialPort->addItem(info.portName());
        //m_serialPort->setp
        count++;
    }
    if (count == 0) {
        QMessageBox::about(this, "waring", "no availabe serial port");
        //exit(0);
    }
    // 初始化波特率的可选择值
    QStringList baundrates;
    baundrates<<"4800"<<"9600"<<"115200";
    ui->baundRateChoose->addItems(baundrates);
    ui->baundRateChoose->setCurrentText("9600");
    // 初始化数据位
    QStringList datas;
    datas<<"5"<<"6"<<"7"<<"8";
    ui->DataBits->addItems(datas);
    ui->DataBits->setCurrentText("8");

    m_serialPort = new QSerialPort(this); // 实例化串口对象
    connect(m_serialPort, QSerialPort::readyRead, this, &readSerialData);

}

MainWindow::~MainWindow()
{
    if (m_serialPort != nullptr) {
        delete m_serialPort;
    }
    delete ui;
}
/*
 *用于初始化串口
*/
void MainWindow::on_OpenSerialPort_clicked()
{
    if (ui->OpenSerialPort->text() == "打开串口") {
#if 1
    //初始化串口对象
    m_serialPort->setPortName(ui->SerialPort->currentText());
    //m_serialPort->setBaudRate(QSerialPort::Baud9600);
    m_serialPort->setBaudRate(ui->baundRateChoose->currentText().toInt());
    QSerialPort::DataBits data;
    switch(ui->DataBits->currentText().toInt()) {
        case 8:
            data = QSerialPort::Data8;
        break;
        case 7:
            data = QSerialPort::Data7;
        break;
        case 6:
            data = QSerialPort::Data6;
        break;
        case 5:
            data = QSerialPort::Data5;
        break;
    }
    m_serialPort->setDataBits(data);

    m_serialPort->setStopBits(QSerialPort::OneStop);
    m_serialPort->setParity(QSerialPort::NoParity);
    m_serialPort->setFlowControl(QSerialPort::NoFlowControl);

    // 打开串口对象
    if(!m_serialPort->open(QIODevice::ReadWrite)) {
        QMessageBox::about(this, "warning", "open serial failed");
        return;
    }
    qDebug() << "open serial succesfull" << endl;
#endif
        ui->OpenSerialPort->setText("关闭串口");
    } else {
       m_serialPort->flush(); // 在串口关闭之前将缓冲区的数据刷新到串口
       m_serialPort->close();
       ui->OpenSerialPort->setText("打开串口");
    }

}

void MainWindow::on_radioButton_clicked(bool checked)
{
    if (checked) {
        m_serialPort->write("led on");
        qDebug() << "led on red" << endl;
    } else {
        m_serialPort->write("led off");
        qDebug() << "led off red" << endl;
    }
}
/*
 * 函数功能：读取串口数据
*/
void MainWindow::readSerialData()
{
    char buf[128];
    qint64 len = 0;
    memset(buf, 0, sizeof(buf));
    len = m_serialPort->read(buf, sizeof(buf) - 1);

    ui->ShowSerialPortData->append(buf);
    qDebug() << "len:" << len << ", raw data:" << buf << endl;


}

void MainWindow::on_radioButton_2_clicked(bool checked)
{
    if (checked) {
        m_serialPort->write("led on green\r");
        qDebug() << "led on green" << endl;
    } else {
        m_serialPort->write("led off green\r");
        qDebug() << "led off green" << endl;
    }
}

void MainWindow::on_radioButton_3_clicked(bool checked)
{
    if (checked) {
        m_serialPort->write("led on blue\r");
        qDebug() << "led on blue" << endl;
    } else {
        m_serialPort->write("led off blue\r");
        qDebug() << "led off blue" << endl;
    }
}

void MainWindow::on_radioButton_4_clicked(bool checked)
{
    if (checked) {
        m_serialPort->write("buzzer on\r");
        qDebug() << "buzzer on" << endl;
    } else {
        m_serialPort->write("buzzer off\r");
        qDebug() << "buzzer off" << endl;
    }
}

void MainWindow::on_checkBox_clicked(bool checked)
{
    if (checked) {
        m_serialPort->write("led on red\r");
        qDebug() << "led on red" << endl;
    } else {
        m_serialPort->write("led off red\r");
        qDebug() << "led off red" << endl;
    }
}

void MainWindow::on_checkBox_2_clicked(bool checked)
{
    if (checked) {
        m_serialPort->write("led on green\r\n");
        qDebug() << "led on green" << endl;
    } else {
        m_serialPort->write("led off green\r\n");
        qDebug() << "led off green" << endl;
    }
}

void MainWindow::on_checkBox_3_clicked(bool checked)
{
    if (checked) {
        m_serialPort->write("led on blue\n");
        qDebug() << "led on blue" << endl;
    } else {
        m_serialPort->write("led off blue\n");
        qDebug() << "led off blue" << endl;
    }
}

void MainWindow::on_checkBox_4_clicked(bool checked)
{
    if (checked) {
        m_serialPort->write("buzzer on\r");
        qDebug() << "buzzer on" << endl;
    } else {
        m_serialPort->write("buzzer off\r");
        qDebug() << "buzzer off" << endl;
    }
}
