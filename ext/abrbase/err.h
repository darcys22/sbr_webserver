#ifndef __ABR_ERR_H__
#define __ABR_ERR_H__

/** @addtogroup abrbase_api_public_errgen 

Error objects are created and attached to the current Context object, if an error occurs. 
Errors can be nested - see abr_err_inner().

For a general description see @ref abrbase_error_overview.

@{
*/

/**
The Error type.
*/
typedef struct _abr_Err abr_Err;

/**
The severity of the error
*/
typedef enum { 
	ABR_ESEVERITY_FATAL, /**< the application may halt immediately, if not it should exit ASAP */
	ABR_ESEVERITY_ERR, /**< the application should go into recovery mode (e.g. restoring connections) */
	ABR_ESEVERITY_WARN /**< business or user level error such as invalid password, so try again */
} abr_eErrSeverity;

#ifdef __cplusplus
extern "C" {
#endif 

/**
Convenience method - FALSE if ABR_ERR_OK.
@param err error object
@return TRUE or FALSE
*/
ABR_EXPORT bool abr_err_iserror(abr_Err *err);

/**
Get the error code.
@param err error object
@return the error code
*/
ABR_EXPORT int abr_err_code(abr_Err *err);

/**
Get the error code name as as string.
@param err error object
@return the error code name e.g. "ABR_ERR_OK" is the name for code 0.
*/
ABR_EXPORT const char *abr_err_codename(abr_Err *err);

/**
Get the stock message defined for the given error code.
@param err error object
@return the error code message
*/
ABR_EXPORT const char *abr_err_codemsg(abr_Err *err);

/**
Get the severity.
@param err error object
@return the severity
*/
ABR_EXPORT abr_eErrSeverity abr_err_severity(abr_Err *err);

/**
Get the library (string) where the error was created.
@param err error object
@return library name
*/
ABR_EXPORT const char *abr_err_library(abr_Err *err);

/**
Get the module (file) where the error was created.
@param err error object
@return module name
*/
ABR_EXPORT const char *abr_err_module(abr_Err *err);

/**
Get the function where the error was created.
@param err error object
@return function name
*/
ABR_EXPORT const char *abr_err_function(abr_Err *err);

/**
Get the line where the error was created.
@param err error object
@return line number
*/
ABR_EXPORT int abr_err_line(abr_Err *err);

/**
Get the message attached to the error.
@param err error object
@return message
*/
ABR_EXPORT const char *abr_err_msg(abr_Err *err);

/**
Get the nested/inner error object if any.
@param err error object
@return inner error
*/
ABR_EXPORT abr_Err *abr_err_inner(abr_Err *err);

/**
Get the custom object if any.
@param err error object
@return custom object
*/
ABR_EXPORT void *abr_err_custom(abr_Err *err);

#ifdef __cplusplus
}
#endif 


/*! @} */

#endif /*__ABR_ERR_H__*/
