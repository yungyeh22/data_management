// #include <QCoreApplication>
#include <iostream>
#include <QString>
#include <QDomNode>
#include <QDomDocument>
#include <QDomNode>
#include <QDebug>
#include <QMap>
#include "Test/SerializableObj.h"
#include "Serialization/XmlUtility.h"
#include "ObjectMgmt/Value.h"
#include "Test/test.h"
// #include "ObjectMgmt/DataObj.h"
// #include "ObjectMgmt/PObject.h"
#include "PSum.h"

int main(int argc, char *argv[])
{
    // QCoreApplication a(argc, argv);
    // Value Test
    // testValue(std::cout);
//    double&& a = 1;
//    qDebug() << a;
    // prepare data
    std::shared_ptr<ObjectMgmt::Vec2d> data = std::make_shared<ObjectMgmt::Vec2d>(ObjectMgmt::Vec2d());
    std::vector<vector<double>> nvec;
    nvec.resize(100);
    for (auto &row : nvec) {
        row.resize(655000);
    }
    double num = 1;
    for (auto &row : nvec) {
        for (auto &col : row) {
            col = 1;
            //num++;
        }
    }
    data->data = std::move(nvec);

    Plugin::PSum p;
    ObjectMgmt::PObject pbase(p);
    pbase.execute(data);
    p.execute(data);
    qDebug() << "Result: " << data->data[0][0];
    qDebug() << QString::fromStdString(p.name());
    getchar();
    return 1;
    // return a.exec();
}
