#ifndef __ABR_NET_PRIVATE_H__
#define __ABR_NET_PRIVATE_H__

#include "abrbase/net.h"

typedef struct _abr_Net abr_Net;

#ifdef __cplusplus
extern "C" {
#endif 

ABR_EXPORT size_t abr_net_settimeout(abr_Net *net, size_t timeout);
ABR_EXPORT size_t abr_net_settimeoutconnect(abr_Net *net, size_t timeout);
ABR_EXPORT size_t abr_net_timeout(abr_Net *net);
ABR_EXPORT size_t abr_net_timeoutconnect(abr_Net *net);

ABR_EXPORT void abr_net_create(abr_Ctx *ctx, abr_Net **net, const char *url, const char *contenttype);
ABR_EXPORT void abr_net_free(abr_Net *net);
ABR_EXPORT void abr_net_setproxy(abr_Net *net, const char *url, const char *userpwd, const char *excludehosts);
ABR_EXPORT abr_NetData *abr_net_request(abr_Ctx *ctx, abr_Net *net, abr_String *data);
ABR_EXPORT abr_NetData *abr_net_requestmp(abr_Ctx *ctx, abr_Net *net, abr_NetData *netdata);

ABR_EXPORT size_t abr_net_timeout_default(abr_Ctx *ctx);
ABR_EXPORT size_t abr_net_timeoutconnect_default(abr_Ctx *ctx);

#ifdef __cplusplus
}
#endif 

#endif /*__ABR_NET_PRIVATE_H__*/
