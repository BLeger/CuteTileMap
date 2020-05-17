#include "Game.h"

Game::Game(TileSet& tileset, QWidget *parent): QGraphicsView(parent), m_tilemap({3, 3}, tileset)
{
    connect(&m_timer, SIGNAL(timeout()), this, SLOT(update()));
    m_timer.start(1000);

    m_scene.setSceneRect(0, 0, 800, 600);
    m_scene.addItem(&m_tilemap);
    setScene(&m_scene);
}

void Game::update() {
    m_tilemap.updatePosition();
}
