#include "TranslationListModel.h"

TranslationListModel::TranslationListModel(QObject *parent) : QAbstractListModel(parent)
{

}

QHash<int,QByteArray>
TranslationListModel::roleNames() const
{
    QHash<int,QByteArray> roles;

    roles.insert(TranslationListModel::TypeTranslation, "translation");

    return roles;
}

void
TranslationListModel::append(QString item)
{
//    beginInsertRows(QModelIndex());
    beginResetModel();
    translations.append(item);
//    endInsertRows();
    endResetModel();
}

//void
//TranslationListModel::set(QVariantList& data)
//{
//    beginResetModel();
//    translations = std::move(data);
//    endResetModel();
//}


QVariant
TranslationListModel::data(const QModelIndex &index, int role) const
{
    Q_UNUSED(role)
    if (index.isValid() && role == TranslationListModel::TypeTranslation)
        return QVariant::fromValue(translations.value(index.row()));
    return QVariant();
}

int TranslationListModel::rowCount(const QModelIndex&) const{
    return translations.count();
}
