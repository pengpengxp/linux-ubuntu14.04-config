/*
 *	Name:
 *		drcom.h
 *
 *	Descr:
 *		drcom context struct and drcom lib routines:
 *		DrcomInit
 *		DrcomRelease
 *		DrcomLogin
 *		DrcomLogout
 *		DrcomPrintAccountInfo
 *		DrcomKeepAlive
 *		DrcomPing
 *
 *	Author:
 *		Zimu LIU
 *
 *	E-mail:
 *		zimu.liu@gmail.com
 *
 *	History:
 *		Apr 28, 2006			Created
 *
 */
 
#ifndef __DRCOM__H
#define __DRCOM__H

struct  drcom_context
{			
	char			Id[36];
	char            Password[20];
	unsigned char   Challenge[4];
	unsigned char	DigestForPing[16];
	unsigned char	DigestForReply[16];
	unsigned short	Plusword[2];

	BOOL			IsBalanceValid;
	unsigned long	Balance;
	BOOL			IsTimeValid;
	unsigned long	Time;
	unsigned long	Flux;	

	char			DrcomInfo[1024];
		
	int             NicCount;	
	unsigned char   MacAddr[6];
	unsigned char   IpAddr[16];
	char            ExtInfo[200];

	unsigned char	SendBuf[1024];
	unsigned char	RecvBuf[1024];
	int				RecvBufLength;
	int				SendBufLength;

	BOOL			IsNewVer;
	BOOL        	PasswdSaved;
	int				MaxCardNum;
	unsigned char	VpnExchangeIp[4];
	unsigned char	VpnHeader[20];

	int						Socket;
	struct sockaddr_in		LocalAddr;
	struct sockaddr_in		ServerAddr;	
};

struct drcom_context *
DrcomInit(
	char 	   			*pServer,
	int					nPort,
	int					nTimeoutSec
	);

void 
DrcomRelease(
	struct drcom_context	**pDrcomContext
	);

BOOL 
DrcomLogin(
	struct drcom_context	*pDrcomContext
	);

BOOL 
DrcomLogout(
	struct drcom_context	*pDrcomContext
	);

void
DrcomPrintAccountInfo(
	struct drcom_context	*pDrcomContext
	);

BOOL
DrcomPing(
	struct drcom_context	*pDrcomContext
	);

BOOL
DrcomKeepAlive(
	struct drcom_context	*pDrcomContext
	);

#endif
