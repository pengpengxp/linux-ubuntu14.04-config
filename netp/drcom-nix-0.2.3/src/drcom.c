/*
 *	Name:
 *		drcom.c
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
 *		Apr 28, 2006	Created
 *		May 1, 2006	Add private DrcomPrintPacket() for debug
 *      	May 20, 2006	Fix bug: offsef of info from fail-packet
 *                              should be 0x14(20), not 14
 *
 */

#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <net/if.h>

#include "global.h"
#include "md5.h"
#include "drcom.h"

#define DRCOM_REQUEST		0x01
#define	DRCOM_CHALLENGE	0x02
#define DRCOM_LOGIN		0x03
#define DRCOM_LOGOUT		0x06
#define	DRCOM_SUCCESS		0x04
#define DRCOM_FAIL			0x05
#define DRCOM_MESSAGE		0x4d
#define DRCOM_REPLY		0xfe
#define DRCOM_PING			0xff

struct msg_info
{
	unsigned char	Type;
	unsigned char	SubType;
	BOOL			IsValid;
};

static void
DrcomPrintPacket(
	unsigned char			*pBuf,
	unsigned int			nBufLength
	)
{
	int 	i;
	for (i = 0; i < nBufLength; i++)
		fprintf(stderr, "%02x ", pBuf[i]);
	fprintf(stderr, "\n");
}


static BOOL
DrcomGetLocalInfo(
	struct drcom_context	*pDrcomContext
	)
{
    struct ifreq 	ifr;
	int				i;

#ifdef DEBUG
	fprintf(stderr, "DrcomGetLocalInfo:Begin to get localhost info\n");
#endif

	for (i = 0; i < 4; i++)
	{
		sprintf(ifr.ifr_name, "eth%d", i);
		if (i == 0)
		{
			if (ioctl(pDrcomContext->Socket, SIOCGIFHWADDR, &ifr) < 0)
			{
#ifdef DEBUG
				perror("DrcomGetLocalInfo:ioctl(SIOCGIFHWADDR)");
#endif
				goto DrcomGetLocalInfoError;
			}
			memcpy(pDrcomContext->MacAddr, ifr.ifr_hwaddr.sa_data, 6);
#ifdef DEBUG
			fprintf(stderr, "DrcomGetLocalInfo:MAC address of eth0 is %02x:%02x:%02x:%02x:%02x:%02x\n",
				pDrcomContext->MacAddr[0],
				pDrcomContext->MacAddr[1],
				pDrcomContext->MacAddr[2],
				pDrcomContext->MacAddr[3],
				pDrcomContext->MacAddr[4],
				pDrcomContext->MacAddr[5]);
#endif
			if (ioctl(pDrcomContext->Socket, SIOCGIFADDR, &ifr) < 0)
			{
#ifdef DEBUG
				perror("DrcomGetLocalInfo:ioctl(SIOCGIFADDR)");
#endif
				goto DrcomGetLocalInfoError;
			}
			memcpy(&pDrcomContext->IpAddr[i*4], &ifr.ifr_addr.sa_data[2], 4);
#ifdef DEBUG
			fprintf(stderr, "DrcomGetLocalInfo:IP address of eth0 is %d.%d.%d.%d\n",
				pDrcomContext->IpAddr[0],
				pDrcomContext->IpAddr[1],
				pDrcomContext->IpAddr[2],
				pDrcomContext->IpAddr[3]);
#endif
		}
		else
		{
			if (ioctl(pDrcomContext->Socket, SIOCGIFADDR, &ifr) >= 0)
			{
				memcpy(&pDrcomContext->IpAddr[i*4], &ifr.ifr_addr.sa_data[2], 4);
#ifdef DEBUG
				fprintf(stderr, "DrcomGetLocalInfo:IP address of %s is %d.%d.%d.%d\n",
					ifr.ifr_name,
					pDrcomContext->IpAddr[i*4],
					pDrcomContext->IpAddr[i*4 + 1],
					pDrcomContext->IpAddr[i*4 + 2],
					pDrcomContext->IpAddr[i*4 + 3]);
#endif
			}
			else
				break;
		}
	}

	pDrcomContext->NicCount = i;
#ifdef DEBUG
	fprintf(stderr, "DrcomGetLocalInfo:Get info successfully\n");
#endif
	return TRUE;

DrcomGetLocalInfoError:
#ifdef DEBUG
	fprintf(stderr, "DrcomGetLocalInfo:Failed to get info\n");
#endif
	return FALSE;
}

