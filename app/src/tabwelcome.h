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

public slots:
    virtual void paintEvent(QPaintEvent *event) override;

private:
    QLabel *l_welcome;
};

#endif // TABWELCOME_H
