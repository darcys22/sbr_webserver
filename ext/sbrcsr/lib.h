#ifndef __SBR_CSR_LIB_H__
#define __SBR_CSR_LIB_H__

/** @addtogroup sbrcsr_api_csr_lib

@{
*/

#ifdef __cplusplus
extern "C" {
#endif 

/**
Return the version of the SBR Core Services Requester API.
@return version in the form major.minor.patch.tweak (not all levels may be present)
*/
SBR_CSR_EXPORT const char *sbr_csr_version(void);

/**
Initialise the SDK. 

This must be called at application startup prior to any threads being started.

abr_base_init() must be called first.

@param ctx the current thread local Context.
@param flag used to control the initialisation process - use SBR_CSR_INIT_ALL unless advised otherwise.

@return ABR_ERR_OK or an errcode.
*/
SBR_CSR_EXPORT int sbr_csr_init(abr_Ctx *ctx, unsigned short flag);
/**
Deinitialise the SDK. This must be called at application shutdown after threads are finished and 
any allocated objects freed.

abr_base_deinit() should be called after all other deinitialisation routines are called.
*/
SBR_CSR_EXPORT void sbr_csr_deinit(void);

/**
The default directory/folder for the template files. 
- Windows
	- %LOCALAPPDATA%/sbrcsr (Vista and above) or, if environment variable not found, 
	- %APPDATA%/sbrcsr or, if environment variable not found, 
	- c:/sbrcsr
- Mac
	- /Library/Application Support/sbrcsr
- Unix
	- /etc/sbrcsr
	
@return the default home folder.
*/
SBR_CSR_EXPORT const char *sbr_csr_default_templatedir(void);

/**
The default filename for the CSR template file.

@return the default CSR template filename.
*/
SBR_CSR_EXPORT const char *sbr_csr_default_templatefile(void);

/**
The default full path for the CSR template file - see sbr_csr_default_templatedir() and sbr_csr_default_templatefile().

@return the default CSR template full path.
*/
SBR_CSR_EXPORT const char *sbr_csr_default_templatepath(void);

/**
The prefix to use when searching for resource files - see sbr_csr_loadtemplate().

If dirname is NULL in the parameter to abr_stm_loadtemplate() AND no config value is set, then
"prefix/sbr_csr_default_templatedir()/filename" is used as the full path. If prefix is not set, then
the file is searched for in default locations depending on the OS. First the "current dir" is checked for
the file - prefix is ".". Then on Windows prefix is %LOCALAPPDATA% or %APPDATA%; 
on Unix it is /usr/local and /usr; on MAC it is "" (nothing).

@return the prefix.
*/
SBR_CSR_EXPORT const char *sbr_csr_installprefix(void);

/**
Set the directory prefix to use when searching - see sbr_csr_loadtemplate().

@param installprefix the prefix to use.
*/
SBR_CSR_EXPORT void sbr_csr_setinstallprefix(const char *installprefix);

/**
Helper method to load an CSR template from a path.

@param ctx the current thread local Context.
@param buffer the address of the buffer to load the contents into - must be freed by the caller.
@param servicetype the id value used to index a given configuration subset with the CSR conguration.
@param dirname the directory to use. 
If NULL, use the value specified in the current configuration or if none, search for the file using sbr_csr_installprefix().
@param filename the filename to use. 
If NULL, use the value specified in the current configuration or if none, use sbr_csr_default_templatefile().

@return ABR_ERR_OK or an errcode.
*/
SBR_CSR_EXPORT int sbr_csr_loadtemplate(abr_Ctx *ctx, char **buffer, const char *servicetype, const char *dirname, const char *filename);


SBR_CSR_EXPORT const char *sbr_msgsourcetypestr(sbr_eMsgSourceType msgsrctype);

#ifdef __cplusplus
}
#endif 

/*! @} */

#endif /*__SBR_CSR_LIB_H__*/
