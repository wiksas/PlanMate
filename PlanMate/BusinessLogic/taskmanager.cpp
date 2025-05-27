#include "taskmanager.h"
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QFile>


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

bool TaskManager::saveTasksToFile(const QString& filePath)
{
    QJsonArray taskArray;
    for (const Task& task : m_tasks) {
        QJsonObject taskObject;
        taskObject["tytul"] = task.getTitle();
        taskObject["opis"] = task.getDescription();
        taskObject["status"] = task.getStatus();
        taskObject["deadline"] = task.getDeadline().toString(Qt::ISODate);
        taskObject["priorytet"] = task.getPriority();
        taskArray.append(taskObject);
    }

    QJsonDocument doc(taskArray);
    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qWarning() << "Nie można otworzyć pliku do zapisu:" << file.errorString();
        return false;
    }

    file.write(doc.toJson());
    file.close();
    return true;
}

bool TaskManager::loadTasksFromFile(const QString& filePath)
{
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning() << "Nie można otworzyć pliku do wczytania:" << file.errorString();
        return false;
    }

    QByteArray jsonData = file.readAll();
    file.close();

    QJsonDocument doc = QJsonDocument::fromJson(jsonData);
    if (!doc.isArray()) {
        qWarning() << "Nieprawidłowy format JSON";
        return false;
    }

    m_tasks.clear();
    QJsonArray taskArray = doc.array();
    for (const QJsonValue& value : taskArray) {
        if (value.isObject()) {
            QJsonObject taskObject = value.toObject();
            QString tytul = taskObject["tytul"].toString();
            QString opis = taskObject["opis"].toString();
            QString status = taskObject["status"].toString();
            QDateTime deadline = QDateTime::fromString(taskObject["deadline"].toString(), Qt::ISODate);
            QString priorytet = taskObject["priorytet"].toString();

            m_tasks.append(Task(tytul, opis, status, deadline, priorytet));
        }
    }
    return true;
}
