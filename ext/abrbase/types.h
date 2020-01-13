#ifndef __ABR_TYPES_H__
#define __ABR_TYPES_H__

#if defined(_WIN32) || defined(_WIN64)
#define ABR_WINXX
#endif

#if defined(_WIN32)
	#define PRINTF_SIZET ""
#elif defined(_WIN64)
	#define PRINTF_SIZET "I"
#else
	#define PRINTF_SIZET "z"
#endif
// e.g 		[size_t size = 0; printf("%" PRINTF_SIZET "u", size);]
// instead of [size_t size = 0; printf("%zu", size);] which is not portable (i.e. to MSVC)


#if defined(ABR_WINXX)
//#define DEBUG_VISUAL_LEAK_DETECTOR
#ifdef DEBUG_VISUAL_LEAK_DETECTOR
//Used to detect memory leaks in Visual Studio environments: http://vld.codeplex.com/
//To work with the existing project files, install Visual Leak Detector to the default location 
//(C:\Program Files\Visual Leak Detector).
//Note: this is set to only detect leaks within DLLs using this. If a dependent DLL allocates memory
//on behalf of a client DLL/application but the client DLL/app does not release it, this will
//not be detected. Also memory corruptions may destabalise VLD.
//For a more robust analysis a comprehensive tool such Valgrind on Linux/Ubuntu is strongly recommended.
//Note2: on Windows do not directly release memory in a client DLL/app that has been allocated within
//a dependent DLL. Instead call a relevant free method provided by the dependent DLL (if one is not 
//provided, don't use the method and/or the DLL that cause the allocation).
//For more information see http://msdn.microsoft.com/en-us/library/ms235460.aspx.
#include <vld.h>
#endif
#endif

#include "abrbase/export.h"

#if defined(_WIN32) || defined(_WIN64)
// We need to cast to non-const due to BUG in MSVC.
// See http://connect.microsoft.com/VisualStudio/feedback/details/101661/warning-c4090-is-incorrectly-issued-when-using-visual-c-net-2003
#define BADCAST2NC_MSVSBUG_C4090 (void *)
#else
#define BADCAST2NC_MSVSBUG_C4090
#endif
#define ABR_BADCAST2NC BADCAST2NC_MSVSBUG_C4090

#ifndef FALSE
#define FALSE 0
#endif
#ifndef TRUE
#define TRUE (!FALSE)
#endif
#ifndef __cplusplus
#ifndef bool
typedef int bool;
#endif
#endif

/** @addtogroup abrbase_api_public_types

@{
*/

/**
Parameter semantics when passing information to some API methods
*/
typedef enum { 
	ABR_PARAMACTION_DEFAULT = 0,  /**< Action is up to individual method */
	ABR_PARAMACTION_COPY, /**< Take a deep copy of the parameter */
	ABR_PARAMACTION_CONST,  /**< Reference the parameter but treat as const so don't free */
	ABR_PARAMACTION_FREE  /**< Reference the parameter but take on ownership so free when finished with it */
} abr_eParamAction;

/**
Loglevels
*/
typedef enum { 
	ABR_LOG_OFF = 1,  /**< Do not log */
	ABR_LOG_FATAL, /**< Typically this will be an assertion for invalid arguments or out of memory */
	ABR_LOG_ERR,  /**< An infrastructure type <i>error</i> has occured, such as a network error or no configuration */
	ABR_LOG_WARN, /**< Usually a business level <i>error</i> such as wrong password */
	ABR_LOG_INFO, /**< Information usually indicating a method succeeded */
	ABR_LOG_DEBUG, /**< Additional information, useful where <i>errors</i> have occurred */
	ABR_LOG_TRACE, /**< Trace the entry and exit calls of methods (exits do not occur on <i>errors</i>) */
	ABR_LOG_ALL /**< Log everything */
} abr_eLoglevel;


/**
The thread local context object
*/
typedef struct _abr_Ctx abr_Ctx;

/** @} */

