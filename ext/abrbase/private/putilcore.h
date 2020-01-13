#ifndef __ABR_UTILCORE_PRIVATE_H__
#define __ABR_UTILCORE_PRIVATE_H__

#include <stddef.h>

#include "abrbase/utilcore.h"

/* @defgroup abrbase_api_putil PUtil
@ingroup abrbase_api_private

@{
*/

/**
The ABR_ASSERT_ISNOTALLOCATED() function macro is used whenever an API method in an SDK has to allocate memory.
It checks that the memory (*obj) is initialised to NULL. This catches some circumstances where
allocated memory may be leaked. 
This is only enabled if the macro ABR_CHECK_ISNOTALLOCATED is defined.
Otherwise just check the pointer itself is not NULL (a NULL argument check within the API calls).
ABR_CHECK_ISNOTALLOCATED is typically undefined (at least in the release binaries) 
as the preferred mechanism is to use a memory profiler such as Valgrind or Purify - however 
it may be useful during debugging and testing.
*/ 
#define ABR_CHECK_ISNOTALLOCATED
#ifdef ABR_CHECK_ISNOTALLOCATED
#define ABR_ASSERT_ISNOTALLOCATED(obj) (assert((obj) != NULL && *(obj) == NULL))
#else
#define ABR_ASSERT_ISNOTALLOCATED(obj) (assert((obj) != NULL)
#endif

/** @internal
Strip the const attribute from types. For example "const char *" becomes "char *'.
This is useful for passing const types to third party libraries that don't support them, yet are 
treating them as const. This, obviously, should be used with care and ONLY as a last resort if you are 
sure the method is treating it as a const.
*/
#define ABR_REMOVE_CONST(x, type) ((type)(uintptr_t)(const void *)(x))
//#define ABR_REMOVE_CONST(x, type) ((type)(size_t)(x))

#ifdef __cplusplus
extern "C" {
#endif 

/** @internal
Free v if not NULL and return NULL but 0 out the string first.
*/
ABR_EXPORT char *abr_freeclr(char *v);

/** @internal
Checks if a file exists.
@param filepath the relative or absolute path to the file.
@return TRUE or FALSE.
*/
ABR_EXPORT bool abr_fileexists(const char *filepath);

/**
If the string is NULL, just return 0.
@param src the string to check
@return Return 0 if the string is NULL, otherwise return the strlen()
*/
ABR_EXPORT size_t abr_strlen(const char *src);

/**
Allocate a string of sufficient size to hold the catanation of the 3 non-NULL strings - caller must free.
If any string is NULL, just ignore it.
@param src1 first string 
@param src2 second string
@param src3 third string
@return a new string
*/
ABR_EXPORT char *abr_strcat(const char *src1, const char *src2, const char *src3);

/**
Allocate a string of sufficient size to hold the catanation of the 4 non-NULL strings - caller must free.
If any string is NULL, just ignore it.
@param src1 first string 
@param src2 second string
@param src3 third string
@param src4 fourth string
@return a new string
*/
ABR_EXPORT char *abr_strcat4(const char *src1, const char *src2, const char *src3, const char *src4);

/**
Allocate a string of sufficient size to hold the duplicate a string plus a padding length - caller must free.
If the string is NULL, just return NULL.
@param src the string to duplicate
@padlen padding length (can be 0)
@return a new string
*/
ABR_EXPORT char *abr_strdup(const char *src, size_t padlen);

/**
Allocate memory size 'len' to hold the duplicate of 'src' plus a padding length - caller must free.
If the string is NULL, just return NULL.
@param src the memory block to duplicate
@len the size of the memory block
@padlen padding length (can be 0)
@return a new memory block
*/
ABR_EXPORT void *abr_memdup(const void *src, size_t len, size_t padlen);

/**

*/
ABR_EXPORT char *abr_pathcat(const char *path1, const char *path2);
ABR_EXPORT time_t abr_str2time(const char *src);
ABR_EXPORT void abr_gmtime(time_t *timep, struct tm *result);
ABR_EXPORT void abr_localtime(time_t *timep, struct tm *result);
ABR_EXPORT size_t abr_strftime_utc(char *buf, size_t sizeinbytes, time_t *timep, bool isUtc); // format="%Y/%m/%d-%H:%M:%S"
ABR_EXPORT char *abr_host(char **buffer, const char *url);
ABR_EXPORT bool abr_isnullorempty(const char *str);
ABR_EXPORT bool abr_isnulloremptyws(const char *str, size_t len);
ABR_EXPORT size_t abr_trim(char *str, size_t len);
ABR_EXPORT char *abr_substitute(char **dst, const char *src, const char *value);
ABR_EXPORT bool abr_streq(const char *src, const char *src2);
ABR_EXPORT bool abr_streqi(const char *src, const char *src2);
ABR_EXPORT bool abr_strstartswith(const char *src, const char *src2);
ABR_EXPORT bool abr_strstartswithi(const char *src, const char *src2);
ABR_EXPORT char *abr_itoa(char *dst, int value);
ABR_EXPORT const char *abr_value(const char *value, const char *defvalue);
ABR_EXPORT const char *abr_valuec(const char *value, const char *defvalue);
ABR_EXPORT int abr_value_int(const char *value, int defvalue);
ABR_EXPORT bool abr_value_bool(const char *value, bool defvalue);
ABR_EXPORT void *abr_value_v(void *value, void *defvalue);

// caller must free returned value if not NULL
ABR_EXPORT char *abr_substr(const char *str, const char *start, const char *end);
ABR_EXPORT char *abr_substrmatch(const char *str, const char *matchstart, const char *matchend);

ABR_EXPORT char *abr_stripouterxml(char *text);

ABR_EXPORT void abr_lf_base64decode(const char *filein, const char *fileout);
ABR_EXPORT void abr_lf_base64encode(const char *filein, const char *fileout);
ABR_EXPORT int abr_lf_generatehmac(const char *filein, const char *fileout);

#ifdef __cplusplus
}
#endif 

/*! @} */

#endif /*__ABR_UTILCORE_PRIVATE_H__*/
