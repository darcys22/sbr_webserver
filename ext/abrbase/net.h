#ifndef __ABR_NET_H__
#define __ABR_NET_H__

/* @addtogroup abrbase_api_public_net

This provides some useful methods to assist in determining application network issues.

*/

/** @defgroup abrbase_api_public_net_defines Defines
@ingroup abrbase_api_public_net

Debug flags for the network library.
*/

/** @defgroup abrbase_api_public_net_defines_flags Flags
@ingroup abrbase_api_public_net_defines

Debug flags for the network library.

@{
*/ 
#define ABR_NET_DEBUG_FLAG_OFF        0    /**< Don't log any network activity */
#define ABR_NET_DEBUG_FLAG_TEXT       0x01 /**< Log basic network activity */
#define ABR_NET_DEBUG_FLAG_HDR_IN     0x02 /**< Log all header data received */
#define ABR_NET_DEBUG_FLAG_HDR_OUT    0x04 /**< Log all header data sent */
#define ABR_NET_DEBUG_FLAG_DATA_IN    0x08 /**< Log all data received - may contain binary */
#define ABR_NET_DEBUG_FLAG_DATA_OUT   0x10 /**< Log all data sent - may contain binary */
#define ABR_NET_DEBUG_FLAG_SSL_IN     0x20 /**< Log SSL related details received - may contain binary */
#define ABR_NET_DEBUG_FLAG_SSL_OUT    0x40 /**< Log SSL related details sent - may contain binary */
#define ABR_NET_DEBUG_FLAG_ALL        0xff /**< Log everything - may contain binary */

/*! @} */

/** @defgroup abrbase_api_public_net_defines_name Names
@ingroup abrbase_api_public_net_defines

Names of net log flags as strings.
This is useful, for example, if passing in on the command line.

@{
*/ 
#define ABR_NET_DEBUG_FLAG_OFF_NAME      "off"  /**< "off" - mutually exclusive - will force everything off */
#define ABR_NET_DEBUG_FLAG_TEXT_NAME     "text" /**< "text" */
#define ABR_NET_DEBUG_FLAG_HDR_IN_NAME   "hin"  /**< "hin" */
#define ABR_NET_DEBUG_FLAG_HDR_OUT_NAME  "hout" /**< "hout" -  */
#define ABR_NET_DEBUG_FLAG_DATA_IN_NAME  "din"  /**< "din" - */
#define ABR_NET_DEBUG_FLAG_DATA_OUT_NAME "dout" /**< "dout" - */
#define ABR_NET_DEBUG_FLAG_SSL_IN_NAME   "sin"  /**< "sin" - */
#define ABR_NET_DEBUG_FLAG_SSL_OUT_NAME  "sout" /**< "sout" - */
#define ABR_NET_DEBUG_FLAG_ALL_NAME      "all"  /**< "all" - mutually exclusive but "off" has precedence - will force everything on */

/**
The signature for the curl option function - see abr_net_setcurloptfn().
void *curl is a CURL *handle. Return value is a CURLcode.
*/
typedef int (abr_curloptfunction)(void *curl);


/*! @} */

