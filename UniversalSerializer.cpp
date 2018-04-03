#include "UniversalSerializer.h"

#include <QMap>
#include <QDomnodeList>
#include <QDebug>
#include "Value.h"


namespace Serialization {

bool UniversalSerializer::writeComponentsToNode(QDomNode &node, ISerializableContainer &container) {
    bool result = false;
    const QMap<QString, Serialization::ObjectToSerialize>* vars = container.serializeElements();
    return result;
}

bool UniversalSerializer::readComponentsFromNode(const QDomNode &node, ISerializableContainer &container) {
    bool result = true;
    QMap<QString, Serialization::ObjectToSerialize>* vars = container.serializeElements();
    if (node.toElement().attribute("type") == QString::fromStdString(ObjectMgmt::kSerializable)) {
        QDomNode item = node.firstChild();
        while (!item.isNull()) {
            QDomElement itemElement = item.toElement();
            QString tagName = itemElement.tagName();
            QString dataType = itemElement.attribute("type");
            if ((dataType == QString::fromStdString(ObjectMgmt::kSerializable))) {
                (*vars)[tagName].serializableItem()->readFromXml(item);
            }
            else {
                QString tagValue = itemElement.text();
                ObjectMgmt::Value value(tagValue.toStdString());
                if (vars->contains(tagName) && dataType == QString::fromStdString((*vars)[tagName].typeAsString())) {
                    switch((*vars)[tagName].type()) {
                    case (ObjectToSerialize::TYPE::DOUBLE):
                    {
                        *(*vars)[tagName].doubleItem() = value.doubleValue();
                        break;
                    }
                    case (ObjectToSerialize::TYPE::INT):
                    {
                        *(*vars)[tagName].intItem() = value.intValue();
                        break;
                    }
                    case (ObjectToSerialize::TYPE::BOOL):
                    {
                        *(*vars)[tagName].boolItem() = value.boolValue();
                        break;
                    }
                    case (ObjectToSerialize::TYPE::STRING):
                    {
                        *(*vars)[tagName].stringItem() = value.stringValue();
                        break;
                    }
                    default:
                    {
                        break;
                    }
                    }
                }
                else {
                    result &= false;
                    qDebug() << "Failed to assign variable" << tagName << endl;
                }
            }
            item = item.nextSibling();
        }
    }
    return result;
}

}
