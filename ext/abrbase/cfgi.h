#ifndef __ABR_CFGI_H__
#define __ABR_CFGI_H__

#include <stddef.h>

/** @addtogroup abrbase_api_public_cfgitem

@{
*/

/**
The Configuration Item - represents a given node within an abr_Cfg.
*/
typedef struct _abr_CfgItem abr_CfgItem;

#ifdef __cplusplus
extern "C" {
#endif 

/**
Convenience method to ask if a setting will be written out if saved. If TRUE, the setting value will 
not be written. Equivalent to abr_cfgi_bool(cfgitem, abr_CfgA_readonly, FALSE).
@param cfgitem the configuration item.
@return TRUE or FALSE.
*/
ABR_EXPORT bool abr_cfgi_isreadonly(abr_CfgItem *cfgitem);

/**
Get the name of the configuration item. This is the name after any '$' subsitutions - see abr_ctx_itemid().
@param cfgitem the configuration item.
@return the name of the configuration item.
*/
ABR_EXPORT const char *abr_cfgi_name(abr_CfgItem *cfgitem);

/**
Get the string for the indicated setting attribute. 
@param cfgitem the configuration item.
@param attrname the attribute - NULL defaults to the "value" attribute (abr_CfgA_value).
@param defvalue the default value to use if attrname is not found.
@return the attrname contents.
*/
ABR_EXPORT const char *abr_cfgi_str(abr_CfgItem *cfgitem, const char *attrname, const char *defvalue);

/**
Get the int for the indicated setting attribute. 
@param cfgitem the configuration item.
@param attrname the attribute - NULL defaults to the "value" attribute (abr_CfgA_value).
@param defvalue the default value to use if attrname is not found.
@return the attrname contents as an int.
*/
ABR_EXPORT int abr_cfgi_int(abr_CfgItem *cfgitem, const char *attrname, int defvalue);

/**
Get the boolean for the indicated setting attribute. 
@param cfgitem the configuration item.
@param attrname the attribute - NULL defaults to the "value" attribute (abr_CfgA_value).
@param defvalue the default value to use if attrname is not found.
@return the attrname contents as an boolean.
*/
ABR_EXPORT bool abr_cfgi_bool(abr_CfgItem *cfgitem, const char *attrname, bool defvalue);

/**
For the indicated setting, read the "value" attribute as a size_t and interpret according to the "type" attribute. 

The type can be seconds, minutes, days. 
If the value is not found, defvalue is used and interpreted as seconds. 
If value is found and type is not found, the found value is interpreted as seconds.

@param cfgitem the configuration item.
@param defvalue the default value to use if attrname is not found.

@return the attr value contents or defvalue as seconds.
*/
ABR_EXPORT size_t abr_cfgi_timeout(abr_CfgItem *cfgitem, size_t defvalue);

/**
Set the string for the indicated setting attribute. If the setting/attribute does not
currently exist it will be created (and saved if not abr_cfg_isreadonly()). 
This call is not thread-safe.
@param cfgitem the configuration item.
@param attrname the attribute - NULL defaults to the "value" attribute (abr_CfgA_value).
@param value the value to use.
@return TRUE if successfully set.
*/
ABR_EXPORT bool abr_cfgi_setstr(abr_CfgItem *cfgitem, const char *attrname, const char *value);

#ifdef __cplusplus
}
#endif 

/*! @} */

#endif /*__ABR_CFGI_H__*/
