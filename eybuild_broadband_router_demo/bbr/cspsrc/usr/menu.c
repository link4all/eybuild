/* menu.c - GUI menu control */

/* Copyright(C) eyBuild Group, 2005, 2006. All Rights Reserved. */

/*
modification history
--------------------
01a, 2005-12-3, newzy author
*/

/*
DESCRIPTION
GUI menu control
*/

#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <ebrequest.h>
#include <ebrespond.h>
#include <menu.h>

/* net */
MENU_NODE menu_net[] = {
	{"/network/lan_setting.csp", "LAN������"}, 
    {"/network/wan_setting.csp", "WAN������"}, 
	{"/network/mac_setting.csp", "MAC��ַ��¡"}, 
    };

/* dhcp */
MENU_NODE menu_dhcp[] = {
    {"/dhcp/server.csp", "DHCP����"}, 
    {"/dhcp/clients.csp", "�ͻ����б�"}, 
	{"/dhcp/fixmap.csp", "��̬��ַ����"}, 
    };

/* nat */   
MENU_NODE menu_nat[] = {
    {"/nat/virtualserver.csp", "���������"}, 
    {"/nat/special_app.csp", "����Ӧ�ó���"}, 
	{"/nat/dmz.csp", "DMZ����"}, 
	{"/nat/upnp.csp", "UPnP����"}, 
	};

/* security */
MENU_NODE menu_security[] = {
    {"/security/firewall.csp", "����ǽ����"}, 
//    {"/security/ipfilter.csp", "IP��ַ����"}, 
	{"/security/domainfilter.csp", "��������"}, 
	{"/security/macfilter.csp", "MAC��ַ����"}, 
	{"/security/remoteweb.csp", "Զ��WEB����"}, 
	{"/security/ping.csp", "WAN��Ping"}, 
	};

/* static route */
MENU_NODE menu_route[] = 
    {{"/route/static.csp", "��̬·�ɱ�"}, };

/* system */
MENU_NODE menu_system[] = {
    {"/system/upgrade.csp", "�������"}, 
    {"/system/restore.csp", "�ָ���������"}, 
	{"/system/reboot.csp", "����·����"}, 
	{"/system/account.csp", "�޸ĵ�¼����"}, 
	{"/system/log.csp", "ϵͳ��־"} };

#define NV(name)  ARRAYNUM(name), &name[0]
MENU_MANI_NODE  menu_list[] = 
{ 
    {{"/basic/status.csp", 			"����״̬"},    0, NULL}, 
    {{"/basic/guide.csp", 			"������"},    0, NULL}, 
    {{"/network/lan_setting.csp", 	"�������"},    NV(menu_net)}, 
    {{"/dhcp/server.csp", 			"DHCP������"},  NV(menu_dhcp)}, 
    {{"/nat/virtualserver.csp", 	"ת������"},    NV(menu_nat)}, 
    {{"/security/firewall.csp", 	"��ȫ����"},    NV(menu_security)}, 
    {{"/route/static", 				"·�ɹ���"},    NV(menu_route)}, 
    {{"/system/upgrade.csp", 		"ϵͳ����"},    NV(menu_system)},
};
#undef NV


int check_id (unsigned  mid, unsigned  sid)
{
    /* invalid main id */
    if (mid >= sizeof(menu_list)/sizeof(menu_list[0]))
    {
        ebSendError(400, "main_id %d is too big.", mid);           
        return -1;
    }
    
    /* no such sub node */
    if (sid >= menu_list[mid].sub_num && 0 != sid)
    {
        ebSendError(400, "sub_id %d is too big.", sid);
        return -1;
    }
    
	return 0;
}

/* return the URL of the main-frame-page
 * if "" = MainID or "" == "SubID" then output default page.
 * result must as following format:
 * /cgi-bin/bbr.cgi?cgi=Status
 */

int menu_get_page(void * fp, char * MainID, char * SubID)
{
    unsigned        mid = 0;		// main ID
    unsigned        sid = 0;		// sub ID
	//char			cginame[256] = "";
	char *			prefix;

	prefix = cgiPrefix(NULL);

    /* output the default page */    
    if ('\0' == MainID[0] || '\0' == SubID[0])
    {
        print("%s/network/lan_setting.csp", prefix);
        return OK;
    }
    
    /* get mainId and subId */
    mid = MainID[0] - 'A';
    sid =  SubID[0] - '0';
	if (-1 == check_id(mid, sid))
		return ERROR;
    
    if (NULL == menu_list[mid].subnode)
    {
		print("%s%s", prefix,
				menu_list[mid].node.pagename);
    }
    else
	{
		/* all right */    
		print("%s%s", prefix,
				menu_list[mid].subnode[sid].pagename);
	}
	
	return OK;
}


/* update menu and sub menu
*
*/
int menu_update(void * fp, char * MainID, char * SubID)
{
	//char			rom_base[256] = "";
	char *			rom_base = NULL;
    unsigned        mid = 0;		// main ID
    unsigned        sid = 0;		// sub ID
	unsigned		i;
	int				j;

    /* get mainId and subId */
    mid = MainID[0] - 'A';
    sid =  SubID[0] - '0';

	/* out of range,
	 * set to default to : network/lansetting
	 */
	if ( mid >= 8) 
	    mid = 2, sid = 0;

	rom_base = romPrefix(NULL);

	for (i=0; i<ARRAYNUM(menu_list); i++)
	{
		/* expand sub node */
		print(
		"  <TR>\n"
		"	<TD class=onelevelsp width=10><IMG height=10 src=\"%s/rom/%s.gif\"\n" 
		"	  width=10></TD>\n"
		"	<TD class=onelevelsp colSpan=2 width=130><A class=tp1 href=\"\"\n"
		"	  onclick=\"return OnHrefClick('%c', '0');\"\n" 
		"	  onmouseover=\"return ResetStatus('%s');\">%s%s%s</A></TD></TR>\n",
		rom_base,
		menu_list[i].subnode ? (mid==i ? "minus": "plus"): "pw",	// has sub node or not
		'A'+i, 
		menu_list[i].node.descripion, 
		((int)mid == i) ? "<FONT color=#ff0000>": "",
		menu_list[i].node.descripion,
		((int)mid == i) ? "</FONT>": ""
		);

		if (mid != i)
			continue;
		
		for (j=0; j<(int)menu_list[i].sub_num; j++)
		{
			print(
			"  <TR>\n"
			"	<TD class=twolevel width=10><IMG height=10 src=\"%s/rom/sp.gif\"\n" 
			"	  width=10></TD>\n"
			"   <TD class=twolevel vAlign=center width=10><IMG height=10\n"
			"     src=\"%s/rom/pw.gif\" width=10></TD>\n"
			"	<TD class=twolevel width=120><A class=tp2 href=\"\"\n"
			"	  onclick=\"return OnHrefClick('%c', '%d');\"\n" 
			"	  onmouseover=\"return ResetStatus('%s');\">"
			"%s%s%s</A></TD></TR>\n",
			rom_base,
			rom_base,
			'A'+i, 
			j, 
			menu_list[i].subnode[j].descripion, 
				((int)sid == j) ? "<FONT color=#ff0000>": "",
			menu_list[i].subnode[j].descripion,
				((int)sid == j) ? "</FONT>": ""
			);
		}
	}

	return OK;
}



