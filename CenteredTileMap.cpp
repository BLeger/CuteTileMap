#include "CenteredTileMap.h"

CenteredTileMap::CenteredTileMap(QPoint size, TileSet &tileset, QPoint viewSize)
    : TileMap(size, tileset), m_viewSize(viewSize)
{

}

CenteredTileMap::CenteredTileMap(TileSet &tileset, QString mapDescriptorPath, QPoint viewSize)
    : TileMap(tileset, mapDescriptorPath), m_viewSize(viewSize)
{
    disableAll();
}

void CenteredTileMap::setViewSize(QPoint viewSize)
{
    m_viewSize = viewSize;
}

void CenteredTileMap::update(QPoint playerPosition)
{
    // Convert player pixel position into tile position
    QPoint tilePlayerPosition {(int) (playerPosition.x() / getTileSize().x()), (int) (playerPosition.y() / getTileSize().y())};

    // Number of tiles that can be displayed horizontaly
    float numberOfTileDisplayX = m_viewSize.x() / getTileSize().x();

    // Number of tiles on each side of the player
    float numberOfTileDisplaySideX = numberOfTileDisplayX / 2;

    // The x position of the tile that will be on the left of the screen
    int leftMostTileX = tilePlayerPosition.x() - numberOfTileDisplaySideX;
    leftMostTileX = std::max(0, leftMostTileX);

    qDebug() << "left most : " << leftMostTileX;

    // The x position of the tile that will be on the right of the screen
    int rightMostTileX = leftMostTileX + numberOfTileDisplayX;
    rightMostTileX = std::min(getSize().x() - 1, rightMostTileX + 1); // +1 to avoid having an empty tile on the right

    qDebug() << "right most : " << rightMostTileX;

    disableAll();
    for (float x = leftMostTileX; x < rightMostTileX; x++) {
        for (float y = 0; y < getSize().y(); y++) {
            enableTile({x, y});
        }
    }

    float offsetX = 0;

    if (leftMostTileX > 0) {
        offsetX = (playerPosition.x() - (m_viewSize.x() / 2)) * -1;
    }

    setPos(offsetX, pos().y());
}
