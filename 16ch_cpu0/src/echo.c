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
#include <string.h>
#include "lwip/err.h"
#include "lwip/tcp.h"
#include "lwip/udp.h"
#if defined (__arm__) || defined (__aarch64__)
#include "xil_printf.h"
#endif
#include "platform_config.h"
#include "platform.h"
#include "echo.h"
#include "display_ctrl.h"

#define REVB_BUFSIZE	(300)
#define SEND_BUFSIZE	(1100)
#define SEND_LENGTH  (1024)

u16 send_num = 0;
unsigned WORK_STATE = 0;
int net_recv_len = 0;

extern u8 WorkModeFlag;
extern struct netif *echo_netif;
struct tcp_pcb *connected_pcb = NULL;
struct udp_pcb *connected_pcb_udp = NULL;
int UdpSwitch = 1;

u8 recv_buf[REVB_BUFSIZE];
u16 recv_buf1[REVB_BUFSIZE];

extern struct CONFIG_POS_STRUCT *ConfigPosStruct;

void CheckDataLED()
{
	if(connected_pcb && connected_pcb->state != CLOSED)
		ConnectedFlag = 1;
	else
		ConnectedFlag = 0;
}

int fMin(int a,int b)
{
	return (a < b) ? a : b;
}

int transfer_data(u8* send_buf,int len)
{
	err_t err;
	struct tcp_pcb *tpcb = connected_pcb;

	if (!connected_pcb)
	{
		UdpSwitch = 1;
		return ERR_OK;
	}
	UdpSwitch = 0;

	/*  transfer data of send_buf to eth0  */
	if (tcp_sndbuf(tpcb) > len) {
		err = tcp_write(tpcb, send_buf, len, 1);//先往tpcb口写数据
		if (err != ERR_OK) {
			xil_printf("Error on tcp_write: %d\r\n", err);
			connected_pcb = NULL;
			return -1;
		}
		err = tcp_output(tpcb);//
		if (err != ERR_OK) {
			xil_printf("Error on tcp_output: %d\r\n",err);
			return -1;
		}
		send_num++;

	}
	else
	{
		xil_printf("Error on memmap: %d\r\n");
		return 0;
	}

	return 0;
}

err_t sent_callback(void *arg, struct tcp_pcb *tpcb,u16_t len)
{
	return ERR_OK;
}

#define FLASH_NET_ADDR 0xFF0000

void FlashRead_NW()
{
	u8 temp_buff[12];
	FlashRead(FLASH_NET_ADDR, 3*4, temp_buff);
	memcpy(ConfigPosStruct[LCD_CHECKED_IP].s_data, temp_buff + 0, 4);
	memcpy(ConfigPosStruct[LCD_CHECKED_MASK].s_data, temp_buff + 4, 4);
	memcpy(ConfigPosStruct[LCD_CHECKED_GATE].s_data, temp_buff + 8, 4);
}

void FlashWrite_NW(u8 *DataSrc)
{
	FlashErase(FLASH_NET_ADDR, 4*3);
	FlashWrite(FLASH_NET_ADDR, 4*3, DataSrc);
}

#define FLASH_SAMPLE_ADDR 0xFE0000

extern u16 SampleState;

void FlashRead_SampleMode()
{
	u8 temp_buff[2];
	FlashRead(FLASH_SAMPLE_ADDR, 2, temp_buff);
	SampleState = (temp_buff[0] << 8) | temp_buff[1];
	Set_Sample_Mode(SampleState);
	SampleState = Get_Sample_Mode();
}

void FlashWrite_SampleMode(u8 *DataSrc)
{
	FlashErase(FLASH_SAMPLE_ADDR, 2);
	FlashWrite(FLASH_SAMPLE_ADDR, 2, DataSrc);
}

void modify_flash_net_config()
{
	u8 flash_ip_data[12];
	memcpy(&flash_ip_data[0], ConfigPosStruct[LCD_CHECKED_IP].s_data, 4);
	memcpy(&flash_ip_data[4], ConfigPosStruct[LCD_CHECKED_MASK].s_data, 4);
	memcpy(&flash_ip_data[8], ConfigPosStruct[LCD_CHECKED_GATE].s_data, 4);
	FlashWrite_NW(flash_ip_data);
	FlashRead_NW();
	set_net_parameter(*(u32*)ConfigPosStruct[LCD_CHECKED_IP].s_data,
			*(u32*)ConfigPosStruct[LCD_CHECKED_MASK].s_data,
			*(u32*)ConfigPosStruct[LCD_CHECKED_GATE].s_data);
}

