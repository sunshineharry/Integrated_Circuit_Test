// MySocket.h: interface for the MySocket class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MYSOCKET_H__25E46640_3897_491B_A6A3_C9C17FCDEF42__INCLUDED_)
#define AFX_MYSOCKET_H__25E46640_3897_491B_A6A3_C9C17FCDEF42__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <afxsock.h>
#define SOCKNUM 50
#define READBUFFERNUM 4
#define WRITEBUFFERNUM 4
#define TRANS32(x) (((x&0xff)<<24)|((x&0xff00)<<8)|((x&0xff0000)>>8)|((x&0xff000000)>>24))
#define FILEPERBUFFER (8*1024*1024)
#define READREGBYTES (256*4+10)
typedef BOOL(*LPFNDLLFUNC)(int);  
static int gb_sock_index;
static unsigned int client[SOCKNUM];
class _declspec(dllexport) MySocket  
{
public:
	MySocket();
	virtual ~MySocket();

public:
	void MySocket::sockInitProcessAddr(LPFNDLLFUNC lpf);
	//接口
	int ConnectToTarget(char *m_ip,int m_port);//连接设备IP
	void DisConnectClient(int fd);//断开IP设备
	

	BOOL WriteMulRegister(int fd,UINT* paddr,UINT* pdata,int num);//参数：对应IP的设备，写地址数组，对应的写地址数据数组，写寄存器个数
	int  ReadMulRegister(int fd,UINT addr,UINT *pdata);//对应IP的设备，初始地址（一般为0），返回的数据数组（256个寄存器）。

	BOOL MySocket::WriteFIFO(int fd,UINT addr,WORD *pdata, DWORD len);
	BOOL MySocket::ReadFIFO(int fd,UINT addr,WORD *pRdata,unsigned int dataLen);
	
	
private:

	char gb_head[8];
	DWORD bRecvDataLen;

	//环形队列读指针和写指针
	int reader[SOCKNUM];
	int writer[SOCKNUM];

	unsigned int FIFOSendByte[SOCKNUM];
	unsigned int FIFORecvByte[SOCKNUM];
};

#endif // !defined(AFX_MYSOCKET_H__25E46640_3897_491B_A6A3_C9C17FCDEF42__INCLUDED_)
