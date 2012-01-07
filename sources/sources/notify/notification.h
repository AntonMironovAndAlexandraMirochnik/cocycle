#ifndef NOTIFICATIONS_NOTIFICATION_H
#define NOTIFICATIONS_NOTIFICATION_H

#include "notify_global.h"

class Notification/* : public Exportable */
{
    friend class Domain;

private:
    Domain* _domain;
    QVariant _data;

protected:
    Notification(Domain* domain, const QVariant &data);

public:
    Domain* domain() const;
    QVariant variant() const;

};

#endif // NOTIFICATIONS_NOTIFICATION_H
