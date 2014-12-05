/*
 *	Name:
 *		drcom-nix
 *
 *	Descr:
 *		Dr.Com Client for Linux.
 *		You can login using this client instead of HTTP.
 *
 *	Author:
 *		Zimu LIU
 *
 *	E-mail:
 *		zimu.liu@gmail.com
 * 
 *	History:
 *		Apr 26, 2006			Ver 0.1b
 *
 *		Apr 29, 2006			Ver 0.2
 *			Change password is still unsupported.
 *			Modify the framework of drcom-nix.
 *
 *		May 1, 2006			Ver 0.2.1
 *			Provide log file for debug, customization of
 *			server address & port.
 *			Users can install drcom-nix in /usr/bin
 *
 *		May 20, 2006			Ver 0.2.2
 *          		Fix bug in drcom.c
 *
 *		Jun 14, 2006			Ver 0.2.3
 *			Fix bug: missing argument of server address.
 */

#define VERSION "0.2.3"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <netinet/in.h>
#include <netdb.h>
#include <net/if.h>

#include "global.h"
#include "getpasswd.h"
#include "drcom.h"

static struct drcom_context	*pDrcomContext = NULL;

static pid_t	keepalive_pid;
static BOOL		TryLogout = FALSE;
static BOOL		IsLogin	= FALSE;

void PrintUseage()
{
    printf("ATTENTION:ONLY 2.8x DR.COM IS SUPPORTED!!\n\n");
	printf("Usage:\n");
	printf("\tdrcom-nix ID [Server] [Port]\n");
	printf("Default:\n");
	printf("\tServer = account.njupt.edu.cn\n");
	printf("\tPort   = 61440\n");
	printf("\n");
	printf("Version:%s\n", VERSION);
}

void CtrlC(int ignored)
{
	if (!IsLogin || TryLogout)
	{
		DrcomRelease(&pDrcomContext);
		fclose(stderr);
		exit(EXIT_SUCCESS);
	}
	TryLogout = TRUE;
}

int main(int argc, char **argv)
{
	int		PasswdLength = 0;
	char   *lineptr[1] = {NULL};
	int		linelen = 0;
	char	Server[100];
	int		Port;

	strcpy(Server, "account.njupt.edu.cn");
	Port = 61440;

	if (argc < 2)
	{
		PrintUseage();
		exit(EXIT_FAILURE);
	}

	if (argc >= 3)
		strncpy(Server, argv[2], sizeof(Server));

	if (argc == 4)
		Port = atoi(argv[3]);

	if ((stderr = fopen("/var/log/drcom-nix.log", "a")) == NULL)
	{
		printf("Failed to open drcom-nix.log\n");
		exit(EXIT_FAILURE);
	}

	signal(SIGINT, CtrlC);

	pDrcomContext = DrcomInit(
		Server,
		Port,
		120);

	if (pDrcomContext == NULL)
	{
		printf("Failed to init Drcom\n");
		goto SafeExit;
	}

	strcpy(pDrcomContext->Id, argv[1]);

	printf("Password:");
	PasswdLength = getpasswd(lineptr, &linelen, stdin) - 1;
	if (lineptr[0] != NULL)
	{
		if (PasswdLength < sizeof(pDrcomContext->Password))
			memcpy(pDrcomContext->Password, lineptr[0], PasswdLength);
		free(lineptr[0]);
		if (PasswdLength >= sizeof(pDrcomContext->Password))
		{
			printf("Password is too long\n");
			goto SafeExit;
		}
	}
	printf("\n");

	if (DrcomLogin(pDrcomContext))
	{
		int		status;

		IsLogin = TRUE;
		printf("Login Success.\n");
		DrcomPrintAccountInfo(pDrcomContext);

		keepalive_pid = fork();
		if (keepalive_pid == 0)
		{
			DrcomKeepAlive(pDrcomContext);
			printf("Drcom Server: %s\n", pDrcomContext->DrcomInfo);
			exit(EXIT_SUCCESS);
		}

		while (!TryLogout)
		{
			if (keepalive_pid == waitpid(keepalive_pid, &status, WNOHANG))
			{
				if (WIFEXITED(status))
					goto SafeExit;
				if (TryLogout)
					break;
			}
			if (!DrcomPing(pDrcomContext))
				goto SafeExit;
			sleep(10);
		}
		kill(keepalive_pid, SIGKILL);
		if (DrcomLogout(pDrcomContext))
		{
			printf("Logout Success.\n");
			DrcomPrintAccountInfo(pDrcomContext);
		}
		else
		{
			if (strlen(pDrcomContext->DrcomInfo) > 0)
				printf("Logout Failed: %s\n", pDrcomContext->DrcomInfo);
			else
				printf("Logout Failed.\n");
		}
	}
	else
	{
		if (strlen(pDrcomContext->DrcomInfo) > 0)
			printf("Login Failed: %s\n", pDrcomContext->DrcomInfo);
		else
			printf("Login Failed.\n");
	}

SafeExit:
	DrcomRelease(&pDrcomContext);
	fclose(stderr);
    return 0;
}

