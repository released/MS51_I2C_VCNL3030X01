/*
 * Main_User.c
 *
 * Created  : 23 July 2021
 * Modified : 4 August 2021
 * Author   : HWanyusof
 * Version	: 1.1
 */


#include "string.h"

#include "VCNL3030X01.h"
#include "VCNL3030X01_Prototypes.h"
#include "typedefinition.h"
#include "VCNL3030X01_Application_Library.h"
#include "Main_User.h"

#include "I2C_Functions.h"
//#include "MS51_16K.h"
#include "i2c_conf.h"
//Global Variables

//Switch the I2C Bus number here (Currently only tested with Teensy3.5 with possibility to use multiple i2c channels)
// I2C_Bus = 1 for Wire 1 (Pin 18-SDA, 19-SCL)
// I2C_Bus = 2 for Wire 2 (Pin 37-SCL, 38-SDA)
//Other Arduino family boards-please use I2C_Bus = 1
//Other platforms will not be affected
int I2C_Bus = 0;

//Variables for Offset Value
int CalibValue = 0;
int AverageCount = 10; //Change the average count to the needed number of offset measurement

//#define ENABLE_BASIC
#define ENABLE_ADVANCED


void HAL_Delay(unsigned int timing)
{
	Timer2_Delay(SYS_CLOCK,16,1,timing*1000);
}

int WriteI2C_Bus(TransferData *pData)
{
	I2Cx_Write_Multi_ToSlave(pData->Slave_Address , pData->RegisterAddress , pData->WData , 2);
	HAL_Delay(5);
	return TRUE;
}

int ReadI2C_Bus (TransferData *pData)
{
	I2Cx_Read_Multi_FromSlave(pData->Slave_Address , pData->RegisterAddress , pData->RData , 2);
	HAL_Delay(5);	
	return TRUE;
}


void INIT_VCNL3030X01()
{
	/* Reset Sensor to default value */
	Reset_Sensor();

	/****************************************************************************/
	/****************************Basic  Initialization***************************/
	/*
     *Basic_Initialization_Auto_Mode() uses the most basic steps to turn on
     *the Proximity Sensor. Very useful when first working with the sensor.
     *For the more advanced settings, you can use the Auto_Mode(), AF_Mode(),
     *and Low_Power_Mode() functions.
     */

	#if defined (ENABLE_BASIC)
	Basic_Initialization_Auto_Mode();
	#elif defined (ENABLE_ADVANCED)
	Auto_Mode();
//	AF_Mode();
//	Low_Power_Mode();
	#endif

	/***************************End of Initialization****************************/
    /****************************************************************************/
}

//Print Function
void PRINT_VCNL3030X01()
{
	/*
     *If you are using Basic_Initialization_Auto_Mode() to turn on the Proximity Sensor,
     *you can use Print_Data_Only() to read the proximity sensor.
     *If you are using more advanced settings like Auto_Mode(), AF_Mode(),
     *and Low_Power_Mode() functions, you can use all of the print functions :
     *Print_Data_Only() or Print_All().
     */

	/* Print the sensor output */
	#if defined (ENABLE_BASIC)
//	Print_Data_Only();
	#elif defined (ENABLE_ADVANCED)
//	Print_All();	

	Print_Data_Simple();
	#endif

}

//Auto/Self-Timed Mode Basic Initialization Function
void Basic_Initialization_Auto_Mode()
{
    //1.) Initialization
    //Disable the PS
    VCNL3030X01_SET_PS_SD(VCNL3030X01_PS_SD_DIS);
    //Setting up Auto Mode
    VCNL3030X01_SET_PS_AF(VCNL3030X01_PS_AUTO);
    //PS_SD will be set after all of the parameters have been set up

    //2.) Setting up PS
    //PS_CONF1
    //Set the Integration Time
    VCNL3030X01_SET_PS_IT(VCNL3030X01_PS_IT_8T);

    //PS_CONF2
    //Set the Output Bit Size
    VCNL3030X01_SET_PS_HD(VCNL3030X01_PS_HD_16Bits);

    //PS_CONF3
    //Enable/Disable Sunlight Cancellation
    VCNL3030X01_SET_PS_SC_EN(VCNL3030X01_PS_SC_EN);

    //PS_MS
    //Set the LED Current
    VCNL3030X01_SET_PS_LED_I(VCNL3030X01_PS_LED_I_200mA);

    //3.) Switch On the sensor
    VCNL3030X01_SET_PS_SD(VCNL3030X01_PS_SD_EN);

    //Delay needs to be changed depending on the API of the µ-controller
	HAL_Delay(1000);
}

