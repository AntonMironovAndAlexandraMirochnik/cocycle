#include "domain.h"

QMap<int, Domain*> Domain::domainRegister;
DomainIndex Domain::greatestRegisteredIndex = UndefinedDomainIndex;

Domain::Domain(DomainType domainType,
       DomainIndex index,
       const QString &description)
    : //Exportable(),
      _domainType(domainType),
      _index(index),
      _description(description)
{
    domainRegister.insert(index, this);
}

DomainIndex Domain::registerDomain(DomainType domainType)
{
    return registerDomain(domainType, ++greatestRegisteredIndex);
}

DomainIndex Domain::registerDomain(DomainType domainType,
                                   const QString &description)
{
    return registerDomain(domainType, ++greatestRegisteredIndex, description);
}

DomainIndex Domain::registerDomain(DomainType domainType,
                                   DomainIndex index)
{
    QString description;
    switch (domainType)
    {
    case Notification:
        description = "<Notification domain>";
        break;
    case Warning:
        description = "<Warning domain>";
        break;
    case Critical:
        description = "<Critical domain>";
        break;
    case BadInput:
        description = "<Bad Input domain>";
        break;
    case InvalidPermisson:
        description = "<Invalid Permisson domain>";
        break;
    default:
        description = "<User domain>";
        break;
    }
    return registerDomain(domainType, index, description);
}

DomainIndex Domain::registerDomain(DomainType domainType,
                                   DomainIndex index,
                                   const QString &description)
{
    DomainIndex result = UndefinedDomainIndex;
    if (!domainRegister.contains(index))
    {
        result = index;
        new Domain(domainType, result, description);
    }

    if (greatestRegisteredIndex < result)
    {
        greatestRegisteredIndex = result;
    }

    return result;
}

Domain* Domain::domain(DomainIndex domainIndex)
{
    Domain* result = nullptr;

    DomainRegister::const_iterator iterator = domainRegister.find(domainIndex);
    if (iterator != domainRegister.constEnd())
    {
        result = *iterator;
    }

    return result;
}

DomainType Domain::domainType() const
{
    return _domainType;
}

DomainIndex Domain::index() const
{
    return _index;
}

QString Domain::description() const
{
    return _description;
}

QString Domain::dataToExport() const
{
    QString result;

    result = QString("index:%1,\ndesc:\"%2\"")
            .arg(index())
            .arg(description());

    return result;
}
