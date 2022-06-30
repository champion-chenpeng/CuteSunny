#include "treehole.h"
#include "ui_treehole.h"
#include "mainwindow.h"

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

treehole::treehole(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::treehole)
{
    ui->setupUi(this);
    connect(ui->emailBtn,SIGNAL(clicked()),this, SLOT(treehole_mail()));
}

treehole::~treehole()
{
    delete ui;
}

QString userToken = "";
QString urlSearch = "https://pkuhelper.pku.edu.cn/services/pkuhole/api.php?action=search&pagesize=%1&page=1&keywords=%2&PKUHelperAPI=3.0&user_token=%3";
QString urlAttention = "https://pkuhelper.pku.edu.cn/services/pkuhole/api.php?action=getattention&PKUHelperAPI=3.0&user_token=%1";
QString urlScore = "https://pkuhelper.pku.edu.cn/api_xmcp/isop/scores?user_token=%1";
QString urlComment = "https://pkuhelper.pku.edu.cn/services/pkuhole/api.php?action=getcomment&pid=%1&PKUHelperAPI=3.0&user_token=%2";

void treehole::on_pushButton_token_clicked()
{
    userToken = ui->lineEdit_token->text();
}

struct Hole {
    int pid, reply, likenum;
    QString text;
    Hole() {}
    Hole(int x, int y, int z, QString s): pid(x), reply(y), likenum(z), text(s) {}
    bool operator < (const Hole & h) const {
        return pid > h.pid;
    }
};  // 暂时用不上这个

// 搜索按钮
void treehole::on_pushButton_search_clicked()
{
    if (userToken == "") {
        ui->textBrowser->setText("请输入并确认正确的User Token！");
        return;
    }
    QString keywords = ui->lineEdit_searchWord->text();
    if (keywords == "") {
        ui->textBrowser->setText("请输入关键词！");
        return;
    }
    int pagesize = 10;
    pagesize = ui->lineEdit_searchNum->text().toInt();
    QNetworkRequest request;
    QNetworkAccessManager * m_manager = new QNetworkAccessManager(this);
    QString url = urlSearch.arg(pagesize).arg(keywords).arg(userToken);
    request.setUrl(QUrl(url));
    m_manager->get(request);   //向网页发起get请求
    connect(m_manager, SIGNAL(finished(QNetworkReply*)), this,SLOT(processSearch(QNetworkReply*)));
    //请求完成,获取数据并在槽函数中进行处理
}

void treehole::processSearch(QNetworkReply* reply) {
    if(reply->error()==QNetworkReply::NoError) {
        QByteArray resBytes = reply->readAll();
        QJsonDocument doc = QJsonDocument::fromJson(resBytes);
        QJsonObject json = doc.object();
        QJsonValue value = json.value("data");
        QJsonArray valueArray = value.toArray();

        int num = valueArray.size();
        QString output = "";
        for (int i = 0; i < num; ++i) {
            // 通过 QJsonArray::at(i)函数获取数组下的第i个元素
            QJsonValue holeArray = valueArray.at(i);
            // 通过 QJsonValue::toObject()函数将数组元素转换成Object对象
            QJsonObject hole = holeArray.toObject();
            output.append(hole["pid"].toString() + "\n" + hole["text"].toString()  + "\n\n");
        }
        ui->textBrowser->setText(output);
    }
}

void treehole::treehole_mail()
{
    MainWindow * w = new MainWindow(0,"treehole:"+ui->lineEdit_searchWord->text(),ui->textBrowser->toPlainText());
    w->show();
}

// 获取所有关注洞按钮
void treehole::on_pushButton_attention_clicked()
{
    if (userToken == "") {
        ui->textBrowser->setText("请输入并确认正确的User Token！");
        return;
    }
    QNetworkRequest request;
    QNetworkAccessManager * m_manager = new QNetworkAccessManager(this);
    QString url = urlAttention.arg(userToken);
    request.setUrl(QUrl(url));
    m_manager->get(request);   //向网页发起get请求
    connect(m_manager, SIGNAL(finished(QNetworkReply*)), this,SLOT(processAttention(QNetworkReply*)));
    //请求完成,获取数据并在槽函数中进行处理
}

void treehole::processAttention(QNetworkReply* reply) {
    if(reply->error()==QNetworkReply::NoError) {
        QByteArray resBytes = reply->readAll();
        QJsonDocument doc = QJsonDocument::fromJson(resBytes);
        QJsonObject json = doc.object();
        QJsonValue value = json.value("data");
        QJsonArray valueArray = value.toArray();

        int num = valueArray.size();
        QString output = "";
        for (int i = 0; i < num; ++i) {
            // 通过 QJsonArray::at(i)函数获取数组下的第i个元素
            QJsonValue holeArray = valueArray.at(i);
            // 通过 QJsonValue::toObject()函数将数组元素转换成Object对象
            QJsonObject hole = holeArray.toObject();
            output.append(hole["pid"].toString() + "\n" + hole["text"].toString()  + "\n\n");
        }
        ui->textBrowser->setText(output);
    }
}

// 查询GPA按钮
void treehole::on_pushButton_gpa_clicked()
{
    if (userToken == "") {
        ui->textBrowser->setText("请输入并确认正确的User Token！");
        return;
    }
    QNetworkRequest request;
    QNetworkAccessManager * m_manager = new QNetworkAccessManager(this);
    QString url = urlScore.arg(userToken);
    request.setUrl(QUrl(url));
    m_manager->get(request);   //向网页发起get请求
    connect(m_manager, SIGNAL(finished(QNetworkReply*)), this,SLOT(processGPA(QNetworkReply*)));
    //请求完成,获取数据并在槽函数中进行处理
}

void treehole::processGPA(QNetworkReply* reply) {
    if(reply->error()==QNetworkReply::NoError) {
        QByteArray resBytes = reply->readAll();
        QJsonDocument doc = QJsonDocument::fromJson(resBytes);
        QJsonObject json = doc.object();
        ui->textBrowser->setText("GPA = " + json.value("gpa").toObject()["gpa"].toString());
    }
}

// 跳转获取评论
void treehole::on_pushButton_clicked()
{
    comment *configWindow = new comment;
    configWindow->show();
}

