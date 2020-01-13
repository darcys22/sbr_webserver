#ifndef __ABR_LIB_PRIVATE_H__
#define __ABR_LIB_PRIVATE_H__

#include "abrbase/lib.h"

#ifdef __cplusplus
extern "C" {
#endif 

ABR_EXPORT void abr_base_var_set(const char *name, const char *value);
ABR_EXPORT bool abr_base_var(const char *name, const char **value);

#ifdef __cplusplus
}
#endif 

#define ABR_FN_TRACESTART() \
	(abr_log_start(log, ABR_LOG_TRACE, _loglevel, _library, _module, function, ""))
#define ABR_FN_TRACEEND()	\
	{ \
	ABR_CTX_ERR_CHECK(ctx, errcode); \
	if (errcode != ABR_ERR_OK) abr_ctx_log(ctx); \
	abr_log_end(log, ABR_LOG_TRACE, _loglevel, _library, _module, function, errcode != 0, ""); \
	}

#endif /*__ABR_LIB_PRIVATE_H__*/
