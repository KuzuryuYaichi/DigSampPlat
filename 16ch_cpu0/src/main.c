/******************************************************************************
*
* Copyright (C) 2009 - 2014 Xilinx, Inc.  All rights reserved.
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
*
* Use of the Software is limited solely to applications:
* (a) running on a Xilinx device, or
* (b) that interact with a Xilinx device through a bus or interconnect.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
* XILINX  BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
* WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF
* OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE.
*
* Except as contained in this notice, the name of the Xilinx shall not be used
* in advertising or otherwise to promote the sale, use or other dealings in
* this Software without prior written authorization from Xilinx.
*
******************************************************************************/

#include <stdio.h>
#include "xparameters.h"
#include "netif/xadapter.h"
#include "platform.h"
#include "echo.h"
#include "platform_config.h"
#include "display_ctrl.h"

#include "lwip/tcp.h"
#include "xil_cache.h"
#include "fpga_ctrl.h"
#include "sleep.h"
#include "uartps_header.h"

/* defined by each RAW mode application */
int start_application();

/* missing declaration in lwIP */
void lwip_init();

struct netif *echo_netif;
extern u8 UARTWorkMode;
extern u8 WORK_STATE;
extern u8 recv_buf[];
extern int net_recv_len;
extern u8 Fpga_data[];
extern u8 F2PInt1;
extern u8 RecvBuffer[TEST_BUFFER_SIZE];
static struct netif server_netif;
extern struct CONFIG_POS_STRUCT *ConfigPosStruct;

int Udp_Send_num = 0;

#define sev() __asm__("sev")
#define CPU1STARTADR 0xFFFFFFF0
#define CPU1STARTMEM 0x20000000

void StartCpu1(void)
{
	/* Write the address of the application for CPU1 to 0xFFFFFFF0 */
	Xil_Out32(CPU1STARTADR, CPU1STARTMEM);
	dmb();
	/* Execute the SEV instruction to cause CPU1 to wake up and jump to the application */
	sev();
}

u8 FpgaState[36];
u16 SampleState;

