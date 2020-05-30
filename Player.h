#ifndef PLAYER_H
#define PLAYER_H

#include <QGraphicsRectItem>
#include <QKeyEvent>
#include <QPointF>
#include <QDebug>
#include <QPainter>

#include <algorithm>

class Player : public QGraphicsRectItem {

public:
    Player(QPoint viewSize);
    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;
    QPoint getWorldPosition() { return m_worldPosition; }

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget) override;

    void update(bool leftTile, bool rightTile, bool downTile);
    void correctCollision(QPoint correction);
    void setJumpAvailable(bool available) { m_jumpAvailable = available; }

private:
    QPointF m_velocity;
    QPoint m_viewSize;
    QPoint m_worldPosition; // Position of the player in the world

    bool m_jumpAvailable = false;

    bool m_leftPressed = false;
    bool m_rightPressed = false;
    bool m_upPressed = false;
};

#endif // PLAYER_H
