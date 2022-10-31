#ifndef SPARTLISTMODEL_H
#define SPARTLISTMODEL_H

#include <QObject>
#include <QVariant>
#include <QVector>
#include <QAbstractListModel>
#include <QNetworkAccessManager>

#include "SubjectListModel.h"

class SpartListModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(QNetworkAccessManager *transport MEMBER _transport)
public:
    explicit SpartListModel(QObject *parent = nullptr);
//    ~SpartListModel();

    enum Roles {
        TypeSpart = Qt::UserRole + 1,
        TypeSubject,
        TypeTranslation,
        TypeComment
    };

    Q_ENUM(Roles)

    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    virtual QVariant data(const QModelIndex &index, int role) const;
//    bool insertRows(int position, int rows, SubjectListModel *item, const QModelIndex &index = QModelIndex());
//    bool removeRows(int position, int rows, const QModelIndex &index = QModelIndex());
    virtual QHash<int, QByteArray> roleNames() const;
//    void append(SubjectListModel *item);

    Q_INVOKABLE void getTranslations(const QString &text, qint64 fromLang, qint64 toLang);
    void onTranslationsReceived();

private:
//    void clear();
private:
    QNetworkAccessManager * _transport;
    QVariantList _subjects;
};

#endif // SPARTLISTMODEL_H
