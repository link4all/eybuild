/* ebrequest.h - CGI request process */

/* Copyright(C) eyBuild Group, 2005, 2006. All Rights Reserved. */

/*
modification history
--------------------
01a, 2006-01-13, newzy   create
*/

#ifndef _INC_EBREQUEST_H_
#define _INC_EBREQUEST_H_

#include <ebhandle.h>	/* not must */
#include <ebcblock.h>	/* dependence */

#ifdef __cplusplus
extern "C" {
#endif

/* execute eybuild */
#define eyBuildExec(lst1, lst2, env)	\
		eyBuildExec2(	\
		(lst1), (lst1) ? sizeof(lst1): 0,  \
		(lst2), (lst2) ? sizeof(lst2): 0, \
		(env))


/* the URL of this page */
#define thisCgiPrefix() \
		cgiPrefix2(NULL, __page_fullname)


/* parameter pair */
typedef struct PARAM_PAIR
{
    char *		name;		/* parameter name */
    char *      value;      /* parameter value */
} PARAM_PAIR;

/* to handle request parameters */
typedef struct CGI_REQUEST
{
    int             counter;	/* count of  */
    char *          databuf;	/* data buffer */
    PARAM_PAIR *	paralist;	/* list */
} CGI_REQUEST;    


/* eybuild control block */
struct EB_BLOCK	
{
	EB_STAT 		stat;
    EB_ENVIRON		env;
    CGI_REQUEST		query;      /* count of  */
    CGI_REQUEST		cookie;     /* count of  */
    char *			mainpage;	/* main page */
    char *			tmpbuf;		/* tmp buffer */
    void *			ebiofp;		/* ebio file pointer */
	void *			csplist;	/* csp map list */
	int				cspsize;	/* size of csp list */
	void *			romlist;	/* csp map list */
	int				romsize;	/* size of csp list */
	void *			resloved;	/* resloved */
};    


/* externs */
extern char * cgiPrefix(char * pname);
extern char * romPrefix(char * pname);

extern char * cgiPrefix2(char * pname, char * psub);
extern char * romPrefix2(char * pname, char * psub);

/* querys */
extern BOOL	  isSetQuery(char * name);
extern char * getParameter(char * name);
extern char * getParameterNext(char * name, int * pindex);
extern int	  getQeuryNumber();
extern char * getQeuryByIndex(char ** pname, int index);

/* cookies */
extern BOOL	  isSetCookie(char * name);
extern char * getCookie(char * name);
extern char * getCookieNext(char * name, int * pindex);
extern int	  getCookieNumber();
extern char * getCookieByIndex(char ** pname, int index);

#ifdef __cplusplus
}
#endif

#endif /* _INC_EBREQUEST_H_ */


