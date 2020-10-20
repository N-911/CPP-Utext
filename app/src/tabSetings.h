#ifndef UTEXT_TABSETINGS_H
#define UTEXT_TABSETINGS_H

#include <QDialog>
#include <QSettings>

class TabSetings : public QWidget {
    Q_OBJECT

public: explicit TabSetings(QWidget *parent = nullptr);

public slots:
    void handle_buttonReleased(int id);

private:
    QWidget *tabWidget;
    QSettings *settings;
};


#endif //UTEXT_TABSETINGS_H
