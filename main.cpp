#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QGraphicsView>

#include "Tile.h"
#include "Game.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    TileSet tileset {":/tileset.json"};
    // add a view to visualize the scene
    Game * view = new Game(tileset);

    view->show();
    return a.exec();
}
