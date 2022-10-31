#ifndef SubjectListModel_H
#define SubjectListModel_H

#include <QAbstractListModel>
#include <QObject>
#include <QVector>

#include "TranslationListModel.h"


class SubjectListModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit SubjectListModel(QObject *parent = nullptr);
    ~SubjectListModel();

    enum Roles {
        TypeSubject = Qt::UserRole + 1,
        TypeTranslationModel
    };

    Q_ENUM(Roles)

    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    virtual QVariant data(const QModelIndex &index, int role) const;
    virtual QHash<int, QByteArray> roleNames() const;

    bool insertRows(int position, int rows, TranslationListModel *item, const QModelIndex &index = QModelIndex());
    bool removeRows(int position, int rows, const QModelIndex &index = QModelIndex());

    void append(TranslationListModel *item);
    void clear();


public:
    QVector<TranslationListModel*> translations;
    QString spart;
};

#endif // SubjectListModel_H
