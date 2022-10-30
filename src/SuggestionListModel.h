#ifndef SUGGESTIONLISTMODEL_H
#define SUGGESTIONLISTMODEL_H

//#include "core.h"
#include <QAbstractListModel>
#include <QNetworkAccessManager>
#include <QNetworkReply>

class SuggestionListModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(QNetworkAccessManager* transport READ getTransport WRITE setTransport)
public:
    explicit SuggestionListModel(QObject *parent = nullptr);

    enum Roles {
        RoleDisplay = Qt::UserRole + 1
    };

    Q_ENUM(Roles)

    Q_INVOKABLE virtual int rowCount(const QModelIndex&) const;
    Q_INVOKABLE virtual QVariant data(const QModelIndex &index, int role) const;
    virtual QHash<int, QByteArray> roleNames() const;

    Q_INVOKABLE void getSuggestions(const QString &text, qint64 fromLang, qint64 toLang);
    void onSuggestionsReceived();

private:
    void clear();
private:
    QVariantList _suggestions;
    QNetworkAccessManager * _transport;
};

#endif // SUGGESTIONLISTMODEL_H
