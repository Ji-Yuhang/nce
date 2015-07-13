#include "collins.h"

#include <QFile>
#include <QStringList>
Collins::Collins(QObject *parent) : QObject(parent)
{
    QString path = "D:/work/mdx/GetDict_veryhuo.com/collins_mdx_source";
    readCollins(path);
}

CollinsWordInfo Collins::wordInfo(const QString &word)
{
    return wordInfo_[word];
}

void Collins::readCollins(const QString &filePath)
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
        wordInfo_.insert(word,wordinfo);

    }
}

