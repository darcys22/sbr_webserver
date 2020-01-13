#ifndef __ABR_UTIL_PRIVATE_H__
#define __ABR_UTIL_PRIVATE_H__

#include <stddef.h>

#include "abrbase/private/putilcore.h"
#include "abrbase/util.h"

/* @defgroup abrbase_api_putil PUtil
@ingroup abrbase_api_private

General utility methods used in the SDK codebase. They are available to use by application developers
should they so wish. 

Note: in API comments elsewhere, the terms "string" generally refers to a 0 terminated char array, 
whereas "abr string" refers the @ref abr_String object.

@{
*/

#ifdef __cplusplus
extern "C" {
#endif 

/**
Load the file content into a newly created abr_String buffer. The caller must use abr_str_free() when finished.
@param buffer the address of the abr_String buffer to create. This must be initialised to NULL.
@param filepath the file to load the content from into buffer.
@return ABR_ERR_OK(0) if successful, otherwise 
- ABR_ERR_FILEOPEN if file cannot be opened (no access or doesn't exist)
- ABR_ERR_FILESTAT if file size cannot be determined.
- ABR_ERR_FILEREAD if file cannot be read.
*/
ABR_EXPORT int abr_fileload(abr_String **buffer, const char* filepath);

/**
Write the buffer content into a file.
@param buffer the abr_String buffer containing the content to write.
@param filepath the file to write the content to. Existing files will be truncated.
@return ABR_ERR_OK(0) if successful, otherwise 
- ABR_ERR_FILEOPEN if file cannot be opened or created. 
- ABR_ERR_FILEWRITE if file cannot be written.
*/
ABR_EXPORT int abr_filewrite(abr_String *buffer, const char* filepath);

/**

*/
ABR_EXPORT int abr_base64decode(abr_Ctx *ctx, abr_String **data, abr_String *b64);
ABR_EXPORT int abr_base64encode(abr_Ctx *ctx, abr_String **b64, abr_String *data);
ABR_EXPORT char *abr_new_pseudo_guid(abr_Ctx *ctx, char *guidstr);
ABR_EXPORT char *abr_new_salt(abr_Ctx *ctx, char *salt);
ABR_EXPORT int abr_generatehmac(abr_Ctx *ctx, abr_String **hmac, abr_String *input, abr_String *salt);
ABR_EXPORT char *abr_md5(abr_Ctx *ctx, char *data, size_t len, bool hex);

#ifdef __cplusplus
}
#endif 

/*! @} */

#endif /*__ABR_UTIL_PRIVATE_H__*/
