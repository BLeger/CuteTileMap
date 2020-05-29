#include "TriggerManager.h"

TriggerManager::TriggerManager(QJsonArray triggerList)
{
    for (auto triggerObjectValue : triggerList) {
        QJsonObject triggerObject = triggerObjectValue.toObject();

        TriggerDescriptor descriptor;
        QString type = triggerObject["type"].toString();
        bool hasEffectPosition = false;

        if (type == "win") {
            descriptor.type = TriggerType::Win;
        } else if (type == "loose") {
            descriptor.type = TriggerType::Loose;
        } else if (type == "change_tile") {
            descriptor.type = TriggerType::ChangeTile;
            hasEffectPosition = true;
        }

        descriptor.name = triggerObject["name"].toString();

        if (hasEffectPosition) {
            QJsonObject effectPosition = triggerObject["effectPosition"].toObject();
            descriptor.effectPosition = {effectPosition["x"].toInt(), effectPosition["y"].toInt()};
        }

    }
}

bool TriggerManager::triggerExists(QString name)
{
    auto descriptor = std::find_if(m_descriptors.begin(), m_descriptors.end(), [&name](const TriggerDescriptor& value) {
        return value.name == name;
    });

    return descriptor != m_descriptors.end();
}

TriggerManager::TriggerDescriptor &TriggerManager::getDescriptor(QString name)
{
    auto descriptor = std::find_if(m_descriptors.begin(), m_descriptors.end(), [&name](const TriggerDescriptor& value) {
        return value.name == name;
    });

    return *descriptor;
}
