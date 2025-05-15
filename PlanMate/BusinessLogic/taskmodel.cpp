#include "taskmodel.h"

TaskModel::TaskModel(TaskManager* manager, QObject* parent)
    : QAbstractTableModel(parent), m_manager(manager) {}

//zwraca liczbe zadan
int TaskModel::rowCount(const QModelIndex&) const {
    return m_manager->taskCount();
}

//zwraca stala ilosc kolumn; do dodania deadline i priorytem(chociaz to mozna przedstawiac kolorem)
int TaskModel::columnCount(const QModelIndex&) const {
    return 3; // title, description, completed
}

//pobiera dane z konkretnego taska do wyswietlenia w jednej komorce
QVariant TaskModel::data(const QModelIndex& index, int role) const {
    if (!index.isValid() || role != Qt::DisplayRole) return {};

    const Task& task = m_manager->getTasks().at(index.row());

    switch (index.column()) {
    case 0: return task.getTitle();
    case 1: return task.getDescription();
    case 2: return task.isCompleted() ? "Yes" : "No";
    default: return {};
    }
}

//zwraca tekst naglowka dla kolumn; wywoluje sie przy renderowaniu tablicy
QVariant TaskModel::headerData(int section, Qt::Orientation orientation, int role) const {
    if (role != Qt::DisplayRole || orientation != Qt::Horizontal) return {};
    switch (section) {
    case 0: return "Title";
    case 1: return "Description";
    case 2: return "Completed";
    default: return {};
    }
}
//Okresla co mozna zrobic z komorka
Qt::ItemFlags TaskModel::flags(const QModelIndex& index) const {
    if (!index.isValid()) return Qt::NoItemFlags;
    return Qt::ItemIsSelectable | Qt::ItemIsEditable | Qt::ItemIsEnabled;
}

//obsluga edycji komorki
bool TaskModel::setData(const QModelIndex& index, const QVariant& value, int role) {
    if (!index.isValid() || role != Qt::EditRole) return false;

    Task& task = m_manager->getTask(index.row());

    switch (index.column()) {
    case 0: task.setTitle(value.toString()); break;
    case 1: task.setDescription(value.toString()); break;
    case 2: task.setCompleted(value.toBool()); break;
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
