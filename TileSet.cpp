#include "TileSet.h"

TileSet::TileSet(QString imagePath, QPointF tileSize, QPoint size, QPointF tileOffset) :
    m_tileSize(tileSize), m_size(size), m_tileOffset(tileOffset)
{
    m_image.load(imagePath);
}

QPointF TileSet::getTileSize()
{
    return m_tileSize;
}

const QImage &TileSet::getImage()
{
    return m_image;
}

QRectF TileSet::getTileRect()
{
    return QRectF{0, 0, m_tileSize.x(), m_tileSize.y()};
}

