#ifndef ARTICLEWIDGET_H
#define ARTICLEWIDGET_H

#include <QWidget>
#include <QMap>
namespace Ui {
class ArticleWidget;
}
class Article;
class QTableWidget;
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
    void setWordStatus(int word, int status);

    void on_allKnown_clicked();

    void on_allUnknown_clicked();

    void on_allAnti_clicked();

    void on_preview_clicked();

    void on_saveWordStatus_clicked();

    void onPreviewUnknowButtonClicked();
    void onPreviewKnowButtonClicked();

private:
    void clearTable(QTableWidget* table);
    Ui::ArticleWidget *ui;
    Article* currentArticle_;
    QMap<int, QTableWidgetItem*> wordstatusItemMap_;
};

#endif // ARTICLEWIDGET_H
