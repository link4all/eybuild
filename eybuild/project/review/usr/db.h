
#ifndef _INC_DB_H_
#define _INC_DB_H_

#ifdef __cplusplus
extern "C" {
#endif

#ifdef LINUX
#define DB_NAME		"/tmp/msg.db"
#elif VXWORKS
#if CPU==SIMNT
#   define DB_NAME	"host:web/msg.db"
#else
#   define DB_NAME	"/hd0/web/msg.db"
#endif
#else
#define DB_NAME		"msg.db"
#endif


#define MSG_MAXLEN	512

typedef struct {
	char 		name[16];
	char 		sex[16];
	char 		mail[32];
	char 		now[24];
	size_t 		msg_len;
	char 		msg[MSG_MAXLEN];
} RECORD;


extern void * open_db(char * mode);
extern int close_db(void * fp);
extern int db_read_next(void * fp, RECORD * rcd);
extern int db_insert(void * fp, RECORD * rcd);

#ifdef __cplusplus
}
#endif

#endif /* _INC_DB_H_ */

