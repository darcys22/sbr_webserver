#ifndef __ABR_LOG_H__
#define __ABR_LOG_H__

/* @addtogroup abrbase_api_public_log

@{
*/

/** @defgroup abrbase_api_public_log_defines Defines
@ingroup abrbase_api_public_log

*/ 

/** @defgroup abrbase_api_public_log_defines_name Name Defines
@ingroup abrbase_api_public_log_defines

Names of loglevels as strings. The first character is unique and can be used to distinguish between them.
This is useful, for example, if passing in on the command line.

@{
*/ 
#define ABR_LOG_OFF_NAME "off" /**< "off" Log level as a string */
#define ABR_LOG_FATAL_NAME "fatal" /**< "fatal" Log level as a string */
#define ABR_LOG_ERR_NAME "err" /**< "err" Log level as a string */
#define ABR_LOG_WARN_NAME "warn" /**< "warn" Log level as a string */
#define ABR_LOG_INFO_NAME "info" /**< "info" Log level as a string */
#define ABR_LOG_DEBUG_NAME "debug" /**< "debug" Log level as a string */
#define ABR_LOG_TRACE_NAME "trace" /**< "trace" Log level as a string */
#define ABR_LOG_ALL_NAME "all" /**< "all" Log level as a string */

/*! @} */

/** @defgroup abrbase_api_public_log_defines_output Output Type
@ingroup abrbase_api_public_log_defines

Character identifying where logging is sent to.

@{
*/

#define ABR_LOG_OUTPUTTYPE_NONE 'n' /**< Configuration entry 'n'one */
#define ABR_LOG_OUTPUTTYPE_STDOUT 'o' /**< Configuration entry 'o'ut (stdout) */
#define ABR_LOG_OUTPUTTYPE_STDERR 'e' /**< Configuration entry 'e'err (stderr) */
#define ABR_LOG_OUTPUTTYPE_PATH 'p' /**< Configuration entry 'p'ath */

/*! @} */

/** @defgroup abrbase_api_public_log_types Types
@ingroup abrbase_api_public_log

@{
*/ 

/**
The log object.
*/
typedef struct _abr_Log abr_Log; 

/**
Indicates whether logging to stdout, stderr, a file, or nothing.
*/
typedef enum { 
	ABR_LOGTO_NULL = 0, /**< Don't log */
	ABR_LOGTO_STDOUT, /**< Log to stdout */
	ABR_LOGTO_STDERR, /**< Log to stderr */
	ABR_LOGTO_FILE /**< Log to a file */
} abr_eLogMode;

/**
Controls the state/type of logging - e.g. header, trailer, or content.
This controls level of indentation if used.
*/
typedef enum { 
	ABR_LOGSTATE_MSG = 0, /**< Just log - usually called within a method */
	ABR_LOGSTATE_OPEN, /**< Log a "header" entry and setup to indent - usually called at method start */
	ABR_LOGSTATE_CLOSE /**< Log a "trailer" entry  and reduce indent - usually called at method end */
} abr_eLogState;

/**
The signature for the logging function - see abr_log_setlogfn()
*/
typedef bool (abr_logfunction)(abr_Log *log, abr_eLoglevel loglevel, abr_eLogState logstate, const char *library, const char *module, const char *function, const char *format, va_list args);

/*! @} */

