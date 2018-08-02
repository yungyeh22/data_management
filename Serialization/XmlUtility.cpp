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

void XmlUtility::appendCaseNode(const QDomNode &node) {
    if (_dom.documentElement().isNull()) {
        createRootNode();
    }
    _dom.documentElement().appendChild(node);
}

bool XmlUtility::appendChildToCaseNode(const QDomNode &node, const int &n) {
    bool result = true;
    QDomNode nNode = _dom.documentElement().firstChild().childNodes().at(n);
    result &= !nNode.isNull();
    if (result) {
        nNode.appendChild(node);
    }
    else {
        qDebug() << "Node does not exist!";
    }
    return result;
}

bool XmlUtility::reorderCaseNode(const int &oldPos, const int &newPos) {
    bool result = true;
    QDomNodeList nodes = _dom.documentElement().childNodes();
    QDomNode cNodeOldPos = nodes.at(oldPos);
    QDomNode cNodeNewPos = nodes.at(newPos);
    result &= !cNodeOldPos.isNull();
    if (!result) {
        qDebug() << "Invalid original index!";
    }
    result &= !cNodeNewPos.isNull();
    if (!result) {
        qDebug() << "Invalid new index!";
    }
    if (result) {
        if (oldPos > newPos) {
            QDomNode newRefNode = cNodeNewPos.parentNode().insertBefore(cNodeOldPos,cNodeNewPos);
            result &= !newRefNode.isNull();
        }
        else if (oldPos < newPos) {
            QDomNode newRefNode = cNodeNewPos.parentNode().insertAfter(cNodeOldPos,cNodeNewPos);
            result &= !newRefNode.isNull();
        }
    }
    else {
        qDebug() << "Failed to reorder node!";
    }
    return result;
}

bool XmlUtility::replaceCaseNode(const QDomNode &node, const int &n) {
    bool result = true;
    QDomNode oldNode = _dom.documentElement().childNodes().at(n);
    result &= !oldNode.isNull();

    if (result) {
        oldNode.parentNode().replaceChild(node,oldNode);
    }
    else {
        qDebug() << "Invalid index!\nFailed to replace node!";
    }
    return result;
}

bool XmlUtility::removeCaseNode(const int &n) {
    bool result = true;
    QDomNode cNode = _dom.documentElement().childNodes().at(n);
    result &= !cNode.isNull();
    if (result) {
        cNode.parentNode().removeChild(cNode);
    }
    else {
        qDebug() << "Invalid index!\nFailed to remove node!";
    }
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


}
