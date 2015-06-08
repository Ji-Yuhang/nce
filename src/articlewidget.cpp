#include "articlewidget.h"
#include "ui_articlewidget.h"
#include "article.hxx"
#include <QTableWidgetItem>
#include <QDebug>
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
    QStringList words = currentArticle_->allWord();
    QStringList unknownList = currentArticle_->unKnownWordList();

    QTableWidget* table = ui->unknownList;
    table->clearContents();
    while (table->rowCount()) table->removeRow(0);
    wordstatusItemMap_.clear();
    table->setRowCount(unknownList.size());
    int row = 0;
    Q_FOREACH(QString word, unknownList) {

        table->setItem(row,0,new QTableWidgetItem(word));
        QTableWidgetItem* statusItem = new QTableWidgetItem("unknown");
        table->setItem(row,1,statusItem);

        QPushButton* knwonButton = new QPushButton;
        table->setCellWidget(row,2,knwonButton);
        knwonButton->setProperty("word", QVariant::fromValue(word));
        connect(knwonButton, SIGNAL(clicked()), this, SLOT(onKnowButtonClicked()));

        QPushButton* unKnwonButton = new QPushButton;
        table->setCellWidget(row,3,unKnwonButton);
        unKnwonButton->setProperty("word", QVariant::fromValue(word));
        connect(unKnwonButton, SIGNAL(clicked()), this, SLOT(onUnknowButtonClicked()));

        wordstatusItemMap_.insert(word,statusItem);
        row++;

    }
}

void ArticleWidget::onKnowButtonClicked()
{
    qDebug() << "onKnowButtonClicked";
    QPushButton* button = qobject_cast<QPushButton*>(sender());
    if (!button) return;

    QString word  = button->property("word").toString();
    setWordStatus(word,1);
}

void ArticleWidget::onUnknowButtonClicked()
{
    qDebug() << "onUnknowButtonClicked";

    QPushButton* button = qobject_cast<QPushButton*>(sender());
    if (!button) return;
    QString word  = button->property("word").toString();
    setWordStatus(word,0);
}

void ArticleWidget::setWordStatus(const QString &word, int status)
{
    qDebug() << "setWordStatus "<<word<<" "<<status;

    QMap<QString, QTableWidgetItem*>::iterator it = wordstatusItemMap_.find(word);
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
    QStringList unknownList = currentArticle_->unKnownWordList();

    Q_FOREACH(QString word, unknownList) {
        setWordStatus(word,1);
    }
}

void ArticleWidget::on_allUnknown_clicked()
{
    QStringList unknownList = currentArticle_->unKnownWordList();

    Q_FOREACH(QString word, unknownList) {
        setWordStatus(word,0);
    }
}

void ArticleWidget::on_allAnti_clicked()
{

}

void ArticleWidget::on_preview_clicked()
{

}

void ArticleWidget::on_saveWordStatus_clicked()
{

}
