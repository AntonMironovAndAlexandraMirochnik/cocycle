#ifndef EXTENDED_CACHE_OBJECT_H
#define EXTENDED_CACHE_OBJECT_H

#include "extended_cache_global.h"
#include "extended_cache_object_delegate.h"

template <class Key>
class ExtendedCacheObject
{
private:
    ExtendedCacheObjectDelegate<Key>* _cacheDelegate;

public:
    virtual Key key() const = 0;
    virtual int cost() const
    {
        return 1;
    }

    ExtendedCacheObjectDelegate<Key>* cacheDelegate() const
    {
        return _cacheDelegate;
    }

    void setCacheDelegate(ExtendedCacheObjectDelegate<Key>* cacheDelegate)
    {
        _cacheDelegate = cacheDelegate;
    }

    void release()
    {
        cacheDelegate()->release(this);
    }
};

#endif // EXTENDED_CACHE_OBJECT_H
