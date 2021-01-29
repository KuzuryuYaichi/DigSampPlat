/*
 * echo.h
 *
 *  Created on: 2019Äê8ÔÂ27ÈÕ
 *      Author: yankai
 */

#ifndef SRC_ECHO_H_
#define SRC_ECHO_H_

#include <stdio.h>
#include <string.h>
#include "lwip/err.h"
#include "lwip/udp.h"
#include "xil_printf.h"
#include "platform_config.h"
#include "stdbool.h"

int transfer_data(u8* data, int len);
err_t recv_callback(void *arg, struct tcp_pcb *tpcb, struct pbuf *p, err_t err);
void set_net_parameter(u32 p_ipaddr, u32 p_netmask, u32 p_gw);
int reset_application();
int tcp_close_application();
int start_application();
int transfer_data_udp(u8 *data, int len);
int start_application_udp(struct ip_addr *ipaddr);
unsigned char calc_tcp_send_data(u8 *data, int len);

#endif /* SRC_ECHO_H_ */
