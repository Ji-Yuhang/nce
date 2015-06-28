#include "dictwidget.hxx"
#include "ui_dictwidget.h"
#include "shanbay.hxx"
DictWidget::DictWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DictWidget)
{
    ui->setupUi(this);
}

DictWidget::~DictWidget()
{
    delete ui;
}

void DictWidget::on_pushButton_clicked()
{
//    shab
    QString text = ui->lineEdit->text();
    SHANBAY->asyncGetWord(text);


}
