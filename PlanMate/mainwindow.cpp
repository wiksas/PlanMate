#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "BusinessLogic/task.h"
#include "BusinessLogic/taskmanager.h"
#include "BusinessLogic/taskmodel.h"

//Do dodania obsluga przyciskow dodaj i usun

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    TaskManager* manager = new TaskManager(this);
    TaskModel* model = new TaskModel(manager, this);

    // Przykladowy task
    manager->addTask(Task("Kup mleko", "Spożywcze", false));

    // Laczenie tabeli z modelem
    ui->tableView->setModel(model);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_addButton_clicked()
{

}