static struct msg_info
DrcomDecodePacket(
	struct drcom_context	*pDrcomContext
	)
{
	char	*RecvBuf = pDrcomContext->RecvBuf;
	int		RecvBufLength = pDrcomContext->RecvBufLength;

	unsigned short		ShortDigest;
	struct msg_info	MsgInfo;

	MsgInfo.Type = 0;
	MsgInfo.SubType = 0;
	MsgInfo.IsValid = FALSE;

	if (RecvBufLength <= 0)
	{
		return MsgInfo;
	}
	switch (RecvBuf[0])
	{
	case DRCOM_CHALLENGE:
		if (RecvBufLength >= 8)
		{
			MsgInfo.IsValid = TRUE;
			MsgInfo.Type = DRCOM_CHALLENGE;
			memcpy(pDrcomContext->Challenge, &RecvBuf[4], 4);
		}
		break;

	case DRCOM_SUCCESS:
		MsgInfo.IsValid = TRUE;
		MsgInfo.Type = DRCOM_SUCCESS;
		if (RecvBufLength >= 13)
		{
			pDrcomContext->IsTimeValid = TRUE;
			memcpy(&pDrcomContext->Time, &RecvBuf[5], 4);
			memcpy(&pDrcomContext->Flux, &RecvBuf[9], 4);
			if (RecvBufLength >= 17)
			{
				pDrcomContext->IsBalanceValid = TRUE;
				memcpy(&pDrcomContext->Balance, &RecvBuf[13], 4);
				/* MaxCarNum?? */
				if (RecvBufLength >= 18)
				{
					pDrcomContext->MaxCardNum = RecvBuf[17];
					/* VPN exchange IP?? */
					if (RecvBufLength >= 23)
					{
						memcpy(pDrcomContext->VpnExchangeIp, &RecvBuf[19], 4);
						/* VPN header */
						if (RecvBufLength >= 43)
						{
							memcpy(pDrcomContext->VpnHeader, &RecvBuf[23], 20);
							/* New Ver */
							if (RecvBufLength >= 44)
							{
								pDrcomContext->IsNewVer = RecvBuf[43];
							}
						}
					}
				}
				else
				{
					pDrcomContext->MaxCardNum = 1;
				}
			}
		}
		break;

	case DRCOM_FAIL:
		if (RecvBufLength < 5)
			break;
		MsgInfo.IsValid = TRUE;
		MsgInfo.Type = DRCOM_FAIL;
		MsgInfo.SubType = RecvBuf[4];
		switch (RecvBuf[4])
		{
		case 0x01:
			/* Packet format is still unknown */
			if (RecvBufLength >= 15)
			{
				char	MacAddr[20];

				sprintf(MacAddr, "%02x-%02x-%02x-%02x-%02x-%02x",
					RecvBuf[9],
					RecvBuf[10],
					RecvBuf[11],
					RecvBuf[12],
					RecvBuf[13],
					RecvBuf[14]
					);
				sprintf(pDrcomContext->DrcomInfo,
					"This account is in use at %s(%s).",
					inet_ntoa(*(unsigned long *)&RecvBuf[5]),
					MacAddr);
			}
			else
			{
				sprintf(pDrcomContext->DrcomInfo, "This account is in use.");
			}
			break;

		case 0x02:
			sprintf(pDrcomContext->DrcomInfo, "Server is busy.");
			break;

		case 0x04:
			if (RecvBufLength >= 10)
				sprintf(pDrcomContext->DrcomInfo, "The accumulated time is over the limit.");
			else
				sprintf(pDrcomContext->DrcomInfo, "The balance is zero.");
			break;

		case 0x05:
			if (RecvBufLength < 6)
				sprintf(pDrcomContext->DrcomInfo, "This account is locked.");
			else
				sprintf(pDrcomContext->DrcomInfo, "This account expired.");
			break;

		case 0x07:

			if (RecvBufLength >= 9)
			{
				sprintf(pDrcomContext->DrcomInfo,
					"This account is bind to sepcial IP address (%d.%d.%d.%d).",
					RecvBuf[5],
					RecvBuf[6],
					RecvBuf[7],
					RecvBuf[8]
					);
			}
			else
			{
				sprintf(pDrcomContext->DrcomInfo, 	"This account is bind to sepcial IP address.");
			}
			break;

		case 0x0b:
			if (RecvBufLength >= 11)
			{
				sprintf(pDrcomContext->DrcomInfo,
					"This account is bind to sepcial MAC address (%02x-%02x-%02x-%02x-%02x-%02x).",
					RecvBuf[5],
					RecvBuf[6],
					RecvBuf[7],
					RecvBuf[8],
					RecvBuf[9],
					RecvBuf[10]
					);
			}
			else
			{
				sprintf(pDrcomContext->DrcomInfo, "This account is bind to sepcial MAC address.");
			}
			break;

		case 0x14:
			sprintf(pDrcomContext->DrcomInfo, "There are too many IP address in localhost.");
			break;

		case 0x15:
			sprintf(pDrcomContext->DrcomInfo, "Info from server:%s", RecvBuf[20]);
			break;

		case 0x16:
		case 0x17:
		case 0x18:
		case 0x19:
		case 0x1a:
		case 0x1b:
		case 0x1c:
			sprintf(pDrcomContext->DrcomInfo, "Undefined subtype 0x%02x.", RecvBuf[4]);
			break;

		default:
			sprintf(pDrcomContext->DrcomInfo, "Incorrect password.");
			break;
		}
		break;

	case DRCOM_MESSAGE:
		if (RecvBufLength < 2)
			break;
		MsgInfo.IsValid = TRUE;
		MsgInfo.Type = DRCOM_MESSAGE;
		MsgInfo.SubType = RecvBuf[1];
		switch (MsgInfo.SubType)
		{
		case 0x00:
			sprintf(pDrcomContext->DrcomInfo, "Please login manually.");
			break;

		case 0x01:
			sprintf(pDrcomContext->DrcomInfo, "Host is fobidden.");
			break;

		case 0x02:
			sprintf(pDrcomContext->DrcomInfo, "IP address is fobidden.");
			break;

		case 0x03:
			sprintf(pDrcomContext->DrcomInfo, "Please re-config IP address of localhost.");
			break;

		case 0x04:
		case 0x05:
			sprintf(pDrcomContext->DrcomInfo, "This account is logout.");
			break;

		case 0x06:
			sprintf(pDrcomContext->DrcomInfo, "Internet service is unavailable today.");
			break;

		case 0x07:
			sprintf(pDrcomContext->DrcomInfo, "Internet service is unavailable in this subnet.");
			break;

		case 0x08:
			sprintf(pDrcomContext->DrcomInfo, "Port access denied.");
			break;

		case 0x09:
			sprintf(pDrcomContext->DrcomInfo, "???.");
			break;

		case 0x0a:
			sprintf(pDrcomContext->DrcomInfo, "The balance is zero.");
			break;

		case 0x14:
			sprintf(pDrcomContext->DrcomInfo, "Your group does not exist.");
			break;

		case 0x15:
			sprintf(pDrcomContext->DrcomInfo, "Please login first.");
			break;

		case 0x1e:
		case 0x1f:
		case 0x20:
		case 0x21:
		case 0x22:
		case 0x23:
		case 0x24:
		case 0x25:
			sprintf(pDrcomContext->DrcomInfo, "The accumulated time or flux is over limit.");
			break;

		case 0x26:
			memcpy(&pDrcomContext->Plusword[1], &RecvBuf[2], 2);
			if (pDrcomContext->IsNewVer)
			{
				memcpy(&ShortDigest, pDrcomContext->DigestForPing, 2);
			}
			else
			{
				int		i;

				ShortDigest = 0;
				for (i = 0; i < 8; i++)
				{
					ShortDigest += *(unsigned short *)&pDrcomContext->DigestForReply[i * 2];
				}
			}
			pDrcomContext->Plusword[0] = pDrcomContext->Plusword[1] ^ ShortDigest;
			break;

		default:
			sprintf(pDrcomContext->DrcomInfo, "Undefined subtype 0x%02x.", MsgInfo.SubType);
			break;
		}
		break;

	}

	return MsgInfo;

}

