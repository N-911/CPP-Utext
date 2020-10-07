#ifndef UTEXT_FILE_MANAGER_H
#define UTEXT_FILE_MANAGER_H

#include <QString>
#include <QWidget>

#include <map>

QT_BEGIN_NAMESPACE
namespace Ui {
    class MainWindow;
}
QT_END_NAMESPACE

class FileManager {

public:
    FileManager(Ui::MainWindow *parent);

//    ~FileManager();

    void loadFile(const QString &fileName);
//    bool saveFile(const QString &fileName);

private:

//    bool saveFile(const QString &fileName);

    void setCurrentFile(QWidget *current_file);
    std::map<QString, QWidget *> m_load_files;
    QWidget *m_current_file;
    Ui::MainWindow *m_parent;
};

#endif //UTEXT_FILE_MANAGER_H
