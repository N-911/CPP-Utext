#include "dialogsettings.h"
#include "ui_dialogsettings.h"

DialogSettings::DialogSettings(QMap<QString, QString> _settings, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogSettings)
{
    ui->setupUi(this);
    m_dialog_settings = _settings;
    QStringList themes({"Default", "ConsoleStyle", "ElegantDark",
                 "MaterialDark", "DarkSolarized", "ManjaroMix"});
    ui->themeComboBox->insertItems(0, themes);
    if (int index = themes.indexOf(m_dialog_settings["theme"]); index > 0) {
       ui->themeComboBox->setCurrentIndex(index);
    } else {
        ui->themeComboBox->setCurrentIndex(0);
    }

//    ui->themeComboBox->(_settings["theme"]);

}

DialogSettings::~DialogSettings()
{
    delete ui;
}

void DialogSettings::accepted() {
//    ui->comboBox->setCurrentIndex();
//     auto index = ui->themeComboBox->currentIndex();

//    auto index = ui->themeComboBox->currentIndex();

     m_dialog_settings["theme"] = ui->themeComboBox->currentText();
    emit SavedSettings(m_dialog_settings);
    QDialog::accept();
}


