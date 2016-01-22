/* ebfrm.h - eybuild frame header file */

/* Copyright(C) eyBuild Group, 2005, 2006. All Rights Reserved. */

/*
modification history
--------------------
01b, 2006-11-10, newzy   mod EB_AUTO_HTONL(), EB_AUTO_NTOHL() to suppuprt 64bit
01b, 2006-04-09, newzy   support fastcgi
01a, 2005-12-25, newzy   create
*/

#ifndef _INC_EBUILD_FRM_H_
#define _INC_EBUILD_FRM_H_

#ifdef HAVE_FASTCGI
#   include <fcgi_stdio.h>
#else
#   include <stdio.h>
#endif /* HAVE_FASTCGI */

#include <time.h>
#include <ebdef.h>

#ifdef __cplusplus
extern "C" {
#endif

/* versions */
#define VER_EYBOX   	"1.1.2"
#define VER_WEB2BIN 	"1.1.2"
#define VER_CSP2BIN 	"1.1.2"
#define VER_CSPENGINE	"1.1.2"

/* WIN32 only */
#ifdef WIN32
#undef vsnprintf
#undef snprintf
#undef setmode
#define vsnprintf		_vsnprintf
#define snprintf		_snprintf
#define setmode		    _setmode

#ifndef HAVE_FASTCGI
#   undef fileno
#   define fileno		_fileno
#endif
#endif /* WIN32 */

/* zero length string */
#define ZERO_STR		""

/* for csp2bin */
#define MAX_CALL_DEPTH	6
#define goto_ERROR	    if (ERROR==__ret) goto ON_END
#define goto_page_end()	goto ON_END
#define pageExit(ret)	page_exit(ret)
#define page_exit(ret)	{__ret=(ret); goto ON_END;}

/* eybuild internal path, 
 * this value must same with the value in 
 * "/src/map/cspmap.map" and "/src/map/rommap.map"
 */
#define EB_VDIR				"/_ebvdir_/"
#define EB_DEFAULT_MAINPAGE	"/main.csp"

/* avaliable envirement */
#define EBENV_MAIN_PAGE			"EBENV_MAIN_PAGE"			
#define EBENV_PAGE_NOT_FOUND	"EBENV_PAGE_NOT_FOUND"	


/* for gcc -Wall option,
 * should add -DREMOVE_NOUSED_WARNING
 */
#ifndef REMOVE_NOUSED_WARNING
#define EB_REMOVE_NOUSED_WARNING()
#else
#define EB_REMOVE_NOUSED_WARNING()	\
    	__page_name=thispage->name,	\
    	__page_path=thispage->path,	\
    	__page_fullname=thispage->fullname
#endif /* REMOVE_NOUSED_WARNING */

/* 
* define macro G to accelerate coding
* EB_G_DISABLE is to undef G macro 
*/

#ifndef EB_DISABLED_G
	#if defined(G) || defined(GNext)
	# 	error G(x) or GNext(x), has been defined.
	#else
	#	define G(x)			getParameter(x)
	#	define GNext(x,y)	getParameterNext((x), (y))
	#endif
#endif /* EB_DISABLED_G */


/*
* EB_FREE 	- free dynamic space 
* EB_MALLOC - allocate dynamic space 
*/ 
#define MALLOC_ERROR		"Allocate memory failure"

#undef  EB_FREE
#define EB_FREE(p)	\
		if (p) {free(p); p=NULL;}

#undef  EB_MALLOC
#define EB_MALLOC(p, size)	\
		if (NULL == (p=malloc(size))) { \
			ebSendErrorLog(500, (MALLOC_ERROR)); \
			return ERROR; \
		} \
		memset(p, 0, (size))		


#define EBNTOHL(x)	((((x) & 0x000000ff) << 24) | \
			 (((x) & 0x0000ff00) <<  8) | \
			 (((x) & 0x00ff0000) >>  8) | \
			 (((x) & 0xff000000) >> 24))

#define EBHTONL(x)	((((x) & 0x000000ff) << 24) | \
			 (((x) & 0x0000ff00) <<  8) | \
			 (((x) & 0x00ff0000) >>  8) | \
			 (((x) & 0xff000000) >> 24))

/* auto convert BYTE-ORDER 
 * support 32bit and 64bit 
 */
#define EB_AUTO_HTONL(x)	((((*(short*)"ABCDEFG")&0xFF)==0x41) ? EBHTONL(x): (x))
#define EB_AUTO_NTOHL(x)	((((*(short*)"ABCDEFG")&0xFF)==0x41) ? EBHTONL(x): (x)) 

/* for compatibility with version 0.x.x */
#define EB_ROM_MAPLIST			EB_ROM_MAPFILE
#define EB_CSP_MAPLIST			EB_CSP_MAPFILE

#define EB_FILE_ID_BASE			0x00001000
#define EB_OPT_AUTOFLASH		0x10000000
#define EB_OPT_COMPRESSED		0x00010000

/* 
 *	Mime type list
 */
typedef struct EB_MIME_TYPE
{
	char *		    type;	    /* Mime type */
	char *		    ext;	    /* File extension */
} EB_MIME_TYPE;

/*  
 * rom file list
 */
typedef struct 
{
	char *			name;       /* name of file */
	unsigned char *	pdata;      /* data area */
    time_t			mtime;      /* last modified time */
	unsigned		options;	/* options */
} EB_ROM_MAPFILE;

/* cgi page hooks */
typedef int (*CGI_PAGE_HOOK)
	(
	int		calldepth,	/* stack depth */
	void *	handle,		/* page handle, used by @require */
	void *	ebfp		/* page buffer pointer */
	);

/* typedefs */
typedef struct EB_CSP_MAPFILE 
{
    char *          name;    	/* page name */
    CGI_PAGE_HOOK   func;       /* page hooks */
    int             bufsize;    /* page buffer size */
	unsigned		options;	/* options */
	unsigned char *	pdata;		/* data list */
} EB_CSP_MAPFILE;


/* externs */
extern int    strcmpin(char *s1, char *s2, int n);
extern char * ebgetenv(char *varname);
extern char * get_filename(char * fullname);

extern int ebSendError
    (
    int         errnum,     /* http error number */
    char *      errfmt, ... /* error message */
    );

#ifdef __cplusplus
}
#endif

#endif /* _INC_EBFRAME_H_ */

