#ifndef CLIENT_H
#define CLIENT_H

#include <QWidget>

#include <QTcpSocket>

namespace Ui {
class Client;
}

class Client : public QWidget
{
    Q_OBJECT

public:
    explicit Client(QWidget *parent = 0);
    ~Client();

private slots:
    void on_connect_clicked();

    void on_sendMsg_clicked();

private:
    Ui::Client *ui;
    QTcpSocket *m_tcp;
};

#endif // CLIENT_H
