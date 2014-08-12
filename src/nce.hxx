#ifndef NCE_HXX
#define NCE_HXX

#include <QObject>
#include <QFile>
class Nce : public QObject
{
    Q_OBJECT
public:
    explicit Nce(QObject *parent = 0);
    bool parseFile(const QString& nce, int _class);
protected:
    QFile file_;

signals:

public slots:

};

#endif // NCE_HXX
