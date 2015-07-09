#include "classinfo.hxx"
#include "data.hxx"
#include <QSqlError>
#include <QDebug>
#include <QSqlRecord>
ClassInfo::ClassInfo(QWidget *parent) :
    QWidget(parent),
    m_knownWord(0)
{
    ui.setupUi(this);
    connect (ui.comboBox, SIGNAL(currentIndexChanged(QString)),this, SLOT(changeList(QString)));
    connect(ui.listWidget, SIGNAL(currentRowChanged(int)),this,SLOT(changeClass(int)));
    connect(ui.pushButton_list, SIGNAL(clicked()),this,SLOT(showList()));
    connect(ui.pushButton_word, SIGNAL(clicked()),this,SLOT(showWord()));
    m_db = QSqlDatabase::addDatabase("QSQLITE");

    m_db.setDatabaseName("nce3.db");
    bool s = m_db.open();
    if (!s) {
        qDebug() << "anki_study open ERROR";
        QSqlError error = m_db.lastError();
        qDebug() << error.text();
    }

}

void ClassInfo::init()
{
    OldData* data = OldData::instance();
    ClassContent& cc = data->classContent_;
    QList<ClassIndex> list = cc.keys();

    foreach (ClassIndex index, list) {
        QString name = index.nce;
        int _class = index.class_;
        nceMap.insert(name, _class);
    }
    QStringList keys = nceMap.uniqueKeys();
    ui.comboBox->addItems(keys);

}

void ClassInfo::changeList(QString key)
{
    ui.listWidget->clear();
    QList<int> classList = nceMap.values(key);
    foreach (int i, classList) {
        QListWidgetItem * item = new QListWidgetItem;
        item->setText(QString::number(i));
        item->setData(32,key);
        item->setData(33,i);
        ui.listWidget->addItem(item);
    }

}

void ClassInfo::changeClass(int row)
{
    m_knownWord = 0;
    m_unknown.clear();
    QListWidgetItem * item =ui.listWidget->item(row);
    if (!item) return;
    QString nce = item->data(32).toString();
    int _class = item->data(33).toInt();
    ClassIndex index;
    index.nce = nce;
    index.class_ = _class;

    QString text;
    ClassContent& cc = OldData::instance()->classContent_;
    ClassContent::iterator it = cc.begin(), ie = cc.end();
    for (; it != ie; ++it) {
        ClassIndex _index = it.key();
        if (_index == index){
            text = it.value();
        }
    }

    QString _text = cc[index];
    ui.textEdit->setPlainText(text);

    ClassMap& cm = OldData::instance()->classMap_;
    ClassMap::iterator cit = cm.begin(), cie = cm.end();
    for (; cit != cie; ++cit) {
        ClassIndex _index = cit.key();
        if (_index == index){
            WordMap& wm = cit.value();
            ui.tableWidget->clear();
            ui.tableWidget->setRowCount(wm.size());
            ui.tableWidget->setColumnCount(2);
            WordMap::iterator vit = wm.begin(), viE = wm.end();
            for (; vit != viE; ++vit) {
                QTableWidgetItem * item0 = new QTableWidgetItem;
                item0->setText(QString(vit.key().word));
                ui.tableWidget->setItem(row, 0, item0);

                QTableWidgetItem * item1 = new QTableWidgetItem;
                item1->setText(vit.value().sentences.join(" "));
                ui.tableWidget->setItem(row, 1, item1);

                parseWord( vit.key().word);
                ++row;
            }
        }
    }

}

void ClassInfo::showList()
{
    ui.listWidget->setVisible(!ui.listWidget->isVisible());
    ui.comboBox->setVisible(!ui.comboBox->isVisible());
}

void ClassInfo::showWord()
{
    ui.tableWidget->setVisible(!ui.tableWidget->isVisible());

}

void ClassInfo::parseWord(const QString &word)
{

    QSqlQuery query(m_db);
    QString sql = QString("select word_id from known_word where word='%1'").arg(word);
    if (query.exec(sql)) {
        if (query.next()) {
            QSqlRecord record = query.record();
            int id = record.value("word_id").toInt();
            if (id != 0 )
                m_knownWord++;
        } else {
            if (!m_unknown.contains(word))
                m_unknown.append(word);
        }


    } else {
        QSqlError error = m_db.lastError();
        qDebug() << " known_word sql error: " << sql <<error.text();
    }
    ui.status->setText("known word : " + QString::number(m_knownWord) + "   unknown: " + QString::number(m_unknown.size()));
}

void ClassInfo::on_save_clicked()
{
    qDebug() << "save clicked";
    foreach (QString word, m_unknown) {
        QString zh = word;
        QString sentence = word;
        QString acticle = word;
        int acquainted = 0;
        int repeat = 0;

//        getWord(word);


        QSqlQuery query(m_db);
        QString sql = QString("insert into known_word (word, zh, sentence, acticle, acquainted, repeats) value('%1','%2','%3','%4',%5,%6)")
                .arg(word).arg(zh).arg(sentence).arg(acticle).arg(acquainted).arg(repeat);
        if (query.exec(sql)) {

        } else {
            QSqlError error = m_db.lastError();
            qDebug() << " word insert into known_word sql error: " << sql <<error.text();
        }

    }
}
