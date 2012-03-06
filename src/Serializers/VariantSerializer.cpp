#include "VariantSerializer.h"
#include "DomDocument.h"

VariantSerializer::VariantSerializer(const QVariant &variant) {
    _variant = variant;
    _isValid = false;
}

VariantSerializer::VariantSerializer(const VariantSerializer &other) {
    _variant = other._variant;
    _isValid = other._isValid;
    _data = other._data;
}

QVariant VariantSerializer::variant() const { return _variant;}
QByteArray VariantSerializer::data() const {return _data; }
bool VariantSerializer::isValid() const {return _isValid; }

void VariantSerializer::serialize() {
    DomDocument doc;
    _isValid = true;
    QDomElement domElement = doc.domValue(_variant, _isValid);
    doc.appendChild(domElement);
    _data = doc.toByteArray();
}

VSerializer VariantSerializer::Serialize(const QVariant &variant) {
    VSerializer serializer = new VariantSerializer(variant);
    serializer->serialize();
    return serializer;
}
