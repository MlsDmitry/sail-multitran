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



class Spart
{
    Q_OBJECT
public:
    explicit Spart(QObject *parent = nullptr);

public:


};

#endif // SPART_H
