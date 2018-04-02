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
 * Recursive content is supported via the serializablesToSerialize() method, which lets the serializable class
 * identify its members that represent subordinate serializable classes.
 */

namespace Serialization {

class ISerializableContainer {

public:
    virtual ~ISerializableContainer(){;}
    virtual QMap<QString, ObjectToSerialize>* serializeElements() = 0; // Return a QMap containing the variables that needs to be serialized
};

}
#endif // SERIALIZABLECONTAINER_H