//Low Power Mode Initialization Function
void Low_Power_Mode()
{
	int i=0;	
    //1.) Initialization
    //Disable the PS
    VCNL3030X01_SET_PS_SD(VCNL3030X01_PS_SD_DIS);
    //Setting up Auto Mode
    VCNL3030X01_SET_PS_AF(VCNL3030X01_PS_AUTO);
    //PS_SD will be set before measuring the offset or after all of the parameters have been set up

    //2.) Setting up PS
    //PS_CONF1
    //Set the PS IRED on/off Duty Ratio setting
    VCNL3030X01_SET_PS_DUTY(VCNL3030X01_PS_DR_1_40);
    //Set the Persistence
    VCNL3030X01_SET_PS_PERS(VCNL3030X01_PS_PERS_1);
    //Set the Integration Time
    VCNL3030X01_SET_PS_IT(VCNL3030X01_PS_IT_8T);

    //PS_CONF2
    //Set the Gain
    //Recommended to use VCNL3030X01_PS_GAIN_2_STEP
    VCNL3030X01_SET_PS_Gain(VCNL3030X01_PS_GAIN_2_STEP);
    //Set the Output Bit Size
    VCNL3030X01_SET_PS_HD(VCNL3030X01_PS_HD_16Bits);
    //Set the Sensitivity Mode
    //Recommended to use VCNL3030X01_PS_NS_2STEP_MODE_X4
    VCNL3030X01_SET_PS_NS(VCNL3030X01_PS_NS_2STEP_MODE_X4);
    //Set the Interrupt
    VCNL3030X01_SET_PS_INT(VCNL3030X01_PS_INT_CLOSE_AWAY);

    //PS_CONF3
    //Enable/Disable Low Current
    //When enabled -  1/10 of normal current set in LED_I,
    //with that the current is: 5 mA, 7.5 mA, 10 mA, 12 mA, 14 mA, 16 mA, 18 mA, 20 mA.
    //The current in VCNL3030X01_SET_PS_LED_I() still has to be set and the value will be 1/10 of that.
    VCNL3030X01_SET_PS_LED_I_LOW(VCNL3030X01_PS_I_LOW_EN);
    //Enable/Disable Smart Persistence
    VCNL3030X01_SET_PS_SMART_PERS(VCNL3030X01_PS_SMART_PERS_DIS);
    //Set Interrupt to Normal/Logic Mode
    VCNL3030X01_SET_PS_MS(VCNL3030X01_PS_MS_NORMAL);
    //Enable/Disable Sunlight Cancellation
    VCNL3030X01_SET_PS_SC_EN(VCNL3030X01_PS_SC_EN);
    //PS_AF has been set during initialization

    //PS_MS
    //Set the Sunlight Cancellation Current
    VCNL3030X01_SET_PS_SC_CUR(VCNL3030X01_PS_SC_CURx1);
    //Set the Sunlight Capability
    VCNL3030X01_SET_PS_SP(VCNL3030X01_PS_SPx1);
    //Set the Output of Sunlight Protect Mode
    VCNL3030X01_SET_PS_SPO(VCNL3030X01_PS_SPO_00);
    //Set the LED Current
    VCNL3030X01_SET_PS_LED_I(VCNL3030X01_PS_LED_I_200mA);

    //3.) Switch On the sensor
    VCNL3030X01_SET_PS_SD(VCNL3030X01_PS_SD_EN);
    //Delay of 10 ms needs to be changed depending on the API of the µ-controller of use
    HAL_Delay(10);

    //Clear Initial Interrupt
    VCNL3030X01_GET_PS_Interrupt();
    HAL_Delay(10);

	//4.) Threshold Setting and Offset Measurement
	for(i=0;i<AverageCount;i++)
	{
		CalibValue += VCNL3030X01_GET_PS_Data();
		//Delay of 10 ms needs to be changed depending on the API of the µ-controller of use
		HAL_Delay(10);
	}

	//Calculate the average of the offset measurement
	CalibValue /= AverageCount;

	//Set Cancellation register to eliminate offset
	VCNL3030X01_SET_PS_CANC(CalibValue);
	//Set Low Threshold
	VCNL3030X01_SET_PS_LowThreshold(3000);
	//set High Threshold
	VCNL3030X01_SET_PS_HighThreshold(5000);

    HAL_Delay(1000);
}

