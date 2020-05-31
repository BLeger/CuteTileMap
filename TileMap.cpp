#include "TileMap.h"

TileMap::TileMap(TileSet* tileset) :
    m_size({0, 0}), m_tileSize(tileset->getTileSize()), m_tileset(tileset)
{}

TileMap::TileMap(TileSet *tileset, QJsonObject map) :
    m_tileSize(tileset->getTileSize()), m_tileset(tileset)
{
    // Read json file
    /*QFile file;
    file.setFileName(mapDescriptorPath);
    file.open(QIODevice::ReadOnly | QIODevice::Text);

    QString val = file.readAll();
    QJsonDocument document = QJsonDocument::fromJson(val.toUtf8());
    QJsonObject mainObject = document.object();*/

    loadMap(map);
}

void TileMap::loadMap(QJsonObject map)
{
    // Read map size
    QJsonObject size = map["size"].toObject();
    m_size = {size["x"].toInt(), size["y"].toInt()};

    // Create tiles
    for (float y = 0.f; y < m_size.y(); y++) {
        for (float x = 0.f; x < m_size.x(); x++) {
            m_tiles.push_back(new Tile {QPointF{x * m_tileSize.x(), y * m_tileSize.y()}, *m_tileset});
        }
    }

    // Read tiles
    QJsonArray tiles = map["map"].toArray();

    for (auto tileInfoRef : tiles) {
        QJsonObject tileInfo = tileInfoRef.toObject();

        // Read the position of the tile
        QJsonObject positionObject = tileInfo["position"].toObject();
        QPoint position {positionObject["x"].toInt(), positionObject["y"].toInt()};

        // Tilename
        QString tileName = tileInfo["tile"].toString();

        enableTile(position, tileName);
    }
}

bool TileMap::tileExists(QPointF position)
{
    return position.x() >= 0 && position.y() >= 0 && position.x() < m_size.x() && position.y() < m_size.y();
}

Tile &TileMap::getTile(QPointF position)
{
    assert(tileExists(position));
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

void TileMap::disableAll()
{
    for (float y = 0.f; y < m_size.y(); y++) {
        for (float x = 0.f; x < m_size.x(); x++) {
            disableTile({x, y});
        }
    }
}
