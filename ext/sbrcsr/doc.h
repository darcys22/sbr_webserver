#ifndef __SBR_CSR_DOC_H__
#define __SBR_CSR_DOC_H__

/** @addtogroup sbrcsr_api_csr_doc

@{
*/

/**
The CSR Business Document object.

Used when adding business documents to a request for submission to CSR - see also @ref sbr_Request.
Used when extracting business documents from a response - see also @ref sbr_Response.
*/
typedef struct _sbr_Doc sbr_Doc;

#ifdef __cplusplus
extern "C" {
#endif

/**
Return the unique id for the Document - this is a memory only value.

@param doc the Business Document

@return unique id.
*/
SBR_CSR_EXPORT const char *sbr_doc_iid(sbr_Doc *doc);

/**
Return the document content.

@param doc the Business Document.

@return document content.
*/

SBR_CSR_EXPORT const char *sbr_doc_content(sbr_Doc *doc);
/**
Return the government id.

@param doc the Business Document.

@return the government id or NULL if none.
*/
SBR_CSR_EXPORT const char *sbr_doc_governmentid(sbr_Doc *doc);

/**
Return the business id.

@param doc the Business Document.

@return the business id or NULL if none.
*/
SBR_CSR_EXPORT const char *sbr_doc_businessid(sbr_Doc *doc);

/**
Return the document create time.

@param doc the Business Document.

@return document create time or NULL if none.
*/
SBR_CSR_EXPORT const char *sbr_doc_createtime(sbr_Doc *doc);

/**
Return the validation uri.

@param doc the Business Document.

@return the validation uri or NULL if none.
*/
SBR_CSR_EXPORT const char *sbr_doc_validationuri(sbr_Doc *doc);

/**
Return the sequence number (starting at 1) of the document within the @ref sbr_Sbdm object.

@param doc the Business Document.

@return the sequence number.
*/
SBR_CSR_EXPORT size_t sbr_doc_sequencenr(sbr_Doc *doc);

/**
Return whether the document is within a @ref sbr_Request or @ref sbr_Response.

@param doc the Business Document.

@return SBR_MSG_RESPONSE or SBR_MSG_REQUEST.
*/
SBR_CSR_EXPORT sbr_eMsgSourceType sbr_doc_msgsourcetype(sbr_Doc *doc);

/**
Set the content of a document in a Request document - see also sbr_doc_setcontentref(). 

@param ctx the current thread local Context.
@param doc the Business Document.
@param content the content of the document (e.g. the xbrl)
This is inserted at StandardBusinessDocumentBody:BusinessDocumentInstances:BusinessDocument.Instance.Text
@param contentaction tells the attachment object what to do with the content. 
ABR_PARAMACTION_DEFAULT or ABR_PARAMACTION_COPY will cause a copy to be taken. ABR_PARAMACTION_CONST will cause
content to be referenced directly and not touched in any way - the caller must maintain until the attachment is freed. 
ABR_PARAMACTION_FREE is not valid as content is a const - use sbr_doc_setcontentref() for this.

@return ABR_ERR_OK if successful or an errorcode OR -1 if the call is ignored (SBR_RESPONSE sbdm).
*/
SBR_CSR_EXPORT int sbr_doc_setcontent(abr_Ctx *ctx, sbr_Doc *doc, const char *content, abr_eParamAction contentaction);

/**
Set the content of a document in a Request document where content is a non-const parameter - see also sbr_doc_setcontent().  

@param ctx the current thread local Context.
@param doc the Business Document.
@param content the content of the document (e.g. the xbrl)
This is inserted at StandardBusinessDocumentBody:BusinessDocumentInstances:BusinessDocument.Instance.Text
@param contentaction tells the attachment object what to do with the content. 
ABR_PARAMACTION_DEFAULT or ABR_PARAMACTION_COPY will cause a copy to be taken. ABR_PARAMACTION_CONST will cause
content to be referenced directly and not touched in any way - the caller must maintain until the attachment is freed. 
ABR_PARAMACTION_FREE will cause content to be referenced directly and will be freed when the attachment is freed (i.e. the 
attachment object takes "ownership" of the content).

@return ABR_ERR_OK if successful or an errorcode OR -1 if the call is ignored (SBR_RESPONSE sbdm).
*/
SBR_CSR_EXPORT int sbr_doc_setcontentref(abr_Ctx *ctx, sbr_Doc *doc, char *content, abr_eParamAction contentaction);

/**
Set the validationuri of a document in a Request document. 

@param ctx the current thread local Context.
@param doc the Business Document.
@param validationuri the validationuri to use in the header 

@return ABR_ERR_OK if successful or an errorcode OR -1 if the call is ignored (SBR_RESPONSE sbdm).
*/
SBR_CSR_EXPORT int sbr_doc_setvalidationuri(abr_Ctx *ctx, sbr_Doc *doc, const char *validationuri);

/**
Set the governmentid of a document in a Request document. 

@param ctx the current thread local Context.
@param doc the Business Document.
@param governmentid the validationuri to use in the header 

@return ABR_ERR_OK if successful or an errorcode OR -1 if the call is ignored (SBR_RESPONSE sbdm).
*/
SBR_CSR_EXPORT int sbr_doc_setgovernmentid(abr_Ctx *ctx, sbr_Doc *doc, const char *governmentid);

/**
Set the businessid of a document in a Request document. 

@param ctx the current thread local Context.
@param doc the Business Document.
@param businessid the businessid to use in the header 

@return ABR_ERR_OK if successful or an errorcode OR -1 if the call is ignored (SBR_RESPONSE sbdm).
*/
SBR_CSR_EXPORT int sbr_doc_setbusinessid(abr_Ctx *ctx, sbr_Doc *doc, const char *businessid);

/**
Set the createtime of a document in a Request document. 

@param ctx the current thread local Context.
@param doc the Business Document.
@param createtime the createtime to use in the header.

@return ABR_ERR_OK if successful or an errorcode OR -1 if the call is ignored (SBR_RESPONSE sbdm).
*/
SBR_CSR_EXPORT int sbr_doc_setcreatetime(abr_Ctx *ctx, sbr_Doc *doc, time_t createtime);

/**
Return the number of attachments this document has.

@param doc the Business Document.

@return a count of the number of attachments.
*/
SBR_CSR_EXPORT size_t sbr_doc_attachment_count(sbr_Doc *doc);

/**
Create an iterator for the collection of attachments - caller must free.

This is useful if a collection is being shared between threads and each thread has its own iterator. 

If this is not the case then the sbr_doc_attachment_firstv() and sbr_doc_attachment_nextv() methods are simpler and this method can be ignored.

@param doc the Business Document.
@param iter the address of the iterator to create - *iter must be NULL. 
This will be NULL if there is no collection.
*/
SBR_CSR_EXPORT void sbr_doc_attachment_iterator(sbr_Doc *doc, abr_Iterator **iter);

/**
Get the first attachment of the collection.

This also initialises the iterator associated with the current doc attachments.

@param doc the Business Document.

@return an attachment or NULL if none.
*/
SBR_CSR_EXPORT sbr_DocA *sbr_doc_attachment_firstv(sbr_Doc *doc);

/**
Get the next attachment of the collection.

@param doc the Business Document.

@return an attachment or NULL if none.
*/
SBR_CSR_EXPORT sbr_DocA *sbr_doc_attachment_nextv(sbr_Doc *doc);

/**
Add an attachment to a Request document - use sbr_doca_setcontent() to set the content.

@param ctx the current thread local Context.
@param doc the Business Document.
@param attachment the address of the attachment object to allocate - DO NOT free.
@param description a description to use in the header 
@param filename the filename to associate with the attachment
@param contenttype the type of the content

@return ABR_ERR_OK if successful or an errorcode OR -1 if the call is ignored (if it's a SBR_RESPONSE sbdm).
*/
SBR_CSR_EXPORT int sbr_doc_attachment_add(abr_Ctx *ctx, sbr_Doc *doc, sbr_DocA **attachment, 
											   const char *description,
											   const char *filename,
											   const char *contenttype
											   );

/**
Remove an attachment from a Request document - not currently implemented.

@param ctx the current thread local Context.
@param doc the Business Document.
@param attachment the attachment object.

@return ABR_ERR_OK if successful or an errorcode OR -1 if the call is ignored (if it's a SBR_RESPONSE sbdm).
*/
SBR_CSR_EXPORT int sbr_doc_attachment_remove(abr_Ctx *ctx, sbr_Doc *doc, sbr_DocA *attachment);

#ifdef __cplusplus
}
#endif 

/*! @} */

#endif /*__SBR_CSR_DOC_H__*/
