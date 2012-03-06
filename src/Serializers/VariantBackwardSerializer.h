#ifndef VARIANTBACKWARDSERIALIZER_H
#define VARIANTBACKWARDSERIALIZER_H

#include <QtCore>

class VariantBackwardSerializer;
typedef VariantBackwardSerializer* VBackwardSerializer;

class VariantBackwardSerializer {
public:
    VariantBackwardSerializer(const QByteArray &data);
    VariantBackwardSerializer(const VariantBackwardSerializer &other);

    QVariant variant() const;
    QByteArray data() const;
    bool isValid() const;

    virtual void deserialize();
    static VBackwardSerializer Deserialize(const QByteArray &data);
private:
    QVariant _variant;
    QByteArray _data;
    bool _isValid;
};

#endif // VARIANTBACKWARDSERIALIZER_H