int Check_Tcp_Data(u8 *data, int len)
{
	u8 DataAck[32] = {0};
	if(data[0] == 0xAA && data[1] == 0xBB && data[2] == 0x01 && data[3] == 0x00)
	{
		memcpy(DataAck, data, len);
		DataAck[2] = 0x11;
		transfer_data(DataAck, len);
		FlashWrite_NW(DataAck+6);
		FlashRead_NW();
		set_net_parameter(*(u32*)ConfigPosStruct[LCD_CHECKED_IP].s_data,
					*(u32*)ConfigPosStruct[LCD_CHECKED_MASK].s_data,
					*(u32*)ConfigPosStruct[LCD_CHECKED_GATE].s_data);
		return 0;
	}
	else if(data[0] == 0xAA && data[1] == 0xBB && data[2] == 0x01 && data[3] == 0x01)
	{
		memcpy(DataAck, data, len);
		DataAck[2] = 0x11;
		transfer_data(DataAck, len);
		FlashWrite_SampleMode(DataAck+4);
		FlashRead_SampleMode();
		return 0;
	}
	return -1;
}

err_t recv_callback(void *arg, struct tcp_pcb *tpcb, struct pbuf *p, err_t err)
{
	/* do not read the packet if we are not in ESTABLISHED state */
	if (!p) {
		tcp_close(tpcb);
		tcp_recv(tpcb, NULL);
		return ERR_OK;
	}
	/* indicate that the packet has been received */
	tcp_recved(tpcb, p->len);
	/*copy receive data to recv_buf and print out by uart*/
	memcpy(&recv_buf, p->payload, p->len);
	net_recv_len = p->len;
	pbuf_free(p);
	WORK_STATE = 1;
	return ERR_OK;
}

err_t accept_callback(void *arg, struct tcp_pcb *newpcb, err_t err)
{
	static int connection = 1;

	/* store state */
	connected_pcb = newpcb;

	/* set the receive callback for this connection */
	tcp_recv(newpcb, recv_callback);

	/* set the sent callback for this connection */
	tcp_sent(newpcb, sent_callback);

	/* just use an integer number indicating the connection id as the
	   callback argument */
	tcp_arg(newpcb, (void*)connection);

	/* increment for subsequent accepted connections */
	++connection;

	return ERR_OK;
}


int start_application()
{
	struct tcp_pcb *pcb;
	err_t err;
	unsigned port = 8000;

	/* create new TCP PCB structure */
	pcb = tcp_new();
	if (!pcb) {
		xil_printf("Error creating PCB. Out of Memory\n\r");
		return -1;
	}

	/* bind to specified @port */
	err = tcp_bind(pcb, IP_ADDR_ANY, port);
	if (err != ERR_OK) {
		xil_printf("Unable to bind to port %d: err = %d\n\r", port, err);
		return -2;
	}

	/* we do not need any arguments to callback functions */
	tcp_arg(pcb, NULL);

	/* listen for connections */
	pcb = tcp_listen(pcb);
	if (!pcb) {
		xil_printf("Out of memory while tcp_listen\n\r");
		return -3;
	}

	/* specify callback to use for incoming connections */
	tcp_accept(pcb, accept_callback);

	xil_printf("TCP echo server started @ port %d\n\r", port);

	return 0;
}

int tcp_close_application()
{
	struct tcp_pcb *tpcb = connected_pcb;
	err_t err;
	err = tcp_close(tpcb);
	if (err != ERR_OK) {
		xil_printf("error close condation is : err = %d\n\r", err);
		return -2;
	}
	return 0;
}

int reset_application()
{
	struct tcp_pcb *tpcb = connected_pcb;
	err_t err;
	unsigned port = 8000;

	/* bind to specified @port */
	err = tcp_bind(tpcb, IP_ADDR_ANY, port);
	if (err != ERR_OK) {
		xil_printf("Unable to bind to port %d: err = %d\n\r", port, err);
		return -2;
	}
	return 0;
}

