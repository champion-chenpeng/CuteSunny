#include "mywidget.h"
#include "ui_mywidget.h"
#include <QPixmap>
#include <QDebug>
#include <QColorDialog>
#include <QFileDialog>
#include <QFontDialog>
#include <QInputDialog>
#include <QMessageBox>
#include <QProgressDialog>
#include <QErrorMessage>
#include <sstream>

#include <QByteArray>
#include <QDesktopServices>
#include <QUrl>
#include <QCoreApplication>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrlQuery>

#include <QJsonValue>
#include <QJsonDocument>
#include <QJsonObject>
#include <QVariantMap>
#include <QJsonArray>

MyWidget::MyWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MyWidget)
{
    ui->setupUi(this);

    ui->label->setText("Welcome!");
    // ui->label->setPixmap(QPixmap("./logo.png"));

    errordlg = new QErrorMessage(this);
}

MyWidget::~MyWidget()
{
    delete ui;
}

void MyWidget::on_pushButton_portal_clicked()
{
    QDesktopServices::openUrl(QUrl(QLatin1String("https://portal.pku.edu.cn")));
}

void MyWidget::on_pushButton_course_clicked()
{
    QDesktopServices::openUrl(QUrl(QLatin1String("https://course.pku.edu.cn")));
}

void MyWidget::on_pushButton_9_clicked()
{
    treehole *configWindow = new treehole;
    configWindow->show();
}


void MyWidget::on_pushButton_10_clicked()
{
    bbs *configWindow = new bbs;
    configWindow->show();
}


void MyWidget::on_pushButton_11_clicked()
{
    campus *configWindow = new campus;
    configWindow->show();
}

