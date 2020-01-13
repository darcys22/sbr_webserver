#ifndef __ABR_CTX_PRIVATE_H__
#define __ABR_CTX_PRIVATE_H__

#include "abrbase/ctx.h"

/* @defgroup abrbase_api_pctx PContext
@ingroup abrbase_api_private

@{
*/

#ifdef __cplusplus
extern "C" {
#endif 

ABR_EXPORT struct exception_context *abr__ctx_ec(abr_Ctx *ctx);

/**@internal
Clear any errors associated with the current context. 
This is done at the start of any method which can generate errors.
@param ctx the context or NULL.
@return ABR_ERR_OK if successful.
*/
ABR_EXPORT int abr_ctx_err_clear(abr_Ctx *ctx);

/**@internal
Create an error object associated with the current context. 
This will wrap any existing error object as an "inner" error.
@param ctx the context or NULL.
@param library the source library generating the error
@param module the library module
@param function the function
@param line __LINE__
@param code the error code, not being ABR_ERR_OK
@param severity the severity of the error - most are ABR_ESEVERITY_WARN 
@param msg specific message for the error. 
@param customobj a custom object to attach to the error. This is interpreted by the source creating the error.
@return ABR_ERR_OK if successful.
*/
ABR_EXPORT int abr_ctx_err_new(abr_Ctx *ctx, const char *library, const char *module, const char *function, int line, int code, abr_eErrSeverity severity, void *customobj, const char *msg);

ABR_EXPORT int abr_ctx_err_vnew(abr_Ctx *ctx, const char *library, const char *module, const char *function, int line, int code, abr_eErrSeverity severity, void *customobj, size_t size, const char *format, ...);

ABR_EXPORT void *abr_ctx_cache(abr_Ctx *ctx, const char *key);

ABR_EXPORT void *abr_ctx_cache_set(abr_Ctx *ctx, const char *key, void *value);

#ifdef __cplusplus
}
#endif 

/**
Creates an error object, using the given severity, in the context and wraps any existing error. 
*/
#define ABR_CTX_NEWERR_SEV(ctx, code, severity, msg) \
	abr_ctx_err_new(ctx, _library, _module, function, __LINE__, (code), (severity), NULL, (msg))

/**
Creates an error object in the context and wraps any existing error. Assigns severity level ABR_ESEVERITY_WARN.
*/
#define ABR_CTX_NEWERR(ctx, code, msg) \
	abr_ctx_err_new(ctx, _library, _module, function, __LINE__, (code), ABR_ESEVERITY_WARN, NULL, (msg))

/**
Creates an error object in the context and wraps any existing error. Assigns severity level ABR_ESEVERITY_WARN.
*/
#define ABR_CTX_VNEWERR(ctx, code, argsize, format, ...) \
	abr_ctx_err_vnew(ctx, _library, _module, function, __LINE__, (code), ABR_ESEVERITY_WARN, NULL, argsize, format, __VA_ARGS__)

#define ABR_CTX_FN_START(ctx) { \
	ABR_LOG_TRACESTART(abr_ctx_log((ctx))); \
	abr_ctx_err_clear((ctx)); \
	}

#define ABR_CTX_FN_END(ctx, errcode) { \
	abr_errh_handler((ctx), (errcode)); \
	ABR_LOG_TRACEEND(abr_ctx_log((ctx)), (errcode)); \
	}

/*! @} */

#endif /*__ABR_CTX_PRIVATE_H__*/

