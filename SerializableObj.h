#ifndef SERIALIZABLEOBJ_H
#define SERIALIZABLEOBJ_H

#include <QMap>
#include <QString>
#include "Value.h"
#include "ISerializable.h"
#include "ISerializableContainer.h"

class SerializableObj : public Serialization::ISerializable, public Serialization::ISerializableContainer
{
public:
    SerializableObj();
    setValue(double _val);
    double number() {return _number.doubleValue();}
    // ISerializable Interface
    void readFromXml(const QDomNode &node);
    void writeToXml(QDomNode &node);

    // ISerializableContainer Interface
    QMap<QString, ObjectMgmt::Value *> * serializeElements();


private:

    QMap<QString, ObjectMgmt::Value *> valueToSerialize;
    ObjectMgmt::Value _number;

};

#endif // SERIALIZABLEOBJ_H
