#include "mywidget.h"
#include "ui_mywidget.h"
#include <QErrorMessage>
#include <QDesktopServices>
#include <QUrl>


MyWidget::MyWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MyWidget)
{
    ui->setupUi(this);

    QFont ft;
    ft.setPointSize(15);
    ui->label->setFont(ft);
    ui->label->setText("Welcome to UKP Helper!");

    errordlg = new QErrorMessage(this);
}


MyWidget::~MyWidget()
{
    delete ui;
}


void MyWidget::on_pushButton_treehole_clicked()
{
    treehole *configWindow = new treehole;
    configWindow->show();
}


void MyWidget::on_pushButton_bbs_clicked()
{
    bbs *configWindow = new bbs;
    configWindow->show();
}


void MyWidget::on_pushButton_campus_clicked()
{
    campus *configWindow = new campus;
    configWindow->show();
}


void MyWidget::on_pushButton_portal_clicked()
{
    QDesktopServices::openUrl(QUrl(QLatin1String("https://portal.pku.edu.cn")));
}


void MyWidget::on_pushButton_course_clicked()
{
    QDesktopServices::openUrl(QUrl(QLatin1String("https://course.pku.edu.cn")));
}

