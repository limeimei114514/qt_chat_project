/*
#include "tcp_serverform.h"
#include "ui_tcp_serverform.h"
#include "qtcp_server.h"


TCP_serverForm::TCP_serverForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWindow.ui)
{
    ui->setupUi(this);
    tserver = QTCP_server::gethand();

}

TCP_serverForm::~TCP_serverForm()
{
    delete ui;
    tserver->stopServer();
}

void TCP_serverForm::on_pushButton_clicked()
{
    qDebug()<<"open TCP server";
    ui->listWidget->addItem("11111111111111");
    ui->listWidget->addItem("AAAAAAAAAAAAAA");
    ui->listWidget->addItem("QQQQQQQQQQQQQQ");
    ui->listWidget->addItem("555555555555");

    tserver->startServer("0");


}

void TCP_serverForm::on_listWidget_itemDoubleClicked(QListWidgetItem *item)
{
    qDebug()<<item->text();
}

void TCP_serverForm::on_pushButton_2_clicked()
{
    if(tserver->iplist.count() > 0)
    {
        for (int i = 0; i < tserver->iplist.count(); ++i) {
            qDebug()<<tserver->iplist.at(i);
            ui->comboBox->addItem(tserver->iplist.at(i));
        }
    }

//    if(tserver->iplist.count() > 0){
//        ui->comboBox->addItems(tserver->iplist);
//    }
}
*/
