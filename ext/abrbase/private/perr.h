#ifndef __ABR_ERR_PRIVATE_H__
#define __ABR_ERR_PRIVATE_H__

#include "abrbase/err.h"


#ifdef __cplusplus
extern "C" {
#endif 

ABR_EXPORT bool abr_err_isdeleted(abr_Err *err);
ABR_EXPORT bool abr_err_isprocessed(abr_Err *err);
ABR_EXPORT void abr_err_setisprocessed(abr_Err *err, bool isprocessed);

#ifdef __cplusplus
}
#endif 

#endif /*__ABR_ERR_PRIVATE_H__*/
