#ifndef __ABR_ITER_H__
#define __ABR_ITER_H__

/** @addtogroup abrbase_api_public_iter

@{
*/

/**
The iteration object. 

Note that the underlying container is implementation dependent, private, and therefore not exposed. 
The iterator methods simply return the underlying values which must be cast to the correct type.
Warning: this is not type safe, so be sure to use the correct iterator for the type.

Preferably, where an object implements a collection (or multiple), it should provide type-safe wrappers for these methods 
for the given collection. 
*/
typedef struct _abr_Iterator abr_Iterator;

#ifdef __cplusplus
extern "C" {
#endif 

/**
Free an iterator. 

@param iter the iterator.

*/
ABR_EXPORT void abr_iter_free(abr_Iterator *iter);

/**
Get the first value in the collection. 

This also primes or resets the iterator to the start for use by abr_iter_nextv(). 

@param iter the iterator.

@return a new iterator.
*/
ABR_EXPORT void *abr_iter_firstv(abr_Iterator *iter);

/**
Get the next value in the collection - see also abr_iter_firstv().

@param iter the iterator.

@return a new iterator.
*/
ABR_EXPORT void *abr_iter_nextv(abr_Iterator *iter);


#ifdef __cplusplus
}
#endif 

/*! @} */

#endif /*__ABR_ITER_H__*/

