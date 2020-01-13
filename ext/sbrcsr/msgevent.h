#ifndef __SBR_CSR_MSGEVENT_H__
#define __SBR_CSR_MSGEVENT_H__

/** @addtogroup sbrcsr_api_csr_msgevent

@{
*/

/**
This contains information from the service about the request and transaction that occurred. 

It represents both success and any business level error conditions, with a successful transaction
containing at least one 'Information' severity level event item. The maximum severity level of all the 
event items is returned using sbr_sbdm_maxseveritycode().
*/
typedef struct _sbr_MsgEventItem sbr_MsgEventItem;

/**
A @ref sbr_MsgEventItem can contain 1 or more of these.
*/
typedef struct _sbr_MsgEventItemLocation sbr_MsgEventItemLocation;

/**
A @ref sbr_MsgEventItem can contain 0 or more of these.
*/
typedef struct _sbr_MsgEventItemParam sbr_MsgEventItemParam;

#ifdef __cplusplus
extern "C" {
#endif

/**
Return the error code.

@param eventitem the eventitem

@return the error code 
*/
SBR_CSR_EXPORT const char *sbr_msgevent_code(sbr_MsgEventItem *eventitem);

/**
Return the severity.

@param eventitem the eventitem

@return the severity 
*/
SBR_CSR_EXPORT const char *sbr_msgevent_severity(sbr_MsgEventItem *eventitem);

/**
Return the short description.

@param eventitem the eventitem

@return the short description */
SBR_CSR_EXPORT const char *sbr_msgevent_shortdesc(sbr_MsgEventItem *eventitem);

/**
Return the long description.

@param eventitem the eventitem

@return the long description 
*/
SBR_CSR_EXPORT const char *sbr_msgevent_longdesc(sbr_MsgEventItem *eventitem);

/**
Return the number of locations this event applies to.
Locations refer an incoming @ref sbr_Doc in the @ref sbr_Request.

@param eventitem the eventitem

@return the number of locations 
*/
SBR_CSR_EXPORT size_t sbr_msgevent_location_count(sbr_MsgEventItem *eventitem);

/**
Create an iterator the collection of locations - caller must free.

This is useful if a collection is being shared between threads and each thread has its own iterator. 

If this is not the case then the sbr_msgevent_location_firstv() and sbr_msgevent_location_nextv() methods are simpler and this method can be ignored.

@param eventitem the eventitem.
@param iter the address of the iterator to create - *iter must be NULL.
This will be NULL if there is no collection.
*/
SBR_CSR_EXPORT void sbr_msgevent_location_iterator(sbr_MsgEventItem *eventitem, abr_Iterator **iter);

/**
Return the first location.

@param eventitem the eventitem.

@return the location or NULL if none. 
*/
SBR_CSR_EXPORT sbr_MsgEventItemLocation *sbr_msgevent_location_firstv(sbr_MsgEventItem *eventitem);

/**
Return the next location.

@param eventitem the eventitem.

@return the location or NULL if none. 
*/
SBR_CSR_EXPORT sbr_MsgEventItemLocation *sbr_msgevent_location_nextv(sbr_MsgEventItem *eventitem);

/**
Return the sequence number of a particular document in the incoming  @ref sbr_Sbdm.

@param location the eventitem location

@return the sequence number or 0 if none or the index is out of range.
*/
SBR_CSR_EXPORT size_t sbr_msgevent_location_sequencenr(sbr_MsgEventItemLocation *location);

/**
The location path field indicates, via an XPath expression, 
the element in the incoming XBRL document to which the event item refers.

@param location the eventitem location

@return the location path or NULL if none or the index is out of range.
*/
SBR_CSR_EXPORT const char *sbr_msgevent_location_path(sbr_MsgEventItemLocation *location);

/**
Return the number of parameters this event has.

@param eventitem the eventitem.

@return the number of parameters. 
*/
SBR_CSR_EXPORT size_t sbr_msgevent_param_count(sbr_MsgEventItem *eventitem);

/**
Create an iterator the collection of paramters - caller must free.

This is useful if a collection is being shared between threads and each thread has its own iterator. 

If this is not the case then the sbr_msgevent_param_firstv() and sbr_msgevent_param_nextv() methods are simpler and this method can be ignored.

@param eventitem the eventitem. 
@param iter the address of the iterator to create - *iter must be NULL. 
This will be NULL if there is no collection.
*/
SBR_CSR_EXPORT void sbr_msgevent_param_iterator(sbr_MsgEventItem *eventitem, abr_Iterator **iter);

/**
Return the first parameter.

@param eventitem the eventitem.

@return the parameter or NULL if none. 
*/
SBR_CSR_EXPORT sbr_MsgEventItemParam *sbr_msgevent_param_firstv(sbr_MsgEventItem *eventitem);

/**
Return the next parameter.

@param eventitem the eventitem.

@return the parameter or NULL if none. 
*/
SBR_CSR_EXPORT sbr_MsgEventItemParam *sbr_msgevent_param_nextv(sbr_MsgEventItem *eventitem);

/**
The parameter name.

@param param the eventitem parameter.

@return the parameter name or NULL if none.
*/
SBR_CSR_EXPORT const char *sbr_msgevent_param_name(sbr_MsgEventItemParam *param);

/**
The parameter value.

@param param the eventitem parameter.

@return the parameter value or NULL if none.
*/
SBR_CSR_EXPORT const char *sbr_msgevent_param_value(sbr_MsgEventItemParam *param);

#ifdef __cplusplus
}
#endif 

/*! @} */

#endif /*__SBR_CSR_MSGEVENT_H__*/
