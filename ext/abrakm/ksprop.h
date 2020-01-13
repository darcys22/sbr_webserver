#ifndef __ABR_AKM_KSPROP_H__
#define __ABR_AKM_KSPROP_H__

#include <stddef.h>

/** @addtogroup abrakm_api_ksprop

@{
*/

/**
The keystore properties object retrieved using abr_ks_properties().
*/
typedef struct _abr_ksProperties abr_ksProperties;

#ifdef __cplusplus
extern "C" {
#endif 

/**
Create a properties object.

@return the newly created object or NULL if memory failure
*/
ABR_AKM_EXPORT abr_ksProperties *abr_ksprop_create(void);

/**
Free a properties object.

@param ksprop the properties object.
@return NULL.
*/
ABR_AKM_EXPORT void *abr_ksprop_free(abr_ksProperties *ksprop);

/**
Get the keystore version

@param ksprop the properties object associated with a keystore.
@return the version of the keystore or NULL if not associated with a keystore.
*/
ABR_AKM_EXPORT const char *abr_ksprop_ver(const abr_ksProperties *ksprop);

/**
Get the keystore salt

@param ksprop the properties object.
@return the salt of the keystore or NULL if not associated with a keystore.
*/
ABR_AKM_EXPORT const char *abr_ksprop_salt(const abr_ksProperties *ksprop);

/**
Get the minimum expiry time allowed (in months).

@return minimum expiry time in months.
*/
ABR_AKM_EXPORT int abr_ksprop_RenewalExpiryTimeMonths_Min(void);

/**
Get the expiry time. 
If non-0, it will never be less than abr_ksprop_RenewalExpiryTimeMonthsMin().
If 0, then the value from the configuration file is used instead.

@param ksprop the properties object.
@return expiry time in months.
*/
ABR_AKM_EXPORT int abr_ksprop_RenewalExpiryTimeMonths(const abr_ksProperties *ksprop);

/**
Set the expiry time. Can be set to 0. 
If != 0 and less than abr_ksprop_RenewalExpiryTimeMonthsMin() then value is forced to abr_ksprop_RenewalExpiryTimeMonthsMin().

@param ksprop the properties object.
@param months expiry time in months (before enddate).
*/
ABR_AKM_EXPORT void abr_ksprop_RenewalExpiryTimeMonths_Set(abr_ksProperties *ksprop, int months);

/**
Get the pbe mode. 

@param ksprop the properties object.
@return pbemode
*/
ABR_AKM_EXPORT const char *abr_ksprop_PbeMode(const abr_ksProperties *ksprop);

/**
Set the pbe mode. Do not use unless advised as this can cause compatibility issues with the AUSkey website.
If pbemode is NULL then the call is ignored.

@param ctx the current thread local Context.
@param ksprop the properties object.
@param pbemode the pbe mode as a string.
*/
ABR_AKM_EXPORT void abr_ksprop_PbeMode_Set(abr_Ctx *ctx, abr_ksProperties *ksprop, const char *pbemode);

/**
Get the URI to use for renewal based on an id. 
Values are hardcoded. 
If abr_ksprop_RenewalOverrideUri() is set then this value is used instead.

@param ksprop the properties object.
@param id the identifier for the renewal URI to use.
@return NULL or the URI
*/
ABR_AKM_EXPORT const char *abr_ksprop_RenewalUri(const abr_ksProperties *ksprop, const char *id);

/**
Get the URI to use for renewal based on an id. 
If abr_ksprop_RenewalOverrideUri() is set then this value is used instead.
If values are set in the config, then they override the hardcoded values.

@param ctx the current thread local Context.
@param ksprop the properties object.
@param id the identifier for the renewal URI to use.
@return NULL or the URI
*/
ABR_AKM_EXPORT const char *abr_ksprop_RenewalUriCfg(abr_Ctx *ctx, const abr_ksProperties *ksprop, const char *id);

/**
Get the override URI to use for renewals, if any. 

@param ksprop the properties object.
@return NULL or the URI
*/
ABR_AKM_EXPORT const char *abr_ksprop_RenewalOverrideUri(const abr_ksProperties *ksprop);

/**
Set the override URI. For testing only.

@param ksprop the properties object.
@param uri the uri .
*/
ABR_AKM_EXPORT void abr_ksprop_RenewalOverrideUri_Set(abr_ksProperties *ksprop, const char *uri);

/**
The test renewal service name used for unit-testing or diagnostics.

@return service name
*/
ABR_AKM_EXPORT const char *abr_ksprop_RenewalTestUriPostfix(void);

/**
get RenewalIncludeSoftwareInfo.
If true then a SoftwareInfo element is included in renewal requests.
This currently defaults to false, in order to be compatible with the legacy renewal service.

@param ksprop the properties object.
@return RenewalIncludeSoftwareInfo
*/
ABR_AKM_EXPORT bool abr_ksprop_RenewalIncludeSoftwareInfo(const abr_ksProperties *ksprop);

/**
Set RenewalIncludeSoftwareInfo.
If true then a SoftwareInfo element is included in renewal requests.
This currently defaults to false, in order to be compatible with the legacy renewal service.
Do not change unless advised.

@param ksprop the properties object.
@param RenewalIncludeSoftwareInfo TRUE or FALSE.
*/
ABR_AKM_EXPORT void abr_ksprop_RenewalIncludeSoftwareInfo_Set(abr_ksProperties *ksprop, bool RenewalIncludeSoftwareInfo);

#ifdef __cplusplus
}
#endif 

/*! @} */

#endif /*__ABR_AKM_KSPROP_H__*/
