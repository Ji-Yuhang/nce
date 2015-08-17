#include "personwordwidget.h"
#include "ui_personwordwidget.h"
#include "staticwidget.h"
#include "database.hxx"
PersonWordWidget::PersonWordWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PersonWordWidget)
    ,staticWidget_(new StaticWidget)

{
    ui->setupUi(this);
    ui->horizontalLayout->addWidget(staticWidget_);

    QList<WordInfo> unknownwordlist = DB->getAllUnknown();
    QStringList unknownwords;
    Q_FOREACH(WordInfo info, unknownwordlist) {
        unknownwords.append(info.word);
    }
    ui->listWidget_unknown->addItems(unknownwords);

    QList<WordInfo> knownwordlist = DB->getAllKnown();
    QStringList knownwords;
    Q_FOREACH(WordInfo info, knownwordlist) {
        knownwords.append(info.word);
    }
    ui->listWidget_known->addItems(knownwords);
    staticWidget_->setStaticValue(knownwords.size(),unknownwords.size(),280,12580);

}

PersonWordWidget::~PersonWordWidget()
{
    delete ui;
    delete staticWidget_;

}
