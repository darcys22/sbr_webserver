#ifndef __SBR_CSR_RESPONSE_H__
#define __SBR_CSR_RESPONSE_H__

/** @addtogroup sbrcsr_api_csr_res

@{
*/

/**
The CSR response object for a given sbr_CsrRequest.
*/
typedef struct _sbr_Response sbr_Response;

#ifdef __cplusplus
extern "C" {
#endif

/**
This is a convenience method to extract the entire response as an XML string.

@param ctx the current thread local Context.
@param response the CSR Response object.
@param buffer the address of the string buffer to put the response into.

@return ABR_ERR_OK or an error code. Use abr_errdef_name() to get the code as a string.
*/
SBR_CSR_EXPORT int sbr_res_xml(abr_Ctx *ctx, sbr_Response *response, char **buffer);

/**
Return the number of @ref sbr_Sbdm objects in the response.

@param response the response object.

@return number of Sbdm objects.
*/
SBR_CSR_EXPORT size_t sbr_res_sbdm_count(sbr_Response *response);

/**
Create an iterator for the collection of sbdms - caller must free.

This is useful if a collection is being shared between threads and each thread has its own iterator.

If this is not the case then the sbr_res_sbdm_firstv() and sbr_res_sbdm_nextv() methods are simpler and this method can be ignored.

@param response the response object.
@param iter the address of the iterator to create - *iter must be NULL. 
This will be NULL if there is no collection.
*/
SBR_CSR_EXPORT void sbr_res_sbdm_iterator(sbr_Response *response, abr_Iterator **iter);

/**
Get the first sbdm of the collection.

This also initialises the iterator associated with the current sbdms.

@param response the response object.

@return an sbdm or NULL if none.
*/
SBR_CSR_EXPORT sbr_Sbdm *sbr_res_sbdm_firstv(sbr_Response *response);

/**
Get the next sbdm of the collection.

@param response the response object.

@return an sbdm or NULL if none.
*/
SBR_CSR_EXPORT sbr_Sbdm *sbr_res_sbdm_nextv(sbr_Response *response);

/**
Search the maxseveritycode for all sbdms for the given value (response only).

The search is case-insensitive. This will return FALSE if called on a request sbdm.

@param response the response object.
@param severitycode the severity string to search for e.g. "error".

@return TRUE if the supplied value is matched else FALSE.
*/
SBR_CSR_EXPORT bool sbr_res_ismaxseveritycode(sbr_Response *response, const char *severitycode);

#ifdef __cplusplus
}
#endif 

/*! @} */

#endif /*__SBR_CSR_RESPONSE_H__*/
