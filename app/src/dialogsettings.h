#ifndef DIALOGSETTINGS_H
#define DIALOGSETTINGS_H

#include <QDialog>
#include <Qmap>
#include <QStringList>


namespace Ui {
class DialogSettings;
}

class DialogSettings : public QDialog
{
    Q_OBJECT

public:
    explicit DialogSettings(QMap<QString, QString> _settings, QWidget *parent = nullptr);
    ~DialogSettings();

    void accepted();

signals:
    QMap<QString, QString> SavedSettings(QMap<QString, QString>);

private:
    Ui::DialogSettings *ui;

    QMap<QString, QString> m_dialog_settings;

};

#endif // DIALOGSETTINGS_H
