#include "listmodel.h"
#include <loggingcategories.h>
#include "projectmanager.h"
#include <QTreeView>
#include "ui_mainwindow.h"
#include <QTreeWidgetItem>

Listmodel::Listmodel(const QString &header, QWidget *parent, Ui::MainWindow *ui)
        : QAbstractListModel(parent),
          m_header(header) {

//    if (!m_manager)
//        return;
//    for (auto& model : m_manager->getProjects()) {
//        QTreeView tmp(parent);
//        ui->listView->setModel(model);
//        m_project_treeView.push_back(&tmp);
//    }
}

int Listmodel::rowCount(const QModelIndex &parent) const {
    return m_projects.size();
}

QVariant Listmodel::data(const QModelIndex &index, int role) const {
    if (!index.isValid())
        return QVariant();

    if (index.row() >= m_projects.size())
        return QVariant();

    if (role == Qt::DisplayRole) {
//        return "m_project_treeView[index.row()]";
        return m_projects[0]->data(index);
//        return QVariant();
    }
    else
        return QVariant();
}

QVariant Listmodel::headerData(int section, Qt::Orientation orientation,
                                     int role) const
{
    if (role != Qt::DisplayRole) {
        return QVariant();
    }

    if (orientation == Qt::Horizontal) {
        return QStringLiteral("Column %1").arg(section);
    }
    else {
        return QStringLiteral("Row %1").arg(section);
    }
}

void Listmodel::add_data(const QString& dirName) {

//    QFileSystemModel *tmp = new QFileSystemModel();
//    tmp->setFilter(QDir::NoDotAndDotDot | QDir::AllDirs);
//    tmp->setRootPath(dirName);
//    m_projects[dirName] = tmp;
//    QTreeView tmp1(m_project_widget);
//    m_project_treeView.push_back(&tmp1);

//    QList<QTreeWidgetItem *> items;
//    for (int i = 0; i < 10; ++i)
//        items.append(new QTreeWidgetItem((QTreeWidget*)0, QStringList(QString("item: %1").arg(i))));
//    m_parent->treeWidget->insertTopLevelItems(0, items);

//    m_parent->treeWidget->insertTopLevelItems(0, m_projects);
}












//void Listmodel::add_project_folder(const QString &dirName) {
//    qDebug(logDebug()) << "add new project " << dirName;
//
//    if (auto it = m_name_projects.indexOf(dirName, 0);  it == -1) {
//        qInfo(logInfo()) << QString("project %1 was already been open ").arg(QDir(dirName).dirName());
//        return;
//    }
//    m_name_projects.insert(m_name_projects.begin() + m_name_projects.size(), dirName);
//    qInfo(logInfo()) << "m_projects size = " << m_name_projects.size();
//}






