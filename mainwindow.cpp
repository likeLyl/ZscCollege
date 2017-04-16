#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <errno.h>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    udpSocket = new QUdpSocket(this);
    udpSocket->bind(QHostAddress::Any,7755);
    connect(udpSocket,SIGNAL(readyRead()),
            this,SLOT(readPendingDatagrams()));

    //udpSocket->connectToHost("localhost",6969);
   //udpSocket->connectToHost(host,port);
   //connect(udpSocket,SIGNAL(readyRead()),
   //        this,SLOT(readPendingDatagrams()));
    memset(RecvData, 0,sizeof(RecvData));
    ui->textBrowser->append("welcome!!!");
    ui->textBrowser->append("welcome!!!");
    ui->line_FILENAME->setText("123");
    ui->line_IP->setText("localhost");
    ui->line_PORT->setText("6969");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::changeEvent(QEvent *e)
{
    QMainWindow::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}
void MainWindow::sendReadReq(QHostAddress &haddr, quint16 port,char *pFilename)
{
    struct TFTPHeader header;
    header.opcode = htons(OPCODE_RRQ);
    int filenamelen = strlen(pFilename)+1;
    char *mode = "octet";
    int packetsize = sizeof(header)+filenamelen+sizeof(mode)+1;
    void *packet = NULL;
    packet = malloc(packetsize);
    memcpy((char *)packet,&header,sizeof(header));
    memcpy((char *)packet+sizeof(header),pFilename,filenamelen);
    memcpy((char *)packet+sizeof(header)+filenamelen,mode,strlen(mode)+1);

    //int bytes = udpSocket->write((char *)packet,packetsize);
    int bytes = udpSocket->writeDatagram((char *)packet,packetsize,haddr,port);

    qDebug("%d bytes has been sent",bytes);
    ui->textBrowser->append("bytes has been sent ");
    ui->textBrowser->textCursor().insertText(QString::number(bytes));

    pFile = new QFile(pFilename);
    if(!pFile->open(QIODevice::ReadWrite))
        return ;
    qDebug()<<"file info"<<pFile->fileName();
    ui->textBrowser->append("file info ");
    ui->textBrowser->textCursor().insertText(pFilename);
}

int MainWindow::sendDataAck(QHostAddress &haddr, quint16 port,struct TFTPData *pData)
{
    struct TFTPACK ack;
    ack.header.opcode = htons(OPCODE_ACK);
    ack.block = pData -> block;

    void* packet = NULL;
    packet = malloc(sizeof(ack));
    memcpy((char *)packet,&ack,sizeof(ack));

   //int bytes = udpSocket->write((char *)packet,sizeof(ack));
   int bytes = udpSocket->writeDatagram((char *)packet,sizeof(ack),haddr,port);
   ui->textBrowser->append("sendDataAck has been sent ");
   ui->textBrowser->textCursor().insertText(QString::number(bytes));

   qDebug("  *****   in the sendDataAck   ********");
   ui->textBrowser->append("  *****   in the sendDataAck   *******  ");
   ui->textBrowser->append((char *)packet);

   return 0;
}

void MainWindow::readPendingDatagrams()
{
     ui->textBrowser->append("it is readPendingDatagrams,bytes:");
     ui->textBrowser->textCursor().insertText(QString::number(udpSocket->size()));
     qDebug("it is readPendingDatagrams,bytes %d",udpSocket->size());

     while(udpSocket->hasPendingDatagrams())
     {
         QHostAddress sender;
         quint16 senderPort;

        // memset(RecvData, 0,sizeof(RecvData));
         int readbytes = udpSocket->readDatagram(RecvData,sizeof(RecvData),
                                   &sender,&senderPort);
         qDebug("port %d ip %s",senderPort,sender.toString().toUtf8().data());
         ui->textBrowser->append("port ");
         ui->textBrowser->textCursor().insertText(QString::number(senderPort));
         ui->textBrowser->textCursor().insertText("    ip");
         ui->textBrowser->textCursor().insertText(sender.toString().toUtf8().data());

         struct TFTPHeader *header = (struct TFTPHeader *)RecvData;
         switch(ntohs(header->opcode))
         {
         case OPCODE_DATA:
             {
                qDebug("it is Data");
                ui->textBrowser->append("it is Data ");

                struct TFTPData *data = (struct TFTPData *)RecvData;
                pFile->write(data->data,readbytes - sizeof(struct TFTPHeader)-sizeof(short));

                sendDataAck(sender,senderPort,data);

                if(readbytes < 512)
                 {
                    ui->textBrowser->append("File Transfer Completed!");
                    qDebug("File Transfer Completed!");
                    pFile->close();
                 }
               }

            break;
        default:
            qDebug("No match %d",header->opcode);
            ui->textBrowser->append("No match %d");
            ui->textBrowser->textCursor().insertText(QString::number(header->opcode));
         }

     }
 }

