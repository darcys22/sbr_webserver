#ifndef __ABR_STR_H__
#define __ABR_STR_H__

#include <stddef.h>

/** @addtogroup abrbase_api_public_str

Unlike many other languages, C does not associate lengths with "strings" or arrays. 
This results in length (size_t) and "string" data (char *) being handled (passed) separately in many methods. 
Since this is so frequent in the API, abr_String and its associated API, encapsulates length and data together. 
It can also handle const and non-const char arrays. This should be used for all public methods and, 
where convenient, for internal methods.

@ref abr_String does not rely on NULL termination of the array.

@{
*/

/**
The object type encapsulating: C strings and char arrays with length, which can be const and non-const. 
This is used as a convenient abstraction by many API methods to tie length to "strings" and to track "constanceness"
to determine how content should be free.
*/
typedef struct _abr_String abr_String;

#ifdef __cplusplus
extern "C" {
#endif 

/**
Create an abr_String object with the given non-const value and length. See also abr_str_createconst().
@param str the address of the object to create. The caller must free with abr_str_free().
@param value the char array to encapsulate - caller must NOT free. 
IMPORTANT: the "ownership" of value is transferred to the abr_String object. See abr_str_free().
@param len the length of the char array.
@param iscstr if TRUE an extra '\0' is expected at the end of the string 

@return pointer to the allocated abr_String object or NULL if allocation failed. 
Note that, currently, out of memory errors result in assert failures.
*/
ABR_EXPORT abr_String *abr_str_create(abr_String **str, char *value, size_t len, bool iscstr);

/**
Create an abr_String object with the given const value and length. See also abr_str_create().
@param str the address of the object to create. The caller must free with abr_str_free().
@param value the char array to encapsulate. In this case the array is not freed when calling abr_str_free().
@param len the length of the char array.
@param iscstr if TRUE an extra '\0' is expected at the end of the string 

@return pointer to the allocated abr_String object or NULL if allocation failed. 
Note that, currently, out of memory errors result in assert failures.
*/
ABR_EXPORT abr_String *abr_str_createconst(abr_String **str, const char *value, size_t len, bool iscstr);

/**
Free the abr_String object. If the underlying value is non-const, then free that as well.
@param str the string object.
*/
ABR_EXPORT void *abr_str_free(abr_String *str);

/**
Return the char array as a const.
@param str the string object.
@return the char array or NULL if currently not assigned or str is NULL.
*/
ABR_EXPORT const char *abr_str_value(const abr_String *str);

/**
Return the length of the char array.
@param str the string object.
@return the length of the char array. 0 is returned if NULL or empty.
*/
ABR_EXPORT size_t abr_str_len(const abr_String *str);

/**
Checks if this is was originally set as a null terminated cstr.

If str is NULL this returns FALSE. 

@param str the string object.
@return TRUE or FALSE.
*/
ABR_EXPORT bool abr_str_iscstr(abr_String *str);

#ifdef __cplusplus
}
#endif 

/*! @} */

#endif /*__ABR_STR_H__*/
