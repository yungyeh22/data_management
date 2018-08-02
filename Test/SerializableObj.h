#ifndef SERIALIZABLEOBJ_H
#define SERIALIZABLEOBJ_H

#include <QMap>
#include <QString>
#include "ObjectMgmt/Value.h"
#include "SerializeCore.h"
#include "SerializableObj2.h"

class SerializableObj : public Serialization::ISerializable, public Serialization::ISerializableContainer
{
public:
    SerializableObj(){;}
    void setValue(double _val) {_number = _val;}
    double number() {return _number;}
    bool useTool() { return _useTool;}
    ObjectMgmt::Value doubleValue() { return _doubleValue;}
    SerializableObj2* otherObj() {return &_obj;}

private:

    double _number;
    bool _useTool = false;
    SerializableObj2 _obj;
    ObjectMgmt::Value _doubleValue = 1.23456;

    // Standard ISerializable Interface
    STANDARD_SERIALIZABLE(valueToSerialize,
        {"number",&_number},
        {"useTool",&_useTool},
        {"otherObj",&_obj},
        {"myValue",&_doubleValue})

};

#endif // SERIALIZABLEOBJ_H
