#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "BusinessLogic/task.h"
#include "BusinessLogic/taskmanager.h"
#include "BusinessLogic/taskmodel.h"
#include <QMessageBox>



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    manager = new TaskManager(this);
    modelDoZrobienia = new TaskModel(manager, this);
    modelZrobione = new TaskModel(manager, this);

    // Ustawia modele dla widoków tabel
    ui->tableViewDoZrobienia->setModel(modelDoZrobienia);
    ui->tableViewZrobione->setModel(modelZrobione);

    // Ustawia własciwości tabel
    ui->tableViewDoZrobienia->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableViewDoZrobienia->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableViewZrobione->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableViewZrobione->setSelectionMode(QAbstractItemView::SingleSelection);

    connect(ui->tableViewDoZrobienia, &QTableView::clicked,
            this, &MainWindow::on_tableRow_clickedDoZrobienia);

    connect(ui->tableViewZrobione, &QTableView::clicked,
            this, &MainWindow::on_tableRow_clickedZrobione);

    ui->Data->setDateTime(QDateTime::currentDateTime());
    ui->DataEdycja->setDateTime(QDateTime::currentDateTime());
    ui->Prio1->setChecked(true);
    ui->DoZrobienia->setChecked(true);
    ui->Prio1Edycja->setChecked(true);
    ui->DoZrobieniaEdycja->setChecked(true);

    odswiezModele();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_Dodaj_clicked() //Dodaje zadanie do tabeli z wprowadzonymi danymi
{
    QString nazwa = ui->Nazwa->toPlainText();
    QString opis = ui->Opis->toPlainText();
    QDateTime data = ui->Data->dateTime();

    QString priorytet;
    if (ui->Prio1->isChecked()) priorytet = "Niski";
    else if (ui->Prio2->isChecked()) priorytet = "Średni";
    else if (ui->Prio3->isChecked()) priorytet = "Wysoki";

    QString status;
    if (ui->DoZrobienia->isChecked()) status = "do zrobienia";
    else if (ui->WTrakcie->isChecked()) status = "w trakcie";
    else if (ui->Zrobione->isChecked()) status = "zrobione";

    if (nazwa.isEmpty()) {
        QMessageBox::warning(this, "Błąd", "Nazwa zadania nie może być pusta!");
        return;
    }

    manager->addTask(Task(nazwa, opis, status, data, priorytet));
    odswiezModele();

    QMessageBox::information(this, "Dodano zadanie", QString("Nazwa: %1\nData: %2\nPriorytet: %3\nStatus: %4").arg(nazwa, data.toString("yyyy-MM-dd"), priorytet, status));

    wyczyscPolaDodawania();
}

void MainWindow::on_tableRow_clickedDoZrobienia(const QModelIndex &index) //Pobiera indeks zadania klikniętego w tabeli 'do zrobienia' i wstawia dane do pola edycji
{
    int row = index.row();
    if (row < 0 || row >= modelDoZrobienia->rowCount()) return;

    // Pobiera oryginalny indeks z managera
    int originalIndex = modelDoZrobienia->getOriginalIndex(row);
    if (originalIndex < 0 || originalIndex >= manager->taskCount()) return;

    Task& task = manager->getTask(originalIndex);

    ui->NazwaEdycja->setPlainText(task.getTitle());
    ui->OpisEdycja->setPlainText(task.getDescription());
    ui->DataEdycja->setDateTime(task.getDeadline());

    // Ustaw priorytet
    if (task.getPriority() == "Niski") ui->Prio1Edycja->setChecked(true);
    else if (task.getPriority() == "Średni") ui->Prio2Edycja->setChecked(true);
    else if (task.getPriority() == "Wysoki") ui->Prio3Edycja->setChecked(true);

    // Ustaw status
    if (task.getStatus() == "do zrobienia") ui->DoZrobieniaEdycja->setChecked(true);
    else if (task.getStatus() == "w trakcie") ui->WTrakcieEdycja->setChecked(true);
    else if (task.getStatus() == "zrobione") ui->checkBoxWykonane->setChecked(true);

    ui->tableViewDoZrobienia->selectRow(row);
}

void MainWindow::on_tableRow_clickedZrobione(const QModelIndex &index) //Pobiera indeks zadania klikniętego w tabeli 'zakonczone' i wstawia dane do pola edycji
{
    int row = index.row();
    if (row < 0 || row >= modelZrobione->rowCount()) return;

    // Pobierz oryginalny indeks z managera
    int originalIndex = modelZrobione->getOriginalIndex(row);
    if (originalIndex < 0 || originalIndex >= manager->taskCount()) return;

    Task& task = manager->getTask(originalIndex);

    ui->NazwaEdycja->setPlainText(task.getTitle());
    ui->OpisEdycja->setPlainText(task.getDescription());
    ui->DataEdycja->setDateTime(task.getDeadline());

    // Ustaw priorytet
    if (task.getPriority() == "Niski") ui->Prio1Edycja->setChecked(true);
    else if (task.getPriority() == "Średni") ui->Prio2Edycja->setChecked(true);
    else if (task.getPriority() == "Wysoki") ui->Prio3Edycja->setChecked(true);

    // Dla zakończonych zadań
    ui->checkBoxWykonane->setChecked(true);

    ui->tableViewZrobione->selectRow(row);
}



