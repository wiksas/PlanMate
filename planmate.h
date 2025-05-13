#ifndef PLANMATE_H
#define PLANMATE_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class PlanMate;
}
QT_END_NAMESPACE

class PlanMate : public QMainWindow
{
    Q_OBJECT

public:
    PlanMate(QWidget *parent = nullptr);
    ~PlanMate();

private:
    Ui::PlanMate *ui;
};
#endif // PLANMATE_H
