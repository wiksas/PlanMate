#include "planmate.h"
#include "./ui_planmate.h"

PlanMate::PlanMate(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::PlanMate)
{
    ui->setupUi(this);
}

PlanMate::~PlanMate()
{
    delete ui;
}
