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
    void close_file();
    bool saveFile(const QString &fileName);

private:

    void setCurrentFile(QWidget *current_file);
    std::map<QString, QWidget *> m_load_files;
    std::map<size_t, QWidget *> m_load2_files;
    QWidget *m_current_file;
    Ui::MainWindow *m_parent;
};

#endif //UTEXT_FILE_MANAGER_H
