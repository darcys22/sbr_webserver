#ifndef __SBR_CSR_EXPORTS_H__
#define __SBR_CSR_EXPORTS_H__

#ifdef __cplusplus
extern "C" {
#endif 

#if !defined(SBR_CSR_EXPORT)
#  if !defined(_WIN32) /* oh! the simplicity */
#    define SBR_CSR_EXPORT
#  else  /* :-( */
#    if defined(SBR_CSR_INBUILD)
#      if !defined(SBR_CSR_STATIC)
#        define SBR_CSR_EXPORT __declspec(dllexport)
#      else
#        define SBR_CSR_EXPORT extern
#      endif
#    else /* client is building */
#      if !defined(SBR_CSR_STATIC)
#        define SBR_CSR_EXPORT __declspec(dllimport)
#      else
#        define SBR_CSR_EXPORT
#      endif
#    endif
#  endif
#endif

#if !defined(SBR_CSR_EXPORT_VAR)
#  if !defined(_WIN32) /* oh! the simplicity */
#    define SBR_CSR_EXPORT_VAR extern
#  else  /* :-( */
#    if defined(SBR_CSR_INBUILD)
#      if !defined(SBR_CSR_STATIC)
#        define SBR_CSR_EXPORT_VAR __declspec(dllexport) extern
#      else
#        define SBR_CSR_EXPORT_VAR extern
#      endif
#    else /* client is building */
#      if !defined(SBR_CSR_STATIC)
#        define SBR_CSR_EXPORT_VAR __declspec(dllimport) extern
#      else
#        define SBR_CSR_EXPORT_VAR extern
#      endif
#    endif
#  endif
#endif

#ifdef __cplusplus
}
#endif 

#endif /*__SBR_CSR_EXPORTS_H__*/
