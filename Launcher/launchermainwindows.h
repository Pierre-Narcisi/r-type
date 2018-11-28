#ifndef LAUNCHERMAINWINDOWS_H
#define LAUNCHERMAINWINDOWS_H

#include <QMainWindow>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QKeyEvent>
#include "Json/Entity.hpp"
#include "mastergetter.h"
#include "gameitem.h"
#include "resoucesdownloader.h"

namespace Ui {
class LauncherMainWindows;
}

class LauncherMainWindows : public QMainWindow
{
    Q_OBJECT

public:
    explicit LauncherMainWindows(QWidget *parent = 0);
    ~LauncherMainWindows();

private:
    void    _loadMasterData(void);
    void    _getSettings(void);
    void    _saveSettings(void);
    void    _loadWinSettings(json::Entity &win);

    void    closeEvent(QCloseEvent *event);

    Ui::LauncherMainWindows *ui;
    json::Entity            _settings;
    MasterGetter            _getter;

public slots:
    void    updatePrintData(GameItem *);
};

#endif // LAUNCHERMAINWINDOWS_H
