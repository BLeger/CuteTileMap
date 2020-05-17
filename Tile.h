#ifndef TILE_H
#define TILE_H

#include <QGraphicsItem>
#include <QPainter>
#include <QPointF>

class Tile : public QGraphicsItem
{
public:
    Tile(QPointF position, QPointF tileSize);

    QRectF boundingRect() const override;
    QPainterPath shape() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget) override;

    void enable() { m_enabled = true; };
    void disable() { m_enabled = false; }
    bool isEnabled() { return m_enabled; }
private:
    QPointF m_position;
    QPointF m_tileSize;

    bool m_enabled = false;
};

#endif // TILE_H
