#include "notification.h"

Notification::Notification(Domain* domain, const QVariant &data)
    :_domain(domain), _data(data)
{

}

Domain* Notification::domain() const
{
    return _domain;
}

QVariant Notification::variant() const
{
    return _data;
}
