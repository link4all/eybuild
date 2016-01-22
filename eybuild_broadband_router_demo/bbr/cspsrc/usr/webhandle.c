/* webhandle.c - CGI background process routines */

/* Copyright(C) eyBuild Group, 2005, 2006. All Rights Reserved. */

/*
modification history
--------------------
01a, 2006-03-22, newzy author
*/

/*
DESCRIPTION
CGI background process routines 
*/

#include <stdio.h>
#include <string.h>
#include <eblib.h>
#include "webhandle.h"

/***************************************************************************
* do_login - auth user
* 
* this routine is a hook, while request a virtual file, 
* this routine will be call.
*
* RETURN: TRUE/FALSE
*/ 

int do_login(void * pblock, char * pname, int type)
{
	char *				puser = getCookie("username");
	char *				pid   = getCookie("session_id");
	BROADBAND_ROUTER 	bbr[1];
	char				errmsg[256] = "";

	load_bbr(bbr, errmsg);
	
	/* have been login */
	if (!isblankstr(puser) && !isblankstr(pid) &&
		!strcmp(puser, bbr->account.user) && 
		!strcmp(pid, bbr->account.session_id))			
		return FALSE;

	/* just login.csp */
	if (!strcmp(pname, "/login.csp"))
		return FALSE;

	/* redirect to login.csp */
	redirect("%s%s", cgiPrefix(NULL), "/login.csp");
	
	return TRUE;
}	


int make_default_config(BROADBAND_ROUTER * bbr, char * errmsg)
{
	memset(bbr, 0, sizeof(*bbr));
	memset(errmsg, 0, 256);

	strcpy(bbr->lan.ip, "192.168.1.1");
	strcpy(bbr->lan.ipmask, "255.255.0.0");
	strcpy(bbr->mac.lan_mac, "00-0A-EB-B2-6B-D8");
	strcpy(bbr->mac.wan_mac, FACTORY_WAN_MAC);
	strcpy(bbr->mac.pc_mac, "00-00-00-00-00-00");
	strcpy(bbr->wan.ip, "0.0.0.0");
	strcpy(bbr->wan.ipmask, "0.0.0.0");
	strcpy(bbr->wan.connect_mode, "2");
	bbr->pppoe.mtu = 1492;
	bbr->dhcps.enable = 1;
	strcpy(bbr->dhcps.main_dsn_server, "202.96.209.5");
	strcpy(bbr->dhcps.backup_dsn_server, "211.116.192.7");
	strcpy(bbr->dhcps.pool_start, "192.168.1.100");
	strcpy(bbr->dhcps.pool_end, "192.168.1.199");
	bbr->dhcps.lease = 120;
	bbr->ip_filter.ip_filter_allow_all = TRUE;
	bbr->ip_filter.mac_filter_allow_added = TRUE;
	bbr->rmanage.wan_port = 8080;
	strcpy(bbr->rmanage.remote_manage_host, "255.255.255.255");

	strcpy(bbr->account.user, "user");
	strcpy(bbr->account.passwd, "user");
	strcpy(bbr->account.session_id, "0123456789");
	
	return save_bbr(bbr, errmsg);
}

int save_bbr(BROADBAND_ROUTER * bbr, char * errmsg)
{
	FILE *		fp;

	/* open error */
	if (NULL == (fp=fopen(CONFIG_FILE, "wb")))
	{
		return ERROR|
		sprintf(errmsg, "Make default configuration error.");
	}

	fwrite(bbr, 1, sizeof(*bbr), fp);

	fclose(fp);
	return OK;
}

int load_bbr(BROADBAND_ROUTER * bbr, char * errmsg)
{
	FILE *		fp;

	memset(bbr, 0, sizeof(*bbr));
	memset(errmsg, 0, 256);

	/* open error */
	if (NULL == (fp=fopen(CONFIG_FILE, "rb")))
	{
		return make_default_config(bbr, errmsg);
	}

	/* read error */
	if ( sizeof(*bbr) != fread(bbr, 1, sizeof(*bbr), fp) )
	{
		fclose(fp);
		return make_default_config(bbr, errmsg);
	}
	
	fclose(fp);
	return OK;
}
