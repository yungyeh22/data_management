#ifndef SERIALIZABLEOBJ2_H
#define SERIALIZABLEOBJ2_H

#include <QMap>
#include <QString>
#include "SerializeCore.h"

class SerializableObj2 : public Serialization::ISerializable, public Serialization::ISerializableContainer
{

public:
    SerializableObj2(){;}
    void setValue(double _val) {_number = _val;}
    double number() {return _number;}
    bool useTool() { return _useTool;}

private:
    //QMap<QString, Serialization::ObjectToSerialize> valueToSerialize;
    double _number;
    bool _useTool = false;

    // Standard ISerializable Interface
    STANDARD_SERIALIZABLE(valueToSerialize,
        {"number",&_number},{"useTool",&_useTool})

};

#endif // SERIALIZABLEOBJ_H
