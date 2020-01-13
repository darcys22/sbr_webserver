#ifndef __SBR_CSR_MSGREC_H__
#define __SBR_CSR_MSGREC_H__

/** @addtogroup sbrcsr_api_csr_msgrec

@{
*/

/**
The optional LodgementReceipt of the @ref sbr_Response @ref sbr_Sbdm.
*/
typedef struct _sbr_MsgReceipt sbr_MsgReceipt;

#ifdef __cplusplus
extern "C" {
#endif

/**
The receipt id, if any.
A unique agency identifier for the lodgement.

@param receipt the receipt

@return the receipt id.
*/
SBR_CSR_EXPORT const char *sbr_msgrec_id(sbr_MsgReceipt *receipt);

/**
The receipt timestamp, if any.
The date and time at which the agency recorded the lodgement as having occurred.

@param receipt the receipt

@return the receipt timestamp.
*/
SBR_CSR_EXPORT const char *sbr_msgrec_datetime(sbr_MsgReceipt *receipt);

#ifdef __cplusplus
}
#endif 

/*! @} */

#endif /*__SBR_CSR_MSGREC_H__*/
