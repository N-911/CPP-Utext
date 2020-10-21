#include "settings.h"
#include "loggingcategories.h"

Settings::Settings(const QString& strOrg, const QString& strAppName) {
    m_preferences = new QSettings(strOrg, strAppName);
}

Settings::~Settings() {
    delete m_preferences;
}


void Settings::set_settings(QMap<QString, QString> _settings) {
    qInfo(logInfo()) << _settings["theme"];

    //    QFile file(":/qss/ElegantDark.qss");
//    file.open(QFile::ReadOnly);
//    app.setStyleSheet(file.readAll());


}
