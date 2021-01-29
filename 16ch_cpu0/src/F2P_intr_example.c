#include "xparameters.h"
#include "platform.h"
#include "platform_config.h"
#include "F2P_header.h"
#include "stdio.h"
#include "xstatus.h"
#include "xscugic.h"
#include "xdebug.h"
#include "xil_exception.h"
#include "xil_cache.h"
#include "fpga_ctrl.h"
#include "echo.h"
/************************** Constant Definitions ****************************/

u8 Fpga_data[2048] = {0};
u32 Fpga_data4[512] = {0};

/*
#define HEARTBEAT_START_ID		XPAR_FABRIC_SYSTEM_BEAT_START_INTR
#define HEARTBEAT_STOP_ID		XPAR_FABRIC_SYSTEM_BEAT_END_INTR
*/
#define INT_TYPE_RISING_EDGE	0X03
#define INT_TYPE_HIGHLEVEL		0x01
#define INT_TYPE_MASK			0x03
#define INT_CFG0_OFFSET			0x00000C00


/**************************** Type Definitions ******************************/


/***************** Macros (Inline Functions) Definitions *******************/


/************************** Function Prototypes ****************************/


void IntcTypeSetup(XScuGic *IntcInstancePtr, int IntrID, int IntrType);

void F2P_intr_Handler(void *CallBackRef);

int F2PIntcInitFunction(XScuGic *IntcInstancePtr);



u8 F2PInt1 = 0;



/*****************************************************************************/
/**
*
* This function does a minimal test on the GPIO device configured as OUTPUT
* and driver as a  example.
*
*
* @param	DeviceId is the XPAR_<GPIO_instance>_DEVICE_ID value from
*		xparameters.h
* @param	GpioWidth is the width of the GPIO
*
* @return	XST_SUCCESS if successful, XST_FAILURE if unsuccessful
*
* @note		None
*
****************************************************************************/
void IntcTypeSetup(XScuGic *IntcInstancePtr, int IntrID, int IntrType)
{
	int mask;

	IntrType &= INT_TYPE_MASK;

	mask = XScuGic_DistReadReg( IntcInstancePtr, INT_CFG0_OFFSET + (IntrID/16)*4);
	mask &= ~(INT_TYPE_MASK << (IntrID % 16)*2);
	mask |= IntrType << (IntrID % 16)*2;
	XScuGic_DistWriteReg( IntcInstancePtr, INT_CFG0_OFFSET + (IntrID/16)*4, mask);
}


/******************************************************************************/
/**
*
* This function  performs a test on the GPIO driver/device with the GPIO
* configured as INPUT
*
* @param	 DeviceId is the XPAR_<GPIO_instance>_DEVICE_ID value from
*			  xparameters.h
* @param	 DataRead is the pointer where the data read from GPIO Input is
*			  returned
*
* @return	XST_SUCCESS if the Test is successful, otherwise XST_FAILURE
*
* @note	  None.
*
******************************************************************************/
int F2PIntcInitFunction(XScuGic *IntcInstancePtr)
{
	 int Status;
	 Status = XScuGic_Connect(IntcInstancePtr, F2P_Intr_DEVICE_ID,
	 				(Xil_InterruptHandler)F2P_intr_Handler,
	 				(void *)1);
	if (Status != XST_SUCCESS) {
		return Status;
	}

	/*
	 * Set interrupt type of F2P to rising edge.
	 */
	IntcTypeSetup(IntcInstancePtr, F2P_Intr_DEVICE_ID, INT_TYPE_RISING_EDGE);

	/*
	 * Enable the interrupt for the F2P device.
	 */
	XScuGic_Enable(IntcInstancePtr, F2P_Intr_DEVICE_ID);

	 return XST_SUCCESS;
}


void F2P_intr_Handler(void *param)
{
	Set_Fpga_Busy();
	get_rx_data_32bit(Fpga_data4, 354 * 4 + 4);
	memcpy(Fpga_data,Fpga_data4, 354 * 4 + 4);
	F2PInt1 = 1;

}

