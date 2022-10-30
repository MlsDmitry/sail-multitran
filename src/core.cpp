#include "core.h"

#include <QDebug>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>


Core::Core(QObject *parent) : QObject(parent)
{
    _transport = new QNetworkAccessManager();
//    fullname = QString("Hello, World!");

//    connect(_transport, &QNetworkAccessManager::finished, this, &Core::onResponseArrived);

}

QVariantList
Core::getSuggestionJsonList(QNetworkReply * reply)
{
    auto json_reply = QJsonDocument::fromJson(reply->readAll());

    if (json_reply.isNull()) {
        throw std::runtime_error("Failed to create JSON doc.");
    }

    if (!json_reply.isObject()) {
        throw std::runtime_error("JSON is not an object.");
    }
    QJsonObject reply_object = json_reply.object();

    if (reply_object.isEmpty()) {
        throw std::runtime_error("JSON object is empty.");
    }

    QVariantMap root_map = reply_object.toVariantMap();

    if (root_map["status"] != "1") {
        throw std::runtime_error("status is not 1.");
    }

    return root_map["data"].toList();
}