static void
DrcomEncodePacket(
	struct drcom_context	*pDrcomContext,
	int 				nType)
{
	unsigned char	Digest[16];

	char	*SendBuf = pDrcomContext->SendBuf;
    int     i;
    int     nPwdLength;

	nPwdLength = strlen(pDrcomContext->Password);
    memset(SendBuf, 0, sizeof(SendBuf));

    switch (nType)
    {
    case DRCOM_REQUEST:
        SendBuf[0] = 0x01;
        SendBuf[3] = 0x04;
        SendBuf[4] = 0x01;
        pDrcomContext->SendBufLength = 20;
		break;

    case DRCOM_LOGIN:
        SendBuf[0] = 0x03;
        SendBuf[1] = 0x01;
        memcpy(&SendBuf[2], pDrcomContext->Challenge, 4);
        strcpy(&SendBuf[6], pDrcomContext->Password);
        MD5String(&SendBuf[0], 6 + nPwdLength, Digest);
        memcpy(&SendBuf[4], Digest, 16);

		/* for ping-packet */
		memcpy(pDrcomContext->DigestForPing, Digest, 16);
		/* for response-packet */
		strcpy(&SendBuf[20], pDrcomContext->Password);
		MD5String(&SendBuf[4], 16 + nPwdLength, pDrcomContext->DigestForReply);

        memset(&SendBuf[20], 0, 36);
        strcpy(&SendBuf[20], pDrcomContext->Id);
        SendBuf[56] = pDrcomContext->PasswdSaved ? 0x18 : 0x10;
        SendBuf[57] = pDrcomContext->NicCount;
        memcpy(&SendBuf[58], pDrcomContext->MacAddr, 6);
        for (i = 0; i < 6; i++)
        {
            SendBuf[58 + i] ^= SendBuf[4 + i];
        }
        SendBuf[64] = 1;
        strcpy(&SendBuf[65], pDrcomContext->Password);
        memcpy(&SendBuf[65 + nPwdLength], pDrcomContext->Challenge, 4);
        memset(&SendBuf[65 + nPwdLength + 4], 0, 4);
        MD5String(&SendBuf[64], 1 + nPwdLength + 8, Digest);
        memcpy(&SendBuf[64], Digest, 16);
        SendBuf[80] = pDrcomContext->NicCount;
        memcpy(&SendBuf[81], pDrcomContext->IpAddr, 16);
        SendBuf[97] = 0x14;
        SendBuf[98] = 0x00;
        SendBuf[99] = 0x07;
        SendBuf[100] = 0x0B;
        MD5String(&SendBuf[0], 101, Digest);
        memcpy(&SendBuf[97], Digest, 8);
        memset(&SendBuf[105], 0, 5);
        memcpy(&SendBuf[110], Digest, 200);
        SendBuf[310] = 0x01;
        SendBuf[311] = 0x00;
        pDrcomContext->SendBufLength = 312;
        break;

	case DRCOM_LOGOUT:
        SendBuf[0] = 0x06;
        SendBuf[1] = 0x01;
        memcpy(&SendBuf[2], pDrcomContext->Challenge, 4);
        strcpy(&SendBuf[6], pDrcomContext->Password);
        MD5String(&SendBuf[0], 6 + nPwdLength, Digest);
        memcpy(&SendBuf[4], Digest, 16);
        memset(&SendBuf[20], 0, 36);
        strcpy(&SendBuf[20], pDrcomContext->Id);
        SendBuf[56] = pDrcomContext->PasswdSaved ? 0x18 : 0x10;
        SendBuf[57] = pDrcomContext->NicCount;
        memcpy(&SendBuf[58], pDrcomContext->MacAddr, 6);
        for (i = 0; i < 6; i++)
        {
            SendBuf[58 + i] ^= SendBuf[4 + i];
        }
		memcpy(&SendBuf[64], pDrcomContext->VpnHeader, 16);

		pDrcomContext->SendBufLength = 80;
		break;

	case DRCOM_PING:
		SendBuf[0] = 0xff;
		memcpy(&SendBuf[1], pDrcomContext->DigestForPing, 16);
		memcpy(&SendBuf[20], pDrcomContext->VpnHeader, 16);
		pDrcomContext->SendBufLength = 36;
		break;

	case DRCOM_REPLY:
		SendBuf[0] = 0xfe;
		SendBuf[1] = (pDrcomContext->Plusword[0] & 0xff) + (pDrcomContext->Plusword[0] >> 8);
		SendBuf[2] = pDrcomContext->NicCount;
		SendBuf[3] = 0x14;
		SendBuf[4] = 0x00;
		SendBuf[5] = 0x07;
		SendBuf[6] = 0x0b;
		memcpy(&SendBuf[7], &pDrcomContext->Plusword[1], 2);
		MD5String(&SendBuf[0], 9, Digest);
		memcpy(&SendBuf[3], Digest, 16);
		memcpy(&SendBuf[20], pDrcomContext->VpnHeader, 16);
		pDrcomContext->SendBufLength = 36;
		break;

	default:
		pDrcomContext->SendBufLength = 0;
    }
}


