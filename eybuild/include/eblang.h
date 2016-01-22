/* eblang.c - multi-language support header file*/

/* Copyright(C) eyBuild Group, 2005, 2006. All Rights Reserved. */

/*
modification history
--------------------
01a, 2006-10-14, newzy author
*/


#ifndef _INC_EBLANG_H_
#define _INC_EBLANG_H_

#include <ebfrm.h>

#ifdef __cplusplus
extern "C" {
#endif
	
#ifndef EB_LANG_NUM
#error You should define EB_LANG_NUM before this line
#endif

/* language set list name */
#ifndef EB_LANG_SET_LIST
#define EB_LANG_SET_LIST	ebLangSetList
#endif
	
/* language element add */
#if	  (1 == EB_LANG_NUM)
#	define EB_LANG_ADD(key, v1)				{(key), {(v1)}}
#elif (2 == EB_LANG_NUM) 
#	define EB_LANG_ADD(key, v1, v2)			{(key), {(v1), (v2)}}
#elif (3 == EB_LANG_NUM) 
#	define EB_LANG_ADD(key, v1, v2, v3)		{(key), {(v1), (v2), (v3)}}
#elif (4 == EB_LANG_NUM) 
#	define EB_LANG_ADD(key, v1, v2, v3, v4)	{(key), {(v1), (v2), (v3), (v4)}}
#else
#	error "Please add EB_LANG_ADD() here manually"
#endif


/* language element add */
#define EB_MULTI_LANG_BEGIN(v1, v2)		\
		struct {						\
			char *	key;				\
			char *  value[EB_LANG_NUM];	\
		}  EB_LANG_SET_LIST [] =


/* language function for short */
#define defLangGet()	ebDefLangGet()
#define defLangSet(id)	ebDefLangSet(EB_LANG_NUM, (id))

/* get language by key */
#define lang(key)		ebLangGetByKey((EB_MULTI_LANG *)EB_LANG_SET_LIST, \
						EB_LANG_NUM, (char*)(key))
#define lang2(key)		lang(#key)

#define langInit()		ebLangInit(EB_LANG_SET_LIST)

/* typedefs */
typedef struct EB_MULTI_LANG {
	char *	key;		/* key */
	char *  value[1];	/* to dynamic increate elements */
} EB_MULTI_LANG; 


/* externs */
extern int ebDefLangGet();
extern int ebDefLangSet(unsigned maxelem, unsigned def);
extern char * ebLangGetByKey(EB_MULTI_LANG * plist, unsigned maxelem, char * key);

extern int ebLangInit(void * pset);
extern int ebLangClean(void * pset);

#ifndef GLOBAL_LANG_SET
extern EB_MULTI_LANG EB_LANG_SET_LIST[];
#endif

#ifdef __cplusplus
}
#endif

#endif /* _INC_EBLANG_H_ */
