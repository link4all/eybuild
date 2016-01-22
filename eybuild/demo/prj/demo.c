/* demo.c -  */

/* Copyright XXX. */

/*
modification history
--------------------
01b, 2005-12-19, newzy add adjust the whole code for CSP.
01a, 2005-04-11, newzy author
*/

/*
DESCRIPTION


SEE ALSO
*/

/* includes */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <ebrequest.h>
#include <ebrespond.h>


int cgimain()
{
	extern EB_CSP_MAPLIST  demo_csp_maplist[];
	extern EB_ROM_MAPLIST  demo_rom_maplist[];
#if 0	/* for debug */
	int				v=0, *p1=&v, *p2=NULL;
	*p2 = 0;
#endif

    /* set debug environment */
    ebSetDebug("GET", "cgi=/demo/list.csp");
    
	/* set main-page */
	putenv("MAIN_PAGE=/demo/main.csp");

	/* respond require */
	eyBuildExec(demo_csp_maplist, demo_rom_maplist, NULL);

    return OK;
}

