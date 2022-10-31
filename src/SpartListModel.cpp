#include <QNetworkReply>
#include <QJsonArray>
#include <QVariant>
#include <QVector>
#include <QJsonObject>

#include "SpartListModel.h"
#include "SubjectListModel.h"
#include "core.h"


SpartListModel::SpartListModel(QObject *parent) : QAbstractListModel(parent)
{

}

void
SpartListModel::getTranslations(const QString &text, qint64 fromLang, qint64 toLang)
{
    QNetworkReply * request = _transport->get(QNetworkRequest(QString("http://www.multitran.com/api/api.exe?s=" + text + "&l1=" + QString::number(fromLang) + "&l2=" + QString::number(toLang) +"&k=AflgfoYf&hl=1")));
    connect(request, &QNetworkReply::finished, this, &SpartListModel::onTranslationsReceived);
}

void
SpartListModel::onTranslationsReceived()
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

                QJsonArray origs = spart_json.toObject()["origs"].toArray();

                QString spart_str = spart_json.toObject()["spart"].toString();

                SubjectListModel* subject_model = new SubjectListModel;
                subject_model->spart = spart_str;

                for (const QJsonValue& orig_json : origs) {
                    QJsonArray subjects = orig_json.toObject()["subjs"].toArray();

                    for (const QJsonValue& subject_json : subjects) {
                        QJsonObject subject = subject_json.toObject();
                        QJsonArray trans = subject["tr"].toArray();

                        TranslationListModel* translation_model = new TranslationListModel;
                        translation_model->subject = subject["subj"].toString();


                        for (const QJsonValue& trans_json : trans) {
                            qDebug() << "spart: " << spart_str << " translation: " << trans_json.toObject()["tran"];

                            translation_model->translations.append(trans_json.toObject()["tran"].toString());
                        }
                        subject_model->append(translation_model);
                    }
                }
                append(subject_model);

            }

        }  catch (std::runtime_error const &er) {
            qDebug() << er.what();
        }
    }

   reply->deleteLater();

//    beginResetModel();
//    _subjects = std::move(newTranslations);
//    endResetModel();
}

SpartListModel::~SpartListModel()
{
    qDeleteAll(_subjects);
    _subjects.clear();
}

void
SpartListModel::append(SubjectListModel *item)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    _subjects.append(item);
    endInsertRows();
}

void
SpartListModel::clear()
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    qDeleteAll(_subjects);
    _subjects.clear();
    endInsertRows();
}

QVariant
SpartListModel::data(const QModelIndex &index, int role) const {
    Q_UNUSED(role)
    if (!index.isValid())
        return QVariant();

    SubjectListModel* subject = _subjects.at(index.row());
    if (role == SpartListModel::TypeSpart) {
        return subject->spart;
    } else if (role == SpartListModel::TypeSubjectModel) {
        return QVariant::fromValue(subject->translations);
    }
    return QVariant();
}

int
SpartListModel::rowCount(const QModelIndex &parent) const {
    Q_UNUSED(parent);
    return _subjects.count();
}


QHash<int,QByteArray>
SpartListModel::roleNames() const
{
    QHash<int,QByteArray> roles;

    roles.insert(SpartListModel::TypeSpart, "spart");
    roles.insert(SpartListModel::TypeSubjectModel, "subjectModel");

    return roles;
}


bool SpartListModel::insertRows(int position, int rows, SubjectListModel *item, const QModelIndex &index)
{
    Q_UNUSED(index);
    if (!(_subjects.contains(item)))
    {
        beginInsertRows(QModelIndex(), position, position+rows-1);
        for (int row = 0; row < rows; ++row) {
            if (!(_subjects.contains(item)))
            {
                _subjects.insert(position, item);
            }
        }
        endInsertRows();
    }
    return true;
}

bool SpartListModel::removeRows(int position, int rows, const QModelIndex &index)
{
    Q_UNUSED(index);
    if((position +rows) > _subjects.size())
    {
        return false;
    }

    beginRemoveRows(QModelIndex(), position, position+rows-1);
    for (int row = 0; row < rows; ++row) {
        _subjects.removeAt(position);
    }
    endRemoveRows();
    return true;
}
