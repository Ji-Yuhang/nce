#ifndef NCE_HXX
#define NCE_HXX

#include <QObject>
#include <QFile>
#include "data.hxx"
#include <QNetworkAccessManager>
class Nce : public QObject
{
    Q_OBJECT
public:
    explicit Nce(QObject *parent = 0);
    bool parseFile(const QString& nce, int _class);
    bool parseWord();
    bool replaceFile(const QString& nce, int _class);
public:
    QFile file_;
    OldData data_;
    QNetworkAccessManager netManager_;

signals:

public slots:

};

#endif // NCE_HXX
