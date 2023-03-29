#include "client.h"
#include "ui_client.h"

#include <QHostAddress>

Client::Client(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Client)
{
    ui->setupUi(this);

    ui->userName->setText("Liang");
    ui->ipAddress->setText("127.0.0.1");
    ui->port->setText("8989");
    setWindowTitle("客户端");

    m_tcp = new QTcpSocket(this);

    // 数据到达发出信号
    connect(m_tcp, &QTcpSocket::readyRead, this, [=](){
        QByteArray msg = m_tcp->readAll();
        ui->record->append(msg);
    });

    connect(m_tcp, &QTcpSocket::connected, this, [=](){
        ui->record->append("已经成功连接到服务器.....");
    });

    // 接收到断开连接信号
    connect(m_tcp, &QTcpSocket::disconnected, this, [=](){
        m_tcp->close();
        ui->record->append("服务器已经和客户端断开.....");
    });
}

Client::~Client()
{
    delete ui;
}

void Client::on_connect_clicked()
{
    // 连接主机
    QString ip = ui->ipAddress->text();
    unsigned int port = ui->port->text().toUInt();
    m_tcp->connectToHost(QHostAddress(ip), port);
}

void Client::on_sendMsg_clicked()
{
    // 将信息写入套接字中
    QString msg = ui->userName->text() + ":" + ui->msg->toPlainText();
    m_tcp->write(msg.toUtf8());
    ui->record->append(msg);
}
