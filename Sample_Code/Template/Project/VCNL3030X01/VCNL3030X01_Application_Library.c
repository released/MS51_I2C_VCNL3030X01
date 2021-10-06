/*
 * VCNL3030X01_Application_Library.c
 *
 * Created  : 23 July 2021
 * Modified : 4 August 2021
 * Author   : HWanyusof
 * Version	: 1.1
 */

#include "VCNL3030X01_Application_Library.h"
#include "VCNL3030X01_Prototypes.h"
#include "VCNL3030X01.h"
#include "I2C_Functions.h"
#include "typedefinition.h"
//#include "MS51_16K.h"

extern int I2C_Bus;

//****************************************************************************************************
//***************************************Application API**********************************************

/*Get Proximity Mode
 *returns the PS mode status of the sensor as follows:
 *
 * 0 - PS Shutdown Mode
 * 1 - Auto/Self-Timed Mode
 * 2 - Active Force Mode/Continuous Forced Mode
 * 4 - Low Power Mode
 *
 */
int VCNL3030X01_GET_PS_Mode()
{
	int Mode;

	//Read the PS_SD bit: Mode = 0 - PS Shutdown
	if (VCNL3030X01_GET_PS_SD_Bit() == 0x01) Mode = 0;

	//Read the PS_AF bit and PS_SD: Mode = 1 - Auto/Self-Timed Mode
	if ((VCNL3030X01_GET_PS_AF_Bit() == 0x00) && (VCNL3030X01_GET_PS_SD_Bit() == 0x00)) Mode = 1;

	//Read the PS_AF bit: Mode = 2 - AF Mode
	if (VCNL3030X01_GET_PS_AF_Bit() == 0x01) Mode = 2;

	//Read the LED_I_LOW bit: Mode = 4 - Low Power Mode
	if (VCNL3030X01_GET_LED_I_LOW_Bit() == 0x01) Mode = 4;

	return Mode;
}

//Reset the Sensor to the default value
void Reset_Sensor()
{
	TransferData VCNL3030X01_Data;
	VCNL3030X01_Data.Slave_Address = VCNL3030X01_SlaveAddress;
	VCNL3030X01_Data.RegisterAddress = VCNL3030X01_PS_CONF_1;
	VCNL3030X01_Data.Select_I2C_Bus = I2C_Bus;
	VCNL3030X01_Data.WData[0] = 0x01;
	VCNL3030X01_Data.WData[1] = 0x00;
	WriteI2C_Bus(&VCNL3030X01_Data);

	VCNL3030X01_Data.Slave_Address = VCNL3030X01_SlaveAddress;
	VCNL3030X01_Data.RegisterAddress = VCNL3030X01_PS_CONF_3;
	VCNL3030X01_Data.Select_I2C_Bus = I2C_Bus;
	VCNL3030X01_Data.WData[0] = 0x00;
	VCNL3030X01_Data.WData[1] = 0x00;
	WriteI2C_Bus(&VCNL3030X01_Data);

    VCNL3030X01_Data.Slave_Address = VCNL3030X01_SlaveAddress;
	VCNL3030X01_Data.RegisterAddress = VCNL3030X01_PS_CANC;
	VCNL3030X01_Data.Select_I2C_Bus = I2C_Bus;
	VCNL3030X01_Data.WData[0] = 0x00;
	VCNL3030X01_Data.WData[1] = 0x00;
	WriteI2C_Bus(&VCNL3030X01_Data);

	VCNL3030X01_Data.Slave_Address = VCNL3030X01_SlaveAddress;
	VCNL3030X01_Data.RegisterAddress = VCNL3030X01_PS_THDL;
	VCNL3030X01_Data.Select_I2C_Bus = I2C_Bus;
	VCNL3030X01_Data.WData[0] = 0x00;
	VCNL3030X01_Data.WData[1] = 0x00;
	WriteI2C_Bus(&VCNL3030X01_Data);

	VCNL3030X01_Data.Slave_Address = VCNL3030X01_SlaveAddress;
	VCNL3030X01_Data.RegisterAddress = VCNL3030X01_PS_THDH;
	VCNL3030X01_Data.Select_I2C_Bus = I2C_Bus;
	VCNL3030X01_Data.WData[0] = 0x00;
	VCNL3030X01_Data.WData[1] = 0x00;
	WriteI2C_Bus(&VCNL3030X01_Data);

	VCNL3030X01_Data.Slave_Address = VCNL3030X01_SlaveAddress;
	VCNL3030X01_Data.RegisterAddress = VCNL3030X01_INT_FLAG;
	VCNL3030X01_Data.Select_I2C_Bus = I2C_Bus;
	VCNL3030X01_Data.WData[0] = 0x00;
	VCNL3030X01_Data.WData[1] = 0x00;
	WriteI2C_Bus(&VCNL3030X01_Data);
}

