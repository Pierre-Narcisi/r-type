#include <QPainter>
#include <QStyle>
#include <QStyleOption>
#include <QNetworkReply>
#include <QMetaMethod>
#include <iostream>
#include "cache.h"
#include "singletons.h"
#include "gameitem.h"
#include "hashchecker.h"
#include "resoucesdownloader.h"
#include "gamelauncher.h"
#include "ui_gameitem.h"

static inline QSize    operator+(QSize s, int toadd)
{
    s.setWidth(s.width() + toadd);
    s.setHeight(s.height() + toadd);
    return s;
}

static inline QSize    operator-(QSize s, int tosub)
{
    s.setWidth(s.width() - tosub);
    s.setHeight(s.height() - tosub);
    return s;
}

GameItem::GameItem(json::Entity &data, QWidget *parent) :
    QWidget(parent),
    stateMessage(""),
    buttonText(""),
    speed(""),
    descriptionHtml(""),
    error(false),
    progress(0),
    checkingFiles(true),
    ready(false),
    _data(data),
    _manager(Singletons::getManager()),
    _rscDler(nullptr),
    _iconReply(nullptr),
    _descReply(nullptr),
    _checker(nullptr),
    ui(new Ui::GameItem)
{
    ui->setupUi(this);
    this->ui->GameNameLabel->setText(QString::fromStdString(data["name"].getData<json::String>().get()));
}

GameItem::~GameItem()
{
    if ((void*) _iconReply) {
        _iconReply->abort();
        _iconReply->deleteLater();
    }
    if ((void*) _descReply) {
        _descReply->abort();
        _descReply->deleteLater();
    }
    if ((void*) _checker) {
        _checker->abort();
    }
    if ((void*)  _rscDler)
        delete _rscDler;
    delete ui;
}

json::Entity GameItem::getDataSheet()
{
    return (_data);
}

void GameItem::select()
{
    this->setProperty("selectedItem", true);
    this->ui->GameNameLabel->setProperty("selectedItem", true);
    this->style()->polish(this);
    this->ui->GameNameLabel->style()->polish(this->ui->GameNameLabel);
    emit onSelectChange(this, true);
}

void GameItem::unSelect()
{
    this->setProperty("selectedItem", {});
    this->ui->GameNameLabel->setProperty("selectedItem", {});
    this->style()->polish(this);
    this->ui->GameNameLabel->style()->polish(this->ui->GameNameLabel);
    emit onSelectChange(this, false);
}

void GameItem::_onHashComplete(json::Entity data)
{
    _checkedData = data;
    _rscDler = ResoucesDownloader::downloadResources(this, _checkedData);
    if (_checkedData["needDownload"] == true) {
        buttonText = (_checkedData["isNewInstall"].to<bool>() ? "Install" : "Update");
    } else {
        progress = 100;
        ready = true;
    }
    connect(_rscDler, &ResoucesDownloader::onProgress,
            this, &GameItem::_onDownloadProgress);
    connect(_rscDler, &ResoucesDownloader::onError,
            this, &GameItem::_onDownloadFailed);
    connect(_rscDler, &ResoucesDownloader::onComplete,
            this, &GameItem::_onDownloadEnd);
    checkingFiles = false;
    emit onStateChange(this);
}

void GameItem::_initDownloader(void)
{
    _checker = HashChecker::needUpdate(_data);
    connect(_checker, &HashChecker::onComplete,
    [this] (json::Entity data) {
        this->_checker = nullptr;
        qRegisterMetaType<json::Entity>("json::Entity");
        QMetaObject::invokeMethod(this, "_onHashComplete", Q_ARG(json::Entity, data));
    });
}

void GameItem::_initIcon()
{
    QString strUrl = QString::fromStdString(_data["icon"].getData<json::String>().get());
    _iconReply = _manager->get(
                QNetworkRequest(QUrl(strUrl)));
    QObject::connect(_iconReply, &QNetworkReply::finished, [this, strUrl] () {
        if (_iconReply) {
            QByteArray data;

            if (_iconReply->error() == QNetworkReply::NoError) {
                data = _iconReply->readAll();
                Cache::saveToCache(strUrl, data);
            } else {
                std::cerr << "ReplyException: " << _iconReply->errorString().toStdString() << std::endl;
                data = Cache::getCachedData(strUrl);
            }
            if (data.isEmpty() == false) {
                QPixmap bkgnd;
                bkgnd.loadFromData(data);
                bkgnd = bkgnd.scaled(this->ui->GameLogo->size(), Qt::IgnoreAspectRatio);
                this->ui->GameLogo->setPixmap(bkgnd);
                this->ui->GameLogo->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
            }

            _iconReply->deleteLater();
        }
        _iconReply = nullptr;
    });
}

void GameItem::_initDesc()
{
    QString descUrl = QString::fromStdString(_data["description"].getData<json::String>().get());
    if (descUrl.isEmpty() == false) {
        _descReply = _manager->get(
                    QNetworkRequest(QUrl(descUrl)));
        QObject::connect(_descReply, &QNetworkReply::finished, [this, descUrl] () {
            if (_descReply) {
                QByteArray data;

                if (_descReply->error() == QNetworkReply::NoError) {
                    data = _descReply->readAll();
                    Cache::saveToCache(descUrl, data);
                } else {
                    std::cerr << "ReplyException: " << _descReply->errorString().toStdString() << std::endl;
                    data = Cache::getCachedData(descUrl);
                }
                if (data.isEmpty() == false) {
                    this->descriptionHtml = data;
                    emit onStateChange(this);
                }
                _descReply->deleteLater();
            }
            _descReply = nullptr;
        });
    }
}

inline void GameItem::_checkSettingsFile(void)
{
    QFile   file(QString::fromStdString(_checkedData["path"].to<std::string>()) + "/.settings.json");

    if (_data["settings"].isObject() && file.exists() == false) {
        std::ostringstream  stm;
        stm << json::makeObject {
            {"settings", _data["settings"]}
        } << std::endl;
        if (file.open(QFile::WriteOnly)) {
            file.write(QByteArray::fromStdString(stm.str()));
            file.close();
        }
    }
}

void GameItem::actionClicked()
{
    if (checkingFiles == false && ready == false && _rscDler) {
        _rscDler->start();
    } else {
        if (_checkedData["entry"].isString()) {
            _checkSettingsFile();
            GameLauncher::start(QString::fromStdString(_checkedData["path"].to<std::string>()),
                                QString::fromStdString(_checkedData["entry"].to<std::string>()));
        } else {
            std::cerr << "Bad Data sheet: \"entry\" key not found!" << std::endl;
        }
        emit onStateChange(this);
    }
}

void GameItem::_onDownloadProgress(int p, qint64 speed)
{
    this->progress = p;
    this->speed = ResoucesDownloader::prettySize(speed) + "/s";
    emit onStateChange(this);
}

void GameItem::_onDownloadEnd()
{
    this->progress = 100;
    this->ready = true;
    emit onStateChange(this);
}

void GameItem::_onDownloadFailed()
{
    this->progress = 100;
    this->error = true;
    this->stateMessage = "Download Failed!!";
    emit onStateChange(this);
}

void GameItem::paintEvent(QPaintEvent *)
 {
     QStyleOption opt;
     opt.init(this);
     QPainter p(this);
     this->style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

void GameItem::mousePressEvent(QMouseEvent *)
{
    select();
}

void GameItem::showEvent(QShowEvent *)
{
    _initDesc();
    _initIcon();
    _initDownloader();
}
