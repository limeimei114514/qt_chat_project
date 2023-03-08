#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include "tcp_serverform.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

signals:
    void sig_pressed();
private slots:
    void on_pushButton_clicked();

    void on_comboBox_currentTextChanged(const QString &arg1);

    void on_pushButton_2_clicked();

    void slot_serverStatChanged();

    void slot_serverShutdown();

    void slot_getIPaddresses(QHostInfo info);

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void slot_serverNewMessage(QString);

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
