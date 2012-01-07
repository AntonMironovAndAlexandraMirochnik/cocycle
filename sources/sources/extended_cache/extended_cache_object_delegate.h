#ifndef EXTENDED_CACHE_MAP_DELEGATE_H
#define EXTENDED_CACHE_MAP_DELEGATE_H

#include "extended_cache_global.h"

template <class Key>
class ExtendedCacheObjectDelegate
{
public:
    virtual void release(void* object) = 0;
};

#endif // EXTENDED_CACHE_MAP_DELEGATE_H
