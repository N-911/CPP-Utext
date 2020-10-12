#ifndef TABMENAGER_H
#define TABMENAGER_H

#include <QTabWidget>
#include <QVector>

class TabManager
{
public:
    TabManager(QTabWidget *parent = nullptr);
    virtual ~TabManager();
    int addNewTab(QWidget *wd = nullptr, const QString &nameTab = "untitled");
    void closeTab(int index);
    int getTabIndex(QWidget *wd);

signals:

private:
    QTabWidget *m_parent;
    QVector<std::unique_ptr<QWidget>> m_tablist;
};

#endif // TABMENAGER_H
