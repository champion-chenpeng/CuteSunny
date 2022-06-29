#ifndef MYWIDGET_H
#define MYWIDGET_H

#include <QWidget>
#include <treehole.h>
#include <bbs.h>
#include <campus.h>
class QErrorMessage;
#include <QWizard>
#include <QNetworkReply>

namespace Ui {
class MyWidget;
}

class MyWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MyWidget(QWidget *parent = 0);

    ~MyWidget();

private slots:

    void on_pushButton_portal_clicked();

    void on_pushButton_course_clicked();

    void on_pushButton_9_clicked();

    void on_pushButton_10_clicked();

    void on_pushButton_11_clicked();

private:
    Ui::MyWidget *ui;
    QErrorMessage *errordlg;

};

#endif // MYWIDGET_H
