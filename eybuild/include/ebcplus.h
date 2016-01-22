/* ebcplus.h - sample C++ wrapper header file */

/* Copyright(C) eyBuild Group, 2005, 2006. All Rights Reserved. */

/*
modification history
--------------------
01a, 2006-11-24, newzy   create
*/

#ifndef _INC_EBCPLUS_H_
#define _INC_EBCPLUS_H_

#ifdef __cplusplus

#include <string>
using namespace std;

extern int print(int num);
extern int print(string &str);
extern int ebstrprintf(void * ebfp, const char * str);
extern int ebstrprintf(void * ebfp, string &str);
extern char * getParameter(string &name);
extern char * getCookie(string &name);

#endif /* __cplusplus */


#endif /* _INC_EBCPLUS_H_ */

