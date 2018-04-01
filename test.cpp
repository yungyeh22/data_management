#include "test.h"
#include "Value.h"
#include <sstream>
#include <ostream>
using namespace ObjectMgmt;
using namespace std;

bool testValueConstructors( ostream& os )
{
    bool result = true;

    Value pProp, pDouble((double) 3.141592), pInt( (int) 5 ), pChars("TESTVALUE") ,pString( string("Property") ), pBool( true ), pDate( date(11,18,1966) );

    if (pProp.type() != Value::TYPE::UNDEFINED) {
        os << "Default constructor failed!" << endl;
        result = false;
    }

    if (pDouble.type() != Value::TYPE::DOUBLE || pDouble.doubleValue() != (double) 3.141592 )
        result = false;

    if (pInt.type() != Value::TYPE::INT || pInt.intValue() != (int) 5 )
        result = false;

    if (pChars.type() != Value::TYPE::STRING || pChars.stringValue().compare( "TESTVALUE" ) != 0 )
        result = false;

    if (pString.type() != Value::TYPE::STRING || pString.stringValue().compare( string("Property") ) != 0 )
        result = false;

    if (pDate.type() != Value::TYPE::DATE || pDate.dateValue() != date(11,18,1966))
        result = false;

    if (pBool.type() != Value::TYPE::BOOL || pBool.boolValue()!=true)
        result = false;

    return result;
}

bool testValue( ostream& os ) {
    bool result = true;
    if (!testValueConstructors(os)) {
        os << "Property constructor test failed..." << endl;
        result = false;
    }
    os << "Test Complete!" << endl;
    return result;
}
