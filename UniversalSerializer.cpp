#include "UniversalSerializer.h"

#include <QMap>
#include <QDomElement>
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
            if (vars->contains(tagName) && dataType == QString::fromStdString((*vars)[tagName].typeAsString())) {
                if ((dataType == QString::fromStdString(ObjectMgmt::kSerializable))) {
                    qDebug() << itemElement.text();
                    (*vars)[tagName].serializableItem()->readFromXml(item);
                }
                else {
                    QString itemValue = itemElement.text();
                    ObjectMgmt::Value value(itemValue.toStdString());
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
            }
            else {
                result &= false;
                qDebug() << "Failed to assign the tagName:" << tagName << "to an object in a serializable class";
            }
            item = item.nextSibling();
        }
    }
    return result;
}

}
