#include <QCryptographicHash>
#include <QStandardPaths>
#include <QFileInfo>
#include <QFile>
#include <QDir>
#include <fstream>
#include "cache.h"

inline QString Cache::getDirHash(QString str)
{
    auto        urlHash = QCryptographicHash::hash(str.toLatin1(), QCryptographicHash::Md5).toHex();

    return (getDataDirectory() + "/cache/" + urlHash);
}

QByteArray Cache::getMd5Hash(QString str)
{
    return QCryptographicHash::hash(str.toLatin1(), QCryptographicHash::Md5).toHex();
}

QString Cache::getDataDirectory()
{
    return QStandardPaths::standardLocations(QStandardPaths::AppLocalDataLocation)[0];
}

QByteArray Cache::getCachedData(QString url)
{
    QFileInfo   urlHashSavePath(getDirHash(url));

    if (urlHashSavePath.absoluteDir().exists() == false)
        return "";
    QFile       urlHashFile(urlHashSavePath.absoluteFilePath());

    if (urlHashFile.open(QFile::ReadOnly) == false)
        return "";
    auto res = urlHashFile.readAll();
    urlHashFile.close();
    return res;
}

bool Cache::saveToCache(QString url, QByteArray data)
{
    QFileInfo   urlHashSavePath(getDirHash(url));

    if (urlHashSavePath.absoluteDir().exists() == false)
            if (urlHashSavePath.absoluteDir().mkpath(urlHashSavePath.absolutePath()) == false)
                return false;
    QFile       urlHashFile(urlHashSavePath.absoluteFilePath());

    if (urlHashFile.open(QFile::WriteOnly) == false)
        return false;
    urlHashFile.write(data);
    urlHashFile.close();
    return true;
}

QString &Cache::getScrollBarStyle(void)
{
    static QString  style(  "QScrollBar:vertical {"
                                "background: rgb(230, 230, 230);"
                                "width: 8px;"
                            "}"

                            "QScrollBar::handle:vertical {"
                                "background: rgb(180, 180, 180);"
                                "min-height: 15px;"
                            "}"

                            "QScrollBar::handle:hover {"
                                "background: rgb(110, 155, 203);"
                            "}"

                            "QScrollBar::add-line {"
                                "background: none;"
                            "}"

                            "QScrollBar::sub-line {"
                                "background: none;"
                            "}");

    return style;
}
