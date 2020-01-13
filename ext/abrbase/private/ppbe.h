#ifndef __ABR_PBE_PRIVATE_H__
#define __ABR_PBE_PRIVATE_H__

typedef struct _abr_Pbe abr_Pbe;

#ifdef __cplusplus
extern "C" {
#endif 

ABR_EXPORT abr_Pbe *abr_pbe_create(abr_Ctx *ctx, abr_Pbe **obj, const char *pbestr);
ABR_EXPORT void *abr_pbe_free(abr_Pbe *pbe);
ABR_EXPORT int abr_pbe_hmac(const abr_Pbe *pbe);
ABR_EXPORT int abr_pbe_enc(const abr_Pbe *pbe);
ABR_EXPORT int abr_pbe_iter(const abr_Pbe *pbe);
ABR_EXPORT const char *abr_pbe_str(const abr_Pbe *pbe);
//ABR_EXPORT const char *abr_pbe_default(bool isLegacy);
// return true if value changes else false
ABR_EXPORT bool abr_pbe_set(abr_Pbe *pbe, const char *pbestr);

ABR_EXPORT bool abr_pbe_isPbe2(const abr_Pbe *pbe);
//ABR_EXPORT bool abr_isPbe2();

#ifdef __cplusplus
}
#endif 

#endif /*__ABR_PBE_PRIVATE_H__*/
