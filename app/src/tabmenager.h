#ifndef TABMENAGER_H
#define TABMENAGER_H

#include <QTabWidget>
#include <QVector>

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
    int getTabListIndex(QWidget *wd);
    void setCurrentIndex(int index);
    void setTabTitle(int index, const QString &title = "untitled");
    int getCountTab() const;

private:
    QTabWidget *m_parent;
    QVector<QWidget *> m_tablist;

    Ui::MainWindow *m_main_widget;
};

#endif // TABMENAGER_H
