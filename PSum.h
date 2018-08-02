#ifndef PSUM_H
#define PSUM_H

#include "ObjectMgmt/PObject.h"

using namespace ObjectMgmt;

namespace Plugin{

class PSum : public PObject
{
public:
    PSum();
    // void execute(ObjectMgmt::DataObjPtr data);
    void execute(std::shared_ptr<Vec2d> udata);
};

}

#endif // PSUM_H
