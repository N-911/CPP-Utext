#ifndef UTEXT_PROJECTMANAGER_H
#define UTEXT_PROJECTMANAGER_H

#include "QWidget"
#include <vector>

QT_BEGIN_NAMESPACE
namespace Ui {
    class MainWindow;
}
QT_END_NAMESPACE


class ProjectManager {

public:
    ProjectManager(Ui::MainWindow *parent);
    ~ProjectManager() = default;

    void add_project_folder(const QString &dirName);

    void close_project_folder(QModelIndex& index);

private:
    std::vector<QString> m_projects;
    Ui::MainWindow *m_project_widget;
};


#endif //UTEXT_PROJECTMANAGER_H
