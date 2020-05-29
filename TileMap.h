#ifndef TILEMAP_H
#define TILEMAP_H

#include <QVector>
#include <QGraphicsItemGroup>
#include <QDebug>

#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

#include "TileSet.h"
#include "Tile.h"

class TileMap : public QGraphicsItemGroup {

public:
    TileMap(QPoint size, TileSet& tileset);
    TileMap(TileSet& tileset, QString mapDescriptorPath);

    void enableTile(QPointF position);
    void enableTile(QPointF position, QString descriptorName);
    void disableTile(QPointF position);
    void disableAll();

    bool tileExists(QPointF position);
    QPointF getTileSize() {return m_tileSize;}
    QPoint getSize() {return m_size;}

protected:
    Tile& getTile(QPointF position);
    bool tileEnabled(QPointF position);

private:
    QPoint m_size;
    QPointF m_tileSize;
    QVector<Tile*> m_tiles;
    TileSet& m_tileset;
};

#endif // TILEMAP_H
