/* db_mysql.c - where to start CGI */

/* Copyright(C) eyBuild Group, 2005, 2006. All Rights Reserved. */
/* http://www.eybuild.com */

/*
modification history
01a, 2005-04-03, newzy	writen
*/

/*
DESCRIPTION
this module is for suport mysql.
Thanks for xxt help.
	
ALSO SEE:
db.c db.h
*/
#include <stdio.h>
#include <string.h>

#include <windows.h>
#include <mysql.h>
#include <undef.h>
#include "db.h"
#include <ebdef.h>

/* database info */
typedef struct {
	char *			dbname;
	char *			table_name;
	MYSQL *			mydata;
	MYSQL_RES *		records;
} DB_INFO;


/* 
open data base 
*/
void * open_db(char * mode)
{
	DB_INFO * 		db_fp = NULL;
	
	db_fp = (DB_INFO *)malloc(sizeof(DB_INFO));
	memset(db_fp, 0, sizeof(DB_INFO));

	if ( ! (db_fp->mydata = mysql_init(NULL) ))
		return NULL;
	
	db_fp->dbname = "example";
	db_fp->table_name = "viewmsg";
	
	if (!mysql_real_connect(db_fp->mydata, NULL, "root", "xxt", 
			db_fp->dbname, MYSQL_PORT, NULL, 0 ))
		return NULL;
			
	return db_fp;
}

/* 
close data base 
*/
int close_db(void * fp)
{
	DB_INFO * 		db_fp = (DB_INFO *)fp;

	if (NULL == fp)
		return ERROR;
		
	if (db_fp->records)
		mysql_free_result(db_fp->records);
	
	if (db_fp->mydata)
		mysql_close(db_fp->mydata);
		
	free (db_fp);
	
	return OK;	
}

/* 
read record from base 
*/
int db_read_next(void * fp, RECORD * rcd)
{
	DB_INFO * 		db_fp = (DB_INFO *)fp;
	MYSQL_ROW		row;

	/* get records from server */
	if (NULL==db_fp)
		return ERROR;
		
	if (NULL==db_fp->records)
	{
		char 			strsql[256] = ""; 
		 
		sprintf (strsql, "select * from %s", db_fp->table_name);
		if (mysql_query(db_fp->mydata, strsql) ) 
		{ 
			close_db(db_fp); 
			return ERROR; 
		}
		
		db_fp->records = mysql_store_result(db_fp->mydata); 
	}

	/* read one record */
	row = mysql_fetch_row(db_fp->records);
	if (NULL == row)	/* end of records */
		return 0;
		
	strcpy(rcd->name, row[1]);
	strcpy(rcd->sex, row[2]);
	strcpy(rcd->mail, row[3]);
	strcpy(rcd->now, row[4]);
	strcpy(rcd->msg, row[5]);
	rcd->msg_len = strlen(rcd->msg);
	
	return sizeof(RECORD);
}

/* 
insert record to data base 
*/
int db_insert(void * fp, RECORD * rcd)
{
	DB_INFO * 		db_fp = (DB_INFO *)fp;
	char 			strsql[sizeof(RECORD)] = ""; 
	
	/* get records from server */
	if (NULL==db_fp || NULL==db_fp->mydata)
		return ERROR;
		
	sprintf(strsql, 
			"insert into %s (name,sex,email,date,content) "
			"values('%s', '%s', '%s', '%s', '%s')",
			db_fp->table_name,
			rcd->name,
			rcd->sex,
			rcd->mail,
			rcd->now,
			rcd->msg
			); 
	
	if (mysql_query(db_fp->mydata, strsql) ) 
	{ 
		close_db(db_fp); 
		return ERROR; 
	}
		
	return sizeof(RECORD);
}

