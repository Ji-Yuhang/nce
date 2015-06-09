#include "articlewidget.h"
#include "ui_articlewidget.h"
#include "article.hxx"
#include <QTableWidgetItem>
#include <QDebug>
#include "database.hxx"
#include <assert.h>
ArticleWidget::ArticleWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ArticleWidget),
    currentArticle_(0)
{
    ui->setupUi(this);
}

ArticleWidget::~ArticleWidget()
{
    delete ui;
    delete currentArticle_;
}

void ArticleWidget::on_save_clicked()
{

}

void ArticleWidget::on_parse_clicked()
{
    if (!currentArticle_) currentArticle_ = new Article;
    QString text = ui->textEdit->toPlainText();
    currentArticle_->parseArticle(text);
    QList<WordInfo> allword = currentArticle_->allWordInfoList();
    QList<WordInfo> unknownList = currentArticle_->unknownWordInfoList();

    {
        int a = allword.size();
        int un = unknownList.size();
        int k = a - un;

        ui->all->setText(QString::number(a));
        ui->known->setText(QString::number(k));
        ui->unknown->setText(QString::number(un));
        ui->ratio->setText(QString::number(double(un* 100.0/a )) + "%");
        ui->unknownratio->setText(QString::number(un) + " / " + QString::number(a));
    }
    QTableWidget* table = ui->unknownList;
    clearTable(table);
    clearTable(ui->previewKnowList);
    clearTable(ui->previewUnknowList);

    wordstatusItemMap_.clear();
    table->setRowCount(unknownList.size());
    int row = 0;
    Q_FOREACH(WordInfo wordinfo, unknownList) {

        table->setItem(row,0,new QTableWidgetItem(wordinfo.word));
        QString known = wordinfo.familiarity > 1 ? "knwon":"unknown";
        QTableWidgetItem* statusItem = new QTableWidgetItem(known);
        table->setItem(row,1,statusItem);

        QPushButton* knwonButton = new QPushButton;
        table->setCellWidget(row,2,knwonButton);
        knwonButton->setProperty("word", QVariant::fromValue(wordinfo.word));
        knwonButton->setProperty("word_id", QVariant::fromValue(wordinfo.word_id));

        connect(knwonButton, SIGNAL(clicked()), this, SLOT(onKnowButtonClicked()));

        QPushButton* unKnwonButton = new QPushButton;
        table->setCellWidget(row,3,unKnwonButton);
        unKnwonButton->setProperty("word", QVariant::fromValue(wordinfo.word));
        unKnwonButton->setProperty("word_id", QVariant::fromValue(wordinfo.word_id));

        connect(unKnwonButton, SIGNAL(clicked()), this, SLOT(onUnknowButtonClicked()));

        wordstatusItemMap_.insert(wordinfo.word_id,statusItem);
        row++;

    }
}

void ArticleWidget::onKnowButtonClicked()
{
    qDebug() << "onKnowButtonClicked";
    QPushButton* button = qobject_cast<QPushButton*>(sender());
    if (!button) return;

    QString word  = button->property("word").toString();
    int word_id  = button->property("word_id").toInt();

    setWordStatus(word_id,1);
}

void ArticleWidget::onUnknowButtonClicked()
{
    qDebug() << "onUnknowButtonClicked";

    QPushButton* button = qobject_cast<QPushButton*>(sender());
    if (!button) return;
    QString word  = button->property("word").toString();
    int word_id  = button->property("word_id").toInt();

    setWordStatus(word_id,0);
}

void ArticleWidget::setWordStatus(int word_id, int status)
{
    WordInfo info = currentArticle_->wordInfo(word_id);
    if (info.word_id <= 0) return;
    qDebug() << "setWordStatus "<<info.word<<" "<<status;

    QMap<int, QTableWidgetItem*>::iterator it = wordstatusItemMap_.find(word_id);
    if (it != wordstatusItemMap_.end()) {
        QTableWidgetItem* item = it.value();
        if (!item) return;
        if (status == 1) {
            item->setText("known");
            item->setBackgroundColor(Qt::green);
        }
        else if (status == 0) {
            item->setText("unknown");
            item->setBackgroundColor(Qt::red);

        }
    }
}

void ArticleWidget::on_allKnown_clicked()
{
    QList<WordInfo> unknownList = currentArticle_->unknownWordInfoList();

    Q_FOREACH(WordInfo wordinfo, unknownList) {
        setWordStatus(wordinfo.word_id,1);
    }
    ui->unknownList->update();
}

void ArticleWidget::on_allUnknown_clicked()
{
    QList<WordInfo> unknownList = currentArticle_->unknownWordInfoList();

    Q_FOREACH(WordInfo wordinfo, unknownList) {
        setWordStatus(wordinfo.word_id,0);
    }
    ui->unknownList->update();
}

void ArticleWidget::on_allAnti_clicked()
{

}

