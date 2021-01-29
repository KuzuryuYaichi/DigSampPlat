#ifndef _FPGA_CTRL_H_
#define _FPGA_CTRL_H_
#include "xparameters_ps.h"

#define XPAR_FPGA_BASEADDR XPAR_DIGSAMP_0_BASEADDR
#define P2F_DATA_OFFSETADDR			0x00010000
#define P2F_STATE_OFFSETADDR		0x00020000
#define F2P_STATE_OFFSETADDR		12

void set_tx_data(u8 *buf,int len);
void get_rx_data(u8 *buf,int len);
void get_rx_data4(u32 *buf,int len);
void set_PS_Busy_State(u32 state);
void set_PS_Date_Ready_Flag(u32 state);
u32 get_PS_Date_Ready_Flag(void);
u32 get_FPGA_Busy_State(void);
u32 get_FPGA_Heartbeat_State(void);
//向固定地址中写入固定的数据
void set_fixed_data(u16 value,int len);
void get_rx_data_16bit(u16 *buf_rx,int len);
void get_rx_data_32bit(u32 *buf_rx,int len);
void Set_Fpga_Busy(void);


void Set_Fpga_Ready(void);

#endif
