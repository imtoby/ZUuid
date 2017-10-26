# ZUuid
A Tool for Create Uuid Format String Developed with Qt

```Qt
#include <QCoreApplication>
#include "ZUuid.h"
#include <QDebug>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    ZUuid* zuuid = new ZUuid(a.parent());
    zuuid->setCurlyBraces(false);
    zuuid->setUppercase(true);
    zuuid->setSeparator("_");
    zuuid->setNameSpace(ZUuid::UNS_X500);

    qDebug() << zuuid->createUuidV5();

    const int r = a.exec();

    if (NULL != zuuid) {
        delete zuuid;
        zuuid = 0;
    }

    return r;
}

```

The result is like this：

![image](https://github.com/imtoby/ZUuid/blob/master/show_image/show.png)
