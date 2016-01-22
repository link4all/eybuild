/* replace.h - replace all the find substring in a string  */

/* Copyright(C) eyBuild Group, 2005, 2006. All Rights Reserved. */

/*
modification history
--------------------
01a, 2004-3-25, 	Ljy write.
*/

#ifndef _REPLACE_H_
#define _REPLACE_H_

#include <ebfrm.h>

#ifdef __cplusplus
    extern "C" {
#endif

#define STR_ANY_SIZE			(~0)/* any size */

#define STR_MATCH_CASE			1	/* match case */
#define STR_NO_MATCH_CASE		2	/* not match case */
#define STR_MATCH_WHOLE_WORD	4	/* match whole word */
#define STR_NO_MATCH_WHOLE_WORD	8	/* not match word */

#define STR_CASE_WHOLE_WORD			(STR_MATCH_CASE|STR_MATCH_WHOLE_WORD)
#define STR_CASE_NO_WHOLE_WORD		(STR_MATCH_CASE|STR_NO_MATCH_WHOLE_WORD)
#define STR_NO_CASE_WHOLE_WORD		(STR_NO_MATCH_CASE|STR_MATCH_WHOLE_WORD)
#define STR_NO_CASE_NO_WHOLE_WORD	(STR_NO_MATCH_CASE|STR_NO_MATCH_WHOLE_WORD)


/**************************************************************************
 * str_find_nocase - find the first occurrence of a substring in a string 
 *
 * This routine locates the first occurrence in string s of the sequence 
 * of characters not match case (excluding the terminating null character) 
 * in the string find. 
 * 
 * RETURN: 
 *  A pointer to the located substring, or src if find points to 
 *  a zero-length string, or NULL if the string is not found
 */

extern char * str_find_no_case
	(
	char *				src,	/* where to find */
	char *				fnd		/* what to find */
	);
	

/**************************************************************************
 * str_find_whole_word - find the first occurrence of a substring in a string 
 *
 * This routine locates the first occurrence in string s of the sequence 
 * of characters match whole word (excluding the terminating null character) 
 * in the string find. 
 * 
 * RETURN: 
 *  A pointer to the located substring, or src if find points to 
 *  a zero-length string, or NULL if the string is not found
 */
extern char * str_find_whole_word
	(
	char *				src,	/* where to find */
	char *				fnd,	/* what to find */
	int					opt
	);

/**************************************************************************
 * str_replace_all - replace all the occurrence of a substring in a string 
 *
 * This routine replace all the occurrence of a substring in a string 
 * not match case (excluding the terminating null character) in 
 * the string find. Operator option 'opt' may specify the rule how to 
 * find the substring, opt my be following value:
 * 
 *   STR_CASE_WHOLE_WORD		- match case and whole word
 *   STR_CASE_NO_WHOLE_WORD		- match case but not whole word
 *   STR_NO_CASE_WHOLE_WORD		- not match case but match whole word
 *   STR_NO_CASE_NO_WHOLE_WORD  - not match case and not match whole word
 * 
 * When the length of 'rpls' longer then 'fnd', the src string would
 * gain longer and need enough longer buffer. if the size of src buffer
 * ('src_size') is longer enough, this routine will return an error.
 * STR_ANY_SIZE (~0) may be use to specify we have a enough longer buffer 
 * or 'src' buffer would't be gain longer(eg. fnd longer than rplc).

 * RETURN: 
 *  Number of have been replaced, or ERROR when src or fnd or rplc value
 *  eque NULL, or ERROR when src_size is too shorter to gain longer buffer
 *  data, or ERROR when malloc memory ERROR;
 */
extern int str_replace_all
	(
	char *				src,		/* where to find */
	unsigned			src_size,	/* size of src buffer */
	char *				fnd,		/* what to find */
	char *				rplc,		/* what to replace to */
	int					opt			/* operator option */
	);
	
#ifdef __cplusplus
}
#endif

#endif /* _REPLACE_H_ */

