#ifndef __ABR_CFG_H__
#define __ABR_CFG_H__

#include <stddef.h>

/** @addtogroup abrbase_api_public_cfgcore

@{
*/

/**
A Configuration object such as "prod", "test"
*/
typedef struct _abr_Cfg abr_Cfg;

#include "abrbase/cfgm.h"

#include "abrbase/cfgi.h"

#ifdef __cplusplus
extern "C" {
#endif 

/**
Return the abr_CfgMgr this configuration belongs to.
@param cfg the configuration.
@return configuration manager.
*/
ABR_EXPORT abr_CfgMgr *abr_cfg_mgr(abr_Cfg *cfg);

/**
Get the "id" of the current configuration.
@param cfg the configuration.
@return id 
*/
ABR_EXPORT const char *abr_cfg_id(abr_Cfg *cfg);

/**
Get the "ref" attribute for the current configuration, if any.
"ref" can be a comma or semi-colon delimited string.
@param cfg the configuration.
@return ref attribute value. 
*/
ABR_EXPORT const char *abr_cfg_ref(abr_Cfg *cfg);

#ifdef __cplusplus
}
#endif 

/*! @} */

#endif /*__ABR_CFG_H__*/
