#ifndef __ABR_CTXM_H__
#define __ABR_CTXM_H__

#include <stddef.h>

/** @addtogroup abrbase_api_public_cfgmgr

Each Configuration Manager contains 0 or more Configurations, where each Configuration contains values accessed by
code at runtime. Each configuration represents a collection of such values and typically represent environments such as
production, test, development, etc. Configurations within a "Manager" (i.e. a "collection" of Configurations) can
reference each other. This allows a standard set of values to be setup in, for example, 'prod', with only 
a select subset of values overriden in, say 'test', which has a reference to the production configuration. 
Such "inheritance" is restricted to 50 levels, otherwise an assertion will result 
(which is sufficient to also catch circular references).

@{
*/

/**
The Configuration Manager containing 0 or more abr_Cfg.
*/
typedef struct _abr_CfgMgr abr_CfgMgr;

#ifdef __cplusplus
extern "C" {
#endif 

/**
Create a configuration manager containing multiple configurations from the cfgbuffer.

@param ctx current thread local context object.
@param mgr the address of the object to create. The caller must free with abr_cfgm_free().
@param cfgbuffer must contain a valid AbrConfigurations XML string even if no AbrConfiguration is defined - see standard config file abrdefconfig.xml.
@param cfgid the configuration to attach to the context.
@return ABR_ERR_OK or an error code.
*/
ABR_EXPORT int abr_cfgm_create(abr_Ctx *ctx, abr_CfgMgr **mgr, const char *cfgbuffer, const char *cfgid);

/**
Free the abr_CfgMgr object. All internal configurations are freed as well, so ensure no object derived from
this manager is in use.
@param mgr configuration manager
*/
ABR_EXPORT void abr_cfgm_free(abr_CfgMgr *mgr);

/**
Add a namespace if adding custom elements and attributes. The default is "abr=http://auth.abr.gov.au/xsd/AbrConfig".
@param ctx current thread local context object.
@param mgr the configuration manager.
@param prefix used in XPath and node references. 
Note that the default "abr" is not required in the XML or XPath attribute references - only XPath element references.
@param uri the namespace URI
@return ABR_ERR_OK or an error code.
*/
ABR_EXPORT int abr_cfgm_addnamespace(abr_Ctx *ctx, abr_CfgMgr *mgr, const char *prefix, const char *uri);

/**
Save the contents into a buffer as an XML string.
@param ctx current thread local context object.
@param mgr the configuration manager.
@param cfgbuffer the address of the buffer to return the XML string to. Must be freed by the caller. 
@return ABR_ERR_OK or an error code.
*/
ABR_EXPORT int abr_cfgm_save(abr_Ctx *ctx, abr_CfgMgr *mgr, char **cfgbuffer);

/**
Check whether any configuration has changed or configurations added or deleted.
@param mgr the configuration manager.
@return TRUE or FALSE.
*/
ABR_EXPORT bool abr_cfgm_isdirty(abr_CfgMgr *mgr);

/**
Return the id of the configuration manager if any.
@param mgr the configuration manager.
@return id of the manager.
*/
ABR_EXPORT const char *abr_cfgm_id(abr_CfgMgr *mgr);

/**
Return the description of the configuration manager if any.
@param mgr the configuration manager.
@return description of the manager.
*/
ABR_EXPORT const char *abr_cfgm_description(abr_CfgMgr *mgr);

/**
Return the configuration corresponding the cfgid.
@param mgr the configuration manager.
@param cfgid the configuration id to select.
@return the configuration.
*/
ABR_EXPORT abr_Cfg *abr_cfgm_cfg(abr_CfgMgr *mgr, const char *cfgid);

/**
Return a NULL terminated array of all configuration ids defined in the manager.
@param mgr the configuration manager.
@param cfgids the address to allocate the array to. Must be freed by the caller.
@return the number of elements.
*/
ABR_EXPORT size_t abr_cfgm_cfgids(abr_CfgMgr *mgr, const char ***cfgids);

#ifdef __cplusplus
}
#endif 

/*! @} */

#endif /*__ABR_CTXM_H__*/
