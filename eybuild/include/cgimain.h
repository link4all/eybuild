/* ebdef.c - define new macros for eybuild */

/* Copyright(C) eyBuild Group, 2005, 2006. All Rights Reserved. */

/*
modification history
--------------------
01b, 2006-8-9		newzy move CGI_ENTRY from cgimain.c to here.
01a, 2006-7-7, 		newzy created
*/


#ifndef _INC_EBCGIMAIN_H_
#define _INC_EBCGIMAIN_H_

#ifdef __cplusplus
extern "C" {
#endif

/* defines */

/* dll entry */
#define EB_DLL_ENTRY	dll_entry


/* For GoAhead webServer link internal */
#if defined(HAVE_CSP_ENGINE)
#	undef CGI_ENTRY
#	define CGI_ENTRY	EB_DLL_ENTRY
#endif

/* dll load entry */
#define EB_MK_ENTRY2(entry)	"" # entry
#define EB_MK_ENTRY(entry)	EB_MK_ENTRY2(entry)
#define DLL_CGI_ENTRY		EB_MK_ENTRY(EB_DLL_ENTRY)


/* typedefs */
typedef int (*LP_CGI_ENTRY)(int argc, char * argv[], char * env[]);


/* externs */
#if defined(WIN32) && defined(HAVE_CSP_ENGINE)
int __declspec(dllexport) EB_DLL_ENTRY(int argc, char * argv[], char * env[]);
#endif /* WIN32 && HAVE_CSP_ENGINE */


#ifdef __cplusplus
	}
#endif

#endif /* _INC_EBCGIMAIN_H_ */
