/* ebbuff.h - buffer header file */

/* Copyright(C) eyBuild Group, 2005, 2006. All Rights Reserved. */

/*
modification history
--------------------
01a, 2006-01-13, newzy   create
*/

/* ebuild in/out */
#ifndef _INC_EBBUFF_H_
#define _INC_EBBUFF_H_

#include <stdarg.h>
#include <ebfrm.h>

#ifdef __cplusplus
extern "C" {
#endif

/* defines */
#define EB_BUFF_SIZE	4096    /* default size, 4k */

/* typedefs */
typedef enum {
	EB_CONST = 1,	/* const data table */
	EB_LOCAL = 2	/* local data */
} EB_TLV_TYPE;

typedef struct EB_TLV
{
	int				type;	/* data type */
    int             len;    /* data length */
} EB_TLV;

/* cache buffer for output */
typedef struct eb_buffer
{
	void *			pself;		/* for verify itself */	
    EB_TLV *		curtlv;     /* current pointer */
    BOOL            autoflush;  /* whether auto flush, default TRUE */
    char *          pbuf;       /* buffer to hold data */
    int             size;       /* buffer size */
    int             count;      /* block number */
	BOOL			flushed;	/* flush has been called */
	void *			pagestack[MAX_CALL_DEPTH+1];
	void *			pifbuf;		/* inflat buffer */
} EB_BUFFER;


/* externs */
extern void * ebBufCreate(int size);
extern void ebBufDistroy(void * fp);
extern int  ebBufReset(void * fp);
extern int  ebBufResize(void * fp, int size);
extern int  ebBufFlush(void * fp);
extern int  ebCheckBufSize(void * ebfp);
extern int  ebSetBufAutoFlush(void * ebfp, BOOL autoflush);
extern BOOL ebBufIsFlushed(void * ebfp);
extern int  ebBufTlvSet(void * fp, int type, int len, char *pdata);
extern int  ebBufTlvAdd(void * ebfp, int type, int len, char *pdata);
extern int  ebBufStringAdd(void * fp, char * pstr);
extern int  ebvprintf(void * fp, const char * fmt, va_list);

extern int  ebprintf(void * fp, const char * fmt, ...);
extern int  ebWriteBlock(void * ebfp, void * data, size_t size);
extern int  ebDeflatAdd(void * ebfp, void * data, size_t offset, size_t len);


#ifdef __cplusplus
}
#endif

#endif /* _INC_EBBUFF_H_ */