/** @defgroup abrbase_api_public_types_modules Module defines
@ingroup abrbase_api_public_types
Each module within the library is individually defined by a name and id.
These can be used to target logging for particular modules and to identify the source of errors.
When setting logging, the MODULEID values can be bitwised or-ed (see abr_setloglevel()).

Note that not all modules are neccessarily exposed via a public API, even though they appear here.
@{
*/ 
#define ABR_BASE_LIBRARY "abrbase" /**< The name of the library. */

#define ABR_BASE_MODULE_LIB "lib" /**< The lib module name. */
#define ABR_BASE_MODULE_ERRDEF "errdef" /**< The errdef module name. */
#define ABR_BASE_MODULE_ERR "err" /**< The error module name. */
#define ABR_BASE_MODULE_NET "net" /**< The network module name. */
#define ABR_BASE_MODULE_XML "xml" /**< The xml module name. */
#define ABR_BASE_MODULE_CTX "ctx" /**< The ctx module name. */
#define ABR_BASE_MODULE_LOG "log" /**< The log module name. */
#define ABR_BASE_MODULE_UTIL "util" /**< The util module name. */
#define ABR_BASE_MODULE_LST "lst" /**< The lst (container) module name. */
#define ABR_BASE_MODULE_STR "str" /**< The str module name. */
#define ABR_BASE_MODULE_CRYPTO "crypto" /**< The crypto module name. */
#define ABR_BASE_MODULE_ERRFN "errfn" /**< The errfn module name. */
#define ABR_BASE_MODULE_CFG "cfg" /**< The cfg module name. */
#define ABR_BASE_MODULE_ITER "iter" /**< The iter module name. */
#define ABR_BASE_MODULE_ERRSOAP "errsoap" /**< The errsoap module name. */
#define ABR_BASE_MODULE_NETD "netdata" /**< The netdata module name. */
#define ABR_BASE_MODULE_SI "si" /**< The softwareinfo module name. */
#define ABR_BASE_MODULE_PBE "pbe" /**< The PasswordBasedEncryption support module. */
#define ABR_BASE_MODULE_PK "pk" /**< The pwd/kdf support module. */

#define ABR_BASE_MODULEID_LIB     0x00000001UL /**< The lib module id. */
#define ABR_BASE_MODULEID_ERRDEF  0x00000002UL /**< The errdef module id. */
#define ABR_BASE_MODULEID_ERR     0x00000004UL /**< The error module id. */
#define ABR_BASE_MODULEID_NET     0x00000008UL /**< The network module id. */
#define ABR_BASE_MODULEID_XML     0x00000010UL /**< The xml module id. */
#define ABR_BASE_MODULEID_CTX     0x00000020UL /**< The ctx module id. */
#define ABR_BASE_MODULEID_LOG     0x00000040UL /**< The log module id. */
#define ABR_BASE_MODULEID_UTIL    0x00000080UL /**< The util module id. */
#define ABR_BASE_MODULEID_LST     0x00000100UL /**< The lst (container) module id. */
#define ABR_BASE_MODULEID_STR     0x00000200UL /**< The str module id. */
#define ABR_BASE_MODULEID_CRYPTO  0x00000400UL /**< The crypto module id. */
#define ABR_BASE_MODULEID_ERRFN   0x00000800UL /**< The errfn module id. */
#define ABR_BASE_MODULEID_CFG     0x00001000UL /**< The cfg module id. */
#define ABR_BASE_MODULEID_ITER    0x00002000UL /**< The iter module id. */
#define ABR_BASE_MODULEID_ERRSOAP 0x00004000UL /**< The errsoap module id. */
#define ABR_BASE_MODULEID_NETD    0x00008000UL /**< The netdata module id. */
#define ABR_BASE_MODULEID_SI      0x00010000UL /**< The softwareinfo module id. */
#define ABR_BASE_MODULEID_PBE     0x00020000UL /**< The PasswordBasedEncryption support module id. */
#define ABR_BASE_MODULEID_PK      0x00040000UL /**< The pwd/kdf support module id. */

/** @} */

/** @defgroup abrbase_api_public_types_otherdefines Other defines
@ingroup abrbase_api_public_types
@{
*/

/**
The ABR_BASE_INIT_... defines are used to control the initialisation that takes place. 

Currently only ABR_BASE_INIT_ALL is defined. 
*/
#define ABR_BASE_INIT_ALL 0xffff