static BOOL
DrcomSendPacket(
	struct drcom_context	*pDrcomContext
	)
{
	int		nBytesSent;

	nBytesSent = sendto(
		pDrcomContext->Socket,
		pDrcomContext->SendBuf,
		pDrcomContext->SendBufLength,
		0,
		(struct sockaddr *)&pDrcomContext->ServerAddr,
		sizeof(struct sockaddr_in));
	if (-1 == nBytesSent)
	{
#ifdef DEBUG
		fprintf(stderr, "DrcomSendPacket:Timeout\n");
#endif
		return FALSE;
	}
	if (nBytesSent != pDrcomContext->SendBufLength)
	{
#ifdef DEBUG
		fprintf(stderr, "DrcomSendPacket:Failed to send\n");
#endif
		return FALSE;
	}
#ifdef DEBUG
	fprintf(stderr, "DrcomSendPacket:%d bytes sent\n", nBytesSent);
	fprintf(stderr, "DrcomSendPacket:");
	DrcomPrintPacket(pDrcomContext->SendBuf, pDrcomContext->SendBufLength);
#endif
	return TRUE;
}

static BOOL
DrcomRecvPacket(
	struct drcom_context	*pDrcomContext
	)
{
	struct sockaddr_in	RecvAddr;
	int					RecvAddrLength = sizeof(struct sockaddr);
	int					nBytesRecv;

	while (1)
	{
		nBytesRecv = recvfrom(
			pDrcomContext->Socket,
			pDrcomContext->RecvBuf,
			sizeof(pDrcomContext->RecvBuf),
			0,
			(struct sockaddr *)&RecvAddr,
			&RecvAddrLength);
		if (-1 == nBytesRecv)
		{
#ifdef DEBUG
			fprintf(stderr, "DrcomRecvPacket:Timeout\n");
#endif
			return FALSE;
		}
		if (memcmp(
			&RecvAddr.sin_addr,
			&pDrcomContext->ServerAddr.sin_addr,
			sizeof(struct in_addr)) != 0)
		{
#ifdef DEBUG
			fprintf(stderr, "DrcomRecvPacket:This packet is not from server\n");
#endif
			continue;
		}
		else
			break;
	}

	pDrcomContext->RecvBufLength = nBytesRecv;
#ifdef DEBUG
	fprintf(stderr, "DrcomRecvPacket:%d bytes received\n", nBytesRecv);
	fprintf(stderr, "DrcomRecvPacket:");
	DrcomPrintPacket(pDrcomContext->RecvBuf, pDrcomContext->RecvBufLength);
#endif
	return TRUE;
}


