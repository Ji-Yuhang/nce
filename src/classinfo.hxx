#ifndef CLASSINFO_HXX
#define CLASSINFO_HXX

#include <QWidget>
#include "ui_classinfo.h"
typedef QMultiMap<QString,int> NceMap;
#include <QSqlDatabase>
#include <QSqlQuery>
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
    void parseWord(const QString& word);
private slots:
    void on_save_clicked();

private:
    QSqlDatabase m_db;
    Ui::ClassUi ui;
    int m_knownWord;
    QStringList m_unknown;

};

#endif // CLASSINFO_HXX
