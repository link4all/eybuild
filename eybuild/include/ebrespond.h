/* ebfrm.h - eybuild frame header file */

/* Copyright(C) eyBuild Group, 2005, 2006. All Rights Reserved. */

/*
modification history
--------------------
01a, 2006-06-15, newzy   add EB_START
01a, 2006-01-13, newzy   create
*/

#ifndef _INC_EBRESPOND_H_
#define _INC_EBRESPOND_H_

#include <ebfrm.h>

#ifdef __cplusplus
extern "C" {
#endif

/* defines */
#define urlEncode(url)		ebUrlEncode(NULL, (url), 0)	
#define urlDecode(url)		ebUrlDecode(NULL, (url))	
#define htmlEncode(url)		ebHtmlEncode(NULL, (url), 0)	
#define htmlDecode(url)		ebHtmlDecode(NULL, (url))	

#define bwrite			ebwrite
#define setCookie		setcookie
#define getcookie		getCookie

#define USE_THIS_PAGE()	\
		EB_THISPAGE		thispage[1] = {	\
			{__page_name, __page_path, __page_fullname}\
		};
	
/* typedefs */
typedef struct EB_THISPAGE
{
    char * 	name;		/* page name, not include path */
    char *	path;		/* path only */
    char *  fullname;	/* full name, include path */
} EB_THISPAGE;


/* externs */
extern int print(const char * fmt, ...);
extern int bwrite(void * data, size_t size);
extern int header(const char * fmt, ...);
extern int setcookie (char * name, char * value, ...);
extern int redirect(char * p_url, ...);

/* compatible with 0.8.X */
extern int ebSetCookie(void * ebfp, char * name, char *	value, ...);
extern int ebHeader(void * ebfp, const char * fmt, ...);
extern int ebRedirect(void * ebfp, char * p_url, ...);

extern char * unEscapeUrl(char *url);
extern char * ebUrlEncode(char * to, char * from, int maxlen);
extern char * ebUrlDecode(char * to, char * from);
extern char * ebHtmlEncode(char * to, char * from, int maxlen);
extern char * ebHtmlDecode(char * to, char * from);           

extern int    ebSetMainPage(char * pagename);
extern char * ebGetMainPage(char * pagename);
extern char * ebGetMainType(char * pagetype);

#ifdef __cplusplus
}
#endif

#endif /* _INC_EBRESPOND_H_ */
