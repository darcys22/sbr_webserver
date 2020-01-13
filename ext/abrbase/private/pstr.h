#ifndef __ABR_STR_PRIVATE_H__
#define __ABR_STR_PRIVATE_H__

#include <stddef.h>

/* @defgroup abrbase_api_pstr PString
@ingroup abrbase_api_private

Create and manage "string" objects that encapsulate non-const and const char arrays with explicit length. 

Unlike many other languages, C does not associate lengths with "strings" or arrays. 
This results in length (size_t) and "string" data (char *) being handled (passed) separately in many methods. 
Since this is so frequent in the API, abr_String and its associated API, encapsulates length and data together. 
It can also handle const and non-const char arrays. This should be used for all public methods and, 
where convenient, for internal methods.

This String does not rely on NULL termination of the array.

@{
*/

#include "abrbase/str.h"

typedef void (abr_str_freefunction)(void *data);

typedef enum { 
	ABR_STR_FORMAT_UNDEFINED = 0, // depends on context i.e. API that generated this.
	ABR_STR_FORMAT_BINARY,
	ABR_STR_FORMAT_BASE64,
	ABR_STR_FORMAT_HEX,
	ABR_STR_FORMAT_STR
} abr_eStrFormat;

#ifdef __cplusplus
extern "C" {
#endif 

/**
Get the format of the string. 

This is informational only and is not used internally. It's up to the calling code to track this correctly.

@param str the string object.
@return format to record. 
*/
ABR_EXPORT abr_eStrFormat abr_str_type(abr_String *str);

/**
Set the format of the string. 

This is informational only and is not used internally. It's up to the calling code to track this correctly.

@param str the address of the string object to allocate.
@param format format to record. 
*/
ABR_EXPORT void abr_str_setformat(abr_String *str, abr_eStrFormat format);

/**
Initialise all characters of the string to the given value. 

Use this to clear ('\0') the string if desired e.g. passwords.

@param str the address of the string object to allocate.
@param format format to record. 
*/
ABR_EXPORT void abr_str_init(abr_String *str, int value);

/**
Return the str as a null terminated char array. 

The calling code is responsible for ensuring the contents are valid for cstrings (no embedded nulls).
The calling code is responsible for freeing the object.

@param str the address of the string object to allocate.
@return the newly allocated char array. 
*/
ABR_EXPORT char *abr_str_cstr(abr_String *str);

/**
Don't free non-const content using free(), but instead call the supplied callback method to do the free.
This should be done where an external shared library has allocated the content and supplies some kind of free method
to free it. In this case freeing data allocated in a different library can lead to segmentation faults due to differing
implementations of memory management.

@param str the address of the string object to allocate.
@param callback the callback to use - if NULL use default free().
@param data transparent data to be passed to the callback method.
*/
ABR_EXPORT void abr_str_setfreefn(abr_String *str, abr_str_freefunction callback, void *data);

/**
Duplicate the abr_String object - iscstr is taken into account. 
@param str the address of the string object to allocate.
@param src the string object to copy.
@return ABR_ERR_OK. A memory allocation error will result in an assertion failure.
*/
ABR_EXPORT void abr_str_dup(abr_String **str, const abr_String *src);

/**
As for abr_str_dup() except forces the destination to be null terminated.
If iscstr is FALSE, then this call is the same as calling abr_str_dup().

@param str the address of the string object to allocate.
@param src the string object to copy.
@param iscstr indicates that the buffer contains an additional terminating '\0'.
@return ABR_ERR_OK. A memory allocation error will result in an assertion failure.
*/
ABR_EXPORT void abr_str_dup2(abr_String **str, const abr_String *src, bool iscstr);

/**
Set the contents of an existing abr_String object. Current contents will be discarded appropriately.
@param str the string object.
@param value the non-const value to use. IMPORTANT: the "ownership" of value is transferred to the abr_String object. See abr_str_free().
@param len the length of the char array.
@param iscstr indicates that the buffer contains an additional terminating '\0'.
@return ABR_ERR_OK. A memory allocation error will result in an assertion failure.
*/
ABR_EXPORT void abr_str_set(abr_String *str, char *value, size_t len, bool iscstr);

/**
Set the contents of an existing abr_String object. Current contents will be discarded appropriately.
@param str the string object.
@param value the char array to encapsulate. In this case the array is not freed when calling abr_str_free().
@param len the length of the char array.
@param iscstr indicates that the buffer contains an additional terminating '\0'.
@return ABR_ERR_OK. A memory allocation error will result in an assertion failure.
*/
ABR_EXPORT void abr_str_setconst(abr_String *str, const char *value, size_t len, bool iscstr);

/**
Check if the str or underlying value is NULL or an empty string.
@param str the string object.
@return TRUE or FALSE.
*/
ABR_EXPORT bool abr_str_isnullorempty(abr_String *str);

/**
Where the object has been created with a non-const value, return the non-const value and transfer the ownership to the caller.
This will force the current contents to revert to const and not be freed - as though abr_str_createconst() were used.
If the underlying object was const anyway, this will return NULL rather than the underlying value - 
in which case, use abr_str_value().
@param str the string object.
@return the char array or NULL if currently not assigned or str is NULL or underlying value is const.
*/
ABR_EXPORT char *abr_str_valueasowner(abr_String *str);

/**
Two strings are equal if they have the same contents.

@param str the string object.
@param str2 string object.
@return TRUE if the same.
*/
ABR_EXPORT bool abr_str_eq(abr_String *str, abr_String *str2);

/**
Check if the string has the given value.

@param str the string object.
@param cstr the char * value.
@return TRUE if the same.
*/
ABR_EXPORT bool abr_str_eqv(abr_String *str, const char *cstr);

/**
Add the given value to a list of values to be catanated. The result is not available
until abr_str_add_complete() is called.

@param str the string object - it MUST be available until abr_str_add_complete() is called.
@param cstr the char * value.
*/
ABR_EXPORT void abr_str_add(abr_String *str, const char *cstr);

/**
This assigns the catanation of all list values so that abr_str_value() will 
return the result at that point. Values can continue to be added by abr_str_add().

@param str the string object.
@param cstr the char * value.
*/
ABR_EXPORT void abr_str_add_complete(abr_String *str);


#ifdef __cplusplus
}
#endif 

/*! @} */

#endif /*__ABR_STR_PRIVATE_H__*/
