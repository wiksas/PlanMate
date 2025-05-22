#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "./ui_mainwindow.h"
#include "BusinessLogic/taskmanager.h"
#include "BusinessLogic/taskmodel.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_Dodaj_clicked();

    void on_DodajEdycja_clicked();

    void on_tableRow_clicked(const QModelIndex &index);


    void on_UsunEdycja_clicked();

private:
    Ui::MainWindow *ui;
    TaskManager* manager;
    TaskModel* model;
    void wyczyscPolaDodawania();
};
#endif // MAINWINDOW_H
