#include "planmate.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    PlanMate w;
    w.show();
    return a.exec();
}
