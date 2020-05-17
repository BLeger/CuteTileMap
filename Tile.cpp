#include "Tile.h"

Tile::Tile(QPointF position, TileSet& tileset) : m_position(position), m_tileSize(tileset.getTileSize()), m_tileset(tileset)
{
    setPos(position);
}

QRectF Tile::boundingRect() const
{
    return QRectF(0, 0, m_tileSize.x(), m_tileSize.y());
}

QPainterPath Tile::shape() const
{
    QPainterPath path;
    path.addRect(0, 0, m_tileSize.x(), m_tileSize.y());
    return path;
}

void Tile::paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget)
{
    if (!m_enabled) return;
    QImage * image = new QImage(":/tilemap.png");
    image->load(":/tilemap.png");

    QPen pen;
    pen.setColor(Qt::red);
    painter->setPen(pen);
    QBrush brush(Qt::red);
    painter->fillRect(0, 0, m_tileSize.x(), m_tileSize.y(), brush);

    painter->drawImage(QRectF{0, 0, m_tileSize.x(), m_tileSize.y()}, m_tileset.getImage(), m_tileset.getTileRect());
}
