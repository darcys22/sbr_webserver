#ifndef __ABR_AKM_LIB_H__
#define __ABR_AKM_LIB_H__

/** @addtogroup abrakm_api_lib

@{
*/

#ifdef __cplusplus
extern "C" {
#endif 

/**
Return the version of the AUSkey Manager API.
@return version in the form major.minor.patch.tweak (not all levels may be present)
*/
ABR_AKM_EXPORT const char *abr_akm_version(void);

/**
Initialise the SDK. This must be called at application startup prior to any threads being started.

abr_base_init() must be called first.

@param ctx the current thread local Context.
@param flag used to control the initialisation process - use ABR_AKM_INIT_ALL unless advised otherwise.

@return ABR_ERR_OK
*/
ABR_AKM_EXPORT int abr_akm_init(abr_Ctx *ctx, unsigned short flag);
/**
Deinitialise the SDK. This must be called at application shutdown after threads are finished and 
any allocated objects freed.

abr_base_deinit() should be called after all other deinitialisation routines are called.
*/
ABR_AKM_EXPORT void abr_akm_deinit(void);

/**
The default directory/folder for the keystore. This is the user's home, platform/OS specific, folder.
@return the default home keystore folder.
*/
ABR_AKM_EXPORT const char *abr_akm_default_dir(void);

/**
The default keystore filename.
@return the default keystore filename.
*/
ABR_AKM_EXPORT const char *abr_akm_default_ksfile(void);

/**
The full path for the default keystore including the default filename.
@return the default keystore path.
*/
ABR_AKM_EXPORT const char *abr_akm_default_kspath(void);

/**
Convenience method to load a keystore from the give path "dirname/filename" into a buffer - caller must free.

If dirname and/or abr_akm_default_ksfile() are NULL then try to discover the default values from the 
config file else use the hard coded values provided by abr_akm_default_dir()/abr_akm_default_ksfile().

@param ctx the current thread local Context.
@param buffer the address of the buffer that is allocated if successful.
@param dirname the directory to load from
@param filename the keystore filename to load

@return ABR_ERR_OK if successful or error.
*/
ABR_AKM_EXPORT int abr_akm_loadks(abr_Ctx *ctx, char **buffer, const char *dirname, const char *filename);

/**
Convenience method to save a keystore buffer to the give path "dirname/filename".

If dirname and/or abr_akm_default_ksfile() are NULL then try to discover the default values from the 
config file else use the hard coded values provided by abr_akm_default_dir()/abr_akm_default_ksfile().

@param ctx the current thread local Context.
@param buffer the buffer containing the raw keystore XML.
@param dirname the directory to save to
@param filename the keystore filename to save

@return ABR_ERR_OK if successful or error.
*/
ABR_AKM_EXPORT int abr_akm_saveks(abr_Ctx *ctx, const char *buffer, const char *dirname, const char *filename);

#ifdef __cplusplus
}
#endif 

/*! @} */

#endif /*__ABR_AKM_LIB_H__*/
