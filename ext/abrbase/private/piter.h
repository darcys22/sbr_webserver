#ifndef __ABR_ITER_PRIVATE_H__
#define __ABR_ITER_PRIVATE_H__

/* @defgroup abrbase_api_piter PIter
@ingroup abrbase_api_private

@{
*/

#include "abrbase/iter.h"

#ifdef __cplusplus
extern "C" {
#endif 

/**
Create an iterator for the given non-NULL collection - caller must free it.

This, and related methods, are generic methods, useful for collections shared between 
threads where each thread may have its own iterator. Because these methods use void pointers, they
do not have type safety.

@param collection the collection.

@return a new iterator or NULL if the collection is NULL.
*/
ABR_EXPORT abr_Iterator *abr_iter_create_lst(abr_List *list);

ABR_EXPORT abr_Iterator *abr_iter_create_arr(void **arr, size_t count);

#ifdef __cplusplus
}
#endif 

/*! @} */

#endif /*__ABR_ITER_PRIVATE_H__*/

