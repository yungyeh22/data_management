#include "test.h"
#include "ObjectMgmt/Value.h"
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
    os << "Value Class Test Complete!" << endl;
    return result;
}

bool testWriteToXml( ostream& os ) {
    os << "Test Fail";
    return false;
}

bool testReadFromXml( ostream& os ) {
    os << "Test Fail";
    return false;
}

bool testSerialWrite( ostream& os ) {
    os << "Test Fail";
    return false;
}

bool testSerialRead( ostream& os ) {
    os << "Test Fail";
    return false;
}

bool testNodeAppend( ostream& os ) {
    os << "Test Fail";
    return false;
}

bool testNodeReplace( ostream& os ) {
    os << "Test Fail";
    return false;
}

bool testNodeRemove( ostream& os ) {
    os << "Test Fail";
    return false;
}

bool testNodeReorder( ostream& os ) {
    os << "Test Fail";
    return false;
}

bool testSerialization( ostream& os) {
    bool result = true;
    if (!testSerialRead(os)) {
        os << "Serial read test failed..." << endl;
        result = false;
    }
//    testWriteToXml(os)
//    testReadFromXml(os)
//    testSerialWrite(os)
//    testNodeAppend(os)
//    testNodeReplace(os)
//    testNodeRemove(os)
//    testNodeReorder(os)

    os << "Serialization Test Complete!" << endl;
    return result;
}

// Serializable object test
//   QString objStr = "<object datatype=\"Serializable\">\n"
//                    "    <number datatype=\"Double\">123</number>\n"
//                    "    <useTool datatype=\"Bool\">true</useTool>\n"
//                    "    <otherObj datatype=\"Serializable\">\n"
//                    "       <number datatype=\"Double\">789</number>\n"
//                    "       <useTool datatype=\"Bool\">true</useTool>\n"
//                    "    </otherObj>\n"
//                    "    <myValue datatype=\"Serializable\">\n"
//                    "    <value datatype = \"Double\">3.1415</value>\n"
//                    "</object>\n";
  // Write
//    Serialization::XmlUtility xmlfile("newFile.xml");
//    const QDomNode* dom = xmlfile.dom();
//    QDomDocument inDom;
//    inDom.setContent(objStr);
//    xmlfile.appendCaseNode(inDom);
//    // qDebug() << dom->toDocument().toString();
//    inDom.clear();
//    inDom.setContent(objStr);
//    xmlfile.appendChildToCaseNode(inDom,0);
//    inDom.clear();
//    inDom.setContent(objStr);
//    xmlfile.appendCaseNode(inDom);
//    inDom.clear();
//    QString newContent = "<object222 datatype=\"Serializable\">\n<number datatype=\"Double\">789</number>\n</object222>\n";
//    inDom.setContent(newContent);
//    xmlfile.replaceCaseNode(inDom,1);
//    // xmlfile.removeCaseNode(0);
//    xmlfile.reorderCaseNode(1,0);
//    qDebug() << dom->toDocument().toString();

// xmlfile.saveDomToFile();


// Read and update
//    Serialization::XmlUtility xmlfile("newFile.xml");
//    QDomDocument inDom;
//    QDomElement item = inDom.createElement("Object2");
//    item.setAttribute("dataType","Serializable");
//    // xmlfile.appendToCaseNodeByName(item,"object");
//    xmlfile.appendToRootNode(item);
//    xmlfile.saveDomToFile();
//    qDebug() << xmlfile.dom()->toDocument().toString();

//       QDomDocument dom;
//       dom.setContent(objStr);
//       QDomNode objNode = dom.documentElement().firstChild();
//       SerializableObj tObj;
//       tObj.setValue(543.0);
//       tObj.otherObj()->setValue(520);
//       qDebug() << "original" << tObj.number();
//       qDebug() << "original" << tObj.useTool();
//       qDebug() << "original" << tObj.otherObj()->number();
//       qDebug() << "original" << tObj.otherObj()->useTool();
//       qDebug() << "original" << tObj.doubleValue().doubleValue();
//       tObj.readFromXml(objNode);
//       qDebug() << "new" << tObj.number();
//       qDebug() << "new" << tObj.useTool();
//       qDebug() << "new" << tObj.otherObj()->number();
//       qDebug() << "new" << tObj.otherObj()->useTool();
//       qDebug() << "new" << tObj.doubleValue().doubleValue();
//       QDomDocument domToWrite("project");
//       QDomElement rootElement = domToWrite.createElement("Case1");
//       domToWrite.appendChild(rootElement);
//       tObj.writeToXml(rootElement);
//       qDebug() << domToWrite.toString();

//       QDomNode node = Serialization::XmlUtility::createNode("GB");
//       SerializableObj obj1;
//       obj1.writeToXml(node);
//       QDomDocument dom("");
//       dom.appendChild(node);
//       qDebug() << dom.toString();
