/* ebhandle.h - handle CGI request and reqsponed */

/* Copyright(C) eyBuild Group, 2005, 2006. All Rights Reserved. */

/*
modification history
--------------------
01a, 2006-01-13, newzy   create
*/

#ifndef _INC_EBHANDLE_H_
#define _INC_EBHANDLE_H_

#include <ebfrm.h>
#include <ebenviron.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef CGI_ENTRY
#define CGI_ENTRY		main
#endif

#define EB_CGIMAIN		__eb_cgimain__
#define EB_USER_CGIMAIN	__usr_cgimain__

#define SET_USRMAIN_RAW2(name, prefix)	prefix ## name	
#define SET_USRMAIN_RAW(name, prefix)	SET_USRMAIN_RAW2(name, prefix)	
#define SET_USRMAIN(name)	SET_USRMAIN_RAW(name, EB_USER_CGIMAIN)

/* force add argument list,
 * used for C++ main(int, char*[], char*[])
 */
#ifdef HAVE_MAIN_ARGLIST
#define EB_MAIN_ARGLIST()	(int argc, char *argv[], char *env[])
#else
#define EB_MAIN_ARGLIST()	()
#endif

#ifdef HAVE_NO_CGIMAIN
#define cgimain CGI_ENTRY
#else /* HAVE_NO_CGIMAIN */
#define cgimain \
		CGI_ENTRY (int argc, char * argv[], char * env[]) {	\
			int SET_USRMAIN(CGI_ENTRY)EB_MAIN_ARGLIST();	\
			return  EB_CGIMAIN(argc, argv, env,		\
					(USR_FUNC)(SET_USRMAIN(CGI_ENTRY)));\
		}			\
		int SET_USRMAIN(CGI_ENTRY)
#endif

/* 
* begin fast cgi loop
* end fastcgi loop 
*/
#ifndef HAVE_FASTCGI
#	define BEGIN_FASTCGI_LOOP()
#	define END_FASTCGI_LOOP()
#else/* HAVE_FASTCGI  */
#define BEGIN_FASTCGI_LOOP()	\
   		while (FCGI_Accept() >= 0) {	\
			if (ERROR == ebRequestReset())	\
				break;

#define END_FASTCGI_LOOP()	\
   	}
#endif /* HAVE_FASTCGI */


/* defines */
#if 0
#define EB_IDMAP_ALL		0	/* default support IDMAP and pagename */
#define EB_IDMAP_DISABLE	1	/* disable IDMAP */
#define EB_IDMAP_ONLY		2	/* only support IDMAP */
#endif

#define EB_OPT_ROM_LOCAL_FS		(1<<0)	/* use local file system */
#define EB_OPT_CGI_LOCAL_FS		(1<<1)	/* use local file system */
#define EB_OPT_IDMAP_ENABLE		(1<<2)	/* disable IDMAP */
#define EB_OPT_VPATH_DISABLE	(1<<3)	/* use local file system */

#define EBTYPE_DISPATCH_MASK	0xF0
#define EBTYPE_DISPATCH_IDMAP	0x01

#define EBTYPE_DISPATCH_CGI		0x10
#define EBTYPE_DISPATCH_ROM		0x20
#define EBTYPE_UNKNOW			0x30


/* typedefs */
typedef int (*USR_FUNC)(int argc, char * argv[], char * env[]);


/* externs */
extern int ebSetDebug (char * p_method, char * p_query);
extern int eyBuildExec2(void *csplist, int size1, 
						void *romlist, int size2, 
						void *resloved
						);

/* check query */
extern char * ebGetRequestPageType();
extern char * ebGetRequestPageName();

/* map to ID */
extern char * ebCSPIDMap(char * pname, char * pbuf);
extern char * ebRomIDMap(char * pname, char * pbuf);

/* search page */
extern EB_ROM_MAPFILE * getRomPage(int rtype, char * pname);
extern EB_CSP_MAPFILE * getCSPPage(int rtype, char * pname);

/* cgi main entry */
extern int EB_CGIMAIN(int argc, char * argv[], char * env[], USR_FUNC usrmain);
extern int ebDefMimeHeader();

#ifdef __cplusplus
}
#endif

#endif /* _INC_EBHANDLE_H_ */


