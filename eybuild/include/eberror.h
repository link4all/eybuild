/* eberror.h - eybuild errors header file */

/* Copyright(C) eyBuild Group, 2005, 2006. All Rights Reserved. */

/*
modification history
--------------------
01b, 2006-04-09, newzy   support fastcgi
01a, 2005-12-25, newzy   create
*/

#ifndef _INC_EBERROR_H_
#define _INC_EBERROR_H_

#ifdef HAVE_FASTCGI
#   include <fcgi_stdio.h>
#else
#   include <stdio.h>
#endif /* HAVE_FASTCGI */

#include <eblog.h>

#ifdef __cplusplus
extern "C" {
#endif

/* note 'msg' must be add () */
#define ebSendErrorLog(errnum, msg)	{		\
		ebLogMsg(EBLOG_ERROR, ebMakeMsg msg);	\
		ebSendError(errnum, ebMakeMsg msg);		\
		}

extern const char * ebHttpError(int errnum);
extern int ebSendError (int errnum, char * errfmt, ...);

#ifdef __cplusplus
}
#endif

#endif /* _INC_EBERROR_H_ */
