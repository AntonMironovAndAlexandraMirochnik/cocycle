#ifndef VARIANTBACKWARDSERIALIZER_H
#define VARIANTBACKWARDSERIALIZER_H

#include <QtCore>

class VariantBackwardSerializer
{
public:
    VariantBackwardSerializer(const QByteArray &data);
    QVariant variant() const;
    QByteArray data() const;
    bool isValid() const;

    QVariant operator()();

protected:
    virtual QVariant deserialize(const QByteArray &data, bool &isOK);

private:
    QVariant _variant;
    QByteArray _data;
    bool _isValid;
};
#endif // VARIANTBACKWARDSERIALIZER_H