void set_net_parameter(u32 p_ipaddr, u32 p_netmask, u32 p_gw)
{
	struct ip_addr ipaddr, netmask, gw;
	ipaddr.addr = p_ipaddr;
	netmask.addr = p_netmask;
	gw.addr = p_gw;
	netif_set_ipaddr(echo_netif, &ipaddr);
	netif_set_netmask(echo_netif, &netmask);
	netif_set_gw(echo_netif, &gw);
	reset_application();
}

u8 data_udp_fifo[36] = {0};
int transfer_data_udp(u8* data,int len)
{
	struct udp_pcb *upcb = connected_pcb_udp;
	struct pbuf *p;
	err_t res = 0;
	if (!connected_pcb_udp)
	{
		xil_printf("Waiting for incoming connections!\r\n");
		return ERR_OK;
	}
	memcpy(data_udp_fifo,data,len);
	p = pbuf_alloc(PBUF_TRANSPORT, len, PBUF_POOL);
	if(p != NULL)
	{
		p->payload = (void*)data_udp_fifo;//存到指向的存储区域
		res = udp_send(upcb, p);//
		pbuf_free(p);
	}
	return 0;
}

void recv_callback_udp(void *arg, struct udp_pcb *tpcb, struct pbuf *p,ip_addr_t *addr, u16_t port)
{
	/* do not read the packet if we are not in ESTABLISHED state */
	if (!p) {
		xil_printf("pbuf create error!\r\n");
		udp_disconnect(tpcb);
		udp_remove(tpcb);
	}
	pbuf_free(p);
}


int start_application_udp(struct ip_addr *ipaddr)
{
	struct udp_pcb *pcb;
	err_t err;
	unsigned remoteport = 8010;
	unsigned localport  = 8090;

	/* create new UDP PCB structure */
	pcb = udp_new();
	if (!pcb) {
		xil_printf("Error creating PCB. Out of Memory\n\r");
		return -1;
	}

	pcb->remote_ip=*ipaddr;
	pcb->remote_port=remoteport;

	err = udp_bind(pcb, IP_ADDR_ANY, localport);
	if (err != ERR_OK) {
		xil_printf("Unable to bind to port %d: err = %d\n\r", localport, err);
		return -2;
	}

	/* specify callback to use for incoming connections */
	udp_recv(pcb,recv_callback_udp,NULL);

	connected_pcb_udp = pcb;

	xil_printf("UDP server started @ port %d\n\r", localport);

	return 0;
}

unsigned char calc_tcp_send_data(u8 *data, int len)
{
	u32 datalen = len - 12;
	u8 senddata[2048] = {0};
	//head
	senddata[0] = 0xAA;
	senddata[1] = 0xBB;
	//mode
	senddata[2] = 0xFF;
	//type
	senddata[3] = data[3];
	//length
	senddata[4] = (datalen >> 24) & 0xff;
	senddata[5] = (datalen >> 16) & 0xff;
	senddata[6] = (datalen >> 8) & 0xff;
	senddata[7] = datalen & 0xff;
	//send times
	senddata[8] = (send_num >> 8) & 0xff;
	senddata[9] = send_num & 0xff;
	memcpy(senddata+10, data+4, len-12);
	transfer_data(senddata, len-2);
	return senddata[3];
}

void test_tcp_frame()
{
	u16 xor = 0;
	int i,j = 0;
	u8 data[SEND_LENGTH] = {0};
	send_num++;
	//head
	data[0] = 0xaa;
	data[1] = 0xbb;
	//mode
	data[2] = 0xff;
	//type
	data[3] = 0x01;//send_num%16;
	//length
	data[4] = 0x00;
	data[5] = 0x00;
	data[6] = 0x02;
	data[7] = 0x00;
	//send times
	data[8] = (u8) ((send_num & 0xff00) >>8);
	data[9] = (u8)(send_num & 0x00ff);
	for(i= 10;i<SEND_LENGTH-3;i++)
	{
		data[10] = 0x55;
	}
	for(j=3;j<SEND_LENGTH-3;j++)
	{
		xor = data[j] + xor;
	}
	data[SEND_LENGTH-2] = (u8)((xor & 0xff00) >> 8);
	data[SEND_LENGTH-1] = (u8)(xor & 0x00ff);
	transfer_data(data,SEND_LENGTH);
}
