/**
 * FreeRDP: A Remote Desktop Protocol Implementation
 * Static Virtual Channel Interface
 *
 * Copyright 2009-2011 Jay Sorg
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/**
 * MS compatible SVC plugin interface
 * reference:
 * http://msdn.microsoft.com/en-us/library/aa383580.aspx
 */

#ifndef FREERDP_SVC_H
#define FREERDP_SVC_H

#include <freerdp/api.h>
#include <freerdp/types.h>
#include <freerdp/freerdp.h>

#if defined(_WIN32) && !defined(_UWP)

#include <pchannel.h>

#else

#define CHANNEL_EVENT_USER	1000

/**
 * Virtual Channel Protocol (pchannel.h)
 */

#define CHANNEL_CHUNK_LENGTH				1600

#define CHANNEL_PDU_LENGTH				(CHANNEL_CHUNK_LENGTH + sizeof(CHANNEL_PDU_HEADER))

#define CHANNEL_FLAG_FIRST				0x01
#define CHANNEL_FLAG_LAST				0x02
#define CHANNEL_FLAG_ONLY				(CHANNEL_FLAG_FIRST | CHANNEL_FLAG_LAST)
#define CHANNEL_FLAG_MIDDLE				0
#define CHANNEL_FLAG_FAIL				0x100

#define CHANNEL_OPTION_INITIALIZED			0x80000000

#define CHANNEL_OPTION_ENCRYPT_RDP			0x40000000
#define CHANNEL_OPTION_ENCRYPT_SC			0x20000000
#define CHANNEL_OPTION_ENCRYPT_CS			0x10000000
#define CHANNEL_OPTION_PRI_HIGH				0x08000000
#define CHANNEL_OPTION_PRI_MED				0x04000000
#define CHANNEL_OPTION_PRI_LOW				0x02000000
#define CHANNEL_OPTION_COMPRESS_RDP			0x00800000
#define CHANNEL_OPTION_COMPRESS				0x00400000
#define CHANNEL_OPTION_SHOW_PROTOCOL			0x00200000
#define CHANNEL_OPTION_REMOTE_CONTROL_PERSISTENT	0x00100000

#define CHANNEL_MAX_COUNT				31
#define CHANNEL_NAME_LEN				7

typedef struct tagCHANNEL_DEF
{
	char name[CHANNEL_NAME_LEN + 1];
	ULONG options;
} CHANNEL_DEF;
typedef CHANNEL_DEF* PCHANNEL_DEF;
typedef PCHANNEL_DEF* PPCHANNEL_DEF;

typedef struct tagCHANNEL_PDU_HEADER
{
	UINT32 length;
	UINT32 flags;
} CHANNEL_PDU_HEADER, *PCHANNEL_PDU_HEADER;

#endif /* _WIN32 */

#define CHANNEL_RC_OK					0
#define CHANNEL_RC_ALREADY_INITIALIZED			1
#define CHANNEL_RC_NOT_INITIALIZED			2
#define CHANNEL_RC_ALREADY_CONNECTED			3
#define CHANNEL_RC_NOT_CONNECTED			4
#define CHANNEL_RC_TOO_MANY_CHANNELS			5
#define CHANNEL_RC_BAD_CHANNEL				6
#define CHANNEL_RC_BAD_CHANNEL_HANDLE			7
#define CHANNEL_RC_NO_BUFFER				8
#define CHANNEL_RC_BAD_INIT_HANDLE			9
#define CHANNEL_RC_NOT_OPEN				10
#define CHANNEL_RC_BAD_PROC				11
#define CHANNEL_RC_NO_MEMORY				12
#define CHANNEL_RC_UNKNOWN_CHANNEL_NAME			13
#define CHANNEL_RC_ALREADY_OPEN				14
#define CHANNEL_RC_NOT_IN_VIRTUALCHANNELENTRY		15
#define CHANNEL_RC_NULL_DATA				16
#define CHANNEL_RC_ZERO_LENGTH				17
#define CHANNEL_RC_INVALID_INSTANCE			18
#define CHANNEL_RC_UNSUPPORTED_VERSION			19
#define CHANNEL_RC_INITIALIZATION_ERROR			20


/**
 * These channel flags are defined in some versions of pchannel.h only
 */

