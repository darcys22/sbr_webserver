#ifndef __SBR_CSR_MSGPARTY_H__
#define __SBR_CSR_MSGPARTY_H__

/** @addtogroup sbrcsr_api_csr_msgparty

@{
*/

/**
Indicates whether the details belong to the sender or receiver.
*/
typedef enum {
    SBR_MSG_SENDER = 1, /**< Party type is Sender */
    SBR_MSG_RECEIVER /**< Party type is Receiver */
} sbr_eMsgPartyType; 

#define SBR_PARTYIDNAME_AGENCY "AgencyInternetDomainName"

/**
Holds the message details for a party involved in a transaction.

This can be used to hold details of the "other" party. 
That is, the request message holds the details of the sender and vica-versa.
*/
typedef struct _sbr_MsgParty sbr_MsgParty; 

#ifdef __cplusplus
extern "C" {
#endif

/**
Get the designation value for the party.

@param party the party object.
@return designation value.
*/
SBR_CSR_EXPORT const char *sbr_msgp_iddesignation(sbr_MsgParty *party);

/**
Get the scheme of the party.

@param party the party object.
@return party scheme.
*/
SBR_CSR_EXPORT const char *sbr_msgp_idname(sbr_MsgParty *party);

/**
Get the type for the party (whether a sender or receiver).

@param party the party object.
@return party type.
*/
SBR_CSR_EXPORT sbr_eMsgPartyType sbr_msgp_type(sbr_MsgParty *party);

/**
Utility method to get the partytype as a string. 

Useful for logging.

@param msgpartytype the partytype.

@return party type as a string.
*/
SBR_CSR_EXPORT const char *sbr_msgp_typestr(sbr_eMsgPartyType msgpartytype);

#ifdef __cplusplus
}
#endif 

/*! @} */

#endif /*__SBR_CSR_MSGPARTY_H__*/