struct drcom_context *
DrcomInit(
	char 	   			*pServer,
	int					nPort,
	int					nTimeoutSec
	)
{
	struct drcom_context	*pDrcomContext = NULL;

	struct hostent    *pHost = NULL;
	struct timeval 	Timeout; /* sec, usec */
	socklen_t			TimeoutLen = sizeof(struct timeval);

#ifdef DEBUG
	fprintf(stderr, "DrcomInit:Begin to init Drcom\n");
#endif
	pDrcomContext = malloc(sizeof(struct drcom_context));
	if (pDrcomContext == NULL)
	{
#ifdef DEBUG
		fprintf(stderr,"DrcomInit:Failed to malloc\n");
#endif
		goto DrcomInitError;
	}
	memset(pDrcomContext, 0, sizeof(struct drcom_context));
	pDrcomContext->Socket = -1;

	pDrcomContext->LocalAddr.sin_family = AF_INET;
	pDrcomContext->LocalAddr.sin_port = htons(nPort);
	pDrcomContext->ServerAddr.sin_family = AF_INET;
	pDrcomContext->ServerAddr.sin_port = htons(nPort);
	if ((pHost = gethostbyname(pServer)) == NULL)
	{
#ifdef DEBUG
		fprintf(stderr,"DrcomInit:Incorrect server %s", pServer);
#endif
		goto DrcomInitError;
	}
	memcpy(&pDrcomContext->ServerAddr.sin_addr, pHost->h_addr_list[0], sizeof(struct in_addr));
#ifdef DEBUG
	fprintf(stderr, "DrcomInit:IP address of server is %d.%d.%d.%d\n",
		(unsigned char)pHost->h_addr_list[0][0],
		(unsigned char)pHost->h_addr_list[0][1],
		(unsigned char)pHost->h_addr_list[0][2],
		(unsigned char)pHost->h_addr_list[0][3]);
#endif
    if ((pDrcomContext->Socket = socket(AF_INET, SOCK_DGRAM, 0)) == -1)
    {
#ifdef DEBUG
		perror("DrcomInit:socket()");
#endif
		goto DrcomInitError;
	}
	if (bind(pDrcomContext->Socket,
		(struct sockaddr *)&pDrcomContext->LocalAddr,
		sizeof(struct sockaddr)) < 0)
	{
#ifdef DEBUG
		perror("DrcomInit:bind()");
#endif
		goto DrcomInitError;
	}
	Timeout.tv_sec = nTimeoutSec;
	Timeout.tv_usec = 0;
	if (setsockopt(pDrcomContext->Socket, SOL_SOCKET, SO_RCVTIMEO, &Timeout, TimeoutLen) < 0)
	{
#ifdef DEBUG
		perror("DrcomInit:setsockopt(SO_RCVTIMEO)");
#endif
		goto DrcomInitError;
	}
	if (setsockopt(pDrcomContext->Socket, SOL_SOCKET, SO_SNDTIMEO, &Timeout, TimeoutLen) < 0)
	{
#ifdef DEBUG
		perror("DrcomInit:setsockopt(SO_SNDTIMEO)");
#endif
		goto DrcomInitError;
	}
	if (!DrcomGetLocalInfo(pDrcomContext))
	{
		goto DrcomInitError;
	}
#ifdef DEBUG
	fprintf(stderr, "DrcomInit:Init successfully\n");
#endif
	return pDrcomContext;

DrcomInitError:
#ifdef DEBUG
	fprintf(stderr, "DrcomInit:Failed to init\n");
#endif
	if (pDrcomContext && pDrcomContext->Socket != -1)
		close(pDrcomContext->Socket);
	if (pDrcomContext)
		free(pDrcomContext);
	return NULL;
}

