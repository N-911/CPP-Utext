#ifndef TABWELCOME_H
#define TABWELCOME_H

#include <QWidget>
#include <QLabel>

class TabWelcome : public QWidget
{
    Q_OBJECT
public:
    explicit TabWelcome(QWidget *parent = nullptr);
    virtual ~TabWelcome();

signals:

public slots:
};

#endif // TABWELCOME_H
