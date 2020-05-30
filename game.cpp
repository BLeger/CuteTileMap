#include "Game.h"

Game::Game(TileSet& tileset, QWidget *parent): QGraphicsView(parent), m_tilemap(tileset, ":/map.json", {800, 20}), m_player({800, 20})
{
    connect(&m_timer, SIGNAL(timeout()), this, SLOT(update()));
    m_timer.start(16);

    m_scene.addItem(&m_player);
    m_scene.setSceneRect(0, 0, 800, 600);
    m_scene.addItem(&m_tilemap);
    setScene(&m_scene);

    m_player.setFlag(QGraphicsItem::ItemIsFocusable);
    m_player.setFocus();

    setBackgroundBrush(QBrush(QColor::fromRgb(162, 216, 255)));
}

void Game::update() {
    QGraphicsItem *itemUnder = itemAt({(int) m_player.pos().x(), (int) (m_player.pos().y() + m_player.boundingRect().height() + 2)});
    if (itemUnder != nullptr && itemUnder->parentItem() == &m_tilemap) {
        m_player.setHasGroundUnder(true);
    } else {
        m_player.setHasGroundUnder(false);
    }

    m_player.focusItem();
    m_player.update();

    for(auto item : m_player.collidingItems()) {
        if (item->parentItem() == &m_tilemap) {
            Tile* tile = (Tile*) item;
            if (tile->hasCollision()) {
                CollisionHandler::playerTile(&m_player, tile, m_tilemap.getOffsetX());
                //tile->enable("air");
            }
            //qDebug() << tile;

        }

    }

    m_tilemap.update();
    m_tilemap.updatePlayerPosition(m_player.getWorldPosition());
}
