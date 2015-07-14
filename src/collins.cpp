#include "collins.h"

#include <QFile>
#include <QStringList>
Collins::Collins(QObject *parent) : QObject(parent)
{
    QString zh_path = "D:/work/mdx/GetDict_veryhuo.com/collins_mdx_source";
    QString en_path = "D:/work/mdx/GetDict_veryhuo.com/collins_english_mdx_source";

    readCollins(zh_path,CollinsZH);
    readCollins(en_path,CollinsEN);


}

CollinsWordInfo Collins::wordInfo(const QString &word)
{
    return enwordInfo_[word];
}

void Collins::readCollins(const QString &filePath,DictType type)
{
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly)) {

        return;
    }

    QStringList info;
    QString line;
    QMap<QString, QStringList> temp; // save temp info
    do {
        line = file.readLine();
        line = line.trimmed();
        if (line == "</>") {
            temp.insert(info.first(),info);
            info.clear();
        } else {
            info << line;
        }
    } while (!file.atEnd());

    QMap<QString, QStringList>::iterator it = temp.begin();
    QMap<QString, QStringList>::iterator iE = temp.end();
    for (; it != iE; ++it) {
        QString word = it.key();
        QStringList text = it.value();
        text.removeFirst();
        QString html = text.join("\n");
        CollinsWordInfo wordinfo;
        wordinfo.word = word;
        wordinfo.html = html;
        if (type == CollinsZH)
            zhwordInfo_.insert(word,wordinfo);
        else if (type == CollinsEN)
            enwordInfo_.insert(word,wordinfo);


    }
}

