#ifndef __SBR_CSR_MSGTS_H__
#define __SBR_CSR_MSGTS_H__

/** @addtogroup sbrcsr_api_csr_msgts

@{
*/

/**
These indicate the date/time at which the message was created. 
In addition to the date/time value, a timestamp includes an indication of the entity 
generating the timestamp. 
*/
typedef struct _sbr_MsgTimestamp sbr_MsgTimestamp;

#ifdef __cplusplus
extern "C" {
#endif

/**
Point in time at which the timestamp was added to the message.

@param timestamp the timestamp object.

@return datetime.
*/
SBR_CSR_EXPORT const char *sbr_msgts_datetime(sbr_MsgTimestamp *timestamp);

/**
The Entity code for the Entity adding the timestamp.

@param timestamp the timestamp object.

@return Entity code.
*/
SBR_CSR_EXPORT const char *sbr_msgts_source(sbr_MsgTimestamp *timestamp);

#ifdef __cplusplus
}
#endif 

/*! @} */

#endif /*__SBR_CSR_MSGTS_H__*/
