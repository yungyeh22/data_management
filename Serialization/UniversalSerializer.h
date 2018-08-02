#ifndef UNIVERSALSERIALIZER_H
#define UNIVERSALSERIALIZER_H

#include <QDomNode>
#include "ISerializableContainer.h"

namespace Serialization {

class UniversalSerializer {

public:    
    static bool writeComponentsToNode(QDomNode &node, ISerializableContainer &container);
    static bool readComponentsFromNode(const QDomNode &node, ISerializableContainer &container);
};

}
#endif // UNIVERSALSERIALIZER_H
