#include "data.hxx"
OldData* OldData::g_data = 0;
OldData::OldData(QObject *parent) :
    QObject(parent)
{
    g_data =this;
}

OldData *OldData::instance()
{
    return g_data;
}


Data::Article Data::BookData::article(int article_id)
{
    return articles.value(article_id);
}

Data::Sentence Data::BookData::sentence(int sentence_id)
{
    return sentences.value(sentence_id);

}

Data::Word Data::BookData::word(int word_id)
{
    return words.value(word_id);
}

Data::Word Data::BookData::word(const QString &word_content)
{
    QMap<int,Data::Word>::iterator it = words.begin();
    QMap<int,Data::Word>::iterator itE = words.end();
    for (; it != itE; ++it) {
        if (it.value().word == word_content) return it.value();
    }
    return Word();
}
