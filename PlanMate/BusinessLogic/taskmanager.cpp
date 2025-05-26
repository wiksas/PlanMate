#include "taskmanager.h"

TaskManager::TaskManager(QObject* parent)
    : QObject(parent) {}

void TaskManager::addTask(const Task& task) {
    m_tasks.append(task);
}

void TaskManager::removeTask(int index) {
    if (index >= 0 && index < m_tasks.size()) {
        m_tasks.removeAt(index);
    }
}

Task& TaskManager::getTask(int index) {
    return m_tasks[index];
}

const QVector<Task>& TaskManager::getTasks() const {
    return m_tasks;
}

int TaskManager::taskCount() const {
    return m_tasks.size();
}
