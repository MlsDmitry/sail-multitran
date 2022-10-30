#include "TranslationListModel.h"

#include <QNetworkReply>


TranslationListModel::TranslationListModel(QObject *parent) : QAbstractListModel(parent)
{

}

void
TranslationListModel::getTranslations(const QString &text, qint64 fromLang, qint64 toLang)
{
    QNetworkReply * request = _transport->get(QString("http://www.multitran.com/api/api.exe?s=" + text + "&l1=" + QString::number(fromLang) + "&l2=" + QString::number(toLang) +"&k=AflgfoYf&hl=1"));
    connect(request, &QNetworkReply::finished, this, &TranslationListModel::onTranslationsReceived);
}

void
onTranslationsReceived()
{
    QNetworkReply *reply = qobject_cast<QNetworkReply*>(sender());

    if (reply->error()) {
        qDebug() << "Error occured." << reply->errorString();

    } else {
        try {
            QVariantList data = Core::getSuggestionJsonList(reply);
            for (int i = 0; i != data.count(); i++) {
                newSuggestions.append(data[i].toMap()["str"].toString());
            }
        }  catch (std::runtime_error const &er) {
            qDebug() << er.what();
        }
    }

   reply->deleteLater();

    beginResetModel();
    _suggestions = std::move(newSuggestions);
    endResetModel();
}
