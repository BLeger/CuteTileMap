#include "Player.h"

Player::Player(QPoint viewSize) : QGraphicsRectItem(nullptr), m_viewSize(viewSize)
{
    setRect(0, 0, 50, 50);
    m_worldPosition = {100, 100};
}

void Player::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Left){
        m_leftPressed = true;
    } else if (event->key() == Qt::Key_Right){
        m_rightPressed = true;
    }

    if (event->key() == Qt::Key_Up){
        m_upPressed = true;
    }
}

void Player::keyReleaseEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Left){
        m_leftPressed = false;
    } else if (event->key() == Qt::Key_Right){
        m_rightPressed = false;
    }

    if (event->key() == Qt::Key_Up){
        m_upPressed = false;
    }
}

QRectF Player::boundingRect() const
{
    return QRectF(0, 0, 20, 30);
}

void Player::paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget)
{
    painter->fillRect(QRectF{0, 0, 20, 30}, Qt::red);
}

void Player::update(bool leftTile, bool rightTile, bool downTile)
{
    // Calculate velocity
    float velocityX = m_velocity.x();

    if (m_leftPressed && !leftTile){
        if (velocityX == 0) velocityX -= 0.5;
        velocityX -= 1;
    } else if (m_rightPressed && !rightTile){
        if (velocityX == 0) velocityX += 0.5;
        velocityX += 1;
    } else {
        // If no movement on x axis, slow down
        if (velocityX > 0) {
            if (velocityX > 0.1) velocityX -= 0.1;
            else velocityX = 0;
        } else if (velocityX < 0){
            if (velocityX < -0.1) velocityX += 0.1;
            else velocityX = 0;
        }
    }

    // Jump
    if (m_upPressed && m_jumpAvailable){
        m_velocity.setY(-10);
        m_worldPosition.setY(m_worldPosition.y() - 2);
        m_upPressed = false;
        setJumpAvailable(false);
    }

    // Gravity
    if (!downTile) {
        m_velocity.setY(m_velocity.y() + 1);
    }

    // Enforce maximum velocity
    if (velocityX > 3) velocityX = 3;
    if (velocityX < -3) velocityX = -3;

    if (m_velocity.y() > 3) m_velocity.setY(3);

    m_velocity.setX(velocityX);

    // Calculate world position
    m_worldPosition.setX(m_worldPosition.x() + m_velocity.x());
    m_worldPosition.setY(m_worldPosition.y() + m_velocity.y());

    // Calculate display position
    int displayXPosition;
    if (m_worldPosition.x() < (m_viewSize.x() / 2)) {
        displayXPosition = m_worldPosition.x();
    } else {
        displayXPosition = m_viewSize.x() / 2;
    }

    setPos(displayXPosition, m_worldPosition.y());
}

void Player::correctCollision(QPoint correction)
{
    if (correction.x() != 0) {
        m_velocity.setX(0);
        m_worldPosition.setX(m_worldPosition.x() + correction.x());
    }

    if (correction.y() != 0) {
        m_velocity.setY(0);
        m_worldPosition.setY(m_worldPosition.y() + correction.y());
    }
}
