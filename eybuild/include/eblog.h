/* eblog.h - eybuild logs header file */

/* Copyright(C) eyBuild Group, 2005, 2006. All Rights Reserved. */

/*
modification history
--------------------
01b, 2006-04-09, newzy   support fastcgi
01a, 2005-12-25, newzy   create
*/

#ifndef _INC_EBLOG_H_
#define _INC_EBLOG_H_

#ifdef HAVE_FASTCGI
#   include <fcgi_stdio.h>
#else
#   include <stdio.h>
#endif /* HAVE_FASTCGI */

#ifdef __cplusplus
extern "C" {
#endif

/* basic log type */
#define EBLOG_NOTICE		0x0000	/* notice */
#define EBLOG_WARNING		0x0010	/* warning */
#define EBLOG_USRBASE		0x0100	/* user log rang */
#define EBLOG_ERROR			0x1000	/* error */

/* log level */
#define EBLOG_NOTHING		0xFFFF	/* log nothing */
#define EBLOG_DEFAULT_LEVEL	EBLOG_WARNING	/* log all except notice */

/* decide what should be logged */
#ifndef EBLOG_LEVEL
#define EBLOG_LEVEL			EBLOG_DEFAULT_LEVEL
#endif


/* log */	
#ifdef HAVE_LOG_SHORT
#	define ebLogMsg(type, msg)	ebLogMsg2(NULL, 0, (type), (msg))
#	define ebLogFMsg(type, msg)	ebLogMsg2(NULL, 0, (type), ebMakeMsg msg)
#else
#	define ebLogMsg(type, msg)	ebLogMsg2(__FILE__, __LINE__, (type), (msg))
#	define ebLogFMsg(type, msg)	ebLogMsg2(NULL, 0, (type), ebMakeMsg msg)
#endif


/* externs */
extern char * ebMakeMsg(char * fmt, ...);
extern int ebLogMsg2(char * file, int line, int type, char * msg);

#ifdef __cplusplus
}
#endif

#endif /* _INC_EBLOG_H_ */
