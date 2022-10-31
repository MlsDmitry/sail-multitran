#include <QNetworkReply>
#include <QJsonArray>
#include <QVariant>
#include <QVector>
#include <QJsonObject>

#include "TranslationListModel.h"
#include "core.h"
#include "spart.h"

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
            clear();

            QJsonArray sparts = Core::getTranslationJsonList(reply);

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

                QString spart_str = spart_json.toObject()["spart"].toString();

//                spart.insert(spart_str, QVariantMap());


                for (const QJsonValue& orig_json : origs) {
                    QJsonArray subjects = orig_json.toObject()["subjs"].toArray();

                    for (const QJsonValue& subject_json : subjects) {
                        QJsonObject subject = subject_json.toObject();
                        QJsonArray trans = subject["tr"].toArray();
                        spart[spart_str].value<QVariantMap>().insert(
                                    subject["subj"].toString(), QVariantList());

                        for (const QJsonValue& trans_json : trans) {
                            spart[spart_str].value<QVariantMap>()[subject["subj"].toString()].value<QVariantList>().append(trans_json.toString());
                            qDebug() << "spart: " << spart_str << " translation: " << trans_json.toObject()["tran"];
                            spart.insert("spart", spart_str);
                            spart.insert("translation", trans_json.toObject()["tran"].toString());

                            Spart *spart2 = new Spart;

                            spart2->spart = spart_str;
                            spart2->translation = trans_json.toObject()["tran"].toString();

                            append(spart2);
                        }
                    }
                }

            }

        }  catch (std::runtime_error const &er) {
            qDebug() << er.what();
        }
    }

   reply->deleteLater();

//    beginResetModel();
//    _translations = std::move(newTranslations);
//    endResetModel();
}

TranslationListModel::~TranslationListModel()
{
    qDeleteAll(_translations);
    _translations.clear();
}

void
TranslationListModel::append(Spart *item)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    _translations.append(item);
    endInsertRows();
}

void
TranslationListModel::clear()
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    qDeleteAll(_translations);
    _translations.clear();
    endInsertRows();
}

QVariant
TranslationListModel::data(const QModelIndex &index, int role) const {
    Q_UNUSED(role)
    if (!index.isValid())
        return QVariant();

    Spart* spart = _translations.at(index.row());
    if (role == TranslationListModel::TypeSpart) {
        return spart->spart;
    } else if (role == TranslationListModel::TypeTranslations) {
        return spart->translation;
    }
    return QVariant();
}

int
TranslationListModel::rowCount(const QModelIndex &parent) const {
    Q_UNUSED(parent);
    return _translations.count();
}


QHash<int,QByteArray>
TranslationListModel::roleNames() const
{
    QHash<int,QByteArray> roles;

    roles.insert(TranslationListModel::TypeSpart, "spart");
    roles.insert(TranslationListModel::TypeTranslations, "translation");

    return roles;
}


bool TranslationListModel::insertRows(int position, int rows, Spart *item, const QModelIndex &index)
{
    Q_UNUSED(index);
    if (!(_translations.contains(item)))
    {
        beginInsertRows(QModelIndex(), position, position+rows-1);
        for (int row = 0; row < rows; ++row) {
            if (!(_translations.contains(item)))
            {
                _translations.insert(position, item);
            }
        }
        endInsertRows();
    }
    return true;
}

bool TranslationListModel::removeRows(int position, int rows, const QModelIndex &index)
{
    Q_UNUSED(index);
    if((position +rows) > _translations.size())
    {
        return false;
    }

    beginRemoveRows(QModelIndex(), position, position+rows-1);
    for (int row = 0; row < rows; ++row) {
        _translations.removeAt(position);
    }
    endRemoveRows();
    return true;
}
