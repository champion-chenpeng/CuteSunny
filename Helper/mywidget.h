#ifndef MYWIDGET_H
#define MYWIDGET_H

#include <QWidget>
#include <treehole.h>
#include <bbs.h>
#include <campus.h>
#include <QWizard>
#include <QNetworkReply>

class QErrorMessage;

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
    void on_pushButton_treehole_clicked();

    void on_pushButton_bbs_clicked();

    void on_pushButton_campus_clicked();

    void on_pushButton_portal_clicked();

    void on_pushButton_course_clicked();

private:
    Ui::MyWidget *ui;
    QErrorMessage *errordlg;

};

#endif // MYWIDGET_H
