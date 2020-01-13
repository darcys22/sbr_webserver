#ifndef __SBR_CSR_H__
#define __SBR_CSR_H__

/** @addtogroup sbrcsr_api_csr

@{
*/

/**
The CSR object used to interact with an SBR core services service to submit business reports.

Use this object to construct one or more sbr_Request objects, each of which contains a @ref sbr_Response object.
*/
typedef struct _sbr_Csr sbr_Csr;

#ifdef __cplusplus
extern "C" {
#endif

/**
Create a CSR object from the XML stored in csrtemplate. 

@param ctx the current thread local Context.
@param csr the address of the object to create. *csr must be initialised to NULL.
@param servicetype the servicetype id to use within the CSR config context. A NULL value will result in an assertion error.
@param csrurl the URL of the CSR service to use. If NULL, the value is read from the current context and servicetype.
@param csrtemplate the XML content. A NULL or empty value will result in an assertion error.
sbr_csr_loadtemplate() is provided as a helper function to load from the filesystem.

@return ABR_ERR_OK
*/
SBR_CSR_EXPORT int sbr_csr_create(abr_Ctx *ctx, sbr_Csr **csr, const char *servicetype, const char *csrurl, const char *csrtemplate);

/**
Free the CSR object if not NULL.

@param csr the CSR object. If NULL do nothing.
*/
SBR_CSR_EXPORT void sbr_csr_free(sbr_Csr *csr);

/**
Get the network total timeout value, in seconds, used for requests to SBR CSR services. 

@param ctx the current thread local Context.
@param csr the CSR object.

@return the current timeout value.
*/
SBR_CSR_EXPORT size_t sbr_csr_timeout(abr_Ctx *ctx, sbr_Csr *csr);

/**
Set the network total timeout value, in seconds, used for requests to SBR CSR services. 

This affects all new requests derived from this CSR instance.

@param ctx the current thread local Context.
@param csr the CSR object.
@param timeout the timeout value to set.
*/
SBR_CSR_EXPORT void sbr_csr_settimeout(abr_Ctx *ctx, sbr_Csr *csr, size_t timeout);

/**
Get the network connect timeout value, in seconds, used for requests to SBR CSR services. 

@param ctx the current thread local Context.
@param csr the CSR object.

@return the current timeout value.
*/
SBR_CSR_EXPORT size_t sbr_csr_timeoutconnect(abr_Ctx *ctx, sbr_Csr *csr);

/**
Set the network connect timeout value, in seconds, used for requests to SBR CSR services. 

This affects all new requests derived from this CSR instance.

@param ctx the current thread local Context.
@param csr the CSR object.
@param timeout the timeout value to set.
*/
SBR_CSR_EXPORT void sbr_csr_settimeoutconnect(abr_Ctx *ctx, sbr_Csr *csr, size_t timeout);

#ifdef __cplusplus
}
#endif 

/*! @} */

#endif /*__SBR_CSR_H__*/
