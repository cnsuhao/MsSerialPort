#include "MsSerialPort.hpp"
#include <iostream>

class Serial:public IProcRevDat
{
	virtual void ProcessReadByte(BYTE *dat,UINT DatSize)
	{
		for (UINT i = 0 ; i < DatSize;++i)
		{
			printf("%0X ",dat[i]);
		}
		cout<<endl;
	}
	virtual void InitRevMsgCheck()
	{//实现该函数进行数据校验

		//数据长度为5，首尾必须为0
		m_MsgLen = 5;
		m_Pos_ChekVal[0] = 0x00;
		m_Pos_ChekVal[4] = 0x00;
	}

	CMsSerialPort m_CMsSerialPort;
public:
	void Run()
	{
		m_CMsSerialPort.Start(1,9600,this);
		
		char Msg[SerialPort_REV_MAX] = {0};
		while (true)
		{
			memset(Msg,0,SerialPort_REV_MAX);
			cout<<endl;
			cin.getline(Msg,SerialPort_REV_MAX);
			int len = strlen(Msg);
			m_CMsSerialPort.WriteData((BYTE*)Msg,len);
		}
	}
};


void main()
{
	Serial().Run();
}