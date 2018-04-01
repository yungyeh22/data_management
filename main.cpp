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
#include "Value.h";
#include "test.h"

int main(int argc, char *argv[])
{
    // QCoreApplication a(argc, argv);
    // Value Test
    // testValue(std::cout);
//    double a = 1.0;
//    Serialization::ObjectToSerialize<decltype(a)> vars("number", &a);
//    decltype(vars.object()) x = vars.object();
//    qDebug() << *x;



    // qDebug() << QString::fromStdString(b.typeAsString()) << QString::fromStdString(b.stringValue());


    // Serializable object test
    //    QString objStr = "<root>\n<Object>\n<number type=\"Int\">123</Time>\n</Object>\n</root>";
    //    QDomDocument dom;
    //    dom.setContent(objStr);
    //    QDomNode objNode = dom.documentElement().firstChild();
    //    SerializableObj tObj;
    //    tObj.setValue(10.0);
    //    tObj.readFromXml(objNode);
    //    qDebug() << tObj.number();

    return 1;
    // return a.exec();
}
