#ifndef GAME_H
#define GAME_H

#include <QApplication>
#include <QObject>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QGraphicsView>
#include <QTimer>
#include <QDebug>

#include "Tile.h"
#include "TileMap.h"

class Game : public QGraphicsView
{
    Q_OBJECT

public:
    Game(QWidget *parent = 0);

public slots:
    void update();

private:
    QTimer m_timer;
    QGraphicsScene m_scene;
    QGraphicsItemGroup m_group;
    TileMap m_tilemap;
    int counter = 0;
};

#endif // GAME_H
