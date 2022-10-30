#include "core.h"

#include <QDebug>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>


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

    if (reply_object["status"] != "1") {
        throw std::runtime_error("status is not 1.");
    }

    return root_map["data"].toList();
}

QVariantList
Core::getTranslationJsonList(QNetworkReply *reply)
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

    if (reply_object["status"] != "1") {
        throw std::runtime_error("status is not 1.");
    }

    // parts of speech
    QJsonArray sparts = reply_object["sparts"].toArray();

    /*  QVariantList structure translations
     *
     *  [
     *      "verb": {
     *          spelling: "original spelling"
     *          "general": {
     *              translation1,
     *              translation2,
     *              translation3
     *          },
     *          "spoken": {
     *              ...
     *          }
     *      },
     *      ...
     *  ]
    */
    QVariantList translations;


    for (const QJsonValue& spart_json : sparts) {
        /*
         *  spart_json
         *
         * {
         *  "id": "128",
         *  "spart": "v",
         *  "origs": [
         *  {
         *      "orig": "hello",
         *      "pron": "hə'ləʊ,he-",
         *      "subjs": [
         *          "subj": "gen.",
         *          "fsubj": "General",
         *          "sid": "0",
         *          "tr": [
         *              {
         *                  "tran": "здороваться"
         *               }
         *          ]
         *      ]
         *  }
        */

        QVariantMap spart;

        QJsonArray origs = spart_json.toObject()["origs"].toArray();

        for (const QJsonValue& orig_json : origs) {
            QJsonArray subjects = orig_json.toObject()["subjs"].toArray();

            for (const QJsonValue& subject_json : subjects) {

            }
        }

    }
}
