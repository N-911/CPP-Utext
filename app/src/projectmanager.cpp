#include "projectmanager.h"
#include "loggingcategories.h"
#include <QDir>
#include <QFileSystemModel>
#include "listmodel.h"

ProjectManager::ProjectManager(Ui::MainWindow *parent) : m_parrent(parent) {
}

void ProjectManager::add_project_folder(const QString &dirName) {
    qDebug(logDebug()) << "add new project " << dirName;

    if (m_dirs.count(dirName) != 0) {
        qInfo(logInfo()) << QString("project %1 was already been open ").arg(QDir(dirName).dirName());
        return;
    }
    m_dirs.push_back(dirName);
    qInfo(logInfo()) << "m_projects size = " << m_dirs.size();
//    m_parrent
}

void ProjectManager::close_project_folder(QModelIndex &index) {
    // get dirname from index
    QString dirName("find_dir");
//    auto it = m_projects.indexOf(dirName, 0);
//    m_projects.remove(it);
}


