#include "mainwindow.hxx"
#include <map>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    ui.setupUi(this);
    connect(ui.tableWidget, SIGNAL(cellClicked(int,int)), this, SLOT(showInfo(int,int)));
    connect(ui.read, SIGNAL(triggered()),this,SLOT(showRead()));
}

void MainWindow::init()
{
    typedef QMultiMap<QString, WordInfo> WordList;
    QStringList list;
    typedef QMap<QString,int> ValueMap;
    ValueMap vm;
    WordList& wl = nce.data_.wordList_;
    WordList::iterator it = wl.begin(), iE = wl.end();
    for (; it != iE; ++it) {
        QString w = it.key();
        ValueMap::iterator vit =  vm.find(w);
        if (vit != vm.end())
            vit.value()++;
        else
            vm.insert(w,0);
    }
    typedef std::multimap<int, QString> MapValue;
    MapValue mv;
    ValueMap::iterator vit = vm.begin(), viE = vm.end();
    for (; vit != viE; ++vit) {
        int value = vit.value();
        mv.insert(std::make_pair(value, vit.key()));
    }
    int _vmSize = vm.size();
    ui.tableWidget->setRowCount(_vmSize);
    int row = 0;
    MapValue::reverse_iterator mmit = mv.rbegin(), mmie = mv.rend();
    for (; mmit != mmie; ++mmit) {
        QTableWidgetItem * item0 = new QTableWidgetItem;
        item0->setText(QString::number(mmit->first));
        ui.tableWidget->setItem(row, 0, item0);

        QTableWidgetItem * item1 = new QTableWidgetItem;
        item1->setText(mmit->second);
        ui.tableWidget->setItem(row, 1, item1);

        ++row;
    }
    ui.tableWidget->resizeColumnsToContents();
    ui.tableWidget->setColumnWidth(1,150);

    classInfo_.init();
}

void MainWindow::showInfo(int row,int col)
{
    QString word = ui.tableWidget->item(row,1)->text();
    WordList::iterator it =  nce.data_.wordList_.find(word);
    if (it == nce.data_.wordList_.end())
        return;
    WordInfo info = it.value();
    QString text;
    text += info.index.nce + " " + QString::number(info.index.class_) + ":\n";
    foreach (QString s, info.sentences) {
        text += "\t"+s +"\n";
    }
    ui.plainTextEdit->setPlainText(text);
}

void MainWindow::showRead()
{
    classInfo_.showNormal();
}
