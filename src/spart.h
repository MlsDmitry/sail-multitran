/*
 *  "spart" short from "part of speech"
 *
 *  Spart structure:
 *
 *  "verb": {
 *      "general": {
 *          translation1,
 *          translation2,
 *          translation3
 *      },
 *      "spoken": {
 *          ...
 *      }
 *  }
*/

#ifndef SPART_H
#define SPART_H

#include <QObject>
#include <QVariantList>
#include <QString>



class Spart : public QObject
{
    Q_OBJECT
public:
//    Q_PROPERTY(QString spart MEMBER spart)
//    Q_PROPERTY(QVariantList translations MEMBER translations)
    explicit Spart(QObject *parent = nullptr);

    QString translation;
    QString spart;

signals:

public slots:

};

#endif // SPART_H
