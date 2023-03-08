#ifndef TCP_SERVERFORM_H
#define TCP_SERVERFORM_H

#include <QWidget>
#include <QListWidgetItem>
#include "qtcp_server.h"

namespace Ui {
class TCP_serverForm;
}

class TCP_serverForm : public QWidget
{
    Q_OBJECT

public:
    explicit TCP_serverForm(QWidget *parent = nullptr);
    ~TCP_serverForm();

private slots:
    void on_pushButton_clicked();
    void on_listWidget_itemDoubleClicked(QListWidgetItem *item);

    void on_pushButton_2_clicked();

private:
    Ui::TCP_serverForm *ui;
    QTCP_server* tserver;
};

#endif // TCP_SERVERFORM_H
