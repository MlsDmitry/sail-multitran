#include "SuggestionListModel.h"
#include "core.h"

#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>

SuggestionListModel::SuggestionListModel(QObject *parent) : QAbstractListModel(parent)
{
    qDebug() << "Suggestions size: " << QString::number(_suggestions.size());
}

void
SuggestionListModel::clear()
{
    beginResetModel();
    _suggestions.clear();
    endResetModel();
}

void
SuggestionListModel::getSuggestions(const QString &text, qint64 fromLang, qint64 toLang)
{
    if (text.length() == 0) {
        clear();
        return;
    }
    QNetworkReply * request = _transport->get(QNetworkRequest(QUrl(QString("http://www.multitran.com/api/ms.exe?s=") + text + QString("&l1=") + QString::number(fromLang) + QString("&l2=") + QString::number(toLang) + QString("&k=AflgfoYf&hl=1"))));
    connect(request, &QNetworkReply::finished, this, &SuggestionListModel::onSuggestionsReceived);
}

void
SuggestionListModel::onSuggestionsReceived()
{
    QVariantList newSuggestions;
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

QVariant
SuggestionListModel::data(const QModelIndex &index, int role) const {
    if(index.isValid() && role == SuggestionListModel::RoleDisplay) {
        return QVariant(_suggestions.value(index.row()));
    }
    return QVariant();
}

int SuggestionListModel::rowCount(const QModelIndex&) const{
    return _suggestions.size();
}


QHash<int,QByteArray>
SuggestionListModel::roleNames() const
{
    QHash<int,QByteArray> roles;

    roles.insert(SuggestionListModel::RoleDisplay, "display");

    return roles;
}
