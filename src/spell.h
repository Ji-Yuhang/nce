#ifndef SPELL_H
#define SPELL_H

#include <QObject>
#include <QStringList>
#include "hunspell/hunspell.hxx"
class Spell : public QObject
{
    Q_OBJECT
public:
    explicit Spell(QObject *parent = 0);
    static Spell* instance(){return g_spell_;}
    bool spell(const QString& word);
    QString removeNSandVS(const QString& word);
    QStringList stem(const QString& word);
    QStringList analyze(const QString& word);
    QStringList suggest(const QString& word);

signals:

public slots:
private:
    Hunspell sp_;
    static Spell* g_spell_;

};
#define HUNSPELL Spell::instance()

#endif // SPELL_H
