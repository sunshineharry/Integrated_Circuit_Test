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
	//�ӿ�
	int ConnectToTarget(char *m_ip,int m_port);//�����豸IP
	void DisConnectClient(int fd);//�Ͽ�IP�豸
	

	BOOL WriteMulRegister(int fd,UINT* paddr,UINT* pdata,int num);//��������ӦIP���豸��д��ַ���飬��Ӧ��д��ַ�������飬д�Ĵ�������
	int  ReadMulRegister(int fd,UINT addr,UINT *pdata);//��ӦIP���豸����ʼ��ַ��һ��Ϊ0�������ص��������飨256���Ĵ�������

	BOOL MySocket::WriteFIFO(int fd,UINT addr,WORD *pdata, DWORD len);
	BOOL MySocket::ReadFIFO(int fd,UINT addr,WORD *pRdata,unsigned int dataLen);
	
	
private:

	char gb_head[8];
	DWORD bRecvDataLen;

	//���ζ��ж�ָ���дָ��
	int reader[SOCKNUM];
	int writer[SOCKNUM];

	unsigned int FIFOSendByte[SOCKNUM];
	unsigned int FIFORecvByte[SOCKNUM];
};

#endif // !defined(AFX_MYSOCKET_H__25E46640_3897_491B_A6A3_C9C17FCDEF42__INCLUDED_)