int main()
{
	/* Disable cache on OCM  S=b1 TEX=b100 AP=b11, Domain=b1111, C=b0, B=b0 */
	Xil_SetTlbAttributes(0xFFFF0000,0x14de2);

	u8 DataBck[24] = {0xAA, 0xBB, 0x10, 0x00, 0x00, 0x00, 0x00, 0x04};
	u16 UartCheckSum = 0;
	struct ip_addr ipaddr_remote;

	/* the mac address of the board. this should be unique per board */
	unsigned char mac_ethernet_address[] = {0x00, 0x0a, 0x35, 0x00, 0x01, 0x02};
	echo_netif = &server_netif;
	init_platform();
	CPU1_Sync_StartFlag = 0;
	FlashReadUID(mac_ethernet_address);
	FlashRead_NW();
	FlashRead_SampleMode();
	/* Wake up CPU1 */
	StartCpu1();

	/* initliaze IP addresses to be used */
	IP4_ADDR(&ipaddr_remote, 255, 255, 255, 255);

	lwip_init();

  	/* Add network interface to the netif_list, and set it as default */
	if (!xemac_add(echo_netif,
					ConfigPosStruct[LCD_CHECKED_IP].s_data,
					ConfigPosStruct[LCD_CHECKED_MASK].s_data,
					ConfigPosStruct[LCD_CHECKED_GATE].s_data,
					mac_ethernet_address,
					PLATFORM_EMAC_BASEADDR))
	{
		xil_printf("Error adding N/W interface\n\r");
		return -1;
	}
	netif_set_default(echo_netif);

	/* specify that the network if is up */
	netif_set_up(echo_netif);

	/* start the application (web server, rxtest, txtest, etc..) */
	start_application();

	start_application_udp(&ipaddr_remote);

	Set_Fpga_Ready();

	CPU1_Sync_StartFlag = 1;

	while(1)
	{
		xemacif_input(echo_netif);

		SampleState = Get_Sample_Mode();

		CheckDataLED();

		if(UARTWorkMode == 1)
		{
			UARTWorkMode = 0;
			if(RecvBuffer[0] == 0xAA && RecvBuffer[1] == 0xBB)
			{
				if(RecvBuffer[2] == 0x01) 	// 写命令
				{
					SendXUart(RecvBuffer, 20);
					FlashWrite_NW(RecvBuffer+6);
					FlashRead_NW();
					set_net_parameter(*(u32*)ConfigPosStruct[LCD_CHECKED_IP].s_data,
									*(u32*)ConfigPosStruct[LCD_CHECKED_MASK].s_data,
									*(u32*)ConfigPosStruct[LCD_CHECKED_GATE].s_data);
					CPU0_2_CPU1_UpdateLCDFlag = 1;
				}
				else if(RecvBuffer[3] == 0x00) //读命令
				{
					static u16 UartBack = 0;
					DataBck[4] = (UartBack >> 8) & 0xff;
					DataBck[5] = UartBack & 0xff;
					FlashRead_NW();
					memcpy(&DataBck[6], ConfigPosStruct[LCD_CHECKED_IP].s_data, 4);
					memcpy(&DataBck[10], ConfigPosStruct[LCD_CHECKED_MASK].s_data, 4);
					memcpy(&DataBck[14], ConfigPosStruct[LCD_CHECKED_GATE].s_data, 4);
					int i;
					for(i=3;i<18;i++)
					{
						UartCheckSum += DataBck[i];
					}
					DataBck[18] = (UartCheckSum >> 8) & 0xff;
					DataBck[19] = UartCheckSum & 0xff;
					++UartBack;
					SendXUart(DataBck, 20);
				}
			}
		}

		if(CPU1_2_CPU0_UpdateLCDFlashFlag)
		{
			CPU1_2_CPU0_UpdateLCDFlashFlag = 0;
			SampleState = Get_Sample_Mode();
			u16 SampleStateTmp = (SampleState << 8) | (SampleState >> 8);
			FlashWrite_SampleMode(&SampleStateTmp);
		}

		//CPU1给CPU0发送的消息标识
		if(CPU1_2_CPU0_UpdateNetFlag)
		{
			CPU1_2_CPU0_UpdateNetFlag = 0;
			modify_flash_net_config();
			CPU0_2_CPU1_UpdateLCDFlag = 1;
		}
		//上位机的配置命令标识
		if(WORK_STATE)
		{
			WORK_STATE = 0;
			Check_Tcp_Data(recv_buf, net_recv_len);
			CPU0_2_CPU1_UpdateLCDFlag = 1;
		}

		const int TRANS_LENGTH = 354 * 4 + 4 + 28;
		//FPGA的数据传输中断
		if(F2PInt1)
		{
			F2PInt1 = 0;
			calc_tcp_send_data(Fpga_data, TRANS_LENGTH);
			if((Fpga_data[3] & 0x0f) < 16)
			{
				FpgaState[(Fpga_data[3] & 0xF) + 4] = 1;
			}
			Set_Fpga_Ready();
		}

		//定时器1s一次的广播包
		if(Udp_Send_num > 100)
		{
			Udp_Send_num = 0;
			FpgaState[0] = 0xAA;
			FpgaState[1] = 0xBB;
			FpgaState[2] = 0xCC;
			FpgaState[3] = 0x00;
			FpgaState[20] = mac_ethernet_address[0];
			FpgaState[21] = mac_ethernet_address[1];
			FpgaState[22] = mac_ethernet_address[2];
			FpgaState[23] = mac_ethernet_address[3];
			FpgaState[24] = mac_ethernet_address[4];
			FpgaState[25] = mac_ethernet_address[5];
			memcpy(FpgaState + 26, ConfigPosStruct[LCD_CHECKED_MASK].s_data, 4);
			memcpy(FpgaState + 30, ConfigPosStruct[LCD_CHECKED_GATE].s_data, 4);
			FpgaState[34] = (SampleState >> 8) & 0xFF;
			FpgaState[35] = SampleState & 0xFF;
			transfer_data_udp(FpgaState,36);
			memset(FpgaState,0,36);
		}
	}

	/* never reached */
	cleanup_platform();

	return 0;
}
