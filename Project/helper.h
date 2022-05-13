#ifndef HELPER_H
#define HELPER_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class Helper; }
QT_END_NAMESPACE

class Helper : public QMainWindow
{
    Q_OBJECT

public:
    Helper(QWidget *parent = nullptr);
    ~Helper();

private:
    Ui::Helper *ui;
};
#endif // HELPER_H
