#ifndef ISERIALIZABLECONTAINER_H
#define ISERIALIZABLECONTAINER_H

#include <QMap>
#include <QString>
#include "ObjectToSerialize.h"

/* Interface (purely abstract base class) to be realized by serializable objects (see the ISerializable interface) to simplify
 * the process of writing and reading the class's content to and from an XML node.
 * The serializable class uses the methods of this interface to identify and name member variables that represent its serializable
 * content.  It can then use the Serializer class to actually transfer its content to an xml node, or populate its content from
 * an xml node.
 * The ObjectToSerialize class holds pointer for some common data types and help the ISeriable interface to understand the serializable
 * objects.
 * Recursive content is supported in ObjectToSerialize class, which lets the serializable class identify its members that represent
 * subordinate serializable classes.
 * This class is used by UniversalSerializer class to read objects from or write objects to an xml document. In other word, the an
 * Serializer class must know how to parse the objects in a container.
 */

#define ADD_SERIABLE_OBJECT(storeMap, objectName,object) \
    storeMap[#objectName] = Serialization::ObjectToSerialize(&object);

namespace Serialization {

class ISerializableContainer {

public:
    virtual ~ISerializableContainer(){;}
    virtual QMap<QString, ObjectToSerialize>* serializeElements() = 0; // Return a QMap containing the variables that needs to be serialized
    // virtual QMap<QString, double*>* serializeDouble = 0; // An example to make the container hold an double object.
};

}
#endif // SERIALIZABLECONTAINER_H
