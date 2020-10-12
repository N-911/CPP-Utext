#ifndef UTEXT_FILE_MANAGER_H
#define UTEXT_FILE_MANAGER_H

#include <QString>
#include <QWidget>

#include <map>
#include <deque>
#include <set>

QT_BEGIN_NAMESPACE
namespace Ui {
    class MainWindow;
}
QT_END_NAMESPACE

class FileManager {

public:
    FileManager(Ui::MainWindow *parent);

    void loadFile(const QString &fullFileName);

    void newFile();
    bool save();
    bool saveAs();
    bool saveAll();
    bool isChanged();
    void closeFile(int index);


private slots:


private:
    QString strippedName(const QString &fullFileName);
    bool saveFile(const QString &fileName);

//    void setCurrentFile(QWidget *current_file);
//    QWidget *m_current_file;
//    std::map<QString, QWidget *> m_load_files;

    std::map<QString, size_t> m_open_files;
    std::set<QString> m_files;

    std::deque<QString> last_files;

    Ui::MainWindow *m_file_widget;
};

#endif //UTEXT_FILE_MANAGER_H
