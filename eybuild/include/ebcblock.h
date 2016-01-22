/* ebcblock.h - eybuild task control block */

/* Copyright(C) eyBuild Group, 2005, 2006. All Rights Reserved. */

/*
modification history
--------------------
01a, 2006-01-13, newzy   create
*/

#ifndef _INC_EBCBLOCK_H_
#define _INC_EBCBLOCK_H_

#include <ebfrm.h>
#include <ebenviron.h>

#ifdef __cplusplus
extern "C" {
#endif

/* defines */
#define EB_DEF_QUERY_NUM       	64     	/* max number */
#define EB_DEF_COOKIE_NUM      	64     	/* max number */
#define EB_DEF_MAINPAGE_LEN		256		/* default lenght */
#define EB_DEF_QUERY_LEN     	2048	/*  */
#define EB_DEF_TMPBUF_LEN     	1024	/*  */
#define EB_MAX_COOKIE_LEN     	4096	/* by protocol */

/*  */
#define EB_MAINPAGE_MAXLEN		EB_DEF_MAINPAGE_LEN

struct EB_BLOCK;
typedef struct EB_BLOCK EB_BLOCK;

typedef BOOL (*PRE_DISPATCH)(EB_BLOCK * pblk, char * pname, int type);
typedef BOOL (*POST_DISPATCH)(EB_BLOCK * pblk, char * pname, int type);
typedef BOOL (*ERR_DISPATCH)(int errnum, char * errmsg);

/* typedefs */
typedef struct EB_STAT
{
    int             options;            /* page map options */
	int				cookie_maxlen;		/* max cookie buffer length */
	int				max_cookies;		/* max cookies number */
	int				query_maxlen;		/* max query buffer length */
	int				max_querys;			/* max querys number */
	int				mainpage_maxlen;	/* max size of mainpage buffer */
	int				tmpbuf_maxlen;		/* for something tmp returned and then output, 
										 * eg: ebUrlDecode, ebUrlEncode 
										 */
	BOOL			disable_log;		/* disabe log, default log enabled */
	PRE_DISPATCH	pre_dispatch_hook;	/* previous dispatch hook */
	POST_DISPATCH   post_dispatch_hook;	/* post dispatch hook */
	ERR_DISPATCH 	error_hook;			/* send error messg */
} EB_STAT;

/* externs */
extern EB_BLOCK * getEbCBlock();
extern int ebInit(EB_STAT * pstat);
extern int ebRequestReset();
extern int ebClean();

#ifdef __cplusplus
}
#endif

#endif /* _INC_EBCBLOCK_H_ */


