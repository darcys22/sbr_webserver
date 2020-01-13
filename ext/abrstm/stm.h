#ifndef __ABR_STM_H__
#define __ABR_STM_H__

/** @addtogroup abrstm_api_stm

@{
*/

/**
The STM object used to interact with an STS service to retrieve Security Tokens (abr_StmTkn).
*/
typedef struct _abr_Stm abr_Stm;

#ifdef __cplusplus
extern "C" {
#endif 

/**
Create an STM object from the XML stored in stmtemplate. 

@param ctx the current thread local Context.
@param stm the address of the object to create.
@param stsurl the URL of the STS service to use. If NULL, the value is read from the current configuration.
@param stmtemplate the XML content.

@return ABR_ERR_OK or an errcode.
*/
ABR_STM_EXPORT int abr_stm_create(abr_Ctx *ctx, abr_Stm **stm, const char *stsurl, const char *stmtemplate);

/**
Free the STM object.

@param ctx the current thread local Context.
@param stm the STM object. If NULL do nothing.
*/
ABR_STM_EXPORT void abr_stm_free(abr_Ctx *ctx, abr_Stm *stm);

/**
Purge the STM token cache for the current context/thread.

@param ctx the current thread local Context.
@param purgeall if TRUE remove all tokens, otherwise remove only stale (expired) tokens.
*/
ABR_STM_EXPORT void abr_stm_purgecache(abr_Ctx *ctx, bool purgeall);

/**
Set the expiry interval (mins) for requested SecurityTokens at time of request - see also abr_stmtkm_isexpired() and abr_stmtkn_expirytime().

This is applied to all subsequent requests. if not explicitly set, the default is 5 minutes. 
The allowed ranged is 5 to 30 mins. If less than 5 mins is specified, then 5 mins is set; if greater than
30 mins is specified, then 30 mins is set.

@param stm the STM object.
@param expirymins the number of minutes from the request time that the SecurityToken should remain valid.
*/
ABR_STM_EXPORT void abr_stm_setexpiryinterval(abr_Stm *stm, size_t expirymins); 

/**
The current expiry time interval in minutes - see also abr_stm_setexpiryinterval()

This is applied to requests (abr_stm_stsissue()). 
The SecurityToken is set to expired at the time of the request + specified number of minutes.

@param stm the STM object.

@return the number of minutes from the request time that the SecurityToken should remain valid.
*/
ABR_STM_EXPORT size_t abr_stm_expiryinterval(abr_Stm *stm); 

/**
Submit an STS issue request to the STS service and return a SecurityToken response object.

The Security Token expiry time is set to a default value unless set using abr_stm_setexpirytime().
If the SecurityToken already exists int the cache and is not expired, then this is used instead, 
and no call is made to the STS service.

@param ctx the current thread local Context.
@param stm the STM object.
@param st the SecurityToken object address (do not free) or NULL if none or an error occurred. 
@param certificate X509 certificate.
@param privatekey P8 private key.
@param relyingpartyurl the relying party for which the token is issued.

@return ABR_ERR_OK or an errcode.
*/
ABR_STM_EXPORT int abr_stm_stsissue(abr_Ctx *ctx, abr_Stm *stm, abr_StmTkn **st, abr_String *certificate, abr_String *privatekey, const char *relyingpartyurl); 

/**
Deserialise a SecurityToken (ST) based on the contents of a previously serialised ST 
- see abr_stmtkn_xml(). 

This creates a corresponding ST object in the ST cache.
An error results if the ST already exists in the cache. 
However, expired STs are accepted, so check abr_stmtkn_isexpired() before using the ST.

@param ctx the current thread local Context.
@param stm the STM object.
@param st the SecurityToken object address (do not free) or NULL if none or an error occurred. 
@param abrrstr Serialised ST content which includes the RSTR and stkey.

@return ABR_ERR_OK or an errcode.
*/
ABR_STM_EXPORT int abr_stm_loadst(abr_Ctx *ctx, abr_Stm *stm, abr_StmTkn **st, abr_String *abrrstr);

/**
Get the network total timeout value, in seconds, used for requests to Vanguard STS. 

@param ctx the current thread local Context.
@param stm the STM object.

@return the current timeout value.
*/
ABR_STM_EXPORT size_t abr_stm_timeout(abr_Ctx *ctx, abr_Stm *stm);

/**
Set the network total timeout value, in seconds, used for requests to Vanguard STS. 

@param ctx the current thread local Context.
@param stm the STM object.
@param timeout the timeout value to set.
*/
ABR_STM_EXPORT void abr_stm_settimeout(abr_Ctx *ctx, abr_Stm *stm, size_t timeout);

/**
Get the network connect timeout value, in seconds, used for requests to Vanguard STS. 

@param ctx the current thread local Context.
@param stm the STM object.

@return the current timeout value.
*/
ABR_STM_EXPORT size_t abr_stm_timeoutconnect(abr_Ctx *ctx, abr_Stm *stm);

/**
Set the network connect timeout value, in seconds, used for requests to Vanguard STS. 

@param ctx the current thread local Context.
@param stm the STM object.
@param timeout the timeout value to set.
*/
ABR_STM_EXPORT void abr_stm_settimeoutconnect(abr_Ctx *ctx, abr_Stm *stm, size_t timeout);

#ifdef __cplusplus
}
#endif 

/*! @} */

#endif /*__ABR_STM_H__*/