void
DrcomRelease(
	struct drcom_context	**pDrcomContext
	)
{
	if (pDrcomContext && *pDrcomContext)
	{
		if ((*pDrcomContext)->Socket != -1)
			close((*pDrcomContext)->Socket);
		free(*pDrcomContext);
		*pDrcomContext = NULL;
	}
#ifdef DEBUG
	fprintf(stderr, "Release Drcom successfully\n");
#endif
}

BOOL
DrcomLogin(
	struct drcom_context	*pDrcomContext
	)
{
	int					nBufLength = 0;
	int					nBytesSent = 0;
	struct sockaddr_in	RecvAddr;
	int					RecvAddrLength = sizeof(struct sockaddr);
	struct msg_info	PacketType;

	if (pDrcomContext == NULL)
	{
#ifdef DEBUG
		fprintf(stderr, "DrcomLogin:Invalid Drcom info\n");
#endif
		return FALSE;
	}
#ifdef DEBUG
	fprintf(stderr, "DrcomLogin:Begin to login\n");
	fprintf(stderr, "DrcomLogin:Sending Request-packet...\n");
#endif
	pDrcomContext->DrcomInfo[0] = '\0';
	DrcomEncodePacket(pDrcomContext, DRCOM_REQUEST);
	if (!DrcomSendPacket(pDrcomContext))
		goto DrcomLoginError;
#ifdef DEBUG
	fprintf(stderr, "DrcomLogin:Request-packet is sent\n");
	fprintf(stderr, "DrcomLogin:Waiting for Challenge-packet...\n");
#endif
	while (1)
	{
		if (DrcomRecvPacket(pDrcomContext))
		{
			PacketType = DrcomDecodePacket(pDrcomContext);
			if (!PacketType.IsValid)
				continue;
			if (PacketType.Type == DRCOM_CHALLENGE)
			{
#ifdef DEBUG
				fprintf(stderr, "DrcomLogin:Challenge-packet is recieved\n");
#endif
				break;
			}
		}
		else
			goto DrcomLoginError;
	}
#ifdef DEBUG
	fprintf(stderr, "DrcomLogin:Sending Login-packet...\n");
#endif
	DrcomEncodePacket(pDrcomContext, DRCOM_LOGIN);
	if (!DrcomSendPacket(pDrcomContext))
		goto DrcomLoginError;
#ifdef DEBUG
	fprintf(stderr, "DrcomLogin:Login-packet is sent\n");
	fprintf(stderr, "DrcomLogin:Waiting for Success-packet or Fail-packet..\n");
#endif
	while (1)
	{
		if (DrcomRecvPacket(pDrcomContext))
		{
			PacketType = DrcomDecodePacket(pDrcomContext);
			if (!PacketType.IsValid)
				continue;
			if (PacketType.Type == DRCOM_SUCCESS)
			{
#ifdef DEBUG
				fprintf(stderr, "DrcomLogin:Success-packet is recieved\n");
#endif
				break;
			}
			if (PacketType.Type == DRCOM_FAIL)
			{
#ifdef DEBUG
				fprintf(stderr, "DrcomLogin:Fail-packet is recieved\n");
#endif
				goto DrcomLoginError;
			}
		}
		else
			goto DrcomLoginError;
	}
#ifdef DEBUG
	fprintf(stderr, "DrcomLogin:Login successfully\n");
#endif
	return TRUE;

DrcomLoginError:
#ifdef DEBUG
	fprintf(stderr, "DrcomLogin:Failed to login\n");
#endif
	return FALSE;
}

