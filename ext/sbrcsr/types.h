#ifndef __SBR_CSR_TYPES_H__
#define __SBR_CSR_TYPES_H__

#include "sbrcsr/export.h"

/** @addtogroup sbrcsr_api_csr_types

@{
*/

/** 
Indicates whether a message is or object belongs to a request or response message. 
*/
typedef enum {
    SBR_REQUEST = 1, /**< Request message */
    SBR_RESPONSE /**< Response message */
} sbr_eMsgSourceType; 

/** @} */

/** @defgroup sbrcsr_api_csr_types_modules Module defines
@ingroup sbrcsr_api_csr_types
Each module within the library is individually defined by a name and id.
These can be used to target logging for particular modules and to identify the source of errors.
When setting logging, the MODULEID values can be bitwised or-ed (see abr_setloglevel()).

Note that not all modules are neccessarily exposed via a public API, even though they appear here.

@{
*/ 
#define SBR_CSR_LIBRARY           "sbrcsr" /**< The name of the library. */
#define SBR_CSR_MODULE_LIB        "lib" /**< The lib module name. */
#define SBR_CSR_MODULE_ERRFN      "errfn" /**< The errfn module name. */
#define SBR_CSR_MODULE_CSR        "csr" /**< The errfn module name. */
#define SBR_CSR_MODULE_REQUEST    "request" /**< The request module name. */
#define SBR_CSR_MODULE_RESPONSE   "response" /**< The response module name. */
#define SBR_CSR_MODULE_DOC        "doc" /**< The doc module name. */
#define SBR_CSR_MODULE_DOCA       "doca" /**< The doca (attachment) module name. */
#define SBR_CSR_MODULE_MSGEVENT   "msgevent" /**< The msgevent module name. */
#define SBR_CSR_MODULE_MSGTS      "msgts" /**< The msgts (timestamp) module name. */
#define SBR_CSR_MODULE_MSGP       "msgp" /**< The msgp (party) module name. */
#define SBR_CSR_MODULE_MSGREC     "msgrec" /**< The msgrec (receipt) module name. */
#define SBR_CSR_MODULE_SBDM       "sbdm" /**< The sbdm module name. */

#define SBR_CSR_MODULEID_LIB        0x00000001UL /**< The lib module id. */
#define SBR_CSR_MODULEID_ERRFN      0x00000002UL /**< The errfn module id. */
#define SBR_CSR_MODULEID_CSR        0x00000004UL /**< The csr module id. */
#define SBR_CSR_MODULEID_REQUEST    0x00000008UL /**< The request module id. */
#define SBR_CSR_MODULEID_RESPONSE   0x00000010UL /**< The response module id. */
#define SBR_CSR_MODULEID_DOC        0x00000020UL /**< The doc module id. */
#define SBR_CSR_MODULEID_DOCA       0x00000040UL /**< The doca (attachment) module id. */
#define SBR_CSR_MODULEID_MSGEVENT   0x00000080UL /**< The msgevent module id. */
#define SBR_CSR_MODULEID_MSGTS      0x00000100UL /**< The msgts (timestamp) module id. */
#define SBR_CSR_MODULEID_MSGP       0x00000200UL /**< The msgp (party) module id. */
#define SBR_CSR_MODULEID_MSGREC     0x00000400UL /**< The msgrec (receipt) module id. */
#define SBR_CSR_MODULEID_SBDM       0x00000800UL /**< The sbdm module id. */

/**
The SBR_CSR_INIT_... defines are used to control the initialisation that takes place. Currently
only SBR_CSR_INIT_ALL is defined. 
*/
#define SBR_CSR_INIT_ALL 0xffff

/** @} */

