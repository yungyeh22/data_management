#ifndef POBJECT_H
#define POBJECT_H

#include <vector>
#include <string>
#include <memory>
#include "DataObj.h"

namespace ObjectMgmt {

class PObject;

typedef std::shared_ptr<PObject> PObjectPtr;

class PObject
{
public:    
    PObject() : _inPortNum(0), _outPortNum(0) {;}
    PObject(const size_t &inPortNum, const size_t &outPortNum) : _inPortNum(inPortNum), _outPortNum(outPortNum) {;}

    //
    //virtual void execute(DataObjPtr data);
    virtual void execute(std::shared_ptr<Vec2d> data) {;} // Virtual funciton must be defined, otherwise vtable emitted.
    virtual bool isTerminal() { return _isTerminal; }
    virtual bool isSource() { return _isSource; }
    std::string name() { return _objName; }
    void setTerminal( bool status ) { _isTerminal = status; }
    void setSource( bool status ) { _isSource = status; }
    void setName(std::string name) { _objName = name; }
    // int id();

private:
    std::string _objName = "";
    // int _id; // Todo: Implement Unique id???
    const size_t _inPortNum; // describe number of port for input signals
    const size_t _outPortNum; // describe number of port for output signals
    bool _isTerminal = false; // Terminal status
    bool _isSource = false; // If the object is a data source

};

}

#endif // POBJECT_H
