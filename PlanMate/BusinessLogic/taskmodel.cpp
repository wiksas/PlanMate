#include "taskmodel.h"
#include <QtGui/qbrush.h>
#include <QtGui/qcolor.h>



TaskModel::TaskModel(TaskManager* manager, QObject* parent)
    : QAbstractTableModel(parent), m_manager(manager) {}

//zwraca liczbe zadan
int TaskModel::rowCount(const QModelIndex&) const {
    return m_manager->taskCount();
}

//zwraca stala ilosc kolumn; do dodania deadline i priorytem(chociaz to mozna przedstawiac kolorem)
int TaskModel::columnCount(const QModelIndex&) const {
    return 4; // title, description, status, deadline
}

//pobiera dane z konkretnego taska do wyswietlenia w jednej komorce
QVariant TaskModel::data(const QModelIndex& index, int role) const {
    if (!index.isValid()) return {};

    const Task& task = m_manager->getTasks().at(index.row());

    if (role == Qt::DisplayRole) {
        switch (index.column()) {
        case 0: return task.getTitle();
        case 1: return task.getDescription();
        case 2: return task.getStatus();
        case 3: return task.getDeadline().toString("yyyy-MM-dd HH:mm");
        default: return {};
        }
    }

    // Kolorowanie tła wiersza wg priorytetu
    if (role == Qt::BackgroundRole) {
        QString priority = task.getPriority();  // np. "Niski", "Średni", "Wysoki"

        if (priority == "Średni") {
            return QBrush(QColor(125, 125, 0));
        } else if (priority == "Wysoki") {
            return QBrush(QColor(125, 0, 0));
        }
        // brak koloru dla "Niski"
    }

    return {};

}

//zwraca tekst naglowka dla kolumn; wywoluje sie przy renderowaniu tablicy
QVariant TaskModel::headerData(int section, Qt::Orientation orientation, int role) const {
    if (role != Qt::DisplayRole || orientation != Qt::Horizontal) return {};
    switch (section) {
    case 0: return "Nazwa";
    case 1: return "Opis";
    case 2: return "Status";
    case 3: return "Data";

    default: return {};
    }
}
//Okresla co mozna zrobic z komorka
Qt::ItemFlags TaskModel::flags(const QModelIndex& index) const {
    if (!index.isValid()) return Qt::NoItemFlags;
    return Qt::ItemIsSelectable | Qt::ItemIsEnabled; // bez editable!
}


//obsluga edycji komorki
bool TaskModel::setData(const QModelIndex& index, const QVariant& value, int role) {
    if (!index.isValid() || role != Qt::EditRole) return false;

    Task& task = m_manager->getTask(index.row());

    switch (index.column()) {
    case 0: task.setTitle(value.toString()); break;
    case 1: task.setDescription(value.toString()); break;
    case 2: task.setStatus(value.toString()); break;
    case 3: task.setDeadline(value.toDateTime()); break;
    default: return false;
    }

    emit dataChanged(index, index);
    return true;
}

//dodawanie nowego taska
void TaskModel::addTask(const Task& task) {
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    m_manager->addTask(task);
    endInsertRows();
}

//usuwanie taska
void TaskModel::removeTask(int row) {
    if (row < 0 || row >= rowCount()) return;
    beginRemoveRows(QModelIndex(), row, row);
    m_manager->removeTask(row);
    endRemoveRows();
}
