#ifndef XMLUTILITY_H
#define XMLUTILITY_H

#include <memory>
#include <QString>
#include <QDomDocument>

namespace Serialization {

class XmlUtility;

typedef std::unique_ptr<XmlUtility> xmlUtility_ptr;

/* Represent a QDomDocument object that holds xml DOM document content,
 * and provide methods to operate on the xml DOM including append new
 * nodes and save or read from an xml file. */

class XmlUtility
{

public:

    XmlUtility(); // Dom is available but no file is associated.
    XmlUtility(const QString &fullFilePath);
    // DOM operations
    void clearDom();
    // File <--> DOM operations
    bool loadDomFromFile();
    bool loadDomFromFile(const QString &fullFilePath); // This action will result in file name change
    bool saveDomToFile();
    bool saveDomToFile(const QString &fullFilePath); // This action will result in file name change
    bool setFileName(const QString &fullFilePath);
    // Node operations (append to, replace, remove). Insert is not necessary because the order is not important.
    void appendToRootNode(const QDomNode &node);
    bool appendToCaseNodeByIndex(const QDomNode &node, const int &n);
    bool appendToCaseNodeByName(const QDomNode &node, const QString &nodeName);
    bool replaceCaseNodeByIndex(const QDomNode &node, const int &n);
    bool replaceCaseNodeByName(const QDomNode &node, const QString &nodeName);
    bool removeCaseNodeByIndex(const QDomNode &node, const int &n);
    bool removeCaseNodeByName(const QDomNode &node, const QString &nodeName);

    const QDomNode* dom() const { return &_dom; } // Get document node. It returns a const object so external operation won't mess up the node structure.
    QString filename() const { return _fullFilePath; } // Get current associated file name
    bool fileExists() const;

public: // Static methods
    // Get an empty node with appropriate tag name. If it's for a serializable object, the node attach datatype="Serializable" atttribute.
    static QDomNode createNode(const QString &name = "Case", const bool &serializable = true);

private:
    QString _fullFilePath;
    QDomDocument _dom;
    void createRootNode();
    int findNodeByName(const QDomNodeList &nodes,  const QString &nodeName);
};
}

#endif // XMLUTILITY_H
