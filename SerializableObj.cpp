#include "SerializableObj.h"
#include "UniversalSerializer.h"

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

QMap<QString, Serialization::ObjectToSerialize>* SerializableObj::serializeElements() {
    valueToSerialize["number"] = Serialization::ObjectToSerialize(&_number);
    return &valueToSerialize;
}

