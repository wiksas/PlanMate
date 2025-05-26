#include "taskmodel.h"
#include <QtGui/qbrush.h>
#include <QtGui/qcolor.h>

TaskModel::TaskModel(TaskManager* manager, QObject* parent)
    : QAbstractTableModel(parent), m_manager(manager) {}

int TaskModel::rowCount(const QModelIndex&) const {
    return m_filteredTasks.size();
}

int TaskModel::columnCount(const QModelIndex&) const {
    return 4;
}

QVariant TaskModel::data(const QModelIndex& index, int role) const {
    if (!index.isValid() || index.row() >= m_filteredTasks.size()) return {};

    const Task& task = m_filteredTasks.at(index.row());

    if (role == Qt::DisplayRole) {
        switch (index.column()) {
        case 0: return task.getTitle();
        case 1: return task.getDescription();
        case 2: return task.getStatus();
        case 3: {
            QDateTime now = QDateTime::currentDateTime();
            QDateTime deadline = task.getDeadline();

            if (deadline < now) {
                qint64 secsAgo = deadline.secsTo(now);
                int minutes = secsAgo / 60;
                int hours = minutes / 60;
                int days = hours / 24;

                QString result;
                if (days > 0) result = QString::number(days) + " dni temu";
                else if (hours > 0) result = QString::number(hours) + " godz. temu";
                else result = QString::number(minutes) + " min temu";

                return result;
            }

            qint64 secs = now.secsTo(deadline);
            int days = secs / (60 * 60 * 24);
            secs %= (60 * 60 * 24);
            int hours = secs / 3600;
            secs %= 3600;
            int minutes = secs / 60;

            QString result;
            if (days > 0) result += QString::number(days) + " dni ";
            if (hours > 0) result += QString::number(hours) + " godz. ";
            if (minutes > 0 || result.isEmpty()) result += QString::number(minutes) + " min";

            return result.trimmed();
        }
        default: return {};
        }
    }

    if (role == Qt::BackgroundRole) {
        QString priority = task.getPriority();
        if (priority == "Średni") return QBrush(QColor(125, 125, 0));
        else if (priority == "Wysoki") return QBrush(QColor(125, 0, 0));
    }

    return {};
}

QVariant TaskModel::headerData(int section, Qt::Orientation orientation, int role) const {
    if (role != Qt::DisplayRole || orientation != Qt::Horizontal) return {};
    switch (section) {
    case 0: return "Nazwa";
    case 1: return "Opis";
    case 2: return "Status";
    case 3: return "Pozostały czas";
    default: return {};
    }
}

Qt::ItemFlags TaskModel::flags(const QModelIndex& index) const {
    if (!index.isValid()) return Qt::NoItemFlags;
    return Qt::ItemIsSelectable | Qt::ItemIsEnabled;
}

bool TaskModel::setData(const QModelIndex& index, const QVariant& value, int role) {
    if (!index.isValid() || role != Qt::EditRole) return false;

    Task& task = m_filteredTasks[index.row()];
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

void TaskModel::setTasks(const QVector<Task>& allTasks, const QString& filterStatus) {
    beginResetModel();
    m_filteredTasks.clear();
    m_originalIndices.clear();
    for (int i = 0; i < allTasks.size(); ++i) {
        const Task& task = allTasks[i];
        if ((filterStatus == "zrobione" && task.getStatus() == "zrobione") ||
            (filterStatus != "zrobione" && task.getStatus() != "zrobione")) {
            m_filteredTasks.append(task);
            m_originalIndices.append(i);
        }
    }
    endResetModel();
}

void TaskModel::clear() {
    beginResetModel();
    m_filteredTasks.clear();
    m_originalIndices.clear();
    endResetModel();
}

int TaskModel::getOriginalIndex(int row) const {
    if (row < 0 || row >= m_originalIndices.size()) return -1;
    return m_originalIndices[row];
}
