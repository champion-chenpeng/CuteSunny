#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "smtp.h"
#include <QtWidgets/QMessageBox>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0,QString subject="Subject",QString mailbody="MailBody");
    ~MainWindow();

private slots:
    void sendMail();
    void mailSent(QString);
    
private:
    Ui::MainWindow *ui;

};

#endif // MAINWINDOW_H
