#ifndef LISTGAMEITEM_H
#define LISTGAMEITEM_H

#include <QVBoxLayout>
#include <QScrollArea>
#include <QScrollBar>
#include "gameitem.h"

class ListGameItem : public QScrollArea
{
    Q_OBJECT
public:
    explicit ListGameItem(QWidget *parent = nullptr);
    ~ListGameItem();

    void        addWidget(GameItem *);
    GameItem    *getSelectedItem(void);
    void        disconnectAll(void);
    void        clean(void);

private:
    QList<GameItem*>    _items;
    QWidget             *_frame = nullptr;
    QVBoxLayout         *_lay = nullptr;
    QScrollBar          *_hb = nullptr;
    GameItem            *_selected = nullptr;

    void _resizeFrame(void);

signals:
    void    onSelectChange(GameItem *itm);

private slots:
    void    onItemIsSelected(GameItem *itmptr, bool selected);
};

#endif // LISTGAMEITEM_H
