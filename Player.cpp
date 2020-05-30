#include "Player.h"

Player::Player(QPoint viewSize) : QGraphicsRectItem(nullptr), m_viewSize(viewSize)
{
    setRect(0, 0, 50, 50);
    m_worldPosition = {100, 100};
}

void Player::keyPressEvent(QKeyEvent *event)
{
    float velocityX = m_velocity.x();
    float velocityY = m_velocity.y();

    bool xAxisPressed = false;

    if (event->key() == Qt::Key_Left){
        if (velocityX == 0) velocityX -= 0.5;
        velocityX -= 1;
        xAxisPressed = true;
    } else if (event->key() == Qt::Key_Right){
        if (velocityX == 0) velocityX += 0.5;
        velocityX += 1;
        xAxisPressed = true;
    }

    m_xAxisPressed = xAxisPressed;
    if (velocityX > 3) velocityX = 3;
    if (velocityX < -3) velocityX = -3;

    m_velocity.setX(velocityX);

    if (event->key() == Qt::Key_Up && m_jumpAvailable){
        m_velocity.setY(-10);
        m_worldPosition.setY(m_worldPosition.y() - 2);
        setJumpAvailable(false);
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

void Player::update()
{
    float velocityX = m_velocity.x();

    if (!m_xAxisPressed) {
        if (velocityX > 0) {
            if (velocityX > 0.1) velocityX -= 0.1;
            else velocityX = 0;
        } else if (velocityX < 0){
            if (velocityX < -0.1) velocityX += 0.1;
            else velocityX = 0;
        }
    }

    m_xAxisPressed = false;
    //qDebug() << m_velocity.y();
    m_velocity.setX(velocityX);
    if (!m_hasGroundUnder) {
        m_velocity.setY(m_velocity.y() + 1);
    }

    if (m_velocity.y() > 3) m_velocity.setY(3);

    /*if (m_velocity.y() == 0) {
        setJumpAvailable(true);
    } else {
        setJumpAvailable(false);
    }*/

    float newXPos = m_worldPosition.x();
    m_worldPosition.setX(newXPos + m_velocity.x());

    float newYPos = m_worldPosition.y();
    m_worldPosition.setY(newYPos + m_velocity.y());

    int newX = m_viewSize.x() / 2;
    if (newX < 0) newX = 0;

    if (m_worldPosition.x() < (m_viewSize.x() / 2)) {
        newX = m_worldPosition.x();
    }

    setPos(newX, newYPos);
}

void Player::correctCollision(QPoint correction)
{
    if (correction.x() != 0) {
        m_velocity.setX(0);
        m_worldPosition.setX(m_worldPosition.x() + correction.x());
    }

    if (correction.y() != 0) {
        qDebug() << "Correct y !";
        m_velocity.setY(0);
        m_worldPosition.setY(m_worldPosition.y() + correction.y());
    }

    update();
}
