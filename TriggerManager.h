#ifndef TRIGGERMANAGER_H
#define TRIGGERMANAGER_H

#include <QJsonArray>
#include <QJsonObject>
#include <QPoint>
#include <QVector>

class TriggerManager {

public:
    enum TriggerType {
        Win,
        Loose,
        ChangeTile
    };

    struct TriggerDescriptor {
        TriggerType type;
        QString name;
        QPoint effectPosition;
    };

public:
    TriggerManager(QJsonArray triggerList);
    bool triggerExists(QString name);
    TriggerDescriptor& getDescriptor(QString name);

private:
    QVector<TriggerDescriptor> m_descriptors;
};

#endif // TRIGGERMANAGER_H
