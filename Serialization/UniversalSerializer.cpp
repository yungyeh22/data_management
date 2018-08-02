#include "UniversalSerializer.h"

#include <QMap>
#include <QDomElement>
#include <QDomDocument>
#include <QDebug>
#include "ObjectMgmt/Value.h"

namespace Serialization {

bool UniversalSerializer::writeComponentsToNode(QDomNode &node, ISerializableContainer &container) {
    bool result = true;
    const QMap<QString, Serialization::ObjectToSerialize>* vars = container.serializeElements();
    if (vars->size() == 0) {
        qDebug() << "Nothing to be serialized!";
        result &= false;
        return result;
    }
    for (auto tagName : vars->keys()) {
        QDomDocument document;
        QDomElement item = document.createElement(tagName);
        item.setAttribute("datatype", QString::fromStdString((*vars)[tagName].typeAsString()));
        if ((*vars)[tagName].type() == ObjectToSerialize::TYPE::SERIALIZABLE) { // Serializable objects
            (*vars)[tagName].serializableItem()->writeToXml(item);
        }
        else { // Primitive type
            ObjectMgmt::Value value;
            switch((*vars)[tagName].type()) {
            case ObjectToSerialize::TYPE::DOUBLE:
            {
                value = *(*vars)[tagName].doubleItem();
                break;
            }
            case ObjectToSerialize::TYPE::INT:
            {
                value= *(*vars)[tagName].intItem();
                break;
            }
            case ObjectToSerialize::TYPE::BOOL:
            {
                value = *(*vars)[tagName].boolItem();
                break;
            }
            case ObjectToSerialize::TYPE::STRING:
            {
                value = *(*vars)[tagName].stringItem();
                break;
            }
            default:
            {
                break;
            }
            }
            item.appendChild(document.createTextNode(QString::fromStdString(value.stringValue())));
        }
        node.appendChild(item);
    }
    return result;
}

bool UniversalSerializer::readComponentsFromNode(const QDomNode &node, ISerializableContainer &container) {
    bool result = true;
    QMap<QString, Serialization::ObjectToSerialize>* vars = container.serializeElements();
    if (node.toElement().attribute("datatype") == QString::fromStdString(ObjectMgmt::kSerializable)) {
        QDomNode item = node.firstChild();
        while (!item.isNull()) {
            QDomElement itemElement = item.toElement();
            QString tagName = itemElement.tagName();
            QString dataType = itemElement.attribute("datatype");
            if (vars->contains(tagName) && dataType == QString::fromStdString((*vars)[tagName].typeAsString())) {
                if ((dataType == QString::fromStdString(ObjectMgmt::kSerializable))) {
                    (*vars)[tagName].serializableItem()->readFromXml(item);
                }
                else {
                    QString itemValue = itemElement.text();
                    ObjectMgmt::Value value(itemValue.toStdString());
                    switch((*vars)[tagName].type()) {
                    case ObjectToSerialize::TYPE::DOUBLE:
                    {
                        *(*vars)[tagName].doubleItem() = value.doubleValue();
                        break;
                    }
                    case ObjectToSerialize::TYPE::INT:
                    {
                        *(*vars)[tagName].intItem() = value.intValue();
                        break;
                    }
                    case ObjectToSerialize::TYPE::BOOL:
                    {
                        *(*vars)[tagName].boolItem() = value.boolValue();
                        break;
                    }
                    case ObjectToSerialize::TYPE::STRING:
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
