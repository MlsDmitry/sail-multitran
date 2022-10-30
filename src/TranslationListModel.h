#ifndef TRANSLATIONLISTMODEL_H
#define TRANSLATIONLISTMODEL_H

#include <QAbstractListModel>
#include <QNetworkAccessManager>

class TranslationListModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(transport MEMBER _transport)
public:
    explicit TranslationListModel(QObject *parent = nullptr);

    enum Roles {
        RoleDisplay = Qt::UserRole + 1
    };

    Q_ENUM(Roles)

    Q_INVOKABLE virtual int rowCount(const QModelIndex&) const;
    Q_INVOKABLE virtual QVariant data(const QModelIndex &index, int role) const;
    virtual QHash<int, QByteArray> roleNames() const;

    Q_INVOKABLE void getTranslations(const QString &text, qint64 fromLang, qint64 toLang);
    void onTranslationsReceived();

private:
    void clear();
private:
    QNetworkAccessManager * _transport;
    QVariantMap _translations;

};

#endif // TRANSLATIONLISTMODEL_H
