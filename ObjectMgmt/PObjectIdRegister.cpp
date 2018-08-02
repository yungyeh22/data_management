#include "PObjectIdRegister.h"

namespace ObjectMgmt {

PObjectIdRegister::PObjectIdRegister()
{

}

unsigned long PObjectIdRegister::assignId() {
    bool all = true;
    unsigned long index = 0;
    for (index ; index < _ids.size() ; ++index) {
        all &= _ids[index];
        if (!all) {
            break;
        }
    }
    if (!all) {
        _ids.emplace_back(true);
        index++;
    }
    return index;
}


void PObjectIdRegister::clear() {
     _ids.clear();
     std::vector<bool>().swap(_ids); // force a relocation
}

}
