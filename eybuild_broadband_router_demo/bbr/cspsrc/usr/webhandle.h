/* webhandle.h - CGI background process routines */

/* Copyright(C) eyBuild Group, 2005, 2006. All Rights Reserved. */

/*
modification history
--------------------
01a, 2006-03-22, newzy author
*/

#ifndef _INC_WEBHANDLE_H_
#define _INC_WEBHANDLE_H_

#include <stdlib.h>
#include <ebfrm.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifdef VXWORKS
#if CPU==SIMNT
#define CONFIG_PATH 	"host:web/"
#else
#define CONFIG_PATH 	"/hd0/tmp/"
#endif
#elif defined(LINUX)
#define CONFIG_PATH 	"/tmp/"
#else
#define CONFIG_PATH 	
#endif

/* configure file path and name */
#define CONFIG_FILE		CONFIG_PATH "bbr.cfg"

#define BBR_VERSION		"V1.0.0"


#define ERROR_LEVEL_ERROR		(-1)
#define ERROR_LEVEL_NONE		0
#define ERROR_LEVEL_WARNING		1

#define MAX_DHCP_STATIC_HOST_NUM	32
#define MAX_VIRTUAL_HOST_NUM		32
#define MAX_SPECIAL_APP_NUM			8
#define MAX_STATIC_ROUTER_NUM		8

#define WAN_TYPE_DYNAMIC_IP		"dynamic_ip"
#define WAN_TYPE_STATIC_IP		"static_ip"
#define WAN_TYPE_PPPOE			"pppoe"

#define FACTORY_WAN_MAC			"00-0B-EB-B2-6B-D8"

/* LAN setting */
typedef struct {
	char		ip[16];
	char		ipmask[16];
} LAN_SETTING;

/* WAN setting */
typedef struct {
	char		ip[16];
	char		ipmask[16];
	char		gateway[16];
	char		wan_type[16];		
	char		account[32];
	char		password[32];
	char		connect_mode[16];	
	int			auto_wait_time;
	int			manual_wait_time;
} WAN_SETTING;

/* PPPoE setting */
typedef struct {
	int			mtu;
	char		server_name[16];
	char		service_name[16];		
	BOOL		use_isp_ip;
	char		isp_ip[16];
	int			interval;	
	BOOL		manual_set_dns;
} PPPOE_SETTING;


/* IP_FILETER setting */
typedef struct {
	BOOL		firewall_enable;
	BOOL		ip_filter_enable;
	BOOL		ip_filter_allow_all;	/* all all through */
	BOOL		domain_filter_enable;		
	BOOL		mac_filter_enable;
	BOOL		mac_filter_allow_added;	
	            /* only alow what that has been added into table */
} IP_FILETER;

/* MAC setting */
typedef struct {
	char		wan_mac[20];	/* WAN port */
	char		lan_mac[20];	/* WAN port */
	char		pc_mac[20];		/* local PC */
} MAC_SETTING;

/* DHCP server setting */
typedef struct {
	BOOL		enable;
	char		pool_start[16];	/* IP address pool */
	char		pool_end[16];	/* IP address pool */
	int			lease;
	char		default_gateway[16];
	char		default_dsn[32];
	char		main_dsn_server[16];
	char		backup_dsn_server[16];
} DHCPS_SETTING;

/* DHCP stiatic hosts by MAC address */
typedef struct {
	char		mac[20];
	char		ip[16];
} DHCPS_STATIC;

/* virtual host */
typedef struct {
	char		server_port[8];
	char		server_ip[16];
	char		protocol[8];
	int			enable;
	int			general_port;
	int			id; 
} VIRTUAL_HOST;

/* special applications */
typedef struct {
	int			trigger_port;
	char		trigger_protocol[8];
	char		port_list[32];
	char		protocol[8];
	int			enable;
} SPECIAL_APP;

/* DMZ host */
typedef struct {
	char		ip[16];
	int			enable;
} DMZ_HOST;

/* DMZ host */
typedef struct {
	int  		wan_port;
	char		remote_manage_host[16];
} REMOTE_MANAGE;

/* DMZ host */
typedef struct {
	BOOL		enable;
	char		dest_ip[16];
	char		mask[16];
	char		gateway[16];
} STATIC_ROUTE;

/* DMZ host */
typedef struct {
	char		user[16];
	char		passwd[16];
	char		session_id[16];
} USER_ACCOUNT;

typedef struct {
	LAN_SETTING			lan;
	WAN_SETTING			wan;
	MAC_SETTING			mac;
	DHCPS_SETTING		dhcps;
	DMZ_HOST			dmz;
	REMOTE_MANAGE		rmanage;
	IP_FILETER			ip_filter;
	DHCPS_STATIC 		static_dhcps[MAX_DHCP_STATIC_HOST_NUM];
	VIRTUAL_HOST		virtual_host[MAX_VIRTUAL_HOST_NUM];
	SPECIAL_APP			special_app[MAX_SPECIAL_APP_NUM];
	STATIC_ROUTE		static_route[MAX_STATIC_ROUTER_NUM];
	PPPOE_SETTING		pppoe;
	BOOL				disable_wan_ping; /* disable ping from wan */
	USER_ACCOUNT		account;
} BROADBAND_ROUTER;

extern int load_bbr(BROADBAND_ROUTER * bbr, char * errmsg);
extern int save_bbr(BROADBAND_ROUTER * bbr, char * errmsg);
extern int make_default_config(BROADBAND_ROUTER * bbr, char * errmsg);
extern int do_login(void * pblock, char * pname, int type);

#ifdef __cplusplus
}
#endif

#endif /* _INC_WEBHANDLE_H_ */

