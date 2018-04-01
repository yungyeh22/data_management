#include "SerializableObj.h"

SerializableObj::SerializableObj() {
}

SerializableObj::setValue(double _val)
{
    _number = _val;
}

void SerializableObj::readFromXml(const QDomNode &node) {
    Serialization::UniversalSerializer::readComponentsFromNode(node, *this);
}

void SerializableObj::writeToXml(QDomNode &node) {

}

QMap<QString, ObjectMgmt::Value *>* SerializableObj::serializeElements() {
    valueToSerialize["number"] = &_number;
    return &valueToSerialize;
}

