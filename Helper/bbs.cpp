#include "bbs.h"
#include "ui_bbs.h"
#include "mainwindow.h"

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

#include <QRegularExpression>
#include <QRegularExpressionMatch>

bbs::bbs(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::bbs)
{
    ui->setupUi(this);
    connect(ui->emailBtn,SIGNAL(clicked()),this, SLOT(bbs_mail()));
}

bbs::~bbs()
{
    delete ui;
}

void bbs::on_pushButton_bbs_clicked()
{
    QNetworkRequest request;
    QNetworkAccessManager * m_manager = new QNetworkAccessManager(this);
    request.setUrl(QUrl(QString("https://bbs.pku.edu.cn/v2/hot-topic.php")));
    m_manager->get(request);   //向网页发起get请求
    connect(m_manager, SIGNAL(finished(QNetworkReply*)), this,SLOT(processBBS(QNetworkReply*)));
    //请求完成,获取数据并在槽函数中进行处理
}

struct BBSPost {
    QString title, board, time;
    BBSPost() {}
} hotTopics[105];     // 100条热点的内容

void bbs::processBBS(QNetworkReply* reply) {
    // 获取http状态码
    QVariant statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute);
    if(statusCode.isValid())
        qDebug() << "processBBS, status code=" << statusCode.toInt();

    if(reply->error()==QNetworkReply::NoError) {
        QByteArray resBytes = reply->readAll();
        // qDebug() << tr(resBytes);
        static QRegularExpression exp_title(".*<div class=\\\"title l limit\\\">.*</div>.*");
        static QRegularExpression exp_board(".*<div class=\\\"board l limit\\\">.*</div>");
        static QRegularExpression exp_time(".*<div class=\"time\">.*</div>.*");

        QStringList htmlList = tr(resBytes).split("\n");
        int topic = 1;
        QString output = "";
        for (int i = 0; i < htmlList.size(); ++i) {
            //qDebug() << htmlList.at(i);
            QRegularExpressionMatch match_title = exp_title.match(htmlList.at(i));
            QRegularExpressionMatch match_board = exp_board.match(htmlList.at(i));
            QRegularExpressionMatch match_time = exp_time.match(htmlList.at(i));
            if (match_title.hasMatch()) {
                QString matched = match_title.captured(0).trimmed();
                matched = matched.mid(matched.indexOf('>') + 1);
                matched = matched.mid(0, matched.indexOf('<'));
                matched.replace("&nbsp;", " ");
                hotTopics[topic].title = matched;
                QString Qtitle =  QString::number(topic) + "  " + matched;
                int bu = 80 - Qtitle.toLocal8Bit().length();    // 使输出对齐
                for (int j = 0; j < bu; ++j)
                    Qtitle += " ";
                output.append(Qtitle);
            }
            if (match_board.hasMatch()) {
                QString matched = match_board.captured(0).trimmed();
                matched = matched.mid(matched.indexOf('>') + 1);
                matched = matched.mid(0, matched.indexOf('<'));
                hotTopics[topic].board = matched;
                output.append(matched);
            }
            if (match_time.hasMatch()) {
                QString matched = match_time.captured(0).trimmed();
                matched = matched.mid(matched.indexOf('>') + 1);
                matched = matched.mid(0, matched.indexOf('<'));
                hotTopics[topic++].time = matched;
                output.append("  " + matched + "\n");
            }
        }
        ui->textBrowser->setText(output);
    }
}

void bbs::bbs_mail()
{
    MainWindow * w = new MainWindow(0,"bbs news",ui->textBrowser->toPlainText());
    w->show();
}
