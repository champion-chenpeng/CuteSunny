#ifndef COMMENT_H
#define COMMENT_H

#include <QWidget>
#include <QNetworkReply>

namespace Ui {
class comment;
}

class comment : public QWidget
{
    Q_OBJECT

public:
    explicit comment(QWidget *parent = nullptr);
    ~comment();

private slots:

    void on_pushButton_clicked();

    void processHole(QNetworkReply* reply);

    void processComment(QNetworkReply* reply);

private:
    Ui::comment *ui;
};

#endif // COMMENT_H
