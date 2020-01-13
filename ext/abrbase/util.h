#ifndef __ABR_UTIL_H__
#define __ABR_UTIL_H__

#include <stddef.h>

/* @defgroup abrbase_api_util Util
@ingroup abrbase_api_public

General utility methods used in the SDK codebase. They are available to use by application developers
should they so wish. 

Note: in API comments elsewhere, the terms "string" generally refers to a '\0' terminated char array (C string), 
whereas "abr string" refers the @ref abr_String object.

@{
*/

#ifdef __cplusplus
extern "C" {
#endif 

/**
Accepts a Base64 array and returns the decoded (possibly binary) data and data length in an abr_String.

To access content, use abr_str_value() and abr_str_len().

@param ctx the current thread local Context
@param data the address of abr_String buffer for the decoded content - caller must free using abr_str_free().
@param b64 the encoded base64 array to decode.
@param len the length of the b64 array

@return ABR_ERR_OK or an error.
*/
ABR_EXPORT int abr_base64decode_array(abr_Ctx *ctx, abr_String **data, const char *b64, size_t len);

/**
Accepts data and returns the Base64 encoded data as an abr_String.

To access content, use abr_str_value() and abr_str_len().

@param ctx the current thread local Context
@param b64 the address of abr_String buffer for the encoded content - caller must free using abr_str_free().
@param data the content - possibly binary
@param len the length of the content

@return ABR_ERR_OK or an error.
*/
ABR_EXPORT int abr_base64encode_array(abr_Ctx *ctx, abr_String **b64, const char *data, size_t len);

#ifdef __cplusplus
}
#endif 

/*! @} */

#endif /*__ABR_UTIL_H__*/
