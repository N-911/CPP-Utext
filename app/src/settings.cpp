#include <QFile>
#include "settings.h"
#include "app.h"
#include "loggingcategories.h"

//Settings::Settings(const QString& strOrg, const QString& strAppName) {
Settings::Settings() {
//    m_preferences = new QSettings(strOrg, strAppName);

    m_preferences = App::utext_app()->utext_settings();
    QString theme = m_preferences->value("theme").toString();

    loadTheme(theme);
}

Settings::~Settings() {
//    delete m_preferences;
}


void Settings::set_settings(QMap<QString, QString> _settings) {
    qInfo(logInfo()) << "new theme =" << _settings["theme"];
    if(current_settings["theme"] != _settings["theme"]) {
        current_settings = _settings;
        loadTheme(_settings["theme"]);
    }


//    m_preferences->setValue("mainwindow/fullScreen", ui->isFullScreen());

    //    QFile file(":/qss/ElegantDark.qss");
//    file.open(QFile::ReadOnly);
//    app.setStyleSheet(file.readAll());


}

void Settings::loadTheme(QString &theme) {
    if (!theme.isEmpty()) {
        QFile file(":/qss/" + theme + ".qss");
        file.open(QFile::ReadOnly);
        App::utext_app()->setStyleSheet(file.readAll());
        current_settings["theme"] = theme;
    }
    qInfo(logInfo()) << theme;
}

QMap<QString, QString> Settings::get_current_settings() const {
    return current_settings;
}
