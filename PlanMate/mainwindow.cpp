#include "mainwindow.h"
#include "./ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);



    ui->Data->setDate(QDate::currentDate());
    ui->DataEdycja->setDate(QDate::currentDate());
    ui->Prio1->setChecked(true);
    ui->DoZrobienia->setChecked(true);
    ui->Prio1Edycja->setChecked(true);
    ui->DoZrobieniaEdycja->setChecked(true);

    connect(ui->listWidgetZadania, &QListWidget::itemClicked, this, &MainWindow::on_listWidgetZadania_itemClicked);

    aktualizujListeZadan();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_Dodaj_clicked()
{
    QString nazwa = ui->Nazwa->toPlainText();
    QDate data = ui->Data->date();
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

    Zadanie noweZadanie;
    noweZadanie.nazwa = nazwa;
    noweZadanie.data = data;
    noweZadanie.priorytet = priorytet;
    noweZadanie.status = status;

    listaZadan.append(noweZadanie);

    QMessageBox::information(this, "Dodaj Zadanie",
                             QString("Dodano zadanie:\nNazwa: %1\nData: %2\nPriorytet: %3\nStatus: %4")
                                 .arg(nazwa, data.toString("yyyy-MM-dd"), priorytet, status));

    wyczyscPolaDodawania();
    aktualizujListeZadan();
}

void MainWindow::on_Edytuj_clicked()
{

    QListWidgetItem *currentItem = ui->listWidgetZadania->currentItem();
    if (!currentItem) {
        QMessageBox::warning(this, "Błąd", "Wybierz zadanie do edycji z listy!");
        return;
    }

    int index = ui->listWidgetZadania->row(currentItem);

    QString nazwa_edycja = ui->NazwaEdycja->toPlainText();
    QDate data_edycja = ui->DataEdycja->date();
    QString priorytet_edycja = "";
    if (ui->Prio1Edycja->isChecked()) {
        priorytet_edycja = "Niski";
    } else if (ui->Prio2Edycja->isChecked()) {
        priorytet_edycja = "Średni";
    } else if (ui->Prio3Edycja->isChecked()) {
        priorytet_edycja = "Wysoki";
    }

    QString status_edycja = "";
    if (ui->DoZrobieniaEdycja->isChecked()) {
        status_edycja = "do zrobienia";
    } else if (ui->WTrakcieEdycja->isChecked()) {
        status_edycja = "w trakcie";
    } else if (ui->ZrobioneEdycja->isChecked()) {
        status_edycja = "zrobione";
    }

    if (nazwa_edycja.isEmpty()) {
        QMessageBox::warning(this, "Błąd", "Nazwa zadania do edycji nie może być pusta!");
        return;
    }

    if (index >= 0 && index < listaZadan.size()) {
        listaZadan[index].nazwa = nazwa_edycja;
        listaZadan[index].data = data_edycja;
        listaZadan[index].priorytet = priorytet_edycja;
        listaZadan[index].status = status_edycja;
        aktualizujListeZadan();
        QMessageBox::information(this, "Edytuj Zadanie", "Zadanie zaktualizowano pomyślnie!");
    } else {
        QMessageBox::critical(this, "Błąd", "Wystąpił problem");
    }
}


void MainWindow::aktualizujListeZadan()
{
    ui->listWidgetZadania->clear();

    for (const Zadanie &zadanie : listaZadan) {

        QString displayText = QString("%1, %2, %3, %4")
                                  .arg(zadanie.nazwa, zadanie.data.toString("yyyy-MM-dd"), zadanie.priorytet, zadanie.status);
        ui->listWidgetZadania->addItem(displayText);
    }

    qDebug() << "Wywołano aktualizujListeZadan(). Liczba zadań w liście: " << listaZadan.size();
}

void MainWindow::wyczyscPolaDodawania()
{
    ui->Nazwa->clear();
    ui->Data->setDate(QDate::currentDate());
    ui->Prio1->setChecked(true);
    ui->DoZrobienia->setChecked(true);
}

void MainWindow::on_listWidgetZadania_itemClicked(QListWidgetItem *item)
{
    int index = ui->listWidgetZadania->row(item);

    if (index >= 0 && index < listaZadan.size()) {
        const Zadanie &selectedZadanie = listaZadan.at(index);


        ui->NazwaEdycja->setPlainText(selectedZadanie.nazwa);
        ui->DataEdycja->setDate(selectedZadanie.data);


        if (selectedZadanie.priorytet == "Niski") {
            ui->Prio1Edycja->setChecked(true);
        } else if (selectedZadanie.priorytet == "Średni") {
            ui->Prio2Edycja->setChecked(true);
        } else if (selectedZadanie.priorytet == "Wysoki") {
            ui->Prio3Edycja->setChecked(true);
        }


        if (selectedZadanie.status == "do zrobienia") {
            ui->DoZrobieniaEdycja->setChecked(true);
        } else if (selectedZadanie.status == "w trakcie") {
            ui->WTrakcieEdycja->setChecked(true);
        } else if (selectedZadanie.status == "zrobione") {
            ui->ZrobioneEdycja->setChecked(true);
        }
    }
}

void MainWindow::on_wczytaj_plikow_clicked()
{
}

void MainWindow::on_zapisz_zadania_clicked()
{
}
