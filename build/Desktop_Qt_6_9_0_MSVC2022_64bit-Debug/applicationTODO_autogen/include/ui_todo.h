/********************************************************************************
** Form generated from reading UI file 'todo.ui'
**
** Created by: Qt User Interface Compiler version 6.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TODO_H
#define UI_TODO_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TODO
{
public:
    QWidget *centralwidget;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *TODO)
    {
        if (TODO->objectName().isEmpty())
            TODO->setObjectName("TODO");
        TODO->resize(800, 600);
        centralwidget = new QWidget(TODO);
        centralwidget->setObjectName("centralwidget");
        TODO->setCentralWidget(centralwidget);
        menubar = new QMenuBar(TODO);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 21));
        TODO->setMenuBar(menubar);
        statusbar = new QStatusBar(TODO);
        statusbar->setObjectName("statusbar");
        TODO->setStatusBar(statusbar);

        retranslateUi(TODO);

        QMetaObject::connectSlotsByName(TODO);
    } // setupUi

    void retranslateUi(QMainWindow *TODO)
    {
        TODO->setWindowTitle(QCoreApplication::translate("TODO", "TODO", nullptr));
    } // retranslateUi

};

namespace Ui {
    class TODO: public Ui_TODO {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TODO_H
