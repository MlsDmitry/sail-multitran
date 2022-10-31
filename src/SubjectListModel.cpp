#include "SubjectListModel.h"

SubjectListModel::SubjectListModel(QObject *parent) : QAbstractListModel(parent)
{

}

int SubjectListModel::rowCount(const QModelIndex&) const{
    return translations.count();
}

QHash<int,QByteArray>
SubjectListModel::roleNames() const
{
    QHash<int,QByteArray> roles;

    roles.insert(SubjectListModel::TypeSubject, "subject");
    roles.insert(SubjectListModel::TypeTranslationModel, "translationModel");

    return roles;
}

SubjectListModel::~SubjectListModel()
{
    qDeleteAll(translations);
    translations.clear();
}

void
SubjectListModel::append(TranslationListModel *item)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    translations.append(item);
    endInsertRows();
}

void
SubjectListModel::clear()
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    qDeleteAll(translations);
    translations.clear();
    endInsertRows();
}

QVariant
SubjectListModel::data(const QModelIndex &index, int role) const {
    Q_UNUSED(role)
    if (!index.isValid())
        return QVariant();

    TranslationListModel* tran = translations.at(index.row());
    if (role == SubjectListModel::TypeSubject) {
        return QVariant::fromValue(tran->subject);
    } else if (role == SubjectListModel::TypeTranslationModel) {
        return QVariant::fromValue(tran->translations);
    }
    return QVariant();
}

bool SubjectListModel::insertRows(int position, int rows, TranslationListModel *item, const QModelIndex &index)
{
    Q_UNUSED(index);
    if (!(translations.contains(item)))
    {
        beginInsertRows(QModelIndex(), position, position+rows-1);
        for (int row = 0; row < rows; ++row) {
            if (!(translations.contains(item)))
            {
                translations.insert(position, item);
            }
        }
        endInsertRows();
    }
    return true;
}

bool SubjectListModel::removeRows(int position, int rows, const QModelIndex &index)
{
    Q_UNUSED(index);
    if((position +rows) > translations.size())
    {
        return false;
    }

    beginRemoveRows(QModelIndex(), position, position+rows-1);
    for (int row = 0; row < rows; ++row) {
        translations.removeAt(position);
    }
    endRemoveRows();
    return true;
}
