/* ebmultiform.h - http multipart/form-data header file */

/* Copyright(C) eyBuild Group, 2005, 2006. All Rights Reserved. */

/*
modification history
--------------------
01a, 2006-01-13, newzy   create
*/


#ifndef _INC_EBMULTIFORM_H_
#define _INC_EBMULTIFORM_H_

#include <ebio.h>
#include <itemlist.h>

#ifdef __cplusplus
extern "C" {
#endif

/* define default post config */
#define EB_MAX_POST_SIZE        0x200000    /* 2M */
#define EB_MAX_FILE_SIZE        0x100000    /* 1M */
#define EB_DEFAULT_FILE_COUNT	1           /* 1 file */
#define EB_MAX_FILE_COUNT		64          /* max files allowd upload */

/* post part header */
typedef struct POST_PART_HDR {
	int				post_remain_len;	/* data length not read */
	char 			content_type[256];	/* data's */
	char			data_name[256];     /* name of post item */
	char			filename[256];      /* name of filename */
	BOOL			isfile;			    /* is upload file */
	void *			cookie;			    /* user cookie */
} POST_PART_HDR;

/* define post hooks type */
typedef BOOL (*FUNC_ON_DOHEADER)(POST_PART_HDR * p_part);
typedef BOOL (*FUNC_ON_DODATA)(POST_PART_HDR * p_part, char * pbuf, int size);
typedef BOOL (*FUNC_ON_DOEND)(POST_PART_HDR * p_part);

/* to handle files in post */
typedef struct {
	int				max_count;
	int				filecount;
	char **			filenames;			
	char **			tempnames;			
} POST_FILE_LIST;

/* to limit or control the action in this post 
 */
typedef struct POST_PARAM {
    EB_ITEM_LIST    item_list;	    /* to return form items */
	int				options;
    int             max_post_size;	
    int             file_max_size;
	int				max_file_number;
    char            upload_tmp_dir[256];
    FUNC_ON_DOHEADER  on_header;
    FUNC_ON_DODATA  on_data;
    FUNC_ON_DOEND	on_end;
	void *			cookie;
} POST_PARAM;


typedef struct THIS_POST
{
	POST_FILE_LIST  file_list;	    /* post file list */
    EB_ITEM_LIST    item_list;	    /* to return form items */
	POST_PARAM *	p_param;
 	int				remain_len;     /* remain length read avaiable */
	int             content_len;    /* post content length */
	char  			boundary[256];  /* post boundary */
	int				boundary_len;	/* length of boundary */
    char *          errmsg;      	/* to return error */
	FILE *			fp;
} THIS_POST;


/* externs */

extern POST_PARAM * createPostParam
	(
	int				max_post_size,		/* max post size */
	int				file_max_size,		/* max size each file */
	int				max_file_number,	/* max file may uploads */
	char *			upload_tmp_dir,		/* where to store temp */
	int				options				/* other options */
	);

extern void distoryPostParam
	(
	POST_PARAM *	p_param
	);

extern int installPostHook
	(
	POST_PARAM *		post_param,
    FUNC_ON_DOHEADER	on_header,
    FUNC_ON_DODATA		on_data,
    FUNC_ON_DOEND		on_end,
	void *				cookie
	);

extern THIS_POST * dopost
    (
    POST_PARAM *	p_param,	/* page post prameters */
	char *			errmsg        /* eybuidlib cookie */
    );
    
extern void distoryPost
    (
	THIS_POST *		p_post,		/* current post */
 	BOOL			isremove	/* remove files in temp_dir or not */
   );

extern int addPostItem
	(
    POST_PARAM *    p_param,    /* where set to */
	char *			name,		/* item name */
	int  			max_size	/* max size of value may be returned */
	);

extern char * getPostItemValue
	(
	THIS_POST *		p_post,		/* where get from */
	char *			name		/* name of item */
	);

extern char * getPostSrcFileName
	(
	THIS_POST *		p_post,		/* where to get */
	int				index		/* index in file list */
	);

extern int getPostFileCount
	(
	THIS_POST *		p_post		/* where get from */
	);

extern int movePostFile
	(
	THIS_POST *		p_post,		/* where get from */
	int				index,		/* index in file list */
	char *			copyto		/* where copy to */
	);

        
#ifdef __cplusplus
}
#endif

#endif /* _INC_EBMULTIFORM_H_ */

