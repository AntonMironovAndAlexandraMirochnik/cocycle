#ifndef NOTIFY_GLOBAL_H
#define NOTIFY_GLOBAL_H

#include<QtCore>

//forward class declarations
class Domain;
class Notification;

//type defines
typedef int DomainIndex;
typedef int DomainType;

//template classes concretization
typedef QMap<DomainIndex, Domain*> DomainRegister;

//definitions
static const DomainIndex UndefinedDomainIndex = 0;

#endif // NOTIFY_GLOBAL_H
