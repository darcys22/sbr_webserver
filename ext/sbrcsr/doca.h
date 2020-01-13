#ifndef __SBR_CSR_DOCA_H__
#define __SBR_CSR_DOCA_H__

/** @addtogroup sbrcsr_api_csr_doca

@{
*/

/**
The CSR Business Document Attachment object.
Used when adding business documents to a request for submission to CSR - see also @ref sbr_Request.
Used when extracting business documents from a response - see also @ref sbr_Response.
*/
typedef struct _sbr_DocA sbr_DocA;

#ifdef __cplusplus
extern "C" {
#endif

/**
Return the unique id for the Attachment - this is a memory only value.

@param attachment the Attachment

@return unique id.
*/
SBR_CSR_EXPORT const char *sbr_doca_iid(sbr_DocA *attachment);

/**
Return the attachment content as base64 within an @ref abr_String.

To access the content, use abr_str_value() and abr_str_len().

See also the utility methods abr_base64encode()/abr_base64decode() to convert binary to base64 and back.

@param attachment the Attachment.

@return attachment content or NULL if none.
*/
SBR_CSR_EXPORT abr_String *sbr_doca_content(sbr_DocA *attachment);

/**
Return the contenttype.

@param attachment the Attachment.

@return the contenttype.
*/
SBR_CSR_EXPORT const char *sbr_doca_contenttype(sbr_DocA *attachment);

/**
Return the description.

@param attachment the Attachment.

@return the description.
*/
SBR_CSR_EXPORT const char *sbr_doca_description(sbr_DocA *attachment);

/**
Return the filename.

@param attachment the Attachment.

@return the filename.
*/
SBR_CSR_EXPORT const char *sbr_doca_filename(sbr_DocA *attachment);

/**
Return the sequence number (starting at 1) of the attachment within the document.

@param attachment the Attachment.

@return the sequence number.
*/
SBR_CSR_EXPORT size_t sbr_doca_sequencenr(sbr_DocA *attachment);

/**
Return whether the attachment is within a @ref sbr_Request or @ref sbr_Response.

@param attachment the Attachment.

@return SBR_MSG_RESPONSE or SBR_MSG_REQUEST.
*/
SBR_CSR_EXPORT sbr_eMsgSourceType sbr_doca_msgsourcetype(sbr_DocA *attachment);

/**
Set the content of an attachment in a Request document.

See also the utility methods: abr_base64encode_array()/abr_base64decode_array() to convert binary to base64 and back; and 
abr_str_create() to wrap char[] in an abr_String object if required.

@param ctx the current thread local Context.
@param attachment the Document Attachment.
@param content the base64 content of the attachment as an abr_String (e.g. the PDF itself).
@param contentaction tells the attachment object what to do with the content. 
ABR_PARAMACTION_DEFAULT or ABR_PARAMACTION_COPY will cause a copy to be taken. ABR_PARAMACTION_CONST will cause
content to be referenced directly and not touched in any way - the caller must maintain until the attachment is freed. 
ABR_PARAMACTION_FREE will cause content to be referenced directly and will be freed when the attachment is freed (i.e. the 
attachment object takes "ownership" of the content).

@return ABR_ERR_OK if successful or an errorcode OR -1 if the call is ignored (SBR_RESPONSE sbdm).
*/
SBR_CSR_EXPORT int sbr_doca_setcontent(abr_Ctx *ctx, sbr_DocA *attachment, abr_String *content, abr_eParamAction contentaction);

/**
Set the content of an attachment in a Request document. 

@param ctx the current thread local Context.
@param attachment the Document Attachment.
@param description the description of the attachment (e.g. the PDF itself)

@return ABR_ERR_OK if successful or an errorcode OR -1 if the call is ignored (SBR_RESPONSE sbdm).
*/
SBR_CSR_EXPORT int sbr_doca_setdescription(abr_Ctx *ctx, sbr_DocA *attachment, const char *description);

/**
Set the filename of an attachment in a Request document. 

@param ctx the current thread local Context.
@param attachment the Document Attachment.
@param filename the filename of the attachment (e.g. the PDF itself)

@return ABR_ERR_OK if successful or an errorcode OR -1 if the call is ignored (SBR_RESPONSE sbdm).
*/
SBR_CSR_EXPORT int sbr_doca_setfilename(abr_Ctx *ctx, sbr_DocA *attachment, const char *filename);

/**
Set the contenttype of an attachment in a Request document. 

@param ctx the current thread local Context.
@param attachment the Document Attachment.
@param contenttype the contenttype of the attachment 

@return ABR_ERR_OK if successful or an errorcode OR -1 if the call is ignored (SBR_RESPONSE sbdm).
*/
SBR_CSR_EXPORT int sbr_doca_setcontenttype(abr_Ctx *ctx, sbr_DocA *attachment, const char *contenttype);

#ifdef __cplusplus
}
#endif 

/*! @} */

#endif /*__SBR_CSR_DOCA_H__*/
