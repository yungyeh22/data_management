#include "ObjectToSerialize.h"
#include "Value.h"

namespace Serialization {

string ObjectToSerialize::typeAsString()
{
    switch (_type) {
    case (TYPE::DOUBLE):
        return ObjectMgmt::kDoubleAsString;
    case (TYPE::INT):
        return ObjectMgmt::kIntAsString;
    case (TYPE::BOOL):
        return ObjectMgmt::kBoolAsString;
    case (TYPE::STRING):
        return ObjectMgmt::kIntAsString;
    case (TYPE::SERIALIZABLE):
        return ObjectMgmt::kSerializable;
    case (TYPE::UNDEFINED):
        return ObjectMgmt::kUndefinedAsString;
    }
}



}



