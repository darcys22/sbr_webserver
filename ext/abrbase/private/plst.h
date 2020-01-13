#ifndef __ABR_LST_PRIVATE_H__
#define __ABR_LST_PRIVATE_H__

#include <stddef.h>

typedef struct _abr_ListNode abr_ListNode;
typedef struct _abr_List abr_List;

#ifdef __cplusplus
extern "C" {
#endif 

ABR_EXPORT void abr_lst_create(abr_List **lst);
ABR_EXPORT void *abr_lst_free(abr_List *lst);
ABR_EXPORT void abr_lst_clear(abr_List *lst);
ABR_EXPORT size_t abr_lst_count(abr_List *lst);
ABR_EXPORT abr_ListNode *abr_lst_add(abr_List *lst, const char *key, void *value);
ABR_EXPORT abr_ListNode *abr_lst_addconst(abr_List *lst, const char *key, const void *value);
ABR_EXPORT abr_ListNode *abr_lst_next(abr_List *lst, abr_ListNode *node);
ABR_EXPORT void *abr_lst_value(abr_ListNode *node);
ABR_EXPORT const void *abr_lst_valueconst(abr_ListNode *node);
// return value as a const or if NULL return const
ABR_EXPORT const void *abr_lst_valueorconst(abr_ListNode *node);
ABR_EXPORT const char *abr_lst_key(abr_ListNode *node);
ABR_EXPORT abr_ListNode *abr_lst_find(abr_List *lst, const char *key);
ABR_EXPORT void abr_lst_delete(abr_ListNode *node);
ABR_EXPORT void abr_lst_setvalue(abr_ListNode *node, void *value);
ABR_EXPORT void abr_lst_setvalueconst(abr_ListNode *node, const void *value);

#ifdef __cplusplus
}
#endif 

#endif /*__ABR_LST_PRIVATE_H__*/

