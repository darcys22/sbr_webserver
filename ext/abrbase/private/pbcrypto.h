#ifndef __ABR_CRYPTO_PRIVATE_H__
#define __ABR_CRYPTO_PRIVATE_H__

typedef struct _abr_Crypto abr_Crypto;

#ifdef __cplusplus
extern "C" {
#endif 

// This will take an internal copy of the arguments
ABR_EXPORT void abr_crypto_create(abr_Ctx *ctx, abr_Crypto **obj, const char *b64p7c, const char *b64p8, const char *b64salt);
// This will take a reference - do not free arguments
ABR_EXPORT void abr_crypto_create_ref(abr_Ctx *ctx, abr_Crypto **obj, char *b64p7c, char *b64p8, char *b64salt);
// This will take a reference - do not free arguments
ABR_EXPORT void abr_crypto_createstr_ref(abr_Ctx *ctx, abr_Crypto **obj, abr_String *b64p7c, abr_String *b64p8, abr_String *b64salt);

ABR_EXPORT void *abr_crypto_free(abr_Crypto *crypto);
ABR_EXPORT abr_Ctx *abr_crypto_ctx(abr_Crypto *crypto);

ABR_EXPORT void abr_crypto_iscorrectpwd(abr_Ctx *ctx, abr_Crypto *crypto, bool *correct, abr_PwdKdf *pk);
ABR_EXPORT bool abr_crypto_changepwd(abr_Ctx *ctx, abr_Crypto *crypto, abr_PwdKdf *pk, abr_PwdKdf *newpk);
ABR_EXPORT void abr_crypto_certificate(abr_Ctx *ctx, abr_Crypto *crypto, abr_String **certificate);
ABR_EXPORT void abr_crypto_chain(abr_Ctx *ctx, abr_Crypto *crypto,  abr_String **certificates);
ABR_EXPORT bool abr_crypto_privatekey(abr_Ctx *ctx, abr_Crypto *crypto, abr_String **privatekey, abr_PwdKdf *pk);
ABR_EXPORT bool abr_crypto_p12(abr_Ctx *ctx, abr_Crypto *crypto, abr_String **p12, abr_PwdKdf *pk);
ABR_EXPORT abr_String *abr_crypto_b64salt(abr_Crypto *crypto);
ABR_EXPORT abr_String *abr_crypto_b64p7(abr_Crypto *crypto);
ABR_EXPORT abr_String *abr_crypto_b64p8(abr_Crypto *crypto);
ABR_EXPORT bool abr_crypto_generateP10(abr_Ctx *ctx, abr_Crypto *crypto, abr_PwdKdf *kdf, abr_String *salt, abr_String **p10, abr_String **p8);
ABR_EXPORT abr_String *abr_crypto_serialnr(abr_Ctx *ctx, abr_Crypto *crypto, abr_String **serialNr);
ABR_EXPORT abr_String *abr_crypto_notbefore(abr_Ctx *ctx, abr_Crypto *crypto, abr_String **notBefore);
ABR_EXPORT abr_String *abr_crypto_notafter(abr_Ctx *ctx, abr_Crypto *crypto, abr_String **notAfter);
ABR_EXPORT char *abr_crypto_kdf(abr_Ctx *ctx, char **dpwd, const char *pwd, const abr_String *bsalt, size_t iterations, size_t octets, int prfid);

ABR_EXPORT bool abr_crypto_ispbe2(abr_Crypto *crypto);
ABR_EXPORT char *abr_crypto_rootcert_name(abr_Crypto *crypto, char *buf, size_t len);

#ifdef __cplusplus
}
#endif 

#endif /*__ABR_CRYPTO_PRIVATE_H__*/