void MainWindow::on_DodajEdycja_clicked() // obsluga pola edycji
{
    QModelIndex index;
    int originalIndex = -1;

    // Sprawdza ktora zakładka jest aktywna i pobierz oryginalny indeks
    if (ui->tabWidgetZadania->currentIndex() == 0) // Do zrobienia
    {
        index = ui->tableViewDoZrobienia->currentIndex();
        if (index.isValid()) {
            originalIndex = modelDoZrobienia->getOriginalIndex(index.row());
        }
    }
    else if (ui->tabWidgetZadania->currentIndex() == 1) // Zrobione
    {
        index = ui->tableViewZrobione->currentIndex();
        if (index.isValid()) {
            originalIndex = modelZrobione->getOriginalIndex(index.row());
        }
    }

    if (originalIndex < 0 || originalIndex >= manager->taskCount()) {
        QMessageBox::warning(this, "Błąd", "Nie wybrano zadania do edycji.");
        return;
    }

    QString nazwa = ui->NazwaEdycja->toPlainText();
    QString opis = ui->OpisEdycja->toPlainText();
    QDateTime data = ui->DataEdycja->dateTime();

    QString priorytet_edycja;
    if (ui->Prio1Edycja->isChecked()) priorytet_edycja = "Niski";
    else if (ui->Prio2Edycja->isChecked()) priorytet_edycja = "Średni";
    else if (ui->Prio3Edycja->isChecked()) priorytet_edycja = "Wysoki";

    if (nazwa.isEmpty()) {
        QMessageBox::warning(this, "Błąd", "Nazwa nie może być pusta!");
        return;
    }

    Task& task = manager->getTask(originalIndex);
    task.setTitle(nazwa);
    task.setDescription(opis);
    task.setDeadline(data);
    task.setPriority(priorytet_edycja);

    // Ustawienie statusu na podstawie checkboxa
    if (ui->checkBoxWykonane->isChecked()) {
        task.setStatus("zrobione");
    } else if (ui->DoZrobieniaEdycja->isChecked()) {
        task.setStatus("do zrobienia");
    } else if (ui->WTrakcieEdycja->isChecked()) {
        task.setStatus("w trakcie");
    }

    // Uaktualnij modele i widok
    odswiezModele();

    QMessageBox::information(this, "Edycja", "Zadanie zostało zaktualizowane.");

    ui->tableViewDoZrobienia->clearSelection();
    ui->tableViewZrobione->clearSelection();

    ui->NazwaEdycja->clear();
    ui->OpisEdycja->clear();
    ui->DataEdycja->setDateTime(QDateTime::currentDateTime());
    ui->Prio1Edycja->setChecked(true);
    ui->DoZrobieniaEdycja->setChecked(true);
    ui->checkBoxWykonane->setChecked(false);
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
    QModelIndex index;
    int originalIndex = -1;

    // Sprawdź która zakładka jest aktywna i pobierz oryginalny indeks
    if (ui->tabWidgetZadania->currentIndex() == 0) // Do zrobienia
    {
        index = ui->tableViewDoZrobienia->currentIndex();
        if (index.isValid()) {
            originalIndex = modelDoZrobienia->getOriginalIndex(index.row());
        }
    }
    else if (ui->tabWidgetZadania->currentIndex() == 1) // Zrobione
    {
        index = ui->tableViewZrobione->currentIndex();
        if (index.isValid()) {
            originalIndex = modelZrobione->getOriginalIndex(index.row());
        }
    }

    if (originalIndex < 0 || originalIndex >= manager->taskCount()) {
        QMessageBox::warning(this, "Błąd", "Nie wybrano zadania do usunięcia.");
        return;
    }

    if (QMessageBox::question(this, "Potwierdzenie", "Czy na pewno chcesz usunąć to zadanie?") == QMessageBox::Yes) {
        manager->removeTask(originalIndex);
        odswiezModele();

        // Wyczyść pola edycji
        ui->NazwaEdycja->clear();
        ui->OpisEdycja->clear();
        ui->DataEdycja->setDateTime(QDateTime::currentDateTime());
        ui->Prio1Edycja->setChecked(true);
        ui->DoZrobieniaEdycja->setChecked(true);
        ui->checkBoxWykonane->setChecked(false);
    }
}


void MainWindow::odswiezModele()
{
    QVector<Task> doZrobienia;
    QVector<Task> zrobione;

    for (const Task& task : manager->getTasks()) {
        if (task.getStatus() == "zrobione") {
            zrobione.append(task);
        } else {
            doZrobienia.append(task);
        }
    }

    modelDoZrobienia->setTasks(manager->getTasks(), "do zrobienia");
    modelZrobione->setTasks(manager->getTasks(), "zrobione");

}