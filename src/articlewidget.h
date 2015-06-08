#ifndef ARTICLEWIDGET_H
#define ARTICLEWIDGET_H

#include <QWidget>
#include <QMap>
namespace Ui {
class ArticleWidget;
}
class Article;
class QTableWidgetItem;
class ArticleWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ArticleWidget(QWidget *parent = 0);
    ~ArticleWidget();

private slots:
    void on_save_clicked();

    void on_parse_clicked();

    void onKnowButtonClicked();
    void onUnknowButtonClicked();
    void setWordStatus(const QString& word, int status);

    void on_allKnown_clicked();

    void on_allUnknown_clicked();

    void on_allAnti_clicked();

    void on_preview_clicked();

    void on_saveWordStatus_clicked();

private:
    Ui::ArticleWidget *ui;
    Article* currentArticle_;
    QMap<QString, QTableWidgetItem*> wordstatusItemMap_;
};

#endif // ARTICLEWIDGET_H