//AF/Continuous Forced Mode Initialization Function
void AF_Mode()
{
	int i=0;	
    //1.) Initialization
    //Disable the PS
    VCNL3030X01_SET_PS_SD(VCNL3030X01_PS_SD_DIS);
    //Setting up AF Mode
    VCNL3030X01_SET_PS_AF(VCNL3030X01_PS_AF_EN);
    //PS_SD will be set before measuring the offset or after all of the parameters have been set up

    //2.) Setting up PS
    //PS_CONF1
    //PS_DUTY does not play a role in AF Mode
    //Set the Persistence
    VCNL3030X01_SET_PS_PERS(VCNL3030X01_PS_PERS_1);
    //Set the Integration Time
    VCNL3030X01_SET_PS_IT(VCNL3030X01_PS_IT_8T);

    //PS_CONF2
    //Set the Gain
    //Recommended to use VCNL3030X01_PS_GAIN_2_STEP
    VCNL3030X01_SET_PS_Gain(VCNL3030X01_PS_GAIN_2_STEP);
    //Set the Output Bit Size
    VCNL3030X01_SET_PS_HD(VCNL3030X01_PS_HD_16Bits);
    //Set the Sensitivity Mode
    //Recommended to use VCNL3030X01_PS_NS_2STEP_MODE_X4
    VCNL3030X01_SET_PS_NS(VCNL3030X01_PS_NS_2STEP_MODE_X4);
    //Set the Interrupt
    VCNL3030X01_SET_PS_INT(VCNL3030X01_PS_INT_CLOSE_AWAY);

    //PS_CONF3
    //Enable/Disable Low Current
    VCNL3030X01_SET_PS_LED_I_LOW(VCNL3030X01_PS_I_LOW_DIS);
    //Enable/Disable Smart Persistence
    VCNL3030X01_SET_PS_SMART_PERS(VCNL3030X01_PS_SMART_PERS_DIS);
    //Set Interrupt to Normal/Logic Mode
    VCNL3030X01_SET_PS_MS(VCNL3030X01_PS_MS_NORMAL);
    //Enable/Disable Sunlight Cancellation
    VCNL3030X01_SET_PS_SC_EN(VCNL3030X01_PS_SC_EN);
    //PS_AF has been set during initialization
    //PS_TRIG must be set before reading the proximity data

    //PS_MS
    //Set the Sunlight Cancellation Current
    VCNL3030X01_SET_PS_SC_CUR(VCNL3030X01_PS_SC_CURx1);
    //Set the Sunlight Capability
    VCNL3030X01_SET_PS_SP(VCNL3030X01_PS_SPx1);
    //Set the Output of Sunlight Protect Mode
    VCNL3030X01_SET_PS_SPO(VCNL3030X01_PS_SPO_00);
    //Set the LED Current
    VCNL3030X01_SET_PS_LED_I(VCNL3030X01_PS_LED_I_200mA);

    //3.) Switch On the sensor
    VCNL3030X01_SET_PS_SD(VCNL3030X01_PS_SD_EN);
    //Delay of 10 ms needs to be changed depending on the API of the µ-controller of use
    HAL_Delay(10);

    //Clear Initial Interrupt
    VCNL3030X01_GET_PS_Interrupt();
    HAL_Delay(10);

	//4.) Threshold Setting and Offset Measurement
	for(i=0;i<AverageCount;i++)
	{
		//Enable trigger to start offset measurement
		VCNL3030X01_SET_PS_TRIG(VCNL3030X01_PS_TRIG_EN);
		//Delay of 10 ms needs to be changed depending on the API of the µ-controller of use
		HAL_Delay(10);
		CalibValue += VCNL3030X01_GET_PS_Data();
		//Delay of 10 ms needs to be changed depending on the API of the µ-controller of use
		HAL_Delay(10);
	}

	//Calculate the average of the offset measurement
	CalibValue /= AverageCount;

	//Set Cancellation register to eliminate offset
	VCNL3030X01_SET_PS_CANC(CalibValue);
	//Set Low Threshold
	VCNL3030X01_SET_PS_LowThreshold(3000);
	//set High Threshold
	VCNL3030X01_SET_PS_HighThreshold(5000);

    HAL_Delay(1000);
}

