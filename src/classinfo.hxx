#ifndef CLASSINFO_HXX
#define CLASSINFO_HXX

#include <QWidget>
#include "ui_classinfo.h"
typedef QMultiMap<QString,int> NceMap;

class ClassInfo : public QWidget
{
    Q_OBJECT
public:
    explicit ClassInfo(QWidget *parent = 0);
    void init();
    NceMap nceMap;
signals:

public slots:
    void changeList(QString key);
    void changeClass(int row);
    void showList();
    void showWord();
private:
    Ui::ClassUi ui;

};

#endif // CLASSINFO_HXX
