/* cgimain.c - where to start CGI */

/* Copyright(C) eyBuild Group, 2005, 2006. All Rights Reserved. */

/*
modification history
--------------------
02a, 2006-03-22, newzy change file name to cspmain.c
01b, 2005-12-19, newzy add adjust the whole code for CSP.
01a, 2005-04-11, newzy author
*/

/*
DESCRIPTION
CGI process always start from cgimain(), user can set the default 
web page(or main page) by set the environment "EBENV_MAIN_PAGE",
or debug a specified page by call ebSetDebug().

*/

/* includes */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ebrequest.h>
#include <ebrespond.h>

#include <cgimain.h>
#ifdef HAVE_CSP_ENGINE
#include <cspsrc/csp_maplist.h>
#define rom_maplist NULL
#else
#include "/cspsrc/csp_maplist.h"
//#include "cspsrc/rom_maplist.h
#endif

#undef  CGI_ENTRY 
#define CGI_ENTRY	dll_entry

/* set debug break in VC++ */
#define EXCEPTION_DEBUG		0

int cgimain()
{
	EB_STAT			stat;
#if EXCEPTION_DEBUG
	int				v=0, *p1=&v, *p2=NULL;
	*p2 = 0;
#endif
	
	/* for test */
	memset(&stat, 0, sizeof(EB_STAT));
	stat.options |= EB_OPT_ROM_LOCAL_FS;
	stat.options |= EB_OPT_IDMAP_ENABLE;

	if (OK != ebInit(&stat))
		return ERROR;

#ifdef HAVE_FASTCGI
    BEGIN_FASTCGI_LOOP();
#endif /* HAVE_FASTCGI */

	/* respond require */
	eyBuildExec(csp_maplist, /*rom_maplist*/NULL, NULL);

#ifdef HAVE_FASTCGI
    END_FASTCGI_LOOP();
#endif /* HAVE_FASTCGI */

    return OK;
}

