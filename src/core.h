#ifndef CORE_H
#define CORE_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>

class Core : public QObject
{
    Q_OBJECT
public:
    explicit Core(QObject *parent = nullptr);
    Q_PROPERTY(QNetworkAccessManager * transport MEMBER _transport)
    Q_PROPERTY(quint32 toLang MEMBER _toLang)
    Q_PROPERTY(quint32 fromLang MEMBER _fromLang)

//    QNetworkAccessManager* getTransport() const;

    static QVariantList getSuggestionJsonList(QNetworkReply * reply);

private:
    QNetworkAccessManager *_transport;
    quint32 _toLang = 1;
    quint32 _fromLang = 2;

};

#endif // CORE_H