/*Print all of the Register Value for both proximity and ambient light sensing functions
 *Print_All()
 */
void Print_All()
{
	unsigned int result;

	printf("*************************************************** \r\n");
	
	HAL_Delay(50);

	//Print PS Mode
	switch(VCNL3030X01_GET_PS_Mode())
	{
		case 0 :	printf(">>>>>>>Mode : PS Off/Shutdown \r\n");
					
					HAL_Delay(50);
					break;
		case 1 :	printf(">>>>>>>Mode : Auto/Self-Timed Mode \r\n");
					
					HAL_Delay(50);
					break;
		case 2 :	printf(">>>>>>>Mode : AF/Continuous Forced Mode \r\n");
					
					HAL_Delay(50);
					break;
		case 4 :	printf(">>>>>>>Mode : Low Power Mode \r\n");
					
					HAL_Delay(50);
					break;
	}

	printf(">>>>>>>>>>>>>>>>>>>>>>>>PS<<<<<<<<<<<<<<<<<<<<<<<<< \r\n");
	
	HAL_Delay(50);

	//Print the Reg 0x03 (PS_CONF1 and PS_CONF2)
	result = VCNL3030X01_READ_Reg(VCNL3030X01_PS_CONF_1);
	printf(">>>>>>>Reg 0x03 (PS_CONF1) Val : 0x%2BX ,0x%2BX\r\n",LOBYTE(result),HIBYTE(result) );
	
	HAL_Delay(50);

	//Print the Reg 0x04 (PS_CONF3 and PS_MS)
	result = VCNL3030X01_READ_Reg(VCNL3030X01_PS_CONF_3);
	printf(">>>>>>>Reg 0x04 (PS_CONF3) Val : 0x%2BX ,0x%2BX\r\n",LOBYTE(result),HIBYTE(result) );
	
	HAL_Delay(50);

	//Print the Reg 0x05 (PS_CANC)
	result = VCNL3030X01_READ_Reg(VCNL3030X01_PS_CANC);
	printf(">>>>>>>Reg 0x05 (PS_CANC) Val : %2Bd Counts \r\n",result);
	
	HAL_Delay(50);

	//Print the Reg 0x06 (PS_THDL)
	result = VCNL3030X01_READ_Reg(VCNL3030X01_PS_THDL);
	printf(">>>>>>>Reg 0x06 (PS_THDL) Val : %2Bd Counts \r\n",result);
	
	HAL_Delay(50);

	//Print the Reg 0x07 (PS_THDH)
	result = VCNL3030X01_READ_Reg(VCNL3030X01_PS_THDH);
	printf(">>>>>>>Reg 0x07 (PS_THDH) Val : %2Bd Counts \r\n",result);
	
	HAL_Delay(50);

	//Print Proximity Data (Only For Auto Mode, AF and Low Power Mode)
	if((VCNL3030X01_GET_PS_Mode() > 0) && (VCNL3030X01_GET_PS_Mode() < 5))
	{
		//Set Trigger for AF Mode + Associated delay due to IT
		if(VCNL3030X01_GET_PS_Mode() == 2)
		{
			//Set trigger to start a measurement
			VCNL3030X01_SET_PS_TRIG(VCNL3030X01_PS_TRIG_EN);

			//Delay of PS Measurement + other Circuit Delay
			HAL_Delay(50);
		}

		//Delay for Auto and Low Power Mode + Associated delay due to IT
		if((VCNL3030X01_GET_PS_Mode() == 1) || (VCNL3030X01_GET_PS_Mode() == 4))
		{
			//Delay of PS Measurement + other Circuit Delay
			HAL_Delay(50);
		}

		//Print the Proximity Data
		result = VCNL3030X01_READ_Reg(VCNL3030X01_PS_DATA);
		printf(">>>>>>>Proximity Data : %2Bd Counts<<<<<<<< \r\n",result);
		
		HAL_Delay(50);
	}

	printf("*************************************************** \r\n");
	
	HAL_Delay(50);

	#if 1
	//Print the Interrupt Flag
	result = VCNL3030X01_GET_PS_Interrupt();
	printf(">>>>>>>Interrupt Flag : 0x%2BX,0x%2BX<<<<<<<< \r\n",LOBYTE(result),HIBYTE(result) );
	
	HAL_Delay(50);

	printf("*************************************************** \r\n");
	
	HAL_Delay(50);

	printf(" \r\n");
	
	HAL_Delay(50);

	printf(" \r\n");
	
	HAL_Delay(2000);
	
	#endif
}

