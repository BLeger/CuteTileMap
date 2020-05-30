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
    void correctCollision(QPoint correction);
    void setJumpAvailable(bool available) { m_jumpAvailable = available; }
    void setHasGroundUnder(bool under) { m_hasGroundUnder = under; }

private:
    QPointF m_velocity;
    QPoint m_viewSize;
    QPoint m_worldPosition; // Position of the player in the world

    bool m_xAxisPressed;
    bool m_jumpAvailable = false;
    bool m_hasGroundUnder = false;

    bool m_leftPressed = false;
    bool m_rightPressed = false;
};

#endif // PLAYER_H
