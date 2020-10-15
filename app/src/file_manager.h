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

class TabManager;

class FileManager {

public:
    FileManager(Ui::MainWindow *parent);
    virtual ~FileManager();

    void loadFile(const QString &fullFileName);

    void newFile();
    bool save();
    bool saveAs();
    bool saveAll();
    bool isChanged();
    void closeFile(int index);


private slots:


private:
    QString strippedName(const QString &fullFileName) const;
    bool saveFile(const QString &fileName);
    void update_history_files();

    std::map<QString, size_t> m_open_files;
//    std::set<QString> m_files;
    std::deque<QString> m_history_files;  // for history

    Ui::MainWindow *m_file_widget;
    TabManager *m_tabManager;

};

#endif //UTEXT_FILE_MANAGER_H
