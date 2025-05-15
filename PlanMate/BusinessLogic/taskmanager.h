#ifndef TASKMANAGER_H
#define TASKMANAGER_H

#include <QObject>
#include <QVector>
#include "task.h"
#include "BusinessLogic_global.h"

class BUSINESSLOGIC_EXPORT TaskManager : public QObject {
    Q_OBJECT

public:
    explicit TaskManager(QObject* parent = nullptr);

    void addTask(const Task& task);
    void removeTask(int index);
    Task& getTask(int index);
    const QVector<Task>& getTasks() const;
    int taskCount() const;

private:
    QVector<Task> m_tasks;
};

#endif // TASKMANAGER_H
