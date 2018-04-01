#ifndef OBJECTTOSERIALIZE_H
#define OBJECTTOSERIALIZE_H

#include <QString>

namespace Serialization {

template <typename T>
class ObjectToSerialize {
public:
    ObjectToSerialize(const QString &name, T* obj) : _name(name), _obj(obj) {;}
    QString name() {return _name;}
    T* object() {return _obj;}

private:
    T* _obj;
    QString _name;
};

}

#endif // OBJECTTOSERIALIZE_H
