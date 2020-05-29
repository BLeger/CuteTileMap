#ifndef PLAYER_H
#define PLAYER_H

#include <QGraphicsRectItem>
#include <QKeyEvent>
#include <QPointF>
#include <QDebug>
#include <QPainter>

class Player : public QGraphicsRectItem {

public:
    Player(QPoint viewSize);
    void keyPressEvent(QKeyEvent *event);
    QPoint getWorldPosition() { return m_worldPosition; }

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget) override;

    void update();

private:
    QPoint m_viewSize;
    QPoint m_worldPosition; // Position of the player in the world
};

#endif // PLAYER_H
