/*
 *	Module:
 *		getpasswd.c
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

#include <stdio.h>
#include <sys/types.h>
#include <termios.h>


#include "getpasswd.h"

ssize_t 
getpasswd(char **lineptr, size_t *n, FILE *stream)
{
  struct termios	old, new;
  int				nread;

  /* Turn echoing off and fail if we can't. */
  if (tcgetattr (fileno (stream), &old) != 0)
    return -1;
  new = old;
  new.c_lflag &= ~ECHO;
  if (tcsetattr (fileno (stream), TCSAFLUSH, &new) != 0)
    return -1;
  
  /* Read the password. */
  nread = getline (lineptr, n, stream);

  /* Restore terminal. */
  (void) tcsetattr (fileno (stream), TCSAFLUSH, &old);
  
  return nread;
}
