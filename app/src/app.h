#ifndef UTEXT_APP_H
#define UTEXT_APP_H

#include <QApplication>
#include <QSettings>

// app settings
class App : public QApplication {

    Q_OBJECT

public:
    App (int& argc, char** argv, const QString& strOrg, const QString& strAppName);
    static App* utext_app();
    QSettings *utext_settings();

private:
    QSettings *m_utext_settings;

};

#endif //UTEXT_APP_H
