#ifndef NETWORKCONTROLLER_H
#define NETWORKCONTROLLER_H

#include "NetworkConstants.h"

class NetworkController : public QObject {
    Q_OBJECT
public:
    explicit NetworkController();
    
public slots:
    void initClient(NClient client);
    void initServer(NServer server);

};

Q_DECLARE_METATYPE(NClient)
Q_DECLARE_METATYPE(NServer)
Q_DECLARE_METATYPE(NConnectionClient)
Q_DECLARE_METATYPE(NConnectionServer)
Q_DECLARE_METATYPE(QHostAddress)

#endif // NETWORKCONTROLLER_H
