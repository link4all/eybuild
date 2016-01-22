/* ebquery.h - handle query and cookie then parse it */

/* Copyright(C) eyBuild Group, 2005, 2006. All Rights Reserved. */

/*
modification history
--------------------
01a, 2006-01-13, newzy   create
*/

#ifndef _INC_EBQUERY_H_
#define _INC_EBQUERY_H_

#include <ebfrm.h>
#include <ebenviron.h>

#ifdef __cplusplus
extern "C" {
#endif

/* externs */
extern int ebParseQuery(EB_BLOCK * pblk);
extern int ebParseCookie(EB_BLOCK * pblk);

#ifdef __cplusplus
}
#endif

#endif /* _INC_EBQUERY_H_ */


