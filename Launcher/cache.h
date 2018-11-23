#ifndef CACHE_H
#define CACHE_H

#include <QByteArray>
#include <QString>

struct Cache
{
public:
    static QString      getDataDirectory(void);
    static QByteArray   getCachedData(QString url);
    static bool         saveToCache(QString url, QByteArray data);
    static QString&     getScrollBarStyle(void);
    static QByteArray   getMd5Hash(QString str);
private:
    static inline QString
                    getDirHash(QString str);
};

#endif // CACHE_H
