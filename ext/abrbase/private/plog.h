#ifndef __ABR_LOG_PRIVATE_H__
#define __ABR_LOG_PRIVATE_H__

/* @defgroup abrbase_api_plog PLog
@ingroup abrbase_api_private

@{
*/

#include "abrbase/log.h"

#define ABR_LOG_MSG(log, targetlevel, msg) \
	(abr_log_msg((log), (targetlevel), _loglevel, _library, _module, function, (msg)))
#define ABR_LOG_MSGV(log, targetlevel, fmt, ...) \
	(abr_log_msg((log), (targetlevel), _loglevel, _library, _module, function, (fmt), __VA_ARGS__))
#define ABR_LOG_TRACESTART(log) \
	(abr_log_start((log), ABR_LOG_TRACE, _loglevel, _library, _module, function, ""))
#define ABR_LOG_TRACEEND(log, errcode)	\
	(abr_log_end((log), ABR_LOG_TRACE, _loglevel, _library, _module, function, errcode != 0, ""))

//typedef void (abr_setloglevelfn)(abr_eLoglevel level);

#ifdef __cplusplus
extern "C" {
#endif 

//ABR_EXPORT int abr_initfnloglevel(const char *library, const char *module, unsigned short moduleid, abr_eLoglevel level, abr_setloglevelfn setloglevelfn);
ABR_EXPORT abr_eLoglevel abr_log_defaultlevel(abr_Log *log);

#ifdef __cplusplus
}
#endif 

/*! @} */

#endif /*__ABR_LOG_PRIVATE_H__*/

