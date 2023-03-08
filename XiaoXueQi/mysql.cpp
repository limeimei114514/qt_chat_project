#include "mysql.h"
MySQL*MySQL::sqlhand=nullptr;

MySQL::MySQL(QObject *parent) : QObject(parent)
{

}
void MySQL::openDatabase(){
    if (QSqlDatabase::contains("qt_sql_default_connection"))
        database=QSqlDatabase::database("qt_sql_default_connection");
    else{
        database=QSqlDatabase::addDatabase("QSQLITE");
        database.setHostName("Admin");
        database.setDatabaseName("YMFdatabase");//数据库文件的名字
        database.setUserName("Guest");
        database.setPassword("810975");
    }
    if (database.open()){
        QStringList tablelist=database.tables();
        if(!tablelist.contains("userstable")){
            QString createusers= "CREATE TABLE userstable (name text, password text, ID text)";
            sqlquery=new QSqlQuery(database);
            if (sqlquery->prepare(createusers)){
                if(sqlquery->exec()){
                    qDebug()<<"Create usertable successfully";
                }
            }
            else{
                qDebug()<<"create table command error !";
            }
        }
        else{
            qDebug()<<"userstable already exist!";
        }
    }
    else {
        qDebug()<<"database open failed !";
    }
}
void MySQL::createTable(){

}
void MySQL::regist_InsertData(QString yonghuming,QString userpassword,QTcpSocket* tcp_socket )
{
    QString insert="INSERT INTO userstable(yonghuming,userpassword) VALUES("+yonghuming+",'"+userpassword+"')";
   sqlquery=new QSqlQuery(database);
     if(sqlquery->prepare(insert))
     {
         if(sqlquery->exec())
         {
             qDebug()<<"Insert successfully!";
              tcp_socket->write("&");//注册成功
         }
         else{
             qDebug()<<"?";
             tcp_socket->write("*");//用户已存在
         }
     }
     else
     {
         qDebug()<<"insert error occured";
     }

}
void MySQL::login_SelectData(QString yonghuming,QString userpassword,QTcpSocket* tcp_socket)
{

        QString truePWD;    // 数据库中的密码
        // 从数据库中获取密码
       sqlquery=new QSqlQuery(database);
        sqlquery->prepare("select password from userstable where yonghuming="+yonghuming);



        if(sqlquery->exec())
       { if(sqlquery->next())
        {truePWD = sqlquery->value(1).toString();






          if(userpassword != NULL && truePWD == userpassword)
        {    qDebug() << "登录";
           tcp_socket->write("#");//登录成功

         }
         else
            { tcp_socket->write("@");//密码错误

           }

        }
        else
        {
            tcp_socket->write("%");//无用户
        }
        }

}
void MySQL::dropTable(QString tableName)
{
    tableName="userstable";
    QString str_drop="DROP TABLE "+tableName;
    if(sqlquery->prepare(str_drop)){
                if(sqlquery->exec()){
                    qDebug()<<"Drop sucessfully";
                }
                else{
                    qDebug()<<"D?";
                }
            }
            else{
                qDebug()<<"drop error occured";
            }
}
QString  MySQL::selectData(QString x, QString y){
    //需要补全
    QString select=QString("SELECT * FROM userstable WHERE ID ='%1' AND password ='%2'").arg(x).arg(y);
   QSqlQuery sqlquery;
       if(sqlquery.exec(select))
       {   sqlquery.next();
           name=sqlquery.value(0).toString();
           return name;
           // QMessageBox::information(NULL, "登录成功", "登录成功！！！", QMessageBox::Yes);
       }
}



QString MySQL::seekData()
{     sqlquery=new QSqlQuery(database);
      QString str_select="SELECT * FROM userstable";

          if(sqlquery->exec(str_select))
          {
              if(sqlquery->next())
              {
                  QString ko=sqlquery->value(2).toString();
                  while(sqlquery->next()) ko=sqlquery->value(2).toString();
                  return ko;
              }else return "0";
          }

}
void MySQL::insertData(QString x,QString y,QString z){
    QString  insert=QString("INSERT INTO userstable VALUES('%1','%2','%3')").arg(x).arg(y).arg(z);

    //sqlquery=new QSqlQuery(database);
     QSqlQuery okk;
        if(okk.exec(insert)){
              qDebug()<<"insert userstable OK";
        }

    else{
        qDebug()<<"insert table command error!";
    }
}

