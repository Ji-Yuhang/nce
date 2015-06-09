#include "unknownwordlistwidget.hxx"
#include "ui_unknownwordlistwidget.h"
#include "database.hxx"
UnknownWordListWidget::UnknownWordListWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UnknownWordListWidget)
{
    ui->setupUi(this);
}

UnknownWordListWidget::~UnknownWordListWidget()
{
    delete ui;
}

void UnknownWordListWidget::getUnknownWord()
{
    ui->wordlist->clear();
    QList<WordInfo> allUnknown = DB->getAllUnknown();
    Q_FOREACH(WordInfo info, allUnknown) {
        QListWidgetItem* item = new QListWidgetItem;
        item->setText(info.word);
        item->setData(100, info.word_id);
        ui->wordlist->addItem(item);
    }
}

void UnknownWordListWidget::on_update_clicked()
{
    getUnknownWord();
    this->update();
}
