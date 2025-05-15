#ifndef TASKMODEL_H
#define TASKMODEL_H

#include <QAbstractTableModel>
#include "taskmanager.h"
#include "BusinessLogic_global.h"

class BUSINESSLOGIC_EXPORT TaskModel : public QAbstractTableModel {
    Q_OBJECT

public:
    explicit TaskModel(TaskManager* manager, QObject* parent = nullptr);

    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    int columnCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
    Qt::ItemFlags flags(const QModelIndex& index) const override;
    bool setData(const QModelIndex& index, const QVariant& value, int role = Qt::EditRole) override;

    void addTask(const Task& task);
    void removeTask(int row);

private:
    TaskManager* m_manager;
};

#endif // TASKMODEL_H
