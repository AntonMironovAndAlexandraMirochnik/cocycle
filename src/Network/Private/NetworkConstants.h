#ifndef NETWORKCONSTANTS_H
#define NETWORKCONSTANTS_H

#include <QtCore>
#include <QtNetwork/QtNetwork>
#include "Log.h"

class NetworkThread;
class NetworkClient;
class NetworkServer;

class NetworkController;
class NetworkConnectionClient;
class NetworkConnectionServer;

typedef QPointer<NetworkClient> NClient;
typedef QPointer<NetworkServer> NServer;
typedef QPointer<NetworkConnectionClient> NConnectionClient;
typedef QPointer<NetworkConnectionServer> NConnectionServer;

#endif // NETWORKCONSTANTS_H