//Print the output of the sensor
void Print_Data_Only()
{
	unsigned int result;

	printf("*************************************************** \r\n");
	
	HAL_Delay(50);

	//Print PS Mode
	switch(VCNL3030X01_GET_PS_Mode())
	{
		case 0 :	printf(">>>>>>>Mode : PS Off/Shutdown \r\n");
					
					HAL_Delay(50);
					break;
		case 1 :	printf(">>>>>>>Mode : Auto/Self-Timed Mode \r\n");
					
					HAL_Delay(50);
					break;
		case 2 :	printf(">>>>>>>Mode : AF/Continuous Forced Mode \r\n");
					
					HAL_Delay(50);
					break;
		case 4 :	printf(">>>>>>>Mode : Low Power Mode \r\n");
					
					HAL_Delay(50);
					break;
	}

	printf(">>>>>>>>>>>>>>>>>>>>>>>>PS<<<<<<<<<<<<<<<<<<<<<<<<< \r\n");
	
	HAL_Delay(50);

	//Print Proximity Data (Only For Auto Mode, AF and Low Power Mode)
	if((VCNL3030X01_GET_PS_Mode() > 0) && (VCNL3030X01_GET_PS_Mode() < 5))
	{
		//Set Trigger for AF Mode + Associated delay due to IT
		if(VCNL3030X01_GET_PS_Mode() == 2)
		{
			//Set trigger to start a measurement
			VCNL3030X01_SET_PS_TRIG(VCNL3030X01_PS_TRIG_EN);

			//Delay of PS Measurement + other Circuit Delay
			HAL_Delay(50);
		}

		//Delay for Auto and Low Power Mode + Associated delay due to IT
		if((VCNL3030X01_GET_PS_Mode() == 1) || (VCNL3030X01_GET_PS_Mode() == 4))
		{
			//Delay of PS Measurement + other Circuit Delay
			HAL_Delay(50);
		}

		//Print the Proximity Data
		result = VCNL3030X01_READ_Reg(VCNL3030X01_PS_DATA);
		printf(">>>>>>>Proximity Data : %2Bd Counts<<<<<<<< \r\n",result);
		
		HAL_Delay(50);
	}

	printf("*************************************************** \r\n");
	
	HAL_Delay(50);

	#if 1
	//Print the Interrupt Flag
	result = VCNL3030X01_GET_PS_Interrupt();
	printf(">>>>>>>Interrupt Flag : 0x%2BX,0x%2BX<<<<<<<< \r\n",LOBYTE(result),HIBYTE(result) );
	
	HAL_Delay(50);

	printf("*************************************************** \r\n");
	
	HAL_Delay(50);

	printf(" \r\n");
	
	HAL_Delay(50);

	printf(" \r\n");

	HAL_Delay(2000);
	
	#endif	

}

