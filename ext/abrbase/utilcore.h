#ifndef __ABR_UTILCORE_H__
#define __ABR_UTILCORE_H__

#include <stddef.h>

/* @defgroup abrbase_api_util Util
@ingroup abrbase_api_public

@{
*/

#ifdef __cplusplus
extern "C" {
#endif 

/**
Free v if not NULL and return NULL.
Any strings allocated by the dependant libraries should be freed using this. 
That is, the library that allocates memory, should free it.
If client code frees such memory, it may work, or may result in segmentation faults.
*/
ABR_EXPORT void *abr_free(void *v);

#ifdef __cplusplus
}
#endif 

/*! @} */

#endif /*__ABR_UTILCORE_H__*/
