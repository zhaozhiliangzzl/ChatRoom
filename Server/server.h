#ifndef SERVER_H
#define SERVER_H

#include <QWidget>
#include <QTcpServer>
#include <QTcpSocket>

namespace Ui {
class Server;
}

class Server : public QWidget
{
    Q_OBJECT

public:
    explicit Server(QWidget *parent = 0);
    ~Server();

private slots:
    void on_setListen_clicked();

private:
    Ui::Server *ui;
    QTcpServer *m_s;
    QTcpSocket *m_tcp;
};

#endif // SERVER_H
