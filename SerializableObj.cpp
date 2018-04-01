#include "SerializableObj.h"

SerializableObj::SerializableObj() {
}

SerializableObj::setValue(double _val)
{
    _number = _val;
}

void SerializableObj::readFromXml(const QDomNode &node) {
    Serialization::UniversalSerializer::readComponentsFromNode(node, *this); // Generic means for read
}

void SerializableObj::writeToXml(QDomNode &node) {
    Serialization::UniversalSerializer::writeComponentsToNode(node, *this); // Generic means for write
}

QMap<QString, ObjectMgmt::Value *>* SerializableObj::serializeElements() {
    valueToSerialize["number"] = &_number;
    return &valueToSerialize;
}