void ArticleWidget::on_preview_clicked()
{
    int knwonsize = 0;
    int unknownsize = 0;
    {
        QMap<int, QTableWidgetItem*>::iterator it = wordstatusItemMap_.begin();
        for (;it != wordstatusItemMap_.end(); ++it) {
            QTableWidgetItem* item = it.value();
            if (item->text() == "known") knwonsize++;
            else if (item->text() == "unknown") unknownsize++;

        }
    }
    QTableWidget* knowntable = ui->previewKnowList;
    clearTable(knowntable);
    knowntable->setRowCount(knwonsize);

    QTableWidget* unknowntable = ui->previewUnknowList;
    clearTable(unknowntable);
    unknowntable->setRowCount(unknownsize);

    int knownRow = 0;
    int unknownRow = 0;
    QMap<int, QTableWidgetItem*>::iterator it = wordstatusItemMap_.begin();
    for (;it != wordstatusItemMap_.end(); ++it) {
        int word_id = it.key();
        WordInfo info = currentArticle_->wordInfo(word_id);
        if (info.word_id <= 0) continue;
        QTableWidgetItem* item = it.value();
        if (!item) continue;
        if (item->text() == "known") {
            knowntable->setItem(knownRow,0,new QTableWidgetItem(info.word));
            QPushButton* unKnwonButton = new QPushButton;
            knowntable->setCellWidget(knownRow,1,unKnwonButton);
            unKnwonButton->setProperty("word", QVariant::fromValue(info.word));
            unKnwonButton->setProperty("word_id", QVariant::fromValue(info.word_id));
            unKnwonButton->setProperty("knownRow", QVariant::fromValue(knownRow));
            connect(unKnwonButton, SIGNAL(clicked()), this, SLOT(onUnknowButtonClicked()));
            connect(unKnwonButton, SIGNAL(clicked()), this, SLOT(onPreviewUnknowButtonClicked()));

            ++knownRow;
        } else if (item->text() == "unknown") {
            unknowntable->setItem(unknownRow,0,new QTableWidgetItem(info.word));
            QPushButton* knwonButton = new QPushButton;
            unknowntable->setCellWidget(unknownRow,1,knwonButton);
            knwonButton->setProperty("word", QVariant::fromValue(info.word));
            knwonButton->setProperty("word_id", QVariant::fromValue(info.word_id));
            knwonButton->setProperty("unknownRow", QVariant::fromValue(unknownRow));
            connect(knwonButton, SIGNAL(clicked()), this, SLOT(onKnowButtonClicked()));
            connect(knwonButton, SIGNAL(clicked()), this, SLOT(onPreviewKnowButtonClicked()));

            ++unknownRow;
        }

    }
}

void ArticleWidget::on_saveWordStatus_clicked()
{
    QMap<int, QTableWidgetItem*>::iterator it = wordstatusItemMap_.begin();
    for (;it != wordstatusItemMap_.end(); ++it) {
        int word_id = it.key();
        WordInfo info = currentArticle_->wordInfo(word_id);
        if (info.word_id <= 0) continue;
        QTableWidgetItem* item = it.value();
        if (!item) continue;
        if (item->text() == "known") {

            DB->setWordFamiliarity(word_id, 1);
            qDebug()<<"set word Familiarity : "<<info.word<<" "<<1;
        } else if (item->text() == "unknown") {
            DB->setWordFamiliarity(word_id, 0);
            qDebug()<<"set word Familiarity : "<<info.word<<" "<<0;

        }
    }
}

void ArticleWidget::onPreviewUnknowButtonClicked()
{
    qDebug() << "onPreviewUnknowButtonClicked";

    QPushButton* button = qobject_cast<QPushButton*>(sender());
    if (!button) return;
    int knownRow  = button->property("knownRow").toInt();
    ui->previewKnowList->removeRow(knownRow);

    int word_id  = button->property("word_id").toInt();
    QTableWidget* knowntable = ui->previewUnknowList;
    int row = knowntable->rowCount();
    knowntable->setRowCount(row + 1);
    WordInfo info = currentArticle_->wordInfo(word_id);
    if (info.word_id <= 0) return;
    knowntable->setItem(row,0,new QTableWidgetItem(info.word));
    QPushButton* unKnwonButton = new QPushButton;
    knowntable->setCellWidget(row,1,unKnwonButton);
    unKnwonButton->setProperty("word", QVariant::fromValue(info.word));
    unKnwonButton->setProperty("word_id", QVariant::fromValue(info.word_id));
    unKnwonButton->setProperty("unknownRow", QVariant::fromValue(row));
    connect(unKnwonButton, SIGNAL(clicked()), this, SLOT(onKnowButtonClicked()));
    connect(unKnwonButton, SIGNAL(clicked()), this, SLOT(onPreviewKnowButtonClicked()));

}

void ArticleWidget::onPreviewKnowButtonClicked()
{
    qDebug() << "onPreviewknowButtonClicked";

    QPushButton* button = qobject_cast<QPushButton*>(sender());
    if (!button) return;
    int unknownRow  = button->property("unknownRow").toInt();
    ui->previewUnknowList->removeRow(unknownRow);

    int word_id  = button->property("word_id").toInt();
    QTableWidget* knowntable = ui->previewKnowList;
    int row = knowntable->rowCount();
    knowntable->setRowCount(row + 1);
    WordInfo info = currentArticle_->wordInfo(word_id);
    if (info.word_id <= 0) return;
    knowntable->setItem(row,0,new QTableWidgetItem(info.word));
    QPushButton* unKnwonButton = new QPushButton;
    knowntable->setCellWidget(row,1,unKnwonButton);
    unKnwonButton->setProperty("word", QVariant::fromValue(info.word));
    unKnwonButton->setProperty("word_id", QVariant::fromValue(info.word_id));
    unKnwonButton->setProperty("knownRow", QVariant::fromValue(row));
    connect(unKnwonButton, SIGNAL(clicked()), this, SLOT(onUnknowButtonClicked()));
    connect(unKnwonButton, SIGNAL(clicked()), this, SLOT(onPreviewUnknowButtonClicked()));
}

void ArticleWidget::clearTable(QTableWidget *table)
{
    assert(table);
    if (!table) return;
    table->clearContents();
    while (table->rowCount()) table->removeRow(0);
}


