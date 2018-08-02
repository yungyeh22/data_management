#ifndef POBJECTCONTAINER_H
#define POBJECTCONTAINER_H

#include "PObject.h"

namespace ObjectMgmt {

typedef std::vector<PObjectPtr> PObjects;

class PObjectContainer : public PObject
{

public:
    PObjectContainer();
    PObjectContainer(PObjects objects);
    PObjectContainer(size_t inPortNum, size_t outPortNum) : PObject(inPortNum, outPortNum) {;}
    virtual ~PObjectContainer();

    // Methods

    // Operations
    void appendObject(PObject &obj);
    void appendObject(PObjectPtr objPtr);
    void insertObject(PObject &obj, size_t position);
    void insertObject(PObjectPtr objPre, const size_t &position);
    void removeObject(PObjectPtr objPtr);
    void removeObjectAtIndex(const size_t &position);
    void execute(std::vector<std::vector<double>> in, std::vector<std::vector<double>> out);

    // Transverse
    PObjectPtr firstObject();
    PObjectPtr nextObject();
    PObjectPtr lastObject();

    // Utilities
    size_t size() {return children.size();}
    size_t count() {return size();}


private:
    PObjects children;
    PObjects::iterator iter;
    PObjects selectedChildren;
    PObjects::iterator selectedIter;

private:
    void getObjects ( const unsigned long &index );

};

}
#endif // POBJECTCONTAINER_H
