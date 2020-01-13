#ifndef __ABR_NETD_PRIVATE_H__
#define __ABR_NETD_PRIVATE_H__

typedef struct _abr_NetData abr_NetData;
typedef struct _abr_NetDataItem abr_NetDataItem;

typedef enum {
	ABR_NETD_TYPE_UNKNOWN,
	ABR_NETD_TYPE_MULTI,
	ABR_NETD_TYPE_SOAP,
	ABR_NETD_TYPE_XOP,
	ABR_NETD_TYPE_OTHER,
	ABR_NETD_TYPE_MULTI_OTHER
} abr_eNetDataType;

typedef enum {
	ABR_NETD_ENC_NONE,
	ABR_NETD_ENC_BASE64,
	ABR_NETD_ENC_QUOTED
} abr_eNetDataTypeEnc;

#ifdef __cplusplus
extern "C" {
#endif

ABR_EXPORT void abr_netd_create(abr_NetData **netdata);
ABR_EXPORT void *abr_netd_free(abr_NetData *netdata);
ABR_EXPORT abr_NetDataItem *abr_netd_additem(abr_NetData *netdata);

ABR_EXPORT const char *abr_netd_cid(abr_NetDataItem *nditem);
ABR_EXPORT const char *abr_netd_cidnoprefix(abr_NetDataItem *nditem);
ABR_EXPORT abr_eNetDataType abr_netd_type(abr_NetDataItem *nditem);
ABR_EXPORT const char *abr_netd_contenttype(abr_NetDataItem *nditem);
ABR_EXPORT abr_eNetDataTypeEnc abr_netd_encoding(abr_NetDataItem *nditem);
ABR_EXPORT abr_String *abr_netd_content(abr_NetDataItem *nditem);

ABR_EXPORT void abr_netd_setcid(abr_NetDataItem *nditem, const char *cid);
ABR_EXPORT void abr_netd_settype(abr_NetDataItem *nditem, abr_eNetDataType type);
ABR_EXPORT void abr_netd_setcontenttype(abr_NetDataItem *nditem, const char *contenttype);
ABR_EXPORT void abr_netd_setencoding(abr_NetDataItem *nditem, abr_eNetDataTypeEnc encoding);
ABR_EXPORT void abr_netd_addcontent(abr_NetDataItem *nditem, abr_String *content);

ABR_EXPORT size_t abr_netd_count(abr_NetData *netdata);
ABR_EXPORT void abr_netd_iterator(abr_NetData *netdata, abr_Iterator **iter);
ABR_EXPORT abr_NetDataItem *abr_netd_firstv(abr_NetData *netdata);
ABR_EXPORT abr_NetDataItem *abr_netd_nextv(abr_NetData *netdata);

ABR_EXPORT abr_NetDataItem *abr_netd_item(abr_NetData *netdata, abr_eNetDataType type);
ABR_EXPORT abr_NetDataItem *abr_netd_item_primary(abr_NetData *netdata);
ABR_EXPORT void abr_netd_clearcontent(abr_NetDataItem *nditem);

ABR_EXPORT void abr_netd_processmpresponse(abr_Ctx *ctx, abr_NetData *netdata, const char *boundaryid);
ABR_EXPORT bool abr_netd_mtom_convertfrom(abr_Ctx *ctx, abr_NetData *netdata, abr_Xml *xml);
ABR_EXPORT bool abr_netd_mtom_convertto(abr_Ctx *ctx, abr_NetData **nddataarg, abr_Xml *xml, const char *mtomxpath, size_t mtomthreshhold, const char *contenttypexpath);

#ifdef __cplusplus
}
#endif 

/*! @} */

#endif /*__ABR_NETD_PRIVATE_H__*/
