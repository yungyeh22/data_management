#include <cmath>
#include <sstream>
#include <limits>
#include <algorithm>
#include <iomanip>
#include "Value.h"

using namespace std;

namespace ObjectMgmt {

// Init const string
const string kDoubleAsString = "Double";
const string kIntAsString = "Int" ;
const string kBoolAsString = "Bool" ;
const string kStringAsString = "String" ;
const string kDateAsString = "Date" ;
const string kUndefinedAsString = "Undefined Type" ;

// Constructor
Value::Value() {
    clear();
}

Value::Value( double d ) { setValue(d); }

Value::Value( int i )  { setValue(i); }

Value::Value( bool b ) { setValue(b); }

Value::Value( string s ) { setValue(s); }

Value::Value( const char* c ) { setValue(c); }

Value::Value( date D ) { setValue(D); }

Value::Value( const ValuePtr& p )  { (*this) = p; }

Value::Value( const Value& p ) { (*this) = p; }

Value& Value::operator=(const Value& other)  {
    clear();
    _type = other._type; // Assign types
    _s = other._s; // And values
    _i = other._i;
    _b = other._b;
    _d = other._d;
    _D = other._D;
    return *this;
}

Value& Value::operator=(const ValuePtr& other) {
    clear();
    _type = other->_type; // Copy types
    _s = other->_s; // And values
    _i = other->_i;
    _b = other->_b;
    _d = other->_d;
    _D = other->_D;
    return *this;
}

Value& Value::operator=( const double& inDouble ) {
    clear();
    _type = TYPE::DOUBLE;
    _d = inDouble;
    return *this;
}

Value& Value::operator=( const int& inInteger ) {
    clear();
    _type = TYPE::INT;
    _i = inInteger;
    return *this;
}

Value& Value::operator=( const string& inString ) {
    clear();
    _type = TYPE::STRING;
    _s = inString;
    return *this;
}

Value& Value::operator=( const char* inChar ) {
    clear();
    _type = TYPE::STRING;
    _s = inChar;
    return *this;
}

Value& Value::operator=( const bool& inBool ) {
    clear();
    _type = TYPE::BOOL;
    _b = inBool;
    return *this;
}

Value& Value::operator=( const date& inDate ) {
    clear();
    _type = TYPE::DATE;
    _D = inDate;
    return *this;
}

void Value::setValue( const Value& other ) { *this = other; }

void Value::setValue( const double& inD ) { *this = inD; }

void Value::setValue( const int& inI ) { *this = inI; }

void Value::setValue( const string& inS ) { *this = inS; }

void Value::setValue( const char* inC ) { *this = inC; }

void Value::setValue( const bool& inB ) { *this = inB; }

void Value::setValue( const date& inD )  { *this = inD; }

double Value::doubleValue() const {
    if (_type == TYPE::DOUBLE)
        return _d;
    else { // Not the type, attempt conversion
        switch ( _type ) {
            case TYPE::INT:
                return (double)_i;
            case TYPE::BOOL:
                return (double)_b;
            case TYPE::STRING:	// Attempt to convert... assuming it is just a number
            {    // avoid crosses initialization error
                double d;
                stringstream ss( _s );
                return (ss >> d) ? d : numeric_limits<double>::quiet_NaN();
            }
            default: // For date
                return 0.0;
        }
    }
}

int Value::intValue() const {
    if (_type == TYPE::INT)
        return _i;
    else	// Not the type, attempt conversion
    {
        switch ( _type )
        {
            case TYPE::DOUBLE:
                return (int)(_d); // Don't use floor which truncates toward negative infinite. Use int cast to round toward 0
            case TYPE::BOOL:
                return (int)_b;
            case TYPE::STRING:	// Attempt to convert... assuming it is just a number
            {
                int aoi;
                stringstream ss( _s );
                return (ss >> aoi) ? aoi : numeric_limits<int>::quiet_NaN();
            }
            default: // For date
                return 0;
        }
    }
}

string Value::stringValue() const {
    if (_type == TYPE::STRING)
        return _s;
    else {
        stringstream ss;
        switch( _type ) {
            case TYPE::DOUBLE:
                ss << setprecision(numeric_limits<double>::digits10+1); // This should take care precision conversion problem
                ss << _d;
                break;
            case TYPE::INT:
                ss << _i ; break;
            case TYPE::BOOL:
                ss << _b ; break;
            case TYPE::DATE:
                ss << _D.month << " " << _D.day << ", " << _D.year; break;
            default:
                ss << 0.0 ; break;
        }
        return ss.str();
    }
}

bool Value::boolValue() const {
    if (_type==TYPE::BOOL)
        return _b;
    else {
        switch( _type ) {
            case TYPE::DOUBLE:
                return (_d!=0.0);
            case TYPE::INT:
                return (_i!=0);
            case TYPE::STRING:
            {
                // Transform before comparing
                string st = _s;
                transform(st.begin(),st.end(),st.begin(),::tolower);
                if (!st.compare( "true" )) // return 0 if equal
                    return true;
                else
                    return false;
            }
            default:
                return false;
        }
    }
}

date Value::dateValue() const {
    if (_type==TYPE::DATE)
        return _D;
    else
    {
        return date(); // This is arbitrary, but ok. Unless a certain date number (double or int type) is defined.
    }
}

Value::TYPE Value::type() const {
    return _type;
}

string Value::typeAsString() const {
    switch (_type) {
        case TYPE::DOUBLE:
            return kDoubleAsString;
        case TYPE::INT:
            return kIntAsString;
        case TYPE::STRING:
            return kStringAsString;
        case TYPE::BOOL:
            return kBoolAsString;
        case TYPE::DATE:
            return kDateAsString;
        default:
            return kUndefinedAsString;
    }
}

bool Value::changeType(Value::TYPE type) {
    bool result = true;
    if (type != _type) {
        switch (type) {
        case TYPE::DOUBLE:
        {
            *this = doubleValue();
            break;
        }
        case TYPE::INT:
        {
            *this = intValue();
            break;
        }
        case TYPE::BOOL:
        {
            *this = boolValue();
            break;
        }
        case TYPE::STRING:
        {
            *this = stringValue();
            break;
        }
        case TYPE::DATE:
        { // Date conversion will always fail unless it's defined (e.g. how to convert from double to date...).
            result = false;
            break;
        }
        default:
        {
            result = false;
            break;
        }
        }
    }
    return result;
}

bool Value::changeType(string typeName) {

    if (typeName == kDoubleAsString) {
        return changeType(TYPE::DOUBLE);
    }
    else if (typeName == kIntAsString){
        return changeType(TYPE::INT);
    }
    else if (typeName == kBoolAsString){
        return changeType(TYPE::BOOL);
    }
    else if (typeName == kStringAsString){
        return changeType(TYPE::STRING);
    }
    else if (typeName == kDateAsString){
        return changeType(TYPE::DATE);
    }
    else if (typeName == kUndefinedAsString){
        return changeType(TYPE::UNDEFINED);
    }
    return false;

}

void Value::clear() {
    _type = TYPE::UNDEFINED;
    _d = numeric_limits<double>::quiet_NaN();
    _i = numeric_limits<int>::quiet_NaN();
    _b = numeric_limits<bool>::quiet_NaN();
    _s = string();
    _D = date();
}

//size_type Value::read  (istream& is) {
//    int type;
//    size_type ks, kl, vs, vl;
//    string content;
//    stringstream ss;
//    getline(is,content);
//    // Parse XML, obviously the bad way, not generic.
//    if ((content.find("<Value>") != string::npos) || (content.find("</Value>") != string::npos)) {
//        serial::deSerialPair(content,ks,kl,vs,vl);
//        type = stoi(content.substr(ks,kl));
//        content = content.substr(vs,vl);
//        ss << content;
//        t = (TYPE)type;
//        switch (t) {
//            case TYPE::DOUBLE:
//            {
//                ss >> d;
//                break;
//            }
//            case TYPE::INT:
//            {
//                ss >> i;
//                break;
//            }
//            case TYPE::STRING:
//            {
//                s = content;
//                break;
//            }
//            case TYPE::BOOL:
//            {
//                ss >> b;
//            }
//            case TYPE::DATE:
//            {
//                ss >> D.month;
//                ss.get();
//                ss >> D.day;
//                ss.get();
//                ss.get();
//                ss >> D.year;
//            }
//            default:
//            {
//                break;
//            }
//        }
//        read(is); // need to setup error codes and return it
//    }
//    return 1000;
//}

//size_type Value::write (ostream& os)  const {
//    // XML tag output
//    os << serial::serialPair(to_string((int)t),stringValue(), "Value", "type");
//    return (int)os.tellp(); // Not really the case. Just temporary set as size of string
//}

}