/**
Ignore unused arguments in a function. 

Useful during development or for placeholder arguments.
*/
#define ABR_IGNORE(v) ((void) &(v))

/** @} */

#ifdef __cplusplus
extern "C" {
#endif 

/** @defgroup abrbase_api_public_types_config Configuration Values
@ingroup abrbase_api_public_types
These consts can be used to access data stored in the configuration file - see @ref abrbase_api_public_cfg.

The abr_CfgN_.. consts refer to the name of configuration items - all data for an item is held in its attributes.

The abr_CfgA_.. consts refer to the name of attributes for the given configuration item. 
These attributes can apply to any configuration item, although not all are used by a given item. 

For more details on individual items, see the ..-desc.xml file in "resources".
@{
*/ 

/**
The "@ref" attribute associated with a configuration node (@ref abr_Cfg).
*/
ABR_EXPORT_VAR const char abr_CfgA_ref[];

/**
The "@readonly" attribute for the configuration item (@ref abr_CfgItem) - see also abr_cfgi_isreadonly().
*/
ABR_EXPORT_VAR const char abr_CfgA_readonly[];

/**
The "@description" attribute for the configuration item (@ref abr_CfgItem).
*/
ABR_EXPORT_VAR const char abr_CfgA_description[];

/**
The "@type" attribute for the configuration item (@ref abr_CfgItem).
*/
ABR_EXPORT_VAR const char abr_CfgA_type[];

/**
The "@value" attribute for the configuration item (@ref abr_CfgItem).

This is the default attribute used when NULL is passed to methods such as abr_cfgi_str().
*/
ABR_EXPORT_VAR const char abr_CfgA_value[];

ABR_EXPORT_VAR const char abr_CfgN_Base_Logger[]; /**< The root logger item - see the subnodes. */
ABR_EXPORT_VAR const char abr_CfgN_Base_Logger_DefaultLevel[]; /**< The default log level to use - if not specified the hard coded value ABR_LOG_WARN is used. */
ABR_EXPORT_VAR const char abr_CfgN_Base_Logger_Indent[]; /**< The amount to indent log lines within nested calls - probably not much use in multithreaded scenarious. */
ABR_EXPORT_VAR const char abr_CfgN_Base_Logger_Output[]; /**< Where to send the log output. */
ABR_EXPORT_VAR const char abr_CfgN_Base_Http[]; /**< The root http - see the subnodes. */
ABR_EXPORT_VAR const char abr_CfgN_Base_Http_SSLIgnoreCertificateErrors[]; /**< For testing environments only (or warn the user) - ignore SSL certificate errors. */
ABR_EXPORT_VAR const char abr_CfgN_Base_Http_Timeout[]; /**< The default total network timeout to use to any remote service - including connect and read/write. */
ABR_EXPORT_VAR const char abr_CfgN_Base_Http_TimeoutConnect[]; /**< The default connect only network timeout to use to any remote service. */
ABR_EXPORT_VAR const char abr_CfgN_Base_Http_Proxy[]; /**< The root http proxy - see the subnodes. */
ABR_EXPORT_VAR const char abr_CfgN_Base_Http_Proxy_Url[]; /**< The proxy url. */
ABR_EXPORT_VAR const char abr_CfgN_Base_Http_Proxy_Bypass[]; /**< The proxy bypass list. */
ABR_EXPORT_VAR const char abr_CfgN_Base_Http_Proxy_User[]; /**< The root http proxy user - see the subnodes. */
ABR_EXPORT_VAR const char abr_CfgN_Base_Http_Proxy_User_Domain[]; /**< the user's domain. */
ABR_EXPORT_VAR const char abr_CfgN_Base_Http_Proxy_User_Name[]; /**< the user's account name. */
ABR_EXPORT_VAR const char abr_CfgN_Base_Http_Proxy_User_Password[]; /**< the user's password. */
ABR_EXPORT_VAR const char abr_CfgN_Base_Http_Proxy_AuthType[]; /**< The type of authentication to use with the proxy. */

/** @} */

#ifdef __cplusplus
}
#endif 

