#ifndef __ABR_CTX_H__
#define __ABR_CTX_H__

#include <stddef.h>

/** @addtogroup abrbase_api_public_ctx

@{
*/

#ifdef __cplusplus
extern "C" {
#endif 

/**
Create a context object for thread local storage - use abr_ctx_free() to free.

At least one object should be created per thread.
This call creates a context object with no associated configuration (or logging) object - use 
abr_ctx_attachcfg() to associate a configuration object in a seperate step. This is primarily used 
to create the first context object on the main thread prior to initialisation. It allows error information
to be propagated during the initialisation phase. abr_ctx_attachcfg() is then used after a configuration 
manager has been created.
@verbatim
	abr_ctx_create(&global_ctx);
	initialisation code ...
	abr_cfgmgr_create(&global_cfgmgr, ...);
	abr_ctx_attachcfg(global_ctx, global_cfgmgr, context_to_use);
@endverbatim

See also abr_ctx_createcfg().

@param ctx the address of the context object to create.
*/
ABR_EXPORT void abr_ctx_create(abr_Ctx **ctx);

/**
Attach a configuration object to an existing context. This is usually used in conjunction with abr_ctx_create();

@param ctx the context object
@param mgr the configuration manager to associate with the context
@param cfgid the configuration (in the config manager) to associate with the context

@return ABR_ERR_OK or an error code - see abr_ctx_err() for any error details
*/
ABR_EXPORT int abr_ctx_attachcfg(abr_Ctx *ctx, abr_CfgMgr *mgr, const char *cfgid);

/**
Create a context object for thread local storage - use abr_ctx_free() to free. 
See abr_ctx_create() and abr_ctx_attachcfg() for details. 
This method is used per additional thread.
@verbatim
	abr_ctx_createcfg(&thread_ctx, global_cfgmgr, context_to_use);
@endverbatim

@param ctx the address of the context object to create
@param mgr the configuration manager to associate with the context
@param cfgid the configuration (in the config manager) to associate with the context

@return ABR_ERR_OK or an error code - see abr_ctx_err() for any error details
*/
ABR_EXPORT int abr_ctx_createcfg(abr_Ctx **ctx, abr_CfgMgr *mgr, const char *cfgid);

/**
Free the context object. This should be done AFTER freeing all other objects bug PRIOR to freeing the 
configuration manager.

@param ctx the context object
*/
ABR_EXPORT void abr_ctx_free(abr_Ctx *ctx);

/**
Get the logger associated with the current context.

@param ctx the context.

@return the logger or NULL if none has been initialised. 
*/
ABR_EXPORT abr_Log *abr_ctx_log(abr_Ctx *ctx);

/**
Get the error object associated with the current context, if any.

@param ctx the context.

@return the error object or NULL if no error. 
*/
ABR_EXPORT abr_Err *abr_ctx_err(abr_Ctx *ctx);

/**
Get the configuration object associated with the current context, if any.

@param ctx the context or NULL.

@return the configuration object or NULL if none has been initialised. 
*/
ABR_EXPORT abr_Cfg *abr_ctx_cfg(abr_Ctx *ctx);

/**
Create a configuration item used to retrieve attributes and values. This is guaranteed to
return a value or assert (e.g. out of memory). This can then be used to 
retrieve an configuration setting/item/node for the given name and id (XPath) expression.
If "id" is not null, the XPath expression is expected to contain a "$" character, for which
the value of "id" is substituted
@verbatim
For example:
In 
	name="abr:MySetting/[@xml:id=\"$\"]/abr:MySubSetting"
If
	id="one"
results in 
	name="abr:MySetting/[@xml:id="one"]/abr:MySubSetting"
@endverbatim

@param ctx the context.
@param id substitute for "$" in name.
@param name the XPath representing the setting name - blank returns the root configuration node.

@return a configuration item to use to retrieve information.
*/
ABR_EXPORT abr_CfgItem *abr_ctx_itemid(abr_Ctx *ctx, const char *id, const char *name);

/**
Create a configuration item used to retrieve attributes and values - see also abr_ctx_itemid(). 
This is guaranteed to return a value or assert (e.g. out of memory). This can then be used to 
retrieve an configuration setting/item/node for the given name and id (XPath) expression.

@param ctx the context.
@param name the XPath representing the setting name - blank returns the root configuration node.

@return a configuration item to use to retrieve information.
*/
ABR_EXPORT abr_CfgItem *abr_ctx_item(abr_Ctx *ctx, const char *name);

#ifdef __cplusplus
}
#endif 

/*! @} */

#endif /*__ABR_CTX_H__*/
