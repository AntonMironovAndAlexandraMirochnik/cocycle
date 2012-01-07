#ifndef EXTENDED_CACHE_DELEGATE_H
#define EXTENDED_CACHE_DELEGATE_H

#include "extended_cache_global.h"

template <class Key>
class ExtendedCacheDelegate
{
public:
    virtual QSharedPointer<ExtendedCacheObject<Key> > extendedCacheObject(
            ExtendedCache<Key> *cache,
            const Key &key) = 0;

    virtual void extendedCacheRequestObject(
            ExtendedCache<key> *cache,
            const Key &key) = 0;
};

#endif // EXTENDED_CACHE_DELEGATE_H