//Auto/Self-Timed Mode Initialization Function
void Auto_Mode()
{
	int i=0;
    //1.) Initialization
    //Disable the PS
    VCNL3030X01_SET_PS_SD(VCNL3030X01_PS_SD_DIS);
    //Setting up Auto Mode
    VCNL3030X01_SET_PS_AF(VCNL3030X01_PS_AUTO);
    //PS_SD will be set before measuring the offset or after all of the parameters have been set up

    //2.) Setting up PS
    //PS_CONF1
    //Set the PS IRED on/off Duty Ratio setting
    VCNL3030X01_SET_PS_DUTY(VCNL3030X01_PS_DR_1_40);
    //Set the Persistence
    VCNL3030X01_SET_PS_PERS(VCNL3030X01_PS_PERS_1);
    //Set the Integration Time
    VCNL3030X01_SET_PS_IT(VCNL3030X01_PS_IT_8T);

    //PS_CONF2
    //Set the Gain
    //Recommended to use VCNL3030X01_PS_GAIN_2_STEP
    VCNL3030X01_SET_PS_Gain(VCNL3030X01_PS_GAIN_2_STEP);
    //Set the Output Bit Size
    VCNL3030X01_SET_PS_HD(VCNL3030X01_PS_HD_16Bits);
    //Set the Sensitivity Mode
    //Recommended to use VCNL3030X01_PS_NS_2STEP_MODE_X4
    VCNL3030X01_SET_PS_NS(VCNL3030X01_PS_NS_2STEP_MODE_X4);
    //Set the Interrupt
    VCNL3030X01_SET_PS_INT(VCNL3030X01_PS_INT_CLOSE_AWAY);

    //PS_CONF3
    //Enable/Disable Low Current
    VCNL3030X01_SET_PS_LED_I_LOW(VCNL3030X01_PS_I_LOW_DIS);
    //Enable/Disable Smart Persistence
    VCNL3030X01_SET_PS_SMART_PERS(VCNL3030X01_PS_SMART_PERS_DIS);
    //Set Interrupt to Normal/Logic Mode
    VCNL3030X01_SET_PS_MS(VCNL3030X01_PS_MS_NORMAL);
    //Enable/Disable Sunlight Cancellation
    VCNL3030X01_SET_PS_SC_EN(VCNL3030X01_PS_SC_EN);
    //PS_AF has been set during initialization

    //PS_MS
    //Set the Sunlight Cancellation Current
    VCNL3030X01_SET_PS_SC_CUR(VCNL3030X01_PS_SC_CURx1);
    //Set the Sunlight Capability
    VCNL3030X01_SET_PS_SP(VCNL3030X01_PS_SPx1);
    //Set the Output of Sunlight Protect Mode
    VCNL3030X01_SET_PS_SPO(VCNL3030X01_PS_SPO_00);
    //Set the LED Current
    VCNL3030X01_SET_PS_LED_I(VCNL3030X01_PS_LED_I_200mA);

    //3.) Switch On the sensor
    VCNL3030X01_SET_PS_SD(VCNL3030X01_PS_SD_EN);
    //Delay of 10 ms needs to be changed depending on the API of the µ-controller of use
    HAL_Delay(10);

    //Clear Initial Interrupt
    VCNL3030X01_GET_PS_Interrupt();
    HAL_Delay(10);

	//4.) Threshold Setting and Offset Measurement
	for(i=0;i<AverageCount;i++)
	{
		CalibValue += VCNL3030X01_GET_PS_Data();
		//Delay of 10 ms needs to be changed depending on the API of the µ-controller of use
		HAL_Delay(10);
	}

	//Calculate the average of the offset measurement
	CalibValue /= AverageCount;

	//Set Cancellation register to eliminate offset
	VCNL3030X01_SET_PS_CANC(CalibValue);
	//Set Low Threshold
	VCNL3030X01_SET_PS_LowThreshold(3000);
	//set High Threshold
	VCNL3030X01_SET_PS_HighThreshold(5000);

	HAL_Delay(1000);
}
