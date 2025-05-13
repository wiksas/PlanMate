#include "todo.h"
#include "./ui_todo.h"

TODO::TODO(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::TODO)
{
    ui->setupUi(this);
}

TODO::~TODO()
{
    delete ui;
}
