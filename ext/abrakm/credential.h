#ifndef __ABR_AKM_CR_H__
#define __ABR_AKM_CR_H__

/** @addtogroup abrakm_api_cr

@{
*/

/**
The credential object. 

An AUSkey credential has a limited lifetime defined by abr_cr_notbefore() and abr_cr_notafter().
*/
typedef struct _abr_Credential abr_Credential;

/**
Defines the type of credential.
*/
typedef enum {
    ABR_NONE, /**< Credential type is undefined */
    ABR_CREDUSER, /**< User Credential */
    ABR_CREDDEVICE /**< Device Credential */
} abr_eCredtype; 

/**
Used to filter lists of abr_Credential in a keystore - see abr_ks_credentials().
*/
typedef enum {
    ABR_FILTER_ALL, /**< Include all credential records */
    ABR_FILTER_VALID, /**< Include credentials which are currently valid. See abr_cr_isvalid() */
    ABR_FILTER_USER, /**< Include user credentials only */
    ABR_FILTER_VALIDUSER, /**< Include user credentials which are valid */
    ABR_FILTER_DEVICE, /**< Include device credentials only */
    ABR_FILTER_VALIDDEVICE /**< Include device credentials which are valid */
} abr_eCredfilter; 

#ifdef __cplusplus
extern "C" {
#endif 

//ABR_AKM_EXPORT abr_Crypto *abr_cr_crypto(abr_Credential *cr);

/**
Return the credential id. This corresponds to the credential "id" attributed in the store.
@param cr the credential object.
@return id.
*/
ABR_AKM_EXPORT const char *abr_cr_id(abr_Credential *cr);

/**
Same as abr_cr_id().
@param cr the credential object.
@return id.
*/
ABR_AKM_EXPORT const char *abr_cr_alias(abr_Credential *cr);

/**
Return the credential type.
@param cr the credential object.
@return credential type.
*/
ABR_AKM_EXPORT abr_eCredtype abr_cr_type(abr_Credential *cr);

/**
Return the credential ABN.
@param cr the credential object.
@return credential ABN.
*/
ABR_AKM_EXPORT const char *abr_cr_abn(abr_Credential *cr);

/**
Return the credential legal name.
@param cr the credential object.
@return credential legal name.
*/
ABR_AKM_EXPORT const char *abr_cr_legalname(abr_Credential *cr);

/**
Return the credential serial number.
@param cr the credential object.
@return credential serial number.
*/
ABR_AKM_EXPORT const char *abr_cr_serialnr(abr_Credential *cr);

/**
Return the credential creation time.
@param cr the credential object.
@return credential creation timestamp.
*/
ABR_AKM_EXPORT const char *abr_cr_creationdate(abr_Credential *cr);

/**
Returns the start of the credential validity period.
@param cr the credential object.
@return timestamp when credential is first valid.
*/
ABR_AKM_EXPORT const char *abr_cr_notbefore(abr_Credential *cr);

/**
Returns the end of the credential validity period.
@param cr the credential object.
@return timestamp when credential is last valid.
*/
ABR_AKM_EXPORT const char *abr_cr_notafter(abr_Credential *cr);

/**
Return the credential SHA1 fingerprint.
@param cr the credential object.
@return SHA1 fingerprint.
*/
ABR_AKM_EXPORT const char *abr_cr_sha1fingerprint(abr_Credential *cr);

/**
Return the credential person id or NULL if not a USER credential.
@param cr the credential object.
@return Family name.
*/
ABR_AKM_EXPORT const char *abr_cr_personid(abr_Credential *cr);

/**
Return the credential device name or NULL if not a DEVICE credential.
@param cr the credential object.
@return Family name.
*/
ABR_AKM_EXPORT const char *abr_cr_devicename(abr_Credential *cr);

/**
Return the credential given name(s) or NULL if not a USER credential.
@param cr the credential object.
@return Family name.
*/
ABR_AKM_EXPORT const char *abr_cr_givenames(abr_Credential *cr);

/**
Return the credential family name or NULL if not a USER credential.
@param cr the credential object.
@return Family name.
*/
ABR_AKM_EXPORT const char *abr_cr_familyname(abr_Credential *cr);

/**
Determines if the credential matches the given filter criteria.
@param cr the credential object.
@param filter the filter to check.
@return TRUE or FALSE.
*/
ABR_AKM_EXPORT bool abr_cr_matchesfilter(abr_Credential *cr, abr_eCredfilter filter);

/**
Determines if the credential is current (between NotBefore and NotAfter dates).

@param cr the credential object.
@return TRUE or FALSE.
*/
ABR_AKM_EXPORT bool abr_cr_iscurrent(abr_Credential *cr);

/*
@deprecated 
Use abr_cr_iscurrent().

@param cr the credential object.
@return TRUE or FALSE.
*/
ABR_AKM_EXPORT bool abr_cr_isvalid(abr_Credential *cr);

/**
Check if the credential has been changed since the last load.
@param cr the credential object.
@return TRUE or FALSE.
*/
ABR_AKM_EXPORT bool abr_cr_ismodified(abr_Credential *cr);

/**
Determines if the credential is renewed, this relates only to the current session.

@param cr the credential object.
@return TRUE or FALSE.
*/
ABR_AKM_EXPORT bool abr_cr_isrenewed(abr_Credential *cr);

/**
Determines if the credential is ready to be renewed - see abr_cr_renew().

Prior to using a method that access a credential private key, abr_cr_renew() or abr_cr_isrenewable() MUST be called
at least once per session, for the given credential, otherwise the method in questions will return the error ABR_AKM_ERR_RENEWNOTCALLED.

To effectively disable renewal, simply call this method and not abr_cr_renew().

If the credential is due to expire within 14 months it is within the expiry period.
This expiry period can be set in the config file, although the minimum is 14 months.
A 25 month period for a 2 year credential will result in a new credential always being 
renewed - useful for testing.

@param ctx the current thread local Context
@param cr the credential object.
@return TRUE if it is not currently renewed, is valid, and is within the expiry period.
*/
ABR_AKM_EXPORT bool abr_cr_isrenewable(abr_Ctx *ctx, abr_Credential *cr);

/**
Determines if the credential matches its expected integrity value.

This will always be true, unless the credential has changed or, possibly if the keystore was 
loaded without integrity validation and there is a mismatch. Used for testing scenarious.

@param ctx the current thread local Context
@param cr the credential object.
@return TRUE if valid; FALSE otherwise or if an internal exception has occurred.
*/
ABR_AKM_EXPORT bool abr_is_integrity_valid(abr_Ctx *ctx, abr_Credential *cr);

/**
Determines if the credential password is valid. 

Given that all credentials in a keystore must have the same password, this is really just
a convenience method on the credential.

@param ctx the current thread local Context
@param cr the credential object.
@param correct address of the bool/int to set as TRUE or FALSE
@param pwd the password to test
@return ABR_ERR_OK, else an error code if an internal exception has occured
*/
ABR_AKM_EXPORT int abr_cr_iscorrectpwd(abr_Ctx *ctx, abr_Credential *cr, bool *correct, const char *pwd);

/**
Determines if the credential P8 uses PBES1 or PBES2 scheme. 

@param ctx the current thread local Context
@param cr the credential object.
@return TRUE if PBES2
*/
ABR_AKM_EXPORT bool abr_cr_ispbe2(abr_Ctx *ctx, abr_Credential *cr);

/**
Construct a X509 certificate object from the credential and return as a DER encoded array. 
This includes the principle as well as the issuer certificates.

@param ctx the current thread local Context
@param cr the credential object.
@param certificate the address of an abr_String object to allocate. The caller must free this using abr_str_free().

@return ABR_ERR_OK(0) if successful, otherwise 
- ?
*/
ABR_AKM_EXPORT int abr_cr_certificate(abr_Ctx *ctx, abr_Credential *cr, abr_String **certificate);

/**
Construct a P7 certificate chain object from the credential and return as a DER encoded array. 
This includes the principle as well as the issuer certificates.

@param ctx the current thread local Context.
@param cr the credential object.
@param certificates the address of an abr_String object to allocate. The caller must free this using abr_str_free().

@return ABR_ERR_OK(0) if successful, otherwise 
- ?
*/
ABR_AKM_EXPORT int abr_cr_chain(abr_Ctx *ctx, abr_Credential *cr, abr_String **certificates);

/**
Construct a decrypted private key object from the credential and return as a DER encoded array 
- see also abr_cr_isrenewable() and abr_cr_renew().

@param ctx the current thread local Context.
@param cr the credential object.
@param privatekey the address of an abr_String object to allocate. The caller must free this using abr_str_free().
@param pwd the password used to access the private key.

@return ABR_ERR_OK(0) if successful, otherwise 
- ABR_AKM_ERR_BADPWD if the  password is wrong
- ABR_AKM_ERR_RENEWNOTCALLED if abr_cr_renew() or abr_cr_isrenewable() has not been called 
*/
ABR_AKM_EXPORT int abr_cr_privatekey(abr_Ctx *ctx, abr_Credential *cr, abr_String **privatekey, const char *pwd);

/**
Construct a P12 object from the credential and return as a DER encoded array
- see also abr_cr_isrenewable() and abr_cr_renew().

@param ctx the current thread local Context.
@param cr the credential object.
@param p12 the address of an abr_String object to allocate. The caller must free this using abr_str_free().
@param pwd the password used to access the private key.

@return ABR_ERR_OK(0) if successful, otherwise 
- ABR_AKM_ERR_BADPWD if the  password is wrong
- ABR_AKM_ERR_RENEWNOTCALLED if abr_cr_renew() or abr_cr_isrenewable() has not been called 
*/
ABR_AKM_EXPORT int abr_cr_p12(abr_Ctx *ctx, abr_Credential *cr, abr_String **p12, const char *pwd);

/**
Renew the credential - see abr_cr_isrenewable().

The renewal service url is defined in the configuration file.

Checks if the credential is renewable and if it is attempts renewal. 
This is done synchronously - no separate thread is created. 
This can be done on a seperate thread if desired.
The renewed credential is made available after a keystore save() operation. 

@param ctx the current thread local Context.
@param cr the credential object.
@param pwd the password used to access the private key.

@return ABR_ERR_OK(0) if successful, otherwise 
- ABR_AKM_ERR_BADPWD if the  password is wrong
*/
ABR_AKM_EXPORT int abr_cr_renew(abr_Ctx *ctx, abr_Credential *cr, const char *pwd);

/**
Return the integrityvalue stored in the keystore for the credential.
	
@param cr the credential object.

@return An abr_String object containing the data, which is null terminated. 
*/
ABR_AKM_EXPORT abr_String *abr_cr_integrityvalue(abr_Credential *cr);

/**
Return the salt stored in the keystore for the credential.
	
@param cr the credential object.

@return An abr_String object containing the data, which is null terminated. 
*/
ABR_AKM_EXPORT abr_String *abr_cr_b64salt(abr_Credential *cr);

/**
Return the base64 encoded P7c stored in the keystore for the credential.
	
@param cr the credential object.

@return An abr_String object containing the data, which is null terminated. 
*/
ABR_AKM_EXPORT abr_String *abr_cr_b64p7(abr_Credential *cr);

/**
Return the base64 encoded P8 stored in the keystore for the credential.
	
@param cr the credential object.

@return An abr_String object containing the data, which is null terminated. 
*/
ABR_AKM_EXPORT abr_String *abr_cr_b64p8(abr_Credential *cr);

#ifdef __cplusplus
}
#endif 

/*! @} */

#endif /*__ABR_AKM_CR_H__*/
