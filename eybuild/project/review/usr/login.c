
#include <stdio.h>
#include <string.h>

#include <ebrequest.h>
#include <ebrespond.h>
#include "login.h"

static USR_STAT		usr_stat;
static USR_STAT *	pusr = &usr_stat;

/*
get user stat
*/
USR_STAT * get_usrstat()
{
	return pusr;
}

/*
do login
*/
int do_login(char * errmsg) 
{
	/* have been login */
	if (pusr->login)
	{
		redirect("%s", cgiPrefix2(NULL, "/review/logout.csp"));
		return OK;
	}
	
	if (OK == auth_user(errmsg))
	{
		/* login OK */
		setcookie("usrname", G("usrname")/*, time(NULL)+3600*/, NULL);
		setcookie("sid", pusr->sid/*, time(NULL)+3600*/, NULL);
#ifdef HAVE_CSP_ENGINE
		print("<meta http-equiv=\"refresh\" content=\"1; url=%s\">", 
				cgiPrefix2(NULL, "/review/review.csp"));
		print("</HEAD>\n<BODY>登录成功, 正在跳转...</BODY>\n");
#else		
		redirect("%s", cgiPrefix2(NULL, "/review/review.csp"));
#endif
		return OK;
	}
	
	return ERROR;
}

/*
do login
*/
int do_logout() 
{
	/* not login */
	if (!pusr->login)
	{
		redirect("%s", cgiPrefix2(NULL, "/review/login.csp"));
		return OK;
	}
	
	if ('\0' != G("logout")[0])
	{
		setcookie("usrname", "", time(NULL)-3600, NULL);
		setcookie("sid", "", time(NULL)-3600, NULL);
		
#ifdef HAVE_CSP_ENGINE
		print("<meta http-equiv=\"refresh\" content=\"1; url=%s\">", 
				cgiPrefix2(NULL, "/review/login.csp"));
		print("</HEAD>\n<BODY>正在登出...</BODY>\n");
#else		
		redirect("%s", cgiPrefix2(NULL, "/review/login.csp"));
#endif
		return OK;
	}
	
	return ERROR;
}

/*
diskpatch check
*/
int diskpatch_check(EB_BLOCK * pblk, char * pname, int type)
{
	char 				ppage[256] = "";

	/* cache control */
	header("Cache-Control: no-cache; no-store\n");	/* for HTTP/1.1 */
	header("Expires: Thu, 19 Nov 1981 08:52:00 GMT\n"); 
	header("Pragma: no-cache\n");			/* for HTTP/1.0 */

	/* have login */
	if (OK == check_usr_session())			
		return FALSE;

	/* just login.csp */
	strcpy(ppage, cgiPrefix2(NULL, pname));
	if (!strcmp(ppage, cgiPrefix2(NULL, "/review/login.csp")))
		return FALSE;

	/* redirect to login.csp */
	redirect("%s", cgiPrefix2(NULL, "/review/login.csp"));
	return TRUE;
}	

/*
check usr session
*/
int check_usr_session()
{
	char *		pname = getCookie("usrname"); 
	char *		psid = getCookie("sid");
	FILE *		fp;

	/* init */
	pusr->login = FALSE;
	memset(pusr, 0, sizeof(*pusr));
	
	/* miss name or sid */
	if ('\0' == pname[0] || '\0' == psid[0])
	{
		return ERROR;
	}
	
	if (NULL == (fp=fopen(USR_COUNT, "rb")))
		return ERROR;
		
	while(!feof(fp))
	{
		char	linebuf[256] = "";
		char *	pstr;
		int		ret = 0;
		
		/* read db */
		if (NULL == (pstr=fgets(linebuf, sizeof(linebuf), fp)))
			break;

		pstr += strspn(pstr, "\t\x20\n\r");	// jump over space
		if ('\0' == *pstr || '#' == *pstr)	// jump over blank line or commont
			continue;

		/* extract user info */
		ret = sscanf(linebuf, "%s%s%s%s%s", 
			pusr->name, pusr->passwd, pusr->sex, pusr->mail, pusr->sid);
		if (5 != ret)
		{
			fclose(fp);
			return ERROR;
		}
		
		/* check */
		if (!strcmp(pusr->name, pname) && !strcmp(pusr->sid, psid))
		{
			pusr->login = TRUE;
			fclose(fp);
			return OK;
		}
	}
	
	fclose(fp);

	return ERROR;
}
	

/*
auth user
*/
int auth_user (char * errmsg)
{
	char *		pname = G("usrname"); 
	char *		ppswd = G("passwd"); 
	FILE *		fp;
	
	/* miss name or sid */
	if ('\0' == pname[0] || '\0' == ppswd[0])
	{
		sprintf(errmsg, "Please login");
		return ERROR;
	}
	
	if (NULL == (fp=fopen(USR_COUNT, "rb")))
	{
		sprintf(errmsg, "Can not open user DB: %s\n", USR_COUNT); 
		return ERROR;
	}
		
	while(!feof(fp))
	{
		char	linebuf[256] = "";
		char *	pstr;
		int		ret = 0;
		
		/* read db */
		if (NULL == (pstr=fgets(linebuf, sizeof(linebuf), fp)))
			break;

		pstr += strspn(pstr, "\t\x20\n\r");	// jump over space
		if ('\0' == *pstr || '#' == *pstr)	// jump over blank line or commont
			continue;

		/* extract user info */
		ret = sscanf(linebuf, "%s%s%s%s%s", 
			pusr->name, pusr->passwd, pusr->sex, pusr->mail, pusr->sid);
		if (5 != ret)
		{
			fclose(fp);
			return ERROR;
		}

		/* check */
		if (!strcmp(pusr->name, pname) && !strcmp(pusr->passwd, ppswd))
		{
			pusr->login = TRUE;
			return OK;
			fclose(fp);
		}
	}
	
	sprintf(errmsg, "No such user: %s", pname);

	fclose(fp);
	return ERROR;
}



