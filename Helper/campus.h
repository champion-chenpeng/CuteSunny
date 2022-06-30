#ifndef CAMPUS_H
#define CAMPUS_H

#include <QWidget>
#include <QNetworkReply>

namespace Ui {
class campus;
}

class campus : public QWidget
{
    Q_OBJECT

public:
    explicit campus(QWidget *parent = nullptr);
    ~campus();

private slots:
    void on_pushButton_canteen_clicked();

    void processCanteen(QNetworkReply *reply);

    void on_pushButton_gym_clicked();

    void processGym(QNetworkReply *reply);

    void on_pushButton_classroom_clicked();

    void processClassroom(QNetworkReply *reply);

private:
    Ui::campus *ui;
};

#endif // CAMPUS_H
