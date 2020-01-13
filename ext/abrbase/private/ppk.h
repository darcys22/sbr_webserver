#ifndef __ABR_PK_PRIVATE_H__
#define __ABR_PK_PRIVATE_H__

typedef struct _abr_PwdKdf abr_PwdKdf;

#ifdef __cplusplus
extern "C" {
#endif 

ABR_EXPORT abr_PwdKdf *abr_pk_create(abr_Ctx *ctx, abr_PwdKdf **obj, const char *pwd, const char *salt, const abr_Pbe *pbe);
ABR_EXPORT void *abr_pk_free(abr_PwdKdf *pk);

ABR_EXPORT const char *abr_pk_rpwd(abr_PwdKdf *pk);
ABR_EXPORT const char *abr_pk_dpwd(abr_Ctx *ctx, abr_PwdKdf *pk);
ABR_EXPORT const char *abr_pk_pwd(abr_Ctx *ctx, abr_PwdKdf *pk);
ABR_EXPORT void abr_pk_rpwd_set(abr_PwdKdf *pk, const char *rpwd);
ABR_EXPORT void abr_pk_pbe_set(abr_Ctx *ctx, abr_PwdKdf *pk, const abr_Pbe *pbe);

ABR_EXPORT const abr_Pbe *abr_pk_pbe(abr_PwdKdf *pk);
ABR_EXPORT bool abr_pk_isPbe2(abr_PwdKdf *pk);

#ifdef __cplusplus
}
#endif 

#endif /*__ABR_PK_PRIVATE_H__*/
