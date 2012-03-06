#include "VariantBackwardSerializer.h"
#include "DomDocument.h"

VariantBackwardSerializer::VariantBackwardSerializer(const QByteArray &data) {
    _data = data;
    _isValid = false;
}

QVariant VariantBackwardSerializer::variant() const { return _variant;}
QByteArray VariantBackwardSerializer::data() const {return _data; }
bool VariantBackwardSerializer::isValid() const {return _isValid; }

QVariant VariantBackwardSerializer::deserialize(const QByteArray &data, bool &isOK) {
    DomDocument doc;
    doc.setContent(data);
    QVariant variant;
    isOK = doc.hasChildNodes();
    if (isOK) {
        QDomElement domElement = doc.firstChildElement();
        variant = doc.variantValue(domElement, isOK);
    }
    return variant;
}

QVariant VariantBackwardSerializer::operator()() {
    bool isOK = true;
    _variant = deserialize(data(), isOK);
    _isValid = isOK;
    return variant();
}
