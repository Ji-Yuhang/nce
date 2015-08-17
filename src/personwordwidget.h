#ifndef PERSONWORDWIDGET_H
#define PERSONWORDWIDGET_H

#include <QWidget>
class StaticWidget;
namespace Ui {
class PersonWordWidget;
}

class PersonWordWidget : public QWidget
{
    Q_OBJECT

public:
    explicit PersonWordWidget(QWidget *parent = 0);
    ~PersonWordWidget();

private:
    Ui::PersonWordWidget *ui;
    StaticWidget* staticWidget_;

};

#endif // PERSONWORDWIDGET_H