/** @defgroup abrbase_api_public_types_errcodes Error codes
@ingroup abrbase_api_public_types
Use abr_err_inner() to retrieve nested errors and their details.
For SOAP related errors see @ref abr_ErrSoap.

@{
*/

#define ABR_ERR_OK 0 /**< No error. */
#define ABR_ERR_MIN 11000 /**< The mimimum error number. */
#define ABR_ERR_UNKNOWN ABR_ERR_MIN /**< Unknown error - catch-all or unanticipated error not covered by other error codes. */
#define ABR_ERR_CFGNOMGR (ABR_ERR_MIN+1) /**< No configuration manager has been set.   */
#define ABR_ERR_MEMORY (ABR_ERR_MIN+2) /**< Memory allocaton error - currently this results in an assert. */
#define ABR_ERR_CFGNOTFOUND (ABR_ERR_MIN+3) /**< Configuration setting not found. */
#define ABR_ERR_INIT (ABR_ERR_MIN+4) /**< Failing to initialise library. */
#define ABR_ERR_VERSION (ABR_ERR_MIN+5) /**< Version mismatch between client and library. */
#define ABR_ERR_VERSION_DEP (ABR_ERR_MIN+6) /**< Version mismatch with dependant library. */
#define ABR_ERR_B64 (ABR_ERR_MIN+7) /**< Failed to decode from or encode to base64. */
#define ABR_ERR_NET (ABR_ERR_MIN+8) /**< Network communication error. */
#define ABR_ERR_FILEOPEN (ABR_ERR_MIN+9) /**< Cannot open file. */
#define ABR_ERR_FILESTAT (ABR_ERR_MIN+10) /**< Cannot determine file size. */
#define ABR_ERR_FILEREAD (ABR_ERR_MIN+11) /**< Cannot read file */
#define ABR_ERR_FILEWRITE (ABR_ERR_MIN+12) /**< Cannot write file */
#define ABR_ERR_P7 (ABR_ERR_MIN+13) /**< Failed to access P7 (certificate). */
#define ABR_ERR_P8 (ABR_ERR_MIN+14) /**< Failed to access P8 (private key). */
#define ABR_ERR_DER (ABR_ERR_MIN+15) /**< Failed to DER encode value. */
#define ABR_ERR_DUPLICATE_ERRDEF (ABR_ERR_MIN+16) /**< Internal/SDK error - duplicate error definition entry detected. */
#define ABR_ERR_DUPLICATE_ERRHANDLER (ABR_ERR_MIN+17) /**< Failed to add error handler for SDK - possible duplicate. */
#define ABR_ERR_XMLPARSE (ABR_ERR_MIN+18) /**< Invalid XML. */
#define ABR_ERR_XMLROOT (ABR_ERR_MIN+19) /**< Failed to find or load root node. */
#define ABR_ERR_CFGDUPLICATE (ABR_ERR_MIN+20) /**< Possible duplicate confuration entry. */
#define ABR_ERR_XMLNODENOTFOUND (ABR_ERR_MIN+21) /**< Failed to find or load expected XML node. */
#define ABR_ERR_NET_TIMEOUT (ABR_ERR_MIN+22) /**< Network timeout connected to remote services. */
#define ABR_ERR_XML (ABR_ERR_MIN+23) /**< Error processing XML. */
#define ABR_ERR_NET_SOAP (ABR_ERR_MIN+24) /**< Network SOAP error returned by remote client. */
#define ABR_ERR_HASH (ABR_ERR_MIN+25) /**< Failed to generate crytographic hash. */
#define ABR_ERR_XMLXPCONTEXT (ABR_ERR_MIN+26) /**< Failed to set XML Xpath context. */
#define ABR_ERR_INVALIDSOFTWAREINFO (ABR_ERR_MIN+27) /**< Invalid or missing Software Info. */
#define ABR_ERR_CRYPTO (ABR_ERR_MIN+28) /**< General error from crypto routines - see message. */
#define ABR_ERR_SDK_EXPIRED (ABR_ERR_MIN+29) /**< SDK expiry date has been reached; please get an updated SDK. */
#define ABR_ERR_MAX (ABR_ERR_MIN+300) /**< The maximum error number. */

/*! @} */

#endif /*__ABR_TYPES_H__*/
