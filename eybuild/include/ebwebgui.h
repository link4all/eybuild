/* ebwebgui.h - eybuild WEB GUI header file */

/* Copyright(C) eyBuild Group, 2005, 2006. All Rights Reserved. */

/*
modification history
--------------------
01b, 2006-04-13, newzy   create
*/

#ifndef _INC_EBWEBGUI_H_
#define _INC_EBWEBGUI_H_

#include <ebdef.h>

#ifdef __cplusplus
extern "C" {
#endif

/* 
 * fill "&nbsp;"
 */
#undef IF_THEN_SPACE
#define IF_THEN_SPACE(v)	\
		(isblankstr(v) ? "&nbsp;": (v))

/* 
 * if true then return xxx, othersize "" 
 */
#undef IF_THEN
#define IF_THEN(c, p)	((c) ? (p): (""))

/* 
 * copy data to limit buffer size, 
 * return type: void
 */
#undef BUFCPY
#ifndef CHECK_BUFCPY

#define BUFCPY(d, s)	\
		((void)(	\
		  strncpy((d), (s), sizeof(d)-1), \
		  (d)[sizeof(d)-1] = '\0') 		\
		)		

#else /* CHECK_BUFCPY */

/* error message */
#define EBGUI_ERR_MSG(p) \
		"Content-Type: text/html\n\n"	\
		"<p><b>" #p "</b>: must be a array name, can't be a pointer<br>\n"

/* send error message */
#define EBGUI_SEND_ERR_MSG(p)	\
		(0 & fprintf(stdout, EBGUI_ERR_MSG(p)) & fflush(stdout)	)

#define EB_GUI_ASSERT(p)	\
		(((void*)p==(void*)&p) ? 1: EBGUI_SEND_ERR_MSG(p))
/* 
 * copy data to limit buffer size, 
 * return type: void
 */
#define BUFCPY(d, s)	\
		  if (EB_GUI_ASSERT(d)) page_exit(ERROR); \
		  (strncpy((d), (s), sizeof(d)-1), \
		  (d)[sizeof(d)-1] = '\0')
#endif /* CHECK_BUFCPY */

/* 
 * display HTML <select></select> by item name
 * 
 * <% SELECT_BEGIN("selname", "2", "size=4 multiple") %>
 *     <% OPTIONS_ADD("1", "no. 1") %>
 *     <% OPTIONS_ADD("2", "no. 2") %>
 *     <% OPTIONS_ADD("3", NULL) %>
 *     <% OPTIONS_ADD("4", NULL) %>
 * <% SELECT_END() %>
 */
#define SELECT_BEGIN(name, item, options) {	\
		char *	_item_ = item;					\
		char _buf1_[256]="", _buf2_[256]="";		\
		print("<select name=\"%s\" %s>\n", (name), (options) ? (options): "");
#define OPTIONS_ADD(value, desc)	\
		print("<option value=\"%s\"%s>%s</option>\n",		\
				ebHtmlEncode(_buf1_, (value), sizeof(_buf1_)), 	\
				!strcmp((_item_), (value)) ? " selected": "", \
				ebHtmlEncode(_buf2_, (char *)((desc) ? (desc): (value)), sizeof(_buf2_))	\
				);
#define SELECT_END() 	\
		print("</select>\n"); \
		}


/* 
 * display HTML <select></select> by index
 * 
 * <% SELECT_BEGIN2("selname2", 2, "size=4 multiple") %>
 *     <% OPTIONS_ADD2(1, "no. 1") %>
 *     <% OPTIONS_ADD2(2, "no. 2") %>
 *     <% OPTIONS_ADD2(3, NULL) %>
 *     <% OPTIONS_ADD2(4, NULL) %>
 * <% SELECT_END2() %>
 */
#define SELECT_BEGIN2(name, index, options) {	\
		char  _item_[16]="";						\
		char _buf1_[256]="", _buf2_[256]="";		\
		sprintf(_item_, "%d", index); 			\
		print("<select name=\"%s\" %s>\n", (name), (options) ? (options): "");

#define OPTIONS_ADD2(value, desc)	{ 	\
		char 	_value_[16] = "";		\
		sprintf(_value_, "%d", value); 	\
		print("<option value=\"%s\"%s>%s</option>\n",		\
				ebHtmlEncode(_buf1_, (_value_), sizeof(_buf1_)), 	\
				!strcmp((_item_), (_value_)) ? " selected": "", \
				ebHtmlEncode(_buf2_, (char *)((desc) ? (desc): (_value_)), sizeof(_buf2_))	\
				); 	\
		}
#define SELECT_END2() 	SELECT_END()


/* mark checked for radiobox and checkbox */
#define FORM_BOX_CHECKED(boxname, name, value, curval, options)	\
		(void)print("<input type=\"%s\" %s name=\"%s\" value=\"%s\"%s>",	\
			(boxname), (options) ? (options): "", (name), (value), 					\
			!strcmp((value), (curval) ? (curval): "") ? " checked": ""); 

/* radio & checkbox */
#define RADIO_BOX(name, value, curval, options)	\
		FORM_BOX_CHECKED("radio", (name), (value), (curval), (options))
#define CHECK_BOX(name, value, curval, options)	\
		FORM_BOX_CHECKED("checkbox", (name), (value), (curval), (options))

/* radio & checkbox */
#define RADIO_BOX2(name, value, curval, options) {	\
		char 		_buf[16] = ""; sprintf(_buf, "%d", (curval)); \
		FORM_BOX_CHECKED("radio", (name), (value), _buf, (options)); \
		}
#define CHECK_BOX2(name, value, curval, options) {	\
		char 		_buf[16] = ""; sprintf(_buf, "%d", (curval)); \
		FORM_BOX_CHECKED("checkbox", (name), (value), (_buf), (options)); \
		}

#ifdef __cplusplus
}
#endif


#endif /* _INC_EBWEBGUI_H_ */
							
							