#ifndef CHANNEL_FLAG_SHOW_PROTOCOL
#define CHANNEL_FLAG_SHOW_PROTOCOL			0x10
#endif
#ifndef CHANNEL_FLAG_SUSPEND
#define CHANNEL_FLAG_SUSPEND				0x20
#endif
#ifndef CHANNEL_FLAG_RESUME
#define CHANNEL_FLAG_RESUME				0x40
#endif
#ifndef CHANNEL_FLAG_SHADOW_PERSISTENT
#define CHANNEL_FLAG_SHADOW_PERSISTENT			0x80
#endif


#define CHANNEL_EXPORT_FUNC_NAME "VirtualChannelEntry"

#define CHANNEL_NAME_LEN 7

typedef void (FREERDP_CC * PCHANNEL_INIT_EVENT_FN)(void* pInitHandle, UINT32 event, void* pData, UINT32 dataLength);
typedef void FREERDP_CC CHANNEL_INIT_EVENT_EX_FN(LPVOID lpUserParam,LPVOID pInitHandle,	UINT event,	LPVOID pData,	UINT dataLength);
typedef CHANNEL_INIT_EVENT_EX_FN* PCHANNEL_INIT_EVENT_EX_FN;
typedef void (FREERDP_CC * PCHANNEL_OPEN_EVENT_FN)(UINT32 openHandle, UINT32 event,
		void* pData, UINT32 dataLength, UINT32 totalLength, UINT32 dataFlags);
typedef void (FREERDP_CC * PCHANNEL_OPEN_EVENT_EX_FN)(LPVOID lpUserParam,	DWORD openHandle,	UINT event,	LPVOID pData,	UINT32 dataLength,	UINT32 totalLength,	UINT32 dataFlags);

#define CHANNEL_RC_OK					0
#define CHANNEL_RC_ALREADY_INITIALIZED			1
#define CHANNEL_RC_NOT_INITIALIZED			2
#define CHANNEL_RC_ALREADY_CONNECTED			3
#define CHANNEL_RC_NOT_CONNECTED			4
#define CHANNEL_RC_TOO_MANY_CHANNELS			5
#define CHANNEL_RC_BAD_CHANNEL				6
#define CHANNEL_RC_BAD_CHANNEL_HANDLE			7
#define CHANNEL_RC_NO_BUFFER				8
#define CHANNEL_RC_BAD_INIT_HANDLE			9
#define CHANNEL_RC_NOT_OPEN				10
#define CHANNEL_RC_BAD_PROC				11
#define CHANNEL_RC_NO_MEMORY				12
#define CHANNEL_RC_UNKNOWN_CHANNEL_NAME			13
#define CHANNEL_RC_ALREADY_OPEN				14
#define CHANNEL_RC_NOT_IN_VIRTUALCHANNELENTRY		15
#define CHANNEL_RC_NULL_DATA				16
#define CHANNEL_RC_ZERO_LENGTH				17

#define VIRTUAL_CHANNEL_VERSION_WIN2000			1

#ifdef _WIN32
#define VCAPITYPE __stdcall
#define VCEXPORT
#else
#define VCAPITYPE CALLBACK
#define VCEXPORT  __export
#endif

#define CHANNEL_EVENT_INITIALIZED			0
#define CHANNEL_EVENT_CONNECTED				1
#define CHANNEL_EVENT_V1_CONNECTED			2
#define CHANNEL_EVENT_DISCONNECTED			3
#define CHANNEL_EVENT_TERMINATED			4
#define CHANNEL_EVENT_REMOTE_CONTROL_START		5
#define CHANNEL_EVENT_REMOTE_CONTROL_STOP		6
#define CHANNEL_EVENT_ATTACHED				7
#define CHANNEL_EVENT_DETACHED				8
#define CHANNEL_EVENT_DATA_RECEIVED			10
#define CHANNEL_EVENT_WRITE_COMPLETE			11
#define CHANNEL_EVENT_WRITE_CANCELLED			12

typedef UINT32 (FREERDP_CC * PVIRTUALCHANNELINIT)(void** ppInitHandle, PCHANNEL_DEF pChannel,
		int channelCount, UINT32 versionRequested, PCHANNEL_INIT_EVENT_FN pChannelInitEventProc);
typedef UINT32 (VCAPITYPE * PVIRTUALCHANNELINITEX)(LPVOID lpUserParam,
	LPVOID clientContext,
	LPVOID pInitHandle,
	PCHANNEL_DEF pChannel,
	INT channelCount,	ULONG versionRequested,	PCHANNEL_INIT_EVENT_EX_FN pChannelInitEventProcEx);
