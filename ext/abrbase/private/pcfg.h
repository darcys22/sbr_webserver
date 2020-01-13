#ifndef __ABR_CFG_PRIVATE_H__
#define __ABR_CFG_PRIVATE_H__

#include "abrbase/cfg.h"

/* @defgroup abrbase_api_pcfg PConfiguration
@ingroup abrbase_api_private
Load, create, and managing Configuration and ConfigurationManager objects.

Each Configuration Manager contains 0 or more Configurations, where each Configuration represents the configuration 
and runtime information (including associated errors - see abr_Err), for any object using the configuration.

@{
*/

#ifdef __cplusplus
extern "C" {
#endif 

ABR_EXPORT void abre_cfgm_create(abr_Ctx *ctx, abr_CfgMgr **obj, const char *cfgbuffer, const char *cfgid);
ABR_EXPORT void abre_cfgm_save(abr_Ctx *ctx, abr_CfgMgr *mgr, char **cfgbuffer);
ABR_EXPORT void abre_cfgm_addnamespace(abr_Ctx *ctx, abr_CfgMgr *mgr, const char *prefix, const char *uri);

#ifdef __cplusplus
}
#endif 

/**
Get the "@value" attribute contents for the given "itemname" or return "defvalue" if not found - see abr_cfg_str() and abr_ctx_item().
*/
#define ABR_CFG_STR(ctx, itemname, defvalue) abr_cfgi_str(abr_ctx_item((ctx), (itemname)), abr_CfgA_value, (defvalue))

/**
Convenience int wrapper for abr_cfg_int() and abr_ctx_item().
*/
#define ABR_CFG_INT(ctx, itemname, defvalue) abr_cfgi_int(abr_ctx_item((ctx), (itemname)), abr_CfgA_value, (defvalue))

/**
Convenience bool wrapper for abr_cfg_int() and abr_ctx_item().
*/
#define ABR_CFG_BOOL(ctx, itemname, defvalue) abr_cfgi_bool(abr_ctx_item((ctx), (itemname)), abr_CfgA_value, (defvalue))

/**
Set/Create the "@value" attribute contents for the given "itemname" - see abr_cfg_setstr() and abr_ctx_item().
*/
#define ABR_CFG_SETSTR(ctx, itemname, value) abr_cfgi_setstr(abr_ctx_item((ctx), (itemname)), abr_CfgA_value, (value))

/**
Get the "@value" attribute contents for the given "itemname(id)" or return "defvalue" if not found - see abr_cfg_str() and abr_ctx_itemid().
*/
#define ABR_CFG_IDSTR(ctx, id, itemname, defvalue) abr_cfgi_str(abr_ctx_itemid((ctx), (id), (itemname)), abr_CfgA_value, (defvalue))

/**
Convenience int wrapper for abr_cfg_int() and abr_ctx_itemid().
*/
#define ABR_CFG_IDINT(ctx, id, itemname, defvalue) abr_cfgi_int(abr_ctx_itemid((ctx), (id), (itemname)), abr_CfgA_value, (defvalue))

/**
Convenience bool wrapper for abr_cfg_int() and abr_ctx_itemid().
*/
#define ABR_CFG_IDBOOL(ctx, id, itemname, defvalue) abr_cfgi_bool(abr_ctx_itemid((ctx), (id), (itemname)), abr_CfgA_value, (defvalue))

/**
Set/Create the "@value" attribute contents for the given "itemname(id)" - see abr_cfg_setstr() and abr_ctx_itemid().
*/
#define ABR_CFG_IDSETSTR(ctx, id, itemname, value) abr_cfgi_setstr(abr_ctx_itemid((ctx), (id), (itemname)), abr_CfgA_value, (value))


/*! @} */

#endif /*__ABR_CFG_PRIVATE_H__*/

