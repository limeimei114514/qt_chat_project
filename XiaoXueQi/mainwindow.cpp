#include "mainwindow.h"
#include "ui_mainwindow.h"
#include"qtcp_server.h"
#include"mytcpserver.h"
#include"mysql.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    MyTCPServer *tcp= MyTCPServer::gethand();
    connect(tcp,SIGNAL(serverStart()),this,SLOT(slot_serverStatChanged()));//将信号和槽链接起来
    connect(tcp,SIGNAL(serverShutdown()),this,SLOT(slot_serverStatChanged()));
    connect(tcp,SIGNAL(sig_getIPaddresses(QHostInfo)),this,SLOT(slot_getIPaddresses(QHostInfo)));
    connect(tcp,SIGNAL(serverNewMessage(QString)),this,SLOT(slot_serverNewMessage(QString)));
    //信号是函数 要加括号
    //一个槽可以和多个信号连接 sender
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::slot_serverShutdown(){

}
void MainWindow::slot_serverStatChanged(){
    if (ui->pushButton->text()!="Server running") ui->pushButton->setText("Server running");
    else ui->pushButton->setText("Shutdown");
}
void MainWindow::slot_getIPaddresses(QHostInfo info){
    QList<QHostAddress> addlist=info.addresses();
    if (addlist.count()>0){
        for (int i=0;i<addlist.count();i++){
            qDebug()<<addlist.at(i).toString();
        }
    }

}

void MainWindow::on_pushButton_clicked()
{
    //emit sig_pressed();//传输信号的
    QString IP = ui->comboBox->currentText();
    QString port=ui->lineEdit->text();
    qDebug()<<"prepare opening server";
    qDebug()<<"IP  = "<<IP<<"port = "<<port;
    MyTCPServer *tcp= MyTCPServer::gethand();
    if (ui->pushButton->text()!="Server running"){
        tcp->openTCPserver(IP,port);
    }
    else {
        tcp->shutdownTCPserver();
    }
   // tserver->startServer("0");
   // ui->pushButton->setText("Server has opened successfully.");
}

void MainWindow::on_comboBox_currentTextChanged(const QString &arg1)
{
    ui->listWidget->addItem(ui->comboBox->currentText());
}

void MainWindow::on_pushButton_2_clicked()
{
    emit sig_pressed();
    MyTCPServer *tcp= MyTCPServer::gethand();
    for (int i=0;i<tcp->iplist.count();i++){
        ui->comboBox->addItem(tcp->iplist.at(i));
    }
}

void MainWindow::on_pushButton_3_clicked()
{
   // MySQL *sql=MySQL::gethand();

}

void MainWindow::on_pushButton_4_clicked()
{
    MySQL::gethand()->dropTable("");
}

void MainWindow::slot_serverNewMessage(QString msg){
    ui->ybb->append(msg);
}
