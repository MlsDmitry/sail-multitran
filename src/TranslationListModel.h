#ifndef TRANSLATIONLISTMODEL_H
#define TRANSLATIONLISTMODEL_H

#include <QAbstractListModel>
#include <QObject>

class TranslationListModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit TranslationListModel(QObject *parent = nullptr);

    enum Roles {
        TypeTranslation = Qt::UserRole + 1
    };

    Q_ENUM(Roles)

    virtual int rowCount(const QModelIndex&) const;
    virtual QVariant data(const QModelIndex &index, int role) const;
    virtual QHash<int, QByteArray> roleNames() const;
    void append(QString item);

    QString subject;
    QVariantList translations;

};

#endif // TRANSLATIONLISTMODEL_H
