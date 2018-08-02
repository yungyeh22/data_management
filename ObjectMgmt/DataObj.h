#ifndef DATAOBJ_H
#define DATAOBJ_H

#include <string>
#include <vector>
#include <memory>

namespace ObjectMgmt {

class DataObj;

typedef std::shared_ptr<DataObj> DataObjPtr;

struct DataObj
{
    virtual std::string dType() const {return "None"; }
};

struct Vec2d : DataObj
{
    std::string dType() const { return "vec2d"; }
    std::vector<std::vector<double>> data;
};


}

#endif // DATAOBJ_H

