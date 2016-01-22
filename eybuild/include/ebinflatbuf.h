/* ebinflatebuf.h - inflat buffer */

/* Copyright(C) eyBuild Group, 2005, 2006. All Rights Reserved. */

/*
modification history
--------------------
01a, 2006-11-06, newzy   extract from ebbuff.h
*/

/* ebuild in/out */
#ifndef _INC_EBINFLATEBUF_H_
#define _INC_EBINFLATEBUF_H_

#include <ebfrm.h>
#include <ebzlib.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct EB_DFBUFF
{
	BOOL			blinflat;	/* inflat or not */
	char *			pbuf;		/* inflat buffer */
	int				size;		/* sizeof of inflat buffer */
} EB_IFBUFF;

typedef struct {
	int				dfpagelen;	/* length of page in deflat buffer */
	int				ifbuflen;	
	unsigned		options;
} EB_IFBUFF_HDR;

extern int ebLoadInflatBuf(void * ebfp, int deepth, char * pname);
extern int ebUnloadInflatBuf(void * ebfp, int deepth);
extern int ebInflatAdd(void * ebfp, size_t offset,	size_t datalen);

extern void * ebInflatBufCreate
	(
	char *			pdata,		/* data buffer */
	int				dfpagelen,	/* length of page in deflat buffer */
	int				ifbuflen,	
	BOOL			blcompr		/* compressed or not */	
	);
extern void ebInflatBufDistroy(void * pif);


#ifdef __cplusplus
}
#endif

#endif /* _INC_EBINFLATEBUF_H_ */