BOOL
DrcomLogout(
	struct drcom_context	*pDrcomContext
	)
{
	int					nBufLength = 0;
	int					nBytesSent = 0;
	struct sockaddr_in	RecvAddr;
	int					RecvAddrLength = sizeof(struct sockaddr);
	struct msg_info	PacketType;

	if (pDrcomContext == NULL)
	{
		fprintf(stderr, "DrcomLogout:Invalid Drcom info\n");
		return FALSE;
	}

#ifdef DEBUG
	fprintf(stderr, "DrcomLogout:Begin to logout\n");
	fprintf(stderr, "DrcomLogout:Sending Request-packet...\n");
#endif
	pDrcomContext->DrcomInfo[0] = '\0';
	DrcomEncodePacket(pDrcomContext, DRCOM_REQUEST);
	if (!DrcomSendPacket(pDrcomContext))
		goto DrcomLogoutError;
#ifdef DEBUG
	fprintf(stderr, "DrcomLogout:Request-packet is sent\n");
	fprintf(stderr, "DrcomLogout:Waiting for Challenge-packet...\n");
#endif
	while (1)
	{
		if (DrcomRecvPacket(pDrcomContext))
		{
			PacketType = DrcomDecodePacket(pDrcomContext);
			if (!PacketType.IsValid)
				continue;
			if (PacketType.Type == DRCOM_CHALLENGE)
			{
#ifdef DEBUG
				fprintf(stderr, "DrcomLogout:Challenge-packet is recieved\n");
#endif
				break;
			}
		}
		else
			goto DrcomLogoutError;
	}
#ifdef DEBUG
	fprintf(stderr, "DrcomLogout:Sending Logout-packet...\n");
#endif
	DrcomEncodePacket(pDrcomContext, DRCOM_LOGOUT);
	if (!DrcomSendPacket(pDrcomContext))
		goto DrcomLogoutError;
#ifdef DEBUG
	fprintf(stderr, "DrcomLogout:Logout-packet is sent\n");
	fprintf(stderr, "DrcomLogout:Waiting for Success-packet or Fail-packet...\n");
#endif
	while (1)
	{
		if (DrcomRecvPacket(pDrcomContext))
		{
			PacketType = DrcomDecodePacket(pDrcomContext);
			if (!PacketType.IsValid)
				continue;
			if (PacketType.Type == DRCOM_SUCCESS)
			{
#ifdef DEBUG
				fprintf(stderr, "DrcomLogout:Success-packet is recieved\n");
#endif
				break;
			}
			if (PacketType.Type == DRCOM_FAIL)
			{
#ifdef DEBUG
				fprintf(stderr, "DrcomLogout:Fail-packet is recieved\n");
#endif
				goto DrcomLogoutError;
			}
		}
		else
			goto DrcomLogoutError;
	}
#ifdef DEBUG
	fprintf(stderr, "DrcomLogout:Logout successfully\n");
#endif
	return TRUE;

DrcomLogoutError:
#ifdef DEBUG
	fprintf(stderr, "DrcomLogout:Failed to logout\n");
#endif
	return FALSE;
}

