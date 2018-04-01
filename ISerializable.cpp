#include "ISerializable.h"
#include <QMap>
#include <QDomnodeList>
#include "Value.h"
#include <QDebug>

namespace Serialization {

bool UniversalSerializer::writeComponentsToNode(QDomNode &node, const ISerializableContainer &container) {

    return false;
}

bool UniversalSerializer::readComponentsFromNode(const QDomNode &node, ISerializableContainer &container) {
    bool result = true;
    QMap<QString, ObjectMgmt::Value*>* vars = container.serializeElements();
    if (node.toElement().tagName() == "Object") {
        QDomElement objElement = node.firstChildElement();
        while (!objElement.isNull()) {
            QString tagName = objElement.tagName();
            QString dataType = objElement.attribute("type");
            QString tagValue = objElement.text();
            ObjectMgmt::Value value(tagValue.toStdString());
            qDebug() << tagName << ":" << QString::fromStdString(value.stringValue());
            value.changeType(dataType.toStdString());
            if (vars->contains(tagName)) {
                (*vars)[tagName]->setValue(value);
                result &= true;
            }
            else {
                result &= false;
                qDebug() << "Failed to assign variable" << tagName << endl;
            }
            objElement = objElement.nextSibling().toElement();
        }
    }
    return result;
}

}
