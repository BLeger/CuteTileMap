#include "TileMap.h"

TileMap::TileMap(QPointF size) : m_size(size) {
    QPointF tileSize {100, 100};

    for (float x = 0.f; x < size.x(); x++) {
        for (float y = 0.f; y < size.y(); y++) {
            m_tiles.push_back(new Tile {QPointF{x * 100, y * 100}, tileSize});
            enableTile({x, y});
        }
    }

    disableTile(QPointF{1, 1});
}

void TileMap::updatePosition()
{
    return;
    QPointF tileSize {100, 100};
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
    return *m_tiles[position.x() * m_size.x() + position.y()];
}

void TileMap::enableTile(QPointF position)
{
    Tile& tile = getTile(position);

    if (!tile.isEnabled()) {
        addToGroup(&tile);
        tile.enable();
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
