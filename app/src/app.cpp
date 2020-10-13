#include "app.h"

App::App (int& argc, char** argv, const QString& strOrg, const QString& strAppName)
                                        : QApplication(argc, argv),
                                        m_utext_settings(0) {
    setOrganizationName(strOrg);
    setApplicationName(strAppName);
    m_utext_settings = new QSettings(strOrg, strAppName);
}


App *App::utext_app() {
    return (App*) qApp;
}

QSettings *App::utext_settings() {
    return m_utext_settings;
}
