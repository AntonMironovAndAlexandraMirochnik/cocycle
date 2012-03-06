#ifndef VARIANTSERIALIZER_H
#define VARIANTSERIALIZER_H

#include <QtCore>

class VariantSerializer;

typedef VariantSerializer* VSerializer;

class VariantSerializer
{
public:
    VariantSerializer(const QVariant &variant);
    VariantSerializer(const VariantSerializer &other);
    QVariant variant() const;
    QByteArray data() const;
    bool isValid() const;

    virtual void serialize();

    static VSerializer Serialize(const QVariant &variant);

private:
    QVariant _variant;
    QByteArray _data;
    bool _isValid;
};

#endif // VARIANTSERIALIZER_H
