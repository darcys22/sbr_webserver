#ifndef __ABR_ERRSOAP_H__
#define __ABR_ERRSOAP_H__

/** @addtogroup abrbase_api_public_errsoap

@{
*/

/**
This object represents a SOAP fault.

This object will be created and attached to the top level generic
@ref abr_Err object returned by the method in which the error occurred. 
Use abr_err_customobj() to retrieve this object.
*/
typedef struct _abr_ErrSoap abr_ErrSoap;

/**
This object represents a code or subcode node in a SOAP fault.
*/
typedef struct _abr_ErrSoapCode abr_ErrSoapCode;

#ifdef __cplusplus
extern "C" {
#endif

/**
Confirms whether or not the error object is of the expected type.

The other methods will assert if this is false.

@param err the soap error object.

@return TRUE if err is of type abr_ErrSoap, otherwise false.
*/
ABR_EXPORT bool abr_errsoap_issoaperr(abr_ErrSoap *err);

/**
Decribes the service node where the error occured.

@param err the soap error object.

@return service node
*/
ABR_EXPORT const char *abr_errsoap_node(abr_ErrSoap *err);

/**
Describes the specifics of the particular error condition, and reflects the finest granularity 
of subcode provided in the fault.

@param err the soap error object.

@return the reason details.
*/
ABR_EXPORT const char *abr_errsoap_reason(abr_ErrSoap *err);

/**
This contains low-level details of the fault and is only provided in non-production environments.

@param err the soap error object.

@return fault details.
*/
ABR_EXPORT const char *abr_errsoap_detail(abr_ErrSoap *err);

/**
Returns the number of subcodes including the toplevel code.

@param err the soap error object.

@return the number or codes/subcodes.
*/
ABR_EXPORT size_t abr_errsoap_code_count(abr_ErrSoap *err);

/**
Create an iterator for the collection of errors - caller must free.

This is useful if a collection is being shared between threads and each thread has its own iterator. 
It is also useful in the unlikely case that higher level code and nested code are bother iterating the 
underlying collection. 

If this is not the case then the abr_errsoap_code_firstv() and abr_errsoap_code_nextv() methods are simpler and this method can be ignored.

@param err the soap error object.
@param iter the address of the iterator to create - *iter must be NULL. 
This will be NULL if there is no collection.
*/
ABR_EXPORT void abr_errsoap_code_iterator(abr_ErrSoap *err, abr_Iterator **iter);

/**
Get the first code of the collection.

This also initialises the iterator associated with the current sbdm timestamps.

@param err the soap error object.

@return a sub/code or NULL if none.
*/
ABR_EXPORT abr_ErrSoapCode *abr_errsoap_code_firstv(abr_ErrSoap *err);

/**
Get the next code of the collection.

@param err the soap error object.

@return a sub/code or NULL if none.
*/
ABR_EXPORT abr_ErrSoapCode *abr_errsoap_code_nextv(abr_ErrSoap *err);

/**
Returns the value of the code/subcode.

@param code the soap error code.

@return the value of the code/subcode or NULL if none.
*/
ABR_EXPORT const char *abr_errsoap_code_value(abr_ErrSoapCode *code);

/**
Returns the namespace of the code/subcode.

@param code the soap error code.

@return the namespace of the code/subcode or NULL if none.
*/
ABR_EXPORT const char *abr_errsoap_code_ns(abr_ErrSoapCode *code);

#ifdef __cplusplus
}
#endif 

/*! @} */

#endif /*__ABR_ERRSOAP_H__*/
