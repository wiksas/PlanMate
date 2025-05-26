#ifndef TASK_H
#define TASK_H

#include <QString>
#include <QDateTime>
#include "BusinessLogic_global.h"

class BUSINESSLOGIC_EXPORT Task {
public:
    Task(const QString& title = "", const QString& description = "", const QString& status = "", const QDateTime& deadline = QDateTime::currentDateTime(), const QString& priority = "");

    QString getTitle() const;
    QString getDescription() const;
    QString getStatus() const;
    QDateTime getDeadline() const;
    QString getPriority() const;
    bool isCompleted() const;
    QDateTime getCreatedAt() const;

    void setTitle(const QString& title);
    void setDescription(const QString& description);
    void setStatus(const QString& status);
    void setDeadline(const QDateTime& deadline);
    void setPriority(const QString& priority);
    void setCompleted(bool completed);

private:
    QString m_title;
    QString m_description;
    QString m_status;
    QDateTime m_deadline;
    QString m_priority;
    bool m_completed;
    QDateTime m_createdAt;
};

#endif // TASK_H
