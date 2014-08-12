#ifndef NCE_HXX
#define NCE_HXX

#include <QObject>
#include <QFile>
#include "data.hxx"
class Nce : public QObject
{
    Q_OBJECT
public:
    explicit Nce(QObject *parent = 0);
    bool parseFile(const QString& nce, int _class);
    bool parseWord();
public:
    QFile file_;
    Data data_;

signals:

public slots:

};

#endif // NCE_HXX
