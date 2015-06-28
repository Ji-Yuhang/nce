#ifndef DICTWIDGET_HXX
#define DICTWIDGET_HXX

#include <QWidget>

namespace Ui {
class DictWidget;
}

class DictWidget : public QWidget
{
    Q_OBJECT

public:
    explicit DictWidget(QWidget *parent = 0);
    ~DictWidget();

private slots:
    void on_pushButton_clicked();

private:
    Ui::DictWidget *ui;
};

#endif // DICTWIDGET_HXX
