#ifndef TILEMAP_H
#define TILEMAP_H

#include <QVector>
#include <QGraphicsItemGroup>
#include <QDebug>

#include "TileSet.h"
#include "Tile.h"

class TileMap : public QGraphicsItemGroup {

public:
    TileMap(QPoint size, TileSet& tileset);

    void updatePosition();

    void enableTile(QPointF position);
    void enableTile(QPointF position, QString descriptorName);
    void disableTile(QPointF position);

private:
    QPoint m_size;
    QPointF m_tileSize;
    QVector<Tile*> m_tiles;
    TileSet& m_tileset;

    bool tileExists(QPointF position);
    Tile& getTile(QPointF position);
    bool tileEnabled(QPointF position);
};

#endif // TILEMAP_H
