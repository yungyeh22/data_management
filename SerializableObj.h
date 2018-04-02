#ifndef SERIALIZABLEOBJ_H
#define SERIALIZABLEOBJ_H

#include <QMap>
#include <QString>
#include "Value.h"
#include "ISerializable.h"
#include "ISerializableContainer.h"
#include "ObjectToSerialize.h"

class SerializableObj : public Serialization::ISerializable, public Serialization::ISerializableContainer
{
public:
    SerializableObj();
    setValue(double _val);
    double number() {return _number;}
    // ISerializable Interface
    void readFromXml(const QDomNode &node);
    void writeToXml(QDomNode &node);

    // ISerializableContainer Interface
    QMap<QString, Serialization::ObjectToSerialize>* serializeElements();

private:
    QMap<QString, Serialization::ObjectToSerialize> valueToSerialize;
    // ObjectMgmt::Value _number;
    double _number;


};

#endif // SERIALIZABLEOBJ_H