#ifdef __cplusplus
extern "C" {
#endif 

/** @defgroup abrbase_api_public_net_methods Methods
@ingroup abrbase_api_public_net

@{
*/ 

/**
Use this to set additional options for CURL that may be required for particular circumstances.

An example of such a function would be:
@code{.c}
static int curloptfunction(void *curl) {
    CURLcode rc = CURLE_OK;
    if (curl == NULL) { return rc; }
    if (arg_sslversion != NULL) {
        // Some servers (VANguard) will negotiate TLS1.2 but some proxies do not properly support it.
        // If this is the case, try another protocol.
        char *urlp = NULL;
        rc = curl_easy_getinfo(curl, CURLINFO_EFFECTIVE_URL, &urlp);
        if (rc != CURLE_OK) { return rc; }
        if (urlp != NULL && strstr(urlp, "authentication.business.gov.au") != NULL) {
            // only do this when connecting to VANguard
            printf("Setting CURLOPT_SSLVERSION to '%s'\n", arg_sslversion);
            if (_streqi(arg_sslversion, "default")) {
                rc = curl_easy_setopt(curl, CURLOPT_SSLVERSION, CURL_SSLVERSION_DEFAULT);
            } else if (_streqi(arg_sslversion, "tlsv1")) {
                rc = curl_easy_setopt(curl, CURLOPT_SSLVERSION, CURL_SSLVERSION_TLSv1);
            } else if (_streqi(arg_sslversion, "sslv2")) {
                rc = curl_easy_setopt(curl, CURLOPT_SSLVERSION, CURL_SSLVERSION_SSLv2);
            } else if (_streqi(arg_sslversion, "sslv3")) {
                rc = curl_easy_setopt(curl, CURLOPT_SSLVERSION, CURL_SSLVERSION_SSLv3);
            } else if (_streqi(arg_sslversion, "tlsv1_0")) {
                rc = curl_easy_setopt(curl, CURLOPT_SSLVERSION, CURL_SSLVERSION_TLSv1_0);
            } else if (_streqi(arg_sslversion, "tlsv1_1")) {
                rc = curl_easy_setopt(curl, CURLOPT_SSLVERSION, CURL_SSLVERSION_TLSv1_1);
            } else if (_streqi(arg_sslversion, "tlsv1_2")) {
                rc = curl_easy_setopt(curl, CURLOPT_SSLVERSION, CURL_SSLVERSION_TLSv1_2);
            } else {
                printf("***Setting CURLOPT_SSLVERSION FAILED (ignoring)***");
            }
        }
    }
    if (arg_sslcainfo != NULL) {
        // careful - we're not catering to platform independence here
        // so the arg_sslcainfo path is OS specific.
        // Don't bother setting if the file doesn't exist
    	struct stat sb;
    	if (stat(arg_sslcainfo, &sb) == 0) {
            rc = curl_easy_setopt(curl, CURLOPT_CAINFO, arg_sslcainfo);
        }
    }
    return rc;
}
@endcode
where _streqi is:
@code{.c}
static bool _streqi(const char *src, const char *src2) {
    if (src == NULL && src2 == NULL) { return TRUE; }
    if ((src == NULL && src2 != NULL) || (src != NULL && src2 == NULL)) { return FALSE; }
    if (strlen(src) != strlen(src2)) { return FALSE; }
	while (*src2 != '\0') {
        if (tolower((int)*src) != tolower((int)*src2)) { return FALSE; }
		src++; src2++;
	}
	return TRUE;
}
@endcode

@param curloptfunction the global function to use
*/
ABR_EXPORT void abr_net_setcurloptfn(abr_curloptfunction curloptfunction);

/**
The version number of the network library libcurl.
@return The version number of the network library libcurl.
*/
ABR_EXPORT const char *abr_net_version(void);

/**
The current debug flags.
@return The current debug flags.
*/
ABR_EXPORT unsigned int abr_net_debugflag(void);

/**
The debug flags to set.
@param flag See defines for values - default is ABR_NET_DEBUG_FLAG_TEXT
*/
ABR_EXPORT void abr_net_setdebugflag(unsigned int flag);

/**
Convert the set of lower-case names, comma delimited, representing flag names to the int equivalent. 

Names must be comma-delimited and lower-case.
They can appear multiple times in any combination - "off" has precedence, then "all".
Unrecognised names will be ignored.

@param names the flag name(s) as a comma delimited string. 
NULL or empty string is equivalent to a string containing "off".
@return the flag int
*/
ABR_EXPORT unsigned int abr_net_names2flag(const char *names);

/*! @} */

#ifdef __cplusplus
}
#endif 

#endif /*__ABR_LOG_H__*/

