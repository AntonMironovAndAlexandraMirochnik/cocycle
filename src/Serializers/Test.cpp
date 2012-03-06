
#include "DomDocument.h"
#include "VariantSerializer.h"
#include "VariantBackwardSerializer.h"

int main() {
    QVariantList list;
    list << "Hello World" << false << 0.123 << 123 << QDate::currentDate() << QTime::currentTime() << QDateTime::currentDateTime();
    QVariantMap map;
    int i = 0;
    map["string"] = list[i++];
    map["bool"] = list[i++];
    map["float"] = list[i++];
    map["int"] = list[i++];
    map["date"] = list[i++];
    map["time"] = list[i++];
    map["date_time"] = list[i++];
    map["list"] = list;

    QByteArray data1;
    QByteArray data2;
    QVariant variantResult;
    bool isOK = true;
    if (isOK) {
        VariantSerializer* serializer = VariantSerializer::Serialize(map);
        data1 = serializer->data();
        isOK = serializer->isValid();
        qDebug() << data1;
    }
    if (isOK) {
        VariantBackwardSerializer* deserializer = VariantBackwardSerializer::Deserialize(data1);
        variantResult = deserializer->variant();
        isOK = deserializer->isValid();
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
