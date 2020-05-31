#include "Game.h"

Game::Game(TileSet& tileset, QWidget *parent): QGraphicsView(parent), m_tilemap(&tileset, {800, 20}), m_player({800, 20})
{
    connect(&m_timer, SIGNAL(timeout()), this, SLOT(update()));
    m_timer.start(16);

    // Read map json
    QFile file;
    file.setFileName(":/map.json");
    file.open(QIODevice::ReadOnly | QIODevice::Text);

    QString val = file.readAll();
    QJsonDocument document = QJsonDocument::fromJson(val.toUtf8());
    QJsonObject mainObject = document.object();

    m_tilemap.loadMap(mainObject);



    m_scene.addItem(&m_player);
    m_scene.setSceneRect(0, 0, 800, 600);
    m_scene.addItem(&m_tilemap);
    setScene(&m_scene);

    m_player.setFlag(QGraphicsItem::ItemIsFocusable);
    m_player.setFocus();

    setBackgroundBrush(QBrush(QColor::fromRgb(162, 216, 255)));
}

void Game::update() {
    bool tileUnderPlayer = tileExistsAt({(int) m_player.pos().x(), (int) (m_player.pos().y() + m_player.boundingRect().height() + 2)});
    bool tileRightPlayer = tileExistsAt({(int) (m_player.pos().x() + m_player.boundingRect().width()) + 2, (int) (m_player.pos().y() + m_player.boundingRect().height() - 2)});
    bool tileLeftPlayer = tileExistsAt({(int) (m_player.pos().x() - 2), (int) (m_player.pos().y() + m_player.boundingRect().height() - 2)});

    m_player.focusItem();
    m_player.update(tileLeftPlayer, tileRightPlayer, tileUnderPlayer);

    for(auto item : m_player.collidingItems()) {
        if (Tile* tile = qgraphicsitem_cast<Tile*>(item)) {
            if (tile->hasCollision()) {
                CollisionHandler::playerTile(&m_player, tile, m_tilemap.getOffsetX());
            }
        }
    }

    m_tilemap.update();
    m_tilemap.updatePlayerPosition(m_player.getWorldPosition());
}

bool Game::tileExistsAt(QPoint position)
{
    QGraphicsItem *item = itemAt(position);
    return item != nullptr && qgraphicsitem_cast<Tile*>(item) != nullptr;
}
