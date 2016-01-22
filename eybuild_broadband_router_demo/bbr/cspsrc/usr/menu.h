/* menu.h - GUI menu control */

/* Copyright(C) eyBuild Group, 2005, 2006. All Rights Reserved. */

/*
modification history
--------------------
01a, 2005-12-3, newzy author
*/

#ifndef _INC_MENU_H_
#define _INC_MENU_H_

#include <stdlib.h>
#include <ebfrm.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    char *      pagename;
    char *      descripion;
} MENU_NODE;

typedef struct {
    MENU_NODE       node;
    unsigned		sub_num;
    MENU_NODE *     subnode;
} MENU_MANI_NODE;  
    
#define ARRAYNUM(name)  (sizeof(name)/sizeof(name[0]))


extern int check_id (unsigned  mid, unsigned sid);
extern int menu_get_page(void * fp, char * MainID, char * SubID);
extern int menu_update(void * fp, char * MainID, char * SubID);
extern int do_login(void * pblock, char * pname, int type);

#ifdef __cplusplus
}
#endif

#endif /* _INC_MENU_H_ */

