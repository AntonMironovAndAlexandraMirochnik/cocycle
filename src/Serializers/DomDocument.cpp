#include "DomDocument.h"

DomDocument::DomDocument() : QDomDocument() {
}

DomDocument::DomDocument(const DomDocument &other) : QDomDocument(other) {
}

//QString
QDomNode DomDocument::domValue(const QString &value, bool &isOK) {
    isOK = true;
    return createTextNode(value);
}
QString DomDocument::stringValue(const QDomNode &node, bool &isOK) {
    QString result;
    if (!isOK) {
    } else if (node.isText()) {
        result = node.toText().data();
        isOK = true;
    } else {
        isOK = false;
    }
    return result;
}

//int
QDomNode DomDocument::domValue(int value, bool &isOK) {
    isOK = true;
    return createTextNode(QString("%1").arg(value));
}
int DomDocument::intValue(const QDomNode &node, bool &isOK) {
    int result = 0;
    if (!isOK) {
    } else if (node.isText()) {
        result = node.toText().data().toInt(&isOK);
    } else {
        isOK = false;
    }
    return result;
}

//float
QDomNode DomDocument::domValue(double value, bool &isOK) {
    isOK = true;
    return createTextNode(QString("%1").arg(value));
}
double DomDocument::doubleValue(const QDomNode &node, bool &isOK) {
    double result = 0.0;
    if (!isOK) {
    } else if (node.isText()) {
        result = node.toText().data().toDouble(&isOK);
    } else {
        isOK = false;
    }
    return result;
}

//date
QDomNode DomDocument::domValue(const QDate &value, bool &isOK) {
    isOK = true;
    return createTextNode(value.toString("yyyy-MM-dd"));
}
QDate DomDocument::dateValue(const QDomNode &node, bool &isOK) {
    QDate result;
    if (!isOK) {
    } else if (node.isText()) {
        result = QDate::fromString(node.toText().data(), "yyyy-MM-dd");
        isOK = result.isValid();
    } else {
        isOK = false;
    }
    return result;
}

//time
QDomNode DomDocument::domValue(const QTime &value, bool &isOK) {
    isOK = true;
    return createTextNode(value.toString("HH:mm:ss"));
}
QTime DomDocument::timeValue(const QDomNode &node, bool &isOK) {
    QTime result;
    if (!isOK) {
    } else if (node.isText()) {
        result = QTime::fromString(node.toText().data(), "HH:mm:ss");
        isOK = result.isValid();
    } else {
        isOK = false;
    }
    return result;
}

//date time
QDomNode DomDocument::domValue(const QDateTime &value, bool &isOK) {
    isOK = true;
    return createTextNode(value.toString("yyyy-MM-dd HH:mm:ss"));
}
QDateTime DomDocument::dateTimeValue(const QDomNode &node, bool &isOK) {
    QDateTime result;
    if (!isOK) {
    } else if (node.isText()) {
        result = QDateTime::fromString(node.toText().data(), "yyyy-MM-dd HH:mm:ss");
        isOK = result.isValid();
    } else {
        isOK = false;
    }
    return result;
}

const QString KeyAttribute = "key";
const QString StringTag = "string";
const QString IntTag = "int";
const QString DoubleTag = "float";
const QString DateTag = "date";
const QString TimeTag = "time";
const QString DateTimeTag = "date_time";
const QString ListTag = "list";
const QString MapTag = "map";

QDomElement DomDocument::domValue(const QVariant &value, bool &isOK, const QString &key) {
    QDomElement result;
    switch (value.type()) {
    case QVariant::List:
        result = domValue(value.toList(), isOK);
        if (!key.isEmpty()) {
            result.setAttribute(KeyAttribute, key);
        }
        break;
    case QVariant::Map:
        result = domValue(value.toMap(), isOK);
        if (!key.isEmpty()) {
            result.setAttribute(KeyAttribute, key);
        }
        break;
    default:
        result = domSimpleValue(value, isOK, key);
        break;
    }
    return result;
}