void
DrcomPrintAccountInfo(
	struct drcom_context	*pDrcomContext
	)
{
	unsigned long x, y;

	if (pDrcomContext == NULL)
	{
		fprintf(stderr, "DrcomPrintAccountInfo:Invalid drcom_context info\n");
		return;
	}

	if (pDrcomContext->IsTimeValid)
	{
		printf("The accumulted time: %lu Min\n", pDrcomContext->Time);

		x = pDrcomContext->Flux >> 10;
		y = pDrcomContext->Flux & 0x3ff;
		y = (y*1000)>>10;
		printf("The accumulated flux: %lu.%03lu MBytes\n", x, y);
	}
	if (pDrcomContext->IsBalanceValid)
	{
		x = pDrcomContext->Balance & 0x7fffffff;
		printf("The balance: %lu.%02lu Yuan\n", (x / 100), (x % 100));
	}
}

BOOL
DrcomPing(
	struct drcom_context	*pDrcomContext
	)
{
	if (pDrcomContext == NULL)
	{
		fprintf(stderr, "DrcomPing:Invalid drcom_context info\n");
		return FALSE;
	}

#ifdef DEBUG
	fprintf(stderr, "DrcomPing: Sending Ping-packet...\n");
#endif
	DrcomEncodePacket(pDrcomContext, DRCOM_PING);
	return DrcomSendPacket(pDrcomContext);
}

BOOL
DrcomKeepAlive(
	struct drcom_context	*pDrcomContext
	)
{
	struct msg_info	PacketType;

	if (pDrcomContext == NULL)
	{
		fprintf(stderr, "DrcomPing:Invalid drcom_context info\n");
		return FALSE;
	}

#ifdef DEBUG
	fprintf(stderr, "DrcomKeepAlive: Begin\n");
#endif

	while (1)
	{
		if (DrcomRecvPacket(pDrcomContext))
		{
			PacketType = DrcomDecodePacket(pDrcomContext);
			if (!PacketType.IsValid)
				continue;
			if (PacketType.Type == DRCOM_MESSAGE)
			{
#ifdef DEBUG
				fprintf(stderr, "DrcomKeepAlive:Message-packet is recieved\n");
#endif
				switch (PacketType.SubType)
				{
				case 0x26:
#ifdef DEBUG
					fprintf(stderr, "DrcomKeepAlive:Sending Reply-packet...\n");
#endif
					DrcomEncodePacket(pDrcomContext, DRCOM_REPLY);
					if (!DrcomSendPacket(pDrcomContext))
					{
						sprintf(pDrcomContext->DrcomInfo,
							"Failed to keep alive.");
#ifdef DEBUG
						fprintf(stderr, "DrcomKeepAlive:Failed to send Reply-packet\n");
#endif
						return FALSE;
					}
					break;

				default:
#ifdef DEBUG
					fprintf(stderr, "DrcomKeepAlive:Disconnected by server\n");
#endif
					return FALSE;
				}
			}
		}
		else
		{
			sprintf(pDrcomContext->DrcomInfo,
				"DrcomKeepAlive:Server may be down.");
			break;
		}
	}
#ifdef DEBUG
	fprintf(stderr, "DrcomKeepAlive: Failed\n");
#endif
	return FALSE;
}

