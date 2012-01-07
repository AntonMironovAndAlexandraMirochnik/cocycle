#include "notify.h"
#include "extended_cache.h"

class Object : public ExtendedCacheObject<int>
{
    static int keyCount;
    const int _key;
public:
    Object() : ExtendedCacheObject<int>(), _key(++keyCount)
    {}

    virtual int key() const
    {return _key;}
};

typedef ExtendedCache<int, Object> Cache;

int Object::keyCount = 0;

int main()
{
    Domain::registerDomain(Domain::UserDomainType);

    Cache cache(1);

    QSharedPointer<Object> object1 = cache.insertAndGetStrongRef(new Object());
    QSharedPointer<Object> object2 = cache.insertAndGetStrongRef(new Object());

    qDebug() << QString("Object #1 id = %1").arg(object1->key());
    qDebug() << QString("Object #2 id = %1").arg(object2->key());

    object1.clear();
    object2.clear();

    return 0;
}
