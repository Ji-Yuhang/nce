#ifndef BOOKS_HXX
#define BOOKS_HXX

#include <QWidget>
#include "ui_books.h"
#include <QLabel>
class BookLabel : public QLabel
{
    Q_OBJECT
public:
    BookLabel () {}
signals:
    void mouseDoubleClicked();
protected:

    void mouseDoubleClickEvent(QMouseEvent* event) {
        emit mouseDoubleClicked();
    }
};
class Books : public QWidget
{
    Q_OBJECT
public:
    explicit Books(QWidget *parent = 0);
    void addBook(const QString& path);

signals:

public slots:
    void openBook();
private:
    Ui::Books ui;
};

#endif // BOOKS_HXX
