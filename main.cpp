// #include <QCoreApplication>
#include <iostream>
#include <QString>
#include <QDomNode>
#include <QDomDocument>
#include <QDomNode>
#include <QDebug>
#include <QMap>
#include "ISerializable.h"
#include "SerializableObj.h"
#include "ObjectToSerialize.h"
#include "Value.h"
#include "test.h"

int main(int argc, char *argv[])
{
    // QCoreApplication a(argc, argv);
    // Value Test
    // testValue(std::cout);
//    double a = 1.0;
//    Serialization::ObjectToSerialize vars(&a);
//    *(vars.doubleItem()) = 2.2;
//    qDebug() << a;



    // qDebug() << QString::fromStdString(b.typeAsString()) << QString::fromStdString(b.stringValue());


    // Serializable object test
       QString objStr = "<root>\n"
                        "<object type=\"Serializable\">\n"
                        "    <number type=\"Double\">123</number>\n"
                        "    <useTool type=\"Bool\">true</useTool>\n"
                        "    <otherObj type=\"Serializable\">\n"
                        "       <number type=\"Double\">789</number>\n"
                        "       <useTool type=\"Bool\">true</useTool>\n"
                        "    </otherObj>\n"
                        "    <myValue type=\"Serializable\">\n"
                        "    <value type = \"Double\">3.1415</value>\n"
                        "</object>\n"
                        "</root>\n";
       QDomDocument dom;
       dom.setContent(objStr);
       QDomNode objNode = dom.documentElement().firstChild();
       SerializableObj tObj;
       tObj.setValue(543.0);
       tObj.otherObj()->setValue(520);
       qDebug() << "original" << tObj.number();
       qDebug() << "original" << tObj.useTool();
       qDebug() << "original" << tObj.otherObj()->number();
       qDebug() << "original" << tObj.otherObj()->useTool();
       qDebug() << "original" << tObj.doubleValue().doubleValue();
       tObj.readFromXml(objNode);
       qDebug() << "new" << tObj.number();
       qDebug() << "new" << tObj.useTool();
       qDebug() << "new" << tObj.otherObj()->number();
       qDebug() << "new" << tObj.otherObj()->useTool();
       qDebug() << "new" << tObj.doubleValue().doubleValue();

    return 1;
    // return a.exec();
}
