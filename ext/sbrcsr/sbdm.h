#ifndef __SBR_CSR_SBDM_H__
#define __SBR_CSR_SBDM_H__


/** @addtogroup sbrcsr_api_csr_sbdm

While similar, the content differs depending on whether the message is a request or response 
(@ref sbr_eMsgSourceType). This is documented in the individual methods.

@{
*/

/**
The CSR SBDM object.
Used when adding business documents to a request for submission to CSR - see @ref sbr_Request.
Used when extracting business documents from a response - see @ref sbr_Response.
*/
typedef struct _sbr_Sbdm sbr_Sbdm;

#ifdef __cplusplus
extern "C" {
#endif

/**
Return the unique id for the SBDM - this is a memory only value.

@param sbdm the StandardBusinessDocumentMessage object

@return unique id.
*/
SBR_CSR_EXPORT const char *sbr_sbdm_iid(sbr_Sbdm *sbdm);

/**
Indicates whether the sbdm is part of a request or response message.

@param sbdm the StandardBusinessDocumentMessage object

@return the sourcetype of the object (request/response).
*/
SBR_CSR_EXPORT sbr_eMsgSourceType sbr_sbdm_msgsourcetype(sbr_Sbdm *sbdm);

/**
Set the message type for this sbdm and request (request only).

This will override the value in the template
(StandardBusinessDocumentHeader:Message.Type.Text).

If this is a response sbdm then this will call will be ignored and will silently fail.

@param ctx the current thread local Context.
@param sbdm the request object. 
@param messagetype the messagetype string (e.g. "message.ping").

@return ABR_ERR_OK if successful or an errorcode OR -1 if the call is ignored (SBR_RESPONSE sbdm).
*/
SBR_CSR_EXPORT int sbr_sbdm_setmessagetype(abr_Ctx *ctx, sbr_Sbdm *sbdm, const char *messagetype);

/**
Get the message type for this sbdm.

This will override any value in the template 
(StandardBusinessDocumentHeader:Message.Type.Text).

If this is a response sbdm then this will return NULL.

@param sbdm the StandardBusinessDocumentMessage object. 

@return the messagetype string (e.g. "message.ping") or NULL.
*/
SBR_CSR_EXPORT const char *sbr_sbdm_messagetype(sbr_Sbdm *sbdm);

/**
Set the other party details for this sbdm and request (request only). 

This will override any value in the template 
- StandardBusinessDocumentHeader:Receiver:IdentificationDetails.IdentifierDesignation.Text (agencyid).
- StandardBusinessDocumentHeader:Receiver:IdentificationDetails.IdentifierName.Text (name).

If this is a response sbdm then this call will be ignored and will silently fail.

@param ctx the current thread local Context.
@param sbdm the StandardBusinessDocumentMessage object. 
@param partytype SBR_MSG_RECEIVER or SBR_MSG_SENDER - see sbr_eMsgPartyType
@param iddesignation the identifier designation string (e.g. "ato.gov.au").
@param idname the party identifier name - for agencies use SBR_PARTYSCHEME_AGENCY (preset to 'AgencyInternetDomainName').

@return ABR_ERR_OK if successful or an errorcode OR -1 if the call is ignored (SBR_RESPONSE sbdm).
*/
SBR_CSR_EXPORT int sbr_sbdm_setparty(abr_Ctx *ctx, sbr_Sbdm *sbdm, sbr_eMsgPartyType partytype, const char *iddesignation, const char *idname);

/**
Get the other party details for this sbdm.  

Use sbr_msgp_type() to determine if sender or receiver. 
Note that in a request the type will always be SBR_MSG_RECEIVER; 
and for a response it will always be SBR_MSG_SENDER.

@param sbdm the StandardBusinessDocumentMessage object. 
@param partytype SBR_MSG_RECEIVER or SBR_MSG_SENDER - see sbr_eMsgPartyType

@return an sbr_MsgParty object.
*/
SBR_CSR_EXPORT sbr_MsgParty *sbr_sbdm_party(sbr_Sbdm *sbdm, sbr_eMsgPartyType partytype);

/**
Create and add a new document object - use sbr_doc_setcontent() to add content (request only).

This will return an error if called on a response.

This object will be free when the request is freed. 
Alternatively, it will be freed if sbr_sbdm_doc_remove() is called on the returned document object.

An appropriate sequence number is assigned.

@param ctx the current thread local Context.
@param sbdm the StandardBusinessDocumentMessage object.
@param doc the address of the document object to create. Do not explictly free.
@param validationuri the validation uri
@param governmentid the government identifier
@param businessid a business specific identifier
@param createtime the time to assign as the create datetime.

@return ABR_ERR_OK if successful or an errorcode OR -1 if the call is ignored (SBR_RESPONSE sbdm).
*/
SBR_CSR_EXPORT int sbr_sbdm_doc_add(abr_Ctx *ctx, sbr_Sbdm *sbdm, sbr_Doc **doc, 
										const char *validationuri,
										const char *governmentid,
										const char *businessid,
										time_t createtime
										);

/**
Remove the indicated document from the sbdm (request only) - not currently implemented.

This will return an error if called on a response.

The document object will be freed, so do not reference it after this call.

@param ctx the current thread local Context.
@param sbdm the StandardBusinessDocumentMessage object.
@param doc the document object to free.

@return ABR_ERR_OK if successful or an errorcode OR -1 if the call is ignored (if its a SBR_RESPONSE sbdm).
*/
SBR_CSR_EXPORT int sbr_sbdm_doc_remove(abr_Ctx *ctx, sbr_Sbdm *sbdm, sbr_Doc *doc);

/** 
Get the number of documents in this sbdm.

@param sbdm the StandardBusinessDocumentMessage object.

@return document count. 
*/
SBR_CSR_EXPORT size_t sbr_sbdm_doc_count(sbr_Sbdm *sbdm);

/**
Create an iterator for the collection of a documents - caller must free.

This is useful if a collection is being shared between threads and each thread has its own iterator. 

If this is not the case then the sbr_sbdm_doc_firstv() and sbr_sbdm_doc_nextv() methods are simpler and this method can be ignored.

@param sbdm the StandardBusinessDocumentMessage object.
@param iter the address of the iterator to create - *iter must be NULL. 
This will be NULL if there is no collection.
*/
SBR_CSR_EXPORT void sbr_sbdm_doc_iterator(sbr_Sbdm *sbdm, abr_Iterator **iter);

/**
Get the first document of the collection.

This also initialises the iterator associated with the current sbdm eventitems.

@param sbdm the StandardBusinessDocumentMessage object.

@return a document or NULL if none.
*/
SBR_CSR_EXPORT sbr_Doc *sbr_sbdm_doc_firstv(sbr_Sbdm *sbdm);

/**
Get the next document of the collection.

@param sbdm the StandardBusinessDocumentMessage object.

@return a document or NULL if none.
*/
SBR_CSR_EXPORT sbr_Doc *sbr_sbdm_doc_nextv(sbr_Sbdm *sbdm);

/**
Get the receipt object for the sbdm (response only).

This will return NULL if called on a request sbdm.

@param sbdm the StandardBusinessDocumentMessage object.

@return a receipt object or NULL.
*/
SBR_CSR_EXPORT sbr_MsgReceipt *sbr_sbdm_receipt(sbr_Sbdm *sbdm);

/**
Get the maxseveritycode for the sbdm (response only).

This will return NULL if called on a request sbdm.

This will be set to 'Information' in the case of no errors.

@param sbdm the StandardBusinessDocumentMessage object.

@return the max severity code value or NULL.
*/
SBR_CSR_EXPORT const char *sbr_sbdm_maxseveritycode(sbr_Sbdm *sbdm);

/**
Get the number of event items (response only).

This will return 0 if called on a request sbdm.

There will be at least one, even when there are no errors. 

@param sbdm the StandardBusinessDocumentMessage object.

@return item count or 0.
*/
SBR_CSR_EXPORT size_t sbr_sbdm_eventitem_count(sbr_Sbdm *sbdm);

/**
Create an iterator for the collection of event items to use in an iterator (response only) - caller must free.

This is useful if a collection is being shared between threads and each thread has its own iterator. 

If this is not the case then the sbr_sbdm_eventitem_firstv() and sbr_sbdm_eventitem_nextv() methods are simpler and this method can be ignored.

This will return NULL if called on a request sbdm.

@param sbdm the StandardBusinessDocumentMessage object.
@param iter the address of the iterator to create - *iter must be NULL. 
This will be NULL if there is no collection.
*/
SBR_CSR_EXPORT void sbr_sbdm_eventitem_iterator(sbr_Sbdm *sbdm, abr_Iterator **iter);

/**
Get the first event item of the collection (response only).

This also initialises the iterator associated with the current sbdm eventitems.

This will return NULL if called on a request sbdm.

@param sbdm the StandardBusinessDocumentMessage object.

@return an eventitem or NULL if none or this is a request.
*/
SBR_CSR_EXPORT sbr_MsgEventItem *sbr_sbdm_eventitem_firstv(sbr_Sbdm *sbdm);

/**
Get the next event item of the collection (response only).

This will return NULL if called on a request sbdm.

@param sbdm the StandardBusinessDocumentMessage object.

@return an eventitem or NULL if none or this is a request.
*/
SBR_CSR_EXPORT sbr_MsgEventItem *sbr_sbdm_eventitem_nextv(sbr_Sbdm *sbdm);

/**
Get the number of timestamps.

@param sbdm the StandardBusinessDocumentMessage object.

@return count or 0.
*/
SBR_CSR_EXPORT size_t sbr_sbdm_timestamp_count(sbr_Sbdm *sbdm);

/**
Create an iterator for the collection of timestamps - caller must free.

This is useful if a collection is being shared between threads and each thread has its own iterator.

If this is not the case then the sbr_sbdm_timestamp_firstv() and sbr_sbdm_timestamp_nextv() methods are simpler and this method can be ignored.

@param sbdm the StandardBusinessDocumentMessage object.
@param iter the address of the iterator to create - *iter must be NULL. 
This will be NULL if there is no collection.
*/
SBR_CSR_EXPORT void sbr_sbdm_timestamp_iterator(sbr_Sbdm *sbdm, abr_Iterator **iter);

/**
Get the first timestamp of the collection.

This also initialises the iterator associated with the current sbdm timestamps.

@param sbdm the StandardBusinessDocumentMessage object.

@return an eventitem NULL if none.
*/
SBR_CSR_EXPORT sbr_MsgTimestamp *sbr_sbdm_timestamp_firstv(sbr_Sbdm *sbdm);

/**
Get the next timestamp of the collection.

@param sbdm the StandardBusinessDocumentMessage object.

@return a timestamp or NULL if none.
*/
SBR_CSR_EXPORT sbr_MsgTimestamp *sbr_sbdm_timestamp_nextv(sbr_Sbdm *sbdm);

#ifdef __cplusplus
}
#endif 

/*! @} */

#endif /*__SBR_CSR_SBDM_H__*/
