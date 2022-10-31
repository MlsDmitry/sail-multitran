#ifndef TRANSLATIONLISTMODEL_H
#define TRANSLATIONLISTMODEL_H

#include <QObject>
#include <QVariant>
#include <QVector>
#include <QAbstractListModel>
#include <QNetworkAccessManager>

#include "spart.h"

class TranslationListModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(QNetworkAccessManager *transport MEMBER _transport)
public:
    explicit TranslationListModel(QObject *parent = nullptr);
    ~TranslationListModel();

    enum Roles {
        TypeSpart = Qt::UserRole + 1,
        TypeTranslations
    };

    Q_ENUM(Roles)

    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    virtual QVariant data(const QModelIndex &index, int role) const;
    bool insertRows(int position, int rows, Spart *item, const QModelIndex &index = QModelIndex());
    bool removeRows(int position, int rows, const QModelIndex &index = QModelIndex());
    virtual QHash<int, QByteArray> roleNames() const;
    void append(Spart *item);

    Q_INVOKABLE void getTranslations(const QString &text, qint64 fromLang, qint64 toLang);
    void onTranslationsReceived();

private:
    void clear();
private:
    QNetworkAccessManager * _transport;
//    QVariantList _translations;
    QVector<Spart*> _translations;

};

#endif // TRANSLATIONLISTMODEL_H
