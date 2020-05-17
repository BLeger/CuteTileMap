#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QGraphicsView>

#include "Tile.h"
#include "Game.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // add a view to visualize the scene
    Game * view = new Game();

    view->show();
    return a.exec();
}
