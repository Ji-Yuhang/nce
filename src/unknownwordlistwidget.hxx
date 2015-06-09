#ifndef UNKNOWNWORDLISTWIDGET_HXX
#define UNKNOWNWORDLISTWIDGET_HXX

#include <QWidget>

namespace Ui {
class UnknownWordListWidget;
}

class UnknownWordListWidget : public QWidget
{
    Q_OBJECT

public:
    explicit UnknownWordListWidget(QWidget *parent = 0);
    ~UnknownWordListWidget();
public Q_SLOTS:
    void getUnknownWord();

private slots:
    void on_update_clicked();

private:
    Ui::UnknownWordListWidget *ui;
};

#endif // UNKNOWNWORDLISTWIDGET_HXX
