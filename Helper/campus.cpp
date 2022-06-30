#include "campus.h"
#include "ui_campus.h"

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

#include <algorithm>
#include <vector>
#include <map>
#include <set>

campus::campus(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::campus)
{
    ui->setupUi(this);
}

campus::~campus()
{
    delete ui;
}

// 查询食堂用餐人数
void campus::on_pushButton_canteen_clicked()
{
    QNetworkRequest request;
    QNetworkAccessManager * m_manager = new QNetworkAccessManager(this);
    request.setUrl(QUrl(QString("https://portal.pku.edu.cn/portal2017/publicsearch/canteen/retrCarteenInfos.do")));
    m_manager->get(request);   //向网页发起get请求
    connect(m_manager, SIGNAL(finished(QNetworkReply*)), this,SLOT(processCanteen(QNetworkReply*)));
    //请求完成,获取数据并在槽函数中进行处理
}

// 食堂
struct Canteen {
    int ip, seat;
    QString name;
    Canteen() {}
    bool operator < (const Canteen & c) const {
        return double(ip) / seat < double(c.ip) / c.seat;
    }
} CanteenList[30];

void campus::processCanteen(QNetworkReply* reply) {
    // 获取http状态码
    QVariant statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute);
    if(statusCode.isValid())
        qDebug() << "processCanteen, status code=" << statusCode.toInt();

    if(reply->error()==QNetworkReply::NoError) {
        QByteArray resBytes = reply->readAll();
        QJsonDocument doc = QJsonDocument::fromJson(resBytes);
        QJsonObject json = doc.object();

        if (json.contains("rows")) {
            QJsonValue value = json.value("rows");
            QJsonArray valueArray = value.toArray();
            int canteenNum = valueArray.size();
            for (int i = 0; i < canteenNum; ++i) {
                // 通过 QJsonArray::at(i)函数获取数组下的第i个元素
                QJsonValue canteenArray = valueArray.at(i);
                // 通过 QJsonValue::toObject()函数将数组元素转换成Object对象
                QJsonObject canteen = canteenArray.toObject();
                CanteenList[i].ip = canteen["ip"].toInt();
                CanteenList[i].seat = canteen["seat"].toInt();
                CanteenList[i].name = canteen["name"].toString();
            }
            std::sort(CanteenList, CanteenList + canteenNum);
            // 获取整数
            bool ok;
            int num = QInputDialog::getInt(this, tr("查询最空闲的食堂"),
                                           tr("请输入需要为您推荐的食堂数目："), 10, 1, canteenNum, 1, &ok);
            if(ok) {
                QString output = "";
                for (int i = 1; i <= num; ++i) {
                    output.append(QString::number(i) + "  ");
                    output.append(CanteenList[i].name);
                    output.append("  占据情况：" + QString::number(CanteenList[i].ip) + " / "
                                  + QString::number(CanteenList[i].seat) + "\n");
                }
                ui->textBrowser->setText(output);
            }
        }
    }
}

// 运动场馆
struct Gym {
    int capacity, occupy, orderNum;
    QString areaName;
    Gym(int x, int y, int z, QString s): capacity(x), occupy(y), orderNum(z), areaName(s) {}
    bool operator < (const Gym & g) const {
        if (double(occupy) / capacity != double(g.occupy) / g.capacity)
            return double(occupy) / capacity < double(g.occupy) / g.capacity;
        return areaName.size() < g.areaName.size();
    }
};
std::vector<Gym> gymList[12];

// 查询场馆占据情况
void campus::on_pushButton_gym_clicked()
{
    QNetworkRequest request;
    QNetworkAccessManager * m_manager = new QNetworkAccessManager(this);
    request.setUrl(QUrl(QString("https://portal.pku.edu.cn/portal2017/publicsearch/gym/retrGymInfos.do?capacityType=1")));
    m_manager->get(request);   //向网页发起get请求
    connect(m_manager, SIGNAL(finished(QNetworkReply*)), this,SLOT(processGym(QNetworkReply*)));
    //请求完成,获取数据并在槽函数中进行处理

    bool ok;
    QStringList items;
    items << tr("篮球") << tr("足球") << tr("排球") << tr("乒乓球") << tr("羽毛球") << tr("网球") << tr("壁球") << tr("台球")
          << tr("游泳") << tr("健身");
    // 获取条目
    QString item = QInputDialog::getItem(this, tr("运动选择"), tr("请选择一项运动"), items, 0, false, &ok);
    if(ok) {
        int index = items.indexOf(item);
        sort(gymList[index].begin(), gymList[index].end());
        QString output = item;
        for (auto & it : gymList[index]) {
            output.append(it.areaName + "\n");
            output.append("占据情况：" + QString::number(it.occupy) + " / " + QString::number(it.capacity)  + "\n\n");
        }
        ui->textBrowser->setText(output);
    }
}

