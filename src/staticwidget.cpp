#include "staticwidget.h"
#include "ui_staticwidget.h"
StaticWidget::StaticWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StaticWidget)
{
    ui->setupUi(this);
}

StaticWidget::~StaticWidget()
{
    delete ui;
}

void StaticWidget::setStaticValue(int known, int unknown, int notSigned, int neverRead)
{
    int all = known + unknown + notSigned + neverRead;
    ui->known->setText(QString::number(known));
    ui->unknown->setText(QString::number(unknown));
    ui->notSigned->setText(QString::number(notSigned));
    ui->neverRead->setText(QString::number(neverRead));
    ui->gridLayout->setColumnStretch(0,known);
    ui->gridLayout->setColumnStretch(1,unknown);
    ui->gridLayout->setColumnStretch(2,notSigned);
    ui->gridLayout->setColumnStretch(3,neverRead);
}
