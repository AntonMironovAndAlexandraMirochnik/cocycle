#ifndef DOMDOCUMENT_H
#define DOMDOCUMENT_H

#include <QtCore>
#include <QtXml>

class DomDocument : public QDomDocument
{
public:
    DomDocument();
    DomDocument(const DomDocument &other);

    virtual QDomElement domValue(const QVariant &value, bool &isOK, const QString &key = QString());
    virtual QVariant variantValue(const QDomElement &element, bool &isOK);
    virtual QVariant variantValue(const QDomElement &element, bool &isOK, QString &key);

protected:
    virtual QDomNode domValue(const QString &value, bool &isOK);
    virtual QString stringValue(const QDomNode &node, bool &isOK);

    virtual QDomNode domValue(bool value, bool &isOK);
    virtual bool boolValue(const QDomNode &node, bool &isOK);

    virtual QDomNode domValue(int value, bool &isOK);
    virtual int intValue(const QDomNode &node, bool &isOK);

    virtual QDomNode domValue(double value, bool &isOK);
    virtual double doubleValue(const QDomNode &node, bool &isOK);

    virtual QDomNode domValue(const QDate &value, bool &isOK);
    virtual QDate dateValue(const QDomNode &node, bool &isOK);

    virtual QDomNode domValue(const QTime &date, bool &isOK);
    virtual QTime timeValue(const QDomNode &node, bool &isOK);

    virtual QDomNode domValue(const QDateTime &value, bool &isOK);
    virtual QDateTime dateTimeValue(const QDomNode &node, bool &isOK);

    virtual QDomElement domSimpleValue(const QVariant &value, bool &isOK, const QString &key = QString());

    virtual QDomElement domValue(const QVariantList &value, bool &isOK);
    virtual QVariantList variantListValue(const QDomNodeList &nodeList, bool &isOK);

    virtual QDomElement domValue(const QVariantMap &value, bool &isOK);
    virtual QVariantMap variantMapValue(const QDomNodeList &nodeList, bool &isOK);
};

#endif // DOMDOCUMENT_H
