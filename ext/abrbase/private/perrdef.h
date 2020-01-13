#ifndef __ABR_ERRDEF_PRIVATE_H__
#define __ABR_ERRDEF_PRIVATE_H__

/* @defgroup abrbase_api_perrdef PError Definition
@ingroup abrbase_api_private

@{
*/

//#include "abrbase/errdef.h"

#ifdef __cplusplus
extern "C" {
#endif 

/** @internal
*/
ABR_EXPORT void abr_errdef_add(int errcode, const char *library, const char *name, const char *msg);

/** @internal
The string representation of the errcode
@param errcode the errorcode int
@return errcode name
*/
ABR_EXPORT const char *abr_errdef_name(int errcode);

/** @internal
The default error msg (may be blank)
@param errcode the errorcode int
@return error message
*/
ABR_EXPORT const char *abr_errdef_msg(int errcode);

/** @internal
The library the errcode belongs to
@param errcode the errorcode int
@return library name
*/
ABR_EXPORT const char *abr_errdef_library(int errcode);

#ifdef __cplusplus
}
#endif 


/*! @} */

#endif /*__ABR_ERRDEF_PRIVATE_H__*/
