#ifndef POBJECTIDREGISTER_H
#define POBJECTIDREGISTER_H

#include <vector>

namespace ObjectMgmt {


/* A sigleton class serves as a unique id dispenser and record keeper
 * This class is only use for providing PObject a unique ID (UID).
 * The method will not be called across thread so no need to considering
 * thread-safe issue.
 * A unsigned integer UID will be generate everytime assignId() is called.
*/

class PObjectIdRegister {

private:
    PObjectIdRegister();

public:
    ~PObjectIdRegister();
    static PObjectIdRegister& instance();
    PObjectIdRegister(PObjectIdRegister const&) = delete;
    void operator=(PObjectIdRegister const&) = delete;
    unsigned long assignId();
    void deleteId(unsigned long id);
    void clear();
    size_t count() { return _ids.size(); }

private:
    std::vector<bool> _ids;

};

}



#endif // POBJECTIDREGISTER_H
