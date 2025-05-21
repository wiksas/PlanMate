#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QMessageBox>
#include <QDate>
#include <QFile>
#include <QTextStream>
#include <QListWidgetItem>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

struct Zadanie {
    QString nazwa;
    QDate data;
    QString priorytet;
    QString status;
};


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_Dodaj_clicked();
    void on_Edytuj_clicked();
    void on_wczytaj_plikow_clicked();
    void on_zapisz_zadania_clicked();

    void on_listWidgetZadania_itemClicked(QListWidgetItem *item);

private:
    Ui::MainWindow *ui;
    QList<Zadanie> listaZadan;

    void aktualizujListeZadan();
    void wyczyscPolaDodawania();
};
#endif // MAINWINDOW_H