void Print_Data_Simple(void)
{
	unsigned int result = 0;
	unsigned char mode = 0;
	
	const unsigned int error_handle = 33667;		// 0x83 , 0x83
	
	static unsigned int backup_Value = 0;
	static unsigned long int avg = 0;
	static unsigned char flag = 1;
	
	mode = 	VCNL3030X01_GET_PS_Mode();
	result = VCNL3030X01_READ_Reg(VCNL3030X01_PS_DATA);	

	// issue : sometimes value is 0x83 , 0x83
	if (result == error_handle)
	{
		result = backup_Value;
//		printf("**\r\n");		// debug
	}
	else
	{
		backup_Value = result;

		// do simple average		
		if (flag)
		{
			flag = 0;
			avg = result;
		}
		avg += result;
		avg = avg >> 1;
	}

	if ((mode == 0) || 
		(mode == 1) || 
		(mode == 2) || 
		(mode == 4) )
	{
		printf("0x%2BX : H :0x%2BX, L : 0x%2BX (dec : %5u)  \r\n" , mode,HIBYTE(result),LOBYTE(result) , (unsigned int)result );
		
	}
	
}

/*Print the variable in DEC for debugging
 *Print_Variable_DEC(Word Var)
 *Word Var - Input Parameter:
 *
 * Value between 0d0 and 0d65535
 */
//void Print_Variable_DEC(unsigned int Var)
//{

//	//	#define TRANSMIT_BUFFER_SIZE  128
//	//	char   TransmitBuffer[TRANSMIT_BUFFER_SIZE];
//	//	char   TransmitBuffer2[TRANSMIT_BUFFER_SIZE];

//	printf("*************************************************** \r\n");
//	
//	HAL_Delay(50);

//	printf(">>>>>>>Variable : 0d%d  \r\n",Var);
//	
//	HAL_Delay(50);

//	printf("*************************************************** \r\n");
//	

//	HAL_Delay(50);//HAL_Delay(2000);

//}

/*Print the variable in HEX for debugging
 *Print_Variable_HEX(Word Var)
 *Word Var - Input Parameter:
 *
 * Value between 0d0 and 0d65535
 */
//void Print_Variable_HEX(unsigned int Var)
//{

//	//	#define TRANSMIT_BUFFER_SIZE  128
//	//	char   TransmitBuffer[TRANSMIT_BUFFER_SIZE];
//	//	char   TransmitBuffer2[TRANSMIT_BUFFER_SIZE];

//	printf("*************************************************** \r\n");
//	
//	HAL_Delay(50);

//	printf(">>>>>>>Variable : 0x%2BX  \r\n",Var);
//	
//	HAL_Delay(50);

//	printf("*************************************************** \r\n");
//	

//	HAL_Delay(50);//HAL_Delay(2000);

//}

//Reverses a string 'str' of length 'len'
//void reverse(char* str, int len)
//{
//    int i = 0, j = len - 1, temp;
//    while (i < j) {
//        temp = str[i];
//        str[i] = str[j];
//        str[j] = temp;
//        i++;
//        j--;
//    }
//}

//Converts a given integer x to string str[].
//d is the number of digits required in the output.
//If d is more than the number of digits in x,
//then 0s are added at the beginning.
//int intToStr(int x, char str[], int d)
//{
//    int i = 0;

//    while (x)
//	{
//		//Store and convert int to char (Valid for single digit)
//        str[i++] = (x % 10) + '0';
//        x = x / 10;
//    }

//    //If number of digits required is more, then
//    //add 0s at the beginning
//    while (i < d) str[i++] = '0';

//	//Reverse the string characters in the array str
//    reverse(str, i);

//	//Place the null character at the end of the array
//    str[i] = '\0';

//	//Return the position i
//    return i;
//}

//Converts a floating-point/double number to a string.
//void ftoa(float n, char* res, int afterpoint)
//{
//    //Extract integer part
//    int ipart = (int)n;

//    //Extract decimal part
//    float fpart = n - (float)ipart;

//    //Convert integer part to string and the function returns the position after the interger
//    int i = intToStr(ipart, res, 0);

//    //Check for display option after point
//    if (afterpoint != 0)
//	{
//		//Add dot after the integer part
//        res[i] = '.';

//        //Multiply decimal part by 10^decimal point
//        fpart = fpart* pow(10, afterpoint);

//		//Convert decimal part to string
//        intToStr((int)fpart, res + i + 1, afterpoint);
//    }
//}



