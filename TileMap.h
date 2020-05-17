#ifndef TILEMAP_H
#define TILEMAP_H

#include <QVector>
#include <QGraphicsItemGroup>
#include <QDebug>
#include "Tile.h"

class TileMap : public QGraphicsItemGroup {

public:
    TileMap(QPointF size);

    void updatePosition();


private:
    QPointF m_size;
    QVector<Tile*> m_tiles;

    bool tileExists(QPointF position);
    Tile& getTile(QPointF position);
    bool tileEnabled(QPointF position);

    void enableTile(QPointF position);
    void disableTile(QPointF position);
};

#endif // TILEMAP_H
