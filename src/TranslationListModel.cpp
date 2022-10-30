#include <QNetworkReply>

#include "TranslationListModel.h"
#include "core.h"

TranslationListModel::TranslationListModel(QObject *parent) : QAbstractListModel(parent)
{

}

void
TranslationListModel::getTranslations(const QString &text, qint64 fromLang, qint64 toLang)
{
    QNetworkReply * request = _transport->get(QNetworkRequest(QString("http://www.multitran.com/api/api.exe?s=" + text + "&l1=" + QString::number(fromLang) + "&l2=" + QString::number(toLang) +"&k=AflgfoYf&hl=1")));
    connect(request, &QNetworkReply::finished, this, &TranslationListModel::onTranslationsReceived);
}

void
TranslationListModel::onTranslationsReceived()
{
    QVariantList newTranslations;
    QNetworkReply *reply = qobject_cast<QNetworkReply*>(sender());

    if (reply->error()) {
        qDebug() << "Error occured." << reply->errorString();

    } else {
        try {
            QVariantList data = Core::getSuggestionJsonList(reply);
            for (int i = 0; i != data.count(); i++) {
                newTranslations.append(data[i].toMap()["str"].toString());
            }
        }  catch (std::runtime_error const &er) {
            qDebug() << er.what();
        }
    }

   reply->deleteLater();

    beginResetModel();
    _translations = std::move(newTranslations);
    endResetModel();
}

QVariant
TranslationListModel::data(const QModelIndex &index, int role) const {
    if(index.isValid() && role == TranslationListModel::RoleDisplay) {
        return QVariant(_translations.value(index.row()));
    }
    return QVariant();
}

int
TranslationListModel::rowCount(const QModelIndex&) const{
    return _translations.size();
}


QHash<int,QByteArray>
TranslationListModel::roleNames() const
{
    QHash<int,QByteArray> roles;

    roles.insert(TranslationListModel::RoleDisplay, "display");

    return roles;
}
