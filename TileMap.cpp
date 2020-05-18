#include "TileMap.h"

TileMap::TileMap(QPoint size, TileSet& tileset) :
    m_size(size), m_tileSize(tileset.getTileSize()), m_tileset(tileset)
{
    for (float y = 0.f; y < size.y(); y++) {
        for (float x = 0.f; x < size.x(); x++) {
            m_tiles.push_back(new Tile {QPointF{x * m_tileSize.x(), y * m_tileSize.y()}, m_tileset});
        }
    }

    for (int i = 0; i < 10; i++) {
        enableTile({(float)i, 0}, "air");
    }

    enableTile({0, 1}, "air");
    enableTile({1, 1}, "grass_left");
    enableTile({2, 1}, "grass_middle");
    enableTile({3, 1}, "grass_middle");
    enableTile({4, 1}, "grass_right");
    enableTile({5, 1}, "air");

    enableTile({0, 2}, "air");
    enableTile({1, 2}, "dirt_left");
    enableTile({2, 2}, "dirt_middle");
    enableTile({3, 2}, "dirt_middle");
    enableTile({4, 2}, "dirt_right");
    enableTile({5, 2}, "air");
}

void TileMap::updatePosition()
{
    return;
    static int counter = 0;
    if (childItems().size() > 0) {
        qDebug() << childItems()[0];
        ((Tile*) childItems()[0])->disable();
        removeFromGroup(childItems()[0]);
        //qDebug() << childItems()[0];

        counter++;
    }
}

bool TileMap::tileExists(QPointF position)
{
    return position.x() >= 0 && position.y() >= 0 && position.x() < m_size.x() && position.y() < m_size.y();
}

Tile &TileMap::getTile(QPointF position)
{
    assert(tileExists(position));
    qDebug() << m_tiles.size();
    return *m_tiles[position.x() + m_size.x() * position.y()];
}

void TileMap::enableTile(QPointF position)
{
    Tile& tile = getTile(position);

    if (!tile.isEnabled()) {
        addToGroup(&tile);
        tile.enable();
    }
}

void TileMap::enableTile(QPointF position, QString descriptorName)
{
    Tile& tile = getTile(position);

    if (!tile.isEnabled()) {
        addToGroup(&tile);
        tile.enable(descriptorName);
    }
}

void TileMap::disableTile(QPointF position)
{
    Tile& tile = getTile(position);

    if (tile.isEnabled()) {
        removeFromGroup(&tile);
        tile.disable();
    }
}
