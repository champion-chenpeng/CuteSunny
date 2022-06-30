#ifndef MAIL_H
#define MAIL_H

#include <QWidget>
#include "smtp.h"
#include <QtWidgets/QMessageBox>

namespace Ui {
class MainWindow;
}

class MainWindow : public QWidget
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void sendMail();
    void mailSent(QString);
    
private:
    Ui::MainWindow *ui;

};

#endif // MAIL_H
