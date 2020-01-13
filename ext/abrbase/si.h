#ifndef __ABR_SI_H__
#define __ABR_SI_H__

#include <stddef.h>

/** @addtogroup abrbase_api_public_si

Provides global details of the application. 

@{
*/

#ifdef __cplusplus
extern "C" {
#endif 

/**
Set up the application information.

@param organisation Organisation name or individual name.
@param product Name of the application.
@param version Version of the application.
@param timestamp The timestamp of the last build for the application

*/
ABR_EXPORT void abr_si_set(const char *organisation, const char *product, const char *version, const char *timestamp);

/**
Return the organisation name owning the application.
@return organisation name
*/
ABR_EXPORT const char *abr_si_organisation(void);

/**
Return the product name.
@return product name
*/
ABR_EXPORT const char *abr_si_product(void);

/**
Return the version.
@return version
*/
ABR_EXPORT const char *abr_si_version(void);

/**
Return the timestamp of the last build of the application.
@return build timestamp
*/
ABR_EXPORT const char *abr_si_timestamp(void);

#ifdef __cplusplus
}
#endif 

/*! @} */

#endif /*__ABR_SI_H__*/
