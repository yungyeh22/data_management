#include "UniversalSerializer.h"

#include <QMap>
#include <QDomnodeList>
#include <QDebug>
#include "Value.h"


namespace Serialization {

bool UniversalSerializer::writeComponentsToNode(QDomNode &node, const ISerializableContainer &container) {

    return false;
}

bool UniversalSerializer::readComponentsFromNode(const QDomNode &node, ISerializableContainer &container) {
    bool result = true;
    QMap<QString, Serialization::ObjectToSerialize>* vars = container.serializeElements();
    if (node.toElement().tagName() == "Object") {
        QDomElement objElement = node.firstChildElement();
        while (!objElement.isNull()) {
            QString tagName = objElement.tagName();
            QString dataType = objElement.attribute("type");
            QString tagValue = objElement.text();
            ObjectMgmt::Value value(tagValue.toStdString());
            qDebug() << tagName << ":" << tagValue;
            if (vars->contains(tagName)) {
                value.changeType(dataType.toStdString());
                if ((*vars)[tagName].type() == Serialization::ObjectToSerialize::TYPE::DOUBLE) {
                    *(*vars)[tagName].doubleItem() = value.doubleValue();
                }
                else {

                }
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
