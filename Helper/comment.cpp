#include "comment.h"
#include "treehole.cpp"
#include "ui_comment.h"
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

#include <map>

comment::comment(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::comment)
{
    ui->setupUi(this);
}

comment::~comment()
{
    delete ui;
}

QString output;

// 获取树洞所有评论内容
void comment::on_pushButton_comment_clicked()
{
    int pid = ui->lineEdit->text().toInt();
    if (pid == 0) {
        ui->textBrowser->setText("请输入洞号！");
        return;
    }
    output = "";
    QString url = urlSearch.arg(100).arg(pid).arg(userToken);
    QNetworkRequest request;
    QNetworkAccessManager * m_manager = new QNetworkAccessManager(this);
    request.setUrl(QUrl(url));
    m_manager->get(request);   //向网页发起get请求
    connect(m_manager, SIGNAL(finished(QNetworkReply*)), this,SLOT(processHole(QNetworkReply*)));
}

// 解析该树洞的回复数，关注数和内容
void comment::processHole(QNetworkReply* reply) {
    // 获取http状态码
    QVariant statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute);
    if(statusCode.isValid())
        qDebug() << "processHole, status code=" << statusCode.toInt();

    if(reply->error()==QNetworkReply::NoError) {
        QByteArray resBytes = reply->readAll();
        QJsonDocument doc = QJsonDocument::fromJson(resBytes);
        QJsonObject json = doc.object();
        QJsonValue value = json.value("data");
        QJsonArray valueArray = value.toArray();
        QJsonValue holeArray = valueArray.at(valueArray.size() - 1);
        QJsonObject hole = holeArray.toObject();
        output.append("回复数：" + QString::number(hole["reply"].toString().toInt()) + "  ");
        output.append("关注数：" + QString::number(hole["likenum"].toString().toInt()) + "\n");
        output.append(hole["text"].toString() + "\n");
        output.append("+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+\n");
        QString url = urlComment.arg(hole["pid"].toString().toInt()).arg(userToken);
        QNetworkRequest request;
        QNetworkAccessManager * m_manager = new QNetworkAccessManager(this);
        request.setUrl(QUrl(url));
        m_manager->get(request);   //向网页发起get请求
        connect(m_manager, SIGNAL(finished(QNetworkReply*)), this,SLOT(processComment(QNetworkReply*)));
    }
}

// 解析该树洞的所有回复
void comment::processComment(QNetworkReply* reply) {
    // 获取http状态码
    QVariant statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute);
    if(statusCode.isValid())
        qDebug() << "processComment, status code=" << statusCode.toInt();

    if(reply->error()==QNetworkReply::NoError) {
        QByteArray resBytes = reply->readAll();
        QJsonDocument doc = QJsonDocument::fromJson(resBytes);
        QJsonObject json = doc.object();
        QJsonValue value = json.value("data");
        QJsonArray valueArray = value.toArray();

        std::map<int, QString> commentMap;       // 按时间升序排序，map的first元素为评论的cid

        int num = valueArray.size();
        for (int i = 0; i < num; ++i) {
            // 通过 QJsonArray::at(i)函数获取数组下的第i个元素
            QJsonValue replyArray = valueArray.at(i);
            // 通过 QJsonValue::toObject()函数将数组元素转换成Object对象
            QJsonObject reply = replyArray.toObject();
            commentMap[reply["cid"].toString().toInt()] = reply["text"].toString();
        }
        int line = 1;
        for (auto & it : commentMap) {
            output.append(QString::number(line) + " " + it.second + "\n");
            ++line;
        }
        ui->textBrowser->setText(output);
    }
}

