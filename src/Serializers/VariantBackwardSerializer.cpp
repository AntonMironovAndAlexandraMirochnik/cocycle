#include "VariantBackwardSerializer.h"
#include "DomDocument.h"

VariantBackwardSerializer::VariantBackwardSerializer(const QByteArray &data) {
    _data = data;
    _isValid = false;
}

VariantBackwardSerializer::VariantBackwardSerializer(const VariantBackwardSerializer &other) {
    _variant = other._variant;
    _isValid = other._isValid;
    _data = other._data;
}

QVariant VariantBackwardSerializer::variant() const { return _variant;}
QByteArray VariantBackwardSerializer::data() const {return _data; }
bool VariantBackwardSerializer::isValid() const {return _isValid; }

void VariantBackwardSerializer::deserialize() {
    DomDocument doc;
    doc.setContent(_data);
    _isValid = doc.hasChildNodes();
    if (_isValid) {
        QDomElement domElement = doc.firstChildElement();
        _variant = doc.variantValue(domElement, _isValid);
    }
}

VBackwardSerializer VariantBackwardSerializer::Deserialize(const QByteArray &data) {
    VBackwardSerializer deserializer = new VariantBackwardSerializer(data);
    deserializer->deserialize();
    return deserializer;
}
