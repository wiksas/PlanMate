#include "task.h"
//Klasa pojedynczego taska; do zrobienia deadline_date, priorytet
Task::Task(const QString& title, const QString& description, bool completed)
    : m_title(title), m_description(description), m_completed(completed), m_createdAt(QDateTime::currentDateTime()) {}

//gettery
QString Task::getTitle() const { return m_title; }
QString Task::getDescription() const { return m_description; }
bool Task::isCompleted() const { return m_completed; }
QDateTime Task::getCreatedAt() const { return m_createdAt; }

//settery
void Task::setTitle(const QString& title) { m_title = title; }
void Task::setDescription(const QString& description) { m_description = description; }
void Task::setCompleted(bool completed) { m_completed = completed; }
