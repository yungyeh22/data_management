#ifndef SERIALIZABLEOBJ_H
#define SERIALIZABLEOBJ_H

#include <QMap>
#include <QString>
#include "SerializeCore.h"
#include "SerializableObj2.h"

class SerializableObj : public Serialization::ISerializable, public Serialization::ISerializableContainer
{
public:
    SerializableObj(){;}
    setValue(double _val) {_number = _val;}
    double number() {return _number;}
    bool useTool() { return _useTool;}
    SerializableObj2* otherObj() {return &_obj;}
    // ISerializable Interface

    // Standard de-serialization using universal serializer
    void readFromXml(const QDomNode &node) {Serialization::UniversalSerializer::readComponentsFromNode(node, *this);}
    // Standard serialization using universal serializer
    void writeToXml(QDomNode &node) {Serialization::UniversalSerializer::writeComponentsToNode(node, *this);}

    // ISerializableContainer Interface.
    QMap<QString, Serialization::ObjectToSerialize>* serializeElements() {
        ADD_SERIABLE_OBJECT(valueToSerialize,number,_number);
        ADD_SERIABLE_OBJECT(valueToSerialize,useTool,_useTool);
        ADD_SERIABLE_OBJECT(valueToSerialize,otherObj,_obj);
        return &valueToSerialize;
    }

private:
    QMap<QString, Serialization::ObjectToSerialize> valueToSerialize;    
    double _number;
    bool _useTool = false;
    SerializableObj2 _obj;


};

#endif // SERIALIZABLEOBJ_H
