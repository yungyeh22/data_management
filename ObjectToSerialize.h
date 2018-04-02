#ifndef OBJECTTOSERIALIZE_H
#define OBJECTTOSERIALIZE_H

#include <string>
#include "Value.h"
#include "ISerializable.h"

namespace Serialization {

class ObjectToSerialize {

public:
    enum class TYPE : int32_t {DOUBLE, INT, BOOL, STRING, VALUE, SERIALIZABLE, UNDEFINED};

    ObjectToSerialize() { _type = TYPE::UNDEFINED; }
    ObjectToSerialize(double* d) : _d(d) { _type = TYPE::DOUBLE; }
    ObjectToSerialize(int* i) : _i(i) { _type = TYPE::INT; }
    ObjectToSerialize(bool* b) : _b(b) { _type = TYPE::BOOL; }
    ObjectToSerialize(std::string* s) : _s(s) { _type = TYPE::STRING; }
    ObjectToSerialize(ObjectMgmt::Value* v) : _v(v) { _type = TYPE::VALUE; }
    ObjectToSerialize(ISerializable* serializable) : _serializable(serializable) { _type = TYPE::SERIALIZABLE; }

    TYPE type(){return _type;}
    double* doubleItem() {return _d;}
    int* intItem() {return _i;}
    bool* boolItem() {return _b;}
    std::string* stringItem() {return _s;}
    ObjectMgmt::Value* valueItem() {return _v;}
    ISerializable* serializableItem() {return _serializable;}

private:
    TYPE _type;
    double* _d;
    int* _i;
    bool* _b;
    std::string* _s;
    ObjectMgmt::Value* _v;
    ISerializable* _serializable;

};

}

#endif // OBJECTTOSERIALIZE_H
