#ifndef __ABR_XML_PRIVATE_H__
#define __ABR_XML_PRIVATE_H__

#include <stddef.h>

/**
This internal API needs serious refactoring. In particular, it should make a lot more use of abr_String.
*/
typedef struct _abr_Xml abr_Xml;

#define ABR_MAX_XPATH_LEN 500

/**
Used in some methods to control how node content is retrieved.
*/
typedef enum {
    ABR_XML_RAW_FALSE, /**< Will apply normal XML processing to the node content */
    ABR_XML_RAW_OUTER, /**< Will dump the node as raw XML text */
    ABR_XML_RAW_INNER /**< Will dump the node as raw XML text but strip the outer XML tags */
} abr_eXmlNodeContent; 


typedef void (abr_xml_setnode)(abr_Ctx *ctx, void *obj, const char *id, void *node);

#ifdef __cplusplus
extern "C" {
#endif 

ABR_EXPORT void abr_xml_create(abr_Ctx *ctx, abr_Xml **obj, abr_String *buffer);
ABR_EXPORT void *abr_xml_free(abr_Xml *xml);

//deprecated - use abr_xml_namespace_register
ABR_EXPORT void abr_xml_addnamespace(abr_Ctx *ctx, abr_Xml *xml, const char *prefix, const char *uri);
ABR_EXPORT void abr_xml_namespace_register(abr_Ctx *ctx, abr_Xml *xml, const char *prefix, const char *uri);

ABR_EXPORT void abr_xml_savetrim(abr_Ctx *ctx, abr_Xml *xml, abr_String **buffer);
ABR_EXPORT void abr_xml_save(abr_Ctx *ctx, abr_Xml *xml, abr_String **buffer);
ABR_EXPORT void abr_xml_savef(abr_Ctx *ctx, abr_Xml *xml, const char *filepath);
ABR_EXPORT bool abr_xml_isdirty(abr_Xml *xml);
ABR_EXPORT void *abr_xml_findnode(abr_Xml *xml, void *pxnode, const char *xpath, const char *var);
ABR_EXPORT char *abr_xml_value(abr_Xml *xml, void *xnode, char **buffer);
ABR_EXPORT char *abr_xml_valueraw(abr_Xml *xml, void *xnode, char **buffer, bool stripouter);
ABR_EXPORT void abr_xml_setvalue(abr_Xml *xml, void *xnode, const char *value);

ABR_EXPORT void abr_xml_setvaluestr(abr_Xml *xml, void *xnode, abr_String *value);

ABR_EXPORT void *abr_xml_encodedvalue_create(abr_Xml *xml, const char *value);
ABR_EXPORT void *abr_xml_encodedvalue_free(abr_Xml *xml, void *encodedvalue);

ABR_EXPORT bool abr_xml_setnodevaluevar(abr_Xml *xml, void *pxnode, const char *xpath, const char *var, const char *value);
ABR_EXPORT bool abr_xml_setnodevalue(abr_Xml *xml, void *pxnode, const char *xpath, const char *value);
ABR_EXPORT bool abr_xml_setnodevaluelen(abr_Xml *xml, void *pxnode, const char *xpath, const char *value, size_t len);
ABR_EXPORT bool abr_xml_createnodevaluevar(abr_Xml *xml, void *pxnode, const char *xpath, const char *name, const char *var, const char *value);
ABR_EXPORT bool abr_xml_createnodevalue(abr_Xml *xml, void *pxnode, const char *xpath, const char *name, const char *value);
ABR_EXPORT bool abr_xml_createnodevaluelen(abr_Xml *xml, void *pxnode, const char *xpath, const char *name, const char *value, size_t len);
ABR_EXPORT bool abr_xml_createnodevalueraw(abr_Ctx *ctx, abr_Xml *xml, void *pxnode, const char *xpath, const char *name, const char *value);
ABR_EXPORT char *abr_xml_nodevaluevar(abr_Xml *xml, void *pxnode, const char *xpath, const char *var, char **value, abr_eXmlNodeContent raw);
ABR_EXPORT char *abr_xml_nodevalue(abr_Xml *xml, void *pxnode, const char *xpath, char **value, abr_eXmlNodeContent raw);
ABR_EXPORT void abr_xml_setnodes(abr_Ctx *ctx, abr_Xml *xml, const char *nodesxpath, const char *idxpath, abr_xml_setnode setnode, void *userobj);
ABR_EXPORT void abr_xml_deletenode(abr_Xml *xml, void *xnode);
ABR_EXPORT void abr_xml_dropdtd(abr_Xml *xml);
// If xpathExprForParent is NULL parent is pxnode; if pxnode is NULL it is set to docroot; xpathExprForParent is relative to pxnode
ABR_EXPORT void *abr_xml_addnodecopy2(abr_Xml *xml, void *pxnode, const char *xpathExprForParent, void *node, bool clearNs);
ABR_EXPORT void *abr_xml_addnodecopy(abr_Xml *xml, const char *xpathExprForParent, void *node, bool clearNs);
ABR_EXPORT void *abr_xml_clonenode(abr_Xml *xml, void *node, bool clearNs);
ABR_EXPORT void *abr_xml_addnode(abr_Xml *xml, const char *xpathExprForParent, void *node);
ABR_EXPORT void *abr_xml_addnode2(abr_Xml *xml, void *pxnode, const char *xpathExprForParent, void *node);
ABR_EXPORT bool abr_xml_addattr(abr_Xml *xml, void *node, const char *name, const char *value);
ABR_EXPORT void *abr_xml_addelt(abr_Xml *xml, void *pnode, const char *name);
ABR_EXPORT void *abr_xml_createelt(abr_Xml *xml, void *pnode, const char *name);
ABR_EXPORT void *abr_xml_createattr(abr_Xml *xml, void *pnode, const char *name, const char *prefix, const char *href);
ABR_EXPORT char *abr_xml_findnamespace(abr_Xml *xml, void *node, const char *nsprefix, char **value);
ABR_EXPORT void *abr_xml_nodeparent(abr_Xml *xml, void *xnode);
//ABR_EXPORT int abr_xml_createnodevalueraw2(abr_Ctx *ctx, abr_Xml *xml, void *pxnode, const char *value, const char *prefix, const char *href);

ABR_EXPORT void *abr_xml_listload(abr_Xml *xml, void *pxnode, const char *xpath, const char *var);
ABR_EXPORT void *abr_xml_listitem(abr_Xml *xml, void *list, size_t index);
ABR_EXPORT size_t abr_xml_listcount(abr_Xml *xml, void *list);
ABR_EXPORT void abr_xml_listfree(abr_Xml *xml, void *list);

ABR_EXPORT char *abr_xml_root_namespace(abr_Xml *xml, char **value);

#ifdef __cplusplus
}
#endif 

#endif /*__ABR_XML_PRIVATE_H__*/
