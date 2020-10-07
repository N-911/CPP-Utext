#ifndef TABMENAGER_H
#define TABMENAGER_H

#include <QTabWidget>
#include <QVector>

class TabMenager : public QWidget
{
public:
    TabMenager(QTabWidget *parent = nullptr);
    virtual ~TabMenager();

private:
    QTabWidget *m_parent;
//    QVector<???> m_tablist;
};

#endif // TABMENAGER_H
