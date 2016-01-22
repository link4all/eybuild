
#ifndef _INC_LOGIN_H_
#define _INC_LOGIN_H_

#ifdef __cplusplus
extern "C" {
#endif

#ifdef VXWORKS
#if CPU==SIMNT
#define USR_COUNT	"host:web/usr.db"
#else
#define USR_COUNT	"/hd0/etc/usr.db"
#endif
#else
#define USR_COUNT	"usr.db"
#endif
#define USR_EXPIRE		36000

typedef struct USR_STAT {
	BOOL		login;
	char 		name[16];
	char 		passwd[16];
	char 		sex[16];
	char 		mail[32];
	char		sid[32];
} USR_STAT;

extern int check_usr_session();
extern int auth_user (char * errmsg);
extern USR_STAT * get_usrstat();
extern int diskpatch_check(EB_BLOCK * pblk, char * pname, int type);
extern int do_login(char * errmsg);
extern int do_logout();

#ifdef __cplusplus
}
#endif

#endif /* _INC_LOGIN_H_ */

