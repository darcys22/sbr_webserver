#ifndef __ABR_AKM_TYPES_H__
#define __ABR_AKM_TYPES_H__

#include "abrakm/export.h"

/** @addtogroup abrakm_api_types

*/

/** @defgroup abrakm_api_types_modules Module defines
@ingroup abrakm_api_types
Each module within the library is individually defined by a name and id.
These can be used to target logging for particular modules and to identify the source of errors.
When setting logging, the MODULEID values can be bitwised or-ed.

Note that not all modules are necessarily exposed via a public API, even though they appear here.

@{
*/
#define ABR_AKM_LIBRARY "abrakm" /**< Short text Name of the library */
#define ABR_AKM_MODULE_LIB "lib" /**< Short text Name of the primary lib module */
#define ABR_AKM_MODULE_KS "ks" /**< Short text Name of the keystore module */
#define ABR_AKM_MODULE_CR "cr" /**< Short text Name of the credential module */
#define ABR_AKM_MODULE_CRR "crr" /**< Short text Name of the renewal module */
#define ABR_AKM_MODULE_ERRFN "errfn" /**< Short text Name of the error callback module */
#define ABR_AKM_MODULE_KSPROP "ksprop" /**< Short text Name of the keystore properties module */

#define ABR_AKM_MODULEID_LIB    0x00000001UL /**< The lib module id. */
#define ABR_AKM_MODULEID_KS     0x00000002UL /**< The keystore module id. */
#define ABR_AKM_MODULEID_CR     0x00000004UL /**< The credential module id. */
#define ABR_AKM_MODULEID_CRR    0x00000008UL /**< The renewal module id. */
#define ABR_AKM_MODULEID_ERRFN  0x00000010UL /**< The error callback module id. */
#define ABR_AKM_MODULEID_KSPROP 0x00000020UL /**< The keystore properties module id. */

/**
The ABR_AKM_INIT_... defines are used to control the initialisation that takes place. Currently
only ABR_AKM_INIT_ALL is defined. 
*/
#define ABR_AKM_INIT_ALL 0xffff

/** @} */

#ifdef __cplusplus
extern "C" {
#endif 

/** @defgroup abrakm_api_types_config Configuration Values
@ingroup abrakm_api_typess
These values can optionally be used to access variables in the configuration file.

@{
*/
/**
 Config Keystore Dir setting - see configuration file (abrdefcontexts.xml) for details.
 */
ABR_AKM_EXPORT_VAR const char abr_CfgN_Akm_Keystore_Dir[];
/**
 Config Keystore File setting - see configuration file (abrdefcontexts.xml) for details.
 */
ABR_AKM_EXPORT_VAR const char abr_CfgN_Akm_Keystore_File[];
/**
 Config Credential Renewal Expiry setting - see configuration file (abrdefcontexts.xml) for details.
 */
ABR_AKM_EXPORT_VAR const char abr_CfgN_Akm_Credential_Renew_ExpireTime[];
/**
@deprecated
URL is now determined by the credential Root CA and is hardcoded. See abr_ksprop_RenewalUri().

Config Credential Renewal Url setting - see configuration file (abrdefcontexts.xml) for details.
 */
ABR_AKM_EXPORT_VAR const char abr_CfgN_Akm_Credential_Renew_Url[];

ABR_AKM_EXPORT_VAR const char abr_CfgN_Akm_Credential_Renew_Urls_Australian_Business_Register_Root_CA[];
ABR_AKM_EXPORT_VAR const char abr_CfgN_Akm_Credential_Renew_Urls_Test_Australian_Business_Register_Root_CA[];

/** @} */

#ifdef __cplusplus
}
#endif 

/** @defgroup abrakm_api_types_errcodes AKM Error codes
@ingroup abrakm_api_typess
All errors are encapsulated in AKM specific errors.
For the underlying error, use abr_err_inner() to retrieve nested errors and their details.

@{
*/

#define ABR_AKM_ERR_MIN 12000 /**< The mimimum error number. */
#define ABR_AKM_ERR_GENERAL (ABR_AKM_ERR_MIN+1)  /**< For errors not otherwise specified. */

#define ABR_AKM_ERR_NETSENDER (ABR_AKM_ERR_MIN+2) /**< A SOAP fault generated by the sender, not including service unavailable. */
#define ABR_AKM_ERR_NETRECEIVER (ABR_AKM_ERR_MIN+3) /**< A SOAP fault generated by the receiver, not including service unavailable. */
#define ABR_AKM_ERR_NETUNAVAILABLE (ABR_AKM_ERR_MIN+4) /**< A SOAP fault where the remote service is unavailable. */
#define ABR_AKM_ERR_NETCOMMS (ABR_AKM_ERR_MIN+5) /**< A general network error has occurred, not including timeouts. */
#define ABR_AKM_ERR_NETTIMEOUT (ABR_AKM_ERR_MIN+6)  /**< A network time has occured trying to connect to a remote service. */

#define ABR_AKM_ERR_CRYPTO (ABR_AKM_ERR_MIN+7) /**< General cryptographic error. */
#define ABR_AKM_ERR_NOTRENEWABLE (ABR_AKM_ERR_MIN+8) /**< Credential is not renewable due to being created too recently. */
#define ABR_AKM_ERR_RENEW (ABR_AKM_ERR_MIN+9)  /**< Error renewing credential. */
#define ABR_AKM_ERR_CREDNOTFOUND (ABR_AKM_ERR_MIN+10) /**< Credential not found in keystore. */

#define ABR_AKM_ERR_ALIASEXISTS (ABR_AKM_ERR_MIN+11) /**< A credential with the given alias exists and is not replaceable. */
#define ABR_AKM_ERR_KEYSTORE_CORRUPTED (ABR_AKM_ERR_MIN+12) /**< Keystore is corrupted. */
#define ABR_AKM_ERR_BADPWD (ABR_AKM_ERR_MIN+13) /**< Bad password. */
#define ABR_AKM_ERR_PWDDEST (ABR_AKM_ERR_MIN+14) /**< The password for the target keystore is wrong. */

#define ABR_AKM_ERR_SAVE (ABR_AKM_ERR_MIN+15) /**< Error saving keystore. */
#define ABR_AKM_ERR_INTEGRITYVALUE (ABR_AKM_ERR_MIN+16) /**< Error validating integrity value. */
#define ABR_AKM_ERR_RENEWNOTCALLED (ABR_AKM_ERR_MIN+17) /**< Private key of a credential accessed without first calling renewall method. */
#define ABR_AKM_ERR_PWDPOLICY (ABR_AKM_ERR_MIN+18)  /**< The supplied password does not meet the strength requirements of the password policy. */
#define ABR_AKM_ERR_COPYCREDENTIAL (ABR_AKM_ERR_MIN+19) /**< Error during copycredential operation. */
#define ABR_AKM_ERR_DUPLICATECR (ABR_AKM_ERR_MIN+20) /**< Possible duplicate credential. */
#define ABR_AKM_ERR_LOAD (ABR_AKM_ERR_MIN+21) /**< Error loading keystore. */
#define ABR_AKM_ERR_RENEW_NOTAVAILABLE (ABR_AKM_ERR_MIN+22)  /**< Renewal not available for the given Certficate Authority (e.g. in a test environment). */

#define ABR_AKM_ERR_MAX (ABR_AKM_ERR_MIN+200) /**< The maximum error number. */
/** @} */

#endif /*__ABR_AKM_TYPES_H__*/
