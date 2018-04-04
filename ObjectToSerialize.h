#ifndef OBJECTTOSERIALIZE_H
#define OBJECTTOSERIALIZE_H

#include <string>
#include "ISerializable.h"

namespace Serialization {

/* Defined how the variables in a serializable object to be received by the ISerializableContainer.
 * This object is used to store some common used data type (e.g. double, int, bool, string..etc)
 * To defined a new receiver for other datatype, inherit ISerializableContainer class and create a
 * new container for a particular type.
 */

class ObjectToSerialize {

public:
    enum class TYPE : int32_t {DOUBLE, INT, BOOL, STRING, SERIALIZABLE, UNDEFINED};

    ObjectToSerialize() { _type = TYPE::UNDEFINED; }
    ObjectToSerialize(double* d) : _d(d) { _type = TYPE::DOUBLE; }
    ObjectToSerialize(int* i) : _i(i) { _type = TYPE::INT; }
    ObjectToSerialize(bool* b) : _b(b) { _type = TYPE::BOOL; }
    ObjectToSerialize(std::string* s) : _s(s) { _type = TYPE::STRING; }
    ObjectToSerialize(ISerializable* serializable) : _serializable(serializable) { _type = TYPE::SERIALIZABLE; }

    TYPE type() const {return _type;}
    double* doubleItem() const {return _d;}
    int* intItem() const {return _i;}
    bool* boolItem() const {return _b;}
    std::string* stringItem() const {return _s;}
    ISerializable* serializableItem() const {return _serializable;}
    std::string typeAsString() const;

private:
    TYPE _type;
    double* _d;
    int* _i;
    bool* _b;
    std::string* _s;
    ISerializable* _serializable;

};

}

#endif // OBJECTTOSERIALIZE_H