QDomElement DomDocument::domSimpleValue(const QVariant &value, bool &isOK, const QString &key) {
    QDomElement result;
    QDomNode node;
    QString tag;
    switch (value.type()) {
    case QVariant::String:
        node = domValue(value.toString(), isOK);
        tag = StringTag;
        break;
    case QVariant::Int:
        node = domValue(value.toInt(), isOK);
        tag = IntTag;
        break;
    case QVariant::Double:
        node = domValue(value.toDouble(), isOK);
        tag = DoubleTag;
        break;
    case QVariant::Date:
        node = domValue(value.toDate(), isOK);
        tag = DateTag;
        break;
    case QVariant::Time:
        node = domValue(value.toTime(), isOK);
        tag = TimeTag;
        break;
    case QVariant::DateTime:
        node = domValue(value.toDateTime(), isOK);
        tag = DateTimeTag;
        break;
    default:
        isOK = false;
        break;
    }
    if (isOK) {
        result = createElement(tag);
        result.appendChild(node);
        if (!key.isEmpty()) {
            result.setAttribute(KeyAttribute, key);
        }
    }
    return result;
}

QVariant DomDocument::variantValue(const QDomElement &element, bool &isOK) {
    QString key;
    return variantValue(element, isOK, key);
}

QVariant DomDocument::variantValue(const QDomElement &element, bool &isOK, QString &key) {
    QVariant result;
    QString tag = element.tagName();
    if (ListTag == tag) {
        result = variantListValue(element.childNodes(), isOK);
    } else if (MapTag == tag) {
        result = variantMapValue(element.childNodes(), isOK);
    } else if (element.hasChildNodes()) {
        if (StringTag == tag) {
            result = stringValue(element.firstChild(), isOK);
        } else if (IntTag == tag) {
            result = intValue(element.firstChild(), isOK);
        } else if (DoubleTag == tag) {
            result = doubleValue(element.firstChild(), isOK);
        } else if (DateTag == tag) {
            result = dateValue(element.firstChild(), isOK);
        } else if (TimeTag == tag) {
            result = timeValue(element.firstChild(), isOK);
        } else if (DateTimeTag == tag) {
            result = dateTimeValue(element.firstChild(), isOK);
        } else {
            isOK = false;
        }
    } else {
        isOK = false;
    }

    if (isOK && element.hasAttribute(KeyAttribute)) {
        key = element.attribute(KeyAttribute);
    }
    return result;
}

//list
QDomElement DomDocument::domValue(const QVariantList &value, bool &isOK) {
    QDomElement element = createElement(ListTag);
    for (QVariantList::const_iterator index = value.constBegin(); isOK && index != value.constEnd(); ++index) {
        element.appendChild(domValue(*index, isOK));
    }
    return element;
}
QVariantList DomDocument::variantListValue(const QDomNodeList &nodeList, bool &isOK) {
    QVariantList list;
    list.reserve(nodeList.count());
    for (int i = 0; isOK && i < nodeList.count(); ++i) {
        QDomNode node = nodeList.at(i);
        if (node.isElement()) {
            list.append(variantValue(node.toElement(), isOK));
        } else {
            isOK = false;
        }
    }
    return list;
}

//map
QDomElement DomDocument::domValue(const QVariantMap &value, bool &isOK) {
    QDomElement element = createElement(MapTag);
    for (QVariantMap::const_iterator index = value.constBegin(); isOK && index != value.constEnd(); ++index) {
        element.appendChild(domValue(index.value(), isOK, index.key()));
    }
    return element;
}
QVariantMap DomDocument::variantMapValue(const QDomNodeList &nodeList, bool &isOK) {
    QVariantMap map;
    QString key;
    for (int i = 0; isOK && i < nodeList.count(); ++i) {
        QDomNode node = nodeList.at(i);
        if (node.isElement()) {
            QVariant value = variantValue(node.toElement(), isOK, key);
            if (isOK) {
                map.insert(key, value);
            }
        } else {
            isOK = false;
        }
    }
    return map;
}
