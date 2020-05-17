#ifndef TILESET_H
#define TILESET_H

#include <QString>
#include <QPointF>
#include <QImage>

class TileSet {

public:
    TileSet(QString imagePath, QPointF tileSize, QPoint size, QPointF tileOffset = {0, 0});

    QPointF getTileSize();
    const QImage& getImage();
    QRectF getTileRect();

private:
    QImage m_image;
    QPointF m_tileSize;
    QPoint m_size;
    QPointF m_tileOffset;
};

#endif // TILESET_H
