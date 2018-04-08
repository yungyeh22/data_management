#ifndef POBJECT_H
#define POBJECT_H

#include <vector>

class PObject
{
public:
    PObject();
    //
    bool execute();
    virtual bool isTerminal() { return false; }

protected:
    // std::vector<PObject> dependencies;


private:
    size_t _inSignal; // describe number of port for input signals
    size_t _outSignal; // describe number of port for output signals
    // PObjectContainer _processors;


};

#endif // POBJECT_H
