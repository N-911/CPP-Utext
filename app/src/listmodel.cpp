#include "listmodel.h"
#include <loggingcategories.h>
#include "projectmanager.h"
#include <QTreeView>
#include "ui_mainwindow.h"

Listmodel::Listmodel(const QString &header, QWidget *parent, Ui::MainWindow *ui, const ProjectManager *manager)
        : QAbstractListModel(parent),
          m_header(header),
          m_manager(manager) {
    if (!m_manager)
        return;
    for (auto& model : m_manager->getProjects()) {
        QTreeView tmp(parent);
        ui->listView->setModel(model);
        m_project_treeView.push_back(&tmp);
    }
}

int Listmodel::rowCount(const QModelIndex &parent) const {
    return m_name_projects.size();
}

QVariant Listmodel::data(const QModelIndex &index, int role) const {
    if (!index.isValid())
        return QVariant();

    if (index.row() >= m_name_projects.size())
        return QVariant();

    if (role == Qt::DisplayRole) {
        return "m_project_treeView[index.row()]";
//        return QVariant();
    }
    else
        return QVariant();
}

QVariant Listmodel::headerData(int section, Qt::Orientation orientation,
                                     int role) const
{
    if (role != Qt::DisplayRole)
        return QVariant();

    if (orientation == Qt::Horizontal)
        return QStringLiteral("Column %1").arg(section);
    else
        return QStringLiteral("Row %1").arg(section);
}

void Listmodel::add_project_folder(const QString &dirName) {
    qDebug(logDebug()) << "add new project " << dirName;

    if (auto it = m_name_projects.indexOf(dirName, 0);  it == -1) {
        qInfo(logInfo()) << QString("project %1 was already been open ").arg(QDir(dirName).dirName());
        return;
    }
    m_name_projects.insert(m_name_projects.begin() + m_name_projects.size(), dirName);
    qInfo(logInfo()) << "m_projects size = " << m_name_projects.size();
}
