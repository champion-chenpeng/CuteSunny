#ifndef TREEHOLE_H
#define TREEHOLE_H

#include <QWidget>
#include <QNetworkReply>
#include <comment.h>

namespace Ui {
class treehole;
}

class treehole : public QWidget
{
    Q_OBJECT

public:
    explicit treehole(QWidget *parent = nullptr);
    ~treehole();

private slots:

    void on_pushButton_token_clicked();

    void on_pushButton_search_clicked();

    void processSearch(QNetworkReply* reply);

    void on_pushButton_attention_clicked();

    void processAttention(QNetworkReply* reply);

    void on_pushButton_gpa_clicked();

    void processGPA(QNetworkReply* reply);

    void on_pushButton_clicked();

private:
    Ui::treehole *ui;
};

#endif // TREEHOLE_H