void MainWindow::on_pushButton_clicked()
{

    ui->textBrowser->clear();
    char *pfilename = NULL;
    char host_buff[20];
    char filename_buff[40];
    char *host = NULL;
    char mode[20];

    int port=0;
    int opt= 1;

    strcpy(filename_buff,ui->line_FILENAME->text().toLatin1());
    strcpy(host_buff,ui->line_IP->text().toLatin1());
    strcpy(mode,ui->line_GET->text().toLatin1());

    pfilename = filename_buff;
    host = host_buff;
    port = atoi(ui->line_PORT->text().toLatin1());






    qDebug("DBG: host = %s , tftpport = %d , tftpopt = %d , file = %s\n",
                    host, port , opt , pfilename);

    assert(1 == opt);

    QHostAddress haddr;
    haddr.setAddress("localhost");

    ui->textBrowser->append("File Start Get !");
    sendReadReq(haddr,port,pfilename);
    readPendingDatagrams();


    /*
    struct sockaddr_in remoteaddr;
    remoteaddr.sin_family = PF_INET;

    struct hostent *remotehost =NULL;

    if((remotehost = gethostbyname(host)) == NULL){
            perror("gethostbyname()");
            exit(1);
    }

    remoteaddr.sin_addr = *((struct in_addr *)remotehost->h_addr_list[0]);
    remoteaddr.sin_port = htons(port);

    struct protoent *proto;
    if((proto = getprotobyname("udp")) == NULL){
            fprintf(stderr, "gethostbyname():failed to find udp protocol info\n");
            exit(1);
    }

    if((sockfd = socket(PF_INET, SOCK_DGRAM , proto->p_proto)) < 0){
            perror("socket()");
            exit(1);
    }

    sendReadReq(pfilename);

    FILE *fp = fopen(pfilename,"wb");
    if(fp == NULL){
            perror("fopen()");
            exit(1);

    }

    struct sockaddr_in peeraddr;
    memset(&peeraddr, 0 ,sizeof(peeraddr));

    while(1)
    {
            int bufferlen = 0;

            while(bufferlen == 0)
            {
                    ioctl(sockfd,FIONREAD, &bufferlen);
            }
            char shuchu[500];
            sprintf(shuchu,"DBG: bufferlen = %d\n", bufferlen);


            QString string = static_cast<QString>(shuchu);
            len<<QString(string);
            QStringListModel *mode =new QStringListModel(len);
            ui->listView->setModel(mode);


            void *buffer = NULL;
            buffer = malloc(bufferlen);
            //printf("sockfd = %d ", sockfd);
            int recvLen = sizeof(peeraddr);
            int recvlen = recvfrom(sockfd,buffer,bufferlen,0,(struct sockaddr *)&peeraddr, (socklen_t*)&recvLen);
            if(recvlen < 0)
            {
                    perror("recvfrom()");
                    exit(1);
            }

            struct TFTPHeader *header = (struct TFTPHeader*)buffer;
            if(ntohs(header->opcode) == OPCODE_ERR)
            {
                    struct TFTPERR *err = (struct TFTPERR*)buffer;
                    printf("Error packer dected with code %d\n", ntohs(err->errcode));
                    exit(1);
            }
            if(ntohs(header->opcode) == OPCODE_DATA)
            {
                    struct TFTPData *data = (struct TFTPData*)buffer;
                    printf("Receiving block %d\n", ntohs(data->block));
                    fwrite(&data->data,recvlen - sizeof(struct TFTPHeader) - sizeof(short) , 1 , fp);
                    sendDataAck(data);

            }

            if(recvlen < BLOCKSIZE + sizeof(struct TFTPHeader) - sizeof(short))
            {
                    fclose(fp);
                    exit(1);

            }
            free(buffer);
    }
*/
}

























