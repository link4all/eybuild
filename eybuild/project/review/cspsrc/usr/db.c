
#include <stdio.h>
#include <string.h>

#include "db.h"

/* 
open data base 
*/
void * open_db(char * mode)
{
	FILE * 		fp;
	
	fp = fopen(DB_NAME, mode);
	
	return fp;
}

/* 
close data base 
*/
int close_db(void * fp)
{
	if (NULL != fp)
		fclose(fp);
	
	return 0;	
}

/* 
read record from base 
*/
int db_read_next(void * fp, RECORD * rcd)
{
	size_t		len;
	
	if (NULL == fp)
		return -1;
		
	if (feof((FILE*)fp))
		return 0;
	
	memset(rcd, 0, sizeof(RECORD));
	
	/* read header */
	len = sizeof(RECORD) - sizeof(rcd->msg);
	if (len != (int)fread(rcd, 1, len, fp))
		return -1;
	
	/* read message body */
	if (rcd->msg_len != fread(rcd->msg, 1, rcd->msg_len, (FILE*)fp))
		return -1;
	
	return sizeof(RECORD);
}

/* 
insert record to data base 
*/
int db_insert(void * fp, RECORD * rcd)
{
	size_t		len;
	
	if (NULL == fp || fseek(fp, 0, SEEK_END))
		return -1;
	
	/* write header */
	rcd->msg_len = strlen(rcd->msg);
	len = sizeof(RECORD) - sizeof(rcd->msg);
	
	if (len != fwrite(rcd, 1, len, (FILE*)fp))
		return -1;
	
	/* write message body */
	if (rcd->msg_len != (fwrite(rcd->msg, 1, rcd->msg_len, (FILE*)fp)))
		return -1;
	
	return sizeof(RECORD);
}