#ifdef __cplusplus
extern "C" {
#endif 

/** @defgroup abrbase_api_public_log_methods Methods
@ingroup abrbase_api_public_log

@{
*/ 

/**
Override the default logging function.
@param logfunction the custom application log function to use
*/
ABR_EXPORT void abr_log_setlogfn(abr_logfunction logfunction);

/**
Convert the loglevel name to the enum equivalent.
@param c the log level as a string - only first character is significant
@return the loglevel enum
*/
ABR_EXPORT abr_eLoglevel abr_log_name2level(const char *c);

/**
Convert the loglevel enum to the string equivalent.
@param level the log level enum
@return the loglevel string name
*/
ABR_EXPORT const char *abr_log_level2name(abr_eLoglevel level);

/**
The unique id of the logger - typically a guid.
Used to uniquify the logfile name per thread.

@param log the log object
@return logger id
*/
ABR_EXPORT const char *abr_log_id(abr_Log *log);

/**
The output type - 'n'one, 'e'rr (stderr), 'out' (stdout), 'p'ath (dir/file)
@param log the log object
@return output type
*/
ABR_EXPORT const char *abr_log_outputtype(abr_Log *log);

/**
The full path of the file being logged to if abr_log_outputtype() is path.
@param log the log object
@return path
*/
ABR_EXPORT const char *abr_log_path(abr_Log *log);

/**
The full 'unique' path, incorporating abr_log_id(), of the file being logged to if abr_log_outputtype() is path.
This will prefix the id before the file extension, so that logfile.log becomes logfile-id.log.
@param log the log object
@return path incorporating the id
*/
ABR_EXPORT const char *abr_log_upath(abr_Log *log);

/**
Amount to indent each level - defaults to 2
@param log the log object
@return Indent size
*/
ABR_EXPORT size_t abr_log_indentsize(abr_Log *log);

/**
Indent level as determined by nested abr_log_start()/abr_log_end() calls.
@param log the log object
@return Indent level
*/
ABR_EXPORT size_t abr_log_indentlevel(abr_Log *log);

/**
Target loglevel of any log calls within a library/module.
@param library name of library
@param module name of module within library
@return Log level
*/
ABR_EXPORT abr_eLoglevel abr_loglevel(const char *library, const char *module);

/**
Set the loglevel for individual registered libraries/modules.
@code
e.g. 
// Set all registered libraries and modules
abr_setloglevel(NULL, 0, ABR_LOG_WARN); 
// Turn off logging in crypto library
abr_setloglevel(ABR_BASE_LIBRARY, ABR_BASE_MODULEID_CRYPTO, ABR_LOG_OFF); 
@endcode

@param library the library name - NULL indicates all. 
Current known libraries using this SDK are BASE, AKM, STM, CSR. See the relevant \#defines e.g. ABR_BASE_LIBRARY
@param moduleidmask the modules each library registers - 0 indicates all. These allow bitwise or-ing
@param level the loglevel to use
*/
ABR_EXPORT void abr_setloglevel(const char *library, unsigned long moduleidmask, abr_eLoglevel level);

/**
For modules that dump content to files (to aid debugging), check if file dumping is on or off.
@param library name of library
@param module name of module within library
@return TRUE if file dumping is on.
*/
ABR_EXPORT bool abr_logfiledump(const char *library, const char *module);

/**
For modules that dump content to files (to aid debugging), turn file dumping on or off.
This has no affect on modules that do not dump files.
@param library name of library
@param moduleidmask the modules each library registers - 0 indicates all. These allow bitwise or-ing
@param filedump TRUE to turn dumping on.
*/
ABR_EXPORT void abr_setlogfiledump(const char *library, unsigned long moduleidmask, bool filedump);

/**
Log message content (ABR_LOGSTATE_MSG) if current >= target.
@param log the log object
@param target the level the module is set at 
@param current the level of the call
@param library call came from
@param module call came from
@param function call came from
@param format printf() format characters
@param ... parameters
@return TRUE if logging occurred.
*/
ABR_EXPORT bool abr_log_msg(abr_Log *log, abr_eLoglevel target, abr_eLoglevel current, const char *library, const char *module, const char *function, const char *format, ...);

/**
Log message header (ABR_LOGSTATE_OPEN) if current >= target.
@param log the log object
@param target the level the module is set at 
@param current the level of the call
@param library call came from
@param module call came from
@param function call came from
@param format printf() format characters
@param ... parameters
@return TRUE if logging occurred.
*/
ABR_EXPORT bool abr_log_start(abr_Log *log, abr_eLoglevel target, abr_eLoglevel current, const char *library, const char *module, const char *function, const char *format, ...);

/**
Log message trailer (ABR_LOGSTATE_CLOSE) if current >= target.
@param log the log object
@param target the level the module is set at 
@param current the level of the call
@param library call came from
@param module call came from
@param function call came from
@param doindentonly don't actually log anything - just adjust the indent level
@param format printf() format characters
@param ... parameters
@return TRUE if logging occurred.
*/
ABR_EXPORT bool abr_log_end(abr_Log *log, abr_eLoglevel target, abr_eLoglevel current, const char *library, const char *module, const char *function, bool doindentonly, const char *format, ...);

/*! @} */

#ifdef __cplusplus
}
#endif 

#endif /*__ABR_LOG_H__*/

