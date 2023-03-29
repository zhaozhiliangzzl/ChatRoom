#include "server.h"
#include "ui_server.h"

Server::Server(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Server)
{
    ui->setupUi(this);

    ui->port->setText("8989");
    setWindowTitle("服务器");

    // 创建服务器对象
    m_s = new QTcpServer(this);

    // 新连接到达发出信号，创建用于通信的QTcpSocket套接字对象
    connect(m_s, &QTcpServer::newConnection, this, [=](){
        m_tcp = m_s->nextPendingConnection();

        // 数据到达发出信号
        connect(m_tcp, &QTcpSocket::readyRead, this, [=](){
            QByteArray msg = m_tcp->readAll();
            ui->record->append(msg);
        });
    });



    // 接收到断开连接信号
    connect(m_tcp, &QTcpSocket::disconnected, this, [=](){
        m_tcp->close();
    });
}

Server::~Server()
{
    delete ui;
}

void Server::on_setListen_clicked()
{
    // 给套接字设置监听
    unsigned int port = ui->port->text().toUInt();
    m_s->listen(QHostAddress::Any, port);
    ui->setListen->setEnabled(false);
}
