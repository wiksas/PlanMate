#include "task.h"

Task::Task(const QString& title, const QString& description, const QString& status, const QDateTime& deadline, const QString& priority)
    : m_title(title), m_description(description), m_status(status), m_deadline(deadline), m_priority(priority) {}


QString Task::getTitle() const { return m_title; }
QString Task::getDescription() const { return m_description; }
QString Task::getStatus() const { return m_status; }
QDateTime Task::getDeadline() const { return m_deadline; }
QString Task::getPriority() const { return m_priority; }
bool Task::isCompleted() const { return m_completed; }
QDateTime Task::getCreatedAt() const { return m_createdAt; }


void Task::setTitle(const QString& title) { m_title = title; }
void Task::setDescription(const QString& description) { m_description = description; }
void Task::setStatus(const QString& status) {m_status = status; }
void Task::setDeadline(const QDateTime& deadline) {m_deadline = deadline; }
void Task::setPriority(const QString& priority) { m_priority = priority; }
void Task::setCompleted(bool completed) { m_completed = completed; }
