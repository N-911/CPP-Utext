#include "listmodel.h"

int Listmodel::rowCount(const QModelIndex &parent) const {
    return m_projects.size();
}

QVariant Listmodel::data(const QModelIndex &index, int role) const {
    if (!index.isValid())
        return QVariant();

    if (index.row() >= m_projects.size())
        return QVariant();

    if (role == Qt::DisplayRole) {
//        return m_projects.at(index.row());
        return QVariant();
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