void campus::processGym(QNetworkReply* reply) {
    // 获取http状态码
    QVariant statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute);
    if(statusCode.isValid())
        qDebug() << "processGym, status code=" << statusCode.toInt();

    if(reply->error()==QNetworkReply::NoError) {
        QByteArray resBytes = reply->readAll();
        QJsonDocument doc = QJsonDocument::fromJson(resBytes);
        QJsonObject json = doc.object();

        QJsonValue value = json.value("gyms");
        QJsonArray valueArray = value.toArray();

        memset(gymList, 0, sizeof(gymList));
        int gymNum = valueArray.size();

        for (int i = 0; i < gymNum; ++i) {
            // 通过 QJsonArray::at(i)函数获取数组下的第i个元素
            QJsonValue gymArray = valueArray.at(i);

            // 通过 QJsonValue::toObject()函数将数组元素转换成Object对象
            QJsonObject gym = gymArray.toObject();
            int areaId = gym["areaId"].toString().toInt();
            switch (areaId)
            {
                case 60:
                    gymList[4].push_back(Gym(gym["capacity"].toInt(), gym["occupy"].toInt(), gym["orderNum"].toInt(), gym["areaName"].toString()));
                    break;
                case 61:
                    gymList[3].push_back(Gym(gym["capacity"].toInt(), gym["occupy"].toInt(), gym["orderNum"].toInt(), gym["areaName"].toString()));
                    break;
                case 62:
                    gymList[9].push_back(Gym(gym["capacity"].toInt(), gym["occupy"].toInt(), gym["orderNum"].toInt(), gym["areaName"].toString()));
                    break;
                case 64:
                    gymList[7].push_back(Gym(gym["capacity"].toInt(), gym["occupy"].toInt(), gym["orderNum"].toInt(), gym["areaName"].toString()));
                    break;
                case 65:
                    gymList[6].push_back(Gym(gym["capacity"].toInt(), gym["occupy"].toInt(), gym["orderNum"].toInt(), gym["areaName"].toString()));
                    break;
                case 67:
                    gymList[8].push_back(Gym(gym["capacity"].toInt(), gym["occupy"].toInt(), gym["orderNum"].toInt(), gym["areaName"].toString()));
                    break;
                case 68:
                    gymList[0].push_back(Gym(gym["capacity"].toInt(), gym["occupy"].toInt(), gym["orderNum"].toInt(), gym["areaName"].toString()));
                    break;
                case 80:
                    gymList[6].push_back(Gym(gym["capacity"].toInt(), gym["occupy"].toInt(), gym["orderNum"].toInt(), gym["areaName"].toString()));
                    break;
                case 82:
                    gymList[0].push_back(Gym(gym["capacity"].toInt(), gym["occupy"].toInt(), gym["orderNum"].toInt(), gym["areaName"].toString()));
                    break;
                case 83:
                    gymList[1].push_back(Gym(gym["capacity"].toInt(), gym["occupy"].toInt(), gym["orderNum"].toInt(), gym["areaName"].toString()));
                    break;
                case 84:
                    gymList[2].push_back(Gym(gym["capacity"].toInt(), gym["occupy"].toInt(), gym["orderNum"].toInt(), gym["areaName"].toString()));
                    break;
                case 85:
                    gymList[5].push_back(Gym(gym["capacity"].toInt(), gym["occupy"].toInt(), gym["orderNum"].toInt(), gym["areaName"].toString()));
                    break;
                case 86:
                    gymList[4].push_back(Gym(gym["capacity"].toInt(), gym["occupy"].toInt(), gym["orderNum"].toInt(), gym["areaName"].toString()));
                    break;
                case 88:
                    gymList[9].push_back(Gym(gym["capacity"].toInt(), gym["occupy"].toInt(), gym["orderNum"].toInt(), gym["areaName"].toString()));
                    break;
                case 93:
                    gymList[3].push_back(Gym(gym["capacity"].toInt(), gym["occupy"].toInt(), gym["orderNum"].toInt(), gym["areaName"].toString()));
                    break;
                case 108:
                    gymList[6].push_back(Gym(gym["capacity"].toInt(), gym["occupy"].toInt(), gym["orderNum"].toInt(), gym["areaName"].toString()));
                    break;
                case 109:
                    gymList[5].push_back(Gym(gym["capacity"].toInt(), gym["occupy"].toInt(), gym["orderNum"].toInt(), gym["areaName"].toString()));
                    break;
                case 113:
                    gymList[8].push_back(Gym(gym["capacity"].toInt(), gym["occupy"].toInt(), gym["orderNum"].toInt(), gym["areaName"].toString()));
                    break;
                case 114:
                    gymList[8].push_back(Gym(gym["capacity"].toInt(), gym["occupy"].toInt(), gym["orderNum"].toInt(), gym["areaName"].toString()));
                    break;
                case 115:
                    gymList[0].push_back(Gym(gym["capacity"].toInt(), gym["occupy"].toInt(), gym["orderNum"].toInt(), gym["areaName"].toString()));
                    gymList[2].push_back(Gym(gym["capacity"].toInt(), gym["occupy"].toInt(), gym["orderNum"].toInt(), gym["areaName"].toString()));
                    break;
            }
        }
    }

}

