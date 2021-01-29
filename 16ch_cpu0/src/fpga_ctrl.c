/*
 * fpga_ctrl.c
 *
 *      Author: Administrator
 *
	-- FPGA CHAN parameters.
 *
 */
#include <stdio.h>
#include "xparameters.h"
#include "xil_cache.h"
#include "xscugic.h"
#include "xil_exception.h"
#include "xil_io.h"
#include "fpga_ctrl.h"
#include "math.h"

void set_fixed_data(u16 value,int len)
{
	int i;
	int len_4 = len/4;
	for(i = 0;i<len_4;i++)//
	{
		//0x4000000c
		//0x40000010
		//0x40000014
		//0x40000018
		//4的倍数：
		Xil_Out16(XPAR_FPGA_BASEADDR+0x000c+i*4,value);//个数
	}
}

void set_tx_data(u8 *buf_tx,int len)
{
	int i;
	u16 data;
	for(i = 0; i < len; i++)
	{
		data=buf_tx[2*i]<<8|buf_tx[2*i+1];
		Xil_Out16(XPAR_FPGA_BASEADDR + P2F_DATA_OFFSETADDR + i*4, data );
	}
}

void get_rx_data4(u32 *buf_rx,int len)
{
	int i;

	for(i = 0; i < len/4; i++)
	{
		*(buf_rx + i) = Xil_In32(XPAR_FPGA_BASEADDR + 4*i+32*4);
	}
}

void get_rx_data(u8 *buf_rx,int len)
{
	int i;

	for(i = 0; i < len; i++)
	{
		*(buf_rx + i) = Xil_In8(XPAR_FPGA_BASEADDR + i+32*4);
	}
}

void get_rx_data_16bit(u16 *buf_rx,int len)
{
	int i;

	for(i = 0; i < len/2; i++)
	{
		*(buf_rx + i) = Xil_In16(XPAR_FPGA_BASEADDR + i*2+32*4);
	}
}

void get_rx_data_32bit(u32 *buf_rx,int len)
{
	int i;

	for(i = 0; i < len/4; i+=1)
	{
		*(buf_rx + i) = Xil_In32(XPAR_FPGA_BASEADDR + 4*i+32*4);
	}
}

void set_PS_Busy_State(u32 state)
{
	Xil_Out32(XPAR_FPGA_BASEADDR + P2F_STATE_OFFSETADDR + 4, state);
}

void set_PS_Date_Ready_Flag(u32 state)
{
	Xil_Out32(XPAR_FPGA_BASEADDR + P2F_STATE_OFFSETADDR/* + 1*/, state);
}

u32 get_PS_Date_Ready_Flag(void)
{
	return Xil_In32(XPAR_FPGA_BASEADDR + P2F_STATE_OFFSETADDR);
}

u32 get_FPGA_Busy_State(void)
{
	return Xil_In32(XPAR_FPGA_BASEADDR + F2P_STATE_OFFSETADDR);
}

u32 get_FPGA_Heartbeat_State(void)
{
	return Xil_In32(XPAR_FPGA_BASEADDR + 12);
}

void Set_Fpga_Busy(void)
{
	Xil_Out8(XPAR_FPGA_BASEADDR,0xBB);
}

void Set_Fpga_Ready(void)
{
	Xil_Out8(XPAR_FPGA_BASEADDR,0xAA);
}

u16 Get_Sample_Mode(void)
{
	return Xil_In16(XPAR_FPGA_BASEADDR + 0x14);
}

void Set_Sample_Mode(u16 state)
{
	Xil_Out16(XPAR_FPGA_BASEADDR + 0x14, state);
}

u32 Get_WorkTime(void)
{
	return Xil_In32(XPAR_FPGA_BASEADDR + 0x08);
}

u32 Get_UpWorkTime(void)
{
	return Xil_In32(XPAR_FPGA_BASEADDR + 0x0C);
}
