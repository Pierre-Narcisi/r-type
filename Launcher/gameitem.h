#ifndef GAMEITEM_H
#define GAMEITEM_H

#include <QWidget>
#include <QNetworkAccessManager>
#include "Json/Entity.hpp"
#include "resoucesdownloader.h"
#include "hashchecker.h"

namespace Ui {
class GameItem;
}

class GameItem : public QWidget
{
    Q_OBJECT
public:
    explicit GameItem(json::Entity &item, QWidget *parent);
    ~GameItem();

    json::Entity    getDataSheet(void);
    void            select(void);
    void            unSelect(void);
    void            actionClicked(void);
signals:
    void    onStateChange(GameItem *me);
    void    onSelectChange(GameItem *me, bool selected);

public:
    QString stateMessage;
    QString buttonText;
    QString speed;
    QString descriptionHtml;
    bool    error;
    int     progress;
    bool    checkingFiles;
    bool    ready;

private slots:
    void    _onHashComplete(json::Entity data);
    void    _onDownloadProgress(int, qint64);
    void    _onDownloadEnd();
    void    _onDownloadFailed();

private:
    inline void _checkSettingsFile(void);
    void        _initDownloader(void);
    void        _initIcon(void);
    void        _initDesc(void);
    virtual void    paintEvent(QPaintEvent *) final;
    virtual void    mousePressEvent(QMouseEvent *event) final;
    virtual void	showEvent(QShowEvent *event) final;

    json::Entity            _data;
    json::Entity            _checkedData;
    QNetworkAccessManager   *_manager;
    ResoucesDownloader      *_rscDler;
    QNetworkReply           *_iconReply;
    QNetworkReply           *_descReply;
    HashChecker             *_checker;
    Ui::GameItem            *ui;
};

#endif // GAMEITEM_H
