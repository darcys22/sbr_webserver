#ifndef __ABR_ERRH_PRIVATE_H__
#define __ABR_ERRH_PRIVATE_H__

#include "abrbase/errh.h"

typedef bool (abr_errfunction)(abr_Ctx *ctx, abr_Err *err, abr_Log *log);

#ifdef __cplusplus
extern "C" {
#endif 

ABR_EXPORT int abr_errh_sethandler(abr_errfunction errfunction, const char *library);

#ifdef __cplusplus
}
#endif 

#endif /*__ABR_ERRH_PRIVATE_H__*/
