#ifndef __ABR_STM_EXPORTS_H__
#define __ABR_STM_EXPORTS_H__

#ifdef __cplusplus
extern "C" {
#endif 

#if !defined(ABR_STM_EXPORT)
#  if !defined(_WIN32) /* oh! the simplicity */
#    define ABR_STM_EXPORT
#  else  /* :-( */
#    if defined(ABR_STM_INBUILD)
#      if !defined(ABR_STM_STATIC)
#        define ABR_STM_EXPORT __declspec(dllexport)
#      else
#        define ABR_STM_EXPORT extern
#      endif
#    else /* client is building */
#      if !defined(ABR_STM_STATIC)
#        define ABR_STM_EXPORT __declspec(dllimport)
#      else
#        define ABR_STM_EXPORT
#      endif
#    endif
#  endif
#endif

#if !defined(ABR_STM_EXPORT_VAR)
#  if !defined(_WIN32) /* oh! the simplicity */
#    define ABR_STM_EXPORT_VAR extern
#  else  /* :-( */
#    if defined(ABR_STM_INBUILD)
#      if !defined(ABR_STM_STATIC)
#        define ABR_STM_EXPORT_VAR __declspec(dllexport) extern
#      else
#        define ABR_STM_EXPORT_VAR extern
#      endif
#    else /* client is building */
#      if !defined(ABR_STM_STATIC)
#        define ABR_STM_EXPORT_VAR __declspec(dllimport) extern
#      else
#        define ABR_STM_EXPORT_VAR extern
#      endif
#    endif
#  endif
#endif

#ifdef __cplusplus
}
#endif 

#endif /*__ABR_STM_EXPORTS_H__*/
