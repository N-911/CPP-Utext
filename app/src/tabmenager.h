#ifndef TABMENAGER_H
#define TABMENAGER_H

#include <QTabWidget>
#include <QVector>
#include "syntaxstyle.h"
#include "syntaxhighlightercxx.h"

QT_BEGIN_NAMESPACE
namespace Ui {
    class MainWindow;
}
QT_END_NAMESPACE

class TabManager
{
public:
    explicit TabManager(QTabWidget *parent, Ui::MainWindow *ui_parent);
    virtual ~TabManager();
    int addNewTab(QWidget *wd = nullptr, const QString &nameTab = "untitled", const QString &content = "");
    [[nodiscard]] QWidget *getWidget(int index) const;
    [[nodiscard]] QWidget *getCurrentWidget() const;
    [[nodiscard]] int getCurrentIndex() const;
    void closeTab(int index);
    void setSyntaxStyle(SyntaxStyle *style);
    void setHighlighter(StyleSyntaxHighlighter *highlighter);
    int getTabListIndex(QWidget *wd);
    void setCurrentIndex(int index);
    void setTabTitle(int index, const QString &title = "untitled");
    void updateTabs();
    int getCountTab() const;

private:
    QTabWidget *m_parent;
    QVector<QWidget *> m_tablist;

    SyntaxStyle *m_style = nullptr;
    StyleSyntaxHighlighter *m_highlighter = nullptr;

    Ui::MainWindow *m_main_widget;
};

#endif // TABMENAGER_H
