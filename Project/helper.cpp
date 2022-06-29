#include "helper.h"
#include "ui_helper.h"

Helper::Helper(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Helper)
{
    ui->setupUi(this);
}

Helper::~Helper()
{
    delete ui;
}

