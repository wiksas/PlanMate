#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "BusinessLogic/task.h"
#include "BusinessLogic/taskmanager.h"
#include "BusinessLogic/taskmodel.h"
#include <QMessageBox>

//Do dodania obsluga przyciskow dodaj i usun


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    manager = new TaskManager(this);
    model = new TaskModel(manager, this);
    ui->tableView->setModel(model);



    ui->Data->setDateTime(QDateTime::currentDateTime());
    ui->DataEdycja->setDateTime(QDateTime::currentDateTime());
    ui->Prio1->setChecked(true);
    ui->DoZrobienia->setChecked(true);
    ui->Prio1Edycja->setChecked(true);
    ui->DoZrobieniaEdycja->setChecked(true);

    connect(ui->tableView, &QTableView::clicked, this, &MainWindow::on_tableRow_clicked);


}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_Dodaj_clicked()
{
    QString nazwa = ui->Nazwa->toPlainText();
    QString opis = ui->Opis->toPlainText();
    QDateTime data = ui->Data->dateTime();
    QString priorytet = "";
    if (ui->Prio1->isChecked()) {
        priorytet = "Niski";
    } else if (ui->Prio2->isChecked()) {
        priorytet = "Średni";
    } else if (ui->Prio3->isChecked()) {
        priorytet = "Wysoki";
    }

    QString status = "";
    if (ui->DoZrobienia->isChecked()) {
        status = "do zrobienia";
    } else if (ui->WTrakcie->isChecked()) {
        status = "w trakcie";
    } else if (ui->Zrobione->isChecked()) {
        status = "zrobione";
    }

    if (nazwa.isEmpty()) {
        QMessageBox::warning(this, "Błąd", "Nazwa zadania nie może być pusta!");
        return;
    }

    model->addTask(Task(nazwa, opis, status, data, priorytet));

    QMessageBox::information(this, "Dodaj Zadanie",
                             QString("Dodano zadanie:\nNazwa: %1\nData: %2\nPriorytet: %3\nStatus: %4")
                                 .arg(nazwa, data.toString("yyyy-MM-dd"), priorytet, status));

    wyczyscPolaDodawania();
}

void MainWindow::on_tableRow_clicked(const QModelIndex &index)
{
    int row = index.row();
    if (row < 0 || row >= model->rowCount()) return;

    Task task = manager->getTask(row);

    ui->NazwaEdycja->setPlainText(task.getTitle());
    ui->OpisEdycja->setPlainText(task.getDescription());
    ui->DataEdycja->setDateTime(task.getDeadline());

    if (task.getStatus() == "do zrobienia") ui->DoZrobieniaEdycja->setChecked(true);
    else if (task.getStatus() == "w trakcie") ui->WTrakcieEdycja->setChecked(true);
    else if (task.getStatus() == "zrobione") ui->ZrobioneEdycja->setChecked(true);

    ui->tableView->selectRow(row);
}


void MainWindow::on_DodajEdycja_clicked()
{
    QModelIndex index = ui->tableView->currentIndex();
    int row = index.row();
    if (row < 0 || row >= model->rowCount()) {
        QMessageBox::warning(this, "Błąd", "Nie wybrano zadania do edycji.");
        return;
    }

    QString nazwa = ui->NazwaEdycja->toPlainText();
    QString opis = ui->OpisEdycja->toPlainText();
    QDateTime data = ui->DataEdycja->dateTime();

    QString priorytet_edycja = "";
    if (ui->Prio1Edycja->isChecked()) {
        priorytet_edycja = "Niski";
    } else if (ui->Prio2Edycja->isChecked()) {
        priorytet_edycja = "Średni";
    } else if (ui->Prio3Edycja->isChecked()) {
        priorytet_edycja = "Wysoki";
    }

    QString status;
    if (ui->DoZrobieniaEdycja->isChecked()) status = "do zrobienia";
    else if (ui->WTrakcieEdycja->isChecked()) status = "w trakcie";
    else if (ui->ZrobioneEdycja->isChecked()) status = "zrobione";

    if (nazwa.isEmpty()) {
        QMessageBox::warning(this, "Błąd", "Nazwa nie może być pusta!");
        return;
    }

    Task& task = manager->getTask(row);
    task.setTitle(nazwa);
    task.setDescription(opis);
    task.setStatus(status);
    task.setDeadline(data);
    task.setPriority(priorytet_edycja);

    model->dataChanged(model->index(row, 0), model->index(row, model->columnCount() - 1));
}

void MainWindow::wyczyscPolaDodawania()
{
    ui->Nazwa->clear();
    ui->Opis->clear();
    ui->Data->setDateTime(QDateTime::currentDateTime());
    ui->Prio1->setChecked(true);
    ui->DoZrobienia->setChecked(true);
}





void MainWindow::on_UsunEdycja_clicked()
{
    QModelIndex index = ui->tableView->currentIndex();
    int row = index.row();
    if (row < 0 || row >= model->rowCount()) {
        QMessageBox::warning(this, "Błąd", "Nie wybrano zadania do usunięcia.");
        return;
    }

    if (QMessageBox::question(this, "Potwierdzenie", "Czy na pewno chcesz usunąć to zadanie?") == QMessageBox::Yes) {
        model->removeTask(row);
    }
}

