#include "nce.hxx"
#include <QApplication>
#include <QFileInfo>
#include <QStringList>
#include <QDebug>
Nce::Nce(QObject *parent) :
    QObject(parent)
{
    QStringList nces;
    nces << "nce1" << "nce2" << "nce3"<<"nce4";
    for (int i = 0; i < 4; ++i) {
        QString nce = nces[i];
        for (int j = 1; j < 100; ++j) {
            parseFile(nce, j);
        }
    }
}

bool Nce::parseFile(const QString &nce, int _class)
{
    QString path = qApp->applicationDirPath()+"/nce/";
    path += nce + "/";
    QString classStr = QString::number(_class);
    if (_class < 10) classStr = "0" + QString::number(_class);
    path += classStr;
    QFileInfo fileInfo(path + ".txt");
    if (!fileInfo.exists())
        path += ".TXT";
    else
        path += ".txt";
    file_.setFileName(path);
    if (!file_.open(QIODevice::ReadOnly)) {
        qDebug() << "Read File Error!"+ path;
        return false;
    }
    QString text = file_.readAll();
    QStringList sentenceList = text.split(".");
    int sentenceSize = sentenceList.size();

    //Todo:

    return true;


}
