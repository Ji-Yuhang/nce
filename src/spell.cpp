#include "spell.h"

Spell* Spell::g_spell_ = 0;
Spell::Spell(QObject *parent) : QObject(parent),
    sp_("en_US.aff","en_US.dic")
{
    g_spell_ = this;

}


bool Spell::spell(const QString &word)
{
    int rs = sp_.spell(word.toUtf8().data());
    return (rs == 1);
}

QString Spell::removeNSandVS(const QString &word)
{
    QStringList ans = analyze(word);
    Q_FOREACH(QString an, ans) {
      if (an.contains(" is:Vs") || an.contains(" is:Ns")) {
          return stem(word).first();
      }
    }
    return word;

}

QStringList Spell::stem(const QString &word)
{
    int max = 40;
    QStringList result;
    {
        char*** anr = new char**[max];
        for (int i = 0;i<max;++i) {
            anr[i] = new char*[max];
            for (int j = 0; j<max;++j) {
                anr[i][j] = new char[max];
            }
        }
        int ra = sp_.stem(anr,word.toUtf8().data());
//        qDebug()<< "stem : "<<ra<<endl;
        int num = 0;

        if (anr == 0) exit(1);

        for (int i = 0; i < max;++i) {
            char** temp = anr[i];
            if (temp == 0 ) continue;
            for (int j = 0; j < max;++j) {
                char* str = temp[j];
                if (str != 0 && num < ra && strlen(str) > 0) {
                    QString s = str;
                    result << s;

//                    qDebug()<< s;
                    num++;

                }
            }
        }
    }
    return result;
}

QStringList Spell::analyze(const QString &word)
{
    int max = 40;
    QStringList result;

    {
        char*** anr = new char**[max];
        for (int i = 0;i<max;++i) {
            anr[i] = new char*[max];
            for (int j = 0; j<max;++j) {
                anr[i][j] = new char[max];
            }
        }

        int ra = sp_.analyze(anr,word.toUtf8().data());
//        qDebug()<< "analyze : "<<ra<<endl;
        int num = 0;

        if (anr == 0) exit(1);
        for (int i = 0; i < max;++i) {
            char** temp = anr[i];
            if (temp == 0 ) continue;
            for (int j = 0; j < max&& num < ra;++j) {
                char* str = temp[j];
                if (str != 0 && strlen(str) > 0) {
                    QString s = str;
                    result << s;
//                    qDebug()<< s;
                    num++;
                }
            }
        }
    }
    return result;
}

QStringList Spell::suggest(const QString &word)
{
    int max = 40;
    QStringList result;

    {
        char*** anr = new char**[max];
        for (int i = 0;i<max;++i) {
            anr[i] = new char*[max];
            for (int j = 0; j<max;++j) {
                anr[i][j] = new char[max];
            }
        }

        int ra = sp_.suggest(anr,word.toUtf8().data());
//        qDebug()<< "suggest : "<<ra<<endl;
        int num = 0;

        if (anr == 0) exit(1);
        for (int i = 0; i < max;++i) {
            char** temp = anr[i];
            if (temp == 0 ) continue;
            for (int j = 0; j < max&& num < ra;++j) {
                char* str = temp[j];
                if (str != 0 && strlen(str) > 0) {
                    QString s = str;
                    result << s;
//                    qDebug()<< s;
                    num++;
                }
            }
        }
    }
    return result;
}
