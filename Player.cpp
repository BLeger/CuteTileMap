#include "Player.h"

Player::Player(QPoint viewSize) : QGraphicsRectItem(nullptr), m_viewSize(viewSize)
{
    setRect(0, 0, 50, 50);
    setPos(0, 170);
}

void Player::keyPressEvent(QKeyEvent *event)
{
    float newX = m_worldPosition.x();
    float newY = m_worldPosition.y();

    if (event->key() == Qt::Key_Left){
        newX -= 5;
    }
    else if (event->key() == Qt::Key_Right){
        newX += 5;
    }

    if (event->key() == Qt::Key_Down){
        newY += 5;
    }
    else if (event->key() == Qt::Key_Up){
        newY -= 5;
    }

    if (newX < 0) newX = 0;
    if (newY < 0) newY = 0;

    m_worldPosition.setX(newX);
    m_worldPosition.setY(newY);
}

QRectF Player::boundingRect() const
{
    return QRectF(0, 0, 10, 10);
}

void Player::paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget)
{
    painter->fillRect(QRectF{0, 0, 10, 10}, Qt::red);
}

void Player::update()
{
    int newX = m_viewSize.x() / 2;

    if (m_worldPosition.x() < (m_viewSize.x() / 2)) {
        newX = m_worldPosition.x();
    }

    setPos(newX, m_worldPosition.y());
}
