#include "dictwidget.hxx"
#include "ui_dictwidget.h"
#include "shanbay.hxx"
#include "data.hxx"
#include "database.hxx"
#include <QScrollBar>
#include <QDebug>
DictWidget::DictWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DictWidget)
{
    ui->setupUi(this);
    connect(ui->listWidget, SIGNAL(itemActivated(QListWidgetItem*)), this, SLOT(on_item_actived(QListWidgetItem*)));
}

DictWidget::~DictWidget()
{
    delete ui;
}

void DictWidget::on_pushButton_clicked()
{
//    shab
    ui->listWidget->clear();
    QString text = ui->lineEdit->text();
    SHANBAY->asyncGetWord(text);
    QList<Data::BookData>& datas = DB->bookData();
    Q_FOREACH (Data::BookData data, datas) {
        Data::Word word = data.word(text);
        Q_FOREACH(int sen_id, word.sentence_id_list) {
            Data::Sentence sentence = data.sentence(sen_id);
            QListWidgetItem* item = new QListWidgetItem;
            QString itemtext = sentence.sentence;
//            itemtext.replace(text, "<font color=\"red\">"+text+"</font>");
            item->setText(itemtext);
            item->setToolTip(word.word);
            Data::Article article = data.article(sentence.article_id);
            item->setData(100,article.content);
            ui->listWidget->addItem(item);
        }
    }
    if (ui->listWidget->count() == 1) on_item_actived(ui->listWidget->item(0));



}

void DictWidget::on_item_actived(QListWidgetItem *item)
{
    QString text = item->toolTip();
    text.insert(0," ");
    QString sentence = item->text();
    QString article = item->data(100).toString();

    int index = article.indexOf(sentence);
    int size = sentence.size();
    int total = article.size();
    article.insert(0,"<html><head><style type=\"text/css\">body{line-height:100%;word-spacing: 3px; font-family:Georgia,Times,\"Times New Roman\",Arial,serif ;font-size:12px;}</style></head><body>");
    article = article.replace(sentence," <sentence style=\"color:black;background:yellow;text-decoration:underline;font-style:italic;\">"+sentence+"</sentence>",Qt::CaseInsensitive);

    article = article.replace(text, "<word style=\"color:red;font-weight:bold;text-decoration:underline;\">"+text+"</word>",Qt::CaseInsensitive);

    article.append("</body></html>");

    qDebug()<<text<<endl<< sentence<<endl<<article;

    ui->article->setHtml(article);
    int max = ui->article->verticalScrollBar()->maximum();
//    int max = ui->article->verticalScrollBar()->maximum();

    // x / max = (index + size/2) / total
    int value = qRound (1.0 * max *(index+size/2.0) / total);
    if (total - index - size < size / 2.0 ) value = max;
    if (index < size ) value = 0;

//    qFuzzyCompare()
    ui->article->verticalScrollBar()->setValue(value);
}
