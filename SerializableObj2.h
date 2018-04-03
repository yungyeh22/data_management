#ifndef SERIALIZABLEOBJ2_H
#define SERIALIZABLEOBJ2_H

#include <QMap>
#include <QString>
#include "SerializeCore.h"

class SerializableObj2 : public Serialization::ISerializable, public Serialization::ISerializableContainer
{
public:
    SerializableObj2(){;}
    setValue(double _val) {_number = _val;}
    double number() {return _number;}
    bool useTool() { return _useTool;}
    // ISerializable Interface

    // Standard de-serialization using universal serializer
    void readFromXml(const QDomNode &node) {Serialization::UniversalSerializer::readComponentsFromNode(node, *this);}
    // Standard serialization using universal serializer
    void writeToXml(QDomNode &node) {Serialization::UniversalSerializer::writeComponentsToNode(node, *this);}

    // ISerializableContainer Interface.
    QMap<QString, Serialization::ObjectToSerialize>* serializeElements() {
        ADD_SERIABLE_OBJECT(valueToSerialize,number,_number);
        ADD_SERIABLE_OBJECT(valueToSerialize,useTool,_useTool);
        return &valueToSerialize;
    }

private:
    QMap<QString, Serialization::ObjectToSerialize> valueToSerialize;
    double _number;
    bool _useTool = false;

};

#endif // SERIALIZABLEOBJ_H