typedef UINT32 (FREERDP_CC * PVIRTUALCHANNELOPEN)(void* pInitHandle, UINT32* pOpenHandle,char* pChannelName, PCHANNEL_OPEN_EVENT_FN pChannelOpenEventProc);
typedef UINT32 (VCAPITYPE * PVIRTUALCHANNELOPENEX)(LPVOID pInitHandle, LPDWORD pOpenHandle, PCHAR pChannelName, PCHANNEL_OPEN_EVENT_EX_FN pChannelOpenEventProcEx);
typedef UINT32 (FREERDP_CC * PVIRTUALCHANNELCLOSE)(UINT32 openHandle);
typedef UINT32 (VCAPITYPE * PVIRTUALCHANNELCLOSEEX)(LPVOID pInitHandle, DWORD openHandle);
typedef UINT32 (FREERDP_CC * PVIRTUALCHANNELWRITE)(UINT32 openHandle, void* pData, UINT32 dataLength, void* pUserData);
typedef UINT32 (VCAPITYPE * PVIRTUALCHANNELWRITEEX)(void* pInitHandle, DWORD openHandle, void* pData, ULONG dataLength, void* pUserData);
typedef UINT32 (FREERDP_CC * PVIRTUALCHANNELEVENTPUSH)(UINT32 openHandle, wMessage* event);

struct _CHANNEL_ENTRY_POINTS
{
	UINT32 cbSize;
	UINT32 protocolVersion;
	PVIRTUALCHANNELINIT  pVirtualChannelInit;
	PVIRTUALCHANNELOPEN  pVirtualChannelOpen;
	PVIRTUALCHANNELCLOSE pVirtualChannelClose;
	PVIRTUALCHANNELWRITE pVirtualChannelWrite;
};
typedef struct _CHANNEL_ENTRY_POINTS CHANNEL_ENTRY_POINTS;
typedef CHANNEL_ENTRY_POINTS* PCHANNEL_ENTRY_POINTS;

typedef int (FREERDP_CC * PVIRTUALCHANNELENTRY)(PCHANNEL_ENTRY_POINTS pEntryPoints);

#define FREERDP_CHANNEL_MAGIC_NUMBER	0x46524450

struct _CHANNEL_ENTRY_POINTS_EX
{
	UINT32 cbSize;
	UINT32 protocolVersion;
	PVIRTUALCHANNELINIT  pVirtualChannelInit;
	PVIRTUALCHANNELOPEN  pVirtualChannelOpen;
	PVIRTUALCHANNELCLOSE pVirtualChannelClose;
	PVIRTUALCHANNELWRITE pVirtualChannelWrite;

	/* Extended Fields */
	UINT32 MagicNumber; /* identifies FreeRDP */
	void* pExtendedData; /* extended initial data */
	void** ppInterface; /* channel callback interface */
	PVIRTUALCHANNELEVENTPUSH pVirtualChannelEventPush;
};
typedef struct _CHANNEL_ENTRY_POINTS_EX CHANNEL_ENTRY_POINTS_EX;
typedef CHANNEL_ENTRY_POINTS_EX* PCHANNEL_ENTRY_POINTS_EX;
typedef BOOL VCAPITYPE VIRTUALCHANNELENTRYEX(PCHANNEL_ENTRY_POINTS_EX
        pEntryPointsEx,
	PVOID pInitHandle);

typedef VIRTUALCHANNELENTRYEX* PVIRTUALCHANNELENTRYEX;
struct _CHANNEL_ENTRY_POINTS_FREERDP_EX
{
	UINT32 cbSize;
	UINT32 protocolVersion;
	PVIRTUALCHANNELINITEX pVirtualChannelInitEx;
	PVIRTUALCHANNELOPENEX  pVirtualChannelOpenEx;
	PVIRTUALCHANNELCLOSEEX pVirtualChannelCloseEx;
	PVIRTUALCHANNELWRITEEX pVirtualChannelWriteEx;

	/* Extended Fields */
	UINT32 MagicNumber; /* identifies FreeRDP */
	void* pExtendedData; /* extended initial data */
	void* pInterface; /* channel callback interface, use after initialization */
	void** ppInterface; /* channel callback interface, use for initialization */
	//rdpContext* context;
	PVIRTUALCHANNELEVENTPUSH pVirtualChannelEventPush;
	rdpContext* context;
};
typedef struct _CHANNEL_ENTRY_POINTS_FREERDP_EX CHANNEL_ENTRY_POINTS_FREERDP_EX;
typedef CHANNEL_ENTRY_POINTS_FREERDP_EX* PCHANNEL_ENTRY_POINTS_FREERDP_EX;

#endif /* FREERDP_SVC_H */
