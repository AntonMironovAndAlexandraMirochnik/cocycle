#include "VariantSerializer.h"
#include "DomDocument.h"

VariantSerializer::VariantSerializer(const QVariant &variant) {
    _variant = variant;
    _isValid = false;
}

QVariant VariantSerializer::variant() const { return _variant;}
QByteArray VariantSerializer::data() const {return _data; }
bool VariantSerializer::isValid() const {return _isValid; }

QByteArray VariantSerializer::serialize(const QVariant &variant, bool &isOK) {
    DomDocument doc;
    isOK = true;
    QDomElement domElement = doc.domValue(variant, isOK);
    doc.appendChild(domElement);
    QByteArray data = doc.toByteArray();
    return data;
}

QByteArray VariantSerializer::operator()() {
    bool isOK = true;
    _data = serialize(variant(), isOK);
    _isValid = isOK;
    return data();
}
