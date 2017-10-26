/***************************************************************************
    Copyright (C) 2014 by ZhaoDongshuang
    Author: ZhaoDongshuang
    Email: imtoby@126.com
    Date: 2014/10/8
    File: ZUuid.h
 ***************************************************************************/

#ifndef ZUUID_H
#define ZUUID_H

#include <QObject>

class ZUuidPrivate;

class ZUuid : public QObject
{
    Q_OBJECT
    Q_ENUMS(UuidNameSpace)
    Q_PROPERTY( bool curlyBraces READ curlyBraces WRITE setCurlyBraces NOTIFY curlyBracesChanged )
    Q_PROPERTY( bool uppercase READ uppercase WRITE setUppercase NOTIFY uppercaseChanged )
    Q_PROPERTY( QString separator READ separator WRITE setSeparator NOTIFY separatorChanged )
    Q_PROPERTY( int nameSpace READ nameSpace  WRITE setNameSpace NOTIFY nameSpaceChanged )

public:
    explicit ZUuid(QObject *parent = 0);
    ~ZUuid();

    void setCurlyBraces(bool enable);
    void setUppercase(bool enable);
    void setSeparator(const QString& separator);
    void setNameSpace(int index);

    bool curlyBraces() const;
    bool uppercase() const;
    QString separator() const;
    int nameSpace() const;

    Q_INVOKABLE QString createUuid(); // random
    Q_INVOKABLE QString createUuidV3();
    Q_INVOKABLE QString createUuidV3(int index);
    Q_INVOKABLE QString createUuidV5();
    Q_INVOKABLE QString createUuidV5(int index);

    enum UuidNameSpace{
        UNS_DNS = 0,
        UNS_URL,
        UNS_OID,
        UNS_X500
    };

signals:
    void curlyBracesChanged();
    void uppercaseChanged();
    void separatorChanged();
    void nameSpaceChanged();

private:
    QString updateResult(const QString& currentUuid);

private:
    ZUuidPrivate* d;
};

#endif // ZUUID_H
