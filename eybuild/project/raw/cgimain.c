/* cgimain.c - where to start CGI */

/* Copyright(C) eyBuild Group, 2005, 2006. All Rights Reserved. */

/*
modification history
--------------------
02b, 2006-03-25, newzy creat raw cgi
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

/* For GoAhead webServer link internal */
#if defined(VXWORKS) && defined(GOAHEAD)
#	undef  CGI_ENTRY
#	define CGI_ENTRY	raw_cgientry
#endif /* VXWORKS && GOAHEAD */


/* set debug break in VC++ */
#define EXCEPTION_DEBUG		0

int cgimain()
{
#if EXCEPTION_DEBUG
	int				v=0, *p1=&v, *p2=NULL;

	*p2 = 0;
#endif
	int		cnt =0;

    /* set debug environment */
    ebSetDebug("GET", "result=false");

#ifdef HAVE_FASTCGI
    BEGIN_FASTCGI_LOOP();
#endif /* HAVE_FASTCGI */

    /* set debug environment */
	printf("Content-Type: text/html\n\n");
    cnt ++;

	if ( 0 != strcmp("true", getParameter("result")) )
	{
		printf("<html>\n<body>\n");
		printf("cnt= %d<br>\n", cnt);
		printf("<H2>This is a cgi test.</H2 >\n");
		printf("<form action=\"%s?result=true\" method=post>\n", getScriptName());
		printf("<p>Input: <input type=text name=\"inputbox1\"></p>\n");
		printf("<p>Choose: \n");
		printf("<select name=\"choosebox1\">\n");
		printf("  <option value=\"Good Luck\">Good Luck</option>\n");
		printf("  <option value=\"Hello world\">Hello world</option>\n");
		printf("  <option value=\"Bye bye\">Bye bye</option>\n");
		printf("</select>\n");
		printf("</p>\n");
		printf("<p><input type=submit value=\"submit\"></p>\n");
		printf("</form>\n");
		printf("</body>\n</html>\n");
	}
	else
	{
		printf("<html>\n<body>\n");
		printf("cnt= %d<br>\n", cnt);
		printf("<p>What you input is: <b>%s</b></p>\n", getParameter("inputbox1"));
		printf("<p>What you choose is: <b>%s</b></p>\n", getParameter("choosebox1"));
		printf("<p><A href=\"%s\">Return</A></p>\n", getScriptName());
		printf("</body>\n</html>\n");
	}

#ifdef HAVE_FASTCGI
	END_FASTCGI_LOOP();
#endif /* HAVE_FASTCGI */

    return OK;
}

