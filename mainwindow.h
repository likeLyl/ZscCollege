#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#ifndef __TFTPC_H__
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <netdb.h>
#include <sys/ioctl.h>
#include <assert.h>

#define OPCODE_RRQ (1)
#define OPCODE_WRQ (2)
#define OPCODE_DATA (3)
#define OPCODE_ACK (4)
#define OPCODE_ERR (5)

#define BLOCKSIZE (512)

struct TFTPHeader{
        short opcode;
}__attribute__((packed));

struct TFTPWRRQ{
        struct TFTPHeader header;
        char *filename;	// Terminal as \0x00
        char *mode;	// Terminal as \0x00
}__attribute__((packed));

struct TFTPData{
        struct TFTPHeader header;
        short block;
        char data[];
}__attribute__((packed));

struct TFTPACK{
        struct TFTPHeader header;
        short block;
}__attribute__((packed));

struct TFTPERR{
        struct TFTPHeader header;
        short errcode;
        char *errmsg;	// Terminal as \0x00
}__attribute__((packed));
#endif

#include <QMainWindow>
#include <QUdpSocket>
#include <QFile>

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
    QUdpSocket *udpSocket;
    char RecvData[1024];
    QFile *pFile;
    int sendDataAck(QHostAddress &haddr, quint16 port,struct TFTPData *pData);
    void sendReadReq(QHostAddress &haddr, quint16 port,char *pFilename);


protected:
    void changeEvent(QEvent *e);

private:
    Ui::MainWindow *ui;
private slots:
    void on_pushButton_clicked();
    void readPendingDatagrams();

};

#endif // MAINWINDOW_H
