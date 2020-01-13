#ifndef __ABR_LIB_H__
#define __ABR_LIB_H__

/** @addtogroup abrbase_api_public_lib

@{
*/

#ifdef __cplusplus
extern "C" {
#endif 

/**
Return the version of the ABR Base API.
@return version in the form major.minor.patch.tweak (not all levels may be present)
*/
ABR_EXPORT const char *abr_base_version(void);

/**
Returns whether or not the abr base library is initialised.

@return TRUE or FALSE.
*/ 
ABR_EXPORT bool abr_base_isinited(void);

/**
Initialise the SDK - see also abr_base_deinit(). 

This must be called at application startup prior to any threads being started, 
and before any other initialisation routines but AFTER the first main context 
object is created using abr_ctx_create() AND AFTER the softwareinfo object has been 
set using abr_si_set().

Subsequent calls to this are ignored.

@param ctx the main context object for associated error information if any.
@param flag used to control the initialisation process - use ABR_BASE_INIT_ALL unless advised otherwise.

@return ABR_ERR_OK or an error code - see abr_ctx_err() for any error details
*/
ABR_EXPORT int abr_base_init(abr_Ctx *ctx, unsigned short flag);

/**
Deinitialise the SDK. This must be called at application shutdown after threads are finished and 
any allocated objects freed.

Subsequent calls to this are ignored.

abr_base_deinit() should be called after all other deinitialisation routines are called.
*/
ABR_EXPORT void abr_base_deinit(void);

#ifdef __cplusplus
}
#endif 

/*! @} */

#endif /*__ABR_LIB_H__*/
