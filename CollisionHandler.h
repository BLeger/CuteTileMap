#ifndef COLLISIONHANDLER_H
#define COLLISIONHANDLER_H

#include <QRectF>
#include <QPointF>
#include <QGraphicsItem>

#include "Player.h"
#include "Tile.h"


class CollisionHandler {

public:
    static void playerTile(Player* player, Tile* tile, int mapOffset);

private:
    struct RectPoints {
        QPointF topLeft;
        QPointF topRight;
        QPointF bottomLeft;
        QPointF bottomRight;
        QPointF center;
    };

    enum Directions {
        Left, Right,
        Bottom, Top
    };


    static RectPoints getPoints(QGraphicsItem *item, int offset = 0);

};

#endif // COLLISIONHANDLER_H
