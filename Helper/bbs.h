#ifndef BBS_H
#define BBS_H

#include <QWidget>
#include <QNetworkReply>

namespace Ui {
class bbs;
}

class bbs : public QWidget
{
    Q_OBJECT

public:
    explicit bbs(QWidget *parent = nullptr);
    ~bbs();

private slots:
    void on_pushButton_bbs_clicked();

    void processBBS(QNetworkReply *reply);

    void bbs_mail();

private:
    Ui::bbs *ui;
};

#endif // BBS_H
