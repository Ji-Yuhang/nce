#include "mainwindow.hxx"
#include <QFileDialog>
#include <map>
#include <QDebug>
#include <QToolTip>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    ui.setupUi(this);
    importUi.setupUi(&import_);
//    import_.setStyleSheet();
    connect(ui.tableWidget, SIGNAL(cellClicked(int,int)), this, SLOT(showInfo(int,int)));
    connect(ui.read, SIGNAL(triggered()),this,SLOT(showRead()));
    connect(ui.importFile, SIGNAL(triggered()),this,SLOT(import()));
    connect(importUi.indent, SIGNAL(clicked()),this, SLOT(indent()));
    connect(importUi.textEdit, SIGNAL(selectionChanged()),this ,SLOT(selectedWord()));
    connect(&netManager_, SIGNAL(finished(QNetworkReply*)),this, SLOT(readReply(QNetworkReply*)));
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

void MainWindow::import()
{
    path_ = QFileDialog::getOpenFileName();
    if (path_.isEmpty()) return;
    QFile file;
    file.setFileName(path_);
    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << "Read File Error!"+ path_;
        return ;
    }
    QString content = file.readAll();
    file.close();

    importUi.textEdit->setPlainText(content);
    import_.setWindowTitle(path_);
    import_.showNormal();
}


void MainWindow::indent()
{
    QString content = importUi.textEdit->toPlainText();
    content.replace("-\r\n", "");
    content.replace("-\n", "");
    content.replace("\r\n"," ");
    content.replace("\n", " ");
    content.replace("- ", "-");
    content.replace("- ", "-");
    QStringList sentenceList = content.split(QRegExp("[\\.!\\?]"),QString::SkipEmptyParts);
    int i = 0;
    foreach (QString s, sentenceList) {
        s.trimmed();
        QString iStr = QString::number(i);
        s.insert(0, iStr+"    ");
    }
    QString newString = sentenceList.join("\n");
    importUi.textEdit->setPlainText(newString);
    /*
    QFile file;
    file.setFileName(path_);
    if (!file.open(QIODevice::WriteOnly)) {
        qDebug() << "Read File Error!"+ path_;
        return ;
    }
    
    file.write(newString.toLatin1());
    file.close();
    */
}

void MainWindow::selectedWord()
{
    QTextCursor cursor =  importUi.textEdit->textCursor();
    QString text = cursor.selectedText();
    if (text.isEmpty()) return;
    qDebug() << "selected text: "<<text;
    QPoint p = QCursor::pos();
    getWordDescription(text);
    
}

void MainWindow::getWordDescription(const QString &text)
{
    /*
    QString url = QString("https://api.shanbay.com/oauth2/authorize/?client_id=CLIENT_ID&response_type=code&state=123")
    QUrl url();
    netManager_.get(url)
    ;
    */
}

void MainWindow::showDescription()
{
    
}

void MainWindow::readReply(QNetworkReply *)
{
    
}
