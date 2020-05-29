#ifndef CENTEREDTILEMAP_H
#define CENTEREDTILEMAP_H

#include "TileMap.h"

class CenteredTileMap : public TileMap {

public:
    CenteredTileMap(QPoint size, TileSet& tileset, QPoint viewSize);
    CenteredTileMap(TileSet& tileset, QString mapDescriptorPath, QPoint viewSize);

    void setViewSize(QPoint viewSize);
    void updatePlayerPosition(QPoint playerPosition);

private:
    QPoint m_viewSize;
};

#endif // CENTEREDTILEMAP_H
