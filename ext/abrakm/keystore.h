#ifndef __ABR_AKM_KS_H__
#define __ABR_AKM_KS_H__

#include <stddef.h>

/** @addtogroup abrakm_api_ks

@{
*/

/**
The keystore object. 
*/
typedef struct _abr_Keystore abr_Keystore;

#ifdef __cplusplus
extern "C" {
#endif 

/**
Create a keystore object from the XML stored in buffer. 

@param ctx the current thread local Context.
@param ks the address of the object to create. *obj must be initialised to NULL.
@param buffer the XML content. If null, an empty keystore is created.
@param properties optional properties to use for the keystore. 
An internal copy of this is created, which means that abr_ks_properties() will return the internal copy.

@return ABR_ERR_OK
*/
ABR_AKM_EXPORT int abr_ks_create(abr_Ctx *ctx, abr_Keystore **ks, const char *buffer, const abr_ksProperties *properties);

/**
Free the keystore object if not NULL.

@param ks the keystore object. If NULL do nothing.
*/
ABR_AKM_EXPORT void abr_ks_free(abr_Keystore *ks);

/**
get the properties object associated with the keystore.

@param ks the keystore object. 
@return the properties object associated with the keystore.
*/
ABR_AKM_EXPORT abr_ksProperties *abr_ks_properties(abr_Keystore *ks);

/*
@deprecated
Use abr_ksprop_ver().

The version of the keystore. 
You can only copy (add) credentials between keystores with the same schema version.

@param ks the keystore object.
@return version in the form 00.00.00.00 with at least 2 levels
*/
ABR_AKM_EXPORT const char *abr_ks_schemaversion(abr_Keystore *ks);

/**
Returns TRUE if the keystore or any of its credentials has been modified since the last created or loaded.

@param ks the keystore object.
@return TRUE or FALSE
*/
ABR_AKM_EXPORT bool abr_ks_ismodified(abr_Keystore *ks);

/**
Returns FALSE if the keystore is in invalid state due to a failed update operation.
This may occur if a change password works for some credentials but not others.
If this occurs, the in-memory keystore should be discarded and reloaded.

@param ks the keystore object.
@return TRUE or FALSE
*/
ABR_AKM_EXPORT bool abr_ks_isvalid(abr_Keystore *ks);

/*
@deprecated
Use abr_ks_ismodified().

@param ks the keystore object.
@return TRUE or FALSE
*/
ABR_AKM_EXPORT bool abr_ks_isdirty(abr_Keystore *ks);

/**
Save the keystore to a buffer. 
This does not change the internal state meaning that ismodified() will still be true.

@param ctx the current thread local Context.
@param ks the keystore object.
@param buffer the buffer to allocate. This caller must free this using abr_str_free().

@return ABR_ERR_OK if successful, otherwise 
- ABR_AKM_ERR_KEYSTORE_CORRUPTED where the keystore should be discarded and reloaded.
*/
ABR_AKM_EXPORT int abr_ks_save(abr_Ctx *ctx, abr_Keystore *ks, char **buffer);

/**
Return the number of credentials in the keystore matching the filter abr_eCredfilter.

@param ks the keystore object.
@param filter the filter to use - ABR_FILTER_ALL counts all records.

@return number of credentials.
*/
ABR_AKM_EXPORT size_t abr_ks_count(abr_Keystore *ks, abr_eCredfilter filter);

/**
Return the credential corresponding to alias or NULL if not found.

@param ks the keystore object.
@param alias the alias (i.e. xml id) for the credential.

@return the credential or NULL if the alias is not found.
*/
ABR_AKM_EXPORT abr_Credential *abr_ks_credential(abr_Keystore *ks, const char *alias);

/**
Return an allocated array of credentials according to the filter provided. 

This is in the original order.

@param ks the keystore object.
@param creds the variable to allocate an array of credentials to. This must be freed by the caller.
Do not, however, free the credentials themselves, as they will be freed when the abr_ks_free() is called.
@param filter the type of credential to include.

@return the size of the array.
*/
ABR_AKM_EXPORT size_t abr_ks_credentials(abr_Keystore *ks, abr_Credential ***creds, abr_eCredfilter filter);

/**
Delete the credential corresponding to the alias or all credentials if alias is NULL.

@param ks the keystore object.
@param alias the alias (i.e. xml id) for the credential. If NULL, delete all credentials.

@return ABR_ERR_OK if successful
*/
ABR_AKM_EXPORT size_t abr_ks_delete(abr_Keystore *ks, const char *alias);

/**
Test if the password is correct without accessing any particular credential. 

If the keystore is empty this will always be true.

@param ctx the current thread local Context.
@param ks the keystore object.
@param correct the address of the boolean to set to TRUE or FALSE
@param pwd the password

@return ABR_ERR_OK or an errcode.
*/
ABR_AKM_EXPORT int abr_ks_iscorrectpwd(abr_Ctx *ctx, abr_Keystore *ks, bool *correct, const char *pwd);

/**
Change the password for all credentials in the keystore - see abr_ks_pwdpolicy_desc() for password rules. 

If multi-threading, ensure that the keystore is not involved in any current abr_ks_copycredential operation.

@param ctx the current thread local Context.
@param ks the keystore 
@param pwd the password
@param newpwd the new password

@return ABR_ERR_OK(0) if successful, otherwise 
- ABR_AKM_ERR_PWD if the password is wrong
- ABR_AKM_ERR_PWDPOLICY if the new password doesn't meet strength requirements
- ABR_AKM_ERR_GENERAL for any other error.
For any error, a nested inner error, if any, will contain more details.
*/
ABR_AKM_EXPORT int abr_ks_changepwd(abr_Ctx *ctx, abr_Keystore *ks, const char *pwd, const char *newpwd);

/**
Check if the password matches the password policy - see abr_ks_pwdpolicy_desc().

It is possible this may vary in future versions of the keystore.

@param ks the keystore. If NULL, the latest policy is used.
@param pwd the password

@return TRUE or FALSE.
*/
ABR_AKM_EXPORT bool abr_ks_pwdpolicy_isvalid(abr_Keystore *ks, const char *pwd);

/**
Return the password policy as a string.

Currently a password must contain:
- no whitespace
- at least 1 uppercase character
- at least 1 lowercase character
- at least 1 digit OR 1 punctuation character
- at least 10 printable characters

@param ks the keystore. If NULL, the latest policy description (above) is returned.

@return The above content as a string - including embedded newlines.
*/
ABR_AKM_EXPORT const char *abr_ks_pwdpolicy_desc(abr_Keystore *ks);

/**
Add a credential from another keystore to a destination keystore - replaces abr_ks_copycredential.

If multi-threading, ensure that either keystores are not involved in any abr_ks_changepwd operation.

@param ctx the current thread local Context.
@param ks the keystore.
@param pwd the password of the keystore.
@param cr the credential to add to the keystore.
@param crpwd the password of the credential (source keystore); can be NULL if same as destination keystore.
@param isreplacable used if the alias already exists in the dstks. If TRUE then replace it, 

@return ABR_ERR_OK(0) if successful, otherwise 
- ABR_AKM_ERR_CREDNOTFOUND if the credential does not exist in the source store
- ABR_AKM_ERR_ALIASEXISTS if isreplacable is FALSE and credential alias already exists in the destination store
- ABR_AKM_ERR_BADPWD if the source credential password is wrong
- ABR_AKM_ERR_PWDDEST if the destination store password is wrong
- ABR_AKM_ERR_PWDPOLICY if this is a new password that doesn't meet strength requirements
- ABR_AKM_ERR_COPYCREDENTIAL if a general error occured - see message text for details
*/
ABR_AKM_EXPORT int abr_ks_addcredential(abr_Ctx *ctx, abr_Keystore *ks, const char *pwd, abr_Credential *cr, const char *crpwd, bool isreplacable);

#ifdef __cplusplus
}
#endif 

/*! @} */

#endif /*__ABR_AKM_KS_H__*/
