#include "Game.h"

Game::Game(QWidget *parent): QGraphicsView(parent), m_tilemap(QPointF{3, 3})
{
    connect(&m_timer, SIGNAL(timeout()), this, SLOT(update()));
    m_timer.start(1000);

    m_scene.setSceneRect(0, 0, 800, 600);
    m_scene.addItem(&m_tilemap);
    //scene->addItem(&tile);
    setScene(&m_scene);
}

void Game::update() {
    m_tilemap.updatePosition();
}
