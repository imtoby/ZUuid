/***************************************************************************
    Copyright (C) 2014 by ZhaoDongshuang
    Author: ZhaoDongshuang
    Email: imtoby@126.com
    Date: 2014/10/8
    File: ZUuid.h
 ***************************************************************************/

#include "ZUuid.h"
#include <QUuid>
#include <QDebug>
#include <QDateTime>
#include <QVariant>
#include <QBitArray>

namespace ZUuidNS{

/* Name string is a fully-qualified domain name */
const QUuid DNS("{6ba7b810-9dad-11d1-80b4-00c04fd430c8}");

/* Name string is a URL */
const QUuid URL("{6ba7b811-9dad-11d1-80b4-00c04fd430c8}");

/* Name string is an ISO OID */
const QUuid OID("{6ba7b812-9dad-11d1-80b4-00c04fd430c8}");

/* Name string is an X.500 DN (in DER or a text output format) */
const QUuid X500("{6ba7b814-9dad-11d1-80b4-00c04fd430c8}");
}

class ZUuidPrivate
{
public:
    ZUuidPrivate()
        : bUseCurlyBraces(false)
        , bUppercase(true)
        , separator("_")
        , nameSpace(0)
    {
        curUuidNS = ZUuidNS::DNS;
    }

    bool bUseCurlyBraces;
    bool bUppercase;
    QString separator;
    int nameSpace;
    QUuid curUuidNS;
};

ZUuid::ZUuid(QObject *parent)
    : QObject(parent)
    , d(new ZUuidPrivate())
{
    if(ZUuidNS::DNS.isNull() ||
            ZUuidNS::URL.isNull() ||
            ZUuidNS::OID.isNull() ||
            ZUuidNS::X500.isNull())
    {
        Q_ASSERT(false && "ZUuidNS is Null");
    }
}

ZUuid::~ZUuid()
{
    if(d){
        delete d;
        d = 0;
    }
}

void ZUuid::setCurlyBraces(bool enable)
{
    d->bUseCurlyBraces = enable;
    emit curlyBracesChanged();
}

void ZUuid::setUppercase(bool enable)
{
    d->bUppercase = enable;
    emit uppercaseChanged();
}

void ZUuid::setSeparator(const QString &separator)
{
    d->separator = separator;
    emit separatorChanged();
}

void ZUuid::setNameSpace(int index)
{
    switch(index)
    {
    case UNS_URL:
        d->curUuidNS = ZUuidNS::URL;
        break;
    case UNS_OID:
        d->curUuidNS = ZUuidNS::OID;
        break;
    case UNS_X500:
        d->curUuidNS = ZUuidNS::X500;
        break;
    case UNS_DNS:
    default:
        d->curUuidNS = ZUuidNS::DNS;
        break;
    }
    d->nameSpace = index;
    emit nameSpaceChanged();
}

bool ZUuid::curlyBraces() const
{
    return d->bUseCurlyBraces;
}

bool ZUuid::uppercase() const
{
    return d->bUppercase;
}

QString ZUuid::separator() const
{
    return d->separator;
}

int ZUuid::nameSpace() const
{
    return d->nameSpace;
}

QString ZUuid::createUuid()
{
    QUuid Uuid = QUuid::createUuid();
    if(!Uuid.isNull()) {
        qDebug() << Uuid.version();
        return updateResult(Uuid.toString());
    }
    return QString();
}

QString ZUuid::createUuidV3()
{
    QUuid Uuid = QUuid::createUuid();
    if(!Uuid.isNull()) {
        QUuid UuidV3 = QUuid::createUuidV3(d->curUuidNS, Uuid.toRfc4122());
        qDebug() << UuidV3.version();
        if(!UuidV3.isNull()) {
            return updateResult(UuidV3.toString());
        }
    }
    return QString();
}

QString ZUuid::createUuidV3(int index)
{
    setNameSpace(index);
    return createUuidV3();
}

QString ZUuid::createUuidV5()
{
    QUuid Uuid = QUuid::createUuid();
    if(!Uuid.isNull()) {
        QUuid UuidV5 = QUuid::createUuidV5(d->curUuidNS, Uuid.toRfc4122());
        qDebug() << UuidV5.version();
        if(!UuidV5.isNull()) {
            return updateResult(UuidV5.toString());
        }
    }
    return QString();
}

QString ZUuid::createUuidV5(int index)
{
    setNameSpace(index);
    return createUuidV5();
}

QString bitArray2String(QBitArray array)
{
   uint value = 0;
   for (int i = 0; i < array.size(); ++i ) {
       value <<= 1;
       value += (int)array.at(i);
   }
   QString str;
   str.setNum(value, 10);
   return str;
}

QString ZUuid::updateResult(const QString& currentUuid)
{
    if(!currentUuid.isEmpty()) {
        QString tmpUuid = currentUuid;
        if(!d->bUseCurlyBraces){
            tmpUuid.remove(0,1).chop(1);
        }
        if(d->separator != "-"){
            QStringList tmpList = tmpUuid.split("-");
            tmpUuid.clear();
            for(int i=0; i<tmpList.count(); ++i){
                tmpUuid.append(tmpList.at(i));
                tmpUuid.append(d->separator);
            }
            tmpUuid.chop(1);
        }
        if(d->bUppercase){
            tmpUuid = tmpUuid.toUpper();
        }
        return tmpUuid;
    }
    return QString();
}
