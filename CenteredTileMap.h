#ifndef CENTEREDTILEMAP_H
#define CENTEREDTILEMAP_H

#include "TileMap.h"

class CenteredTileMap : public TileMap {

public:
    CenteredTileMap(TileSet* tileset, QPoint viewSize);
    CenteredTileMap(TileSet* tileset, QJsonObject map, QPoint viewSize);

    void setViewSize(QPoint viewSize);
    void updatePlayerPosition(QPoint playerPosition);
    float getOffsetX() { return m_offsetX; }

private:
    QPoint m_viewSize;
    float m_offsetX;
};

#endif // CENTEREDTILEMAP_H
