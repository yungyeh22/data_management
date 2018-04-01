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
#include "test.h"

int main(int argc, char *argv[])
{
    // QCoreApplication a(argc, argv);

    // testValue(std::cout);
    QString objStr = "<root>\n<Object>\n<number type=\"Int\">123</Time>\n</Object>\n</root>";
    QDomDocument dom;
    dom.setContent(objStr);
    QDomNode objNode = dom.documentElement().firstChild();
    SerializableObj tObj;
    tObj.setValue(10.0);
    tObj.readFromXml(objNode);
    qDebug() << tObj.number();

    return 1;
    // return a.exec();
}
