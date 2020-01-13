#ifndef __ABR_STM_TKN_H__
#define __ABR_STM_TKN_H__

/** @addtogroup abrstm_api_stmtkn

@{
*/

/**
The Security Token object. 
*/
typedef struct _abr_StmTkn abr_StmTkn;

#ifdef __cplusplus
extern "C" {
#endif 

/**
Given a SecurityToken object, serialise the data - see also abr_stm_loadst().

@param st the SecurityToken.
@return The ABR RSTR serialised SecurityToken.
*/
ABR_STM_EXPORT abr_String *abr_stmtkn_xml(abr_StmTkn *st);

/**
Given a SecurityToken object, retrieve the key used in an ST cache.

@param st the SecurityToken.

@return ST key.
*/
ABR_STM_EXPORT const char *abr_stmtkn_key(abr_StmTkn *st);

/**
Given a SecurityToken object, retrieve the embedded proof token.

@param st the SecurityToken.

@return Proof Token.
*/
ABR_STM_EXPORT abr_String *abr_stmtkn_prooftoken(abr_StmTkn *st);

/**
Given a SecurityToken object, retrieve the encrypted assertion.

@param st the SecurityToken.

@return Assertion.
*/
ABR_STM_EXPORT abr_String *abr_stmtkn_assertion(abr_StmTkn *st);

/**
Given a SecurityToken object, retrieve the Assertion (SAML) ID.

This is stored in the KeyIdentifier Element of the RSTR.

@param st the SecurityToken.

@return Assertion (SAML) ID.
*/
ABR_STM_EXPORT const char *abr_stmtkn_samlid(abr_StmTkn *st);

/**
Check if the SecurityToken has expired - see also abr_stm_setexpirytime() and abr_stmtkn_expirytime().

@param st the SecurityToken. 

@return TRUE or FALSE.
*/
ABR_STM_EXPORT bool abr_stmtkn_isexpired(abr_StmTkn *st);

/**
Get the local time the SecurityToken is to expire - see also abr_stmtkn_isexpired() and abr_stm_setexpirytime().

@param st the SecurityToken. 

@return the expiry time (granularity is seconds).
*/
ABR_STM_EXPORT time_t abr_stmtkn_expirytime(abr_StmTkn *st);

#ifdef __cplusplus
}
#endif 

/*! @} */

#endif /*__ABR_STM_TKN_H__*/
