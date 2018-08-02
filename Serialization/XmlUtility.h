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
    // Node operations (append to, replace, remove, insert)
    void appendCaseNode(const QDomNode &node);
    bool appendChildToCaseNode(const QDomNode &node, const int &n);
    bool reorderCaseNode(const int &oldPos, const int &newPos);
    bool replaceCaseNode(const QDomNode &node, const int &n);
    bool removeCaseNode(const int &n);

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

};
}

#endif // XMLUTILITY_H