// 查询空闲教室
void campus::on_pushButton_classroom_clicked()
{
    QNetworkRequest request;
    QNetworkAccessManager * m_manager = new QNetworkAccessManager(this);
    request.setUrl(QUrl(QString("https://portal.pku.edu.cn/portal2017/publicsearch/classroom/retrClassRoomInfos.do")));
    m_manager->get(request);   //向网页发起get请求
    connect(m_manager, SIGNAL(finished(QNetworkReply*)), this,SLOT(processClassroom(QNetworkReply*)));
    //请求完成,获取数据并在槽函数中进行处理
}

// 教学楼
struct Building {
    int classroomFree, classroomSum;
    Building() {}
    Building(int x, int y): classroomFree(x), classroomSum(y) {}
};

void campus::processClassroom(QNetworkReply* reply) {
    // 获取http状态码
    QVariant statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute);
    if(statusCode.isValid())
        qDebug() << "processClassroom, status code=" << statusCode.toInt();

    if(reply->error()==QNetworkReply::NoError) {
        QByteArray resBytes = reply->readAll();

        QJsonDocument doc = QJsonDocument::fromJson(resBytes);
        QJsonObject json = doc.object();

        QJsonValue value = json.value("rows");
        QJsonArray valueArray = value.toArray();

        std::map<QString, Building> buildingMap;
        QStringList items;

        int buildingNum = valueArray.size();
        for (int i = 0; i < buildingNum; ++i) {
            // 通过 QJsonArray::at(i)函数获取数组下的第i个元素
            QJsonValue buildingArray = valueArray.at(i);
            // 通过 QJsonValue::toObject()函数将数组元素转换成Object对象
            QJsonObject building = buildingArray.toObject();
            QString buildingName = building["buildingName"].toString();
            buildingMap[buildingName] = Building(building["classroomFree"].toInt(), building["classroomSum"].toInt());
            items << tr(buildingName.toStdString().c_str());
        }
        bool ok;
        // 获取条目
        QString item = QInputDialog::getItem(this, tr("教学楼选择"), tr("请选择一栋教学楼"), items, 0, false, &ok);
        if(ok) {
            QString output = item;
            output += "\n";
            output.append("空闲教室：" + QString::number(buildingMap[item].classroomFree) + "\n");
            output.append("总教室数：" + QString::number(buildingMap[item].classroomSum) + "\n");
            ui->textBrowser->setText(output);
        }
    }
}
