#ifndef STATICWIDGET_H
#define STATICWIDGET_H

#include <QWidget>

namespace Ui {
class StaticWidget;
}

class StaticWidget : public QWidget
{
    Q_OBJECT

public:
    explicit StaticWidget(QWidget *parent = 0);
    ~StaticWidget();
    void setStaticValue(int known, int unknown, int notSigned, int neverRead);

private:
    Ui::StaticWidget *ui;
};

#endif // STATICWIDGET_H
