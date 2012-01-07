#ifndef EXTENDED_CACHE_IMPL_H
#define EXTENDED_CACHE_IMPL_H

#include "extended_cache_global.h"
#include "extended_cache_object.h"

template <class Key, class Object>
class ExtendedCache : public ExtendedCacheObjectDelegate<Key>
{
private:
    typedef QCache<Key, Object > DataCache;
    typedef QHash<Key, QWeakPointer<Object > > DataMap;

    DataCache cache;
    DataMap map;

    QSharedPointer<Object> retain(const Key &key)
    {
        Object* object = cache.take(key);
        object->setCacheDelegate(this);
        QSharedPointer<Object> result(object, &Object::release);
        map.insert(key, result.toWeakRef());
        return result;
    }

    QSharedPointer<Object > retain(Object *object)
    {
        return retain(object->key());
    }

public:
    ExtendedCache(int maxCost = 1024) : cache(maxCost)
    {}

    // delegate members
    void release(void* object_)
    {
        Object* object = (Object*)object_;
        cache.insert(object->key(), object, object->cost());
        map.remove(object->key());
    }

    bool contains(const Key &key) const
    {
        return cache.contains(key) || map.contains(key);
    }

    int count() const
    {
        return cache.count() + map.count();
    }

    int countOfCached() const
    {
        return cache.count();
    }

    QSharedPointer<Object> insertAndGetStrongRef(Object *object)
    {
        QSharedPointer<Object> result;
        Key key = object->key();
        if (!map.contains(key))
        {
            result = QSharedPointer<Object>(object, &Object::release);
            object->setCacheDelegate(this);
            map.insert(key, result.toWeakRef());
        }
        return result;
    }

    bool insert(Object *object)
    {
        return cache.insert(object->key(), object, object->cost());
    }

    bool isEmpty() const
    {
        return cache.isEmpty() && map.isEmpty();
    }

    QList<Key> keys() const
    {
        QList<Key> result;
        result.append(cache.keys());
        result.append(map.keys());
        return result;
    }

    int maxCost() const
    {
        return cache.maxCost();
    }

    Object* object(const Key &key)
    {
        Object* result = NULL;
        while (true)
        {
            if (cache.contains(key))
            {
                result = cache[key];
                break;
            }

            if (map.contains(key))
            {
                result = map[key].data();
                break;
            }

            break;
        }
        return result;
    }

    QSharedPointer<Object > objectStrongRef(const Key &key)
    {
        QSharedPointer<Object > result;
        while (true)
        {
            if (cache.contains(key))
            {
                result = retain(key);
                break;
            }

            if (map.contains(key))
            {
                result = map[key].toStrongRef();
                break;
            }

            break;
        }
        return result;
    }

    void setMaxCost(int cost)
    {
        cache.setMaxCost(cost);
    }

    int size() const
    {
        return cache.size() + map.size();
    }

    int totalConst() const
    {
        return cache.totalCost();
    }

    Object* operator[](const Key &key)
    {
        return object(key);
    }
};

#endif // EXTENDED_CACHE_IMPL_H
