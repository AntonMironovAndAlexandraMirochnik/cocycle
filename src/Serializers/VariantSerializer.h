#ifndef VARIANTSERIALIZER_H
#define VARIANTSERIALIZER_H

#include <QtCore>

class VariantSerializer
{
public:
    VariantSerializer(const QVariant &variant);
    QVariant variant() const;
    QByteArray data() const;
    bool isValid() const;

    QByteArray operator()();

protected:
    virtual QByteArray serialize(const QVariant &variant, bool &isOK);

private:
    QVariant _variant;
    QByteArray _data;
    bool _isValid;
};

#endif // VARIANTSERIALIZER_H
