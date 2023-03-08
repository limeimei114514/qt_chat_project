#ifndef MYSQL_H
#define MYSQL_H
#include <QTcpSocket>
#include <QObject>
#include<QtSql/QSqlDatabase>
#include<QtSql/QSqlError>
#include <QDebug>
#include<QtSql/QSqlQuery>
#include<QMessageBox>
class MySQL : public QObject
{
    Q_OBJECT
public:
    static MySQL*gethand(){
        if (sqlhand==nullptr) sqlhand=new MySQL();
        return sqlhand;
    }
    void openDatabase();
    void createTable();
    void regist_InsertData(QString yonghuming,QString userpassword,QTcpSocket* tcp_socket );
    void login_SelectData(QString yonghuming,QString userpassword,QTcpSocket* tcp_socket);
    void dropTable(QString tableName);
    QString selectData(QString x,QString y);
    void insertData(QString x,QString y,QString z);
    QString seekData();
    QString name;



private:
    explicit MySQL(QObject *parent = nullptr);
    static MySQL*sqlhand;
    QSqlDatabase database;
    QSqlQuery *sqlquery;

private slots:

signals:

};

#endif // MYSQL_H
