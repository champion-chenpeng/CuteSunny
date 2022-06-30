#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent,QString subject,QString mailbody) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QString uname = "champrince@pku.edu.cn";
    QString paswd = "zyzxwwtq!!!516";
    QString rcpt = "champrince@pku.edu.cn";

    ui->uname->setText(uname);
    ui->paswd->setText(paswd);
    ui->rcpt->setText(rcpt);
    ui->subject->setText(subject);
    ui->msg->document()->setPlainText(mailbody);

    connect(ui->sendBtn, SIGNAL(clicked()),this, SLOT(sendMail()));
    connect(ui->exitBtn, SIGNAL(clicked()),this, SLOT(close()));
}

void MainWindow::sendMail()
{

    Smtp* smtp = new Smtp(ui->uname->text(), ui->paswd->text(), "smtp.pku.edu.cn");
    connect(smtp, SIGNAL(status(QString)), this, SLOT(mailSent(QString)));


    smtp->sendMail(ui->uname->text(), ui->rcpt->text() , ui->subject->text(),ui->msg->toPlainText());
}

void MainWindow::mailSent(QString status)
{
    if(status == "Message sent")
        QMessageBox::warning( 0, tr( "Qt Simple SMTP client" ), tr( "Message sent!\n\n" ) );
}

MainWindow::~MainWindow()
{
    delete ui;
}
