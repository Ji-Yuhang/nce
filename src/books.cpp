#include "books.hxx"

#include <QLabel>
#include <QPushButton>

Books::Books(QWidget *parent) :
    QWidget(parent)
{
    ui.setupUi(this);
    addBook("NCE1");
    addBook("NCE2");
    addBook("NCE3");
    addBook("NCE4");
    addBook("神探狄仁杰");
    addBook("降龙十八掌");
}

void Books::addBook(const QString &path)
{
    QString bookName = path;
    BookLabel * label = new BookLabel;
    label->setAlignment(Qt::AlignCenter);
    label->setText(bookName);
    QString style = "background-color: green";
    label->setStyleSheet(style);
    label->setMinimumSize(100, 100);
    connect(label, SIGNAL(mouseDoubleClicked()), this, SLOT(openBook()));
    ui.scrollAreaWidgetContents->layout()->addWidget(label);

}

void Books::openBook()
{
    BookLabel* label = dynamic_cast<BookLabel*>(sender());
    if (!label) return;
    QString bookName = label->text();
    QWidget * w = new QWidget;
    w->setAttribute(Qt::WA_DeleteOnClose);
    w->show();

}

