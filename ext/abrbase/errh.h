#ifndef __ABR_ERRH_H__
#define __ABR_ERRH_H__

/** @addtogroup abrbase_api_public_errh

@{
*/

#ifdef __cplusplus
extern "C" {
#endif 

/**
Invoke the error handler for any errors in the Context. 

Each SDK has its own handler to handle custom error objects the SDK may produce.

The error handler interprets the error and calls the logging function. 

The default logging function can be replaced by the application - see abr_log_setlogfn().

@param ctx the thread local context containing 0 or more (nested) @ref abr_Err objects.
@param errcode the error code of the top level error object. If this does not match, it indicates
a coding error has occurred which will result in an assertion failure.

@return TRUE if the error was processed (i.e. logged) or FALSE otherwise.
*/
ABR_EXPORT bool abr_errh_handler(abr_Ctx *ctx, int errcode);

#ifdef __cplusplus
}
#endif 

/*! @} */

#endif /*__ABR_ERRH_H__*/

