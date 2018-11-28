#include <QListWidgetItem>
#include <QInputDialog>
#include <QMessageBox>
#include <QAction>
#include <QDir>
#include <iostream>
#include <fstream>
#include "Json/Parser.hpp"
#include "cache.h"
#include "launchermainwindows.h"
#include "ui_launchermainwindows.h"
#include "gameitem.h"
#include "singletons.h"
#include "about.h"

LauncherMainWindows::LauncherMainWindows(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::LauncherMainWindows)
{
    ui->setupUi(this);

    _getSettings();

    auto    update = this->ui->menuBar->addAction("Update");
    connect(update, &QAction::triggered, [this, update] () {
            update->setEnabled(false);
            _loadMasterData();
            QTimer::singleShot(1000, [update] () {
                update->setEnabled(true);
            });
    });

    QAction *master = this->ui->menuBar->addAction("Master");
    connect(master, &QAction::triggered, [this] () {
        bool ok;
        QString text = QInputDialog::getText(this, "Change Master URL",
                        "New Url:", QLineEdit::Normal,
                        QString::fromStdString(_settings["masterUrl"].to<std::string>()), &ok);
        if (ok && !text.isEmpty()) {
            this->_getter.setMaster(text);
            this->_settings["masterUrl"] = text.toStdString();
            _loadMasterData();
            _saveSettings();
        }
    });

    QAction *about = this->ui->menuBar->addAction("About");
    connect(about, &QAction::triggered, [this] () {
        About   aboutModal(this);

        aboutModal.exec();
    });

    connect(this->ui->gameActionButton, &QPushButton::clicked, [this] () {
        this->ui->gameActionButton->setEnabled(false);
        this->ui->listGames->getSelectedItem()->actionClicked();
    });

    connect(this->ui->listGames, &ListGameItem::onSelectChange, [this] (GameItem *itm) {
        this->ui->listGames->disconnectAll();
        connect(itm, &GameItem::onStateChange, this, &LauncherMainWindows::updatePrintData);
        updatePrintData(itm);
    });
    QScrollBar *textSb = new QScrollBar(this);
    textSb->setStyleSheet(Cache::getScrollBarStyle());
    this->ui->descriptionText->setVerticalScrollBar(textSb);
    this->ui->gameActionButton->hide();
    _getter.setMaster(QString::fromStdString(_settings["masterUrl"].to<std::string>()));
    _loadMasterData();
}

LauncherMainWindows::~LauncherMainWindows()
{
    delete ui;
}

void LauncherMainWindows::_loadMasterData()
{
    this->ui->listGames->clean();
    this->ui->gameActionButton->setEnabled(true);
    this->ui->gameActionButton->hide();
    this->ui->downloadProgress->setValue(0);
    this->ui->descriptionText->setHtml("");
    _getter.loadMaster([this] (json::Entity const &data) {
        auto    games = const_cast<json::Entity&>(data)["games"];

        if (games.isArray() == false) {
            return;
        } else {
            for (auto &game : games.getData<json::Array>().get()) {
                try {
                    if (game["name"].isString()) {
                        this->ui->listGames->addWidget(new GameItem(game, this));
                    }
                } catch (std::exception &e) {
                    QMessageBox::critical(this, "Error", e.what());
                }
            }
        }
    }, [this] () {
        QMessageBox::critical(this, "Error", "Cannot get master data at:\n"
                              + this->_getter.getMaster());
    });
}

void LauncherMainWindows::_getSettings(void)
{
    QDir    dataDir(Cache::getDataDirectory());
    QFile   settingsFile(dataDir.absolutePath() + "/settings.json");

    if (settingsFile.exists() == false) {
        dataDir.mkpath(dataDir.absolutePath());
        std::ofstream   stm(settingsFile.fileName().toStdString());
        _settings = json::makeObject {
            {"masterUrl", "https://www.holidev.net/epitech-games-launcher/master.json"}
        };
        stm << _settings;
    } else {
        std::ifstream   stm(settingsFile.fileName().toStdString());
        stm >> _settings;

        if (_settings.isObject() && _settings["window"].isObject())
            _loadWinSettings(_settings["window"]);
    }
}

void    LauncherMainWindows::_loadWinSettings(json::Entity &win)
{
    auto    winPos = win["position"];
    auto    winSize = win["size"];

    if (winPos.isObject()) {
        this->move(winPos["x"].to<int>(), winPos["y"].to<int>());
    }
    if (winSize.isObject()) {
        this->resize(winSize["w"].to<int>(), winSize["h"].to<int>());
    }
}

void LauncherMainWindows::_saveSettings()
{
    QDir    dataDir(Cache::getDataDirectory());
    QString settingsFile(dataDir.absolutePath() + "/settings.json");
    std::ofstream   stm(settingsFile.toStdString());

    stm << _settings;
}

void LauncherMainWindows::closeEvent(QCloseEvent *)
{
    auto winSettings = json::Entity::newObject();

    winSettings["position"] = json::makeObject {
        {"x", this->pos().x()},
        {"y", this->pos().y()}
    };
    winSettings["size"] = json::makeObject {
        {"w", this->width()},
        {"h", this->height()}
    };
    _settings["window"] = winSettings;
    _saveSettings();
}

void LauncherMainWindows::updatePrintData(GameItem *selected)
{
    this->ui->gameActionButton->setText(selected->buttonText);
    this->ui->descriptionText->setHtml(selected->descriptionHtml);
    this->ui->downloadProgress->setValue(selected->progress);
    if (selected->error == true) {
        this->ui->downloadProgress->setStyleSheet("background-color: #FF0000");
        this->ui->downloadProgress->setFormat(selected->stateMessage);
        this->ui->gameActionButton->setEnabled(false);
        return;
    }
    this->ui->gameActionButton->setEnabled(true);
    this->ui->downloadProgress->setStyleSheet("");
    if (selected->checkingFiles) {
        this->ui->gameActionButton->hide();
        this->ui->downloadProgress->setFormat("Checking metadata...");
    } else {
        if (!this->ui->gameActionButton->isVisible())
            this->ui->gameActionButton->show();
        if (selected->ready) {
            this->ui->downloadProgress->setFormat("Ready");
            this->ui->gameActionButton->setText("Play");
            this->ui->gameActionButton->setEnabled(true);
        } else {
            if (selected->progress)
                this->ui->gameActionButton->setEnabled(false);
            this->ui->downloadProgress->setFormat(selected->progress > 0
                                                    ? "%p% (" + selected->speed + ")"
                                                    : "%p%");
        }
    }
}
