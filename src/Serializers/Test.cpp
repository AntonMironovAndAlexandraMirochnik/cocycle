
#include "DomDocument.h"
#include "VariantSerializer.h"
#include "VariantBackwardSerializer.h"

int main() {
    QVariantList list;
    list << "Hello World" << 0.123 << 123 << QDate::currentDate() << QTime::currentTime() << QDateTime::currentDateTime();
    QVariantMap map;
    map["string"] = list[0];
    map["float"] = list[1];
    map["int"] = list[2];
    map["date"] = list[3];
    map["time"] = list[4];
    map["date_time"] = list[5];
    map["list"] = list;

    QByteArray data1;
    QByteArray data2;
    QVariant variantResult;
    bool isOK = true;
    if (isOK) {
        VariantSerializer serializer(map);
        data1 = serializer();
        isOK = serializer.isValid();
        qDebug() << data1;
    }
    if (isOK) {
        VariantBackwardSerializer deserializer(data1);
        variantResult = deserializer();
        isOK = deserializer.isValid();
        qDebug() << variantResult;
    }
    if (isOK) {
        DomDocument doc;
        QDomElement domMap = doc.domValue(variantResult, isOK);
        doc.appendChild(domMap);
        data2 = doc.toByteArray();
        qDebug() << data2;
    }

    isOK = isOK && (data1 == data2);
    qDebug() << (isOK ? "OK" : "FAIL");

    return 0;
}
