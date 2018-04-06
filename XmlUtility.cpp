#include "XmlUtility.h"
#include <QFile>
#include <QFileInfo>
#include <QDomNodeList>
#include <QDebug>


namespace Serialization {

XmlUtility::XmlUtility() : _fullFilePath(QString()), _dom("Project")  {
    createRootNode();
}

XmlUtility::XmlUtility(const QString &fullFilePath) : _fullFilePath(fullFilePath), _dom("Project") {
    if (fileExists()) {
        setFileName(fullFilePath);
    }
    else {
        createRootNode(); // Create the root node so the dom is ready to be written.
    }
}

void XmlUtility::clearDom() {
    _dom.clear();
}

bool XmlUtility::loadDomFromFile() {
    return loadDomFromFile(_fullFilePath);
}

bool XmlUtility::loadDomFromFile(const QString &fullFilePath) {
    bool result = true;
    QFile xmlFile(fullFilePath);
    result &= xmlFile.exists();
    if (result) {
        result &= xmlFile.open(QIODevice::ReadOnly | QIODevice::Text);
        if (result) {
            result &= _dom.setContent(&xmlFile);
            if (!result) {
                qDebug() << "Failed to parse the file into a DOM tree.";
            }
        }
        else {
            qDebug() <<  "Failed to open file for reading xml." ;
        }
        xmlFile.close();
    }
    else {
        qDebug() << "File does not exist";
    }
    return result;
}

bool XmlUtility::saveDomToFile() {
    // Goes through the overload function so the validity of file got checked;
    return saveDomToFile(_fullFilePath);
}

bool XmlUtility::saveDomToFile(const QString &fullFilePath) {
    bool result = true;
    QFile xmlFile(fullFilePath);
    result &= xmlFile.open(QIODevice::WriteOnly | QIODevice::Text);
    if(result) {
        if (_fullFilePath != fullFilePath) {
            _fullFilePath = fullFilePath;
        }
        QTextStream content(&xmlFile);
        content << _dom.toString();
        xmlFile.close();
    }
    else {
        qDebug() << "Failed to open file for writing xml!";
    }
    return result;
}

bool XmlUtility::setFileName(const QString &fullFilePath) {
    QFileInfo fileInfo(fullFilePath);
    QString newFullFilePath;
    if (!fileInfo.isAbsolute()) {
        newFullFilePath = fileInfo.absoluteFilePath();
    }
    else {
        newFullFilePath = fullFilePath;
    }
    _fullFilePath = newFullFilePath;
    return loadDomFromFile();
}

void XmlUtility::appendToRootNode(const QDomNode &node) {
    if (_dom.documentElement().isNull()) {
        createRootNode();
    }
    _dom.documentElement().appendChild(node);
}

bool XmlUtility::appendToCaseNodeByIndex(const QDomNode &node, const int &n) {
    bool result = true;
    QDomNode nNode = _dom.documentElement().firstChild().childNodes().at(n);
    result &= !nNode.isNull();
    if (result) {
        nNode.appendChild(node);
    }
    else {
        qDebug() << "Node does not exist.";
    }
    return result;
}

bool XmlUtility::appendToCaseNodeByName(const QDomNode &node, const QString &nodeName) {
    bool result = true;
    QDomNodeList nodes = _dom.documentElement().firstChild().childNodes();
    int idx = findNodeByName(nodes,nodeName);
    if (result &= (idx > 0)) {
        nodes.at(idx).appendChild(node);
    }
    return result;
}

bool XmlUtility::replaceCaseNodeByIndex(const QDomNode &node, const int &n)
{
    bool result = true;
    return result;
}

bool XmlUtility::replaceCaseNodeByName(const QDomNode &node, const QString &nodeName)
{
    bool result = true;
    return result;
}

bool XmlUtility::removeCaseNodeByIndex(const QDomNode &node, const int &n)
{
    bool result = true;
    return result;
}

bool XmlUtility::removeCaseNodeByName(const QDomNode &node, const QString &nodeName)
{
    bool result = true;
    return result;
}

bool XmlUtility::fileExists() const {
    QFileInfo fileInfo(_fullFilePath);
    return fileInfo.exists();
}

QDomNode XmlUtility::createNode(const QString &name, const bool &serializable) {
    // QDomElement item = QDomDocument().createElement(name); // Create an element like this somehow causes runtime error if there is more operation immediately after creating the element. It could due to the deep copy of the node.
    QDomDocument doc; // Null node, but good for just creating the tag we want.
    QDomElement item = doc.createElement(name);
    if (serializable) {
        item.setAttribute("datatype","Serializable");
    }
    return item;
}

void XmlUtility::createRootNode() {
    QDomElement rootNodeElement = _dom.createElement("root");
    _dom.appendChild(rootNodeElement);
}

int XmlUtility::findNodeByName(const QDomNodeList &nodes, const QString &nodeName) {
    int idx= -1;
    if (nodes.size()) {
        for ( idx = 0 ; idx < nodes.size() ; ++idx) {
            if (nodes.at(idx).toElement().tagName() == nodeName) {
                break;
            }
        }
        if (idx == nodes.size()) {
            idx = -1;
            qDebug() << "Node couldn't be found!";
        }
    }
    else {
        qDebug() << "Node does not exist.";
    }
}

}
