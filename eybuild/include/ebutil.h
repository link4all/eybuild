/* ebutil.h - eybuild logs header file */

/* Copyright(C) eyBuild Group, 2005, 2006. All Rights Reserved. */

/*
modification history
--------------------
01b, 2006-04-09, newzy   support fastcgi
01a, 2005-12-25, newzy   create
*/

#ifndef _INC_EBUTIL_H_
#define _INC_EBUTIL_H_

#include <ebdef.h>

#ifdef __cplusplus
extern "C" {
#endif


/* check c name */	
#define is_c_name_charactor(c)	\
			(					\
			('a'<=(c) && 'z'>=(c)) ||	/* a-z */	\
			('A'<=(c) && 'Z'>=(c)) ||	/* A-Z */	\
			('0'<=(c) && '9'>=(c)) ||	/* 0-9 */	\
			('_' == (c)) 				/* _ */		\
			)

/* 
 */
#undef I2A
#undef ITOA
#define I2A(d)		ebI2A(d)
#define ITOA(d)		ebI2A(d)
		

/* extern */
extern int list_environ();
extern int memshow(void * pstart, size_t size);

extern char * get_filename(char * fullname);
extern char * trimspace(char ** ppstart, char **ppend);

extern BOOL isblankstr(char * pstr);
extern int strcmpin(char *s1, char *s2, int n);
extern char * make_c_name(char * pname);
extern char * ebI2A(int num);

#ifdef __cplusplus
}
#endif

#endif /* _INC_EBFRAME_H_ */
