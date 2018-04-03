/*! @file Value.h
 @brief Representation of a value.
 
 An abstraction to represent value that can take different forms: a number,
 an adjustable parameter, an expression (string), a name (string), a color.
 The value can serialize itself, describe and validate itself.
 */

#ifndef _VALUE_H
#define _VALUE_H

#include <string>
#include <memory>
#include <cstdint>
#include <QDomNode>
#include "ISerializable.h"

using namespace std;

namespace ObjectMgmt {

typedef struct date {
    int month, day, year;

    date( int inMonth=0, int inDay=0, int inYear=0 ) : month(inMonth), day(inDay), year(inYear) { } // Default date is C.E. 0

    // Overload operator==
    inline bool operator==(const date& od) const {
        return (od.month==month && od.day==day && od.year==year);
    }

    // Overload operator!=
    inline bool operator!=(const date& od) const {
        return (!(od.month==month && od.day==day && od.year==year));
    }

    // Overload operator<
    inline bool operator<(const date& od) const {
        return ( year < od.year || (year == od.year && month < od.month) || (year == od.year && month == od.month && day < od.day));
    }

    // Overload operator>
    inline bool operator>(const date& od) const {
        return od<(*this);
    }
    // Overload operator<=
    inline bool operator<=(const date& od) const {
        return !(*this>od);
    }
    // Overload operator>=
    inline bool operator>=(const date& od) const {
        return !(*this<od);
    }
    // Overload assignment
    date& operator=(const date& od)
    {
        month = od.month;
        day = od.day;
        year = od.year;
        return *this;
    }
} date;
        
class Value;

typedef shared_ptr<Value> ValuePtr;

extern const string kDoubleAsString;
extern const string kIntAsString;
extern const string kBoolAsString;
extern const string kStringAsString;
extern const string kDateAsString;
extern const string kSerializable;
extern const string kUndefinedAsString;

class Value : public Serialization::ISerializable{
    public:
        // Use Strongly typed enum with underlying type int32
        enum class TYPE : int32_t {DOUBLE, INT, BOOL, STRING, DATE, UNDEFINED};

    private:
        TYPE _type;
        double _d;	// Value if value is of a 'DOUBLE' type
        int _i;	// Value for type = 'INT'
        bool _b;	// Value for type = 'BOOL'
        string _s;	// Value if it is of a 'STRING' type
        date _D;     // Value for type = 'DATE'

    public:
        // Constructor
        Value();                    // Default constructor will yield UNDEFINED TYPE.
        Value(const double d);          // Double argument constructor
        Value(const int i);             // Int argument constructor
        Value(const bool b);            // Bool argument constructor
        Value(const string &s);          // String argument constructor
        Value(const char*);        // C-string  argument constructor
        Value(const date &D);            // Bool argument constructor
        Value(const ValuePtr& p); // Clone using shared pointer.
        Value(const Value& p);    // Clone from another value.
        // Overload operator=
        Value& operator=( const Value& other );     // Copy from another object
        Value& operator=( const ValuePtr& other );  // Copy from a pointer to another object
        Value& operator=( const double& inDouble );	// Sets the double value and changes type to 'string'
        Value& operator=( const int& inInteger );	// Sets the int value and changes type to 'string'
        Value& operator=( const string& inString );	// Sets the string value and changes type to 'string'
        Value& operator=( const char* inChar );     // Sets the char* value and changes type to 'string'
        Value& operator=( const bool& inBool );	// Sets the bool value and changes type to 'bool'
        Value& operator=( const date& inDate );     // Sets the date value and changes type to 'date
        // Set Value
        void setValue( const Value& other);         // Sets value object from another value object
        void setValue( const double& inDouble );	// Sets the double value and changes type to 'string'
        void setValue( const int& inInteger );	// Sets the int value and changes type to 'string'
        void setValue( const string& inString );	// Sets the string value and changes type to 'string'
        void setValue( const char* inString);       // Sets the char* value and changes type to 'string'
        void setValue( const bool& inBool );	// Sets the bool value and changes type to 'bool'
        void setValue( const date& inDate );        // Sets the date value and changes type to 'date
        // Type conversion
        double doubleValue() const;	// Read double value. Conversion from other type if carried out when possible, otherwise NaN is returned.
        int intValue() const;       // Returns int value. Conversion from other type if carried out when possible, otherwise NaN is returned.
        string stringValue() const;	// Returns string value.
        bool boolValue() const;	// Returns bool value.
        date dateValue() const;     // Returns the date value if value is a date, C.E. 0, otherwise.
        // Type ID
        TYPE type() const;          // Type as an enum with possible values DOUBLE STRING INT, BOOL or DATE
        string typeAsString() const;// Type as a string
        bool changeType(TYPE type); // Change type if possible. Return trur if succeeded.
        bool changeType(string typeName);
        // Clear private variables (for initialization)
        void clear();

        // ISerializable Interface
         void readFromXml(const QDomNode &node);
         void writeToXml(QDomNode &node);

};
}

#endif // VALUE_H

