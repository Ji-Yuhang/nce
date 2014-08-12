#include "classinfo.hxx"
#include "data.hxx"
ClassInfo::ClassInfo(QWidget *parent) :
    QWidget(parent)
{
    ui.setupUi(this);
    connect (ui.comboBox, SIGNAL(currentIndexChanged(QString)),this, SLOT(changeList(QString)));
    connect(ui.listWidget, SIGNAL(currentRowChanged(int)),this,SLOT(changeClass(int)));
    connect(ui.pushButton_list, SIGNAL(clicked()),this,SLOT(showList()));
    connect(ui.pushButton_word, SIGNAL(clicked()),this,SLOT(showWord()));
}

void ClassInfo::init()
{
    Data* data = Data::instance();
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
    QListWidgetItem * item =ui.listWidget->item(row);
    if (!item) return;
    QString nce = item->data(32).toString();
    int _class = item->data(33).toInt();
    ClassIndex index;
    index.nce = nce;
    index.class_ = _class;

    QString text;
    ClassContent& cc = Data::instance()->classContent_;
    ClassContent::iterator it = cc.begin(), ie = cc.end();
    for (; it != ie; ++it) {
        ClassIndex _index = it.key();
        if (_index == index){
            text = it.value();
        }
    }

    QString _text = cc[index];
    ui.textEdit->setPlainText(text);

    ClassMap& cm = Data::instance()->classMap_;
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
