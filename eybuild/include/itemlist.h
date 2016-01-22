/* itemlist.c - maintain an link list */

/* Copyright(C) eyBuild Group, 2005, 2006. All Rights Reserved. */

/*
modification history
--------------------
01a, 2006-01-16, newzy   create
*/

#ifndef _INC_ITEMLIST_H_
#define _INC_ITEMLIST_H_

#ifdef __cplusplus
extern "C" {
#endif

/* defines */

/* limit item size, include tail '\0' */

#define EB_ITEM_MAX_SIZE		0x100000	/* 1M */
#define EB_ITEM_DEFAULT_SIZE	0x100		/* 256K */

/* typedefs */

/* define item node */
typedef struct EB_ITEM {
	char *			name;
	char *			value;
	int				max_size;
	struct EB_ITEM *next;		
} EB_ITEM;

/* define item list */
typedef struct EB_ITEM_LIST {
	EB_ITEM *		first;
	EB_ITEM *		last;
} EB_ITEM_LIST;

/* externs */
extern EB_ITEM * ebFindItem
	(
	EB_ITEM_LIST *  form_list,	/* where insert to */
	char *			name		/* name of item */
	);

extern int ebNewItemAdd
	(
	EB_ITEM_LIST *  form_list,	/* where insert to */
	char *			name,		/* item name */
	int  			max_size	/* max size of value to returned */
	);

extern char * ebGetItemValue
	(
	EB_ITEM_LIST *  form_list,	/* where insert to */
	char *			name		/* name of item */
	);

extern char * ebSetItemValue
	(
	EB_ITEM_LIST *  form_list,	/* where insert to */
	char *			name,		/* name of item */
	char *			value		/* value to set to */
	);

extern void ebDistoryItemList
	(
	EB_ITEM_LIST *  form_list	/* where insert to */
	);

        
#ifdef __cplusplus
}
#endif

#endif /* _INC_ITEMLIST_H_ */

