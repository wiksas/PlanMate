#ifndef TASK_H
#define TASK_H

#include <QString>
#include <QDateTime>
#include "BusinessLogic_global.h"

class BUSINESSLOGIC_EXPORT Task {
public:
    Task(const QString& title = "", const QString& description = "", bool completed = false);

    //gettery
    QString getTitle() const;
    QString getDescription() const;
    bool isCompleted() const;
    QDateTime getCreatedAt() const;

    //settery
    void setTitle(const QString& title);
    void setDescription(const QString& description);
    void setCompleted(bool completed);

private:
    QString m_title;
    QString m_description;
    bool m_completed;
    QDateTime m_createdAt;
};

#endif // TASK_H
