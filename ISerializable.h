#ifndef ISERIALIZABLE_H
#define ISERIALIZABLE_H

#include <QDomNode>
#include "ISerializableContainer.h"

namespace Serialization {

/* Interface (purely abstract base class) to be realized by classes that can write & read their content to
 * and from an element within an XML DOM.  The XML element is represented as a QDomNode node which already
 * must exist and be provided to the serializable object when readFromXml or writeToXml is called on that
 * object.
 *
 * The readFromXml method is responsible for reading and interpreting the sub-elements within the node
 * that is provided.
 *
 * The writeToXml method is responsible for writing sub-elemtns into the node that is provided.
 *
 */

class ISerializable {

public:
    virtual ~ISerializable(){;}

    //populate the ISerializable object's members with data extracted from the given xml node.
    virtual void readFromXml(const QDomNode &node) = 0;

    //use the ISerializable object's members to populate elements within the xml node provided.
    virtual void writeToXml(QDomNode &node) = 0;
};


class UniversalSerializer {

public:
    static bool writeComponentsToNode(QDomNode &node, const ISerializableContainer &container);
    static bool readComponentsFromNode(const QDomNode &node, ISerializableContainer &container);
};




}

#endif // ISERIALIZABLE_H
