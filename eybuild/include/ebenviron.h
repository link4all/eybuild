/* ebenviron.h - CGI environment variable header file */

/* Copyright(C) eyBuild Group, 2005, 2006. All Rights Reserved. */

/*
modification history
--------------------
02a, 2006-06-22, newzy	tidy and removed unused declaration
01a, 2006-01-13, newzy 	create
*/

#ifndef _INC_EBENVIRON_H_
#define _INC_EBENVIRON_H_

#ifdef __cplusplus
extern "C" {
#endif

/* defines */

#define AUTH_TYPE        		"AUTH_TYPE"
#define CONTENT_LENGTH   		"CONTENT_LENGTH"
#define CONTENT_TYPE     		"CONTENT_TYPE"
#define GATEWAY_INTERFACE		"GATEWAY_INTERFACE"
#define PATH_INFO        		"PATH_INFO"
#define PATH_TRANSLATED  		"PATH_TRANSLATED"
#define QUERY_STRING     		"QUERY_STRING"
#define REMOTE_ADDR      		"REMOTE_ADDR"
#define REMOTE_HOST      		"REMOTE_HOST"
#define REMOTE_IDENT     		"REMOTE_IDENT"
#define REMOTE_PORT      		"REMOTE_PORT"		/* ** */
#define REMOTE_USER      		"REMOTE_USER"
#define REQUEST_METHOD   		"REQUEST_METHOD"
#define SCRIPT_NAME      		"SCRIPT_NAME"
#define SERVER_ADDR      		"SERVER_ADDR" 		/* ** */
#define SERVER_NAME      		"SERVER_NAME"
#define SERVER_PORT      		"SERVER_PORT"
#define SERVER_PROTOCOL  		"SERVER_PROTOCOL"
#define SERVER_SOFTWARE  		"SERVER_SOFTWARE"

#define HTTP_COOKIE             "HTTP_COOKIE"      
#define HTTP_CONNECTION			"HTTP_CONNECTION"
#define HTTP_USER_AGENT         "HTTP_USER_AGENT"
#define HTTP_IF_MODIFIED_SINCE  "HTTP_IF_MODIFIED_SINCE"
#define HTTP_ACCEPT             "HTTP_ACCEPT"      
#define HTTP_ACCEPT_LANGUAGE    "HTTP_ACCEPT_LANGUAGE"                               
#define HTTP_ACCEPT_ENCODING    "HTTP_ACCEPT_ENCODING"                               


/* for compatibility with old version  */
#define getLastModified()	getHttpLastModified()


/* typedefs */

typedef struct  EB_ENVIRON
{
	char *		auth_type;
	int			content_length;
	char *		content_type;
	char *		gateway_interface;
	char *		path_info;
	char *		path_translated;
	char *		query_string;
	char *		remote_addr;
	char *		remote_host;
	char *		remote_ident;
	short		remote_port;		/* ** */
	char *		remote_user;
	char *		request_method;
	char *		script_name;
	char *		server_addr;		/* ** */
	char *		server_name;
	short		server_port;
	char *		server_protocol;
	char *		server_software;

	char *		http_cookie;
	char *		http_connection;
	char *		http_user_agent;
	char *		http_if_modified_since;
	char *		http_accept;
	char *		http_accept_language;
	char *		http_accept_encoding;
} EB_ENVIRON;


/* externs */

extern char * ebgetenv(char * varname);
extern char * getHttpHeader(char * name);

/* CGI/1.1 */
extern char * getAuthType();
extern int    getContentLength();
extern char * getContentType();
extern char * getGatewayInterface();
extern char * getPathInfo();
extern char * getPathTranslated();
extern char * getQueryString();
extern char * getRemoteAddr();
extern char * getRemoteHost();
extern char * getRemoteIdent();
extern short  getRemotePort();		/* ** */
extern char * getRemoteUser();
extern char * getRequestMethod();
extern char * getScriptName();
extern char * getServerAddr(); 		/* ** */
extern char * getServerName();
extern short  getServerPort();
extern char * getServerProtocol();
extern char * getServerSoftware();

/* HTTP HEADER */
extern char * getHttpCookie();
extern char * getHttpConnection();
extern char * getHttpUserAgent();
extern char * getHttpLastModified();
extern char * getHttpAccept();
extern char * getHttpAcceptLanguage();
extern char * getHttpAcceptEncode();

/* internal */
extern char * getRequestPageName();
extern char * getRequestPageType();
extern int initEnviron(EB_ENVIRON * penv);
extern int ebCgiInfo(FILE * fp);

#ifdef __cplusplus
}
#endif

#endif /* _INC_EBENVIRON_H_ */
