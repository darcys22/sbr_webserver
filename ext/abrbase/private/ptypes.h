#ifndef __ABR_TYPES_PRIVATE_H__
#define __ABR_TYPES_PRIVATE_H__

#include "abrbase/types.h"

#define ABR_RETHROW_ONERR(errcode) { if ((errcode) != ABR_ERR_OK) Throw (errcode); }

typedef void (abr_setloglevelfn)(abr_eLoglevel level);
typedef void (abr_setlogfiledumpfn)(bool filedump);

typedef struct _abr_LibModule abr_LibModule;


#ifdef __cplusplus
extern "C" {
#endif 

ABR_EXPORT abr_LibModule *abr_initfnloglevel(const char *library, const char *module, unsigned long moduleid, abr_eLoglevel level, abr_setloglevelfn setloglevelfn);
ABR_EXPORT void abr_initfnlogfiledump(abr_LibModule *moddefn, bool filedump, abr_setlogfiledumpfn setlogfiledumpfn);

#ifdef __cplusplus
}
#endif 

#endif /*__ABR_TYPES_PRIVATE_H__*/
