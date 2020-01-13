#ifndef __SBR_CSR_REQUEST_H__
#define __SBR_CSR_REQUEST_H__

/** @addtogroup sbrcsr_api_csr_req

@{
*/

/**
The CSR request object used to submit a business report.
*/
typedef struct _sbr_Request sbr_Request;

/**
Default threshold to use for MTOM processing - see sbr_req_mtom_setsize().
*/
#define SBR_MTOM_THRESHOLD_DEFAULT 2000

#ifdef __cplusplus
extern "C" {
#endif

/**
Create a CSR request object based on the service type and template information of the CSR object. 
Use sbr_req_free() to free.


@param ctx the current thread local Context.
@param request the CSR request object.
@param csr the CSR service object used to construct the request.

@return ABR_ERR_OK
*/
SBR_CSR_EXPORT int sbr_req_create(abr_Ctx *ctx, sbr_Request **request, sbr_Csr *csr);

/**
Free the CSR request object if not NULL.

@param request the request object. If NULL do nothing.
*/
SBR_CSR_EXPORT void sbr_req_free(sbr_Request *request);

/**
This is a convenience method to extract the entire request as an XML string.

@param ctx the current thread local Context.
@param request the request object.
@param buffer the address of the buffer to allocate - must be freed by the caller.

@return ABR_ERR_OK or an error code.
*/
SBR_CSR_EXPORT int sbr_req_xml(abr_Ctx *ctx, sbr_Request *request, char **buffer);

/**
Use a CSR request object to submit to the CSR service and return a CSR response.

The set methods will assert if called AFTER a submit. To change values, create a new request.

@param ctx the current thread local Context.
@param request the request object. 
@param response the response object address (do not free) or NULL if none or an error occurred. 
@param certificate X509 certificate
@param privatekey P8 private key
@param prooftoken prooftoken from an STS response
@param assertion encrypted assertion from an STS response

@return ABR_ERR_OK or an error code.
*/
SBR_CSR_EXPORT int sbr_req_submit(abr_Ctx *ctx, sbr_Request *request, sbr_Response **response, abr_String *certificate, abr_String *privatekey, abr_String *prooftoken, abr_String *assertion);

/**
Set whether or not to process the request through the MTOM filter. 
This will convert all (Base64) element values over the given threshold size to binary before sending to the
CSR URL service endpoint. This typically applies to attachments.

@param request the request object. 
@param threshold the size, in bytes, of the value to apply the MTOM process to. 
If 0, turn off MTOM processing. For the default use the "#define" SBR_MTOM_THRESHOLD_DEFAULT.
*/
SBR_CSR_EXPORT void sbr_req_mtom_setsize(sbr_Request *request, size_t threshold);

/**
Return the current threshold size for processing content through MTOM.

@param request the request object.

@return the current MTOM size. If 0 MTOM processing is disabled.
*/
SBR_CSR_EXPORT size_t sbr_req_mtom_size(sbr_Request *request);

/**
Set the current softwareSubscriptionId value (copy taken), which may be NULL. 

Clear existing value if any.

This element will be only included in the request if the value is not NULL.

@param request the request object. 
@param ssid softwareSubscriptionId value. 
*/
SBR_CSR_EXPORT void sbr_req_ssid_set(sbr_Request *request, const char *ssid);

/**
Return the current softwareSubscriptionId value, which may be NULL.

@param request the request object.

@return the current softwareSubscriptionId value.
*/
SBR_CSR_EXPORT const char *sbr_req_ssid(sbr_Request *request);

/**
Return the number of @ref sbr_Sbdm objects in the request.

@param request the request object.

@return number of Sbdm objects.
*/
SBR_CSR_EXPORT size_t sbr_req_sbdm_count(sbr_Request *request);

/**
Create an iterator for the collection of sbdms to use - caller must free.

This is useful if a collection is being shared between threads and each thread has its own iterator. 

If this is not the case then the sbr_req_sbdm_firstv() and sbr_req_sbdm_nextv() methods are simpler and this method can be ignored.

@param request the request object.
@param iter the address of the iterator to create - *iter must be NULL. 
This will be NULL if there is no collection.
*/
SBR_CSR_EXPORT void sbr_req_sbdm_iterator(sbr_Request *request, abr_Iterator **iter);

/**
Get the first sbdm of the collection.

This also initialises the iterator associated with the current sbdms.

@param request the request object.

@return an sbdm or NULL if none.
*/
SBR_CSR_EXPORT sbr_Sbdm *sbr_req_sbdm_firstv(sbr_Request *request);

/**
Get the next sbdm of the collection.

@param request the request object.

@return an sbdm or NULL if none.
*/
SBR_CSR_EXPORT sbr_Sbdm *sbr_req_sbdm_nextv(sbr_Request *request);

/**
Create and add a new @ref sbr_Sbdm object - not currently implemented.

@param ctx the current thread local Context.
@param request the request object.
@param sbdm the address of the Sbdm object to allocate - DO NOT free. 
The object will be freed when the request is freed or sbr_req_sbdm_remove() is used.

@return ABR_ERR_OK or an error code.
*/
SBR_CSR_EXPORT int sbr_req_sbdm_add(abr_Ctx *ctx, sbr_Request *request, sbr_Sbdm **sbdm);

/**
Remove an existing @ref sbr_Sbdm object - not currently implemented.

@param ctx the current thread local Context.
@param request the request object.
@param sbdm the Sbdm object - DO NOT reference after this call. 
The object will be freed.

@return ABR_ERR_OK or an error code.
*/
SBR_CSR_EXPORT int sbr_req_sbdm_remove(abr_Ctx *ctx, sbr_Request *request, sbr_Sbdm *sbdm);

#ifdef __cplusplus
}
#endif 

/*! @} */

#endif /*__SBR_CSR_REQUEST_H__*/
