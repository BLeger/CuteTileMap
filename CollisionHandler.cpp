#include "CollisionHandler.h"

void CollisionHandler::playerTile(Player *player, Tile *tile, int mapOffset)
{
    RectPoints playerPoints = getPoints(player);

    RectPoints tilePoints = getPoints(tile, mapOffset);

    //qDebug() << "Collision ======================";
    //qDebug() << playerWorldBound;

    // For both axis get the side the player is comming from
    // And the value of "penetration"
    Directions horizontalSide;
    float horizontalValue;
    if (playerPoints.topRight.x() <= tilePoints.center.x()) {
        horizontalSide = Directions::Left;
        horizontalValue = playerPoints.topRight.x() - tilePoints.topLeft.x();
    } else {
        horizontalSide = Directions::Right;
        horizontalValue = tilePoints.topRight.x() - playerPoints.topLeft.x();
    }

    Directions verticalSide;
    float verticalValue;
    if (playerPoints.bottomRight.y() <= tilePoints.center.y()) {
        verticalSide = Directions::Top;
        player->setJumpAvailable(true);
        verticalValue = playerPoints.bottomRight.y() - tilePoints.topRight.y();
    } else {
        verticalSide = Directions::Bottom;

        verticalValue = tilePoints.bottomRight.y() - playerPoints.topRight.y();
    }

    if (verticalValue < horizontalValue) {
        // Move the player on the vertical axis
        if (verticalSide == Directions::Top) {
            verticalValue *= -1;
        }

        player->correctCollision({0, (int) verticalValue});
    } else {
        // Move the player on the horizontal axis
        if (horizontalSide == Directions::Left) {
            horizontalValue *= -1;
        }

        player->correctCollision({(int) horizontalValue, 0});
    }

    // Horizontal collisions

    /*qDebug() << tilePoints.topRight.x() << " - " << tilePoints.center.x();
    if (playerPoints.topRight.x() > tilePoints.topLeft.x() && playerPoints.topRight.x() <= tilePoints.center.x()) {
        // Collision on the left of the tile => move player to the left
        //player->correctCollision({-10, 0});
        qDebug() << "Correct left";

    } else if (playerPoints.topLeft.x() < tilePoints.topRight.x() && playerPoints.topLeft.x() >= tilePoints.center.x()) {
        // Collision on the right of the tile
    }*/

}

CollisionHandler::RectPoints CollisionHandler::getPoints(QGraphicsItem *item, int offset)
{
    RectPoints points;

    QRectF rect = item->boundingRect();

    points.topLeft = {rect.x() + item->pos().x() + offset, rect.y() + item->pos().y()};
    points.topRight = {points.topLeft.x() + rect.width(), points.topLeft.y()};
    points.bottomLeft = {points.topLeft.x(), rect.y() + rect.height()};
    points.bottomRight = {points.topLeft.x() + rect.width(), points.topLeft.y() + rect.height()};
    points.center = {points.topLeft.x() + (rect.width() / 2), points.topLeft.y() + (rect.height() / 2)};

    return points;
}
