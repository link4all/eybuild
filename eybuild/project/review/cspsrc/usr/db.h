
#ifndef _INC_DB_H_
#define _INC_DB_H_

#define DB_NAME		"msg.db"

typedef struct {
	char 		name[16];
	char 		sex[4];
	char 		mail[128];
	char 		now[24];
	size_t 		msg_len;
	char 		msg[512];
} RECORD;


extern void * open_db(char * mode);
extern int close_db(void * fp);
extern int db_read_next(void * fp, RECORD * rcd);
extern int db_insert(void * fp, RECORD * rcd);

#endif /* _INC_DB_H_ */

