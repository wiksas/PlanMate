#ifndef TODO_H
#define TODO_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class TODO;
}
QT_END_NAMESPACE

class TODO : public QMainWindow
{
    Q_OBJECT

public:
    TODO(QWidget *parent = nullptr);
    ~TODO();

private:
    Ui::TODO *ui;
};
#endif // TODO_H
