#ifndef __ABR_AKM_EXPORTS_H__
#define __ABR_AKM_EXPORTS_H__

#ifdef __cplusplus
extern "C" {
#endif 

#if !defined(ABR_AKM_EXPORT)
#  if !defined(_WIN32) /* oh! the simplicity */
#    define ABR_AKM_EXPORT
#  else  /* :-( */
#    if defined(ABR_AKM_INBUILD)
#      if !defined(ABR_AKM_STATIC)
#        define ABR_AKM_EXPORT __declspec(dllexport)
#      else
#        define ABR_AKM_EXPORT extern
#      endif
#    else /* client is building */
#      if !defined(ABR_AKM_STATIC)
#        define ABR_AKM_EXPORT __declspec(dllimport)
#      else
#        define ABR_AKM_EXPORT
#      endif
#    endif
#  endif
#endif

#if !defined(ABR_AKM_EXPORT_VAR)
#  if !defined(_WIN32) /* oh! the simplicity */
#    define ABR_AKM_EXPORT_VAR extern
#  else  /* :-( */
#    if defined(ABR_AKM_INBUILD)
#      if !defined(ABR_AKM_STATIC)
#        define ABR_AKM_EXPORT_VAR __declspec(dllexport) extern
#      else
#        define ABR_AKM_EXPORT_VAR extern
#      endif
#    else /* client is building */
#      if !defined(ABR_AKM_STATIC)
#        define ABR_AKM_EXPORT_VAR __declspec(dllimport) extern
#      else
#        define ABR_AKM_EXPORT_VAR extern
#      endif
#    endif
#  endif
#endif

#ifdef __cplusplus
}
#endif 

#endif /*__ABR_AKM_EXPORTS_H__*/
