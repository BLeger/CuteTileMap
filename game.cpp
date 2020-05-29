#include "Game.h"

Game::Game(TileSet& tileset, QWidget *parent): QGraphicsView(parent), m_tilemap(tileset, ":/map.json", {800, 20}), m_player({800, 20})
{
    connect(&m_timer, SIGNAL(timeout()), this, SLOT(update()));
    m_timer.start(16);

    m_scene.setSceneRect(0, 0, 800, 600);
    m_scene.addItem(&m_tilemap);
    setScene(&m_scene);

    m_player.setFlag(QGraphicsItem::ItemIsFocusable);
    m_player.setFocus();

    m_scene.addItem(&m_player);
}

void Game::update() {
    m_player.update();

    for(auto item : m_player.collidingItems()) {
        if (item->parentItem() == &m_tilemap) {
            Tile* tile = (Tile*) item;
            if (tile->hasCollision()) {
                tile->enable("air");
                qDebug() << "test";
            }
            //qDebug() << tile;

        }

    }
    m_tilemap.update();
    m_tilemap.updatePlayerPosition(m_player.getWorldPosition());
}
