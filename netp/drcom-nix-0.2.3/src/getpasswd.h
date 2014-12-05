/*
 *	Module:
 *		getpasswd.h
 *
 *	Descr:
 *		Get password without echo.
 *
 *	Author:
 *		Zimu LIU
 *
 *	E-mail:
 *		zimu.liu@gmail.com
 *
 *	History:
 *		Apr 26, 2006			Created
 *
 */

#ifndef __GETPASSWD__H
#define __GETPASSWD__H

ssize_t
getpasswd(char **lineptr, size_t *n, FILE *stream);

#endif
