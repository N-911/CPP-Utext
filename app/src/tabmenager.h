#ifndef TABMENAGER_H
#define TABMENAGER_H

#include <QTabWidget>
#include <QVector>

class TabManager
{
public:
    explicit TabManager(QTabWidget *parent = nullptr);
    virtual ~TabManager();
    int addNewTab(QWidget *wd = nullptr, const QString &nameTab = "untitled");
    int addNewTab(std::unique_ptr<QWidget> wd = nullptr, const QString &nameTab = "untitled");
    [[nodiscard]] QWidget *getWidget(int index) const;
    [[nodiscard]] QWidget *getCurrentWidget() const;
    [[nodiscard]] int getCurrentIndex() const;
    void closeTab(int index);
    int getTabListIndex(QWidget *wd);

signals:

private:
    QTabWidget *m_parent;
    QVector<std::unique_ptr<QWidget>> m_tablist;
};

#endif // TABMENAGER_H
