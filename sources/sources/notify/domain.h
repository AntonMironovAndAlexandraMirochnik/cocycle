#ifndef NOTIFICATIONS_DOMAIN_H
#define NOTIFICATIONS_DOMAIN_H

#include "notify_global.h"
//#include"exportable.h"

class Domain/* : public Exportable */
{

public:
    enum
    {
        Notification = 1,
        Warning,
        Error,
        Critical,
        //specific domain types
        BadInput,
        InvalidPermisson,
        UserDomainType
    };

private:
    const DomainType _domainType;
    const DomainIndex _index;
    const QString _description;

    static DomainRegister domainRegister;
    static DomainIndex greatestRegisteredIndex;

protected:
    Domain(DomainType domainType,
           DomainIndex index,
           const QString &description);
    virtual QString dataToExport() const;

public:
    static DomainIndex registerDomain(DomainType domainType);

    static DomainIndex registerDomain(DomainType domainType,
                                      const QString &description);

    static DomainIndex registerDomain(DomainType domainType,
                                      DomainIndex index);

    static DomainIndex registerDomain(DomainType domainType,
                                      DomainIndex index,
                                      const QString &description);

    static Domain* domain(DomainIndex domainIndex);

    DomainIndex index() const;
    QString description() const;
    DomainType domainType() const;
};

#endif // NOTIFICATIONS_DOMAIN_H