#ifdef __cplusplus
extern "C" {
#endif

/** @defgroup sbrcsr_api_csr_types_config Configuration Values
@ingroup sbrcsr_api_csr_types
These values can optionally be used to access variables in the configuration file.

@{
*/ 

/**
This is the configuration variable name for the overall network timeout to use instead of @ref abr_CfgN_Base_Http_Timeout - independent of servicetype.
*/
SBR_CSR_EXPORT_VAR const char sbr_CfgN_Csr_HttpTimeout[];

/**
This is the configuration variable name for the network connect timeout to use instead of @ref abr_CfgN_Base_Http_TimeoutConnect - independent of servicetype.
*/
SBR_CSR_EXPORT_VAR const char sbr_CfgN_Csr_HttpTimeoutConnect[];

/**
This is the configuration variable name for the directory where the template files are - independent of servicetype.
*/
SBR_CSR_EXPORT_VAR const char sbr_CfgN_Csr_Template_Dir[];

/**
This is the configuration variable name for the filename of the template file - independent of servicetype.
*/
SBR_CSR_EXPORT_VAR const char sbr_CfgN_Csr_Template_File[];

/**
This is the configuration variable name for the URL of the CSR service - specific to servicetype.

Because this is specific to a service type, use the abr_ctx_itemid() method instead of abr_ctx_item(). In this
case the "id" is the "servicetype".
*/
SBR_CSR_EXPORT_VAR const char sbr_CfgN_Csr_ServiceType_Url[];

/**
This is the configuration variable name for the ServiceName - specific to servicetype.

Because this is specific to a service type, use the abr_ctx_itemid() method instead of abr_ctx_item(). In this
case the "id" is the "servicetype".
*/
SBR_CSR_EXPORT_VAR const char sbr_CfgN_Csr_ServiceType_Template_ServiceName[];

/**
This is the configuration variable name for the ServiceNamespace - specific to servicetype.

Because this is specific to a service type, use the abr_ctx_itemid() method instead of abr_ctx_item(). In this
case the "id" is the "servicetype".
*/
SBR_CSR_EXPORT_VAR const char sbr_CfgN_Csr_ServiceType_Template_ServiceNamespace[];

/**
This is the optional configuration variable name for the template filename which overrides @ref sbr_CfgN_Csr_Template_File[] - specific to servicetype.

Because this is specific to a service type, use the abr_ctx_itemid() method instead of abr_ctx_item(). In this
case the "id" is the "servicetype".
*/
SBR_CSR_EXPORT_VAR const char sbr_CfgN_Csr_ServiceType_Template_File[];

/** @} */

#ifdef __cplusplus
}
#endif 

/** @defgroup sbrcsr_api_csr_types_errcodes Error codes
@ingroup sbrcsr_api_csr_types
All errors are encapsulated in CSR specific errors. 
For the underlying error, use abr_err_inner() to retrieve nested errors and their details.
For SOAP related errors see @ref abr_ErrSoap.

@{
*/ 

#define SBR_CSR_ERR_MIN 14000 /**< The mimimum error number. */
#define SBR_CSR_ERR_GENERAL (SBR_CSR_ERR_MIN+1)  /**< For errors not specified below. */
#define SBR_CSR_ERR_NETSENDER (SBR_CSR_ERR_MIN+2) /**< A SOAP fault generated by the sender, not including service unavailable. */
#define SBR_CSR_ERR_NETRECEIVER (SBR_CSR_ERR_MIN+3) /**< A SOAP fault generated by the receiver, not including service unavailable. */
#define SBR_CSR_ERR_NETUNAVAILABLE (SBR_CSR_ERR_MIN+4) /**< A SOAP fault where the remote service is unavailable. */
#define SBR_CSR_ERR_NETCOMMS (SBR_CSR_ERR_MIN+5) /**< A general network error has occurred, not including timeouts. */
#define SBR_CSR_ERR_NETTIMEOUT (SBR_CSR_ERR_MIN+6)  /**< A network time has occured trying to connect to a remote service. */
#define SBR_CSR_ERR_MAX (SBR_CSR_ERR_MIN+200) /**< The maximum error number. */

/** @} */

#endif /*__SBR_CSR_TYPES_H__*/
