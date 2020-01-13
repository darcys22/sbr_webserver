#ifndef __ABR_STM_LIB_H__
#define __ABR_STM_LIB_H__

/** @addtogroup abrstm_api_lib

@{
*/

#ifdef __cplusplus
extern "C" {
#endif 

/**
Return the version of the ABR Security Token Manager API. 
@return version in the form major.minor.patch.tweak (not all levels may be present)
*/
ABR_STM_EXPORT const char *abr_stm_version(void);

/**
Initialise the SDK. 

This must be called at application startup prior to any threads being started.

abr_base_init() must be called first.

@param ctx the current thread local Context.
@param flag used to control the initialisation process - use ABR_STM_INIT_ALL unless advised otherwise.

@return ABR_ERR_OK or an errcode.
*/
ABR_STM_EXPORT int abr_stm_init(abr_Ctx *ctx, unsigned short flag);
/**
Deinitialise the SDK. This must be called at application shutdown after threads are finished and 
any allocated objects freed.

abr_base_deinit() should be called after all other deinitialisation routines are called.
*/
ABR_STM_EXPORT void abr_stm_deinit(void);

/**
The default directory/folder for the template files. 
- Windows
	- %LOCALAPPDATA%/abrstm (Vista and above) or, if environment variable not found, 
	- %APPDATA%/abrstm or, if environment variable not found, 
	- c:/abrstm
- Mac
	- /Library/Application Support/abrstm
- Unix
	- /etc/abrstm

@return the default home folder.
*/
ABR_STM_EXPORT const char *abr_stm_default_templatedir(void);

/**
The default filename for the STM template file.

@return the default STM template filename.
*/
ABR_STM_EXPORT const char *abr_stm_default_templatefile(void);

/**
The default full path for the STM template file - see abr_stm_default_templatedir() and abr_stm_default_templatefile().

@return the default STM template path.
*/
ABR_STM_EXPORT const char *abr_stm_default_templatepath(void);

/**
The prefix to use when searching for resource files - see abr_stm_loadtemplate().

If dirname is NULL in the parameter to abr_stm_loadtemplate() AND no config value is set, then
"prefix/abr_stm_default_templatedir()/filename" is used as the full path. If prefix is not set, then
the file is searched for in default locations depending on the OS. First the "current dir" is checked for
the file - prefix is ".". Then on Windows prefix is %LOCALAPPDATA% or %APPDATA%; 
on Unix it is /usr/local and /usr; on MAC it is "" (nothing).

@return the prefix.
*/
ABR_STM_EXPORT const char *abr_stm_installprefix(void);

/**
Set the directory prefix to use when searching - see abr_stm_loadtemplate().

@param installprefix the prefix to use.
*/
ABR_STM_EXPORT void abr_stm_setinstallprefix(const char *installprefix);

/**
Helper method to load an STM template from a path.

@param ctx the current thread local Context.
@param buffer the address of the buffer to load the contents into - must be freed by the caller.
@param dirname the directory to use. 
If NULL: use the value specified in the current configuration or if none, search for the file using abr_stm_installprefix().
@param filename the filename to use. 
If NULL: use the value specified in the current configuration or if none, use abr_stm_default_templatefile().

@return ABR_ERR_OK or an errcode.
*/
ABR_STM_EXPORT int abr_stm_loadtemplate(abr_Ctx *ctx, char **buffer, const char *dirname, const char *filename);

#ifdef __cplusplus
}
#endif 

/*! @} */

#endif /*__ABR_STM_LIB_H__*/
