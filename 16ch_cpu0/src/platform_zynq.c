/*
 *
 * Xilinx, Inc.
 * XILINX IS PROVIDING THIS DESIGN, CODE, OR INFORMATION "AS IS" AS A 
 * COURTESY TO YOU.  BY PROVIDING THIS DESIGN, CODE, OR INFORMATION AS
 * ONE POSSIBLE   IMPLEMENTATION OF THIS FEATURE, APPLICATION OR 
 * STANDARD, XILINX IS MAKING NO REPRESENTATION THAT THIS IMPLEMENTATION 
 * IS FREE FROM ANY CLAIMS OF INFRINGEMENT, AND YOU ARE RESPONSIBLE 
 * FOR OBTAINING ANY RIGHTS YOU MAY REQUIRE FOR YOUR IMPLEMENTATION
 * XILINX EXPRESSLY DISCLAIMS ANY WARRANTY WHATSOEVER WITH RESPECT TO 
 * THE ADEQUACY OF THE IMPLEMENTATION, INCLUDING BUT NOT LIMITED TO 
 * ANY WARRANTIES OR REPRESENTATIONS THAT THIS IMPLEMENTATION IS FREE 
 * FROM CLAIMS OF INFRINGEMENT, IMPLIED WARRANTIES OF MERCHANTABILITY 
 * AND FITNESS FOR A PARTICULAR PURPOSE.
 */

/*
 * 
 *
 * This file is a generated sample test application.
 *
 * This application is intended to test and/or illustrate some 
 * functionality of your system.  The contents of this file may
 * vary depending on the IP in your system and may use existing
 * IP driver functions.  These drivers will be generated in your
 * SDK application project when you run the "Generate Libraries" menu item.
 *
 */

#include <stdio.h>
#include "xparameters.h"
#include "xil_cache.h"
#include "xscugic.h"
#include "xil_exception.h"
#include "scugic_header.h"
#include "xscutimer.h"
#include "scutimer_header.h"
#include "xuartps.h"
#include "uartps_header.h"

#include "xqspips.h"
#include "qspips_header.h"
#include "xuartps.h"
#include "uartps_header.h"
#include "F2P_header.h"
static XScuGic intc;
XScuTimer TimerInstance;

int init_platform()
{
	print("---Entering platform_init---\n\r");
   
	int Status;
	Status = ScuGicInterruptSetup(&intc, XPAR_PS7_SCUGIC_0_DEVICE_ID);
	if (Status == 0) {
		print("ScuGic Interrupt Setup PASSED\r\n");
	}
	else {
		print("ScuGic Interrupt Setup FAILED\r\n");
	}

	print("\r\n Running Interrupt Test for ps7_scutimer_0...\r\n");
	Status = ScuTimerIntrExample(&intc, &TimerInstance, XPAR_XSCUTIMER_0_DEVICE_ID, XPAR_SCUTIMER_INTR);
	if (Status == 0) {
		print("ScuTimerIntrExample PASSED\r\n");
	}
	else {
		print("ScuTimerIntrExample FAILED\r\n");
	}

	print("\r\n Running QspiSelfTestExample() for ps7_qspi_0...\r\n");
	Status = QspiPsSelfTestExample(XPAR_PS7_QSPI_0_DEVICE_ID);
	if (Status == 0) {
		print("QspiPsSelfTestExample PASSED\r\n");
	}
	else {
		print("QspiPsSelfTestExample FAILED\r\n");
	}

	print("\r\nRunning FPGAToPsIntc0InitFunction() for F2P...\r\n");
	Status = F2PIntcInitFunction(&intc);
	if (Status == 0) {
		print("FPGAToPsIntc0InitFunction PASSED.\r\n");
	}
	else {
		print("FPGAToPsIntc0InitFunction FAILED.\r\n");
	}

    print("\r\n Running Interrupt Test for ps7_uart_1...\r\n");

    Status = UartPsIntrExample(&intc);
    if (Status == 0) {
       print("UartPsIntrExample PASSED\r\n");
    }
    else {
       print("UartPsIntrExample FAILED\r\n");
    }

	return 0;
}

